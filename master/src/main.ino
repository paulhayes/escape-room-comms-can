#include <Arduino.h>
#include <stdlib.h>
#include <CmdParser.hpp>
#include <CmdCallback.hpp>
#include "erc-master.h"

CmdCallback<3> cmdCallback;

char strCommand[] = "CMD";
char strStatusR[] = "STATUS";
ERCMaster master;

void setup() {
  Serial.begin(9600);

  cmdCallback.addCmd(strCommand, &functCommand);
  cmdCallback.addCmd(strStatusR, &functStatusR);

  while (!Serial);

  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!master.begin()) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {

  CmdBuffer<32> myBuffer;
  CmdParser     myParser;

  cmdCallback.loopCmdProcessing(&myParser, &myBuffer, &Serial);
}

void functCommand(CmdParser *myParser){
  Serial.println("CMD Got");
  char *strCommandId = myParser->getCmdParam(1);
  int id = strtol(strCommandId,NULL,16);
  master.sendMessage(id,myParser->getCmdParam(2));
}

void functStatusR(CmdParser *myParser){
  Serial.println("STATUS Got");
  char *strStatusId = myParser->getCmdParam(1);
  int id = strtol(strStatusId,NULL,16);
  master.sendMessage(id,"");
}

/*
void loop() {
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  }
}*/