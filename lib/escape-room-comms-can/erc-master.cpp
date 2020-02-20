#include "erc-master.h"
#include "erc-util.h"

ERCMaster::ERCMaster(){
  //ERCMaster::instance = this;
}

bool ERCMaster::begin(){
  return CAN.begin(BAUD_SPEED);
  CAN.onReceive(ERCMaster::onReceive);
}

void onReceive(int packetSize){
  int id = CAN.packetId();
  int messageType = id>>TYPE_BITS;
  bool isMaster = (messageType & 0b10)!=0; //This checks if the signal is from the master. 
  if(isMaster){
    return;
  }

  //get sender id
  int slaveId = getSlaveId(id);
  
  //convert message into char array


  if(messageType==SLAVE_SENSOR){
    Serial.print("SENSOR:");
  }
  else if(messageType==SLAVE_STATUS_RES){
    Serial.print("STATUS:");
  }
}