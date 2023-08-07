#define PIN_A 2
#define PIN_B 3
#define PIN_C 4
#define PIN_D 6
#define PIN_E 5
#define PIN_F 7
#define PIN_G 8
#define PIN_ENABLE  9

#define LIGHT_A   0x01
#define LIGHT_B   0x02
#define LIGHT_C   0x04
#define LIGHT_D   0x08
#define LIGHT_E   0x10
#define LIGHT_F   0x20
#define LIGHT_G   0x40

int onesDigit[] = {LIGHT_A | LIGHT_B | LIGHT_C | LIGHT_D | LIGHT_E | LIGHT_F, LIGHT_B | LIGHT_C, LIGHT_A | LIGHT_B | LIGHT_G | LIGHT_E | LIGHT_D, LIGHT_A | LIGHT_B | LIGHT_G | LIGHT_C | LIGHT_D,
  LIGHT_F | LIGHT_G | LIGHT_B | LIGHT_C, LIGHT_A | LIGHT_F | LIGHT_G | LIGHT_C | LIGHT_D, LIGHT_F | LIGHT_G | LIGHT_C | LIGHT_D | LIGHT_E, LIGHT_A | LIGHT_B | LIGHT_C,
  LIGHT_A | LIGHT_B | LIGHT_C | LIGHT_D | LIGHT_E | LIGHT_F | LIGHT_G, LIGHT_A | LIGHT_F | LIGHT_G | LIGHT_B | LIGHT_C};

int tensDigit[] = {};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int randNumber = random(1,20);
  Serial.println(randNumber);
  
  delay(100);
}

void lightLEDs(bool ones, int value) { 
  int currentSegments;
  
  if (ones) {
    digitalWrite(PIN_ENABLE, LOW);
    currentSegments = onesDigit[value];
  } else  { 
    digitalWrite(PIN_ENABLE, HIGH);
    currentSegments = tensDigit[value];
  }

  digitalWrite(PIN_A, currentSegments & LIGHT_A);
  digitalWrite(PIN_B, currentSegments & LIGHT_B);
  digitalWrite(PIN_C, currentSegments & LIGHT_C);
  digitalWrite(PIN_D, currentSegments & LIGHT_D);
  digitalWrite(PIN_E, currentSegments & LIGHT_E);
  digitalWrite(PIN_F, currentSegments & LIGHT_F);
  digitalWrite(PIN_G, currentSegments & LIGHT_G);
}
