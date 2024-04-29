#include <cc1101.h>
#include <registers.h>
#include <pins.h>
#include <stdint.h>
#include <macros.h>

const uint8_t echoTrigPin = 32;     // Trigger pin to echo sensor
const uint8_t echoReturnPin = 33;   // Output pin from echo sensor
const double sensorHeight = 79.0;   // height of echo sensor from floor (inches)
volatile uint8_t isrFlag = 0;      // interrupt flag
uint8_t echoData[1] = {0};

/* Setup code -- runs once on startup. */
void setup() {
   /* Initialize the CC1101 Radio module. */
   Radio.Init();
   Radio.SetDataRate(4);         // 38.313 kBaud
   Radio.SetLogicalChannel(2);   // Set the radio to channel 105
   Radio.SetTxPower(7);          // 11.9 mA
   Radio.Wakeup();
   delayMicroseconds(100);
   /* Enable the LED. */
   P1DIR |= BIT0;
   P1OUT &= ~BIT0;
   /* Enable the echo sensor. */
   pinMode(echoTrigPin, OUTPUT);
   pinMode(echoReturnPin, INPUT);
   /* Enable interrupts on P2.4 & P2.5 */
   P2OUT = BIT5 | BIT4;       // Enable pull-up resistors
   P2REN = BIT5 | BIT4;
   P2DIR &= ~(BIT5 | BIT4);   // Set input direction
   P2IES &= ~BIT4;            // Comparator1 low to high
   P2IES |= BIT5;             // Comparator2 high to low
   P2IFG = 0;                 // Clear all P1 interrupt flags
   P2IE = BIT5 | BIT4;        // Enable P2.4 & P2.5 interrupts
   __bis_SR_register(GIE);    // Enable general interrupts
}

/* Main program loop. */
void loop() {
   __bis_SR_register(LPM3_bits); // Enter LPM3
   if (isrFlag) {
      P2IE = 0;                  // Turn off Port_2 interrupts
      P1OUT |= BIT3;             // CSN echo sensor
      fireEchoSensor();
      P1OUT &= ~BIT3;            // Deselect echo sensor
      delayMicroseconds(50);
      transmitData();            // Transmit height data
      P1OUT ^= BIT0;             // Toggle LED
      isrFlag = 0;               // Clear interrupt flag
      P2IFG = 0;                 // Clear all P2 interrupt flags
      P2IE = BIT5 | BIT4;        // Enable P2.4 & P2.5 interrupts
   }
}

/* Take measurement with ultrasonic sensor. */
void fireEchoSensor() {
	digitalWrite(echoTrigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(echoTrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(echoTrigPin, LOW);

	double dist;
	dist = pulseIn(echoReturnPin, HIGH);
	dist *= 0.0001657;		// convert pulse width to meters
	dist *= 39.3701;			// convert meters to inches
   dist = sensorHeight-dist; // distance from person to sensor

   /* Discard any measurements that are too small or too large. */
   if(dist > 6.0 && dist < sensorHeight) {
      echoData[0] = (uint8_t)dist;
   }
	delayMicroseconds(50);
}

/* Send most recent echo sensor data. */
void transmitData() {
   Radio.SendData(echoData, 1);
   delay(1);
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
      isrFlag = 1;     // Set interrupt flag
      P2IFG &= ~BIT4;   // Clear P2.4 IFG
   }
   if (P2IFG & BIT5) {
      isrFlag = 1;     // Set interrupt flag
      P2IFG &= ~BIT5;   // Clear P2.5 IFG
  }
  __bic_SR_register_on_exit(LPM3_bits);   // Exit LPM3
}
