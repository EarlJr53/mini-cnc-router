#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define RPWM 5
#define LPWM 6
#define REN 8
#define LEN 9

#define HOVER 0


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Number of steps per revolution
uint16_t stepsZ = 200; // Need actual value!!

// on motor shield: M1/M2 = Pin 1; M3/M4 = Pin 2
uint8_t pinZ = 1;

Adafruit_StepperMotor *stepperZ = AFMS.getStepper(stepsZ, pinZ);

String request;
int speed = 0;
uint8_t direction = HOVER;

void setup()
{
    Serial.begin(9600);
    Serial.setTimeout(1);

    AFMS.begin();

    pinMode(RPWM,OUTPUT);
    pinMode(REN,OUTPUT);
    pinMode(LPWM,OUTPUT);
    pinMode(LEN,OUTPUT);

    stepperZ->setSpeed(100);

    while (!Serial.available())
    {
    }

    digitalWrite(REN,HIGH);
    digitalWrite(LEN,HIGH);
}

void loop()
{

  if (Serial.available() > 0) 
  {
    request = Serial.readString();
  }


  if (request == "stop")
  {
    speed = 0;
    stepperZ->release();
  }
  else if (request == "up")
  {
    direction = FORWARD;
  }
  else if (request == "down")
  {
    direction = BACKWARD;
  }
  else
  {
    speed = 50 * request.toInt();
  }

  analogWrite(RPWM,speed);
  analogWrite(LPWM,0);

  // step(#steps, direction, steptype)
    //      direction: FORWARD or BACKWARD
    //      steptype: SINGLE, DOUBLE, INTERLEAVE or MICROSTEP
  stepperZ->step(60, direction, SINGLE);
}
