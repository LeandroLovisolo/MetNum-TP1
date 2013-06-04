function res = R(s, Muestra)
    A = Msombrero(s, Muestra);
    B = M(s, Muestra);
    res = (A / B);