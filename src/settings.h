//WLAN-Config
//const char* ssid = "Keine Verbindung";               //Hier WLAN-Name eintragen
//const char* password = "[Al++Da]";            //Hier Passwort eintragen
const char* ssid = "FRITZ!Box 7530 WJ";               //Hier WLAN-Name eintragen
const char* password = "54609281796841465586";            //Hier Passwort eintragen
String sServerAdress = "http://192.168.178.23:80/game/index.php";    //Ziel URL (http://IP:80/game)

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

//Define PIN-Ein & Ausgaenge
int inputs_CS[] = {39, 35, 33, 34, 9, 11, 8, 7}; //Pins Chip-Select Eingänge/Ausgänge
int output_CS[] = {26, 18, 19}; //Pins Auswahl Chip-Select Baustein

//Ausgelesenes Array
int aktuell[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//Spielbrett-Array
int spielbrett[25][5] = { //set?;x;y;x_off;y_off
    {0, 100, 100, -100, -100},
    {0, -500, 500, -100, 100}, //Position 1
    {0, 100, 500, -100, 100}, //Position 2
    {0, 500, 500, 100, 100}, //Position 3
    {0, -300, 300, -100, 100}, //Position 4
    {0, 100, 300, -100, 100}, //Position 5
    {0, 300, 300, 100, 100}, //Position 6
    {0, -100, 100, -100, 100}, //Position 7
    {0, 100, 100, -100, 100}, //Position 8
    {0, 100, 100, 100, 100}, //Position 9
    {0, -500, 100, -100, -100}, //Position 10
    {0, -300, 100, -100, -100}, //Position 11
    {0, -100, 100, -100, -100}, //Position 12
    {0, 100, 100, 100, -100}, //Position 13
    {0, 300, 100, 100, -100}, //Position 14
    {0, 500, 100, 100, -100}, //Position 15
    {0, -100, -100, -100, -100}, //Position 16
    {0, 100, -100, -100, -100}, //Position 17
    {0, 100, -100, 100, -100}, //Position 18
    {0, -300, -300, -100, -100}, //Position 19
    {0, 100, -300, -100, -100}, //Position 20
    {0, 300, -300, 100, -100}, //Position 21
    {0, -500, -500, -100, -100}, //Position 22
    {0, 100, -500, -100, -100}, //Position 23
    {0, 500, -500, 100, -100} //Position 24
};


void setupPins(){
    pinMode(LED_BUILTIN, OUTPUT);   //Onboard LED
    pinMode(15, INPUT_PULLDOWN);    //Eingang Button
    pinMode(14,OUTPUT);             // Relais für Magnet
    pinMode(26, OUTPUT); //ChipSelect Baustein 1
    digitalWrite(26,HIGH);
    pinMode(18, OUTPUT); //ChipSelect Baustein 2
    digitalWrite(18,HIGH);
    pinMode(19, OUTPUT); //ChipSelect Baustein 3
    digitalWrite(19,HIGH);
    pinMode(13, OUTPUT); //Spannung auf Brett

    //pinMode(39,INPUT_PULLDOWN); //ChipSelect-Eingang 0 - INPUT_PULLDOWN
    //pinMode(35,INPUT_PULLDOWN); //ChipSelect-Eingang 1 - INPUT_PULLDOWN
    //pinMode(33,INPUT_PULLDOWN); //ChipSelect-Eingang 2 -INPUT_PULLDOWN
    //pinMode(34,INPUT_PULLDOWN); //ChipSelect-Eingang 3 - INPUT_PULLDOWN
    //pinMode(9,INPUT_PULLDOWN); //ChipSelect-Eingang 4
    //pinMode(11,INPUT_PULLDOWN); //ChipSelect-Eingang 5
    //pinMode(8,INPUT_PULLDOWN); //ChipSelect-Eingang 6
    //pinMode(7,INPUT_PULLDOWN); //ChipSelect-Eingang 7
    pinMode(36,INPUT_PULLDOWN); //Parkposition
}
