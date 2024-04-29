#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>

unsigned long lastrx; 
unsigned long elapsed; 
void setup()
{
  Serial.begin(9600);
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;
  delay(1000);
  Radio.Init();
  Radio.SetDataRate(3); // Needs to be the same in Tx and Rx
  Radio.SetLogicalChannel(0); // Needs to be the same as receiver
	lastrx=millis();
  Radio.RxOn();
}

byte RX_buffer[1]={0};
byte sizerx,i,flag;

void loop()
{
  if(Radio.CheckReceiveFlag())
  {
    lastrx = millis();
    sizerx=Radio.ReceiveData(RX_buffer);
    // Should be one byte
    //Serial.write(RX_buffer[0]);
    Serial.println( RX_buffer[0], DEC);
    if (RX_buffer[0] == 3)
      P1OUT ^= BIT0;
    Radio.RxOn();
  }
}


