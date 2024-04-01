#ifndef kahuil_motors
#define kahuil_motors

#include <DynamixelSDK.h>


#define PROTOCOL_VERSION                1.0
#define DEVICENAME                      "OpenCR_DXL_Port"
#define BAUDRATE                        57600

class Kahuil_Motors{
    private:
        dynamixel::PortHandler *portHandler;
        dynamixel::PacketHandler *packetHandler;
        int dxlID[5] = {1,2,3,4,5};

    public:
        Kahuil_Motors();

        int startComunication();

        void torque(int enable);
        void setPos(int pos[5], int platTime);
        void setVel(int vel[5]);

        int degreesToBits(float degrees[5]);
        int speedToBits(float speed[5]);

        int stopComunication();
};

#endif