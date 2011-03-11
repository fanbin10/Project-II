#include "shoot.h"
#include <iomanip>

double run_rk(double* meshP, double* meshV, double* potential, double E, double h, int steps){
  double k1[2], k2[2], k3[2], k4[2];
  double U, W;
  for (int i=0; i<steps-1; i++){
      U = meshP[i];
      W = meshV[i];
      
      k1[0] = W;
      k1[1] = U*(potential[i]-E);

      k2[0] = k1[1]*h/2+W;
      k2[1] = ((potential[i]+potential[i+1])/2-E)*(k1[0]*h/2+U);

      k3[0] = k2[1]*h/2+W;
      k3[1] = ((potential[i]+potential[i+1])/2-E)*(k2[0]*h/2+U);

      k4[0] = k3[1]*h+W;
      k4[1] = (potential[i+1]-E)*(k3[0]*h+U);
      
      meshP[i+1] = U + 1.0/6*h*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
      meshV[i+1] = W + 1.0/6*h*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
    }

  return meshP[steps-1];
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


int search(double* meshP, double* meshV, double* potential, double h, int steps, double resolv){
  int keyN = floor(1/resolv);
  int N=0;
  double  E;
  double* keys = (double*)malloc(sizeof(double)*(keyN+1));
  double range[]={0,0,0};
  for (int m=0; m<2; m++){
    meshP[0]=m;
    meshV[0]=1-m;
    keys[0]=run_rk(meshP, meshV, potential, 0, h, steps);
    for (int i=1; i<=keyN; i++ ){
      E = -1.0*i*resolv*40;
      keys[i]=run_rk(meshP, meshV, potential, E, h, steps);
      if ( (keys[i]*keys[i-1]) < 0 ){
	bisec(-1*i*resolv-resolv, keys[i-1],  -1*i*resolv, keys[i],meshP, meshV, potential, E, h, steps, range);
	N++;
	if (m==0)
	  cout<<setiosflags(ios::fixed)<<setprecision(6)<<"Energy state found:  "<<range[0]<<" (odd) "<<"Range ["<<range[1]<<" "<<range[2]<<"]"<<endl;
	else
	  cout<<setiosflags(ios::fixed)<<setprecision(6)<<"Energy state found:  "<<range[0]<<" (even) "<<"Range ["<<range[1]<<" "<<range[2]<<"]"<<endl;
      }
    }
  }
  return N;
};

double bisec(double low, double lowP,  double high, double highP, double* meshP, double* meshV, double *potential, double E, double h, int steps, double (&range)[3]){
  if (high-low < 0.00001){
    range[0] = 0.5*(low+high);
    range[1] = low;
    range[2] = high;
    return range[0];
  }
  double middle = 0.5*(low+high);
  double middleP = run_rk(meshP, meshV, potential, middle, h, steps);

  if (middleP * lowP < 0)
    bisec(low, lowP,  middle, middleP,meshP, meshV, potential, E, h, steps, range);
  else
    bisec(middle, middleP, high, highP, meshP, meshV, potential, E, h, steps, range);
  return range[0];
};
/*
double shoot(, double* well, int steps, double h, int flag){
 
  for (int i=1; i<steps-1; i++){
    run(i, one, h, well);
    temp = one.getU(i);
    if (flag == 1){
      fprintf(fp,"%lf\t%lf\n",i*h,one.getU(i) );
      fflush(fp);
      usleep(1);
     
      fflush(pipe);
      usleep(1);
    }
  }
  return temp;
}

*/
