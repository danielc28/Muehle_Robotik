#include <stdio.h>
#include <Wire.h>

bool xEdgeEndschalterX;
bool xEdgeEndschalterY;

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

void resetVars(){
  iRemoved = 999;
  iAdded = 999;
}
