#include <Wire.h>
#include "Adafruit_DRV2605.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Fonts/FreeMonoBold9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON1 2
#define BUTTON2 3
#define PAD 1

#include <ArduinoJson.h>
const int capacity = 123 * JSON_OBJECT_SIZE(1) + 123 * JSON_OBJECT_SIZE(2);
StaticJsonDocument<capacity> doc;

Adafruit_DRV2605 drv;
uint8_t effect = 1;

void setup() {
  Serial.begin(9600);

  //init pin
  attachInterrupt(BUTTON1, plusOne, RISING);
  attachInterrupt(BUTTON2, minusOne, RISING);
  pinMode(PAD, INPUT);

  //init DRV2605L
  Serial.println("DRV test");
  drv.begin();

  //Using LRA
  //  drv.selectLibrary(6);
  //  drv.useLRA();
  //If uning ERM, comment 2 lines above, and uncommand the lowwer lines.
  drv.selectLibrary(2);
  drv.useERM();

  drv.setMode(DRV2605_MODE_INTTRIG);

  //Load pattern text
  char json[] = "{\"1\":{\"name\": \"Strong Click\", \"strength\": \"100%\"},\"2\":{\"name\": \"Strong Click\", \"strength\": \"60%\"},\"3\":{\"name\": \"Strong Click\", \"strength\": \"30%\"},\"4\":{\"name\": \"Sharp Click\", \"strength\": \"100%\"},\"5\":{\"name\": \"Sharp Click\", \"strength\": \"60%\"},\"6\":{\"name\": \"Sharp Click\", \"strength\": \"30%\"},\"7\":{\"name\": \"Soft Bump\", \"strength\": \"100%\"},\"8\":{\"name\": \"Soft Bump\", \"strength\": \"60%\"},\"9\":{\"name\": \"Soft Bump\", \"strength\": \"30%\"},\"10\":{\"name\": \"Double Click\", \"strength\": \"100%\"},\"11\":{\"name\": \"Double Click\", \"strength\": \"60%\"},\"12\":{\"name\": \"Triple Click\", \"strength\": \"100%\"},\"13\":{\"name\": \"Soft Fuzz\", \"strength\": \"60%\"},\"14\":{\"name\": \"Strong Buzz\", \"strength\": \"100%\"},\"15\":{\"name\": \"750 ms Alert\", \"strength\": \"100%\"},\"16\":{\"name\": \"1000 ms Alert\", \"strength\": \"100%\"},\"17\":{\"name\": \"Strong Click 1\", \"strength\": \"100%\"},\"18\":{\"name\": \"Strong Click 2\", \"strength\": \"80%\"},\"19\":{\"name\": \"Strong Click 3\", \"strength\": \"60%\"},\"20\":{\"name\": \"Strong Click 4\", \"strength\": \"30%\"},\"21\":{\"name\": \"Medium Click 1\", \"strength\": \"100%\"},\"22\":{\"name\": \"Medium Click 2\", \"strength\": \"80%\"},\"23\":{\"name\": \"Medium Click 3\", \"strength\": \"60%\"},\"24\":{\"name\": \"Sharp Tick 1\", \"strength\": \"100%\"},\"25\":{\"name\": \"Sharp Tick 2\", \"strength\": \"80%\"},\"26\":{\"name\": \"Sharp Tick 3\", \"strength\": \"60%\"},\"27\":{\"name\": \"Short Double Click Strong 1\", \"strength\": \"100%\"},\"28\":{\"name\": \"Short Double Click Strong 2\", \"strength\": \"80%\"},\"29\":{\"name\": \"Short Double Click Strong 3\", \"strength\": \"60%\"},\"30\":{\"name\": \"Short Double Click Strong 4\", \"strength\": \"30%\"},\"31\":{\"name\": \"Short Double Click Medium 1\", \"strength\": \"100%\"},\"32\":{\"name\": \"Short Double Click Medium 2\", \"strength\": \"80%\"},\"33\":{\"name\": \"Short Double Click Medium 3\", \"strength\": \"60%\"},\"34\":{\"name\": \"Short Double Sharp Tick 1\", \"strength\": \"100%\"},\"35\":{\"name\": \"Short Double Sharp Tick 2\", \"strength\": \"80%\"},\"36\":{\"name\": \"Short Double Sharp Tick 3\", \"strength\": \"60%\"},\"37\":{\"name\": \"Long Double Sharp Click Strong 1\", \"strength\": \"100%\"},\"38\":{\"name\": \"Long Double Sharp Click Strong 2\", \"strength\": \"80%\"},\"39\":{\"name\": \"Long Double Sharp Click Strong 3\", \"strength\": \"60%\"},\"40\":{\"name\": \"Long Double Sharp Click Strong 4\", \"strength\": \"30%\"},\"41\":{\"name\": \"Long Double Sharp Click Medium 1\", \"strength\": \"100%\"},\"42\":{\"name\": \"Long Double Sharp Click Medium 2\", \"strength\": \"80%\"},\"43\":{\"name\": \"Long Double Sharp Click Medium 3\", \"strength\": \"60%\"},\"44\":{\"name\": \"Long Double Sharp Tick 1\", \"strength\": \"100%\"},\"45\":{\"name\": \"Long Double Sharp Tick 2\", \"strength\": \"80%\"},\"46\":{\"name\": \"Long Double Sharp Tick 3\", \"strength\": \"60%\"},\"47\":{\"name\": \"Buzz 1\", \"strength\": \"100%\"},\"48\":{\"name\": \"Buzz 2\", \"strength\": \"80%\"},\"49\":{\"name\": \"Buzz 3\", \"strength\": \"60%\"},\"50\":{\"name\": \"Buzz 4\", \"strength\": \"40%\"},\"51\":{\"name\": \"Buzz 5\", \"strength\": \"20%\"},\"52\":{\"name\": \"Pulsing Strong 1\", \"strength\": \"100%\"},\"53\":{\"name\": \"Pulsing Strong 2\", \"strength\": \"60%\"},\"54\":{\"name\": \"Pulsing Medium 1\", \"strength\": \"100%\"},\"55\":{\"name\": \"Pulsing Medium 2\", \"strength\": \"60%\"},\"56\":{\"name\": \"Pulsing Sharp 1\", \"strength\": \"100%\"},\"57\":{\"name\": \"Pulsing Sharp 2\", \"strength\": \"60%\"},\"58\":{\"name\": \"Transition Click 1\", \"strength\": \"100%\"},\"59\":{\"name\": \"Transition Click 2\", \"strength\": \"80%\"},\"60\":{\"name\": \"Transition Click 3\", \"strength\": \"60%\"},\"61\":{\"name\": \"Transition Click 4\", \"strength\": \"40%\"},\"62\":{\"name\": \"Transition Click 5\", \"strength\": \"20%\"},\"63\":{\"name\": \"Transition Click 6\", \"strength\": \"10%\"},\"64\":{\"name\": \"Transition Hum 1\", \"strength\": \"100%\"},\"65\":{\"name\": \"Transition Hum 2\", \"strength\": \"80%\"},\"66\":{\"name\": \"Transition Hum 3\", \"strength\": \"60%\"},\"67\":{\"name\": \"Transition Hum 4\", \"strength\": \"40%\"},\"68\":{\"name\": \"Transition Hum 5\", \"strength\": \"20%\"},\"69\":{\"name\": \"Transition Hum 6\", \"strength\": \"10%\"},\"70\":{\"name\": \"Transition Ramp Down Long Smooth 1\", \"strength\": \"100 to 0%\"},\"71\":{\"name\": \"Transition Ramp Down Long Smooth 2\", \"strength\": \"100 to 0%\"},\"72\":{\"name\": \"Transition Ramp Down Medium Smooth 1\", \"strength\": \"100 to 0%\"},\"73\":{\"name\": \"Transition Ramp Down Medium Smooth 2\", \"strength\": \"100 to 0%\"},\"74\":{\"name\": \"Transition Ramp Down Short Smooth 1\", \"strength\": \"100 to 0%\"},\"75\":{\"name\": \"Transition Ramp Down Short Smooth 2\", \"strength\": \"100 to 0%\"},\"76\":{\"name\": \"Transition Ramp Down Long Sharp 1\", \"strength\": \"100 to 0%\"},\"77\":{\"name\": \"Transition Ramp Down Long Sharp 2\", \"strength\": \"100 to 0%\"},\"78\":{\"name\": \"Transition Ramp Down Medium Sharp 1\", \"strength\": \"100 to 0%\"},\"79\":{\"name\": \"Transition Ramp Down Medium Sharp 2\", \"strength\": \"100 to 0%\"},\"80\":{\"name\": \"Transition Ramp Down Short Sharp 1\", \"strength\": \"100 to 0%\"},\"81\":{\"name\": \"Transition Ramp Down Short Sharp 2\", \"strength\": \"100 to 0%\"},\"82\":{\"name\": \"Transition Ramp Up Long Smooth 1\", \"strength\": \"0 to 100%\"},\"83\":{\"name\": \"Transition Ramp Up Long Smooth 2\", \"strength\": \"0 to 100%\"},\"84\":{\"name\": \"Transition Ramp Up Medium Smooth 1\", \"strength\": \"0 to 100%\"},\"85\":{\"name\": \"Transition Ramp Up Medium Smooth 2\", \"strength\": \"0 to 100%\"},\"86\":{\"name\": \"Transition Ramp Up Short Smooth 1\", \"strength\": \"0 to 100%\"},\"87\":{\"name\": \"Transition Ramp Up Short Smooth 2\", \"strength\": \"0 to 100%\"},\"88\":{\"name\": \"Transition Ramp Up Long Sharp 1\", \"strength\": \"0 to 100%\"},\"89\":{\"name\": \"Transition Ramp Up Long Sharp 2\", \"strength\": \"0 to 100%\"},\"90\":{\"name\": \"Transition Ramp Up Medium Sharp 1\", \"strength\": \"0 to 100%\"},\"91\":{\"name\": \"Transition Ramp Up Medium Sharp 2\", \"strength\": \"0 to 100%\"},\"92\":{\"name\": \"Transition Ramp Up Short Sharp 1\", \"strength\": \"0 to 100%\"},\"93\":{\"name\": \"Transition Ramp Up Short Sharp 2\", \"strength\": \"0 to 100%\"},\"94\":{\"name\": \"Transition Ramp Down Long Smooth 1\", \"strength\": \"50 to 0%\"},\"95\":{\"name\": \"Transition Ramp Down Long Smooth 2\", \"strength\": \"50 to 0%\"},\"96\":{\"name\": \"Transition Ramp Down Medium Smooth 1\", \"strength\": \"50 to 0%\"},\"97\":{\"name\": \"Transition Ramp Down Medium Smooth 2\", \"strength\": \"50 to 0%\"},\"98\":{\"name\": \"Transition Ramp Down Short Smooth 1\", \"strength\": \"50 to 0%\"},\"99\":{\"name\": \"Transition Ramp Down Short Smooth 2\", \"strength\": \"50 to 0%\"},\"100\":{\"name\": \"Transition Ramp Down Long Sharp 1\", \"strength\": \"50 to 0%\"},\"101\":{\"name\": \"Transition Ramp Down Long Sharp 2\", \"strength\": \"50 to 0%\"},\"102\":{\"name\": \"Transition Ramp Down Medium Sharp 1\", \"strength\": \"50 to 0%\"},\"103\":{\"name\": \"Transition Ramp Down Medium Sharp 2\", \"strength\": \"50 to 0%\"},\"104\":{\"name\": \"Transition Ramp Down Short Sharp 1\", \"strength\": \"50 to 0%\"},\"105\":{\"name\": \"Transition Ramp Down Short Sharp 2\", \"strength\": \"50 to 0%\"},\"106\":{\"name\": \"Transition Ramp Up Long Smooth 1\", \"strength\": \"0 to 50%\"},\"107\":{\"name\": \"Transition Ramp Up Long Smooth 2\", \"strength\": \"0 to 50%\"},\"108\":{\"name\": \"Transition Ramp Up Medium Smooth 1\", \"strength\": \"0 to 50%\"},\"109\":{\"name\": \"Transition Ramp Up Medium Smooth 2\", \"strength\": \"0 to 50%\"},\"110\":{\"name\": \"Transition Ramp Up Short Smooth 1\", \"strength\": \"0 to 50%\"},\"111\":{\"name\": \"Transition Ramp Up Short Smooth 2\", \"strength\": \"0 to 50%\"},\"112\":{\"name\": \"Transition Ramp Up Long Sharp 1\", \"strength\": \"0 to 50%\"},\"113\":{\"name\": \"Transition Ramp Up Long Sharp 2\", \"strength\": \"0 to 50%\"},\"114\":{\"name\": \"Transition Ramp Up Medium Sharp 1\", \"strength\": \"0 to 50%\"},\"115\":{\"name\": \"Transition Ramp Up Medium Sharp 2\", \"strength\": \"0 to 50%\"},\"116\":{\"name\": \"Transition Ramp Up Short Sharp 1\", \"strength\": \"0 to 50%\"},\"117\":{\"name\": \"Transition Ramp Up Short Sharp 2\", \"strength\": \"0 to 50%\"},\"118\":{\"name\": \"Long buzz for programmatic stopping\", \"strength\": \"100%\"},\"119\":{\"name\": \"Smooth Hum 1 (No kick or brake pulse)\", \"strength\": \"50%\"},\"120\":{\"name\": \"Smooth Hum 2 (No kick or brake pulse)\", \"strength\": \"40%\"},\"121\":{\"name\": \"Smooth Hum 3 (No kick or brake pulse)\", \"strength\": \"30%\"},\"122\":{\"name\": \"Smooth Hum 4 (No kick or brake pulse)\", \"strength\": \"20%\"},\"123\":{\"name\": \"Smooth Hum 5 (No kick or brake pulse)\", \"strength\": \"10%\"}}";
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }


  //init display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  //Display the Name of the
  display.clearDisplay();
  //Parameter of the test
  //display.setFont(&FreeMonoBold9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(3, 5);
  display.print("DRV2605L\n TEST MODULE");
  display.display();
  delay(2000); // Pause for 2 seconds

  refreashDisplay(effect);
}



void loop() {
  Serial.begin(9600);
  //  Serial.print("BUTTON 01: ");
  //  Serial.print(digitalRead(2));
  //  Serial.print("\tBUTTON 02: ");
  //  Serial.print(digitalRead(3));
  //  Serial.print("\tPAD 01: ");
  //  Serial.println(analogRead(1));

  if (analogRead(1) > 500) {
    //Trigger motor
    drv.setWaveform(0, effect);  // play effect
    drv.setWaveform(1, 0);       // end waveform
    // play the effect!
    drv.go();
    delay(1000);
  } else {
    drv.stop();
  }
  delay(2);

}


void refreashDisplay(int Num) {
  String patternNumber = String(Num);
  String patternName = doc[patternNumber]["name"];
  String patternStrength = doc[patternNumber]["strength"];

  //Display info on the screen
  display.clearDisplay();
  //Parameter of the test
  display.cp437(true);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println(patternNumber);
  display.println(patternName);
  display.println(patternStrength);
  display.display();
  delay(1); // Pause for 2 seconds
}



void plusOne() {
  //Press the button, go to the next pattern.
  effect += 1;
  if (effect > 123) {
    effect = 1;
  }
  refreashDisplay(effect);
}

void minusOne() {
  //Press the button, go to the last pattern.
  effect -= 1;
  if (effect <= 0) {
    effect = 123;
  }
  refreashDisplay(effect);
}
