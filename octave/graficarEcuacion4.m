% zoom: Si vale true, centra el gráfico en los ceros.
%       Si vale false o se omite, plotea toda la función.

function graficarEcuacion4(zoom)


if(!exist('zoom'))
    zoom = false;
endif

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

figure;
hold on;
grid on;

if(zoom)
    interval = -2:0.1:6;
    xlim([-2 6]);
    ylim([-0.1 0.05]);
else
    interval = -5:0.5:100;
    xlim([-5 100]);
endif

for i=interval
    puntos1(end + 1) = ecuacion4(i, datos1);
    puntos2(end + 1) = ecuacion4(i, datos2);
    puntos3(end + 1) = ecuacion4(i, datos3);
    puntos4(end + 1) = ecuacion4(i, datos4);
    puntos5(end + 1) = ecuacion4(i, datos5);
    puntos6(end + 1) = ecuacion4(i, datos6);
    puntos7(end + 1) = ecuacion4(i, datos7);
%   puntos8(end + 1) = 0;
endfor

plot(interval, puntos1, 'Color', 'red');
plot(interval, puntos2, 'Color', 'magenta');
plot(interval, puntos3, 'Color', 'blue');
plot(interval, puntos4, 'Color', 'green');
plot(interval, puntos5, 'Color', 'yellow');
plot(interval, puntos6, 'Color', 'black');
plot(interval, puntos7, 'Color', 'cyan');
%plot(interval, puntos8, 'Color', 'brown');

legend('Muestra X1', 'Muestra X2', 'Muestra X3',
       'Muestra X4', 'Muestra X5', 'Muestra X6',
       'Muestra X7');
legend('boxon');

if(zoom)
    legend('Location', 'SouthWest');
else
    legend('Location', 'SouthEast');
endif
