const uint16_t echoTrigPin = 32;    // Trigger pin to echo sensor
const uint16_t echoReturnPin = 33;  // Output pin from echo sensor
const double sensorHeight = 83.5;   // height of echo sensor from floor (inches)
volatile uint8_t isr_flag = 0;

void setup() {

   /* 1. Enable the MOSFET signal pin. */
   P1DIR |= BIT3;
   P1OUT &= ~BIT3;

   /* 2. Enable the LED. */
   P1DIR |= BIT0;
   P1OUT &= ~BIT0;

   /* 3. Enable serial communication and the echo sensor. */
   Serial.begin(9600);
   pinMode(echoTrigPin, OUTPUT);
   pinMode(echoReturnPin, INPUT);

   /* 4. Enable interrupts on P2.4 & P2.5 */
   P2OUT = BIT5 | BIT4;       // Enable pull-up resistors
   P2REN = BIT5 | BIT4;
   P2DIR &= ~(BIT5 | BIT4);   // Set input direction
   P2IES &= ~BIT4;            // Comparator1 low to high
   P2IES |= BIT5;             // Comparator2 high to low
   P2IFG = 0;                 // Clear all P1 interrupt flags
   P2IE = BIT5 | BIT4;        // Enable P2.4 & P2.5 interrupts
   __bis_SR_register(GIE);    // Enable general interrupts
}

void loop() {
   __bis_SR_register(LPM3_bits); // Enter LPM3
   if (isr_flag) {
      P2IE = 0;                  // Turn off Port_2 interrupts
      P1OUT |= BIT3;
      fireEchoSensor();
      P1OUT |= ~BIT3;
      delayMicroseconds(50);
      P1OUT &= BIT0;             // Turn LED on
      delayMicroseconds(1000);
      P1OUT &= ~BIT0;            // Turn LED off
      isr_flag = 0;              // Clear int flag
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
   	Serial.print(sensorHeight-distance);
   	Serial.println(" in");
   	Serial.println();
   }
	delayMicroseconds(50);
}

/* Port 2 interrupt service routine */
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
      isr_flag = 1;     // Set isr flag
      P2IFG &= ~BIT4;   // Clear P2.4 IFG
   }
   if (P2IFG & BIT5) {
      isr_flag = 1;     // Set isr flag
      P2IFG &= ~BIT5;   // Clear P2.5 IFG
  }
  __bic_SR_register_on_exit(LPM3_bits);   // Exit LPM3
}
