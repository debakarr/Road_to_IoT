#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN 14
#define DHTTYPE DHT11 

const char* ssid = "Provakar_Wifi-Network";
const char* password = "linkingparkcool";
const char* mqtt_server = "iot.eclipse.org";

//float t = 27.0;

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(D4, OUTPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  dht.begin();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client-baka")) {
      Serial.println("connected");
      client.subscribe("baka/room1/lamp");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float t = dht.readTemperature();
  //t++;
  
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
   }

  char criticalTemp[10];

  snprintf(criticalTemp, sizeof criticalTemp, "%f", t);
  
  client.publish("baka/serverRoom/critical", criticalTemp);
  delay(5000);
}
