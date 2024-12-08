#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Blynk credentials
char auth[] = "YourBlynkAuthToken";  
char ssid[] = "YourWiFiSSID";        
char pass[] = "YourWiFiPassword";    

TinyGPSPlus gps;
HardwareSerial gpsSerial(1); 

const int buttonPin = 25;  

void setup() {

  Serial.begin(115200);
  
  
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  

  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
  
  // Configure button pin as input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  Blynk.run();
  
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
  
  if (digitalRead(buttonPin) == LOW) {
    sendLocationToBlynk();
    delay(1000); // debounce delay
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
  }
}
