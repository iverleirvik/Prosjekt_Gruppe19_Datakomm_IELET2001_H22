
#include "OLED.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void OLED::setupDisplay(Adafruit_SSD1306 & display){
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}


void OLED::victoryCelebration(Adafruit_SSD1306 & display){
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Du vant!");
  display.display();
  delay(4000);
  display.clearDisplay();
  display.drawBitmap(0, 0, Happyfacearray, 128, 64, 1);
  display.invertDisplay(true);
  display.display();
}


void OLED::loserNotification(int Placement, Adafruit_SSD1306 & display){
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Du tapte..");
  display.display();
  delay(4000);
  
  display.clearDisplay();
  display.drawBitmap(0, 0, Sadfacearray, 128, 64, 1);
  display.invertDisplay(true);
  display.display();
}