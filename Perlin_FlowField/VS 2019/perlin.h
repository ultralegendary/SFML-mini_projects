#pragma once

#include <cstdio>
#include <cmath>
#include <cstdlib>


 extern int numX ,numY ,numOctaves;
extern double persistence ;

#define maxPrimeIndex 10
extern int primeIndex ;
extern int primes[maxPrimeIndex][3];

double Noise(int i, int x, int y);
double SmoothedNoise(int i, int x, int y);
double Interpolate(double a, double b, double x);
double InterpolatedNoise(int i, double x, double y);
double ValueNoise_2D(double x, double y);
