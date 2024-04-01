#ifndef kahuil_h
#define kahuil_h

#include <stdlib.h>
#include "math.h"

class Kahuil
{
    private:
        float l1; float l2; float l3; float l4;
        float posX; float posY; float posZ;
        float q1; float q2; float q3; float q4; float q5;
        float beta;
    
    public:
        Kahuil();
        Kahuil(float l1, float l2, float l3, float l4);

        float getQ1();
        float getQ2();
        float getQ3();
        float getQ4();
        float getQ5();
        float getPosX();
        float getPosY();
        float getPosZ();
        float getDim();

        void forwardKinematics(float q1, float q2, float q3, float q4, float q5);
        void inverseKinematics(float x, float y, float z, float beta);
        float updatePosition(int enX, int enY, int enZ, float stepX, float mstepY, float mstepZ);

};
#endif