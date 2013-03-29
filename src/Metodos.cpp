#include <iostream>

#include "Metodos.h"

pair<double, int> Biseccion(double(*f)(double x, const vector<double>& muestra, size_t t),
				 double a0, double b0, double tol, unsigned int n,
				 const vector<double>& muestra, size_t t) {
	TFloat a(a0, t), b(b0, t), p(t);

	// Aplico el método de bisección hasta n iteraciones
	for(unsigned int i = 0; i < n; i++) {
		// Busco punto medio del intervalo
		p = (a + b) / 2.0;

		// Si la longitud del intervalo es menor que la tolerancia,
		// devolver el punto medio
		if(((b - a) / 2.0).dbl() < tol) {
			return make_pair(p.dbl(), i + 1);
		}

		// Elegir un nuevo intervalo
		if((f(a.dbl(), muestra, t) * f(p.dbl(), muestra, t)) > 0) {
			a = p;
		} else {
			b = p;
		}
	}

	// Si luego de n iteraciones no caímos dentro de la tolerancia exigida,
	// devolvemos el punto medio del último intervalo
	return make_pair(p.dbl(), n);
}
