#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid = "E2 111 2.4GHz";
const char* password =  "neeta0605";

//Global 
AsyncWebServer server(80);
AsyncWebSocket connection("/test");



void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){

  if(type == WS_EVT_CONNECT){

    Serial.println("Websocket client connection received");

  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
    Serial.println("-----------------------");

  } else if(type == WS_EVT_DATA){

    Serial.print("Data received: ");

    for(int i=0; i < len; i++) {
          Serial.print((char) data[i]);
    }

    Serial.println();
  }
}

void setup(){
  Serial.begin(115200);

  if(!SPIFFS.begin()){
     Serial.println("An Error has occurred while mounting SPIFFS");
     return;
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  connection.onEvent(onWsEvent);
  server.addHandler(&connection);

  server.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });



  server.begin();
}

void loop(){}


/*
 * class Joystick1
 * {
 * public:
 * int stick1x;
 * int stick1y;
 * }
 * 
 * class Joystick2
 * {
 * public:
 * int stick2x;
 * int stick2y;
 * }
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
