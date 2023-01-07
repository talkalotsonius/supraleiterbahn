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
#include "PhotoSensorUnit.h"

PhotoSensorUnit::PhotoSensorUnit(const int P1, const int P2)
                :PS_1(P1), PS_2(P2), PS_id(P1){
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  digitalWrite(P1, HIGH);
  digitalWrite(P2, HIGH);
  TimeStampOld = 0;
}

boolean PhotoSensorUnit::PS_1_state = true;
boolean PhotoSensorUnit::PS_2_state = true;

boolean PhotoSensorUnit::active(){
  boolean A=true;
  
  if ((digitalRead(PS_1) == PS_1_state) &&
      (digitalRead(PS_2) == PS_2_state)){
        
        while(digitalRead(PS_1)==PS_1_state){
          
          if(digitalRead(PS_2)!=PS_2_state){
            while(digitalRead(PS_2)!=PS_2_state){
              A=false;
            }
            if(A==false){
              
              while(digitalRead(PS_2)==PS_2_state){
                delay(1);
                if(digitalRead(PS_1)!=PS_1_state){
                  while(digitalRead(PS_1)!=PS_1_state){
                    digitalRead(PS_1);
                  }
                  break;
                }
              }
              break;
            }
          }
          
          if(digitalRead(PS_2)==PS_2_state){
            while(digitalRead(PS_2)==PS_2_state){
              A=true;
              if(digitalRead(PS_1)!=PS_1_state){
                break;
                }
              }
            }         
          
       }
     }
     
  if(A==true){
    t1=micros();    //[µs]
    while(digitalRead(PS_2)!=PS_2_state){
      digitalRead(PS_2);
    }
    t3=micros();    //[µs]
    while(digitalRead(PS_2)==PS_2_state){
      digitalRead(PS_2);
    }
    t2=micros();    //[µs]
    while(digitalRead(PS_2)!=PS_2_state){
      delayMicroseconds(1);
      break;
    }
    t4=micros();    //[µs]
  }
  
  return A;
}

void PhotoSensorUnit::calculate(const float delta_x_PSU, const float delta_x_coil){
  v=(delta_x_PSU/(t2-t1))/1000;   //[m/s]
  x_S=v*(t4-t3)*1000;   //[mm]
  t_trigger=(delta_x_coil+(0.5*x_S))/v;  //[ms]
  t_trigger_millis=(unsigned long)t_trigger;  //[ms]
  t_trigger_micros=(unsigned int)(t_trigger*1000)-(t_trigger_millis*1000);  //[µs]
  TimeStamp = millis();
}

void PhotoSensorUnit::ChangeState(String swap){
  if(swap == "change"){
    PS_1_state = false;
    PS_2_state = false;
  }else if(swap == "reset"){
    PS_1_state = true;
    PS_2_state = true;
  }
}

boolean PhotoSensorUnit::TimeStampTest(){
  boolean A=false;
  if (TimeStampOld < TimeStamp){
    A=true;
    TimeStampOld = TimeStamp;
  }
  return A;
}
