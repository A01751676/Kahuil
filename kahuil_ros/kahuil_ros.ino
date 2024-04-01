#include "kahuil.h"
#include <ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Float32.h>

Kahuil brazo;

// HANDLER DEL NODO DE ROS Y PUBLICADOR --------------------------------------------------------------------------
ros::NodeHandle  nh;
std_msgs::Float32 x_position;
std_msgs::Float32 y_position;
std_msgs::Float32 z_position;
std_msgs::Float32 clawState;

ros::Publisher chatter1("posX", &x_position);
ros::Publisher chatter2("posY", &y_position);
ros::Publisher chatter3("posZ", &z_position);
ros::Publisher chatter4("clawState", &clawState);

float stepX = 0;
float stepY = 0;
float stepZ = 0;

bool moveArm = 0;
bool moveClaw = 0;

float buttonA = 0;
float buttonB = 0;
float buttonX = 0;
float buttonY = 0;

void moveKahuil(const sensor_msgs::Joy& control){

  //stepX = 0; stepY = 0; stepZ = 0;

  buttonA = control.buttons[0];
  buttonB = control.buttons[1];
  buttonX = control.buttons[2];
  buttonY = control.buttons[3];

  // Enable and disable arm motion 
  if (buttonA == 1){
    moveArm = 1;}
  if (buttonB == 1){
    moveArm = 0;}
  
  // Enable and disable claw motion
  if (buttonX == 1){
    moveClaw = 0;}
  if (buttonY == 1){
    moveClaw = 1;}

  // Move arm on 3 axis
  if (moveArm == 1){
    // axes comands 
      // joy iquierdo 
      // 0 -> mov derecha a izquierda
      // 1 -> mov arriba a abajo

      // joy derecho 
      // 3 -> mov de derecha a izquierda
      // 4 -> mov de arrbia a abajo 
    
    stepX = control.axes[4]; // joy derecho (up -> , down ->)
    stepY = control.axes[3]; // joy derecho (right -> , left ->)
    stepZ = control.axes[1]; // joy izquierdo (up -> , down ->)

    brazo.updatePosition(1,1,1,stepX,stepY,stepZ);

    x_position.data = stepX;//brazo.getPosX();
    y_position.data = stepY; //brazo.getPosX();
    z_position.data = stepZ;//brazo.getPosX();

    chatter1.publish(&x_position);
    chatter2.publish(&y_position);
    chatter3.publish(&z_position);
  }

  // Open and close claw
  if (moveClaw == 1){
    clawState.data = control.axes[0]; // joy izquierdo (right -> , left ->)
    chatter4.publish(&clawState);
  }
}

// SUSBSRCIPTOR DE ROS ----------------------------------------------
ros::Subscriber<sensor_msgs::Joy> sub("joy", &moveKahuil);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter1);
  nh.advertise(chatter2);
  nh.advertise(chatter3);
  nh.advertise(chatter4);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
}
