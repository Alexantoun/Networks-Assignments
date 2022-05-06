#include <ESP8266WiFi.h>
#include "DHT.h"
#define inRead 12
DHT dht(inRead, DHT11);
const char* ssid = "Alex's iPhone (2)";
const char* psswrd = "alex1234";
const char* host ="172.20.10.9";
const uint16_t port = 2345;
int bttnState = 0;
float temp;
float humid;
int status;
                    

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, psswrd);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.print("WiFi Connected! Local IP is: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  pinMode(D3, INPUT);
  pinMode(inRead, INPUT);
  dht.begin();
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  WiFiClient client;
  if(!client.connect(host,port)){
    Serial.println("Connection Failed");
    delay(5000);
  }
  while(client.connected()){
    bttnState = digitalRead(D3);
    if(bttnState == LOW){
      digitalWrite(D4, HIGH);
      client.print("Button being pressed");
    }
    else{
      digitalWrite(D4, LOW);
      client.print("Button not being pressed");
    }  
    status = dht.read(inRead);
    Serial.println(status);
    temp = dht.readTemperature();
    Serial.println(temp);
    Serial.print("Tempreture read = ");
    Serial.print(temp);
    client.print("Humid Read = ");
    client.print(dht.readHumidity());
    delay(2000);
  }

  Serial.println("Disconnected from server");
  delay(500000);

}
