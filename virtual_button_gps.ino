// Include required libraries
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "YourBlynkAuthToken";  
char ssid[] = "YourWiFiSSID";        
char pass[] = "YourWiFiPassword";    

TinyGPSPlus gps;
HardwareSerial gpsSerial(1); // Use UART1

void setup() {
  Serial.begin(115200);
  
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Run Blynk
  Blynk.run();
  
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
}

BLYNK_WRITE(V0) {
  int buttonState = param.asInt();
  if (buttonState == 1) { 
    sendLocationToBlynk();
  }
}

void sendLocationToBlynk() {
  if (gps.location.isValid()) {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();
    String location = "Lat: " + String(latitude, 6) + ", Lng: " + String(longitude, 6);
    
    Serial.println(location);
    
    Blynk.virtualWrite(V1, location); 
  } else {
    Serial.println("Waiting for GPS signal...");
    Blynk.virtualWrite(V1, "Waiting for GPS signal...");
  }
}
