#include "kahuil_motors.h"
Kahuil_Motors motor;

void setup() {
  // put your setup code here, to run once:
  motor.startComunication();
  motor.torque(1);
  int pos[6] = {0,2048,2048,1024,512,512};
  int vel[6] = {100,100,100,100,100,100};
  motor.setVel(vel);
  motor.setPos(pos,100);
  delay(1000);
  motor.stopComunication();
}

void loop() {
  // put your main code here, to run repeatedly:

}
