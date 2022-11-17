#include "OLED.h" // Inkluderer til h-fila.


void OLED::setupDisplay(Adafruit_SSD1306 & display){  //Tar inn displayet ved pass-by-reference.
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Sjekker om displayet fungerer som det skal.
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Vil prøve å ta så mange loops som mulig. samme som while(true);
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
  display.drawBitmap(0, 0, Happyfacearray, 128, 64, 1); // Bruker variabelen happyfacearray til å faktisk noe display kan vise på skjermen.
  display.invertDisplay(true);  // Jeg velger å beskrive denne fordi denne er ikke beskrevet andre steder i prosjektkoden. Denne inverterer skjermen. Det vil si
  display.display();            // at de lyse pikslene vil bli svarte, og de svare vil bli lyse.
  delay(2000);
  display.invertDisplay(false); // man må huske å reversere det, ellers vil det forbli sånn.
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
  delay(2000);
  display.invertDisplay(false);
  display.display();
}