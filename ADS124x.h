/*
 * Copyright (c) 2013 by Barnaby Shearer <b@zi.is>
 * ADS124x library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _ADS124X_H_INCLUDED
#define _ADS124X_H_INCLUDED

#include <SPI.h>

//Register addresses
#define REG_MUX0     0x00
#define REG_MUX1     0x02
#define REG_SYS0     0x03
#define REG_IDAC0    0x0A
#define REG_IDAC1    0x0B

//Register Values
#define VREFCON_AUTO 0b01000000 //Turn int ref on and off out of sleep mode
#define PGA_16       0b01000000 //x16
#define IMAG_50      0b00000001 //50 micro amps
#define IMAG_100     0b00000010 //50 micro amps
#define I1DIR_AIN1   0b00010000 //Connect current source to Ain1
#define I2DIR_NONE   0b00001111 //Dissconnect 2nd current source
#define SP_AIN1      0b00001000 //Connect Ain1 to positive sample
#define SN_AIN0      0b00000000 //Connect Ain0 to negative sample

//Commands
#define CMD_SLEEP    0b00000010
#define CMD_RESET    0b00000110
#define CMD_NOP      0b11111111
#define CMD_READ     0b00010010
#define CMD_SDATAC   0b00010110 //Stop autoconversion
#define CMD_RREG     0b00100000 //Read Register
#define CMD_WREG     0b01000000 //Write Register

class ADS124XClass {
public:
  void begin(uint8_t chipselect, uint8_t clockdevider);
  void select();
  void deselect();
  void reset();
  void stop_auto();
  void writeRegister(uint8_t reg, uint8_t value);
  void sleep();
  long read();
private:
  uint8_t cs;
};

extern ADS124XClass ADS124X;

#endif
