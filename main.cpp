
#include <iostream>
#include "shoot.h"

using namespace std;

int main(int argc, char *argv[])
{
  double energy = 0.08;
  double bound = 5;
  int c;
  int steps = 1000;
  int flag=0;
  double h;
  double bic;
  
  while ((c = getopt(argc, argv, "n:h:e:l:p")) != -1)
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
      case 'p':
	flag =1;
	break;
      case 'l':
	bound = atof(optarg);
	break;
      }
  h = bound/steps;

  particle one(steps, energy, 0, 1);

  // construct potential well
  double* well = (double *)malloc(steps*sizeof(double));
  potential(well, steps, bound/steps);

  bic=shoot(one, well, steps, h, flag);
  cout<<bic<<endl;
  return 0;
}
