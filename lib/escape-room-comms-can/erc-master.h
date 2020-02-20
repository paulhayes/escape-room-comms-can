#define MASTER_COMMAND 0b00
#define MASTER_STATUS_REQ 0b01
#define SLAVE_SENSOR 0b10
#define SLAVE_STATUS_RES 0b11
#define BAUD_SPEED 500E3

#define TYPE_BITS 10

#include <CAN.h>

class ERCMaster {
  static ERCMaster *instance;

  public:
  ERCMaster();
  bool begin();

  private:
  static void onReceive(int packetSize);
};


  

