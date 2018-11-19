import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d


x = np.genfromtxt("proyectil_x.txt")
v = np.genfromtxt("proyectil_v.txt")


plt.figure()
plt.plot(x[:,0], x[:,1])
plt.grid()
plt.ylim([0,5])
plt.xlim([0,6])
plt.savefig('proyectil_x.png')



X = np.genfromtxt("proyectil_x_varios.txt")
V = np.genfromtxt("proyectil_v_varios.txt")

n = len(X) # numero de datos
nreal = int(n/7) # numero de datos por cada lanzamiento


Xordenado = np.reshape(X, (7,nreal,2))
Vordenado = np.reshape(V, (7,nreal,2))
#reordena los datos


plt.figure()
labels=[]
for i in range(7):
	plt.plot(Xordenado[i,:,0], Xordenado[i,:,1])
	labels.append(str(10*(i+1)))
	
plt.grid()
plt.ylim([0,5])
plt.xlim([0,6])
plt.legend(labels)
plt.xlabel('x'); plt.ylabel('y')
plt.savefig('proyectil_x_varios.png')



def contar_lineas(fname):
	D = np.genfromtxt(fname) # Archivo crudo
	lineas = int(len(D)/100) # numero de lineas

	return lineas

def cargar_matriz_datos(fname):
	D = np.genfromtxt(fname) # Archivo crudo
	lineas = int(len(D)/100) # numero de lineas
	forma = (lineas,100,100) # forma de los datos

	newD = np.reshape(D, forma) # reordenar el archivo

	return newD

def grafica(D, i, fname):
	print(np.shape(D))

	# Crear cuadricula XY para graficar
	X,Y = np.meshgrid(np.linspace(-25,25,100), np.linspace(-25,25,100))

	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	ax.plot_wireframe(X=X, Y=Y, Z=D[i,:,:], rstride=5, cstride=2)
	plt.savefig(fname + '_'+str(i)+'.png') # guardar con el nombre que le corresponde


nombres = ["0", "1", "2"]
Matrices = [cargar_matriz_datos(nombre + ".txt") for nombre in nombres]
lineas = [contar_lineas(nombre+".txt") for nombre in nombres]

for i in range(len(nombres)):
	indices = [0, lineas[i]*0.333, lineas[i]*0.666,  lineas[i]-1]
	indices = np.asarray(indices).astype(int) # indices de los tiempos a graficar

	for indice in indices:
		grafica(Matrices[i], indice, nombres[i])
