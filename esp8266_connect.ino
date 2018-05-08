#include<ESP8266WiFi.h>
#include <WiFiUdp.h>

// WiFi Definitions
const char* ssid = "Esp8266TestNet";
const char* password = "Esp8266Test"; // has to be longer than 7 chars


int ledPin1 = 13; // GPIO13

int ledPin2 = 12; // GPIO13

int ledPin3 = 14; // GPIO13
WiFiServer server(80);

void setup() {

   Serial.begin(115200);
   delay(10);
   pinMode(ledPin1, OUTPUT);
   pinMode(ledPin2, OUTPUT);
   pinMode(ledPin3, OUTPUT);
   digitalWrite(ledPin1, HIGH);
   digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin3, HIGH);// turn on

   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid, password, 1,1);
  Serial.println(WiFi.softAPIP());
 
   server.begin();
}

void loop() {
  // Check of client has connected
  WiFiClient client = server.available();
  if(!client) {
    return;
    Serial.println("N4ra");
  }

  // Read the request line
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  // Match request
  int value;
  if(request.indexOf("/led/1") != -1) {   //if(request.indexOf("/led/on") != -1) {
     digitalWrite(ledPin1, HIGH);
     Serial.println("ON");
     value = 1;
  } else if (request.indexOf("/led/0") != -1) {            //} else if (request.indexOf("/led/off") != -1) {
     digitalWrite(ledPin1, LOW);
     Serial.println("OFF");
      value = 0;
  }
  
  client.flush();

  // Send the response to the client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("LED yra: ");
  if(value == 1)
    client.print("Įjungta");
  else if (value == 0)
    client.print("Išjungta");
  delay(1);
  Serial.println("Client disconnected");

  // The client will actually be disconnected when the function returns and the client object is destroyed
}
