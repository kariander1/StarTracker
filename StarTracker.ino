/* Example sketch to control a 28BYJ-48 stepper motor with ULN2003 driver board and Arduino UNO. More info: https://www.makerguides.com */

// Include the Arduino Stepper.h library:
#include "Point.h"
#include "eeprom.h"
#include "Antenna.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "Serializer.h"

//Servo srv;  // create servo object to control a servo

Antenna tracker(8, 10, 9, 11,0);


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 13;     // the number of the pushbutton pin
const int ledPin = 7;      // the number of the LED pin
const int servo_az_pin = 53;
const int servo_el_pin = 52;


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
   
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
  //  srv.attach(52);
    tracker.init(servo_el_pin,2);
   
    // eeprom_write_byte((uint8_t*)(0),0);
   // eeprom_write_byte((uint8_t*)(0+ 1), 0);
}

float angle = 0;
void loop() {
    
   
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        digitalWrite(ledPin, HIGH);
       
    }
    else {
        // turn LED off:
        digitalWrite(ledPin, LOW);
        tracker.setCoordinates(Point(angle, angle));


        angle += 45;
        if (angle >90)
            angle = 0;
   
    }
    Point dest = tracker.coordinates;
    if (Serializer::ListenForCoordinates(dest))
    {
       // tracker.setCoordinates(dest);
        tracker.setCoordinatesAsync(dest);
    }
    
}