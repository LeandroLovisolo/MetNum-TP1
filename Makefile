###############################################################################
# Binario                                                                     #
###############################################################################

CC     = g++
CFLAGS = -Wall
BIN    = dgg
OBJ    = $(addsuffix .o, $(basename $(shell find . -name "*.cpp")))

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o dgg

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(BIN) $(shell find . -name "*.o")

###############################################################################
# Gráficos                                                                    #
###############################################################################

# Parámetros para los gráficos comparativos
MUESTRA_MANTISAS         = data/X1.txt
MUESTRA_CRITERIOS_PARADA = data/X2.txt
MANTISA_1                = 51
MANTISA_2                = 20
MANTISA_3                = 15
PRECISION_1              = 0.001
PRECISION_2              = 0.1

graficos: graficos-referencia graficos-comparativos

graficos-referencia:
	./graficar --archivo referencia-1 "--metodo newton --p0 5 --muestra data/X1.txt"
	./graficar --archivo referencia-2 "--metodo newton --p0 5 --muestra data/X2.txt"
	./graficar --archivo referencia-3 "--metodo newton --p0 5 --muestra data/X3.txt"
	./graficar --archivo referencia-4 "--metodo newton --p0 5 --muestra data/X4.txt"
	./graficar --archivo referencia-5 "--metodo newton --p0 5 --muestra data/X5.txt"
	./graficar --archivo referencia-6 "--metodo newton --p0 5 --muestra data/X6.txt"
	./graficar --archivo referencia-7 "--metodo newton --p0 5 --muestra data/X7.txt"
	mv *.eps *.tex tex

graficos-comparativos:
	./graficar --archivo newton-mantisas \
	           "--metodo newton --p0 5 -e 0.001 -t $(MANTISA_1) --muestra $(MUESTRA_MANTISAS)" \
	           "--metodo newton --p0 5 -e 0.001 -t $(MANTISA_2) --muestra $(MUESTRA_MANTISAS)" \
	           "--metodo newton --p0 5 -e 0.001 -t $(MANTISA_3) --muestra $(MUESTRA_MANTISAS)"
	./graficar --archivo biseccion-mantisas \
	           "--metodo biseccion --a0 1 --b0 100 -t $(MANTISA_1) --muestra $(MUESTRA_MANTISAS)" \
	           "--metodo biseccion --a0 1 --b0 100 -t $(MANTISA_2) --muestra $(MUESTRA_MANTISAS)" \
	           "--metodo biseccion --a0 1 --b0 100 -t $(MANTISA_3) --muestra $(MUESTRA_MANTISAS)"
	./graficar --archivo newton-criterios-parada \
	           "--metodo newton --p0 5 -t 51 -e $(PRECISION_1)    --muestra $(MUESTRA_CRITERIOS_PARADA)" \
	           "--metodo newton --p0 5 -t 51 -e $(PRECISION_2)    --muestra $(MUESTRA_CRITERIOS_PARADA)" \
	           "--metodo newton --p0 5 -t 51 -e $(PRECISION_1) -r --muestra $(MUESTRA_CRITERIOS_PARADA)" \
	           "--metodo newton --p0 5 -t 51 -e $(PRECISION_2) -r --muestra $(MUESTRA_CRITERIOS_PARADA)"
	./graficar --archivo biseccion-criterios-parada \
	           "--metodo biseccion --a0 1 --b0 100 -t 51 -e $(PRECISION_1)    --muestra $(MUESTRA_CRITERIOS_PARADA)" \
	           "--metodo biseccion --a0 1 --b0 100 -t 51 -e $(PRECISION_2)    --muestra $(MUESTRA_CRITERIOS_PARADA)" \
	           "--metodo biseccion --a0 1 --b0 100 -t 51 -e $(PRECISION_1) -r --muestra $(MUESTRA_CRITERIOS_PARADA)" \
	           "--metodo biseccion --a0 1 --b0 100 -t 51 -e $(PRECISION_2) -r --muestra $(MUESTRA_CRITERIOS_PARADA)"
	mv *.eps *.tex tex

clean-graficos:
	rm tex/X*.eps tex/X*.tex

###############################################################################
# CSVs                                                                        #
###############################################################################

csvs: csv-referencia csv-biseccion csv-newton

csv-referencia:
	./dgg --csvheaders                                       >  tex/referencia.csv
	./dgg --csv --metodo newton --p0 5 --muestra data/X1.txt >> tex/referencia.csv
	./dgg --csv --metodo newton --p0 5 --muestra data/X2.txt >> tex/referencia.csv
	./dgg --csv --metodo newton --p0 5 --muestra data/X3.txt >> tex/referencia.csv
	./dgg --csv --metodo newton --p0 5 --muestra data/X4.txt >> tex/referencia.csv
	./dgg --csv --metodo newton --p0 5 --muestra data/X5.txt >> tex/referencia.csv
	./dgg --csv --metodo newton --p0 5 --muestra data/X6.txt >> tex/referencia.csv
	./dgg --csv --metodo newton --p0 5 --muestra data/X7.txt >> tex/referencia.csv

csv-biseccion:
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X1.txt > tex/biseccion-1.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X2.txt > tex/biseccion-2.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X3.txt > tex/biseccion-3.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X4.txt > tex/biseccion-4.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X5.txt > tex/biseccion-5.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X6.txt > tex/biseccion-6.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X7.txt > tex/biseccion-7.csv

csv-newton:
	./tabular --metodo newton --p0 5 --muestra data/X1.txt > tex/newton-1.csv
	./tabular --metodo newton --p0 5 --muestra data/X2.txt > tex/newton-2.csv
	./tabular --metodo newton --p0 5 --muestra data/X3.txt > tex/newton-3.csv
	./tabular --metodo newton --p0 5 --muestra data/X4.txt > tex/newton-4.csv
	./tabular --metodo newton --p0 5 --muestra data/X5.txt > tex/newton-5.csv
	./tabular --metodo newton --p0 5 --muestra data/X6.txt > tex/newton-6.csv
	./tabular --metodo newton --p0 5 --muestra data/X7.txt > tex/newton-7.csv

clean-csvs:
	rm tex/*.csv

###############################################################################
# Misc                                                                        #
###############################################################################

all-all: all graficos csvs

clean-all: clean clean-graficos clean-csvs