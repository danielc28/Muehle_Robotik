

// für handleButton():
int bounceTime = 50;
int holdTime = 500;     // Zeit bis als Button gehalten erkannt
int doubleTime = 1000;  // Zeit für Doppelklick
int lastButtonReading = LOW;
int hold = 0;
int single = 0;
long onTime = 0;
long lastSwitchTime = 0;

void initializePosition(){
    bool xXref = false;
    bool xYref = false;
    calcDirectionAndMove(-4,0); // 4 Schritte links
    delay(1000);
    while (digitalRead(5) == LOW)
    {
        calcDirectionAndMove(0,-5); //5 Schritte runter
    }

    if(digitalRead(5) == HIGH){
        xYref = true;
        calcDirectionAndMove(0,10);
        iYpos = -630;
    }

    while (digitalRead(23) == LOW){
        calcDirectionAndMove(10,0); //10 Schritt rechts)
    }

    if(digitalRead(23) == HIGH){
        xXref = true;
        calcDirectionAndMove(-10,0);
        iXpos = 630;
    }

    if ((xXref == HIGH) && (xYref == HIGH)){

        //Damit auf Parkposition in die Mitte (0/0)
        calcDirectionAndMove(-630,630); //Fahre x- und y-Ebene auf Höhe Parkposition
        xReferenced = true;
    }
}

void setupGame(){

    digitalWrite(14, LOW); //Relais aus
    
    if (xReferenced == false){
        initializePosition();
    }

    

    //Fertig mit Initialisierung
    xGameInitialized = true;
}

int compareState(bool test){
    for (int i = 1; i < sizeof(aktuell)/sizeof(int); i++){ 
        if ((aktuell[i] ^ spielbrett[i][0]) == 1){
            if(aktuell[i] == 1 && test == true){  
                return i;
            }else if (test == false){
                return i;
            }
        }
    }
    return 999;
}

void readBoard(){
    int k = 0;
    for (int i = 0 ; i < (sizeof(output_CS)/sizeof(int)) ; i++ ){
        digitalWrite(output_CS[i], HIGH); 
        for (int j = 0; j < (sizeof(inputs_CS)/sizeof(int)); j++){
            aktuell[k] = convertBoolToInt(digitalRead(inputs_CS[j]));
            k++;
        }
        digitalWrite(output_CS[i], LOW); 
    }
}

void calcGamemove() {
    if(player == true){
        resetVars();  //Hilfsvariablen initialisieren
        readBoard(); //Brett auslesen

        iAdded = compareState(1); //Wo wurde ein Stein hinzugefügt
        iRemoved = compareState(0); //Wo wurde ein Stein hinzugefügt

        showText("Hinweis","Sende Bewegung an Partner...");
        int rcSendGamemove = sendGamemove(iAdded,iRemoved);
        if(rcSendGamemove != 1){
            //Konnte nicht gesendet werden
            showText("Fehler","Bewegung beim Senden. Bitte erneut Button drücken\nCode: " + convertIntToString(rcSendGamemove));
        }else{
            spielbrett[iAdded][0] = 1;
            spielbrett[iRemoved][0] = 0;
            showText("Hinweis","Bewegung gesendet\n\nWarten auf Gegenspieler...");

            player = false; //Versenden von Spielzügen wird gesperrt
        }

        resetVars(); //Rücksetzen der Hilfsvariablen
    }    
}

void onButtonRelease(){
    if ((millis() - lastSwitchTime)>= doubleTime){
        single = 1;
        lastSwitchTime = millis();
        return;
    }

    if((millis() - lastSwitchTime) < doubleTime){
        //Funktion für Doppelklick
        showText("Hinweis", "Doppelklick");
        //TODO: Was soll bei Doppelklick passieren?
        single = 0;
        lastSwitchTime = millis();
    }
}

void buttonHandling(){
    int buttonReading = digitalRead(15);

    //Gedrückt
    if(buttonReading == HIGH && lastButtonReading == LOW){
        onTime = millis();
    }

    //Gehalten
    if(buttonReading == HIGH && lastButtonReading == HIGH){
        if((millis() - onTime) > holdTime){
            hold = 1;
        }
    }

    //Loslassen
    if(buttonReading == LOW && lastButtonReading == HIGH){
        if(((millis()- onTime) > bounceTime) && hold != 1){
            //Auswertung einfacher oder doppelter Klick
            onButtonRelease();
        }
        if(hold == 1){
            //Funktion für gehalten
            showText("Hinweis", "Spiel wird neu initialisiert");
            xGameInitialized = false;
            xReferenced = false;
            hold = 0;
        }
    }
    lastButtonReading = buttonReading;

    if(single == 1 && (millis() - lastSwitchTime) > doubleTime){
        //Funktion für einfachen Druck
        calcGamemove();
        single = 0;
    }
}

