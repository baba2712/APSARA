#include <TinyGPS++.h>
#include <HardwareSerial.h>

// GPS and SIM800L connections
TinyGPSPlus gps;
HardwareSerial mySerial(1);  

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

void setup() {
  Serial.begin(115200);  
  mySerial.begin(9600, SERIAL_8N1, 4, 5);  

  Serial.println("Starting GPS and SIM800L setup");

  Serial.println("Initializing GPS...");
  Serial1.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN); 
  
  sendCommand("AT", 2000); 
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

      String message = "Current Location: https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
      sendSMS("+1234567890", message);  // Replace with your phone number
    }
  }
}

void sendCommand(String command, const int timeout) {
  String response = "";
  mySerial.println(command);  // Send the command to SIM800L
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (mySerial.available()) {
      char c = mySerial.read();
      response += c;
    }
  }
  Serial.print(response);  
}

void sendSMS(String phoneNumber, String message) {
  sendCommand("AT+CMGF=1", 2000);
  String command = "AT+CMGS=\"" + phoneNumber + "\"";  
  sendCommand(command, 2000);  
  sendCommand(message, 2000); 
  mySerial.write(26);  
}
