#  **Connections for ESP32 WROVER-E + Neo-6M GPS Module**

---

## **1️⃣ Connections for Real Physical Button**
| **Component**        | **ESP32 Pin**  | **Description**                 |
|---------------------|----------------|-----------------------------------|
| **Neo-6M VCC**       | **3.3V**       | Power for GPS                    |
| **Neo-6M GND**       | **GND**        | Ground for GPS                   |
| **Neo-6M TX**        | **GPIO 16 (RX1)** | Data from GPS to ESP32 (RX)    |
| **Neo-6M RX**        | **GPIO 17 (TX1)** | Data from ESP32 to GPS (TX)    |
| **Button (1 leg)**   | **GND**         | One leg to ground (GND)          |
| **Button (2nd leg)** | **GPIO 25**     | Other leg to GPIO 25 (input)     |

---

## **2️⃣ Connections for Virtual Button (Blynk)**
| **Component**        | **ESP32 Pin**  | **Description**                 |
|---------------------|----------------|-----------------------------------|
| **Neo-6M VCC**       | **3.3V**       | Power for GPS                    |
| **Neo-6M GND**       | **GND**        | Ground for GPS                   |
| **Neo-6M TX**        | **GPIO 16 (RX1)** | Data from GPS to ESP32 (RX)    |
| **Neo-6M RX**        | **GPIO 17 (TX1)** | Data from ESP32 to GPS (TX)    |


