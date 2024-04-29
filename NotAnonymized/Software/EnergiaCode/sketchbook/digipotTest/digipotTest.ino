#define INC 25
#define UD  24
#define CS  23  // Used to store the wiper value
volatile uint8_t count = 100;
int button1State = 0;
int button2State = 0;

void setup() {
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);  
  P1DIR |= BIT0;
  P9DIR |= BIT7;
  pinMode(UD,  OUTPUT);
  pinMode(CS,  OUTPUT);
  pinMode(INC, OUTPUT);
  digitalWrite(CS,  LOW);
  digitalWrite(UD,  LOW);
  digitalWrite(INC, HIGH);
}

void loop() {
  button1State = digitalRead(PUSH1);
  button2State = digitalRead(PUSH2);
  // Decrement
  if (button1State == LOW && count > 0) {
    P1OUT |= BIT0;
    digitalWrite(UD, LOW);
    digitalWrite(INC, LOW);
    delayMicroseconds(5);
    digitalWrite(INC, HIGH);
    count--;
    delay(50);
  } else P1OUT &= ~BIT0;
  // Increment
  if (button2State == LOW && count < 100) {
    P9OUT |= BIT7;
    digitalWrite(UD, HIGH);
    digitalWrite(INC, LOW);
    delayMicroseconds(5);
    digitalWrite(INC, HIGH);
    count++;
    delay(50);
  } else P9OUT &= ~BIT7;
}
