all: 0.png 1.png 2.png

0.png 1.png 2.png: 0.txt 1.txt 2.txt
	python plots.py

0.txt 1.txt 2.txt: pde.cpp
	g++ pde.cpp -o calcita_varilla.x
	./calcita_varilla.x


proyectil_x.txt proyectil_.txt: ode.cpp
	g++ ode.cpp -o proyectil_con_friccion.x
	./proyectil_con_friccion.x

