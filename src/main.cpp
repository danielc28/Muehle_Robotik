//Variablen
int iRemoved;                                   //Hier werden die GET-Parameter der URL drin abgespeichert => Damit kann nachher weitergearbeitet werden
int iAdded;                                     //Hier werden die GET-Parameter der URL drin abgespeichert => Damit kann nachher weitergearbeitet werden
int iXDimension = 620;
int iYDimension = 620;
bool player = true;                             //Wer ist gerade am Zug? 0 = Nein (Es können keine Spielzüge gesendet werden); 1 = Ja (Es können Spielzüge gesendet werden) - Am Start beide Partner = true
int iXpos = 999999;
int iYpos = 999999;
bool xGameInitialized = false;
bool xReferenced = false;                       // für initializePosition():
bool xAcknowledgedAdd =false;
bool xAcknowledgedRemove =false;
bool xAcknowledgedMove =false;
bool xAcknowledgeX =false;
bool xAcknowledgeY =false;
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
      Serial.begin(115200);
  Serial.print("Hier");
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

    if(xAcknowledgedAdd || xAcknowledgedRemove || xAcknowledgedMove){
      Serial.print("Main" + convertIntToString(iAdded) + convertIntToString(iRemoved));
      place(iAdded,iRemoved);
      xAcknowledgedAdd = false;
      xAcknowledgedRemove = false;
      xAcknowledgedMove = false;
      resetVars();
    }
    if(xAcknowledgeX || xAcknowledgeY){
      calcDirectionAndMove(iRemoved, iAdded);
      xAcknowledgeX = false;
      xAcknowledgeY = false;
      resetVars();
    }

}