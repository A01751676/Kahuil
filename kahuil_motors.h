#ifndef kahuil_motors
#define kahuil_motors

#include <DynamixelSDK.h>


#define PROTOCOL_VERSION                1.0
#define DEVICENAME                      "OpenCR_DXL_Port"
#define BAUDRATE                        1000000

class Kahuil_Motors{
    private:
        dynamixel::PortHandler *portHandler;
        dynamixel::PacketHandler *packetHandler;
        int dxlID[6] = {1,2,3,4,5,6};

    public:
        Kahuil_Motors();

        int startComunication();

        void torque(int enable);
        void setPos(int pos[6], int platTime);
        void setVel(int vel[6]);

        int radiansToBits(float degrees[6]);
        int speedToBits(float speed[6]);

        int stopComunication();
};

#endif