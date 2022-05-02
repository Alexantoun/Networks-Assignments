#include <ESP8266WiFi.h>

const char* ssid = "OceanFast_2GEXT";
const char* psswrd = "IDontKnow1";
const char* host ="192.168.1.6";
const uint16_t port = 2345;
int bttnState = 0;


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
      digitalWrite(D4, LOW);
      client.print("Button being pressed");
      delay(750);
    }
    else{
      digitalWrite(D4, HIGH);
      client.print("Button not being pressed");
      delay(750);
    }
  }

  Serial.println("Disconnected from server");
  delay(500000);

}
