#define PIN_A 2
#define PIN_B 3
#define PIN_C 4
#define PIN_D 5
#define PIN_E 6
#define PIN_F 7
#define PIN_G 8
#define PIN_SELECT_ONES  9
#define PIN_SELECT_TENS  10

#define DIGIT_SELECT  LOW
#define DIGIT_DESELECT  HIGH

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

int segments[] = { /* 0 */  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
                   /* 1 */          SEG_B | SEG_C,
                   /* 2 */  SEG_A | SEG_B         | SEG_D | SEG_E         | SEG_G,
                   /* 3 */  SEG_A | SEG_B | SEG_C | SEG_D                 | SEG_G,
                   /* 4 */         SEG_B | SEG_C                  | SEG_F | SEG_G,
                   /* 5 */  SEG_A         | SEG_C | SEG_D         | SEG_F | SEG_G,
                   /* 6 */                  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
                   /* 7 */  SEG_A | SEG_B | SEG_C,
                   /* 8 */  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
                   /* 9 */  SEG_A | SEG_B | SEG_C                 | SEG_F | SEG_G
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
  pinMode(PIN_SELECT_ONES, OUTPUT);
  pinMode(PIN_SELECT_TENS, OUTPUT);

  digitalWrite(PIN_A, HIGH);
  digitalWrite(PIN_B, HIGH);
  digitalWrite(PIN_C, HIGH);
  digitalWrite(PIN_D, HIGH);
  digitalWrite(PIN_E, HIGH);
  digitalWrite(PIN_F, HIGH);
  digitalWrite(PIN_G, HIGH);
  digitalWrite(PIN_SELECT_ONES, HIGH);
  digitalWrite(PIN_SELECT_TENS, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  int randNumber = random(1,99);
  //Serial.println(randNumber);
  displayNumber(randNumber);
  delay(500);
}

void displayNumber(int number) {
  int digits = countDigits(number);

  if (digits > 2) {
    while (digits > 2) {
      number /= 10;
      digits--;
    }
  } 

  int startTime = millis();

  while (! (millis() > startTime + 500)) {
    lightLEDs(TENS_DIGIT, number / 10);
    lightLEDs(ONES_DIGIT, number % 10);
  }

}

void lightLEDs(int digit, int number) { 
  int currentSegments = segments[number];
  uint8_t on = HIGH; 
  uint8_t off = LOW;
  
  switch (digit) {
    case ONES_DIGIT:
      digitalWrite(PIN_SELECT_ONES, DIGIT_SELECT);
      digitalWrite(PIN_SELECT_TENS, DIGIT_DESELECT);
      break;
    case TENS_DIGIT:
      digitalWrite(PIN_SELECT_TENS, DIGIT_SELECT);
      digitalWrite(PIN_SELECT_ONES, DIGIT_DESELECT);
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

int countDigits(int number) {
  int digits = 0;
  while (number != 0) {
    number /= 10;
    digits++;
  }

  return digits;
}
