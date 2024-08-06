#include <SPI.h>
#include <mcp2515.h>

struct can_frame read_can_msg;
struct can_frame write_can_msg;


MCP2515 mcp2515(5);


void setup() {
  Serial.begin(115200);


  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
}

void loop() {
  if (mcp2515.readMessage(&read_can_msg) == MCP2515::ERROR_OK) {
    int potent_rpm = analogRead(36) / 40;
     int potent_speed = analogRead(39) / 40;
    unsigned char p_id = read_can_msg.data[2];

    Serial.print(read_can_msg.can_id, HEX); // print ID
    Serial.print(" ");
    Serial.print(read_can_msg.can_dlc, HEX); // print DLC
    Serial.print(" ");


    for (int i = 0; i < read_can_msg.can_dlc; i++)  { // print the data
      Serial.print(read_can_msg.data[i], HEX);
      Serial.print(" ");
    }

    Serial.println();




    switch (p_id)
    {
      case 0:
        write_can_msg.can_id  = 0x7e8;
        write_can_msg.can_dlc = 0x08;
        write_can_msg.data[0] = 0x06;
        write_can_msg.data[1] = 0x041;
        write_can_msg.data[2] = 0x00;
        write_can_msg.data[3] = 0xFF;
        write_can_msg.data[4] = 0xFF;
        write_can_msg.data[5] = 0xFF;
        write_can_msg.data[6] = 0xFF;
        write_can_msg.data[7] = 170;
        Serial.println("aqui 1");
        mcp2515.sendMessage(&write_can_msg);
        break;

      case 12:
        write_can_msg.can_id  = 0x7e8;
        write_can_msg.can_dlc = 0x08;
        write_can_msg.data[0] = 0x04;
        write_can_msg.data[1] = 0x41;
        write_can_msg.data[2] = 0x0C;
        write_can_msg.data[3] = potent_rpm;
        write_can_msg.data[4] = 0x00;
        write_can_msg.data[5] = 0xAA;
        write_can_msg.data[6] = 0xAA;
        write_can_msg.data[7] = 0xAA;
        Serial.println("aqui 2");
        mcp2515.sendMessage(&write_can_msg);
        break;


      case 13:
        write_can_msg.can_id  = 0x7e8;
        write_can_msg.can_dlc = 0x08;
        write_can_msg.data[0] = 0x04;
        write_can_msg.data[1] = 0x41;
        write_can_msg.data[2] = 0x0D;
        write_can_msg.data[3] = potent_speed;
        write_can_msg.data[4] = 0x00;
        write_can_msg.data[5] = 0xAA;
        write_can_msg.data[6] = 0xAA;
        write_can_msg.data[7] = 0xAA;
        Serial.println("aqui 3");
        mcp2515.sendMessage(&write_can_msg);
        break;


      default:
        break;
    }
  }

}
