#include "bsp.h"

void motor_on(void)
{
  INA1=1;
  INA2=0;
}

void motor_off(void)
{
  INA1=0;
  INA2=0;
}
