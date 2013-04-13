#ifndef METODOS_H_
#define METODOS_H_

#include <utility>
#include <vector>

#include "TFloat.h"

enum CriterioParada { ERROR_RELATIVO, ERROR_ABSOLUTO };

pair<double, int> Biseccion(double (*f)(double x, const vector<double>& muestra, size_t t),
                            double a0, double b0, CriterioParada cp, double err, unsigned int n,
                            const vector<double>& muestra, size_t t);

pair<double, int> Newton(double (*f )(double x, const vector<double>& muestra, size_t t),
                         double (*df)(double x, const vector<double>& muestra, size_t t),
                         double p0, CriterioParada cp, double err, unsigned int n,
                         const vector<double>& muestra, size_t t);

#endif /* METODOS_H_ */
