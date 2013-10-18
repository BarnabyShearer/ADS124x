/*
 * Copyright (c) 2013 by Barnaby Shearer <b@zi.is>
 * ADS124x library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "ADS124x.h"

ADS124XClass ADS124X;

struct {signed long value:24;} int24;

void ADS124XClass::begin(uint8_t chipselect, uint8_t clockdevider) {
  cs = chipselect;
  pinMode(cs, OUTPUT);
  deselect();
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE1);
  SPI.setClockDivider(clockdevider);
}
void ADS124XClass::select() {
  deselect(); //wake-up if we are asleep
  delay(10);
  digitalWrite(cs, LOW);
}

void ADS124XClass::deselect() {
  digitalWrite(cs, HIGH);
}
void ADS124XClass::reset() {
    select();
    SPI.transfer(CMD_RESET);
    delay(1);
    deselect();
}

void ADS124XClass::stop_auto() {
  select();
  SPI.transfer(CMD_SDATAC);
  SPI.transfer(CMD_NOP);
  deselect();
}

void ADS124XClass::writeRegister(byte reg, byte value) {
  select();
  SPI.transfer(CMD_WREG | (reg & 0b00001111));
  SPI.transfer(0); //Write to 1 register
  SPI.transfer(value);
  deselect();
}

void ADS124XClass::sleep() {
  select();
  SPI.transfer(CMD_SLEEP);
  //HACK:keep selected or it wakes up
}

long ADS124XClass::read() {
  select();
  SPI.transfer(CMD_READ);
  return int24.value = ((unsigned long)SPI.transfer(CMD_NOP) << 16) |
    ((unsigned long)SPI.transfer(CMD_NOP) << 8) |
    SPI.transfer(CMD_NOP);
}
