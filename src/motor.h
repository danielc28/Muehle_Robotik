/*
Cheatcheat:
M1 uhrzeigersinn + M2 uhrzeigersinn = X-Richtung Rechts
M1 gegen uhrzeigersinn + M2 gegen uhrzeigersinn = X-Richtung Links
M1 uhrzeigersinn + M2 gegen uhrzeigersinn = Y-Richtung zu Spieler
M1 gegen uhrzeigersinn + M2 uhrzeigersinn = Y-Richtung weg von Spieler
----------------------------------------------------------------------
HIGH = im Uhrzeigersinn
LOW = gegen Uhrzeigersinn
*/

int iStepCounter;
int iStepperspeed = 2000; //in Mikrosekunden für PWM Je Kleiner die Zahl, desto schneller
//bool xXlock = false;
//bool xYlock = false;




void setupEndschalter(){
    pinMode(5,INPUT_PULLDOWN); // Endschalter Y
    pinMode(23, INPUT_PULLDOWN); // Endschalter X
}

void setupMotor(){
    // Set target motor RPM to 1RPM and microstepping to 1 (full step mode)
    //stepper.begin(1, 1);
    pinMode(3,OUTPUT); // M1 - Step
    pinMode(17,OUTPUT); //M1 - Dir
    pinMode(1,OUTPUT); //M2 - Step
    pinMode(16,OUTPUT); //M2 - Dir
    setupEndschalter();
}

/*
void move(int steps, String direction){

    if (direction == "rechts"){
        digitalWrite(17,LOW); // M1 gg Uhrzeigersinn
        digitalWrite(16,LOW); // M2 gg Uhrzeigersinn
        iXpos = iXpos + steps;
    }else if(direction == "links"){
        digitalWrite(17,HIGH); // M1 im Uhrzeigersinn
        digitalWrite(16,HIGH); // M2 im Uhrzeigersinn
        iXpos = iXpos - steps;
    }else if(direction == "oben"){
        digitalWrite(17,HIGH); // M1 im Uhrzeigersinn
        digitalWrite(16,LOW); // M2 gg Uhrzeigersinn
        iYpos = iYpos + steps;
    }else if(direction == "unten"){
        digitalWrite(17,LOW); // M1 gg Uhrzeigersinn
        digitalWrite(16,HIGH); // M2 im Uhrzeigersinn
        iYpos = iYpos - steps;
    }else{
        //Error
    }
    iStepCounter = 0;

    for(iStepCounter = 0; iStepCounter < steps && xXlock == false && xYlock == false; iStepCounter++) {

        if(digitalRead(5) == HIGH && xYlock == false){
            xYlock = true;
            break;
        }
        if(digitalRead(23) == HIGH && xXlock == false){
            xXlock = true;
            break;
        }
        if(xXlock == false && xYlock == false){
            digitalWrite(3,HIGH);
            digitalWrite(1,HIGH);
            delayMicroseconds(iStepperspeed);
            digitalWrite(3,LOW);
            digitalWrite(1,LOW);
            delayMicroseconds(iStepperspeed);
        }
    }

    if(xXlock == true){
        //Einstellung für Links fahren
        digitalWrite(17,HIGH); // M1 gegen Uhrzeigersinn
        digitalWrite(16,HIGH); // M2 gegen Uhrzeigersinn
        showText("","XLock");
    }

    if(xYlock == true){
        //Einstellung für Hoch fahren
        digitalWrite(17,HIGH); // M1 gegen Uhrzeigersinn
        digitalWrite(16,LOW); // M2 gegen Uhrzeigersinn
        showText("","YLock");
    }

    if(xYlock == true || xXlock == true){
        for(int j = 0; j<10; j++){
            digitalWrite(3,HIGH);
            digitalWrite(1,HIGH);
            delayMicroseconds(iStepperspeed);
            digitalWrite(3,HIGH);
            digitalWrite(1,LOW);
            delayMicroseconds(iStepperspeed);
        }
        xYlock = false;
        xXlock = false;
    }

    iStepCounter = 0;
    showText("Aktuelle Position","X: "+convertIntToString(iXpos)+" - Y: "+convertIntToString(iYpos));
}
*/

void move2(int steps){
    iStepCounter = 0;
    for(iStepCounter=0; iStepCounter < abs(steps); iStepCounter++){
        digitalWrite(3,HIGH);
        digitalWrite(1,HIGH);
        delayMicroseconds(iStepperspeed);
        digitalWrite(3,LOW);
        digitalWrite(1,LOW);
        delayMicroseconds(iStepperspeed);
    }
}

bool calcDirectionAndMove(int xSteps, int ySteps){
    if((iXpos + xSteps < iXDimension && iXpos + xSteps > (-1)*iXDimension) || xReferenced == false){
        //Richtung der Motoren festlegen
        if (xSteps > 0){
            //showText("Richtung","rechts");
            digitalWrite(17,LOW); // M1 gg Uhrzeigersinn
            digitalWrite(16,LOW); // M2 gg Uhrzeigersinn
            iXpos = iXpos + xSteps;
        }else if(xSteps < 0){
            //showText("Richtung","links");
            digitalWrite(17,HIGH); // M1 im Uhrzeigersinn
            digitalWrite(16,HIGH); // M2 im Uhrzeigersinn
            iXpos = iXpos + xSteps;
        }else{
            //Eroor
        }
        //Move Bewegung X-Richtung
        move2(xSteps);
    }else{
        //Fehler anzeigen
        showText("Fehler","Neue X-Position passt nicht: "+convertIntToString(iXpos) +"+ " +convertIntToString(xSteps));
        return 0;
    }

    if((iYpos + ySteps < iYDimension && iYpos + ySteps > (-1)*iYDimension) || xReferenced == false){
        if(ySteps > 0){
            //showText("Richtung","hoch");
            digitalWrite(17,HIGH); // M1 im Uhrzeigersinn
            digitalWrite(16,LOW); // M2 gg Uhrzeigersinn
            iYpos = iYpos + ySteps;
        }else if(ySteps < 0){
            //showText("Richtung","runter");
            digitalWrite(17,LOW); // M1 gg Uhrzeigersinn
            digitalWrite(16,HIGH); // M2 im Uhrzeigersinn
            iYpos = iYpos + ySteps;
        }else{
            //Error
        }
        //Move Bewegung Y-Richtung
        move2(ySteps);
    }else{
        //Fehler anzeigen
        showText("Fehler","Neue Y-Position passt nicht: "+convertIntToString(iYpos) +"+ " +convertIntToString(ySteps));
        return 0;
    }

    //Ausgabe der neuen Position auf Display
    showText("Aktuelle Position","X: "+convertIntToString(iXpos)+" - Y: "+convertIntToString(iYpos));
    return 1;
}



void place(int iAdded, int iRemoved){
    int iXmove, iYmove;
    bool moveError;

    if (iRemoved != 999 && iAdded == 999) { //entfernen: Stein zu Parkposition fahren
        Serial.println("");
        Serial.print("Entfernt");
        //zu Stein fahren, der entfernt wird
        moveError = calcDirectionAndMove(spielbrett[iRemoved][1]+spielbrett[iRemoved][3], spielbrett[iRemoved][2]+spielbrett[iRemoved][4]);

        //Magnet einschalten
        switchMagnetState();
        
        //Offset verschieben
        moveError = calcDirectionAndMove(spielbrett[iRemoved][3], spielbrett[iRemoved][4]);

        //Weg berechnen
        iXmove = (spielbrett[iRemoved][1]-iXpos);
        iYmove = (spielbrett[iRemoved][2]-iYpos);

        //mit Stein verfahren
        moveError = calcDirectionAndMove(iXmove, iYmove);
        
        //negatives Offset verschieben auf Parkposition
        moveError = calcDirectionAndMove((-1)*spielbrett[0][3], (-1)*spielbrett[0][4]);
        
        //Magnet ausschalten
        switchMagnetState();
    }else if (iRemoved == 999 && iAdded != 999) { //Hinzufügen: Parkposition nach Position fahren
        Serial.println("");
        Serial.print("Gesetzt");
        //zu  Parkposition fahren
        if(iXpos != 0 && iYpos != 0){
            Serial.println("");
            Serial.print("zu Parkposition");
            moveError = calcDirectionAndMove(-iXpos, -iYpos);
        }
    
        //Magnet einschalten
        switchMagnetState();
        
        //Versatz Parkpositon fahren
        Serial.println("");
        Serial.print("Versetzen");
        moveError = calcDirectionAndMove(spielbrett[0][3], spielbrett[0][4]);

        //Weg berechnen und verfahren (ohne Offset)
        iXmove = (spielbrett[iAdded][1]-iXpos);
        iYmove = (spielbrett[iAdded][2]-iYpos);
        Serial.println("");
        Serial.print("Verfahren");
        moveError = calcDirectionAndMove(iXmove, iYmove);

        //Offset zurückfahren
        Serial.println("");
        Serial.print("Zurückversetzen");
        moveError = calcDirectionAndMove((-1)*spielbrett[iAdded][3], (-1)*spielbrett[iAdded][4]);
        
        //Magnet ausschalten
        switchMagnetState();
    }else if (iRemoved == 999 && iAdded == 999){ //Spielstein von A nach B fahren
        Serial.println("");
        Serial.print("Bewegt");
        //Unter Removed-Stein fahren
        moveError = calcDirectionAndMove(spielbrett[iRemoved][1]+spielbrett[iRemoved][3], spielbrett[iRemoved][2]+spielbrett[iRemoved][4]);

        //Magnet einschalten
        switchMagnetState();
        
        //Offset verfahren
        moveError = calcDirectionAndMove(spielbrett[iRemoved][3], spielbrett[iRemoved][4]);
        
        //Weg berechnen und verfahren
        iXmove = (spielbrett[iAdded][1]-spielbrett[iRemoved][1]);
        iYmove = (spielbrett[iAdded][2]-spielbrett[iRemoved][2]);
        moveError = calcDirectionAndMove(iXmove, iYmove);

        //Versatz rückwärtsfahren
        moveError = calcDirectionAndMove((-1)*spielbrett[iAdded][3], (-1)*spielbrett[iAdded][4]);

        //Magnet ausschalten
        switchMagnetState();
    }else{
        //Error
    }
}
