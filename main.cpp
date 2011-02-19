
#include <iostream>
#include "shoot.h"

using namespace std;

int main(int argc, char *argv[])
{
  double energy = -0.08;
  double bound = 5;
  int c;
  int steps;
  int flag=0;
  double h = 0.001;
  double bic;
  
  while ((c = getopt(argc, argv, "n:h:e:b:p")) != -1)
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
      }
  
  steps= bound/h;
  energy *= 40;
  particle one(steps, energy, 0, 1);

  // construct potential well
  double* well = (double *)malloc(steps*sizeof(double));
  potential(well, steps, h);

  bic=shoot(one, well, steps, h, flag);
  cout<<bic<<endl;
  return 0;
}
