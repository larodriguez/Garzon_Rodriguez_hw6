/*SEBASTIAN GARZON - ALEJANDRO RODRIGUEZ*/

/*PROGRAMA QUE RESUELTE LAS ECUACIONES ACOPLADAS, DEL PROBLEMA DE CAZADORES Y PRESAS*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define A 20.0
#define B 1.0
#define C 30.0
#define D 1.0

/*LLAMA LAS FUNCIONES DEFINIDAS**/
float derivada_x (float t, float x, float y);
float derivada_y (float t, float x, float y);

/*MAIN*/
int main (int argc, char **argv){ 

  /*DEFINICION DE LAS VARIABLES*/
  float h = 1.0E-3;
  float t_min = 0.0;
  float t_max = 1.0;

  int n_puntos = (int)((t_max - t_min)/h);

  float y0;
  float x0;
  int i;

  float t1;
  float t2;
  float t3;
  float t4;
  float x1;
  float x2;
  float x3;
  float x4;
  float y1;
  float y2;
  float y3;
  float y4;
  float k1;
  float k2;
  float k3;
  float k4;
  float u1;
  float u2;
  float u3;
  float u4;
  float average_k;
  float average_u;

  FILE *data;
    
  float* x;
  float* y;
  float* t;

  /*DEFINIMOS EL TAMAÑO DE LOS PUNTEROS*/
  x = malloc(n_puntos*sizeof(float));
  y = malloc(n_puntos*sizeof(float));
  t = malloc(n_puntos*sizeof(float));

  /*LLENAMOS DE 0.0 TODOS 3 PUNTEROS*/
  for(i=0;i<n_puntos;i++){
    x[i] = 0.0;
    y[i] = 0.0;
    t[i] = 0.0;
  }
  
  /*RECIBIMOS POR PARAMETRO LA CONDICION INICIAL*/
  x0 = atof(argv[1]);
  y0 = atof(argv[2]);

  /*ASIGNAMOS LAS CONDICIONES INICIALES*/
  t[0] = t_min;
  x[0] = x0;
  y[0] = y0;

  /*RESOLVEMOS LAS ECUACIONES ACOPLADAS POR EL METODO RUNGE-KUTTA DE 4TO ORDEN*/
  for(i=1;i<n_puntos;i++){
    
    k1 = derivada_x(t[i-1],x[i-1],y[i-1]);
    u1 = derivada_y(t[i-1],x[i-1],y[i-1]);
    /* Primer paso*/
    t1 = t[i-1] + (h/2.0);
    x1 = x[i-1] + ((h/2.0)*k1);
    y1 = y[i-1] + ((h/2.0)*u1);
    k2 = derivada_x(t1, x1, y1);
    u2 = derivada_y(t1, x1, y1);
    /*Segundo paso*/
    t2 = t[i-1] + (h/2.0);
    x2 = x[i-1] + ((h/2.0)*k2);
    y2 = y[i-1] + ((h/2.0)*u2);
    k3 = derivada_x(t2, x2, y2);
    u3 = derivada_y(t2, x2, y2);
    /*Tercer paso*/    
    t3 = t[i-1] + h;
    x3 = x[i-1] + (h*k3);
    y3 = y[i-1] + (h*u3);
    k4 = derivada_x(t3, x3, y3);
    u4 = derivada_y(t3, x3, y3);
    /*Cuarto paso*/
   
    average_k = (1.0/6.0)*(k1 + (2.0*k2) + (2.0*k3) + k4);
    average_u = (1.0/6.0)*(u1 + (2.0*u2) + (2.0*u3) + u4);
    
    t[i] = t[i-1] + h;
    x[i] = x[i-1] + (h*average_k);
    y[i] = y[i-1] + (h*average_u);
    
  }

  /*GENERAMOS EL ARCHIVO .DAT QUE ALMACENA LOS DATOS*/
  data = fopen("Poblaciones_X0_Y0.dat", "w"); 
  
  /*LLENAMOS EL .DAT*/
  for (i=0;i<n_puntos;i++){
    fprintf(data,"%f %f %f \n", t[i], x[i], y[i]);
  }
  fclose(data);
  return 0;
}

/*DEFINIMOS LA FUNCION derivada_x COMO LA PRIMERA ECUACION DIFERENCIAL DEL PROBLEMA*/
float derivada_x (float t, float x, float y){

  float derix;
  derix = (A*x) - ((B*x)*y);
  return derix;
}

/*DEFINIMOS LA FUNCION derivada_y COMO LA SEGUNDA ECUACION DIFERENCIAL DEL PROBLEMA*/
float derivada_y (float t, float x, float y){

  float deriy;
  deriy = -(C*x) + ((D*x)*y);
  return deriy;
}
