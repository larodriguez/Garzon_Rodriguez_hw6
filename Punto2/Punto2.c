/*SEBASTIAN GARZON - ALEJANDRO RODRIGUEZ*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.14159265
#define h 0.01
#define min_t 0.0
#define max_t 100.0
#define B0 3E-5 /*T*/
#define Rt 6378.1 /*Km*/
#define rr 0.001  /*??????????????*/
#define q 10000  /*??????????????*/
#define c 0.001  /*VELOCIDAD DE LA LUZ*/
#define m 10000  /*MASA ELECTRON*/

/*LLAMA LAS FUNCIONES DEFINIDAS*/

float get_a(float rx, float ry, float rz, float vx, float vy, float vz);

/*MAIN*/
int main (int argc, char **argv){

  float k;
  float alpha;
  float k_jul;
  float alpha_rad;
  float n_puntos = (int)((max_t - min_t)/h);
  int i;
  float t; 
  float V; 

  FILE *data;
  char nombrearchivo[100];
  
  /*RECIBIMOS POR PARAMETRO (k, alpha) Y LOS TRANSFORMAMOS A LAS UNIDADES NECESARIAS*/

  k = atof(argv[1]);  /*Energia cinetica en megaelectronvoltios*/
  alpha = atof(argv[2]);  /*alpha en grados*/
  alpha_rad= (alpha*pi)/180; /*alpha en radianes*/
  k_jul=(1.60217733*(10E-13)*k)/1; /*Energia cinetica en julios*/

  /*FALTA DEFINIR QUE ES V USANDO LA ENERGIA Y LA RELACION CON "Y"*/

  float* a;
  float* v;
  float* r;

  float* a1;
  float* a2;
  float* a3;
  float* a4;
  float* v1;
  float* v2;
  float* v3;
  float* r1;
  float* r2;
  float* r3;

  a = malloc(3*sizeof(float));
  v = malloc(3*sizeof(float));
  r = malloc(3*sizeof(float));

  a1 = malloc(3*sizeof(float));
  a2 = malloc(3*sizeof(float));
  a3 = malloc(3*sizeof(float));
  a4 = malloc(3*sizeof(float));
  v1 = malloc(3*sizeof(float));
  v2 = malloc(3*sizeof(float));
  v3 = malloc(3*sizeof(float));
  r1 = malloc(3*sizeof(float));
  r2 = malloc(3*sizeof(float));
  r3 = malloc(3*sizeof(float));
  
  /*LLENAMOS DE 0.0 TODOS 3 PUNTEROS*/
  for(i=0;i<3;i++){
    a[i] = 0.0;
    v[i] = 0.0;
    r[i] = 0.0;
    a1[i] = 0.0;
    a2[i] = 0.0;
    a3[i] = 0.0;
    a4[i] = 0.0;
    v1[i] = 0.0;
    v2[i] = 0.0;
    v3[i] = 0.0;
    r1[i] = 0.0;
    r2[i] = 0.0;
    r3[i] = 0.0;
  }


  V= (sqrt(1-(1/(pow((k_jul/(m*pow(c,2))+1),2)))))*c;


  /*ASIGNAMOS LAS CONDICIONES INICIALES*/
  r[0] = 2*Rt;
  r[1] = 0.0;
  r[2] = 0.0;

  v[0] = 0.0;
  v[1] = V*sin(alpha_rad);
  v[2] = V*cos(alpha_rad);

  
  sprintf(nombrearchivo, "trayectoria_%.0f_%.0f.dat",k,alpha);

  data = fopen(nombrearchivo, "w");

  fprintf(data, "%f %f %f \n", 0.0, r[0], r[1], r[2]);

  /*RESOLVEMOS LAS ECUACIONES ACOPLADAS*/
  
  for(i=1;i<n_puntos;i++){

    a1 = get_a(r[0],r[1],r[2],v[0],v[1],v[2]);

    v1 = v + ((h/2)*a1);
    r1 = r + ((h/2)*v1);
    a2 = get_a(r1[0],r1[1],r1[2],v1[0],v1[1],v1[2]);

    v2 = v + ((h/2)*a2);
    r2 = r + ((h/2)*v2);
    a3 = get_a(r2[0],r2[1],r2[2],v2[0],v2[1],v2[2]);

    v3 = v + (h*a3);
    r3 = r + (h*v3);
    a4 = get_a(r3[0],r3[1],r3[2],v3[0],v3[1],v3[2]);

    a = (1.0/6.0)*(a1 + (2.0*a2) + (2.0*a3) + a4);
    v = v + (h*a);
    r = r + (h*v);
    t = i*h;
    
    if
    fprintf(data, "%f %f %f \n", t, r[0], r[1], r[2]);
    
  }

  fclose(data);
  return 0;

}


float get_a(float rx, float ry, float rz, float vx, float vy, float vz){
  
  float L = (B0*(Rt^3))/(rr^5);
  float* a;
  a = malloc(3*sizeof(float));
  

  a[0] = q*((vy*2*L*(rz^2))-(vy*L*(rx^2))-(vy*L*(ry^2))-(vz*L*3*ry*rz));
  
  a[1] = q*(-(vx*L*2*(rz^2))+(vx*L*(rx^2))+(vx*L*(ry^2))+(vz*L*3*rx*rz));

  a[2] = q*((vx*L*3*y*z)-(vy*L*3*x*z));

  return a; 
 
}

