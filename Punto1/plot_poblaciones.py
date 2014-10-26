#SEBASTIAN GARZON - ALEJANDRO RODRIGUEZ

#PROGRAMA PARA GENERAR LA GRAFICA X - Y DEL ARCHIVO DE POBLACIONES. DAT
import pylab
import math 
import numpy as np
import sys 
import matplotlib.pyplot as plt

colors = np.random.rand(10)

#EJECUTA EL PROGRAMA COMO DATA
archivo = sys.argv[1]
data = np.loadtxt(archivo)

#DEFINE LAS VARIABLES t, x, y
t = data[:,0]
x = data[:,1]
y = data[:,2]

#GENERA LA GRAFICA DE (X,Y)
plt.figure(figsize=(15, 10))
plt.plot (x,y,c=colors)
plt.title(r'$Grafica\ de\ Presas\ vs\ Cazadores$', fontsize=20)
plt.xlabel(r'$Presas$', fontsize=20)
plt.ylabel(r'$Cazadores$', fontsize=20)
plt.grid()

x0 = data[0,1]
y0 = data[0,2]

#GUARDA LA IMAGEN COMO .PDF
plt.savefig("Poblaciones_"+str(int(x0))+"_"+str(int(y0))+".pdf", format='pdf', bbox_inches='tight', transparent=True)
