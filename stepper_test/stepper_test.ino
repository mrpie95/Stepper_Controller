
#define BTN_UP_PIN 13
#define BTN_DOWN_PIN 12
#define UP HIGH
#define DOWN LOW
#define TOP 0
#define BOTTOM 1

byte directionPin = 9;
byte stepPin = 8;
int numberOfSteps = 30000;
byte ledPin = 13;
int pulseWidthMicros = 20;  
int millisbetweenSteps = 1;
int position = TOP;


void setup() { 

  Serial.begin(9600);
  Serial.println("Starting StepperTest");
  digitalWrite(ledPin, LOW);

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(BTN_UP_PIN, INPUT);
  pinMode(BTN_DOWN_PIN, INPUT);

 
}



void loop() { 

  if (digitalRead(BTN_UP_PIN) == 1){
    Serial.println("up pressed");
    moveMotor(UP, 30000);
    delay(100);
    moveMotor(UP, 8000);
    Serial.println("Movement Complete");
  }

  if (digitalRead(BTN_DOWN_PIN) == 1){
    Serial.println("down pressed");
    moveMotor(DOWN, 30000);
    delay(100);
    moveMotor(DOWN, 8000);
    Serial.println("Movement Complete");
  }
}



void moveMotor(int direction, int steps){
  Serial.println(position);

  if(((position == TOP) && (direction == DOWN)) || ((position == BOTTOM) && (direction == UP)))
  {
    Serial.println("Movement started");
    digitalWrite(directionPin, direction);
  
    for(int n = 0; n < steps; n++) {

      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulseWidthMicros); // this line is probably unnecessary
      digitalWrite(stepPin, LOW);
      delayMicroseconds(millisbetweenSteps*50); // this line is probably unnecessary
      digitalWrite(ledPin, !digitalRead(ledPin));

    }

    if (position == BOTTOM)
      position = TOP;
    else 
      position = BOTTOM;

  }
  else {
      Serial.println("Criteria for movement not met");
  }

}