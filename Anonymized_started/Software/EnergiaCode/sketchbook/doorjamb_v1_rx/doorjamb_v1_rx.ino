#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>

unsigned long lastrx;
byte RX_buffer[1]={0};
byte sizerx,i,flag;

/* Setup code -- runs once on startup. */
void setup() {
   /* Open the Serial port. */
   Serial.begin(9600);
   delay(1000);
   /* Initialize the CC1101 Radio module. */
   Radio.Init();
   Radio.SetDataRate(4);         // Needs to be the same in both tx & rx
   Radio.SetLogicalChannel(2);   // Needs to be the same in both tx & rx
   lastrx = millis();
   Radio.RxOn();
   /* Enable the LED. */
   P1DIR |= BIT0;
   P1OUT &= ~BIT0;
}

/* Main program loop. */
void loop() {
   if(Radio.CheckReceiveFlag()) {
      lastrx = millis();
      sizerx = Radio.ReceiveData(RX_buffer);
      Serial.println(RX_buffer[0], DEC);
      Radio.RxOn();
      P1OUT ^= BIT0;   // toggle LED
   }
}
