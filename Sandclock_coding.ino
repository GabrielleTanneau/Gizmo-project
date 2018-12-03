// Gizmo project - Reverse Sandclock

#include <Stepper.h>

const int stepsPerRevolution = 512;  // Number of steps per revolution for our motor (28BYJ-48)

// defines pins numbers for the Ultrasonic sensor (HC-SR04)
const int trigPin = 7;
const int echoPin = 6;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); // Write down pins accoridng to the order 1,3,2,4 

// defines variables
long duration; // duration of echo
int distance; // distance between the sensor and whatever is in front
int Step = 0; // number of revolutions done by the motor
int previous; // previous distance


void setup() {
  myStepper.setSpeed(64);   // set the speed at 64 rpm:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}


void loop() {
  
  previous = distance ; // The 'previous' variable is taking the value of the distance previously read
  
  // Read the distance between the sensor and any object in front of it
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = duration * 0.34 / 2;


// Making the motor turning clockwise or anti-clockwise in order to make the magnet moving up or down

  if ( (distance < 300) && (0 < Step <= 14)) // if something is detected by the sensor and if the magnet is down or the magnet is not at the top (kowing that the top is reached in 14 revolutions
  {
    if (distance - previous <= 0) { // if the hand comes closer to the sensor, the magnet goes up
      myStepper.step(stepsPerRevolution); // the motor is making one revolution turning clockwise
      delay(0.9375); // wait until the revolution is completed
      Step++; // adding one revolution
    }
    
    else { // if the hand goes away from the sensor, the magnet goes down
      myStepper.step(-stepsPerRevolution); // the motor is making one revolution turning anti-clockwise
      delay(0.9375); // wait until the revolution is completed
      Step--; // substracting one revolution
    }
  }
  
  else if ( (distance > 300) && (Step > 0)) { // if there is nothing detected by the sensor but the magnet is still up, it automatically goes down to the strating position
    myStepper.step(-stepsPerRevolution); // the motor is making one revolution turning anti-clockwise
    delay(0.9375); // wait until the revolution is completed
    Step--; // substracting one revolution
  }
  
  else { // if the hand is out of the sensor and the magnet is down, nothing happens
    myStepper.step(0);
  }

}
