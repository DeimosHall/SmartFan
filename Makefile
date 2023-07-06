BOARD_TAG = esp32:esp32:esp32
# MONITOR_PORT = /dev/ttyACM0
MONITOR_PORT = /dev/cu.wchusbserial550D0100521
USER_NAME := $(shell whoami)
# ARDUINO_CLI_PATH := /home/$(USER_NAME)/arduino-cli/arduino-cli
ARDUINO_CLI_PATH := arduino-cli

compile:
	$(ARDUINO_CLI_PATH) compile --fqbn esp32:esp32:esp32

upload:
	$(ARDUINO_CLI_PATH) upload -p $(MONITOR_PORT) --fqbn $(BOARD_TAG)

monitor:
	$(ARDUINO_CLI_PATH) monitor -p $(MONITOR_PORT)

clean:
	$(ARDUINO_CLI_PATH) cache clean

all: compile upload