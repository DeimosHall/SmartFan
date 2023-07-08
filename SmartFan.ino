#include <OneWire.h>
#include <DallasTemperature.h>
#include <ezOutput.h>

#define FAN_PIN 28
#define TEMPERATURE_PIN 27

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature sensor(&oneWire);
ezOutput fan(FAN_PIN);

void setup() {
  Serial.begin(9600);
  sensor.begin();  // Start the DS18B20 sensor
  fan.low();
}

void loop() {
  static unsigned long elapsedTime = millis();

  if (millis() - elapsedTime > 1000) {
    elapsedTime = millis();
    Serial.println("Temperature: " + String(getTemperature(), 2) + "°C");
    Serial.println("Fan: " + String(fan.getState() ? "ON" : "OFF"));
  }  
}

float getTemperature() {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);
}
