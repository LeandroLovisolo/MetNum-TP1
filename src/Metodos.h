#ifndef METODOS_H_
#define METODOS_H_

#include <utility>
#include <vector>

#include "TFloat.h"

enum CriterioParada { ERROR_RELATIVO, ERROR_ABSOLUTO };

pair<TFloat, int> Biseccion(TFloat (*f)(TFloat x, const vector<TFloat>& muestra, size_t t),
                            double a0, double b0, CriterioParada cp, double err, unsigned int n,
                            const vector<TFloat>& muestra, size_t t);

pair<TFloat, int> Newton(TFloat (*f )(TFloat x, const vector<TFloat>& muestra, size_t t),
                         TFloat (*df)(TFloat x, const vector<TFloat>& muestra, size_t t),
                         double p0, CriterioParada cp, double err, unsigned int n,
                         const vector<TFloat>& muestra, size_t t);

#endif /* METODOS_H_ */
