#include "kahuil_motors.h"
#include <DynamixelSDK.h>

#define PROTOCOL_VERSION                1.0
#define DEVICENAME                      "OpenCR_DXL_Port"
#define BAUDRATE                        57600

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

    int torque_address = 36;
    for (int i = 0; i < 5; i++) {
        dxl_comm_result = packetHandler->write1ByteTxRx(this->portHandler, this->dxlID[i], torque_address, enable, &dxl_error);
    }
};

void Kahuil_Motors::setPos(int pos[5], int platTime){
    int position_address = 36;
    for (int i = 0; i < 5; i++) {
        dxl_comm_result = packetHandler->write2ByteTxRx(this->portHandler, this->dxlID[i], position_address, pos[i], &dxl_error);
    }
    delay(platTime);
};

void Kahuil_Motors::setVel(int vel[5]){
    int velocity_address = 36;
    for (int i = 0; i < 5; i++) {
        dxl_comm_result = packetHandler->write2ByteTxRx(this->portHandler, this->dxlID[i], velocity_address, vel[i], &dxl_error);
    }
};

int Kahuil_Motors::degreesToBits(float degrees[5]){
    // use datasheet to convert degrees to bits
    return 0, 0, 0, 0, 0;
};

int Kahuil_Motors::speedToBits(float speed[5]){
    // use datasheet to convert degrees to bits
    return 0, 0, 0, 0, 0;
};

int Kahuil_Motors::stopComunication(){
    torque(0);
    delay(500);
    this->portHandler->closePort();
}