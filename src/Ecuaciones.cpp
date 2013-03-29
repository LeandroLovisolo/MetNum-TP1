#include <cmath>

#include "Ecuaciones.h"

double M(double s, vector<double> muestra, size_t t) {
	TFloat sumatoria(0.0, t);

	for(unsigned int i = 0; i < muestra.size(); i++) {
		sumatoria = sumatoria + pow(muestra[i], s);
	}

	return ((TFloat(1.0, t) / muestra.size()) * sumatoria).dbl();
}

double Msombrero(double s, vector<double> muestra, size_t t) {
	TFloat sumatoria(0.0, t);

	for(unsigned int i = 0; i < muestra.size(); i++) {
		sumatoria = sumatoria + pow(muestra[i], s) * log(muestra[i]);
	}

	return ((TFloat(1.0, t) / muestra.size()) * sumatoria).dbl();
}

double R(double s, vector<double> muestra, size_t t) {
	/*
	 * R = A / B
	 *
	 * donde:
	 *
	 * A = Msombrero(s)
	 * B = M(s)
	 */

	TFloat A(t), B(t);
	A = Msombrero(s, muestra, t);
	B = M(s, muestra, t);

	return (A / B).dbl();
}

double Ecuacion4(double beta, const vector<double>& muestra, size_t t) {
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
	A = log(M(beta * 2.0, muestra, t));
	B = 2 * log(M(beta, muestra, t));
	D = R(beta, muestra, t);
	E = R(0.0, muestra, t);
	C = log((((D - E) * beta) + 1.0).dbl());

	return (A - B - C).dbl();
}

double Ecuacion5(double beta, const vector<double>& muestra, size_t t) {
	/*
	 * A - 1 - B = 0
	 *
	 * donde:
	 *
	 * A = M(2 * beta) / [M(beta)]^2
	 * B = beta * (R(beta) - R(0))
	 */

	TFloat A(t), B(t);
	A = TFloat(M(2 * beta, muestra, t), t) / pow(M(beta, muestra, t), 2);
	B = TFloat(beta, t) * (R(beta, muestra, t) - R(0, muestra, t));

	return (A - 1 - B).dbl();
}

double Sigma(double beta, const vector<double>& muestra, size_t t) {
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
		B = B + pow(muestra[i], beta);
	}

	TFloat A(t);
	A = B / (Lambda(beta, muestra, t) * muestra.size());

	return TFloat(pow(A.dbl(), (TFloat(1.0, t) / beta).dbl()), t).dbl();
}

double Lambda(double beta, const vector<double>& muestra, size_t t) {
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
		A = A + pow(muestra[i], beta) * log(muestra[i]);
	}

	TFloat B(0.0, t);
	for(unsigned int i = 0; i < muestra.size(); i++) {
		B = B + pow(muestra[i], beta);
	}

	TFloat C(0.0, t);
	for(unsigned int i = 0; i < muestra.size(); i++) {
		C = C + log(muestra[i]);
	}

	return (TFloat(1.0, t) / (TFloat(beta, t) * (A/B - C/muestra.size()))).dbl();
}
