/*
 * Control a LED from Web Browser using NodeMCU
 * In this sketch we will use the builtin LED of Lolin NodeMCU v3
 * The builtin LED of Lolin NodeMCU is attached to D4 with is mapped to GPIO2
 * Another thing to be noted is that the LED is active low
 * In other word if input to pin 2 is '0' then LED will turn 'ON' and if input to pin 2 is '1' then LED will turn OFF
 * NOTE: This is the only LED in Lolin NodeMCU and thus it differ from otherdevkits which have LED in GPIO16
 * We will use Transmission Control Protocol as a channel between server and client (transport) and WiFi as Network
 * Here our NodeMCU will act as a server and we can connect using any device (client) which is connected with the same WiFi network using web browser
 */

#include <SPI.h> // serial peripheral interface
#include <ESP8266WiFi.h>

const char * ssid = "thanks"; // service set identifier i.e. name of the WiFi network
const char * password = "@#12345#@"; // Password for the same network

/* We will use port number 80
 * NOTE: Port range is from 0 to 65535 and port 80 is used for HTTP 
 * On a Hypertext Transfer Protocol, port 80 is the port that the server is listening to or it expects to receive data from Web client through this port by default
 * Though we can configure it to listen through other ports too
*/ 
//WiFiServer server(80);

IPAddress server(192,168,43,94);

WiFiClient client; // Initialize the client library

int LED_Pin = 2; // Inbuilt LED of NodeMCU is mapped to GPIO2

void setup() {
  Serial.begin(115200); //Sets the data rate in bits per second (baud) for serial data transmission to 115200
  
  WiFi.begin(ssid, password); // Connect to WiFi

  pinMode(LED_Pin, OUTPUT); // Set the pin mode
  digitalWrite(LED_Pin, HIGH); // Sets the digital pin 2 off

  Serial.print("Trying to connect. Please wait ");

  // Attempting to connect to Wifi network, print '*' until connected
  // WiFi.status() is assigned WL_CONNECTED when connected to a WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.print("*");
  }

  // Print the network in which we are connected and the URL for accessing server in Serial Monitor
  Serial.print("\nConnected to ");
  Serial.println(ssid);
  Serial.print("Local IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.println();

//  server.begin(); // Start the server and start listening for clients
}

void loop() {
  client.connect(server, 80); // Initialize client, if there is any client available then we will recieve a byte
  String request = client.readStringUntil('\r');
  digitalWrite(LED_Pin, LOW);
  delay(500);
  digitalWrite(LED_Pin, HIGH);
}
