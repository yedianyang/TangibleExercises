/*
 * The led blink once when the knob change 10%
 * 
 * 2/23/2021 yedianyang
*/

#define LED 2
#define Knob A0

bool isOverThreshold = false;
int ledThreshold = 512;
int knobStep = 102; //1024 * 10%;
float currentStage = 0; //Can't be an int


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  currentStage = analogRead(Knob);
}


void loop() {
  int knobRead = map(analogRead(Knob), 0, 1024, 0, 1021);
  Serial.println(knobRead - currentStage);
  Serial.println(knobRead);

  if (abs((knobRead - currentStage)) > 6) {
    if (knobRead % knobStep == 0) {
      ledBlink();
      currentStage = knobRead;
    }
  }
}


void ledBlink() {
  digitalWrite(LED, HIGH);
  delay(111);
  digitalWrite(LED, LOW);
  delay(111);
}

void ledOff() {
  digitalWrite(LED, LOW);
}
