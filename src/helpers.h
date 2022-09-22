#include <stdio.h>
#include <Wire.h>

bool xEdgeEndschalterX;
bool xEdgeEndschalterY;

// für switchMagnetState():
bool xMagnetEnabled = false;

int convertStringToInt(String s){               //Konvertiert String zu Int => für Verwertung der GET-Parameter benötigt
  int iTmp_int;
  const char * c = s.c_str();
  sscanf(c, "%d", &iTmp_int);
  return iTmp_int;
}

String convertIntToString(int i){               //Konvertiert Int zu String => für Lesbare Ausgabe notwendig
  char str[5];
  return itoa(i, str, 10);
}

String convertBoolToString(bool b){             //Konvertiert Bool zu String
  return b ? "true" : "false";
}

int convertBoolToInt(bool b){                   //Konvertiert Bool zu Integer
  return b ? 1 : 0;
}

void resetVars(){
  iRemoved = 999;
  iAdded = 999;
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