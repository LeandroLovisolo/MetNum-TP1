#include <cmath>

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

pair<double, int> Newton(double (*f )(double x, const vector<double>& muestra, size_t t),
                         double (*df)(double x, const vector<double>& muestra, size_t t),
                         double p0, double tol, unsigned int n,
                         const vector<double>& muestra, size_t t) {
	TFloat p(t);

	// Aplico el método de Newton hasta n iteraciones
	for(unsigned int i = 0; i < n; i++) {
		// Busco nueva aproximación
		p = TFloat(p0, t) - TFloat(f(p0, muestra, t), t) / df(p0, muestra, t);

		// Si el error es menor que la tolerancia máxima,
		// devolver la aproximación actual
		if(abs((p - p0).dbl()) < tol) {
			return make_pair(p.dbl(), i);
		}

		// Actualizo la aproximación inicial
		p0 = p.dbl();
	}

	// Si luego de n iteraciones no caímos dentro de la tolerancia exigida,
	// devolvemos la última aproximación obtenida.
	return make_pair(p.dbl(), n);
}
