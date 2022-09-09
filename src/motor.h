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
int iStepperspeed = 4000; //in Mikrosekunden für PWM 
bool xXlock = false;
bool xYlock = false;




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
        digitalWrite(17,LOW); // M1 im Uhrzeigersinn
        digitalWrite(16,LOW); // M2 im Uhrzeigersinn
        iXpos = iXpos + steps;
    }else if(direction == "links"){
        digitalWrite(17,HIGH); // M1 gegen Uhrzeigersinn
        digitalWrite(16,HIGH); // M2 gegen Uhrzeigersinn
        iXpos = iXpos - steps;
    }else if(direction == "oben"){
        digitalWrite(17,HIGH); // M1 gegen Uhrzeigersinn
        digitalWrite(16,LOW); // M2 im Uhrzeigersinn
        iYpos = iYpos + steps;
    }else if(direction == "unten"){
        digitalWrite(17,LOW); // M1 im Uhrzeigersinn
        digitalWrite(16,HIGH); // M2 gegen Uhrzeigersinn
        iYpos = iYpos - steps;
    }else{
        //Error
    }
    iStepCounter = 0;

    for(iStepCounter = 0; (iStepCounter < steps && xXlock == false && xYlock == false); iStepCounter++) {
        
        if(digitalRead(5) == HIGH){
            xYlock = true;
        }
        if(digitalRead(23) == HIGH){
            xXlock = true;
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
        for(int j = 0; j<5; j++){
            digitalWrite(3,HIGH);
            digitalWrite(1,HIGH);
            delayMicroseconds(iStepperspeed);
            digitalWrite(3,HIGH);
            digitalWrite(1,LOW);
            delayMicroseconds(iStepperspeed);
        }
    }
    



    iStepCounter = 0;
    showText("Aktuelle Position","X: "+convertIntToString(iXpos)+" - Y: "+convertIntToString(iYpos));
}
*/

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