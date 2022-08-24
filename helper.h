#ifndef __HELPER_H__
#define __HELPER_H__

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "ledModes.h"



extern int steer;
extern boolean throttle;
extern boolean breaks;
extern char ledMode;

void wifiInit();
void cleanupClients();

#endif
