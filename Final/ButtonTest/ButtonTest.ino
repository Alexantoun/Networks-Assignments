#include <ESP8266WiFi.h>
#include "DHT.h"
//Sensor stuff
#define inRead 12
DHT dht(inRead, DHT11);

//wifi stuff
const char* ssid = "OceanFast_2GEXT";
const char* psswrd = "IDontKnow1";
const char* host ="192.168.1.6";
const uint16_t port = 2345;

//Component stuff
int bttnState = 0;
float temp;
float humid;
String msg = "";
                    

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
      client.print("bTrue");
    }
    else{
      digitalWrite(D4, LOW);
      client.print("bFalse");
    }
    delay(100);  
    temp = dht.readTemperature();
    humid = dht.readHumidity();
    msg = "c" + String(temp);
    Serial.println(msg);
    client.print(msg);
    msg = "";
    delay(100);
    msg = "h" + String(humid);
    Serial.println(msg);
    client.print(msg);
    //client.print   
    delay(2000);
  }

  Serial.println("Disconnected from server");
  delay(5000);

}
