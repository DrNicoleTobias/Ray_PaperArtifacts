volatile uint32_t count = 0;

void setup()
{
  // put your setup code here, to run once:
  WDTCTL = WDTPW | WDTHOLD;
  PM5CTL0 &= ~LOCKLPM5;
  P8DIR |= BIT5;
  P9DIR |= BIT7;
}

void loop()
{
  // put your main code here, to run repeatedly:
  P8OUT ^= BIT5;
  P9OUT ^= BIT7;
  count = 1000000;
  do count--;
  while (count != 0);

}
