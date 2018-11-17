#include <stdio.h>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;


float derivada_velocidad_x(float vx, float vy, float c, float m)
{
	float gravedadx = 0.0;
	float friccion = -c/m*sqrt(vx*vx + vy*vy);
	return gravedadx + friccion*vx;
}


float derivada_velocidad_y(float vx, float vy, float c, float m)
{
	float gravedadx = -10.0;
	float friccion = -c/m*sqrt(vx*vx + vy*vy);
	return gravedadx + friccion*vy;
}

int main()
{
	

	return 0;
}
