#include<cstdlib>
#include<iostream>

class particle {
 public:
  particle(int N, double E, double U, double W){
    n = N;
    u = (double *)malloc(n*sizeof(double));
    e = E;
    w = (double *)malloc(n*sizeof(double));
    u[0] = U;
    w[0] = W;
  }
  double getE(){return e;}
  int getN(){return n;}
  double getU(int n){return u[n];}
  double getW(int n){return w[n];}
  int saveU(int n, double value){
    u[n]=value;
    return 0;
  }
  int saveW(int n, double value){
    w[n] = value;
    return 0;
  }
 private:
  int n;
  double e;
  double* u;
  double* w;
};

int run(int, particle, double, double *);
