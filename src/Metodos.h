#ifndef METODOS_H_
#define METODOS_H_

#include <vector>

#include "TFloat.h"

TFloat Biseccion(TFloat (*f)(const TFloat& x, const vector<double>& muestra, size_t t),
				 double a0, double b0, double tol, unsigned int n,
				 const vector<double>& muestra, size_t t);

#endif /* METODOS_H_ */
