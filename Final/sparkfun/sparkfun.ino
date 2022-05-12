#include <WiFi.h>
int ledPin = 5;

const char * netName = "";
const char * psswrd = "";
const char* host = "192.168.1.24";
const int port = 2345;

const int bttn = 0;
const int redLED = 17;
int bttnState = 0;

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.println(netName);
    WiFi.mode(WIFI_STA);
    WiFi.begin(netName, psswrd);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
    pinMode(redLED, OUTPUT);
    digitalWrite(redLED, HIGH);
    pinMode(bttn, INPUT);
}

void loop()
{
  WiFiClient client;
  if(!client.connect(host,port)){
    Serial.println("Connection Failed");
    delay(5000);
  }
  while(client.connected()){
    bttnState = digitalRead(bttn);
    if(bttnState == LOW){
      digitalWrite(redLED, LOW);
      client.print("Button being pressed");
      delay(1000);
    }
    else{
      digitalWrite(redLED, HIGH);
      client.print("Button not being pressed\n");
      delay(1000);
    }  
  }
  Serial.println("Disconnected from server");
}
