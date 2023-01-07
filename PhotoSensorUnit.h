/************************************************
*						*
*						*
*	PhotoSensor Class			*
*	Date: 07/16/2012			*
*	$id stolberg				*
*						*
*						*
************************************************/

#include "Arduino.h"

#ifndef PhotoSensorUnit_h
#define PhotoSensorUnit_h

class PhotoSensorUnit{
  public:
  PhotoSensorUnit(const int P1, const int P2);  
  boolean active();
  void calculate(const float delta_x_PSU, const float delta_x_coil);
  void ChangeState(String swap);
  boolean TimeStampTest();
  
  unsigned const int PS_id;
  unsigned long t_trigger_millis;
  unsigned int t_trigger_micros;
    
  private:
  static boolean PS_1_state, PS_2_state;
  unsigned long t1, t2, t3, t4, TimeStamp, TimeStampOld;
  const int PS_1, PS_2;
  float x_S, v, t_trigger;
};

#endif
