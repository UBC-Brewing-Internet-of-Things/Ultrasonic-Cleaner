#include <Servo.h>

Servo myservo;
int servoPin = 9;   // Servo control pin
int switchPin = 2; // Start button connected to pin 2
int ledPin = 13;     // Built-in LED for status indicator

bool isCleanerOn = false;
bool initialize = true;
unsigned long currentTime = 0;



//Parameters for ultrasonic cleaning. 
//Machine will turn on for "onTimer" minutes then off for "offTimer" minutes
//until "totalDuration" is exceeded. 
int onTimer = 25 * 60 * 1000; // Minutes in milliseconds
int offTimer = 5 * 60 * 1000; // Minutes in milliseconds
int totalDuration = 5 * 60 * 60 * 1000 // Hours in milliseconds


void setup() {
  myservo.attach(servoPin);
  pinMode(switchPin, INPUT_PULLUP);  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Turn off the LED initially
}


void loop() {
  // Get the current time
  unsigned long currentTime = millis();

  // Check if the switch is turned on
  if (digitalRead(switchPin) == LOW) {

    //Run once to start the cleaning
    if(initialize && !isCleanerOn){
        startTime = currentTime;
        pressButton(); 
        isCleanerOn = true;
        initialize = false;
        onTime = currentTime + onTimer;
        digitalWrite(ledPin, HIGH);
    }
    // Check if the onTimer is exceeded
    if (currentTime >= onTime && isCleanerOn) {
      // Turn the cleaner off
      pressButton(); 
      isCleanerOn = false;
      offTime = currentTime + offTimer;
    }

    // Check if the offTimer is exceeded
    if (currentTime >= offTime && !isCleanerOn) {
      // Turn the cleaner on 
      pressButton(); 
      isCleanerOn = true;
      onTime = currentTime + onTimer;
    }

    // Check if the totalDuration is exceeded
    if (currentTime - startTime >= totalDuration) {
      // Turn the cleaner off
      if (isCleanerOn) {
        pressButton(); 
        isCleanerOn = false;
        digitalWrite(ledPin, LOW);
      }
    }
  }
  else {
    // Switch is turned off, ensure cleaner is off
    if (isCleanerOn) {
      pressButton(); 
      isCleanerOn = false;
    }
    // Turn light off and prep for new cleaning run
    initialize = true;
    digitalWrite(ledPin, LOW);
    
  }
}

//rotates servo to press button
void pressButton(){
    myservo.write(90);
    delay(500);
    myserbo.write(0);
}