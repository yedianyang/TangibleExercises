/*
 * The led blinking 10% faster when press the button
 * 
 * 2/23/2021 yedianyang
*/

#define LED 2
#define Button 3

int blinkTime = 1000;


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
  
  attachInterrupt(Button, speedChange, RISING);
}

void loop() {
  ledBlink();
}

void ledBlink() {
  digitalWrite(LED, HIGH);
  delay(blinkTime);
  digitalWrite(LED, LOW);
  delay(blinkTime);
}

void ledOff() {
  digitalWrite(LED, LOW);
}

void speedChange() {
  Serial.println("press");
  blinkTime *= 0.9;
}
