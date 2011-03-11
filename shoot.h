#include<cstdlib>
#include<iostream>
#include<cmath>
using namespace std;

//int run(int, particle, double, double *);
double run_rk(double*, double*,double*, double, double, int);
int potential(double* well, int length, double bound);
int search(double* meshP, double* meshV, double* potential, double h, int steps, double resolv);
double bisec(double low, double lowP, double high, double highP,  double* meshP, double* meshV, double *potential, double E, double h, int steps, double (&range)[3]);
