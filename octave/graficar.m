#!/usr/bin/octave -qf

source("octave/leer_datos.m")
source("octave/dibujarHistyAjuste.m")
source("octave/GGDpdf_c.m")

args = argv();
d = leer_datos(args{2});
dibujarHistyAjuste(d, str2double(args{3}),
                      str2double(args{4}),
                      str2double(args{5}))

if strcmp(args{1}, "png")
	print -dpng grafico.png
	printf("El archivo grafico.png fue generado exitosamente.\n")
else
	printf("Presionar cualquier tecla para terminar.\n")
	pause
endif