all: Resultados_hw4.pdf


Resultados_hw4.pdf: Resultados_hw4.tex 0_0.png 1_0.png 2_0.png proyectil_x.png proyectil_x_varios.png
	# Compilar dos veces para que las referencias queden bien
	pdflatex Resultados_hw4.tex > log_tex
	pdflatex Resultados_hw4.tex > log_tex

0_0.png 1_0.png 2_0.png proyectil_x.png proyectil_x_varios.png: 0.txt 1.txt 2.txt proyectil_x.txt proyectil_x_varios.txt
	python Plots_hw4.py

0.txt 1.txt 2.txt: PDE.cpp
	g++ PDE.cpp -o calcita_varilla.x
	./calcita_varilla.x


proyectil_x.txt proyectil_x_varios.txt: ODE.cpp
	g++ ODE.cpp -o proyectil_con_friccion.x
	./proyectil_con_friccion.x
