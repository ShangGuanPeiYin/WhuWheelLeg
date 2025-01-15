#ifndef _FILTER_H_
#define _FILTER_H_
#include "zf_common_headfile.h"

float Kalman_filter(float newAngle, float newRate, float t);

float FirstOrder(float newAngle, float newRate, float t);

float SecondOrder(float newAngle, float newRate, float t);

float fliter1(float num, int times);

float Low_Pass_Filter_x(float nowData);

float Low_Pass_Filter_y(float nowData);

float Low_Pass_Filter_z(float nowData);

#endif
