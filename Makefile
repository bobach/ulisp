

ALTERNATE_CORE 		= MightyCore
BOARD_TAG 		= 1284
MCU 			= atmega1284p
F_CPU			= 20000000L
VARIANT			= standard 
ARDUINO_LIB_PATH= /usr/share/arduino/hardware/MightyCore/avr/libraries/
AVRDUDE_ARD_BAUDRATE 	= 115200 
AVRDUDE_ARD_PROGRAMMER	= arduino
ARDUINO_LIBS = Wire SD EEPROM SPI 

MONITOR_BAUDRATE = 230400

# This variable is local, name it however you want
SOURCE_FOLDERS = src src/ulisp

# These two are used by Arduino.mk
LOCAL_C_SRCS = $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.c))
LOCAL_CPP_SRCS = $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.cpp))

#mk
include /usr/share/arduino/Arduino.mk
