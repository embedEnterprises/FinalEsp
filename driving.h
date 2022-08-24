#ifndef __DRIVING_H__
#define __DRIVING_H__
#include <Arduino.h>
#include <ESP32Servo.h>
#include <math.h>

#define servoPin 17
#define leftAngle 80
#define rightAngle 180
#define maxSteering 360

#define in1 18
#define in2 19

#define maxPwm 200
#define minPwm 40
#define maxSpeed 200

extern int pwm;
extern uint8_t steerAngle;
void SetupDriving();
void driveMotors();
void updatePose();

#endif
