#ifndef ECUACIONES_H_
#define ECUACIONES_H_

#include <vector>

#include "TFloat.h"

double Ecuacion4(double beta, const vector<double>& muestra, size_t t);

double Ecuacion5(double beta, const vector<double>& muestra, size_t t);

double DEcuacion4(double beta, const vector<double>& muestra, size_t t);

double Sigma(double beta, const vector<double>& muestra, size_t t);

double Lambda(double beta, const vector<double>& muestra, size_t t);

#endif /* ECUACIONES_H_ */