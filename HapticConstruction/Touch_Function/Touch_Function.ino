#define FSR01 10
#define FSR02 9
#define FSR03 8
#define DISTANCE01 7



void setup() {
  Serial.begin(9600);
  pinMode(FSR01, INPUT);
  pinMode(FSR02, INPUT);
  pinMode(FSR03, INPUT);
  pinMode(DISTANCE01, INPUT);
}


void loop() {
  int fsr01 = analogRead(FSR01);
  delay(1);
  int fsr02 = analogRead(FSR02);
  delay(1);
  int fsr03 = analogRead(FSR03);
  delay(1);
  int Distance = analogRead(DISTANCE01);
  
  Serial.print("fsr01: ");
  Serial.print(fsr01);
  Serial.print("\tfsr02: ");
  Serial.print(fsr02);
  Serial.print("\tfsr03: ");
  Serial.print(fsr03);
  Serial.print("\tDistance: ");
  Serial.print(Distance);
  Serial.println(" ");
  delay(50);
}
