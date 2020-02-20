#ifndef ERCUTIL_H
#define ERCUTIL_H

#pragma once

#include <CAN.h>

#define TYPE_BITS 10

int getSlaveId(int id){
  return (id>>4) & 0b111111;
};

int getType(int id){
  return id>>TYPE_BITS;
};

void getMessage(char buffer[]){
  int index = 0;
  while( CAN.available() ){
    buffer[index] = CAN.read();
    index++;
  }
};

bool isSenderMaster(int id){
  return (getType(id) & 0b10)!=0; //This checks if the signal is from the master. 
};

#endif