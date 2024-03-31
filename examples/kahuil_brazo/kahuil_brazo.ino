#include "kahuil.h"

Kahuil brazo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  /*
  Serial.print("q1 :"); Serial.print(brazo.getQ1());
  Serial.print(" q2 :"); Serial.print(brazo.getQ2());
  Serial.print(" q3 :"); Serial.print(brazo.getQ3());
  Serial.print(" q4 :"); Serial.print(brazo.getQ4());
  Serial.print(" q5 :"); Serial.println(brazo.getQ5());
  Serial.println("");*/

}

void loop() {
  // PONER AQUI LOS IFS CON LOS JOYSTICKS 

  //brazo.updatePosition(1,0,0,-0.5);
  
  Serial.print("pos X :"); Serial.print(brazo.getPosX());
  Serial.print("pos Y :"); Serial.print(brazo.getPosY());
  Serial.print("pos Z :"); Serial.println(brazo.getPosZ());

  delay(1000);
}
