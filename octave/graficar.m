#!/usr/bin/octave -qf

source("octave/leer_datos.m")
source("octave/GGDpdf_c.m")

args   = argv();
data   = leer_datos(args{2});
sigma  = [];
beta   = [];
lambda = [];
colors = {"red", "blue", "magenta", "black"};

i = 3;
while(i < length(args))
    sigma(end+1)  = str2double(args{i});
    beta(end+1)   = str2double(args{i+1});
    lambda(end+1) = str2double(args{i+2});
    i += 3;
endwhile

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Gráfico - Inicio                                                          %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

x_bins = min(data) : 0.02 : max(data);

% cuento cant repeticiones en rangos delimitados por x_bins
count = histc(data,x_bins);

figure;
color = [0, 0.7, 0];
bar(x_bins, count / sum(count), "facecolor", color, "edgecolor", color);

i = 1;
while(i <= length(sigma))
    hold on
    y = GGDpdf_c(x_bins, sigma(i), beta(i), lambda(i));
    p = plot(x_bins, y/sum(y), 'r');
    set(p, "linewidth", 3)
    set(p, "color", colors{i})
    i++;
endwhile

% Pendiente: mostrar etiquetas coloreadas en el gráfico cuando se tienen
% más de una curva de ajuste.
title(strcat("$\\sigma = ",  num2str(sigma(1)),  "$ \\hspace{2.5mm}",
             "$\\beta = ",   num2str(beta(1)),   "$ \\hspace{2.5mm}",
             "$\\lambda = ", num2str(lambda(1)), "$"));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Gráfico - Fin                                                             %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if strcmp(args{1}, "")
    printf("Presionar cualquier tecla para terminar.\n")
    pause   
else
    print(args{1}, "-S400,300", "-dtex")
    printf(cstrcat("El gráfico ", args{1}, " fue generado exitosamente.\n"))
endif