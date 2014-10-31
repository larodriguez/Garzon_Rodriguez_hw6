/*SEBASTIAN GARZON - ALEJANDRO RODRIGUEZ*/

/*ESTE PROGRAMA REALIZA LA INTEGRACION DE LAS ECUACIONES DE MOVIEMIENTO RELATIVISTA DE PROTONES QUE TIENEN UNA 
POSICION INICIAL (2Rt,0,0) Y VELOCIDAD INICIAL (0,Vsin(alpha),Vsin(alpha)), EL PROGRAMA RECIBE POR PARAMETRO
LA ENERGIA CINETICA DEL SISTEMA, LA CUAL ESTA MEDIDA EN MEGAELECTRONVOLTS Y EL ANGULO alpha QUE ES EL 
PITCH ANGLE DEL SISTEMA*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.14159265
#define h 1E-5
#define min_t 0.0
#define max_t 100.0

#define B0 3E-5 /*[T]*/
#define Rt 63781000 /*RADIO DE LA TIERRA [m]*/
#define q 1.602E-19 /*CARGA PROTON [C]*/
#define c 3E8  /*VELOCIDAD DE LA LUZ [m/s]*/
#define m 1.67E-27  /*MASA PROTON [Kg]*/

/*LLAMA LAS FUNCIONES DEFINIDAS*/
void get_a(float rx, float ry, float rz, float vx, float vy, float vz,float* a, float V);

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

  /*DEFINIMOS LOS PUNTEROS DE TAMAÑO 3*/
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
  
  /*DEFINIMOS V A PARTIR DE LA RELACION CON gamma Y la energia cinetica*/
  float VV1 = (k_jul/(m*(pow(c,2))))+1;
  float VV2 = 1 - (1/(pow(VV1,2)));
  
  V = (sqrt(VV2))*c;
  

  /*ASIGNAMOS LAS CONDICIONES INICIALES*/
  r[0] = 2*Rt;
  r[1] = 0.0;
  r[2] = 0.0;

  v[0] = 0.0;
  v[1] = V*sin(alpha_rad);
  v[2] = V*cos(alpha_rad);

  /*IMPRIMIMOS LAS CONDICIONES INICIALES EN EL ARCHIVO .DAT*/
  sprintf(nombrearchivo, "trayectoria_%.0f_%.0f.dat",k,alpha);

  data = fopen(nombrearchivo, "w");

  fprintf(data, "%f %f %f %f \n", 0.0, r[0], r[1], r[2]);

  /*RESOLVEMOS LAS ECUACIONES ACOPLADAS POR MEDIO DE UN RUNGE-KUTTA DE CUARTO ORDEN
   PARA CADA PASO DE i EL PROGRAMA IMPRIME EL RESULTADO DE (x,y,z) PERO COMO SON MUCHOS
  DATOS, SELECIONAMOS QUE UNICAMENTE LO REALICE PARA LOS i QUE SON MULTIPLOS DE 1000*/
  for(i=1;i<n_puntos;i++){
    
    /*Primer paso*/
    get_a(r[0],r[1],r[2],v[0],v[1],v[2],a1,V);


    v1[0] = v[0] + ((h/2)*a1[0]);
    v1[1] = v[1] + ((h/2)*a1[1]);
    v1[2] = v[2] + ((h/2)*a1[2]);
    r1[0] = r[0] + ((h/2)*v1[0]);
    r1[1] = r[1] + ((h/2)*v1[1]);
    r1[2] = r[2] + ((h/2)*v1[2]);

     /*Segundo paso*/
    get_a(r1[0],r1[1],r1[2],v1[0],v1[1],v1[2],a2,V);
    
    v2[0] = v[0] + ((h/2)*a2[0]);
    v2[1] = v[1] + ((h/2)*a2[1]);
    v2[2] = v[2] + ((h/2)*a2[2]);
    r2[0] = r[0] + ((h/2)*v2[0]);
    r2[1] = r[1] + ((h/2)*v2[1]);
    r2[2] = r[2] + ((h/2)*v2[2]);

    /*Tercer paso*/
    get_a(r2[0],r2[1],r2[2],v2[0],v2[1],v2[2],a3,V);
    
    v3[0] = v[0] + (h*a3[0]);
    v3[1] = v[1] + (h*a3[1]);
    v3[2] = v[2] + (h*a3[2]);
    r3[0] = r[0] + (h*v3[0]);
    r3[1] = r[1] + (h*v3[1]);
    r3[2] = r[2] + (h*v3[2]);

    /*Cuarto paso*/
    get_a(r3[0],r3[1],r3[2],v3[0],v3[1],v3[2],a4,V);
    
    a[0] = (1.0/6.0)*(a1[0] + (2.0*a2[0]) + (2.0*a3[0]) + a4[0]);
    a[1] = (1.0/6.0)*(a1[1] + (2.0*a2[1]) + (2.0*a3[1]) + a4[1]);
    a[2] = (1.0/6.0)*(a1[2] + (2.0*a2[2]) + (2.0*a3[2]) + a4[2]);
    v[0] = v[0] + (h*a[0]);
    v[1] = v[1] + (h*a[1]);
    v[2] = v[2] + (h*a[2]);
    r[0] = r[0] + (h*v[0]);
    r[1] = r[1] + (h*v[1]);
    r[2] = r[2] + (h*v[2]);
    t = i*h;
    
    if(i%1000 == 0){
      fprintf(data, "%f %f %f %f \n", t, r[0], r[1], r[2]);
    }
  }
  
  fclose(data);
  return 0;
  
}

/*DEFINIMOS LA FUNCION get_a QUE REALIZA LA ACTUALIZACION DEL PUNTERO DE LA ACELERACION, 
ESTO SE REALIZA POR MEDIO DE LA RESOLUCION DEL PRODUCTO CRUZ QUE SE ENCUENTRA EN UNA DE LAS
ECUACIONES ACOPLADAS*/
void  get_a(float rx, float ry, float rz, float vx, float vy, float vz,float* a, float V){

  float rr = sqrt((pow(rx,2))+(pow(ry,2))+(pow(rz,2)));
  
  float L = (B0*(pow(Rt,3)))/(pow(rr,5));
  
  float gamma;

  gamma = 1/(sqrt(1-(pow((V/c),2))));

  a[0] = (q/(gamma*m))*((vy*2*L*(pow(rz,2)))-(vy*L*(pow(rx,2)))-(vy*L*(pow(ry,2)))-(vz*L*3*ry*rz));
  
  a[1] = (q/(gamma*m))*(-(vx*L*2*(pow(rz,2)))+(vx*L*(pow(rx,2)))+(vx*L*(pow(ry,2)))+(vz*L*3*rx*rz));

  a[2] = (q/(gamma*m))*((vx*L*3*ry*rz)-(vy*L*3*rx*rz));
 
}

