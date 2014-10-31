#SEBASTIAN GARZON - ALEJANDRO RODRIGUEZ

#PROGRAMA PARA GENERAR LA GRAFICA X - Y DEL ARCHIVO DE trayectoria_E_alpha.dat. DAT
import pylab
import math
import numpy as np
import sys
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import re

archivo = sys.argv[1]
data = np.loadtxt(archivo)
con_iniciales = re.findall("\d+",archivo)

t = data[:,0]
x = data[:,1]
y = data[:,2]
z = data[:,3]

#Genera la grafica de (x,y)
plt.figure(figsize=(15, 10))
plt.plot (x,y)
plt.title(r'$Posicion\ X \ vs \ Y\ Condiciones\ Iniciales \  \alpha ='+str(con_iniciales[1])+'^{\circ} \ K=\ '+str(con_iniciales[0])+'\ MeV $', fontsize=20)
plt.xlabel(r'$Eje\ X$',fontsize=20)
plt.ylabel(r'$Eje\ y$',fontsize=20)
plt.grid()
plt.savefig("Plot_XvsY_K_"+str(con_iniciales[0])+"_alpha_"+str(con_iniciales[1])+".pdf", format='pdf', bbox_inches='tight', transparent=True)

#Genera la grafica en 3D

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.plot(x, y, z, color='r')
plt.title(r'$Trayectoria\ proton\  Condiciones\ Iniciales \  \alpha ='+str(con_iniciales[1])+'^{\circ}\ K=\ '+str(con_iniciales[0])+'\ MeV $', fontsize=20)
plt.xlabel(r'$Eje\ X$',fontsize=10)
plt.ylabel(r'$Eje\ y$',fontsize=10)
plt.grid()
plt.savefig("Trayectoria_3D_K_"+str(con_iniciales[0])+"_alpha_"+str(con_iniciales[1])+".pdf", format='pdf', bbox_inches='tight', transparent=True)



