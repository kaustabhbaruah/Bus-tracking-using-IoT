# Bus-tracking-using-IoT


This is a program for an ESP8266 microcontroller that scans nearby WiFi networks and sends the information to Google's Geolocation API to get an estimate of the device's location. The program uses the Blynk library to communicate with the Blynk server and the WiFi library to connect to nearby networks. It also uses the ArduinoJson library to create and parse JSON data and the BearSSL library for secure communication.

The program begins by setting up the serial communication and connecting to the WiFi network. Then, it initializes the Blynk server and the WidgetMap object to be used to display the location on the Blynk app.

In the loop function, the program scans nearby WiFi networks and stores the network information in a JSON format string. The JSON string includes the country code, network type, carrier, and signal strength of each network.

The program then connects to Google's Geolocation API using the WiFiClientSecure object and sends the JSON data in a POST request to the API. The API responds with an estimate of the device's location, which is then parsed and displayed on the Blynk app using the WidgetMap object.

As the ESP8266 is connected to bus driver's device through wifi, it will provide the location of the bus in the blynk app.

Overall, this program demonstrates how to use the ESP8266 microcontroller to scan nearby WiFi networks and estimate the device's location using an external API.
