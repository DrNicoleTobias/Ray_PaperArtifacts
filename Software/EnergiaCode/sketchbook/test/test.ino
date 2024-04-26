const uint16_t echoTrigPin = 32;    // Trigger pin to echo sensor
const uint16_t echoReturnPin = 33;  // Output pin from echo sensor
const double sensorHeight = 83.5;   // height of echo sensor from floor (inches)

volatile uint8_t flag = 0;

void setup() {
   /* Enable the LEDs. */
   P1DIR |= BIT0;
   P1OUT &= ~BIT0;
   P9DIR |= BIT7;
   P9OUT &= ~BIT7;

   /* Enable serial communication and the echo sensor. */
   Serial.begin(9600);
   pinMode(echoTrigPin, OUTPUT);
   pinMode(echoReturnPin, INPUT);

   /* Enable interrupts on P2.4 & P2.5 */
   P2OUT = BIT5 | BIT4;       // Enable pull-up resistors
   P2REN = BIT5 | BIT4;
   P2DIR &= ~(BIT5 | BIT4);   // Set input direction
   P2IES &= ~BIT4;            // Comparator1 low to high
   P2IES |= BIT5;             // Comparator high to low
   P2IFG = 0;                 // Clear all P1 interrupt flags
   P2IE = BIT5 | BIT4;        // Enable P2.4 & P2.5 interrupts
   __bis_SR_register(GIE);    // Enable general interrupts
}

void loop() {
   __bis_SR_register(LPM3_bits); // Enter LPM3
   if (flag) {
      P2IE = 0;                  // Turn off Port_2 interrupts
      fireEchoSensor();
      P1OUT ^= BIT0;             // Toggle Red LED
      flag = 0;                  // Clear int flag
      P2IFG = 0;                 // Clear all P2 interrupt flags
      P2IE = BIT5 | BIT4;        // Enable P2.4 & P2.5 interrupts
   }
}

/* Take measurement with ultrasonic sensor. */
void fireEchoSensor() {
   Serial.println("Echo");
	digitalWrite(echoTrigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(echoTrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(echoTrigPin, LOW);

	double distance;
	distance = pulseIn(echoReturnPin, HIGH);
	distance *= 0.0001657;		// convert pulse width to meters
	distance *= 39.3701;			// convert meters to inches

   if(sensorHeight-distance > 6.0) {
      Serial.println("Human detected.");
   	Serial.println();
   	Serial.print(sensorHeight-distance);
   	Serial.println(" in");
   	Serial.println();
   }
	delayMicroseconds(50);
}

// Port 2 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void)
#else
#error Compiler not supported!
#endif
{
   if (P2IFG & BIT4) {
      flag = 1;
      P2IFG &= ~BIT4;                           // Clear P1.1 IFG
   }
   if (P2IFG & BIT5) {
      flag = 1;
      P2IFG &= ~BIT5;                           // Clear P1.1 IFG
  }
  __bic_SR_register_on_exit(LPM3_bits);     // Exit LPM4
}
