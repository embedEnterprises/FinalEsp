#ifndef __DRIVING_H__
#define __DRIVING_H__
#include <Arduino.h>
#include <ESP32Servo.h>
#include <math.h>
#include "helper.h"

#define servoPin 17
#define leftAngle 65
#define rightAngle 165
#define centerAngle 115
#define maxSteering 180

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
