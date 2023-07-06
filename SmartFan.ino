#include <CPU.h>

#define FAN_PIN 33
#define FAN_DELAY 10000

CPU cpu;
bool fanState = false;

void setup() {
  cpu.begin();
}

void loop() {
  Serial.println("Temperature: " + String(cpu.getTemperature(), 2) + "°C");
  delay(1000);
}

void fanOn() {
  digitalWrite(FAN_PIN, HIGH);
  fanState = true;
}

void fanOff() {
  digitalWrite(FAN_PIN, LOW);
  fanState = false;
}
