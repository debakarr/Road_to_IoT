#include <ESP8266WiFi.h>         
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>      
#include <PubSubClient.h>

const char* mqtt_server = "iot.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
//PubSubClient client2(espClient);
//PubSubClient client3(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Baka");
  Serial.println("Connected to Baka :)");

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    digitalWrite(2, LOW);  
  } else {
    digitalWrite(2, HIGH);  
  }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client-baka")) {
      Serial.println("connected");
      //client.publish("baka", "aarigato");
      client.subscribe("baka/room1/lamp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }

  //=================================================
  /*
  while (!client2.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client2.connect("ESP8266Client-baka")) {
      Serial.println("connected");
      //client.publish("baka", "aarigato");
      client2.subscribe("baka/room1/lamp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client2.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }

  //=================================================

  while (!client3.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client3.connect("ESP8266Client-baka")) {
      Serial.println("connected");
      //client.publish("baka", "aarigato");
      client3.subscribe("baka/room1/fanSpeed");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client3.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  */
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
//  client2.loop();
//  client3.loop();

  long now = millis();
  if (now - lastMsg > 500) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Aarigato Gojaimas %ld times", value);
    //Serial.print("Publish message: ");
    //Serial.println(msg);
    //client.publish("baka", msg);
  }
}
