#include "shoot.h"

int run(int i, particle one, double h, double *potential){
  one.saveU(i, one.getU(i-1)+one.getW(i-1)*h);
  one.saveW(i, one.getW(i-1)+one.getU(i-1)*h*(-1*one.getE()+potential[i]) );
  return 0;
}
