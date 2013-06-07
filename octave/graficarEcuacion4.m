function graficarEcuacion4()
datos1 = leer_datos('../data/X1.txt');
datos2 = leer_datos('../data/X2.txt');
datos3 = leer_datos('../data/X3.txt');
datos4 = leer_datos('../data/X4.txt');
datos5 = leer_datos('../data/X5.txt');
datos6 = leer_datos('../data/X6.txt');
datos7 = leer_datos('../data/X7.txt');

puntos1 = [];
puntos2 = [];
puntos3 = [];
puntos4 = [];
puntos5 = [];
puntos6 = [];
puntos7 = [];
%puntos8 = [];

for i=-5:0.5:100
	puntos1(end + 1) = ecuacion4(i, datos1);
	puntos2(end + 1) = ecuacion4(i, datos2);
	puntos3(end + 1) = ecuacion4(i, datos3);
	puntos4(end + 1) = ecuacion4(i, datos4);
	puntos5(end + 1) = ecuacion4(i, datos5);
	puntos6(end + 1) = ecuacion4(i, datos6);
	puntos7(end + 1) = ecuacion4(i, datos7);
%	puntos8(end + 1) = 0;
endfor
figure;
hold on;
grid on;
plot(puntos1, 'Color', 'red');
plot(puntos2, 'Color', 'magenta');
plot(puntos3, 'Color', 'blue');
plot(puntos4, 'Color', 'green');
plot(puntos5, 'Color', 'yellow');
plot(puntos6, 'Color', 'black');
plot(puntos7, 'Color', 'cyan');
%plot(puntos8, 'Color', 'brown');
legend('Muestra X1','Muestra X2', 'Muestra X3', 'Muestra X4', 'Muestra X5', 'Muestra X6', 'Muestra X7', 'Location','SouthEast');