function dibujarHistyAjuste(data, sigma,beta,lambda)
%
% Dado un vector de datos data y los parametros sigma, beta y lambda de una
% distribucion Gamma Generalizada, se grafica el histograma de los datos y
% la funcion de densidad de la DGG.
%


x_bins = min(data) : 0.02 : max(data);

% cuento cant repeticiones en rangos delimitados por x_bins
count = histc(data,x_bins);

figure;
color = [0, 0.7, 0];
bar(x_bins, count / sum(count), "facecolor", color, "edgecolor", color);

hold on
y = GGDpdf_c(x_bins,sigma,beta,lambda);
p = plot(x_bins, y/sum(y),'r');
set(p, "linewidth", 5)

title(strcat("$\\sigma = ",  num2str(sigma),  "$ \\hspace{2.5mm}",
	         "$\\beta = ",   num2str(beta),   "$ \\hspace{2.5mm}",
	         "$\\lambda = ", num2str(lambda), "$"));