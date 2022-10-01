#include "helper.h"

const char* ssid = "Onkar";
const char* password = "Onkar@link";

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void assignValues(uint8_t *data , size_t len){
//  Serial.print("w " );
//  Serial.println(xPortGetCoreID());
  char command = 'a';
  uint8_t i = 0;
  while(i<len){
    command = (char) data[i];
    if(isAlpha(command)){
      i++;
      switch(command) {
        case 's' :if((char)data[i] == '+'){
                    steerFlg = true; 
                  }else {
                    steerFlg = false;
                    steer = atoi((const char *) &data[i]);
                  }
                  break;
        case 't' : throttle = (char) data[i] == '1' ? true : false;
                  break;
        case 'l' : updateLedMode((char) data[i]);
                  break;
        case 'b' : breaks = (char) data[i] == '1' ? true : false;
                  break;
      }
    }
    i++;
  }
}


void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      {
        assignValues(data , len);
      }
      break;
    case WS_EVT_PONG:
    {
      
    }
      break;
    case WS_EVT_ERROR:
    {
      
    }
      break;
  }
  vTaskDelay(3);
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void wifiInit(){
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  } 
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

//  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text", "HTTP GET request sent to your ESP on input field (");
  });

  // Start server
  server.begin();
}


void cleanupClients(){
  ws.cleanupClients();
}
