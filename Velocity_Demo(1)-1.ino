//Cubemarse motor trial
#include <SPI.h>                                                //importing communication library
#include "mcp2515_can.h"
 
/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE                          // checking for communication availability
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif
 
const int SPI_CS_PIN = 9;                                       
mcp2515_can CAN(SPI_CS_PIN);                                    // Set CS pin
 
void setup() 
{
   SERIAL.begin(115200);                                        // Set baudrate
   while(!Serial){};
   while (CAN_OK != CAN.begin(CAN_1000KBPS))                    // init can bus : baudrate = 1000k
   {            
        SERIAL.println("CAN BUS Shield init fail");
        SERIAL.println("Init CAN BUS Shield again");
        delay(100);
    }
    SERIAL.println("CAN BUS Shield init ok!");
    
}
 
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};              //Communication bit array
unsigned char len;
unsigned char buf[8];
unsigned char temp=0;

void loop() 
{
    // Address:id = 0x01，Standard Frame，frame length = 8, stmp:data
    Enter_Mode();                                              //Calling Enter_mode() function
    Cw();                                                      //Calling Cw() function
    delay(5000);
    Ccw();                                                    //Calling Ccw() function
    delay(5000);
    Cmd_init();        
    Exit_Mode();                                              //Calling Exit_mode() function
   
}

void Enter_Mode()                                            // Enter_mode() used to enter run mode   
{
      stmp[0] = 0xFF;                                        // specific HEX instructions to Initialize
      stmp[1] = 0xFF;
      stmp[2] = 0xFF;
      stmp[3] = 0xFF;
      stmp[4] = 0xFF;
      stmp[5] = 0xFF;
      stmp[6] = 0xFF;
      stmp[7] = 0xFC;
      CAN.sendMsgBuf(0x01, 0, 8, stmp);                    // Sending data to 0x01 register address( actuator data bit)
      delay(1000);
}

void Cw()                                                 // Cw() is used to rotate motor at moderate speed in clockwise direction
{
      stmp[0] = 0x7F;                                     // specific HEX instructions to rotate in Clockwise direction
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

void Ccw()                                                 // Cw() is used to rotate motor at moderate speed in counter clockwise direction
{
      stmp[0] = 0x7F;                                      // specific HEX instructions to rotate in Counter Clockwise direction
      stmp[1] = 0xFF;
      stmp[2] = 0x0B;
      stmp[3] = 0x90;
      stmp[4] = 0x00;
      stmp[5] = 0x33;
      stmp[6] = 0x37;
      stmp[7] = 0xFF;
      CAN.sendMsgBuf(0x01, 0, 8, stmp);                   // Sending data to 0x01 register address( actuator data bit)
      delay(1000); 
}

void Exit_Mode()                                         // Exit_mode() used to exit run mode   
{
      stmp[0] = 0xFF;                                    // specific HEX instructions to exit run mode
      stmp[1] = 0xFF;
      stmp[2] = 0xFF;
      stmp[3] = 0xFF;
      stmp[4] = 0xFF;
      stmp[5] = 0xFF;
      stmp[6] = 0xFF;
      stmp[7] = 0xFD;
      CAN.sendMsgBuf(0x01, 0, 8, stmp);                 // Sending data to 0x01 register address( actuator data bit)
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
      CAN.sendMsgBuf(0x01, 0, 8, stmp);                 // Sending data to 0x01 register address( actuator data bit)
      delay(1000); //延时1S  
}
