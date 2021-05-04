/*
 * When the knob crosses a threshold,
 * LED Blink
 * 
 * 2/23/2021 yedianyang
 */


#define LED 2
#define Knob A0

bool isOverThreshold = false;
int ledThreshold = 1000;


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

}

void loop() {
  Serial.println(analogRead(Knob));

  if (analogRead(Knob) > ledThreshold) {
    if (!isOverThreshold) {
      ledBlinkOnce();
    }
    isOverThreshold = true;
  }

  if (analogRead(Knob) < ledThreshold) {
    isOverThreshold = false;
  }

}


void ledBlinkOnce() {
  digitalWrite(LED, HIGH);
  delay(666);
  digitalWrite(LED, LOW);
}
