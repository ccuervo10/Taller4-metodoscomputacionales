#include <stdio.h>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

const int n = 100;
int ultimo = n-1;


float cambiar_referencia_tiempo(float pasado[n][n], float futuro[n][n])
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			pasado[i][j] = futuro[i][j];
		}
	}
}

float calcular_difusion(float T[n][n], int i, int j, int tipoFrontera, float constante)
{
	// tipo de nodo: 0 para varilla
	// 				 1 para calcita
	//				 2 para borde
	//
	// i,j -> indices i,j del nodo que estoy viendo en la matriz T
	//
	// tipo de fronterea:
	//						0 para frontera fija
	//						1 para frontera abierta
	//						2 para frontera periodica


	// determinar el tipo de nodo
	int TipoNodo;
	float h=0.5/((float)(n));

	if (i==0 || i==ultimo || j==0 || j==ultimo)
	{
		TipoNodo = 2;
	}else if ( pow((i-n/2)*h,2) + pow((j-n/2)*h,2) < pow(0.1/2,2) )
	{
		TipoNodo = 0;
	}else
	{
		TipoNodo = 1;
	}

	// variables de indices de vecinos para usar con condiciones de frontera periodica
	int vecino_i1;
	int vecino_i2;
	int vecino_j1;
	int vecino_j2;


	float T1=0;
	if (TipoNodo==0)
	{
		T1 = 100.0; // temperatura de la varilla
	}else if (TipoNodo==1)
	{
		// Nodo de calcita
		T1 += T[i][j] - constante*4.0*T[i][j];
		T1 += constante*( T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1]);
	}else // nodo de frontera
	{

		// fronteras fijas
		if (tipoFrontera==0) // fronteras fijas -> asignar temperatura de los bordes
		{
			for (int i = 0; i < n; ++i)
			{
				T1 = 10.0;
			}
		}

		// fronteras abiertas
		else if (tipoFrontera==1)
		{
			if (i==0){ T1=T[1][j]; }
			if (i==ultimo){ T1=T[ultimo-1][j]; }

			if (j==0){ T1=T[i][1]; }
			if (j==ultimo){ T1=T[i][ultimo-1]; }
		}


		// fronteras periodicas
		else if (tipoFrontera==2)
		{
			if (i==0 && j!=0 && j!=ultimo)
			{
				vecino_i1 = ultimo;
				vecino_i2 = 1;
				vecino_j1 = j+1;
				vecino_j2 = j-1;
				
				T1 += T[i][j] - constante*4.0*T[i][j];
				T1 += constante*( T[vecino_i1][j] + T[vecino_i2][j] + T[i][vecino_j1] + T[i][vecino_j2]);
			}
			else if (i==ultimo && j!=0 && j!=ultimo)
			{
				vecino_i1 = ultimo-1;
				vecino_i2 = 0;
				vecino_j1 = j+1;
				vecino_j2 = j-1;
				
				T1 += T[i][j] - constante*4.0*T[i][j];
				T1 += constante*( T[vecino_i1][j] + T[vecino_i2][j] + T[i][vecino_j1] + T[i][vecino_j2]);
			}
			else if (j==0 && i!=0 && i!=ultimo)
			{
				vecino_i1 = i-1;
				vecino_i2 = i+1;
				vecino_j1 = ultimo;
				vecino_j2 = 1;
				
				T1 += T[i][j] - constante*4.0*T[i][j];
				T1 += constante*( T[vecino_i1][j] + T[vecino_i2][j] + T[i][vecino_j1] + T[i][vecino_j2]);
			}
			else if (j==ultimo && i!=0 && i!=ultimo)
			{
				vecino_i1 = i-1;
				vecino_i2 = i+1;
				vecino_j1 = ultimo-1;
				vecino_j2 = 0;
				
				T1 += T[i][j] - constante*4.0*T[i][j];
				T1 += constante*( T[vecino_i1][j] + T[vecino_i2][j] + T[i][vecino_j1] + T[i][vecino_j2]);
			}
			else if ( i==0 && j==0 ) // esquinas
			{
				vecino_i1 = ultimo;
				vecino_i2 = 1;
				vecino_j1 = ultimo;
				vecino_j2 = 1;
				
				T1 += T[i][j] - constante*4.0*T[i][j];
				T1 += constante*( T[vecino_i1][j] + T[vecino_i2][j] + T[i][vecino_j1] + T[i][vecino_j2]);
			}
			else if ( i==0 && j==ultimo ) // esquinas
			{
				vecino_i1 = ultimo;
				vecino_i2 = 1;
				vecino_j1 = ultimo-1;
				vecino_j2 = 0;
				
				T1 += T[i][j] - constante*4.0*T[i][j];
				T1 += constante*( T[vecino_i1][j] + T[vecino_i2][j] + T[i][vecino_j1] + T[i][vecino_j2]);
			}
			else if ( i==ultimo && j==0 ) // esquinas
			{
				vecino_i1 = ultimo-1;
				vecino_i2 = 0;
				vecino_j1 = ultimo;
				vecino_j2 = 1;
				
				T1 += T[i][j] - constante*4.0*T[i][j];
				T1 += constante*( T[vecino_i1][j] + T[vecino_i2][j] + T[i][vecino_j1] + T[i][vecino_j2]);
			}
			else if ( i==ultimo && j==ultimo ) // esquinas
			{
				vecino_i1 = ultimo-1;
				vecino_i2 = 0;
				vecino_j1 = ultimo-1;
				vecino_j2 = 0;
				
				T1 += T[i][j] - constante*4.0*T[i][j];
				T1 += constante*( T[vecino_i1][j] + T[vecino_i2][j] + T[i][vecino_j1] + T[i][vecino_j2]);
			}
		}




	}



	return T1;
}



int main(int argc, char const *argv[])
{
	// constantes fisicas
	float k=1.62, Cp=820, p=2.71*1e3, v=k/(p*Cp);

	float tiempo=0.2*pow((float)(0.5/n),2)/v;
	float constante=v*tiempo/pow((float)(0.5/n),2);
	int pasos_de_tiempo;

	// crear arreglo de temperaturas
	float TC[n][n];
	float proximaTC[n][n];


	ofstream mi_archivo;


	

	// inicializar temperaturas en cero
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			TC[i][j] = 0.0;
			proximaTC[i][j] = 0.0;
		}
	}



	//int tipoFrontera=1;
	// for tipofrontera entre 0 y 2:

	for (int tipoFrontera = 0; tipoFrontera < 3; ++tipoFrontera)
	{ //***********************************************************
		//***********************************************************
		//***********************************************************

		if (tipoFrontera==0) // fronteras fijas -> asignar temperatura de los bordes
		{
			for (int i = 0; i < n; ++i)
			{
				TC[0][i] = 10.0;
				TC[ultimo][i] = 10.0;
				TC[i][0] = 10.0;
				TC[i][ultimo] = 10.0;
			}
		}

		// distribucion de temperatrua que me invento para probar las condiciones de frontera
//		for (int i = 0; i < 20; ++i)
//		{
//			for (int j = 0; j < 10; ++j)
//			{
//				TC[i][j] = 300;
//			}
//		}


		if (tipoFrontera==0)
		{
			mi_archivo.open("0.txt");
		}else if (tipoFrontera==1)
		{
			mi_archivo.open("1.txt");
		}else
		{
			mi_archivo.open("2.txt");
		}

		/// +++++++++++++++++++++++++++++++++++++++++++++++++++++
		/// recorrido principal
		pasos_de_tiempo = 100;
		for (int i_tiempo = 0; i_tiempo < pasos_de_tiempo; ++i_tiempo)
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					proximaTC[i][j] = calcular_difusion(TC, i, j, tipoFrontera, constante);
				}
			}

			cambiar_referencia_tiempo(TC, proximaTC);


			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					mi_archivo << proximaTC[i][j] << " ";
				}
				mi_archivo << endl; 
			}
		
		}


		
		mi_archivo.close();

	//***********************************************************
	//***********************************************************
	} //***********************************************************


	



	/* code */
	return 0;
}
