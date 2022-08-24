#include "ledModes.h"

#define r1 13
#define r2 32
#define r3 14
#define l1 14
#define l2 27
#define l3 12
#define b 25

#define ON HIGH
#define OFF LOW

char ledMode = '0';

uint8_t arr[7] = {r1 , r2 , r3 , l1 , l2 , l3 , b};
uint8_t mode4Arr[6] = {r1 , r2 , r3 , l3 , l2 , l1};

TaskHandle_t Task1;

void switchOffAll(){
  for(uint8_t i = 0 ; i< 7; i++){
    digitalWrite(arr[i] , OFF);
  }
}

//inward moving led's
void mode1(){
  for(uint8_t i = 0; i<3 ; i++){
    digitalWrite(arr[i] , ON);
    digitalWrite(arr[i+3] , ON);
    delay(200); 
  }
  delay(200);
  for(uint8_t i = 0; i<3 ; i++){
    digitalWrite(arr[i] , OFF);
    digitalWrite(arr[i+3] , OFF);
    delay(200); 
  }
}

void mode2First(){
  digitalWrite(r1 , ON);
  digitalWrite(l1 , ON);
  digitalWrite(r2 , OFF);
  digitalWrite(l2 , OFF);
  digitalWrite(r3 , OFF);
  digitalWrite(l3 , OFF);
}
void mode2Second(){
  digitalWrite(r1 , OFF);
  digitalWrite(l1 , OFF);
  digitalWrite(r2 , ON);
  digitalWrite(l2 , ON);
  digitalWrite(r3 , OFF);
  digitalWrite(l3 , OFF);
}
void mode2Third(){
  digitalWrite(r1 , OFF);
  digitalWrite(l1 , OFF);
  digitalWrite(r2 , OFF);
  digitalWrite(l2 , OFF);
  digitalWrite(r3 , ON);
  digitalWrite(l3 , ON);

}

//swing leds one by one
void mode2(){
  mode2First();
  delay(200);
  mode2Second();
  delay(200);
  mode2Third();
  delay(200);
  mode2Third();
  delay(200);
  mode2Second();
  delay(200);
  mode2First();
  delay(200);
}


//Blink 
void mode3(){
  for(uint8_t i = 0; i<7 ; i++){
    digitalWrite(arr[i] , ON);
    digitalWrite(arr[i+3] , ON);
  }
  delay(200);
  for(uint8_t i = 0; i<7 ; i++){
    digitalWrite(arr[i] , OFF);
    digitalWrite(arr[i+3] , OFF);
  }
  delay(200);
}

//swing three led back and forth
void mode4(){
  for (uint8_t i = 0; i<4 ; i++){
    digitalWrite(mode4Arr[i] , ON);
    digitalWrite(mode4Arr[i+1] , ON);
    digitalWrite(mode4Arr[i+2] , ON);
    delay(200);
    switchOffAll();
  }
  delay(200);
  for (uint8_t i = 3; i>=0 ; i--){
    digitalWrite(mode4Arr[i] , ON);
    digitalWrite(mode4Arr[i+1] , ON);
    digitalWrite(mode4Arr[i+2] , ON);
    delay(200);
    switchOffAll();
  }
  delay(200);
}

void mode5(){
  switchOffAll();
  for(uint8_t i = 0; i< 6 ; i++){
    digitalWrite(mode4Arr[i] , ON);
    delay(100);
  }
  for(uint8_t i = 0 ; i<6;i++){
    digitalWrite(mode4Arr[i] , OFF);
    delay(100);
  }
  for(uint8_t i = 5 ; i>=0 ; i--){
    digitalWrite(mode4Arr[i] , ON);
    delay(100); 
  }
  for(uint8_t i = 5 ; i>=0 ; i--){
    digitalWrite(mode4Arr[i] , OFF);
    delay(100);
  }
}


void Task1code( void * parameter) {
  unsigned long int prevMil = millis();
  while(millis() - prevMil > 5000){
    switch(ledMode){
      case '0' : switchOffAll(); break;
      case '1' : mode1(); break;
      case '2' : mode2(); break;
      case '3' : mode3(); break;
      case '4' : mode4(); break;
      case '5' : mode5(); break;
    }
  }
  vTaskDelete(NULL);
}


void createLedTask(){
    xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "LedTask", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task1,  /* Task handle. */
      1); /* Core where the task should run */
}
void ledInit(){
  for(int i=0;i<=7;i++){
    pinMode(arr[i] , OUTPUT);
    digitalWrite(arr[i] , OFF);
  }
//  createLedTask();
}

void updateLedMode(char c){
  ledMode = c;
  createLedTask();
}
