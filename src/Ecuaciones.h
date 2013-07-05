#ifndef ECUACIONES_H_
#define ECUACIONES_H_

#include <vector>

#include "TFloat.h"

TFloat Ecuacion4(TFloat beta, const vector<TFloat>& muestra, size_t t);

TFloat Ecuacion5(TFloat beta, const vector<TFloat>& muestra, size_t t);

TFloat DEcuacion4(TFloat beta, const vector<TFloat>& muestra, size_t t);

TFloat Sigma(TFloat beta, const vector<TFloat>& muestra, size_t t);

TFloat Lambda(TFloat beta, const vector<TFloat>& muestra, size_t t);

#endif /* ECUACIONES_H_ */