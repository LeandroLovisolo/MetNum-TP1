#include <cmath>

#include "Ecuaciones.h"

TFloat M(const TFloat& s, vector<double> muestra, size_t t) {
	TFloat sumatoria(0, t);

	for(unsigned int i = 0; i < muestra.size(); i++) {
		sumatoria = sumatoria + pow(muestra[i], s.dbl());
	}

	return (TFloat(1.0, t) / muestra.size()) * sumatoria;
}

TFloat Msombrero(const TFloat& s, vector<double> muestra, size_t t) {
	TFloat sumatoria(0, t);

	for(unsigned int i = 0; i < muestra.size(); i++) {
		sumatoria = sumatoria + pow(muestra[i], s.dbl()) * log(muestra[i]);
	}

	return (TFloat(1.0, t) / muestra.size()) * sumatoria;
}

TFloat R(const TFloat& s, vector<double> muestra, size_t t) {
	return Msombrero(s, muestra, t) / M(s, muestra, t);
}

TFloat Ecuacion4(const TFloat& beta, const vector<double>& muestra, size_t t) {
	/*
	 * A - B - C = 0
	 *
	 * donde:
	 *
	 * A = log(M(2 * beta))
	 * B = 2 * log(M(beta))
	 * C = log(1 + beta * (D - E))
	 * D = R(beta)
	 * E = R(0)
	 */

	TFloat A(t), B(t), C(t), D(t), E(t);
	A = log(M(beta * 2, muestra, t).dbl());
	B = 2 * log(M(beta, muestra, t).dbl());
	D = R(beta, muestra, t);
	E = R(TFloat(0.0, t), muestra, t);
	C = log(((beta * (D - E)) + 1.0).dbl());

	cout << "A = " << A.dbl() << " "
	     << "B = " << B.dbl() << " "
	     << "C = " << C.dbl() << endl;
	cout << "A - B - C = " << (A - B - C).dbl() << endl;

	return A - B - C;
}

TFloat Sigma(const TFloat& beta, const vector<double>& muestra, size_t t) {
	/*
	 * sigma = [A] ^ (1/beta)
	 *
	 * donde:
	 *
	 * A = B / (n * lambda)
	 * B = Sumatoria [x_i^beta], con i = 1..n
	 * x_i = i-ésimo elemento de la muestra
	 * n = cantidad de elementos de la muestra
	 */

	TFloat B(0.0, t);
	for(unsigned int i = 0; i < muestra.size(); i++) {
		B = B + pow(muestra[i], beta.dbl());
	}

	TFloat A = B / (Lambda(beta, muestra, t) * muestra.size());

	return TFloat(pow(A.dbl(), (TFloat(1.0, t) / beta).dbl()), t);
}

TFloat Lambda(const TFloat& beta, const vector<double>& muestra, size_t t) {
	/*
	 * lambda = [beta * (A/B - C/n)]^-1
	 *
	 * donde:
	 *
	 * A = Sumatoria [(x_i^beta) * log(x_i)], con i = 1..n
	 * B = Sumatoria [x_i^beta], con i = 1..n
	 * C = Sumatoria [log(x_i)], con i = 1..n
	 * x_i = i-ésimo elemento de la muestra
	 * n = cantidad de elementos de la muestra
	 */

	TFloat A(0.0, t);
	for(unsigned int i = 0; i < muestra.size(); i++) {
		A = A + pow(muestra[i], beta.dbl()) * log(muestra[i]);
	}

	TFloat B(0.0, t);
	for(unsigned int i = 0; i < muestra.size(); i++) {
		B = B + pow(muestra[i], beta.dbl());
	}

	TFloat C(0.0, t);
	for(unsigned int i = 0; i < muestra.size(); i++) {
		C = C + log(muestra[i]);
	}

	return TFloat(1.0, t) / (beta * (A/B - C/muestra.size()));
}
