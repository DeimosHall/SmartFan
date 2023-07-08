#include <DallasTemperature.h>
#include <OneWire.h>
#include <ezButton.h>
#include <ezOutput.h>

#define FAN_PIN 28
#define TEMPERATURE_PIN 27
#define IR_SENSOR_PIN 26

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature sensor(&oneWire);
ezOutput fan(FAN_PIN);
ezButton btnIRSensor(IR_SENSOR_PIN);

// Temperature consts to turn the fan on/off
const float TEMPERATURE_ON = 29.0;
const float TEMPERATURE_OFF = 28.0;

void setup() {
  Serial.begin(9600);
  sensor.begin();  // Start the DS18B20 sensor
  fan.low();
  pinMode(IR_SENSOR_PIN, INPUT_PULLDOWN);
  btnIRSensor.setDebounceTime(50);
}

void loop() {
  static unsigned long elapsedTime = millis();
  btnIRSensor.loop();
  unsigned long startTime = millis();
  float temperature = getTemperature();
  Serial.println("Time to get temperature: " + String(millis() - startTime) + "ms");

  if (millis() - elapsedTime > 1000) {
    elapsedTime = millis();
    Serial.println("Temperature: " + String(temperature, 2) + "°C");
    Serial.println("Fan: " + String(fan.getState() ? "ON" : "OFF"));
    if (digitalRead(IR_SENSOR_PIN) == LOW) {
      Serial.println("pressed");
    }

    if (digitalRead(IR_SENSOR_PIN) == HIGH) {
      Serial.println("released");
    }
  }

  temperatureListener(temperature);
}

void temperatureListener(float temperature) {
  if (temperature > TEMPERATURE_ON) {
    fan.high();
  } else if (temperature < TEMPERATURE_OFF) {
    fan.low();
  }
}

/// @brief Get the temperature from the DS18B20 sensor
/// @details This process takes around 519 ms
/// @return The temperature in Celsius
float getTemperature() {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);
}
