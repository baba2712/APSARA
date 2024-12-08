#include <BlynkSimpleEsp32.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Blynk Auth Token, Wi-Fi credentials
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"
const char* ssid = "YourWiFiSSID"; // Your Wi-Fi SSID
const char* password = "YourWiFiPassword"; // Your Wi-Fi password

// GPS Setup
TinyGPSPlus gps;
HardwareSerial mySerial(1);  // Hardware serial port 1 (for GPS)
int gpsRxPin = 16;  // RX pin for GPS (change as needed)
int gpsTxPin = 17;  // TX pin for GPS (change as needed)

// Blynk Virtual Pins (used for latitude and longitude)
#define LATITUDE_PIN V1
#define LONGITUDE_PIN V2

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Start GPS communication
  mySerial.begin(9600, SERIAL_8N1, gpsRxPin, gpsTxPin);
  
  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  // Read GPS data
  while (mySerial.available() > 0) {
    gps.encode(mySerial.read());
    
    // When new GPS data is available, send it to Blynk
    if (gps.location.isUpdated()) {
      double latitude = gps.location.lat();  // Get latitude
      double longitude = gps.location.lng();  // Get longitude
      
      // Send latitude and longitude to Blynk using virtual pins
      Blynk.virtualWrite(LATITUDE_PIN, latitude);
      Blynk.virtualWrite(LONGITUDE_PIN, longitude);
    }
  }
  
  // Run Blynk (to keep connection alive and handle events)
  Blynk.run();
}

