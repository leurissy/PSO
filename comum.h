#ifndef _COMUM_H_
#define _COMUM_H_

#include <cstdlib>
#include <cmath>
#include <string>
#include <exception>
#include "myexception.h"

namespace std {

const double _PI = acos(-1);
const double raiz_3_sobre_2 = sqrt(3.0)/2.0;

template <typename T>
void troca( T& i, T& j ) {
	T aux;
	aux = i;
	i = j;
	j = aux;
}

template <typename T>
T modulo( T val ) {
	if( val >= 0 ) 
		return val;
	else
		return -val;
}

inline double alfa() {
	return (double)rand() / (double)RAND_MAX;
}

inline int pot( int base, int exp ) {
	int res = 1;
	for( int i = 0; i < exp; i++ )
		res *= base;
	return res;
}

/* para biblioteca
// Computes x^n, where n is a natural number.
double pown(double x, unsigned n) {
    double y = 1;
    // n = 2*d + r. x^n = (x^2)^d * x^r.
    unsigned d = n >> 1;
    unsigned r = n & 1;
    double x_2_d = d == 0? 1 : pown(x*x, d);
    double x_r = r == 0? 1 : x;
    return x_2_d*x_r;
} */

template <typename T>
void sistema_2_grau( const T a, const T b, const T c, const T d, const T e, const T f, T& x, T& y ) {
	const T nulo(0);
	const T det = (a*d-b*c);
	if( det == nulo )
		throw myexception("Determinante nulo.");

	y = (a*f-c*e) / det;
	x = (d*e-b*f) / det;
}

string ldtos( long double val, int precisao );

} //namespace std

#endif

