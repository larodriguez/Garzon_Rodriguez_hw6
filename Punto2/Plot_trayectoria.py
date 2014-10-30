#SEBASTIAN GARZON - ALEJANDRO RODRIGUEZ

#PROGRAMA PARA GENERAR LA GRAFICA X - Y DEL ARCHIVO DE trayectoria_E_alpha.dat. DAT
import pylab
import math
import numpy as np
import sys
import matplotlib.pyplot as plt

archivo = sys.argv[1]
data = np.loadtxt(archivo)

x = data[:,0]
y = data[:,1]
z = data[:,2]

#Genera la grafica de (x,y)
plt.figure(figsize=(15, 10))
plt.plot (x,y)
plt.title(r'$Posicion\ X \ vs \ Y$', fontsize=20)
plt.xlabel(r'$Eje\ X$',fontsize=20)
plt.ylabel(r'$Eje\ X$',fontsize=20)
plt.grid()
plt.savefig("Plot_XvsY.pdf", format='pdf', bbox_inches='tight', transparent=True)


