#define UP HIGH
#define DOWN LOW
#define TOP 0
#define BOTTOM 1
#define BAUDRATE 57600

//set pin values
const int pwmRead = 3;
const int directionPin = 8;
const int stepPin = 9;
const int btnUpPin = 13;
const int btnDownPin = 12;
const int btnStartPin = 11;

//global variables
const int debounceDelay = 500;
const unsigned long fastPulseWidth = 35;  

volatile bool stateChanged = false;
volatile unsigned long cycleCount = 0;
bool counting = true;
bool setupDone = false;

unsigned long lastDebounceTime = 0;


bool buttonState = false;

void setup(){
  //initialisation message, set baudrate & pins
  Serial.begin(BAUDRATE);
  Serial.println("Starting...");

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(btnUpPin, INPUT);
  pinMode(btnDownPin, INPUT);
  pinMode(btnStartPin, INPUT);
  pinMode(pwmRead, INPUT);

  //interrupt script for counting 
  attachInterrupt(digitalPinToInterrupt(pwmRead), pulseCounterISR, CHANGE);
  sei();
  

  Serial.println("Ready.");

  //initialisation routine, listen for START press
  Serial.println("Press button to start...");
  while(digitalRead(btnStartPin) == LOW){}
  //move to top until top button is pressed
  while(digitalRead(btnDownPin) == LOW){
    digitalWrite(directionPin, DOWN);
    analogWrite(stepPin, 128);
  }
  
  delay(1000);
  int position = 0;
  
  digitalWrite(directionPin, UP);
  analogWrite(stepPin, 128);
}


void loop(){
  if(counting){
    if(stateChanged){
      cycleCount++;
      stateChanged=false;
    }
  }

  if(digitalRead(btnUpPin) == HIGH){
    if(setupDone == false){
     counting = false;
     analogWrite(stepPin, 0);
     Serial.print("Setup finished after: ");
     Serial.print(cycleCount);
     Serial.println(" steps.");
     setupDone = true;  
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

void pulseCounterISR() {
  stateChanged = true;
}
