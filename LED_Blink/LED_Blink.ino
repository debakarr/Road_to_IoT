/*
 * Simple program to blink LED using Lolin NodeMCU V3 ESP8266 WiFi
 * This program will use the inbuit LED of Lolin NodeMCU V3 ESP8266 WiFi
 * The builtin LED of Lolin NodeMCU is attached to D4 with is mapped to GPIO2
 * Another thing to be noted is that the LED is active low
 * In other word if input to pin 2 is '0' then LED will turn 'ON' and if input to pin 2 is '1' then LED will turn OFF
 * NOTE: This is the only LED in Lolin NodeMCU and thus it differ from otherdevkits which have LED in GPIO16
 * In this program the LED will blink continuously i.e. it will be ON for 1 second and OFF for other 1 second
 */

int LED_Pin = 2; // As LED is attached with D4 which mapped to GPIO2 


void setup() {
  pinMode(LED_Pin, OUTPUT);
}

void loop() {
  digitalWrite(LED_Pin, HIGH); // LED ON
  delay(1000); // 1 second delay
  digitalWrite(LED_Pin, LOW); // LED OFF
  delay(1000); // 1 second delay
}
