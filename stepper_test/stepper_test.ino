#define UP HIGH
#define DOWN LOW
#define TOP 0
#define BOTTOM 1
#define BAUDRATE 9600

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


void setup() {
  Serial.begin(BAUDRATE);
  Serial.println("Starting Steppertest");

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(btnUpPin, INPUT);
  pinMode(btnDownPin, INPUT);

  //used for debugging button behaviour
  //Serial.println(digitalRead(btnUpPin));
  //Serial.println(digitalRead(btnDownPin));
}

void loop() {
  unsigned long currentMillis = millis();

  //listen for UP press
  if(digitalRead(btnUpPin) == HIGH){

    if(!buttonState){

      if (currentMillis - lastDebounceTime >= debounceDelay) {
        lastDebounceTime = currentMillis;

        buttonState = true;

        if(position == BOTTOM){
          Serial.println("Up pressed");
          Serial.println("Movement started");
          moveMotor(UP, 30000);
          position = TOP;
        }

        else{
          Serial.println("Up pressed");
          Serial.println("Already on top!");
        }

        while(buttonState == 1){
          buttonState = digitalRead(btnUpPin);
        }
        buttonState = false;
      }
    }
  }

  //listen for DOWN press
  if(digitalRead(btnDownPin) == HIGH){

    if(!buttonState){

      if (currentMillis - lastDebounceTime >= debounceDelay) {
        lastDebounceTime = currentMillis;

        buttonState = true;

        if(position == TOP){
          Serial.println("Down pressed");
          Serial.println("Movement started");
          moveMotor(DOWN, 30000);
          position = BOTTOM;
        }

        else{
          Serial.println("Down pressed");
          Serial.println("Already on Bottom!");
        }

        while(buttonState == 1){
          buttonState = digitalRead(btnDownPin);
        }
        buttonState = false;
      }
    }
  }
}

void moveMotor(int direction, int steps){
  digitalWrite(directionPin, direction);
  for(int i = 0; i < steps; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(fastPulseWidth);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(fastPulseWidth);
  }
}