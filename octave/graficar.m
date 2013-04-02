#!/usr/bin/octave -qf

source("octave/leer_datos.m")
source("octave/GGDpdf_c.m")

args   = argv();
data   = leer_datos(args{2});
sigma  = args{3};
beta   = args{4};
lambda = args{5};

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Gráfico - Inicio                                                          %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

x_bins = min(data) : 0.02 : max(data);

% cuento cant repeticiones en rangos delimitados por x_bins
count = histc(data,x_bins);

figure;
color = [0, 0.7, 0];
bar(x_bins, count / sum(count), "facecolor", color, "edgecolor", color);

hold on
y = GGDpdf_c(x_bins, str2double(sigma), str2double(beta), str2double(lambda));
p = plot(x_bins, y/sum(y), 'r');
set(p, "linewidth", 5)

title(strcat("$\\sigma = ",  sigma,  "$ \\hspace{2.5mm}",
	         "$\\beta = ",   beta,   "$ \\hspace{2.5mm}",
	         "$\\lambda = ", lambda, "$"));

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