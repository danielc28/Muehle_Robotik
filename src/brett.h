// für initializePosition():
bool xReferenced = false;

// für switchMagnetState():
bool xMagnetEnabled = false;

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
    move(4,"links"); // 2 Schritte links
    delay(1000);
    while (digitalRead(5) == LOW)
    {
        move(5,"unten"); //5 Schritte runter
    }

    if(digitalRead(5) == HIGH){
        xYref = true;
        move(10,"hoch");
        iYpos = -630;
    }

    while (digitalRead(23) == LOW){
        move(10,"rechts"); //1 Schritt rechts)
    }

    if(digitalRead(23) == HIGH){
        xXref = true;
        move(10,"links");
        iXpos = 630;
    }

    if ((xXref == HIGH) && (xYref == HIGH)){

        //Damit auf Parkposition in die Mitte (0/0)
        move(630,"links"); //Fahre x-Ebene auf Höhe Parkposition
        move(630,"oben"); //Fahre y-Ebene auf Höhe Parkposition
        xReferenced = true;
    }
}

void switchMagnetState(){
    if(xMagnetEnabled){
        digitalWrite(14, LOW);
        xMagnetEnabled = false;
    }else{
        digitalWrite(14,HIGH);
        xMagnetEnabled = true;
    }
}

void setupGame(){
    if (xReferenced == false){
        initializePosition();
    }
    pinMode(14,OUTPUT); // Relais für Magnet

    digitalWrite(14, LOW); //Relais aus

    //Fertig mit Initialisierung
    xGameInitialized = true;
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
            showText("Hinweis", "gehalten");
            hold = 0;
        }
    }
    lastButtonReading = buttonReading;

    if(single == 1 && (millis() - lastSwitchTime) > doubleTime){
        //Funktion für einfachen Druck
        showText("Hinweis","Einfacher Klick");
        single = 0;
    }
}