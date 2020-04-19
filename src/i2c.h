#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <Arduino.h>

extern unsigned int I2CCount;

void I2Cinit(bool enablePullup);

int I2Cread();

bool I2Cwrite(uint8_t data);

bool I2Cstart(uint8_t address, uint8_t read);

bool I2Crestart (uint8_t address, uint8_t read);

void I2Cstop (uint8_t read);

#endif
