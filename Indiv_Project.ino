// C++ code
// Michelle Zhou, Mechatronics Friday Lab
//
// This TinkerCAD simulates my Breathuino Individual Project consisting
// of 2 input signals: button and heartbeat sensor, and 2 output signals:
// a positional servo and a continuous servo. The code reads in an analog
// voltage signal from the button and potentiometer, then calculates an appropriate
// angle range for the positional servo and speed for the continuous servo.
// The output from the potentiometer is used/updated every so often via sampling.
// 
// To test: adjust the potentiometer to a higher number to simulate a 
// higher heart rate, press down on the button to represent user interfacing
// with the device.
// 
// Note: a potentiometer is used here to represent the heartbeat sensor 
// that I will be using, which outputs an analog signal representing heart rate.
// 
// Note: the continuous servo oscillates roughly around a stationary position
// when the switch is off, but in real life it should be completely still.
//


#include <Servo.h>       // load servo library

Servo myservo;          // create positional servo object
Servo my360servo;       // create continuous servo object

int angle = 0;          // declare variable for servo angle
int delayFactor = 1;    // WIP: trying to effectively control how fast positional servo is being set

int factor = 1.5;       // declare variable for continuous servo speed calibration 
int pulseRate = 10;     // declare variable for continuous servo speed
int angleRange = 90;    // declare variable for positional servo angle range
int offset = 90;        // declare variable for this specific servo's default starting angle

int pot = 0;            // declare variable for potentiometer output
int counter1 = 0;       // declare variable for sampling process
int counter2 = 0;       // declare variable for sampling process

// this set up code runs once
void setup() {
  myservo.attach(10);     // tell theArduino which pin will drive the positional servo
  my360servo.attach(11);  // tell theArduino which pin will drive the continuous servo
  
  Serial.begin (9600);    // Serial output initialization
  myservo.write(angle);   // manually setting up default angle position
}

// this code runs continuously
void loop(){  
  
  // CODE BLOCK 1
  // sampling potentiometer ("heartbeat sensor") output
  if (counter1 == 0 || counter1 > 10 || counter2 > 10){
    
    pot = analogRead(A0);   // 0-5V is mapped to base 10: 0-1023 
    Serial.println(pot);    // print to Serial Monitor
    
    pulseRate = pot/2;      // set speed of continuous servo proportional to potentiometer input
    angleRange = pot/6;     // set range of positional servo proportional to potentiometer input
    // ^ WIP: in order to be ~ 1/3 of heart rate, will need to callibrate this division
    // ^ Probably won't be divided by 6
   
    // Serial.println(angle);
    
    // sampling counter reset
    counter1 = 0;       
    counter2 = 0;
    
    // WIP: trying to scale the speed of the positional servo by changing 
    // the delay time betw angle change commands
    
    // delayFactor = angleRange/100;
  }

  
  // CODE BLOCK 2
  // rotating forward in 1 degree increments if button is pressed 
  // and angle range has not been swept through completely
  while(angle < angleRange && digitalRead(2) == HIGH){       
      // Serial.println ("Button pushed");
      angle++;                        // increment angle
      myservo.write(angle);           // move positional servo to new angle
      my360servo.write(factor*pulseRate);     //rotate one way at a callibrated speed proportional to potentiometer input
      delay(55);                      // only really affects the positional servo "speed"

      // Serial.println ("One way");     
      // Serial.println (angle);
  
      counter1++;               // controlling sampling time interval
  }
  
  
  // CODE BLOCK 3
  // rotating the other direction in 1 degree increments if button is pressed 
  // and angle range has been swept through completely
  while(angle>0 && digitalRead(2) == HIGH){         
      angle--;                            // decrement angle
      myservo.write(angle);                 // move positional servo to new angle
      my360servo.write(180 - factor*pulseRate);     // rotate the continuous servo the other way at slow speed

      // Serial.println ("Other way");     

      delay(5);                     // delay time in between increments
      counter2++;                   // controlling sampling time interval
  }
    
  
  // CODE BLOCK 4
  // resetting sampling counter and controlling continuous servo to stop when button is not pressed
  if (digitalRead(2) == LOW){
    my360servo.write(92.5);     // in real life, this translates to the continuous servo not moving
    
    // Serial.println ("Off"); 
    
    counter1 = 0;         // controlling sampling time interval       
    counter2 = 0;         // controlling sampling time interval
  } 
 
}
 
