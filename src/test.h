//Testfunktion

void test(){
    if(digitalRead(5) == HIGH){
        showText("Test","Endschalter Y");
        Serial.print("High5");
    }else{
        Serial.print("Low");
    }
    if(digitalRead(23) == HIGH){
        showText("Test","Endschalter X");
        Serial.print("High23");
    }else{
        Serial.print("Low23");
    }
}
