#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "HTTPClient.h"

AsyncWebServer server(80);                      //Webserver auf Port 80 starten
HTTPClient http;



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

  //on control - Manuelle Steuerung
  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request){
    int paramsNr = request->params();
    String direction;
    String sServerAdressTemp;
    bool xFirstParam=true;
    int iXval = 0;
    int iYval = 0;
    String response = "!ok";

    for(int i=0;i<paramsNr;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "x"){
            if(convertStringToInt(p->value()) > 0){
                direction = "rechts";
            }else{
                direction = "links";
            }
            iXval = convertStringToInt(p->value());
            move(abs(convertStringToInt(p->value())),direction);
            if(xFirstParam == true){
                sServerAdressTemp = sServerAdress+"?x1="+p->value();
                xFirstParam = false;
            }else{
                sServerAdressTemp = sServerAdressTemp+"&x1="+p->value();
            }
        }
        if (p->name() == "y"){
            if(convertStringToInt(p->value()) > 0){
                direction = "oben";
            }else{
                direction = "unten";
            }
            iYval = convertStringToInt(p->value());
            move(abs(convertStringToInt(p->value())),direction);
            if(xFirstParam == true){
                sServerAdressTemp = sServerAdress+"?y1="+p->value();
                xFirstParam = false;
            }else{
                sServerAdressTemp = sServerAdressTemp+"&y1="+p->value();
            }
        }
    }
    while(response != "ok"){
        http.begin(sServerAdressTemp.c_str());
        int httpResponseCode = http.GET();
        response = http.getString();
        //delay(500);
    }
    request->send(200, "text/plain", "Verfahre \n X: "+convertIntToString(iXval)+" - Y: "+convertIntToString(iYval));
  });

  //on /game/index.php
  server.on("/game/index.php", HTTP_GET, [](AsyncWebServerRequest *request){
    resetVars();  //Damit geprüft werden kann, ob beide oder nur ein Teil der Variablen gesetzt wurden
 
    int paramsNr = request->params();
    //Serial.println(paramsNr); //Ausgabe Anzahl der Parameter
 
    for(int i=0;i<paramsNr;i++){
 
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "removed"){
          iRemoved = convertStringToInt(p->value()); //ID des entfernten Steins
          //TODO: Spielfeld-Array aktualisieren
          Serial.println(iRemoved);
        } else if (p->name() == "added"){
          iAdded = convertStringToInt(p->value()); //ID des gesetzten Steins
          //TODO: Spielfeld-Array aktualisieren
          Serial.println(iAdded);
        } else{
          Serial.println("Error");
        }
        //Serial.println("------");
    }

    if (iRemoved != 999 && iAdded == 999){
      request->send(200, "text/plain", "ok"); //Dadurch weiß Partner, dass Spielzug erkannt wurde
      showText("Spielstein entfernt","Position "+convertIntToString(iRemoved)+"\n\nDu bist dran...");
      
      player = true; //Damit Spielzüge gesendet werden können
    }
    if (iRemoved == 999 && iAdded != 999){
      request->send(200, "text/plain", "ok"); //Dadurch weiß Partner, dass Spielzug erkannt wurde
      showText("Spielstein gesetzt","Position "+convertIntToString(iAdded)+"\n\nDu bist dran...");

      player = true; //Damit Spielzüge gesendet werden können
    }
    if (iRemoved != 999 && iAdded != 999){;
      request->send(200, "text/plain", "ok"); //Dadurch weiß Partner, dass Spielzug erkannt wurde
      showText("Spielstein bewegt", "Von Position "+convertIntToString(iRemoved)+" nach Position "+convertIntToString(iAdded)+"\n\nDu bist dran...");

      player = true; //Damit Spielzüge gesendet werden können
    }

    resetVars();
  });
 
  //Abfangen von unbekannten Anfragen
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Page not Found");
  });

  server.begin();
}

int sendGamemove(int iAddedToken, int iRemovedToken){

    bool xFirstParam = true;    //Um ersten Parameter mit ? einzuleiten, sonst &-Verkettung
    String sUrlParams="";       //String zum ergänzen der Serveradresse
    //String response = "!ok";    //Um sicherzustellen, dass der Partner den Zug erkannt hat
    String sServerAdressTemp;   //komplette URL
    int httpResponseCode = 999; //Responsecode von HTML-Sendevorgang, wird genutzt um erfolgreiches senden zu überprüfen

    //Wenn Stein gesetzt
    if(iAddedToken != 999){
        if(xFirstParam == true){
            sUrlParams=sUrlParams+"?added="+convertIntToString(iAddedToken);
            xFirstParam = false;
        }else{
            sUrlParams=sUrlParams+"&added="+convertIntToString(iAddedToken);
        }
    }

    //Wenn Stein entfernt
    if(iRemovedToken != 999){
        if(xFirstParam == true){
            sUrlParams=sUrlParams+"?removed="+convertIntToString(iRemovedToken);
            xFirstParam = false;
        }else{
            sUrlParams=sUrlParams+"&removed="+convertIntToString(iRemovedToken);
        }
    }

    //URL zusammenbauen
    sServerAdressTemp = sServerAdress + sUrlParams;

    //5 Sendeversuche, vor Abbruch
    for(int i = 0; i<5 && httpResponseCode != 200;i++){
        http.begin(sServerAdressTemp.c_str());
        httpResponseCode = http.GET();
        //response = http.getString();
    }

    //Rückgabe
    if(httpResponseCode == 200){
        return 1;
    }else{
        return httpResponseCode;
    }
}