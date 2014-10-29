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
#define r 0.001
#define q 10000


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

  FILE *data;
  chat nombrearchivo[100];
  
  /*RECIBIMOS POR PARAMETRO (k, alpha) Y LOS TRANSFORMAMOS A LAS UNIDADES NECESARIAS*/

  k = atof(argv[1]);  /*Energia cinetica en megaelectronvoltios*/
  alpha = atof(argv[2]);  /*alpha en grados*/
  alpha_rad= (alpha*pi)/180; /*alpha en radianes*/
  k_jul=(1.60217733*(10E-13)*k)/1; /*Energia cinetica en julios*/

  float* a;
  float* v;
  float* vi;
  float* r;
  
  a = malloc(3*sizeof(float));
  v = malloc(3*sizeof(float));
  vi= malloc(3*sizeof(float));
  r = malloc(3*sizeof(float));
  
  /*LLENAMOS DE 0.0 TODOS 3 PUNTEROS*/
  for(i=0;i<3;i++){
    a[i] = 0.0;
    v[i] = 0.0;
    vi[i] = 0.0;
    r[i] = 0.0;
  }

  /*ASIGNAMOS LAS CONDICIONES INICIALES*/
  r[0] = 2*Rt;
  r[1] = 0.0;
  r[2] = 0.0;

  vi[0] = 0.0;
  vi[1] = v*sin(alpha_rad);
  vi[2] = v*cos(alpha_rad);

  
  sprintf(nombrearchivo, "trayectoria_%.0f_%.0f.dat",k,alpha);

  data = fopen(nombrearchivo, "w");

  /*RESOLVEMOS LAS ECUACIONES ACOPLADAS*/
  
  for(i=1;i<n_puntos;i++){

    a1 = get_a(r[0],r[1],r[2],vi[0],vi[1],vi[2]);

    v1 = vi + ((h/2)*a1);
    r1 = r + ((h/2)*v1);
    a2 = get_a(r1[0],r1[1],r1[2],v1[0],v1[1],v1[2]);

    v2 = vi + ((h/2)*a2);
    r2 = r + ((h/2)*v2);
    a3 = get_a(r2[0],r2[1],r2[2],v2[0],v2[1],v2[2]);

    v3 = vi + (h*a3);
    r3 = r + (h*v3);
    a4 = get_a(r3[0],r3[1],r3[2],v3[0],v3[1],v3[2]);

    a = (1.0/6.0)*(a1 + (2.0*a2) + (2.0*a3) + a4);
    v = vi + (h*a);
    r = r + (h*v);
    
    fprintf(data, "%f %f %f \n", tiempo, r[0], r[1], r[2]);

    /* COMO ACTUALIZO VI ?????? */
    
  }

  fclose(data);
  return 0;

}


float get_a(float rx, float ry, float rz, float vx, float vy, float vz){
  
  float L = (B0*(Rt^3))/(r^5);
  float* a;
  a = malloc(3*sizeof(float));
  

  a[0] = ((vy*2*L*(rz^2))-(vy*L*(rx^2))-(vy*L*(ry^2))-(vz*L*3*ry*rz));
  
  a[1] = (-(vx*L*2*(rz^2))+(vx*L*(rx^2))+(vx*L*(ry^2))+(vz*L*3*rx*rz));

  a[2] = ((vx*L*3*y*z)-(vy*L*3*x*z));

  return a; 
 
}


/*

float func_prime_1_x(t, x_1, x_2);
float func_prime_2_x(t, x_1, x_2);
float func_prime_1_y(t, y_1, y_2);
float func_prime_2_y(t, y_1, y_2);
float func_prime_1_z(t, z_1, y_2);
float func_prime_2_z(t, z_1, z_2);
float RungekuttaX(t_old, x_1_old, x_2_old);
float RungekuttaY(t_old, y_1_old, y_2_old);
float RungekuttaZ(t_old, z_1_old, z_2_old);

float func_prime_1_x(t, x_1, x_2){
  return x_2;
}

floa
t func_prime_2_x(t, x_1, x_2){

}

float func_prime_1_y(t, y_1, y_2){
  return y_2;
}

float func_prime_2_y(t, y_1, y_2){

}

float func_prime_1_z(t, z_1, z_2){
  return z_2;
}

float func_prime_2_z(t, z_1, z_2){

}

float RungekuttaX(t_old, x_1_old, x_2_old){

  float x_prime_1;
  float x_prime_2;
  float t_middle;
  float x_1_middle;
  float x_2_middle;
  float t_new;
  float x_1_new;
  float x_2_new;
  

  x_prime_1 = func_prime_1_x(t_old, x_1_old, x_2_old);
  x_prime_2 = func_prime_2_x(t_old, x_1_old, x_2_old);
  

  t_middle = t_old + (h/2.0);
  x_1_middle = x_1_old + (h/2.0) * x_prime_1;
  x_2_middle = x_2_old + (h/2.0) * x_prime_2;
  
  
  x_middle_prime_1 = func_prime_1_x(t_middle, x_1_middle, x_2_middle);
  x_middle_prime_2 = func_prime_2_x(t_middle, x_1_middle, x_2_middle);
  
  t_new = t_old + h;
  x_1_new = (x_1_old + h) * x_middle_prime_1;
  x_2_new = (x_2_old + h) * x_middle_prime_2;
  return t_new, y_1_new, y_2_new;

}

float RungekuttaY(t_old, y_1_old, y_2_old){

  float y_prime_1;
  float y_prime_2;
  float t_middle;
  float y_1_middle;
  float y_2_middle;
  float t_new;
  float y_1_new;
  float y_2_new;
  

  y_prime_1 = func_prime_1_y(t_old,y_1_old, y_2_old);
  y_prime_2 = func_prime_2_y(t_old,y_1_old, y_2_old);
  

  t_middle = t_old + (h/2.0);
  y_1_middle = y_1_old + (h/2.0) * y_prime_1;
  y_2_middle = y_2_old + (h/2.0) * y_prime_2;
  
  
  y_middle_prime_1 = func_prime_1_y(t_middle, y_1_middle, y_2_middle);
  y_middle_prime_2 = func_prime_2_y(t_middle, y_1_middle, y_2_middle);
  
  t_new = t_old + h;
  y_1_new = (y_1_old + h) * y_middle_prime_1;
  y_2_new = (y_2_old + h) * y_middle_prime_2;
  return t_new, y_1_new, y_2_new;

}

float RungekuttaZ(t_old, z_1_old, z_2_old){

  float z_prime_1;
  float z_prime_2;
  float t_middle;
  float z_1_middle;
  float z_2_middle;
  float t_new;
  float z_1_new;
  float z_2_new;
  

  z_prime_1 = func_prime_1_z(t_old,z_1_old, z_2_old);
  z_prime_2 = func_prime_2_z(t_old,z_1_old, z_2_old);
  

  t_middle = t_old + (h/2.0);
  z_1_middle = z_1_old + (h/2.0) * z_prime_1;
  z_2_middle = z_2_old + (h/2.0) * z_prime_2;
  
  
  z_middle_prime_1 = func_prime_1_z(t_middle, z_1_middle, z_2_middle);
  z_middle_prime_2 = func_prime_2_z(t_middle, z_1_middle, z_2_middle);
  
  t_new = t_old + h;
  z_1_new = (z_1_old + h) * z_middle_prime_1;
  z_2_new = (z_2_old + h) * z_middle_prime_2;
  return t_new, z_1_new, z_2_new;

}

*/


