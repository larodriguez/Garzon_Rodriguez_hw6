/*SEBASTIAN GARZON - ALEJANDRO RODRIGUEZ*/

/*PROGRAMA QUE RESUELTE LAS ECUACIONES ACOPLADAS, DEL PROBLEMA DE CAZADORES Y PRESAS*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*LLAMA LAS FUNCIONES DEFINIDAS**/
float derivada_x (float x, float y, float t);
float derivada_y (float x, float y, float t);

/*MAIN*/
int main (int argc, char **argv){ 

  /*DEFINICION DE LAS VARIABLES*/
  float h = 0.01;
  float t_min = 0.0;
  float t_max = 1.0;
  float A = 20.0;
  float B = 1.0;
  float C = 30.0;
  float D = 1.0;

  float n_puntos = ((t_max - t_min)/h);

  int y0;
  int x0;
  int i;

  float x_prime;
  float y_prime;

  float t_middle; 
  float x_middle;
  float y_middle;

  float x_middle_prime;
  float y_middle_prime;

  FILE *data;
    
  float* x;
  float* y;
  float* t;

  /*DEFINIMOS EL TAMAÑO DE LOS PUNTEROS*/
  x = malloc(n_puntos*sizeof(float));
  y = malloc(n_puntos*sizeof(float));
  t = malloc(n_puntos*sizeof(float));

  /*LLENAMOS DE O.0 TODOS 3 PUNTEROS*/
  for(i=0;i<n_puntos;i++){
    x[i] = 0.0;
    y[i] = 0.0;
    t[i] = 0.0;
  }
  
  /*RECIBIMOS POR PARAMETRO LA CONDICION INICIAL*/
  x0 = atoi(argv[1]);
  y0 = atoi(argv[2]);

  /*ASIGNAMOS LAS CONDICIONES INICIALES*/
  t[0] = t_min;
  x[0] = y0;
  y[0] = x0;

  /*RESOLVEMOS LAS ECUACIONES ACOPLADAS POR EL METODO RUNGE-KUTTA DE 2DO ORDEN*/
  for(i=1;i<n_puntos;i++){
    x_prime = derivada_x(t[i-1],x[i-1],y[i-1]);
    y_prime = derivada_y(t[i-1],x[i-1],y[i-1]);

    t_middle = t[i-1] + (h/2.0);
    x_middle = ((x[i-1] + (h/2.0))*x_prime);
    y_middle = ((y[i-1] + (h/2.0))*y_prime);

    x_middle_prime = derivada_x(t_middle,x_middle,y_middle);
    y_middle_prime = derivada_y(t_middle,x_middle,y_middle);

    t[i] = t[i-1] + h;
    x[i] = (x[i-1] + h)*x_middle_prime;
    y[i] = (y[i-1] + h)*y_middle_prime;
  }

  /*GENERAMOS EL ARCHIVO .DAT QUE ALMACENA LOS DATOS*/
  data = fopen("Poblaciones_X0_Y0.dat", "w"); 
  
  /*LLENAMOS EL .DAT*/
  for (i=0;i<n_puntos;i++){
    fprintf(data,"%f %f %f \n", t[i], x[i], y[i]);
  }
  fclose(data);
 
}

/*DEFINIMOS LA FUNCION derivada_x COMO LA PRIMERA ECUACION DIFERENCIAL DEL PROBLEMA*/
float derivada_x (float t, float x, float y){

  float A = 20.0;
  float B = 1.0;
  float C = 30.0;
  float D = 1.0;
  float deri;

  deri = (A*x) - (B*x*y);
  return deri;
}

/*DEFINIMOS LA FUNCION derivada_y COMO LA SEGUNDA ECUACION DIFERENCIAL DEL PROBLEMA*/
float derivada_y (float t, float x, float y){

  float A = 20.0;
  float B = 1.0;
  float C = 30.0;
  float D = 1.0;
  float deri;

  deri = -(C*x) + (D*x*y);
  return deri;
}
