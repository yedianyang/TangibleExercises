/*
 * When the knob crosses a threshold,
 * LED Blink
 * 
 * 2/23/2021 yedianyang
 */
 
#define LED 2
#define Knob A0

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  while (analogRead(Knob) < 1000) {
    Serial.println(analogRead(Knob));
  }
  digitalWrite(2, HIGH);
  delay(2000);
  digitalWrite(2, LOW);
}


void loop() {
 //
}
