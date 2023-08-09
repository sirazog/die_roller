#define PIN_A 2
#define PIN_B 3
#define PIN_C 4
#define PIN_D 5
#define PIN_E 6
#define PIN_F 7
#define PIN_G 8
#define PIN_ENABLE  9

#define SEG_A   0x01
#define SEG_B   0x02
#define SEG_C   0x04
#define SEG_D   0x08
#define SEG_E   0x10
#define SEG_F   0x20
#define SEG_G   0x40

//       --A--
//      |     |
//      F     B
//      |     |
//       --G--
//      |     |
//      E     C
//      |     |
//       --D--

int segments[] = { /* 0 */ SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
                   /* 1 */         SEG_B | SEG_C,
                   /* 2 */ SEG_A | SEG_B         | SEG_D | SEG_E         | SEG_G,
                   /* 3 */ SEG_A | SEG_B | SEG_C | SEG_D                 | SEG_G,
                   /* 4 */         SEG_B | SEG_C                 | SEG_F | SEG_G,
                   /* 5 */ SEG_A         | SEG_C | SEG_D         | SEG_F | SEG_G,
                   /* 6 */                 SEG_C | SEG_D | SEG_E         | SEG_G,
                   /* 7 */ SEG_A | SEG_B | SEG_C,
                   /* 8 */ SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
                   /* 9 */ SEG_A | SEG_B | SEG_C                 | SEG_F | SEG_G
                };

#define TENS_DIGIT  10
#define ONES_DIGIT  1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_ENABLE, OUTPUT);

  digitalWrite(PIN_ENABLE, HIGH);
  digitalWrite(PIN_D, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  int randNumber = random(1,20);
  Serial.println(randNumber);
  
  delay(100);
}

void displayNumber(int number) {

}

void lightLEDs(int digit, int number) { 
  int currentSegments = segments[digit];
  uint8_t on, off;
  
  switch (digit) {
    case ONES_DIGIT:
      on = LOW;
      off = HIGH;
      digitalWrite(PIN_ENABLE, HIGH);
      break;
    case TENS_DIGIT:
      on = HIGH;
      off = LOW;
      digitalWrite(PIN_ENABLE, LOW);
      break;
    
    return;
  }

  digitalWrite(PIN_A, (currentSegments & SEG_A) ? on : off);
  digitalWrite(PIN_B, (currentSegments & SEG_B) ? on : off);
  digitalWrite(PIN_C, (currentSegments & SEG_C) ? on : off);
  digitalWrite(PIN_D, (currentSegments & SEG_D) ? on : off);
  digitalWrite(PIN_E, (currentSegments & SEG_E) ? on : off);
  digitalWrite(PIN_F, (currentSegments & SEG_F) ? on : off);
  digitalWrite(PIN_G, (currentSegments & SEG_G) ? on : off);
}
