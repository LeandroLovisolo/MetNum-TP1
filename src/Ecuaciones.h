#ifndef ECUACIONES_H_
#define ECUACIONES_H_

#include <vector>

#include "TFloat.h"

TFloat Ecuacion4(const TFloat& beta, const vector<double>& muestra, size_t t);

TFloat Sigma(const TFloat& beta, const vector<double>& muestra, size_t t);

TFloat Lambda(const TFloat& beta, const vector<double>& muestra, size_t t);

#endif /* ECUACIONES_H_ */



