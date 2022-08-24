#include "driving.h"



int steer = 0;
uint8_t steerAngle = 0;
boolean throttle = false;
boolean breaks = false;
boolean directions = true; // true means forward
int pwm = 0;

const int freq = 5000;
const int resolution = 8;

unsigned long prevMil = 0;

Servo myservo;

TaskHandle_t throttleTask;

void driveMotors() {
  if (pwm >= 0) {
    ledcWrite(0, abs(pwm));
    ledcWrite(1, 0);
  } else {
    ledcWrite(0, 0);
    ledcWrite(1, abs(pwm));
  }
}

void updateSteer() {
  steerAngle = map(steer , -maxSteering , maxSteering , rightAngle , leftAngle);
}

void updatePose() {
  updateSteer();
  myservo.write(steerAngle);
  delay(20);
}

void throttleTaskCode(void * parameter) {
  Serial.println("throttle task code");
  while (true) {
    if (millis() - prevMil > 5) {
      if (throttle && pwm < maxPwm) {
        pwm += 5;
      } else if (breaks && pwm > -maxPwm ) {
        pwm -= 5;
      } else if (pwm > 0) {
        pwm -= 2;
      }
      driveMotors();
      prevMil = millis();
    }
    updatePose();
  }
}
void SetupDriving() {
  //Servo setup
//  ESP32PWM::allocateTimer(0);
//  ESP32PWM::allocateTimer(1);
//  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2500);

  //Motor setup
  pinMode(in1 , OUTPUT);
  pinMode(in2 , OUTPUT);
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcAttachPin(in1, 0);
  ledcAttachPin(in2, 1);
  Serial.println("setup driving");
//  xTaskCreatePinnedToCore(throttleTaskCode, "ThrottleTask", 10000, NULL, 1, &throttleTask, 1);
}
