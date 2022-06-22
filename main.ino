#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define BUTTON_RED D1  
#define BUTTON_BLUE D2  

// WiFi
const char *ssid = ""; // Enter your WiFi name
const char *password = "";  // Enter WiFi password

// MQTT Broker

const char *mqtt_broker = "test.mosquitto.org";
const char *topic = "";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;
int r_goal=48;
int b_goal=48;
char red_char[256];
char blue_char[256];
String r_goal_srt;
String b_goal_str;

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
  reconnect();
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
 // Serial.println("MQTT connection succesfull");
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
      if(r_goal<=57){
        delay(1000);
        r_goal++;
        Serial.println("RED: ");
        Serial.printf("%d",r_goal);
     // MQTT.publish(topic, "2");
     //   Serial.println(MQTT.publish(topic, r_goal));
      }else{
        r_goal=0;
     //   Serial.println(MQTT.publish(topic, r_goal));
        Serial.println("RED WINS");
        Serial.printf("%d",r_goal);
      }
      }     
    } 
    if(!digitalRead(BUTTON_BLUE) == LOW) { 
      while(!digitalRead(BUTTON_BLUE) == LOW) {
        if(b_goal<=57){
        delay(1000);
        b_goal++;
        Serial.println("BLUE: ");
        Serial.printf("%d",b_goal); 
     // MQTT.publish(topic, ""); 
        b_goal_str=String(b_goal);
     //   Serial.println(b_goal_str);
        b_goal_str.toCharArray(blue_char, b_goal_str.length()+1);
      //  sprintf(blue_char, "%d", b_goal);
        Serial.printf("%d",blue_char); 
        Serial.println(MQTT.publish(topic, blue_char));
       }else{
        b_goal=0;
    //    sprintf(blue_char, "%d", b_goal);
    b_goal_str=String(b_goal);
        b_goal_str.toCharArray(blue_char, b_goal_str.length()+1);
        Serial.println(MQTT.publish(topic, blue_char));
        Serial.println("BLUE WINS");
        Serial.printf("%d",blue_char);
       }
        }   
      }  
    
  
  
}
