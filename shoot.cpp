#include "shoot.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

int run(int i, particle one, double h, double *potential){
  one.saveU(i, one.getU(i-1)+one.getW(i-1)*h);
  one.saveW(i, one.getW(i-1)+one.getU(i-1)*h*3.86*(-1*one.getE()+potential[i]) );
  return 0;
};

int run_rk(int i, particle one, double h, double *potential){
  double k1[2], k2[2], k3[2], k4[2];
  double E = one.getE();
  double U = one.getU(i-1);
  double W = one.getW(i-1);
  k1[0] = W;
  k1[1] = U*(potential[i-1]-E);

  k2[0] = k1[1]*h/2+W;
  k2[1] = ((potential[i-1]+potential[i])/2-E)*(k1[0]*h/2+U);

  k3[0] = k2[1]*h/2+W;
  k3[1] = ((potential[i-1]+potential[i])/2-E)*(k2[0]*h/2+U);

  k4[0] = k3[1]*h+W;
  k4[1] = (potential[i]-E)*(k3[0]*h+U);

  U = U + 1.0/6*h*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
  W = W + 1.0/6*h*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);

  one.saveU(i, U);
  one.saveW(i, W);

  return 0;
};

int potential(double* well, int length, double h){
  int i;
  double width = floor(1/h);
  for (i=0; i<length; i++){
    well[i]=0;
  }
  for (i=0; i<=width; i++){
    well[i]=-1*40;
  }
  return 0;
};

double shoot(particle one, double* well, int steps, double h, int flag){
  FILE *pipe = popen("gnuplot -persist","w");
  FILE *fp;
  double temp;
  if ( ((fp = fopen("plot.dat","w")) == NULL) )
    { 
      printf("Error can't open plot.dat for writing.\n");
      exit(1);
    }
  for (int i=1; i<steps-1; i++){
    run_rk(i, one, h, well);
    temp = one.getU(i);
    if (flag == 1){
      fprintf(fp,"%lf\t%lf\n",i*h,one.getU(i) );
      fflush(fp);
      usleep(1);
      fprintf(pipe,"set xrange [0:%d]\n", (int)floor(h*steps));
      fflush(pipe);
      fprintf(pipe,"set yrange [-10:10]\n");
      fflush(pipe);
      fprintf(pipe,"plot 'plot.dat' with lines\n");
      fflush(pipe);
      usleep(1);
    }
  }
  return temp;
}

