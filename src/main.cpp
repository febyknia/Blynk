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