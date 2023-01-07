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
#include "PhotoSensorUnit.h"

#ifndef CoilTrigger_h
#define CoilTrigger_h

class CoilTrigger{
  public:
  CoilTrigger(const int _pin, PhotoSensorUnit _PSU, const float x_PSU, const float x_coil);
  boolean start();
  void turnOff();
    
  private:
  void turnOn();
  
  PhotoSensorUnit PSU;
  const int pin;
  const float delta_x_PSU, delta_x_coil;  
};

#endif
