#include <iostream>

#include "Metodos.h"

TFloat Biseccion(TFloat (*f)(const TFloat& x, const vector<double>& muestra, size_t t),
				 double a0, double b0, double tol, unsigned int n,
				 const vector<double>& muestra, size_t t) {
	TFloat a(a0, t);
	TFloat b(b0, t);
	TFloat p;

	// Aplico el método de bisección hasta n intervalos
	for(unsigned int i = 0; i < n; i++) {
		// Busco punto medio del intervalo
		p = (a + b) / 2.0;

		cout << "#" << (i + 1) << ": a = " << a.dbl() << "; b = " << b.dbl()
		     << "; f(a) = " << f(a, muestra, t).dbl()
		     << "; f(b) = " << f(b, muestra, t).dbl()
		     << endl;

		// Si la longitud del intervalo es menor que la tolerancia,
		// devolver el punto medio
		if(((b - a) / 2.0).dbl() < tol) {
			return p;
		}

		// Elegir un nuevo intervalo
		if((f(a, muestra, t) * f(p, muestra, t)).dbl() > 0) {
			a = p;
		} else {
			b = p;
		}
	}

	// Si luego de n iteraciones no caímos dentro de la tolerancia exigida,
	// devolvemos el punto medio del último intervalo
	return p;
}
