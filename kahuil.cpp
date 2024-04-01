#include "kahuil.h"
#include <stdlib.h>
#include "math.h"

Kahuil::Kahuil(){
    // robot default dimensions
    this->l1 = 14;   this->l2 = 5; this->l3 = 14; this->l4 = 14;
    // robot starts in home
    this->posX = l2 + l3;// + l4; 
    this->posY = 0; this->posZ = l1;

    inverseKinematics(this->posX,this->posY,this->posZ, this->beta);
    forwardKinematics(this->q1, this->q2, this->q3, this->q4, this->q5);
};

Kahuil::Kahuil(float l1, float l2, float l3, float l4){
    // robot dimensions
    this->l1 = l1; this->l2 = l2; this->l3 = l3; this->l4 = l4;
    // robot starts in home
    this->posX = l2 + l3 + l4; this->posY = 0; this->posZ = l1;
    inverseKinematics(this->posX,this->posY,this->posZ, this->beta);
    forwardKinematics(this->q1, this->q2, this->q3, this->q4, this->q5);
};

// Metodos 
float Kahuil::getQ1(){
    // get articular current values
    return this->q1;
};

float Kahuil::getQ2(){
    // get articular current values
    return this->q2;
};

float Kahuil::getQ3(){
    // get articular current values
    return this->q3;
};

float Kahuil::getQ4(){
    // get articular current values
    return this->q4;
};

float Kahuil::getQ5(){
    // get articular current values
    return this->q5;
};

float Kahuil::getPosX(){
    return this->posX;//, this->posY, this->posZ;
};

float Kahuil::getPosY(){
    return this->posY;//, this->posY, this->posZ;
};

float Kahuil::getPosZ(){
    return this->posZ;//, this->posY, this->posZ;
};

float Kahuil::getDim(){
    return this->l3;
};

void Kahuil::forwardKinematics(float q1, float q2, float q3, float q4, float q5){
    float A = 0.5*M_PI -atan(l2/l3);
    float D = sqrt(pow(l2,2) + pow(l1,2));

    float c1 = cos(this->q1); float s1 = sin(this->q1);
    float cA2 = cos(this->q2 + A); float sA2 = sin(this->q2 + A);
    float c23 = cos(this->q2 + this->q3); float s23 = sin(this->q2 + this->q3);

    this->posX = c1*(D*cA2 + this->l3*c23);
    this->posY = s1*(D*cA2 + this->l3*c23);
    this->posZ = D*sA2+l3*s23;

};

void Kahuil::inverseKinematics(float x, float y, float z, float beta){
    float A = 0.5*M_PI -atan(l2/l3);
        float cA = cos(A); float sA = sin(A);
    float D = sqrt(pow(l2,2) + pow(l1,2));
    float b = (pow(x,2) + pow(y,2) + pow(z,2) - pow(D,2) - pow(l3,2))/(2*D*l3);

    if ((1-pow(b,2)) >= 0){
        this->q3 = A - acos(b); // +-
    } else{this->q3 = 0;} // best effort

        float c3 = cos(this->q3); float s3 = sin(this->q3);
    this->q1 = atan2(y,x); // atan2(y,x);
        float c1 = cos(q1); float s1 = sin(q1);
    this->q2 = atan2(z,x*c1+y*s1) -atan2(D*sA+l3*s3,D*cA+l3*c3);
    this->q4 = -0.5*M_PI -q2 -q3;
    this->q5 = beta + q1; // revisar**
    //return q1, q2, q3, q4, q5;
};

float Kahuil::updatePosition(int enX, int enY, int enZ, float mstepX, float mstepY, float mstepZ){

    // upadte current gripper position
    float pos_X = this->posX + enX*mstepX;
    float pos_Y = this->posY + enY*mstepY;
    float pos_Z = this->posZ + enZ*mstepZ;

    // generate inverse kinematics for position
    inverseKinematics(pos_X, pos_Y, pos_Z, this->beta);
    forwardKinematics(this->q1, this->q2, this->q3, this->q4, this->q5);
    // send data to motors 
    return 0;
};