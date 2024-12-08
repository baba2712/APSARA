If the GPS data is not updating, check the Serial Monitor for debugging. print the GPS data to the Serial Monitor (Serial.print(latitude) and Serial.print(longitude)) to see if it's being read correctly.

- #**connections** : 

 - **GPS TX Pin** (Neo-6M) -> **RX Pin** (GPIO16) on ESP32
- **GPS RX Pin** (Neo-6M) -> **TX Pin** (GPIO17) on ESP32
- **GPS VCC Pin** (Neo-6M) -> **5V Pin** (on ESP32)
- **GPS GND Pin** (Neo-6M) -> **GND Pin** (on ESP32)
