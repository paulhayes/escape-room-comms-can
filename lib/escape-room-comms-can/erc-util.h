#pragma once

#include <CAN.h>

int getSlaveId(int message){
  return (message>>4) & 0b111111;
}

void getMessage(char buffer[]){
  int index = 0;
  while( CAN.available() ){
    buffer[index] = CAN.read();
    index++;
  }
}