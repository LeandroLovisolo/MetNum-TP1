function res = ecuacion4(beta, Muestra)
    A = log(M(beta * 2.0, Muestra));
    B = 2 * log(M(beta, Muestra));
    D = R(beta, Muestra);
    E = R(0.0, Muestra);
    C = log((((D - E) * beta) + 1.0));
    res = (A - B - C);