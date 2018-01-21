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

#include <ESP8266WiFi.h>

const char * ssid = "Provakar_Wifi-Network"; // service set identifier i.e. name of the WiFi network
const char * password = "linkingparkcool"; // Password for the same network

/* We will use port number 80
 * NOTE: Port range is from 0 to 65535 and port 80 is used for HTTP 
 * On a Hypertext Transfer Protocol, port 80 is the port that the server is listening to or it expects to receive data from Web client through this port by default
 * Though we can configure it to listen through other ports too
*/ 
WiFiServer server(80);

WiFiClient client; // Initialize the client library

int LED_Pin = 2; // Inbuilt LED of NodeMCU is mapped to GPIO2

void setup() {
  Serial.begin(115200); //Sets the data rate in bits per second (baud) for serial data transmission to 115200
  
  WiFi.begin(ssid, password); // Connect to WiFi

  pinMode(LED_Pin, OUTPUT); // Set the pin mode
  digitalWrite(LED_Pin, LOW); // Sets the digital pin 2 off

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

  server.begin(); // Start the server and start listening for clients
}

void loop() {
  client = server.available(); // Initialize client, if there is any client available then we will recieve a byte

  // If there is no byte recieve then return
  if (!client) {
    return;
  }

  IPAddress remote = client.remoteIP();
  Serial.println();
  Serial.print("Client connected with IP ");
  Serial.println(remote);
  Serial.println();

  // client.available() returns the number of bytes available for reading 
  // Most of the time client will not send any byte. Hence we can have a loop when it's not happening with a certain delay
  while (!client.available()) {
    delay(1);
  }

  // Read a line of the request
  String request = client.readStringUntil('\r');

  // Instance variable to keep a check on state of LED i.e. either it is ON or OFF
  int value = 0;

  // Print the request in Serial Monitor
  Serial.println("Request:");
  Serial.println(request);

  // checking for corresponding request and thereafter turning the LED either ON or OFF
  // Here 'indexOf' locates a character or String within another String and returns index of val matched within the String, or -1 if it is not found
  if (request.indexOf("/INPUT=ON") != -1) {
    digitalWrite(LED_Pin, HIGH); // Sets the digital pin 2 on
    value = 1; // assign 1 to value
    Serial.println("LED is turned ON."); // print 'LED ON...' in Serial Monitor
  } else if (request.indexOf("/INPUT=OFF") != -1) {
    digitalWrite(LED_Pin, LOW); // Sets the digital pin 2 off
    value = 0; // assign 0 to value
    Serial.println("LED is turned OFF."); // print 'LED OFF...' in Serial Monitor
  } else {
    Serial.println("Invalid request"); // print 'Invalid request' if the request doesn't meet any of the above in Serial Monitor
  }

  client.flush(); // flush the buffer

  // Standard http response send by the server to the client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type:text/html");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<link href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css\" rel=\"stylesheet\">");
  client.println("<body>");
  client.println("<div class=\"container\">");
  client.println("<h1>Controlling LED using Web Browser</h1>");
  client.println("<a href=\"/INPUT=ON\"\"><button type=\"button\" class=\"btn btn-success\">ON</button></a>");
  client.println("<a href=\"/INPUT=OFF\"\"><button type=\"button\" class=\"btn btn-danger\">OFF</button></a>");
  client.println("<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js\"></script>");
  client.println("<script src=\"https://code.jquery.com/jquery-3.3.0.js\"></script>");
  client.println("<br>");
  client.println("<p>LED Status: </p>");
  if (value == 1) {
    client.println("<p class=\"text-success\">ON</p>");
  } else {
    client.println("<p class=\"text-danger\">OFF</p>");
  }
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");

  Serial.println();
  Serial.print("Client with IP ");
  Serial.print(remote);
  Serial.println(" disconnected");
}
