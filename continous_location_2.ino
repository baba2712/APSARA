#include <BlynkSimpleEsp32.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Blynk Auth Token
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

const char* ssid = "Your_WiFi_SSID"; 
const char* password = "Your_WiFi_Password"; 

TinyGPSPlus gps;
HardwareSerial mySerial(1);  
int gpsRxPin = 16; 
int gpsTxPin = 17;  

#define LATITUDE_PIN V1
#define LONGITUDE_PIN V2

void setup() {
  Serial.begin(115200);
  
  mySerial.begin(9600, SERIAL_8N1, gpsRxPin, gpsTxPin);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  while (mySerial.available() > 0) {
    gps.encode(mySerial.read());
    
    if (gps.location.isUpdated()) {
      double latitude = gps.location.lat();  
      double longitude = gps.location.lng();  
      
      Blynk.virtualWrite(LATITUDE_PIN, latitude);
      Blynk.virtualWrite(LONGITUDE_PIN, longitude);
    }
  }
  
  Blynk.run();
}
