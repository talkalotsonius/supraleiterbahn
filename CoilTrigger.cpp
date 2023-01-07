/************************************************
*						*
*						*
*	Coil Trigger Class			*
*	Date: 07/16/2012			*
*	$id stolberg				*
*						*
*						*
************************************************/

#include "Arduino.h"
#include "CoilTrigger.h"
#include "PhotoSensorUnit.h"

CoilTrigger::CoilTrigger(const int _pin, PhotoSensorUnit _PSU, const float x_PSU, const float x_coil)
            :pin(_pin), PSU(_PSU), delta_x_PSU(x_PSU), delta_x_coil(x_coil){
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

boolean CoilTrigger::start(){
  boolean A=true;
  unsigned long a, b;
  
  if(PSU.active()==true){
    
    PSU.calculate(delta_x_PSU, delta_x_coil);
    turnOn();
    
    b=millis();
    a=millis();
    while((digitalRead(((unsigned int)(PSU.PS_id+2)))==HIGH) &&
          ((a-b)<=90)){
            a=millis();
            if((a-b)==80){
              A=false;
              return A;
            }
    }
    turnOff();
    PSU.ChangeState("change");
  }
  return A;
}

void CoilTrigger::turnOn(){
  delay(PSU.t_trigger_millis);
  delayMicroseconds(PSU.t_trigger_micros);
  digitalWrite(pin, HIGH);
}

void CoilTrigger::turnOff(){
  digitalWrite(pin, LOW);
}
