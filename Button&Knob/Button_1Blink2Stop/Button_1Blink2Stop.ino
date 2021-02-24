/*
 * Press button once led blinking, 
 * Press button twice led stop blinking
 * 
 * 2/24/2021 yedianyang
*/

#define LED 2
#define Button 3
int blinkTime = 500;

int pressSpeedRange = 1000;
int pressTime = 0;
bool ledState = false;
int pressCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT_PULLUP);

  attachInterrupt(Button, buttonPressed, RISING);
}

void loop() {
  
  if (pressCount >= 2) {
    Serial.println(millis() - pressTime);
    if (millis() - pressTime < pressSpeedRange) {
      
      ledState = false;
      pressCount = 0;
    }
  }

  if (pressCount == 1) {
    ledState = true;
  }


  Serial.println(pressCount);

  if (ledState) {
    ledBlink();
  } else {
    ledOff();
  }
}


void buttonPressed() {
  pressTime = millis();
  pressCount += 1;
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
