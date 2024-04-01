#include "kahuil_motors.h"
#include <DynamixelSDK.h>

#define PROTOCOL_VERSION                1.0
#define DEVICENAME                      "OpenCR_DXL_Port"
#define BAUDRATE                        1000000

int dxl_comm_result = COMM_TX_FAIL;
uint8_t dxl_error = 0; 

Kahuil_Motors::Kahuil_Motors(){
    this->portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    this->packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
};

int Kahuil_Motors::startComunication(){
    int port = 0;
    int baud  = 0;

    // open port
    if (this->portHandler->openPort()) {port = 1;}
    else {return port, -1;}

    // change baudrate
    if (this->portHandler->setBaudRate(BAUDRATE)){baud = 1;}
    else { return port, baud;}

    return port, baud;
};

void Kahuil_Motors::torque(int enable){

    int torque_address = 24;
    for (int i = 0; i < 6; i++) {
        dxl_comm_result = packetHandler->write1ByteTxRx(this->portHandler, this->dxlID[i], torque_address, enable, &dxl_error);
    }
};

void Kahuil_Motors::setPos(int pos[6], int platTime){
    int position_address = 30;
    for (int i = 0; i < 6; i++) {
        dxl_comm_result = packetHandler->write2ByteTxRx(this->portHandler, this->dxlID[i], position_address, pos[i], &dxl_error);
    }
    delay(platTime);
};

void Kahuil_Motors::setVel(int vel[6]){
    int velocity_address = 32;
    for (int i = 0; i < 6; i++) {
        dxl_comm_result = packetHandler->write2ByteTxRx(this->portHandler, this->dxlID[i], velocity_address, vel[i], &dxl_error);
    }
};

int Kahuil_Motors::radiansToBits(float degrees[6]){
    // use datasheet to convert degrees to bits

    int bits[6] = {0,0,0,0,0,0};
    for (int i = 0; i < 6; i++) {

        if (i == 0){ // for ID 1
            // for MX28 (1 bit -> 0.088 grados)
            bits[i] = (degrees[i]/0.088);
        }

        if (i == 1 || i == 2){ // for ID 2 y 3
            // for MX64 (1 bit -> 0.088 grados)
            bits[i] = (degrees[i]/0.088) + 2048;
        }

        if (i == 3){ // for ID 4
            // for MX28 (1 bit -> 0.088 grados)
            bits[i] = (degrees[i]/0.088) + 1024;
        }

        if (i == 4 || i == 5){ // for ID 5 y 6
            // for AX12 (1 bit -> 0.088 grados)
            bits[i] = (degrees[i]/0.29) + 512;
        }
    }
    return bits[0], bits[1], bits[2], bits[3], bits[4], bits[5];
};

int Kahuil_Motors::speedToBits(float speed[6]){
    // use datasheet to convert degrees to bits
    
    int bits[6] = {0,0,0,0,0,0};
    for (int i = 0; i < 6; i++) {

        if (i == 0 || i == 1 || i == 2 || i == 3){ // for ID 1, 2, 3 y 4
            // for MX64 (1 bit -> 0.088 grados)
            bits[i] = (speed[i]/0.01193);
        }
        if (i == 4 || i == 5){ // for ID 5 y 6
            // for AX12 (1 bit -> 0.088 grados)
            bits[i] = (speed[i]/0.01162);
        }
    }
    return bits[0], bits[1], bits[2], bits[3], bits[4], bits[5];
};

int Kahuil_Motors::stopComunication(){
    torque(0);
    delay(500);
    this->portHandler->closePort();
}