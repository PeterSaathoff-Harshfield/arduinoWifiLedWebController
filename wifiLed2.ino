// #pragma once

#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" 

#include "Controller.h"
#include "Light.h"
// #include "White.h"
// #include "Spectrum.h"
// #include "SolidColors.h"
// #include "Gradient.h"
// #include "Random.h"
// #include "Flow.h"
// #include "RedPulse.h"


int redPin = 6;
int greenPin = 5;
int bluePin = 3;

Light light(redPin, greenPin, bluePin);
Controller controller = Controller();

bool on = true;
int currentColor[3] = {100, 100, 100};

long currentTime = millis();
long lastTime = millis();



char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;



char* htmlHeader =
"HTTP/1.1 200 OK\n\
Content-Type: text/html\n\
Connection: close\n\
\n";

extern char index[];

char* jsonHeader =
"HTTP/1.1 200 OK\n\
Content-Type: text/json\n\
Connection: close\n\
\n";

char* jsonResponse = "";





WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  
  
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
  
  
  
  
}


int number = 0;

void loop() {
  if (on) {
    
    currentTime = millis();
    if (lastTime < currentTime - 20) {
      
      controller.update(currentTime);
      
      light.set(controller.r, controller.g, controller.b);
      
      lastTime = millis();
    }
    
    light.display();
  }
  else {
    light.set(0, 0, 0);
    light.display();
  }
  
  
  
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    
    String path = "";
    boolean gotPathLine = false;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (!gotPathLine) {
          path += c;          
        }
        
        if (c == '\n' && currentLineIsBlank) {
          path = path.substring(4, path.length()-11);
          
          char b[128];
          
          // Serial.print("path: ");
          // Serial.println(path);
          
          if (path == "/") {
            client.println(htmlHeader);
            client.println(index);
          }
          else {
            if (path == "/powerToggle") {
              on = !on;
            }
            if (path == "/white") {
              controller.setMode(0);
            }
            if (path == "/spectrum") {
              controller.setMode(1);
            }
            if (path == "/solidColors") {
              controller.setMode(2);
            }
            if (path == "/gradient") {
              controller.setMode(3);
            }
            if (path == "/random") {
              controller.setMode(4);
            }
            if (path == "/flow") {
              controller.setMode(5);
            }
            if (path == "/red") {
              controller.setMode(6);
            }
            if (path == "/left") {
              controller.adjustMode('l');
            }
            if (path == "/right") {
              controller.adjustMode('r');
            }
            
            
            // if (path == "/josn") {
            // }
            
            client.println(jsonHeader);
            buildJsonResponse();
            client.println(jsonResponse);
            
          }

          
          
          
          
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          gotPathLine = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
  }
}

void buildJsonResponse() {
  char r[512];
  char* onString;
  char* powerButtonString;
  if (on) {
    onString = "On";
    powerButtonString = "Turn Off";
  }
  else {
    onString = "Off";
    powerButtonString = "Turn On";
  }
  sprintf(r, "{\"number\": %d, \"powerStatus\": \"%s\", \"powerButtonText\": \"%s\", \"r\": %d, \"g\": %d, \"b\": %d}", number, onString, powerButtonString, controller.r, controller.g, controller.b);
  jsonResponse = r;
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
