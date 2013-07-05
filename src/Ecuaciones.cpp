#include <cmath>

#include "Ecuaciones.h"

TFloat M(TFloat s, vector<TFloat> muestra, size_t t) {
    TFloat sumatoria(0.0, t);
    for(unsigned int i = 0; i < muestra.size(); i++) {
        sumatoria = sumatoria + pow(muestra[i].dbl(), s.dbl());
    }

    return ((TFloat(1.0, t) / muestra.size()) * sumatoria);
}

TFloat Msombrero(TFloat s, vector<TFloat> muestra, size_t t) {
    TFloat sumatoria(0.0, t);

    for(unsigned int i = 0; i < muestra.size(); i++) {
        sumatoria = sumatoria + TFloat(pow(muestra[i].dbl(), s.dbl()),t) * TFloat(log(muestra[i].dbl()),t);
    }

    return ((TFloat(1.0, t) / muestra.size()) * sumatoria);
}

TFloat R(TFloat s, vector<TFloat> muestra, size_t t) {
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

    return (A / B);
}

TFloat Ecuacion4(TFloat beta, const vector<TFloat>& muestra, size_t t) {
    /*
     * Ecuacion4 = A - B - C
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
    A = log(M(beta * 2.0, muestra, t).dbl());
    B = 2 * log(M(beta, muestra, t).dbl());
    D = R(beta, muestra, t);
    E = R(TFloat(0.0,t), muestra, t);
    C = log((((D - E) * beta) + 1.0).dbl());

    return (A - B - C);
}

TFloat Ecuacion5(TFloat beta, const vector<TFloat>& muestra, size_t t) {
    /*
     * Ecuacion5 = A - 1 - B
     *
     * donde:
     *
     * A = M(2 * beta) / [M(beta)]^2
     * B = beta * (R(beta) - R(0))
     */

    TFloat A(t), B(t);
    A = M(beta * 2, muestra, t) / TFloat(pow(M(beta, muestra, t).dbl(), 2), t);
    B = beta * (R(beta, muestra, t) - R(0, muestra, t));

    return (A - 1 - B);
}

TFloat Sigma(TFloat beta, const vector<TFloat>& muestra, size_t t) {
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
        B = B + TFloat(pow(muestra[i].dbl(), beta.dbl()), t);
    }

    TFloat A(t);
    A = B / (Lambda(beta, muestra, t) * muestra.size());

    return TFloat(pow(A.dbl(), (TFloat(1.0, t) / beta).dbl()), t);
}

TFloat Lambda(TFloat beta, const vector<TFloat>& muestra, size_t t) {
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
        A = A + TFloat(pow(muestra[i].dbl(), beta.dbl()) * log(muestra[i].dbl()), t);
    }

    TFloat B(0.0, t);
    for(unsigned int i = 0; i < muestra.size(); i++) {
        B = B + TFloat(pow(muestra[i].dbl(), beta.dbl()),t);
    }

    TFloat C(0.0, t);
    for(unsigned int i = 0; i < muestra.size(); i++) {
        C = C + TFloat(log(muestra[i].dbl()),t);
    }

    return (TFloat(1.0, t) / (beta * (A/B - C/muestra.size())));
}

/*****************************************************************************
 * DERIVADAS *****************************************************************
 *****************************************************************************/

TFloat DM(TFloat s, vector<TFloat> muestra, size_t t) {
    TFloat sumatoria(0.0, t);

    for(unsigned int i = 0; i < muestra.size(); i++) {
        sumatoria = sumatoria + TFloat(pow(muestra[i].dbl(), s.dbl()), t) * TFloat(log(muestra[i].dbl()),t);
    }

    return ((TFloat(1.0, t) / muestra.size()) * sumatoria);
}

TFloat DMsombrero(TFloat s, vector<TFloat> muestra, size_t t) {
    TFloat sumatoria(0.0, t);

    for(unsigned int i = 0; i < muestra.size(); i++) {
        sumatoria = sumatoria + TFloat(pow(muestra[i].dbl(), s.dbl()),t) * TFloat(pow(log(muestra[i].dbl()), 2),t);
    }

    return ((TFloat(1.0, t) / muestra.size()) * sumatoria);
}

TFloat DR(TFloat s, vector<TFloat> muestra, size_t t) {
    /*
     * DR = [D*A - C*B] / A^2
     *
     * donde:
     *
     * A = M(s)
     * B = Msombrero(s)
     * C = DM(s)
     * D = DMsombrero(s)
     */

    TFloat A(t), B(t), C(t), D(t);
    A = M(s, muestra, t);
    B = Msombrero(s, muestra, t);
    C = DM(s, muestra, t);
    D = DMsombrero(s, muestra, t);

    return ((D*A - C*B) / (A * A));
}

TFloat DEcuacion4(TFloat beta, const vector<TFloat>& muestra, size_t t) {
    /*
     * DEcuacion4 = 2*D/C - 2*B/A - [E + beta*F - G]/[1 + beta*(E - G)]
     *
     * donde:
     * A = M(beta)
     * B = DM(beta)
     * C = M(2 * beta)
     * D = DM(2 * beta)
     * E = R(beta)
     * F = DR(beta)
     * G = R(0)
     */

    TFloat A(t), B(t), C(t), D(t), E(t), F(t), G(t);
    A = M(beta, muestra, t);
    B = DM(beta, muestra, t);
    C = M(beta*2, muestra, t);
    D = DM(beta*2, muestra, t);
    E = R(beta, muestra, t);
    F = DR(beta, muestra, t);
    G = R(TFloat(0.0, t), muestra, t);

    return (D*2/C - B*2/A - (E + F*beta - G)/((E - G)*beta + 1));
}
