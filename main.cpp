#include <cstdlib>
#include <iostream>
#include "shoot.h"
#include <cmath>>

using namespace std;

int main(int argc, char *argv[])
{
  double energy = 0.08;
  double h = 0.01;
  int c,i;
  int steps = 1000;
  double *potential;
  int bound;
  FILE *pipe = popen("gnuplot -persist","w");
  FILE *fp, *result;
  if ( ((fp = fopen("plot.dat","w")) == NULL) )
    { 
      printf("Error can't open plot.dat for writing.\n");
      exit(1);
    }
  if ( ((result = fopen("result.txt","w")) == NULL) )
    { 
      printf("Error can't open result.txt for writing.\n");
      exit(1);
    }
  while ((c = getopt(argc, argv, "n:h:e:")) != -1)
    switch(c)
      {
	case'n':
	  steps = atoi(optarg);
	  break;
	case 'h':
	  h = atof(optarg);
	  break;
	case 'e':
	  energy = atof(optarg);
	  break;
      }

  particle one(steps, energy, 0, 1);

  // construct potential well
  potential = (double *)malloc(steps*sizeof(double));
  for (i=0; i<steps; i++){
    potential[i]=0;
  }
  bound = floor(1/h);
  cout<<bound<<endl;
  for (i=0; i<=bound; i++){
    potential[i]=-1;
  }
  for (i=0; i<steps; i++){
    fprintf(result,"%lf\n",potential[i]);
  }
  cout<<one.getE()<<endl;
  
  for (i=1; i<steps; i++){
    run(i,one, h, potential);
    fprintf(fp,"%lf\t%lf\n",i*h,one.getU(i) );
    // Flush buffer when we want, not when the computer wants. 
    fflush(fp);
    // Put code to sleep so there is time to write data to file 
    usleep(1);
    // Send commands directly to gnuplot through pipe.
    fprintf(pipe,"set xrange [0:10]\n");
    fflush(pipe);
    fprintf(pipe,"set yrange [0:10]\n");
    fflush(pipe);
    fprintf(pipe,"plot 'plot.dat' with lines\n");
    // Force execution of gnuplot commands by flushing buffer pipe. 
    fflush(pipe);
    // Put code to sleep again to give gnuplot a chance to execute commands.
    usleep(1);
  }
  printf("%lf\n", one.getU(i-1));
  return 0;
}
