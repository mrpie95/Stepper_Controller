#define UP HIGH
#define DOWN LOW
#define TOP 0
#define BOTTOM 1

//set pin values
const int directionPin = 9;
const int stepPin = 8;
const int btnUpPin = 13;
const int btnDownPin = 12;

//global variables
const int fastPulseWidth = 35;  
int position;


void setup() {
  Serial.begin(9600);
  Serial.println("Starting Steppertest");

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(btnUpPin, INPUT);
  pinMode(btnDownPin, INPUT);
}

void loop() {


  //listen for UP press
  if(digitalRead(btnUpPin) == 1){
    Serial.println("up pressed");

    if(position == BOTTOM){
      Serial.println("Movement started");
      digitalWrite(directionPin, UP);
      moveMotor(30000);
      position = TOP;
    }
    else{
      Serial.println("already on top!");
    }
  }

  //listen for DOWN press
  if (digitalRead(btnDownPin) == 1){
    Serial.println("down pressed");
      
      if(position == TOP){
      Serial.println("Movement started");
      digitalWrite(directionPin, DOWN);
      moveMotor(30000);
      position = BOTTOM;
    }
    else{
      Serial.println("already on bottom!");
    }
  }
}

void moveMotor(int steps){
  for(int i = 0; i < steps; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(fastPulseWidth);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(fastPulseWidth);
  }
}