#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Number of steps per revolution
uint16_t stepsZ = 200; // Need actual value!!

// on motor shield: M1/M2 = Pin 1; M3/M4 = Pin 2
uint8_t pinZ = 1;

Adafruit_StepperMotor *stepperZ = AFMS.getStepper(stepsZ, pinZ);

void setup()
{
    AFMS.begin();
    stepperZ->setSpeed(100);
}

void loop()
{
  // step(#steps, direction, steptype)
  //      direction: FORWARD or BACKWARD
  //      steptype: SINGLE, DOUBLE, INTERLEAVE or MICROSTEP
  stepperZ->step(1000, FORWARD, SINGLE);
}
