#ifndef METODOS_H_
#define METODOS_H_

#include <utility>
#include <vector>

#include "TFloat.h"

pair<double, int> Biseccion(double (*f)(double x, const vector<double>& muestra, size_t t),
                            double a0, double b0, double tol, unsigned int n,
                            const vector<double>& muestra, size_t t);

#endif /* METODOS_H_ */
