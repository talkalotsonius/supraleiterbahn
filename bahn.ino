/************************************************
*												*
*												*
*	Supraleiterbahn Ver 0.4						*
*	Date: 07/16/2012							*
*	$id stolberg								*
*												*
*												*
************************************************/


/*
This is Version 0.4 of the Arduino Program to contoll the "Supraleiterbahn"
located at the PI 3 of the Friedrich-Alexander-Universität of Erlangen-Nürnberg.
*/

#include "Arduino.h"
#include "PhotoSensorUnit.h"
#include "CoilTrigger.h"

// Global static distance values in [mm] !!!
const float x_PSU = 37.7;
const float x_coil = 30.5;//25;

// Global Arduino classed pin constants !!!
PhotoSensorUnit PSU_1(2,3);
PhotoSensorUnit PSU_2(4,5);
PhotoSensorUnit PSU_3(6,7);
CoilTrigger Trigger_1(8, PSU_1, x_PSU, x_coil);
CoilTrigger Trigger_2(10, PSU_2, x_PSU, x_coil);
CoilTrigger Trigger_3(11, PSU_3, x_PSU, x_coil);


// Program loop
void setup(){}

void loop(){
  while(2!=4){
    Trigger_1.turnOff();
    Trigger_2.turnOff();
    Trigger_3.turnOff();
    PSU_1.ChangeState("reset");
    
    if(Trigger_1.start()==false){
      continue;
    }
    if(Trigger_2.start()==false){
      continue;
    }
    if(Trigger_3.start()==false){
      continue;
    }
  } 
}
