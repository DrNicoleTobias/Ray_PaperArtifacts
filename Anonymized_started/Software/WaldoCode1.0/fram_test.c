#include <msp430fr6989.h>

void FRAMWrite(void);

unsigned char count = 0;
unsigned long *FRAM_write_ptr;
unsigned long data;

#define FRAM_TEST_START 0x10000

int main(void)
{
 WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

 // Configure GPIO
 P1OUT &= ~BIT0;                           // Clear P1.0 output latch for a defined power-on state
 P1DIR |= BIT0;                            // Set P1.0 to output direction

 // Disable the GPIO power-on default high-impedance mode to activate
 // previously configured port settings
 PM5CTL0 &= ~LOCKLPM5;

 // Initialize dummy data
 data = 0x00;
 FRAM_write_ptr = (unsigned long *)FRAM_TEST_START;
 FRAMWrite();

 // while(1)
 // {
 //   data += 0x00010001;
 //   FRAM_write_ptr = (unsigned long *)FRAM_TEST_START;
 //   FRAMWrite();                            // Endless loop
 //   count++;
 //   if (count > 100)
 //   {
 //     P1OUT ^= 0x01;                        // Toggle LED to show 512K bytes
 //     count = 0;                            // ..have been written
 //     data = 0x00010001;
 //   }
 // }
}

void FRAMWrite(void)
{
 unsigned int i=0;
 *FRAM_write_ptr = data;
 for ( i= 0; i<128; i++)
 {
   FRAM_write_ptr[i] = data;
 }
}
