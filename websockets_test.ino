#include <Ethernet.h>
#include <SPI.h>
#include <WebSocketClient.h>
#include <CommandManager.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//char server[] = "echo.websocket.org";
char server[] = "192.168.1.9";
char path[] = "/";
int port = 8080;
int ledPin = 30;
WebSocketClient client;
CommandManager commands;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Init");
  
  Ethernet.begin(mac);
  
  Serial.print("IP: ");
  Serial.print(Ethernet.localIP());
  Serial.println();
  
  Serial.println("Adding commands");
  commands.addCommand("ON", on);
  commands.addCommand("OFF", off);
  //commands.setDefaultCallback(unk);
  
  Serial.print("Connecting to ");
  Serial.println(server);
  client.connect(server, path, port);
  
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
  int len = 100;
  char command[len];
  data.toCharArray(command, len);
  commands.runCommand(command);
}

void on(){
  digitalWrite(ledPin, HIGH);
}

void off(){
  digitalWrite(ledPin, LOW);
}

void unk(char *command){
  Serial.print(command);
  Serial.println(": Unknown command.");
}
