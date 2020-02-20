#include "erc-master.h"
#include "erc-util.h"

ERCMaster::ERCMaster(){
  //ercMasterInstance = this;
}

bool ERCMaster::begin(){
  return CAN.begin(BAUD_SPEED);
  CAN.onReceive(ERCMaster::onReceive);
}

void ERCMaster::onReceive(int packetSize){
  int id = CAN.packetId();
  int messageType = getType(id);
  bool isMaster = isSenderMaster(id);
  if(isMaster){
    return;
  }

  //get sender id
  int slaveId = getSlaveId(id);
  
  //convert message into char array
  getMessage(ERCMaster::buffer);

  if(messageType==SLAVE_SENSOR){
    Serial.print("SENSOR:");
  }
  else if(messageType==SLAVE_STATUS_RES){
    Serial.print("STATUS:");
  }
}

void ERCMaster::sendMessage(int slaveId,const char *msg){
  CAN.beginPacket(slaveId);
  int i = 0;
  while(msg[i]!=0 && i<8){
    CAN.write(msg[i]);
    i++;
  }
  CAN.endPacket();
  
}