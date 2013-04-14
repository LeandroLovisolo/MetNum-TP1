#!/usr/bin/octave -qf

source("octave/leer_datos.m")
source("octave/GGDpdf_c.m")

args     = argv();
data     = leer_datos(args{2});
sigma    = [];
beta     = [];
lambda   = [];
etiqueta = {"Muestra"};
colors   = {"red", "blue", "magenta", "black"};

i = 3;
while(true)
    sigma(end+1)  = str2double(args{i});
    i++;
    if(i > length(args)) break; endif;

    beta(end+1)   = str2double(args{i});
    i++;
    if(i > length(args)) break; endif;

    lambda(end+1) = str2double(args{i});
    i++;
    if(i > length(args)) break; endif;

    etiqueta{end+1} = args{i};
    i++;
    if(i > length(args)) break; endif;
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
    p = plot(x_bins, y/sum(y), 'color', colors{i});
    set(p, "linewidth", 3)
    i++;
endwhile

xlabel("Muestra");
ylabel("Frecuencia");

% Si graficamos sólo una curva, mostrar los parámetros de esa curva
% en el título del gráfico
if(length(etiqueta) == 1)
    title(strcat("$\\sigma = ",  num2str(sigma(1)),  "$ \\hspace{2.5mm}",
             "$\\beta = ",   num2str(beta(1)),   "$ \\hspace{2.5mm}",
             "$\\lambda = ", num2str(lambda(1)), "$"));

% En caso contrario, mostramos la referencia de colores de las curvas
else
    legend(etiqueta);
    legend("boxon");
endif;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Gráfico - Fin                                                             %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if strcmp(args{1}, "")
    printf("Presionar cualquier tecla para terminar.\n")
    pause   
else
    print(args{1}, "-S800,500", "-dtex")
    printf(cstrcat("El gráfico ", args{1}, " fue generado exitosamente.\n"))
endif