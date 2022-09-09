int iXpos = 999999;
int iYpos = 999999;
bool xGameInitialized = false;
#include "helpers.h"
#include "settings.h"
#include "display.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "HTTPClient.h"
#include "motor.h"
#include "brett.h"
#include "test.h"
HTTPClient http;


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

//Variablen
int iRemoved;                                   //Hier werden die GET-Parameter der URL drin abgespeichert => Damit kann nachher weitergearbeitet werden
int iAdded;                                     //Hier werden die GET-Parameter der URL drin abgespeichert => Damit kann nachher weitergearbeitet werden

AsyncWebServer server(80);                      //Webserver auf Port 80 starten

void resetVars(){
  iRemoved = 999;
  iAdded = 999;
}

void setupWebserver(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting_to_WiFi...");

  //Auf Verbindung warten
  while (WiFi.status() != WL_CONNECTED) {       //Warten bis Verbunden => solange blinkende On-Board-LED
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);                        
    Serial.print(".");
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);    
    delay(500);                        
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED) {          //Verbunden + LED Dauer an
    digitalWrite(LED_BUILTIN, HIGH); 

  }

  //Ausgabe von Infos
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Routing (hier Sub-URLs) z.B. http://IP/game oder http://IP/sync für Spielfeld-Sync ??
  
  // on root
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Willkommen zum Muehlespiel von Gruppe 2");
  });

  //on /game
  server.on("/game", HTTP_GET, [](AsyncWebServerRequest *request){
    resetVars();  //Damit geprüft werden kann, ob beide oder nur ein Teil der Variablen gesetzt wurden
 
    int paramsNr = request->params();
    //Serial.println(paramsNr); //Ausgabe Anzahl der Parameter
 
    for(int i=0;i<paramsNr;i++){
 
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "removed"){
          iRemoved = convertStringToInt(p->value()); //ID des entfernten Steins
          Serial.println(iRemoved);
        } else if (p->name() == "added"){
          iAdded = convertStringToInt(p->value()); //ID des gesetzten Steins
          Serial.println(iAdded);
        } else{
          Serial.println("Error");
        }
        //Serial.println("------");
    }

    if (iRemoved != 999 && iAdded == 999){
      request->send(200, "text/plain", "Spielstein mit ID= "+convertIntToString(iRemoved)+" wurde entfernt.");
      showText("Spielstein entfernt","Position "+convertIntToString(iRemoved));
      //Funktion zur Fahrtberechnung
      move(200,"oben");
      switchMagnetState();
      http.begin(sServerAdress);
    }
    if (iRemoved == 999 && iAdded != 999){
      request->send(200, "text/plain", "Spielstein mit ID= "+convertIntToString(iAdded)+" wurde gesetzt.");
      showText("Spielstein gesetzt","Position "+convertIntToString(iAdded));
      //Funktion zur Fahrtberechnung
      move(200,"rechts");
    }
    if (iRemoved != 999 && iAdded != 999){
      request->send(200, "text/plain", "Spielstein wurde von ID= "+convertIntToString(iRemoved)+" nach ID= "+convertIntToString(iAdded)+" bewegt.");
      showText("Spielstein bewegt", "Von Position "+convertIntToString(iRemoved)+" nach Position "+convertIntToString(iAdded));
      //Funktion zur Fahrtberechnung
      //move(200,"oben");
    }

    resetVars();
  });
 
  //Abfangen von unbekannten Anfragen
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Page not Found");
  });

  server.begin();
}

void setup() {
    // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  setupDisplay();
  setupWebserver();
  setupMotor();
  setupGame();
  

}

void loop() {

  //Tests
  test();

  //Spielbrett Initialisierung
  if(xGameInitialized == false){
    setupGame();
  }

}