#!/usr/bin/octave -qf

source("octave/leer_datos.m")
source("octave/dibujarHistyAjuste.m")
source("octave/GGDpdf_c.m")

args = argv();
d = leer_datos(args{2});

dibujarHistyAjuste(d, str2double(args{3}),
                      str2double(args{4}),
                      str2double(args{5}))

if strcmp(args{1}, "")
	printf("Presionar cualquier tecla para terminar.\n")
	pause	
else
	print(args{1}, "-S400,300", "-dtex")
	printf(cstrcat("El gráfico ", args{1}, " fue generado exitosamente.\n"))
endif