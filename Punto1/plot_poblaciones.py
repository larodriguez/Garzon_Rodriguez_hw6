#SEBASTIAN GARZON - ALEJANDRO RODRIGUEZ

#PROGRAMA PARA GENERAR LA GRAFICA X - Y DEL ARCHIVO DE POBLACIONES. DAT
import pylab
import math 
import numpy as np
import sys 
import matplotlib.pyplot as plt

#EJECUTA EL PROGRAMA COMO DATA
data = np.loadtxt("Poblaciones_X0_Y0.dat")

#DEFINE LAS VARIABLES t, x, y
t = data[:,0]
x = data[:,1]
y = data[:,2]

#GENERA LA GRAFICA DE (X,Y)
plt.figure(figsize=(15, 10))
plt.plot (x,y)
plt.title(r'$Grafica\ de\ X\ y\ Y$', fontsize=20)
plt.xlabel(r'$Eje\ X$', fontsize=20)
plt.ylabel(r'$Eje\ Y$', fontsize=20)
plt.grid()

#GUARDA LA IMAGEN COMO .PDF
plt.savefig("Poblaciones_X0_Y0.pdf", format='pdf', bbox_inches='tight', transparent=True)
