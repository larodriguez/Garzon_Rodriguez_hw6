all:	particle_in_field.x	Plot_trayectoria.py	trayectoria_1_30.dat	Plot_XvsY_K_1_alpha_30.pdf

particle_in_field.x:	Plot_trayectoria.py	Punto2.c
	touch particle_in_field.x
	cc Punto2.c -o particle_in_field.x
trayectoria_1_30.dat:	particle_in_field.x
	./particle_in_field.x 1 30
Plot_XvsY_K_1_alpha_30.pdf:	trayectoria_1_30.dat
	python Plot_trayectoria.py trayectoria_1_30.dat
