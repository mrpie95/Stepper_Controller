#define UP HIGH
#define DOWN LOW
#define TOP 0
#define BOTTOM 1
#define baudRate 9600

//set pin values
const int directionPin = 9;
const int stepPin = 8;
const int btnUpPin = 13;
const int btnDownPin = 12;

//global variables
const int debounceDelay = 500;
const unsigned long fastPulseWidth = 35;  

int position;
unsigned long lastDebounceTime = 0;


bool buttonState = false;

void setup(){
    //initialisation message, set baudrate & pins
    Serial.begin(baudRate);
    Serial.println("Starting...");

    pinMode(directionPin, OUTPUT);
    pinMode(stepPin, OUTPUT);

    pinMode(btnUpPin, INPUT);
    pinMode(btnDownPin, INPUT);
    
    Serial.println("Ready.");

    //initialisation routine
    Serial.println("Press button to start...");

}

void loop(){

}

void moveMotor(int steps){
  for(int i = 0; i < steps; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(fastPulseWidth);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(fastPulseWidth);
  }
}