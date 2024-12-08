#include <TinyGPS++.h>
#include <BlynkSimpleSIM800.h>
#include <SoftwareSerial.h>

// GPS module connection
TinyGPSPlus gps;
HardwareSerial mySerial(1);  // Using HardwareSerial 1 for SIM800L

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

// Blynk authentication token
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";  

void setup() {
  Serial.begin(115200);  
  mySerial.begin(9600, SERIAL_8N1, 4, 5); 

  Serial.println("Starting GPS and Blynk setup");

  Serial1.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN); 
  
  Blynk.begin(auth, mySerial, "APN_NAME", "APN_USERNAME", "APN_PASSWORD"); 
}

void loop() {
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());  

    if (gps.location.isUpdated()) {
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();
      Serial.print("Latitude= "); 
      Serial.print(latitude, 6);  
      Serial.print(" Longitude= "); 
      Serial.println(longitude, 6);

      Blynk.virtualWrite(V1, latitude);  
      Blynk.virtualWrite(V2, longitude);
    }
  }

  Blynk.run();  
}
