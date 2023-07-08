#include <OneWire.h>
#include <DallasTemperature.h>

#define FAN_PIN 28
#define TEMPERATURE_PIN 27

bool fanState = false;

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature sensor(&oneWire);

void setup() {
  Serial.begin(9600);

  sensor.begin();  // Start the DS18B20 sensor
}

void loop() {
  Serial.println("Temperature: " + String(getTemperature(), 2) + "°C");
  delay(1000);
}

float getTemperature() {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);
}

void fanOn() {
  digitalWrite(FAN_PIN, HIGH);
  fanState = true;
}

void fanOff() {
  digitalWrite(FAN_PIN, LOW);
  fanState = false;
}
