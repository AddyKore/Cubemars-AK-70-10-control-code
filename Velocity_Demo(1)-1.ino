//Cubemarse motor trial
#include <SPI.h>
#include "mcp2515_can.h"
 
/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif
 
const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
 
void setup() {
   SERIAL.begin(115200);
   while(!Serial){};
   while (CAN_OK != CAN.begin(CAN_1000KBPS)) 
   {             // init can bus : baudrate = 1000k
        SERIAL.println("CAN BUS Shield init fail");
        SERIAL.println(" Init CAN BUS Shield again");
        delay(100);
    }
    SERIAL.println("CAN BUS Shield init ok!");
    
}
 
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char len;
unsigned char buf[8];
unsigned char temp=0;

void loop() 
{
     // 发送数据:id = 0x01，标准帧，数据长度 = 8, stmp:数据  
    Enter_Mode();
    Cw();
    delay(5000);
    Ccw();
    delay(5000);
    Cmd_init();        
    Exit_Mode();
   
}

void Enter_Mode()
{
      stmp[0] = 0xFF;
      stmp[1] = 0xFF;
      stmp[2] = 0xFF;
      stmp[3] = 0xFF;
      stmp[4] = 0xFF;
      stmp[5] = 0xFF;
      stmp[6] = 0xFF;
      stmp[7] = 0xFC;
      CAN.sendMsgBuf(0x01, 0, 8, stmp);
      delay(1000); //延时1S  
}

void Cw()
{
      stmp[0] = 0x7F;
      stmp[1] = 0xFF;
      stmp[2] = 0xF4;
      stmp[3] = 0x40;
      stmp[4] = 0x00;
      stmp[5] = 0x33;
      stmp[6] = 0x37;
      stmp[7] = 0xFF;
      CAN.sendMsgBuf(0x01, 0, 8, stmp);
      delay(1000); //延时1S  
}

void Ccw()
{
      stmp[0] = 0x7F;
      stmp[1] = 0xFF;
      stmp[2] = 0x0B;
      stmp[3] = 0x90;
      stmp[4] = 0x00;
      stmp[5] = 0x33;
      stmp[6] = 0x37;
      stmp[7] = 0xFF;
      CAN.sendMsgBuf(0x01, 0, 8, stmp);
      delay(1000); //延时1S  
}

void Exit_Mode()
{
      stmp[0] = 0xFF;
      stmp[1] = 0xFF;
      stmp[2] = 0xFF;
      stmp[3] = 0xFF;
      stmp[4] = 0xFF;
      stmp[5] = 0xFF;
      stmp[6] = 0xFF;
      stmp[7] = 0xFD;
      CAN.sendMsgBuf(0x01, 0, 8, stmp);
      delay(1000); //延时1S  
}

void Cmd_init()
{
      stmp[0] = 0x7F;
      stmp[1] = 0xFF;
      stmp[2] = 0x7F;
      stmp[3] = 0xF0;
      stmp[4] = 0x00;
      stmp[5] = 0x00;
      stmp[6] = 0x07;
      stmp[7] = 0xFF;
      CAN.sendMsgBuf(0x01, 0, 8, stmp);
      delay(1000); //延时1S  
}
