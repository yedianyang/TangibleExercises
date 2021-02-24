/*
 * When the knob crosses a threshold,
 * LED Blink
 * 
 * 2/23/2021 yedianyang
 */


#define LED 2
#define Knob A0

bool isOverThreshold = false;
int ledThreshold = 512;


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

}

void loop() {
  Serial.println(analogRead(Knob));

  if (analogRead(Knob) > ledThreshold) {
    ledBlink();
  } else {
    ledOff();
  }

}


void ledBlink() {
  digitalWrite(LED, HIGH);
  delay(333);
  digitalWrite(LED, LOW);
  delay(333);
}

void ledOff() {
  digitalWrite(LED, LOW);
}
