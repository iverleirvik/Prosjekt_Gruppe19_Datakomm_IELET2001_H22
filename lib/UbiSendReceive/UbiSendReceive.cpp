#include "UbiSendReceive.h" // Henter h-fila med deklarasjoner og initialiseringer.

void UbiSendReceive::UbiSendReceive_CALLBACK(char *topic, byte *payload, unsigned int length, int steps) {
  char charWord[20];                              // Denne funksjonen oversetter til brukbare datatyper. 
  for (int i = 0; i < length; i++)  {             // Deretter så låser den steg og legger evt. skritt fra forskjellige skrittellere i en vektor.
    charWord[i] = (char)payload[i];
  }

  ///*
  if(firstMessagesIgnore <= 3) { // Ubiodts fungerer ved at når man abonnerer vil de siste meldingene som ble sendt fra ubidots
    firstMessagesIgnore++;       // bli sendt på nytt. Disse vil ikke vi registrere så vi ignorer dem.
    return;
  }
  //*/

  if(strstr(topic, "/v2.0/devices/esp32/1/lv")) { // OBS: Pass på og endre topic-streng til ubidotsbrukeren!
    skrittFelles.push_back(atoi(charWord));   // Legger verdi til i vectoren.
  }

  if(strstr(topic, "/v2.0/devices/esp32/2/lv")) { // sjekker om det er ny dag.
    newDay = true;  // Setter tilstandsmaskinvariabelen til sant.
    lockedSteps = steps;  // Låser stegene slik at det ikke vil komme inn noen nye.
    Serial.println("Callback 2");
  }
  Serial.println("generell callback");
}

void UbiSendReceive::UbiSendReceive_INIT(const char *VARIABLE_DATA, const char *VARIABLE_NEWDAY ) { // Ikke i bruk, men kan brukes til abonnere på variabler.
  _ubidots.subscribeLastValue(_deviceLabel, VARIABLE_DATA);
  _ubidots.subscribeLastValue(_deviceLabel, VARIABLE_NEWDAY);
}


void UbiSendReceive::UbiSendReceive_loop(Adafruit_SSD1306 &display, int &steps) { // Funksjonen som kjøres hver runde i loopen.
  if (newDay == true) { // Sjekker om det er en ny dag.
    if (millis() > timerEspSendMessage && notPubYet == false) { // Hvis det har gått en viss tid som burde være forskjellig for hver skritteller og at enheten ikke har publisert enda.
      _ubidots.add(_variableLabel, lockedSteps);
      _ubidots.publish(_deviceLabel);             // Går videre med å publisere data på variabel slik at andre skrittellere kan hente skritt.
      notPubYet = true;                           // Gjør det umulig å komme inn igjen i denne funksjonen mens opptellingen foregår.
      Serial.println("Inne i pub");
      startTime = millis(); // Brukes i neste if-setning for å matche opp tid mellom dem.
    }

    if(millis() > startTime + timerEspStopListening) {  // Ved en viss tid vil skrittellerne slutte å lytte etter nye meldinger. De vil da gå videre med 
      newDay = false;                                   // å vise resultatene.
      notPubYet = false;
      Serial.println("ferdig nå");                      // Går tilbake til square 1 i tilstandsmaskinene.
// -----------------------------------------------------------------------------
        
        // LEGG INN ALVAR OG TORSTEIN FUNKSJON
          {                                                                 // Kode som sorterer skritt fra de forskjellige skrittellerene og sjekker om denne skrittelleren
            sort(skrittFelles.begin(), skrittFelles.end(), greater<int>()); // har vunnet. Avhengig av resultatet vil det bli vist forskjellige animasjoner og tekst
            vinner = skrittFelles[0];                                       // på skjermen.
            for(int i = 0; i < skrittFelles.size(); i++) {
              if(skrittFelles[i] > lockedSteps)  {                          //Vektoren blir sortert til stigende rekkefølge.
                Placement += 1;                                            // Er nivået høyere enn ditt eget vil variabelen øe med en.
              }
            }
            if(Placement == 1){           // Har det ikke skjedd noe med variabelene og den fortsatt er 1, har ingen hatt høyere skritt. Man slår fast at man har vunnet.
              oled.victoryCelebration(display); // Animasjon på skjerm.
            }
            else {
              oled.loserNotification(Placement, display); // Animasjon på skjerm.
            }
            Placement = 1;  // setter variabelen tilbake til den var før man startet på koden mellom disse klammebrakettene.
          }
// -----------------------------------------------------------------------------
      skrittFelles.clear(); // Renser listen og gjør den klar for neste runde. Samme gjelder variablene under.
      lockedSteps = 0;
      steps = 0;
      }
    }
}
