//WLAN-Config
const char* ssid = "Keine Verbindung";               //Hier WLAN-Name eintragen
const char* password = "[Al++Da]";            //Hier Passwort eintragen
String sServerAdress = "http://192.168.250.50:80/game/index.php";    //Ziel URL (http://IP:80/game)

//Display-Config
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

//Motor-Config
#define MOTOR_STEPS 200
#define MOTOR_STEPS 200
// configure the pins connected
#define DIR 17
#define STEP 3
#define MS1 10
#define MS2 11
#define MS3 12

//Spielbrett-Config
    //25 Positionen; 0 = Parkposition; 1 = links oben - 24 = rechts unten
    //[x][0] => 1=belegt/0=frei
    //[x][1] => iM1steps (Schritte M1 Motor)
    //[x][2] => iM2steps (Schritte M2 Motor)
    //[x][3] => xXoffset 0=rechts,1=links
    //[x][4] => xYoffset 0=hoch,1=runter
    int brett[25][5];
//array 25x5 (25 Steine* SET, X, Y, OffsetX(0=R, 1=L), OffsetY(0=R, 1=L))

void setupPins(){
    pinMode(LED_BUILTIN, OUTPUT);   //Onboard LED
    pinMode(15, INPUT_PULLDOWN);    //Eingang Button
    pinMode(14,OUTPUT);             // Relais für Magnet
}
