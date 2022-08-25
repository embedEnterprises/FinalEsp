#include "helper.h"
#include "driving.h"
#include "ledModes.h"
unsigned long prevMilis = 0;
int core = 3;
int prevCore = -1;
void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  wifiInit();
  SetupDriving();
  ledInit();
}

void loop() {
  cleanupClients();
//  Serial.printf("pwm- %d  , steer - %d \n",pwm,steerAngle); //breaks - %d , steer - %d \n"  , pwm , throttle , breaks , steerAngle);
core = xPortGetCoreID();
if(core != prevCore){
  
Serial.print("l " );
  Serial.println(core);
  prevCore = core;
}
  if (millis() - prevMilis > 15) {
    if (throttle && pwm < maxPwm) {
      pwm = (maxPwm - pwm) < 1 ? maxPwm : pwm+1;
      if(pwm < minPwm) {
        pwm = minPwm;
      }
    } else if (breaks && pwm > -maxPwm ) {
      pwm = (pwm + maxPwm) < 3 ? -maxPwm : pwm - 3;
//      if(pwm > 0 && pwm < minPwm){
//        pwm = 0;
//      }
//      if(pwm < 0 && pwm > -minPwm){
//        pwm = -minPwm;
//      }
    } else if (pwm > 0) {
      if(pwm < minPwm) {
        pwm = 0;
      }else {
        pwm -= 3;
      }
    } else if(pwm < 0){
      pwm += 2;
    }
    driveMotors();
    prevMilis = millis();
  }
  updatePose();
}
