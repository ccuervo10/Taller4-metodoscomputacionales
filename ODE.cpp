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


void lanzamiento_sencillo()
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
}


int lanzamientos_multiples(float vxInicial[7], float vyInicial[7], int NA)
{
	// NA es el numero de angulos
	// 8 en este caso
	int i;
	float c=0.2;
	float m=0.2;

	int indice_mayor_recorrido=0;

	int numero_pasos=10000;
	float paso_de_tiempo=0.0002;

	float XX[NA][numero_pasos][2];
	float VV[NA][numero_pasos][2];
	float vmedia[NA][2];
	float derivada_vx;
	float derivada_vy;
	float distancia[NA];

	for (i = 0; i < NA; ++i)
	{
		// valores iniciales de posicion
		XX[i][0][0] = 0.0;
		XX[i][0][1] = 0.0;

		// valores inciales de velocidad
		VV[i][0][0] = vxInicial[i];
		VV[i][0][1] = vyInicial[i];

		distancia[i] = -100.0; // valor arbitrario
	}
	
	

	ofstream proyectil_x("proyectil_x_varios.txt");
	ofstream proyectil_v("proyectil_v_varios.txt");

	for (int k = 0; k < NA; ++k)
	{
		// uso esta linea para encontrar un error de segmentation core fault
		//cout << "Started from the bottom now we r here!" << "\n\n";

		for (i = 0; i < numero_pasos -1; i++)
		{
			// velocidad medio paso de tiempo adelante
			derivada_vx = derivada_velocidad_x(VV[k][i][0], VV[k][i][1], c, m);
			derivada_vy = derivada_velocidad_y(VV[k][i][0], VV[k][i][1], c, m);

			// Calcular la velocidad medio paso de tiempo adelante
			vmedia[k][0] = VV[k][i][0] + (paso_de_tiempo/2.0)*derivada_vx;
			vmedia[k][1] = VV[k][i][1] + (paso_de_tiempo/2.0)*derivada_vy;

			// Calcular nuevas posiciones XX
			XX[k][i+1][0] = XX[k][i][0] + (paso_de_tiempo)*vmedia[k][0];
			XX[k][i+1][1] = XX[k][i][1] + (paso_de_tiempo)*vmedia[k][1];

			// Calcular nuevas velocidades
			VV[k][i+1][0] = VV[k][i][0] + (paso_de_tiempo)*derivada_vx;
			VV[k][i+1][1] = VV[k][i][1] + (paso_de_tiempo)*derivada_vy;		

			// imprimir datos
			proyectil_x << XX[k][i][0] << " " << XX[k][i][1] << endl;
			proyectil_v << VV[k][i][0] << " " << VV[k][i][1] << endl;
		

			if (XX[k][i+1][1]<0.0 && distancia[k]==-100.0)
				{
					distancia[k] = XX[k][i+1][0];
					//guardar la maxima distancia en el instante en el que cae al piso y tiene velocidad negativa
				}	
			}	
	}


	indice_mayor_recorrido = 0;
	cout << "Distancias recorridas: (-100 indica que no alcanzo a llegar al piso en lo que se simulo)\n";
	for (int k = 0; k < NA; ++k)
	{

		cout << distancia[k] << " ";
		if (distancia[k] > distancia[indice_mayor_recorrido])
		{	// encontrar cual trayectoria llego mas lejos antes de llegar al piso
			indice_mayor_recorrido = k;
		}
	}
					

	
	cout << "\n\n\n Maxima distancia recorrida = \t" << distancia[indice_mayor_recorrido] << "\n";
	return indice_mayor_recorrido;
}

int main()
{
	// llamar funcion de lanzacmiento a 45 grados
	lanzamiento_sencillo();


	float v0=300.0; // [m/s]

	// arreglos para guardar los angulos y velocidades inicales
	int NA=7;
	float angulo_deg[NA];
	float angulo_rad[NA];
	float vxInicial[NA];
	float vyInicial[NA];

	for (int i = 0; i < NA; ++i)
	{
			//angulos de grados y radianes
		angulo_deg[i]=(float)((i+1)*10);
		angulo_rad[i]=6.283185307179586*angulo_deg[i]/360.0;

		
		// velociades inicialesz
		vxInicial[i] = v0*cos(angulo_rad[i]);
		vyInicial[i] = v0*sin(angulo_rad[i]);

	}

	int indice_mayor_recorrido;
	indice_mayor_recorrido =  lanzamientos_multiples(vxInicial, vyInicial, NA);
	cout << "\n Angulo de Maxima distancia recorrida = \t" << angulo_deg[indice_mayor_recorrido] << "\n\n\n";
	

	return 0;
}
