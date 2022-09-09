bool xReferenced = false;
bool xMagnetEnabled = false;

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

    digitalWrite(14, LOW);

    //Fertig mit Initialisierung
    xGameInitialized = true;
}