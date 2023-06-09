#ifndef __LIGHTING_H__
#define __LIGHTING_H__

#include <stdlib.h>
#include <math.h>

int light_init(int max_distance, double step, double instensity);
int light_free();

double get_intensity(double distance, double height);

#endif