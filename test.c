
/*
   Madgwick IMU/AHRS Numeric Stability Tests

   Copyright (C) 2012 Tobias Simon

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MadgwickAHRS.h"


float rad2deg(float r)
{
   return r * 180.0f / M_PI;
}


void quat_2_euler(float q[4], float e[3])
{
   float sqw = q[0]*q[0];
   float sqx = q[1]*q[1];
   float sqy = q[2]*q[2];
   float sqz = q[3]*q[3];
   e[0] = atan2f(2.f * (q[1]*q[2] + q[3]*q[0]), sqx - sqy - sqz + sqw);
   e[1] = asinf(-2.f * (q[1]*q[3] - q[2]*q[0]));
   e[2] = atan2f(2.f * (q[2]*q[3] + q[1]*q[0]), -sqx - sqy + sqz + sqw);
}

float randf(void)
{
   return (float)rand()/(float)RAND_MAX;
}


float acc_noise(void)
{
   float noise = 0.1;
   return noise / 2.0f - randf() * noise;
}


int main(int argc, char *argv[])
{
   srand(1237823);
   if (argc > 1)
   {
      instability_fix = atoi(argv[1]);
   }
   int i, c = 0;
   int max_iter = 20000000;
   for (i = 0; i < max_iter; i++)
   {
      float acc_x = acc_noise() + 2.5;
      float acc_y = acc_noise() + 2.5;
      float acc_z = acc_noise() + 9.15;
      MadgwickAHRSupdateIMU(0.0f, 0.0f, 0.0f, acc_x, acc_y, acc_z);
      float euler[3];
      float quat[4] = {q0, q1, q2, q3};
      quat_2_euler(quat, euler);
      if (++c == (max_iter / 1000))
      {
         c = 0;
         printf("%f %f %f %f %f %f\n",
                rad2deg(euler[0]), rad2deg(euler[1]), rad2deg(euler[2]),
                acc_x, acc_y, acc_z);
      }
   }
}

