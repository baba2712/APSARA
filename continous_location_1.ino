#include <TinyGPS++.h>
#include <BlynkSimpleSIM800.h>
#include <SoftwareSerial.h>

// Blynk Auth Token
#define BLYNK_AUTH_TOKEN "Your_Blynk_Auth_Token"

// Define APN credentials for your SIM card (ask your carrier for these details)
#define GPRS_APN "your_apn"     
#define GPRS_USER ""            
#define GPRS_PASS ""            

// Initialize Blynk and GPS
SoftwareSerial sim800l(3, 1); 
TinyGPSPlus gps;

#define RX2 16
#define TX2 17
HardwareSerial gpsSerial(2); 

void setup() {
  
  Serial.begin(115200);

  gpsSerial.begin(9600, SERIAL_8N1, RX2, TX2);

  sim800l.begin(9600);

  Blynk.begin(sim800l, BLYNK_AUTH_TOKEN, GPRS_APN, GPRS_USER, GPRS_PASS);

  Serial.println("Setup completed. Waiting for GPS data...");
}

void loop() {
  Blynk.run();

  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated()) {
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();

      Serial.print("Latitude: ");
      Serial.println(latitude);
      Serial.print("Longitude: ");
      Serial.println(longitude);

      Blynk.virtualWrite(V1, latitude); 
      Blynk.virtualWrite(V2, longitude);
    }
  }
}
