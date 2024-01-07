#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define GPIO_PARACHUTE 1 //TX

// Replace with your desired credentials
const char *ssid = "czarus";
const char *password = ""; // Password can be between 8 and 64 characters
ESP8266WebServer server(80); 

void handleRoot() {  // HTML & CSS content for the web page
  String HTML = "<html>\
  <head>\
    <title>ESP8266 Parachute Deploy</title>\
    <style>\
      body { background-color: #def; font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }\
      .button { padding: 15px 25px; font-size: 24px; text-align: center; cursor: pointer; outline: none; color: #fff; background-color: #008CBA; border: none; border-radius: 15px; box-shadow: 0 9px #999; }\
      .button:hover {background-color: #0077A7}\
      .button:active { background-color: #0077A7; box-shadow: 0 5px #666; transform: translateY(4px); }\
    </style>\
  </head>\
  <body>\
    <h1>ESP8266 Parachute Controller</h1>\
    <form action=\"/deploy\">\
      <input type=\"submit\" class=\"button\" value=\"DEPLOY PARACHUTE!\"/>\
    </form>\
  </body>\
</html>";

  server.send(200, "text/html", HTML); // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleDeployParachute() {
  digitalWrite(GPIO_PARACHUTE, HIGH); // Set TX GPIO 1 high
  delay(500);
  digitalWrite(GPIO_PARACHUTE, LOW);
  //server.send(200, "text/plain", "Parachute Deployed!");
}

void setup() {
  Serial.begin(115200); // Starts serial communication
  Serial.println();

  //init parachute deploy
  pinMode(GPIO_PARACHUTE, OUTPUT); // Set GPIO 2 as output
  digitalWrite(GPIO_PARACHUTE, LOW); // Initialize GPIO 2 to low

  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter if you want the AP to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP(); // Get the ESP's IP address
  server.on("/", HTTP_GET, handleRoot); // Serve the HTML form at root
  server.on("/deploy", HTTP_GET, handleDeployParachute); // Handle form submission
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop() {
  server.handleClient();
}
