#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define BUTTON_RED D1  
#define BUTTON_BLUE D2  

// WiFi
const char *ssid = ""; // Enter your WiFi name
const char *password = "";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "";
const char *topic = "";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;


WiFiClient WIFI;
PubSubClient MQTT(WIFI);


void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_RED, INPUT);
  pinMode(BUTTON_BLUE, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
  }
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void reconnect() {
  MQTT.setServer(mqtt_broker, mqtt_port);
  MQTT.setCallback(callback);
  while (!MQTT.connected()) {
   String clientID = "esp8266";
    clientID += String(WiFi.macAddress());
    Serial.println("Attempt to connect to MQTT broker");
    if (MQTT.connect(clientID.c_str(), mqtt_username, mqtt_password )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(MQTT.state());
    delay(3000);
  }


}
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
void loop() {

 
    
    
     if(!digitalRead(BUTTON_RED) == LOW) {

    
    while(!digitalRead(BUTTON_RED) == LOW) {
      delay(1000);
      MQTT.publish(topic, "2");
     // Serial.println(MQTT.publish(topic, "2"));
      }     
    } 
    if(!digitalRead(BUTTON_BLUE) == LOW) {
       
      while(!digitalRead(BUTTON_BLUE) == LOW) {
        delay(1000);
        MQTT.publish(topic, "1"); 
       //  Serial.println(MQTT.publish(topic, "1"));
        }   
      }  
    
  
  
}
