#include "shoot.h"
#include <cmath>
#include <cstdlib>

int run(int i, particle one, double h, double *potential){
  one.saveU(i, one.getU(i-1)+one.getW(i-1)*h);
  one.saveW(i, one.getW(i-1)+one.getU(i-1)*h*3.86*(-1*one.getE()+potential[i]) );
  return 0;
};


int potential(double* well, int length, double h){
  int i;
  double width;
  for (i=0; i<length; i++){
    well[i]=0;
  }
  width = floor(1/h);
  for (i=0; i<=width; i++){
    well[i]=-1;
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
  for (int i=1; i<steps; i++){
    run(i, one, h, well);
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

