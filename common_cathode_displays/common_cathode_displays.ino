//display pins
#define PIN_A 2
#define PIN_B 3
#define PIN_C 4
#define PIN_D 5
#define PIN_E 6
#define PIN_F 7
#define PIN_G 8
#define PIN_SELECT_ONES  9
#define PIN_SELECT_TENS  10

//bcd pins
#define ONES_COMMON 22
#define ONES_ONE    24
#define ONES_TWO    26
#define ONES_FOUR   28
#define ONES_EIGHT  30

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
#define MUX_DELAY   10 //milliseconds

unsigned long startTime = 0;
int randomCounter = 0;
int randomNumber = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

  pinMode(ONES_COMMON, OUTPUT);
  pinMode(ONES_ONE, INPUT);
  pinMode(ONES_TWO, INPUT);
  pinMode(ONES_FOUR, INPUT);
  pinMode(ONES_EIGHT, INPUT);

  digitalWrite(ONES_COMMON, LOW);

  displayOff();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("randomCounter: ");
  //Serial.println(randomCounter);
  Serial.println(readBCD());

  if (randomCounter <= 0) {
    randomNumber = random(1,99);
    //Serial.println(randomNumber);
    randomCounter = 250;
  } else {
    randomCounter--;
  }
  
  displayNumber(randomNumber);
}

void displayNumber(int number) {
  if (number > 99) {
    number %= 100;
  } 

  while(millis() < startTime + MUX_DELAY) {} //Wait if we haven't displayed the last digit long enough

  lightLEDs(TENS_DIGIT, number / 10);
  //Serial.println("number / 10: ");
  //Serial.print(number / 10);
  delay(MUX_DELAY);

  lightLEDs(ONES_DIGIT, number % 10);
  //Serial.println("number % 10: ");
  //Serial.print(number % 10);
  startTime = millis();

  //Serial.println("End of displayNumber");

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
    
  }

  digitalWrite(PIN_A, (currentSegments & SEG_A) ? on : off);
  digitalWrite(PIN_B, (currentSegments & SEG_B) ? on : off);
  digitalWrite(PIN_C, (currentSegments & SEG_C) ? on : off);
  digitalWrite(PIN_D, (currentSegments & SEG_D) ? on : off);
  digitalWrite(PIN_E, (currentSegments & SEG_E) ? on : off);
  digitalWrite(PIN_F, (currentSegments & SEG_F) ? on : off);
  digitalWrite(PIN_G, (currentSegments & SEG_G) ? on : off);
}

void displayOff() {
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);
  digitalWrite(PIN_C, LOW);
  digitalWrite(PIN_D, LOW);
  digitalWrite(PIN_E, LOW);
  digitalWrite(PIN_F, LOW);
  digitalWrite(PIN_G, LOW);
  digitalWrite(PIN_SELECT_ONES, LOW);
  digitalWrite(PIN_SELECT_TENS, LOW);
}

int readBCD() {
  int value = 0;
  
  // (value & digitalRead(ONES_ONE)) ? value++ : value;
  // (value & digitalRead(ONES_TWO)) ? value += 2 : value;
  // (value & digitalRead(ONES_FOUR)) ? value += 4 : value;
  // (value & digitalRead(ONES_EIGHT)) ? value += 8 : value;

  if (digitalRead(ONES_ONE))
    value++;
  if (digitalRead(ONES_TWO))
    value += 2;
  if (digitalRead(ONES_FOUR))
    value += 4;
  if (digitalRead(ONES_EIGHT))
    value += 8;
  
  return value;
}
