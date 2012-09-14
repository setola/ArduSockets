#include "Arduino.h"
#include <Ethernet.h>
#include <SPI.h>
#include <WebSocketClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//char server[] = "echo.websocket.org";
char server[] = "192.168.168.46";
WebSocketClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Init");
  
  Ethernet.begin(mac);
  
  Serial.print("IP: ");
  Serial.print(Ethernet.localIP());
  Serial.println();
  
  
  Serial.print("Connecting to ");
  Serial.println(server);
  client.connect(server);
  
  if(client.connected()){
    Serial.println("Connected");
  } else {
    Serial.println("Connection Failed");
  }
  
}

void loop() {
  client.monitor();
  
  if(!client.connected()){
    Serial.print("Retrying connection to: ");
    Serial.println(server);
    
    client.disconnect();
    client.connect(server);
  }
  
  if(client.connected()){
    client.setDataArrivedDelegate(dataArrived);
    Serial.println("Sending...");
    client.send("Hello World!");
  }
  delay(1000);
}

void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}
