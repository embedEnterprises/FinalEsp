#include "helper.h"
#include "driving.h"
#include "ledModes.h"
unsigned long prevMilis = 0;
void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  wifiInit();
  SetupDriving();
  ledInit();
}

void loop() {
  cleanupClients();
//  Serial.printf("pwm- %d  , throttle - %d , breaks - %d , steer - %d \n"  , pwm , throttle , breaks , steerAngle);
  if (millis() - prevMilis > 50) {
    if (throttle && pwm < maxPwm) {
      pwm = (maxPwm - pwm) < 3 ? maxPwm : pwm+3;
      if(pwm < minPwm) {
        pwm = minPwm;
      }
    } else if (breaks && pwm > -maxPwm ) {
      pwm = (pwm + maxPwm) < 3 ? -maxPwm : pwm - 3;
      if(pwm < 0 && pwm > -minPwm){
        pwm = -minPwm;
      }
    } else if (pwm > 0) {
      pwm -= 1;
    } else if(pwm < 0){
      pwm += 1;
    }
    driveMotors();
    prevMilis = millis();
  }
  updatePose();
}
