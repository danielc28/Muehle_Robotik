//Variablen
int iRemoved;                                   //Hier werden die GET-Parameter der URL drin abgespeichert => Damit kann nachher weitergearbeitet werden
int iAdded;                                     //Hier werden die GET-Parameter der URL drin abgespeichert => Damit kann nachher weitergearbeitet werden
int iXpos = 999999;
int iYpos = 999999;
bool xGameInitialized = false;
#include "helpers.h"
#include "settings.h"
#include "display.h"
#include "motor.h"
#include "web.h"
#include "brett.h"
#include "test.h"




/*
----------------- 2022-07-20 ----------------- 
V1.0
Funktionen: 
- Verbindung mit WLAN-Netz
- Webserver bereitstellen
- Auswertung von Sub-URLs
- Auswertung von GET-Parametern
- Funktionen zur Konvertierung von GET-Parametern, damit sie auch nutzbar sind


ToDo:
- Spielfeld-Sync? (komplette Array-Übergabe)
- Input, wann Spielstein auf Finalposition steht oder Timer, wenn Veränderung erkannt wurde?
- ESP auch als Client nutzen => Bestätigung von Spielzug zurück senden
*/

void setup() {
  // put your setup code here, to run once:
  setupPins();
  setupDisplay();
  setupWebserver();
  setupMotor();
  setupGame();
}

void loop() {

  //Umgang mit Button
  buttonHandling();

  //Tests
  test();

  //Spielbrett Initialisierung
  if(xGameInitialized == false){
    setupGame();
  }

}