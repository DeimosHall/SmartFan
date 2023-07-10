#include <DallasTemperature.h>
#include <OneWire.h>
#include <ezButton.h>
#include <ezOutput.h>

#define DEBOUNCE_TIME_MS 50
#define FAN_PIN 28
#define TEMPERATURE_SENSOR_PIN 27
#define MANUAL_MODE_BUTTON 26
#define AUTOMATIC_MODE_BUTTON_PIN 16
#define AUTOMATIC_MODE_LED_PIN 17

OneWire oneWire(TEMPERATURE_SENSOR_PIN);
DallasTemperature sensor(&oneWire);
ezOutput fan(FAN_PIN);
ezOutput automaticMode(AUTOMATIC_MODE_LED_PIN);
ezButton btnManualMode(MANUAL_MODE_BUTTON);
ezButton btnAutomaticMode(AUTOMATIC_MODE_BUTTON_PIN);

// Temperature consts to turn the fan on/off
const float TEMPERATURE_ON = 28.0;
const float TEMPERATURE_OFF = 27.5;

void setup() {
  Serial.begin(9600);
  sensor.begin();  // Start the DS18B20 sensor
  pinMode(MANUAL_MODE_BUTTON, INPUT_PULLUP);
  pinMode(AUTOMATIC_MODE_BUTTON_PIN, INPUT_PULLUP);

  fan.low();
  automaticMode.high();
  btnManualMode.setDebounceTime(DEBOUNCE_TIME_MS);
  btnAutomaticMode.setDebounceTime(DEBOUNCE_TIME_MS);
}

void loop() {
  static unsigned long elapsedTime = millis();
  static unsigned long elapsedTime2 = millis();
  btnManualMode.loop();
  btnAutomaticMode.loop();
  static float temperature = getTemperature();

  if (millis() - elapsedTime > 1000) {
    elapsedTime = millis();
    printDebugInfo(temperature);
  }

  if (millis() - elapsedTime2 > 10000) {
    elapsedTime2 = millis();
    temperature = getTemperature();
  }

  if (btnAutomaticMode.isPressed()) {
    automaticMode.toggle();
  }

  manualModeListener();
  temperatureListener(temperature);
}

void manualModeListener() {
  if (automaticMode.getState()) {  // Values are inverted
    return;
  }

  if (btnManualMode.isPressed()) {
    fan.toggle();
  }
}

void temperatureListener(float temperature) {
  if (!automaticMode.getState()) {
    return;
  }

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

void printDebugInfo(float temperature) {
  Serial.println("Temperature: " + String(temperature, 2) + "°C");
  Serial.println("Fan: " + String(fan.getState() ? "ON" : "OFF"));
  Serial.println("Automatic mode: " + String(automaticMode.getState() ? "ON" : "OFF"));
}
