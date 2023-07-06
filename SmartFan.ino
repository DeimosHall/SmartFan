#define FAN_PIN 33
#define FAN_DELAY 10000
#define LM35_PIN 35  // Temperature sensor

bool fanState = false;

// 12-bit conversion, assume max value == ADC_VREF == 3.3 V
const float CONVERSION_FACTOR = 3.3f / (1 << 12);

void setup() {
  // put your setup code here, to run once:
  adc_init();
  adc_set_temp_sensor_enabled(true);
  // Select ADC input 4 for internal temperature sensor
  adc_select_input(4);
}

void loop() {
  // put your main code here, to run repeatedly:

  uint16_t adc = adc_read();
  float ADC_Voltage = float(adc) * CONVERSION_FACTOR;
  float T = 27 - (ADC_Voltage - 0.706) / 0.001721;  // formula found on page 71 (section 4.1.1. hardware_adc) of the Raspberry Pi Pico C/C++ SDK documentation

  Serial.println("Raw value: 0x" + String(adc, HEX) + " | ADC voltage: " + String(ADC_Voltage, 2) + "V | Temp: " + String(T, 2) + "C");

  delay(1000);
}

float getTemperature() {
  float voltage = analogRead(LM35_PIN) * 3.3 / 4095;
  return voltage * 100;
}

void fanOn() {
  digitalWrite(FAN_PIN, HIGH);
  fanState = true;
}

void fanOff() {
  digitalWrite(FAN_PIN, LOW);
  fanState = false;
}
