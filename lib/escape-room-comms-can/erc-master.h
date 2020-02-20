#ifndef ERCMASTER_H
#define ERCMASTER_H

#define MASTER_COMMAND 0b00
#define MASTER_STATUS_REQ 0b01
#define SLAVE_SENSOR 0b10
#define SLAVE_STATUS_RES 0b11
#define BAUD_SPEED 500E3

#include <CAN.h>

class ERCMaster {

  public:
  
  ERCMaster();
  bool begin();
  void registerStatusCallback(void(*callback)(int));
  void registerSensorCallback(void(*callback)(int));
  void sendMessage(int slaveId,const char *msg);

  private:
  static void onReceive(int packetSize);
  static char buffer[9];
};

//ERCMaster *ercMasterInstance;

#endif
  

