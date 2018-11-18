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
	int i;
	float c=0.2;
	float m=0.2;

	float v0=300.0; // [m/s]


	int numero_pasos=10000;
	float paso_de_tiempo=0.0002;

	float XX[numero_pasos][2];
	float VV[numero_pasos][2];
	float vmedia[2];
	float derivada_vx;
	float derivada_vy;

	// valores iniciales de posicion
	XX[0][0] = 0.0;
	XX[0][1] = 0.0;

	// valores inciales de velocidad
	VV[0][0] = v0*cos(3.1416/4);
	VV[0][1] = v0*cos(3.1416/4);


	ofstream proyectil_x("proyectil_x.txt");
	ofstream proyectil_v("proyectil_v.txt");

	for (i = 0; i < numero_pasos -1; i++)
	{
		// velocidad medio paso de tiempo adelante
		derivada_vx = derivada_velocidad_x(VV[i][0], VV[i][1], c, m);
		derivada_vy = derivada_velocidad_y(VV[i][0], VV[i][1], c, m);

		// Calcular la velocidad medio paso de tiempo adelante
		vmedia[0] = VV[i][0] + (paso_de_tiempo/2.0)*derivada_vx;
		vmedia[1] = VV[i][1] + (paso_de_tiempo/2.0)*derivada_vy;

		// Calcular nuevas posiciones XX
		XX[i+1][0] = XX[i][0] + (paso_de_tiempo)*vmedia[0];
		XX[i+1][1] = XX[i][1] + (paso_de_tiempo)*vmedia[1];

		// Calcular nuevas velocidades
		VV[i+1][0] = VV[i][0] + (paso_de_tiempo)*derivada_vx;
		VV[i+1][1] = VV[i][1] + (paso_de_tiempo)*derivada_vy;		

		// imprimir datos
		proyectil_x << XX[i][0] << " " << XX[i][1] << endl;
		proyectil_v << VV[i][0] << " " << VV[i][1] << endl;
	}

	return 0;
}
