#define FAN_PIN 33
#define FAN_DELAY 10000
#define LM35_PIN 35  // Temperature sensor

bool fanState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LM35_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
}

void loop() {
  float temperature = getTemperature();
  Serial.println("Temperature: " + String(temperature) + " C");

  if (temperature > 30) {
    fanOn();
  } else {
    fanOff();
  }

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
