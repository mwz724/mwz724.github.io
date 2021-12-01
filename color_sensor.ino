// Color Sensor Example Code
// This code prints half the period of the signal sensed (pin7)
//
// MAE 3780 - Mechatronics
// Ethan Liu
// Last edited: 9/29/2021
// pin number of color sensor

const int colorPin = 12;
// declare variable to keep track of duration of wave
long duration;

void setup() {
  
 Serial.begin(9600); // initialize serial communication
 pinMode(colorPin, INPUT); // set color sensor pin to input
 
}

void loop() {
  
 duration = pulseIn(colorPin, HIGH); 
 // for pin starting at HIGH to go to LOW

 Serial.println(duration); // print duration to serial
 // monitor every 100ms
}
