#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <ESP8266HTTPClient.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "ESP8266WiFi.h"
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "-uvM9xxxxxxxxxGDIwq0_PYMO_FU3Yzk";

char ssid[] = "Your_wifi_name";         // your network SSID name
char pass[] = "_password_";          // your network password
WidgetMap myMap(V1);
//Credentials for Google GeoLocation API...

const char* Host = "www.googleapis.com";
String thisPage = "/geolocation/v1/geolocate?key=";
String key = "AIzaSyC0yXJeJxcPLINxuUxxxxxxxxx_xxx";

int status = WL_IDLE_STATUS;
String jsonString = "{\n";

float latitude    = 0.0;
float longitude   = 0.0;

double accuracy    = 0.0;
int more_text = 1;    // set to 1 for more debug output

void setup()   {
  Serial.begin(115200);
  Serial.println("Start");
 
 // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
  
// We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".");
   Blynk.begin(auth, ssid, pass);

  // If you want to remove all points:
  //myMap.clear();

  int index = 1;
  float lat = 0.0;
  float lon = 0.0;
  myMap.location(index, lat, lon, "value");

}

void loop() {
  Blynk.run();
  char bssid[6];
  DynamicJsonDocument doc(1024);
  Serial.println("scan start");
  
// WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  elseb
  {
    Serial.print(n);
    Serial.println(" networks found...");

    if (more_text) {
      Serial.println("\"wifiAccessPoints\": [");
      for (int i = 0; i < n; ++i)
      {
        Serial.println("{");
        Serial.print("\"macAddress\" : \"");
        Serial.print(WiFi.BSSIDstr(i));
        Serial.println("\",");
        Serial.print("\"signalStrength\": ");
        Serial.println(WiFi.RSSI(i));
        if (i < n - 1)
        {
          Serial.println("},");
        }
        else
        {
          Serial.println("}");
        }
      }
      Serial.println("]");
      Serial.println("}");
    }
    Serial.println(" ");
  }

// now build the jsonString...
  jsonString = "{\n";
  jsonString += "\"homeMobileCountryCode\": 91,\n"; // country code
  jsonString += "\"homeMobileNetworkCode\": 91,\n";  // country code
  jsonString += "\"radioType\": \"lte\",\n";         // for network mode
  jsonString += "\"carrier\": \"Jio\",\n";      // associated with network carrier
  jsonString += "\"wifiAccessPoints\": [\n";
  for (int j = 0; j < n; ++j)
  {
    jsonString += "{\n";
    jsonString += "\"macAddress\" : \"";
    jsonString += (WiFi.BSSIDstr(j));
    jsonString += "\",\n";
    jsonString += "\"signalStrength\": ";
    jsonString += WiFi.RSSI(j);
    jsonString += "\n";
    if (j < n - 1)
    {
      jsonString += "},\n";
    }
    else
    {
      jsonString += "}\n";
    }
  }
  jsonString += ("]\n");
  jsonString += ("}\n");

  //-------------------------------------------------------------------- Serial.println("");

  //Connect to the client and make the api call

  WiFiClientSecure client;
  Serial.print("Requesting URL: ");
  Serial.println("https://" + (String)Host + thisPage + key);
  Serial.println(" ");
  if (client.connect(Host, 443)) {
    Serial.println("Connected");
    client.println("POST " + thisPage + key + " HTTP/1.1");
    client.println("Host: " + (String)Host);
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.println("User-Agent: Arduino/1.0");
    client.print("Content-Length: ");
    client.println(jsonString.length());
    client.println();
    client.print(jsonString);
    delay(500);
  }

  //Read and parse all the lines of the reply from server
  while (client.available()) {
    String line = client.readStringUntil('\r');
    if (more_text) {
      Serial.print(line);
    }
  DeserializationError error = deserializeJson (doc, line);
    if (error) {
      Serial.print("deserializeJson() failed with code ");
      Serial.println(error.c_str());
      return;
    }
      double latitude    = doc["location"]["lat"];
      double longitude   = doc["location"]["lng"];
      double accuracy   = doc["accuracy"];
    }
  

  Serial.println("closing connection");
  Serial.println();
  client.stop();

  Serial.print("Latitude = ");
  Serial.println(latitude, 6);
  Serial.print("Longitude = ");
  Serial.println(longitude, 6);
  Serial.print("Accuracy = ");
  Serial.println(accuracy);
   ;
}