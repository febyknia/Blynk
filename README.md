
>👩🏻‍💻Feby 🗓 18 March 2025

# CONNECT TEMPERATURE AND HUMIDITY ON BLYNK BASED ON ESP32 MICROCONTROLLER 
---
## **A. Introduction**

This project is a temperature check activity using Wokwi based on ESP32 Microcontroller, Visual Studio Code C++ programming language, and Blynk. The output of this simulation is display temperature and humidity.

## **B. Diagram**
This diagram was created using the ESP32 Microcontroller based Wokwi simulation.
<img width="1020" alt="12" src="https://github.com/user-attachments/assets/e8f9e29b-a189-448f-82d6-536ca87975f4" />






```json
{
  "version": 1,
  "author": "Anonymous maker",
  "editor": "wokwi",
  "parts": [
    { "type": "wokwi-esp32-devkit-v1", "id": "esp", "top": -278.9, "left": 52.76, "attrs": {} },
    { "type": "wokwi-led", "id": "led1", "top": -262.8, "left": 3.8, "attrs": { "color": "red" } },
    {
      "type": "wokwi-resistor",
      "id": "r5",
      "top": -196.8,
      "left": -0.55,
      "rotate": 90,
      "attrs": { "value": "1000" }
    },
    {
      "type": "wokwi-dht22",
      "id": "dht1",
      "top": -258.9,
      "left": 177,
      "attrs": { "temperature": "58.7", "humidity": "77" }
    }
  ],
  "connections": [
    [ "esp:TX0", "$serialMonitor:RX", "", [] ],
    [ "esp:RX0", "$serialMonitor:TX", "", [] ],
    [ "led1:A", "r5:1", "red", [ "v0" ] ],
    [ "led1:C", "esp:GND.2", "black", [ "v0" ] ],
    [ "esp:D15", "dht1:SDA", "black", [ "h0" ] ],
    [ "esp:GND.1", "dht1:GND", "black", [ "h0" ] ],
    [ "esp:D13", "r5:2", "black", [ "h0" ] ],
    [
      "dht1:VCC",
      "esp:VIN",
      "black",
      [
        "v0",
        "h-28.8",
        "v-134.4",
        "h-115.2",
        "v134.4",
        "h-9.6",
        "v0",
        "h0",
        "v-115.2",
        "h-28.8",
        "v134.4",
        "h0",
        "v9.6"
      ]
    ]
  ],
  "dependencies": {}
}
```

## **C. Program Code**
This program code is for setting the temperature and humidity, as well as the connection to Blynk.

```cpp
#define BLYNK_PRINT Serial

#define DHT_PIN 15 
#define LED_PIN 13 

#define BLYNK_AUTH_TOKEN "c-ek_3kRGcQWdf1CPoGC3l5PmYD9LMZ6"
#define BLYNK_TEMPLATE_ID "TMPL6n36jrzSi"
#define BLYNK_TEMPLATE_NAME "Feby"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST"; 
char pass[] = ""; 

DHTesp dht;
BlynkTimer timer;

void sendSensor() {
  float temperature = dht.getTemperature();
  float humidity = dht.getHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Gagal membaca data DHT22!");
    return;
  }

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);

  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.print("°C  -  Kelembaban: ");
  Serial.print(humidity);
  Serial.println("%");
}

BLYNK_WRITE(V2) {
  int ledState = param.asInt(); 
  digitalWrite(LED_PIN, ledState);
  Serial.println(ledState ? "LED ON" : "LED OFF");
}

void setup() {
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass);
  dht.setup(DHT_PIN, DHTesp::DHT22);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  timer.setInterval(2000L, sendSensor); 
}

void loop() {
  Blynk.run();
  timer.run();
}
```
## **C. Result**
Temperature and humidity successfully connect with blynk and run according to the commands made, DHT22 on temperature and humidity can also be edited, then on the blynk device will change to online and display Temperature and Humidity. 
<img width="1020" alt="7" src="https://github.com/user-attachments/assets/f77e2bbb-d9f7-4154-9bf4-1183c63f352b" />

<img width="1020" alt="9" src="https://github.com/user-attachments/assets/b097be45-2224-46d3-bb81-ae4feea44752" />

<img width="1020" alt="12" src="https://github.com/user-attachments/assets/2f72c430-3e1f-41ad-8547-97b527bbfe9b" />

For more details, please follow the implementation steps in the blynk check report (pdf).
