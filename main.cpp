#include <fstream>
#include "shoot.h"


int main(int argc, char *argv[])
{
  double energy = -0.08;
  double bound = 5;
  int c;
  int steps;
  int flag = 0;
  double h = 0.0001;
  double bic;
  double m = 0;

  while ((c = getopt(argc, argv, "n:h:e:b:po")) != -1)
    switch(c)
      {
      case 'h':
	h = atof(optarg);
	break;
      case 'e':
	energy = atof(optarg);
	break;
      case 'p':
	flag =1;
	break;
      case 'b':
	bound = atof(optarg);
	break;
      case 'o':
	m = 1;
	break;
      }
  
  steps= bound/h;
  energy *= 40;

  // construct potential well
  double* well = (double *)malloc(steps*sizeof(double));
  // construct grid for positions
  double* meshP = (double *)malloc(steps*sizeof(double));
  meshP[0] = 1-m;
  // construct grid for velocities
  double* meshV = (double *)malloc(steps*sizeof(double));
  meshV[0] = m;
  potential(well, steps, h);
  
     if (flag == 1){
    bic=run_rk(meshP, meshV, well, energy, h, steps);
    cout<<bic<<endl;

      ofstream fp;
      fp.open("plot.dat");
      for (int j=0; j<steps; j++){
	fp<<h*j<<"   "<<meshP[j]<<endl;
      }
      fp.close();
      FILE *pipe = popen("gnuplot -persist","w");
      fprintf(pipe,"set title \"energy: %f \" \n", energy/40);
      fflush(pipe);
      fprintf(pipe,"set xrange [0:%d]\n", (int)floor(h*steps));
      fflush(pipe);
      fprintf(pipe,"set yrange [-10:10]\n");
      fflush(pipe);
      fprintf(pipe,"plot 'plot.dat' with lines\n");
      fflush(pipe);
      //sleep(2);
    }						
     else
       search(meshP, meshV,well, h, steps, 0.001);
  return 0;
}
