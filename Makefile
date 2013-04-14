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

graficos:
	./graficar --archivo X1-final --metodo newton --p0 10 --muestra data/X1.txt
	./graficar --archivo X2-final --metodo newton --p0 10 --muestra data/X2.txt
	./graficar --archivo X3-final --metodo newton --p0 1  --muestra data/X3.txt
	./graficar --archivo X4-final --metodo newton --p0 10 --muestra data/X4.txt
	./graficar --archivo X5-final --metodo newton --p0 10 --muestra data/X5.txt
	./graficar --archivo X6-final --metodo newton --p0 10 --muestra data/X6.txt
	./graficar --archivo X7-final --metodo newton --p0 10 --muestra data/X7.txt	
	mv *.eps *.tex tex

clean-graficos:
	rm tex/X*.eps tex/X*.tex

###############################################################################
# CSVs                                                                        #
###############################################################################

csvs: csv-final csv-biseccion csv-newton

csv-final:
	./dgg --csvheaders                                        >  tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X1.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X2.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 1  --muestra data/X3.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X4.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X5.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X6.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X7.txt >> tex/final.csv

csv-biseccion:
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X1.txt >> tex/biseccion-1.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X2.txt >> tex/biseccion-2.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X3.txt >> tex/biseccion-3.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X4.txt >> tex/biseccion-4.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X5.txt >> tex/biseccion-5.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X6.txt >> tex/biseccion-6.csv
	./tabular --metodo biseccion --a0 1 --b0 100 --muestra data/X7.txt >> tex/biseccion-7.csv

csv-newton:
	./tabular --metodo newton --p0 10 --muestra data/X1.txt >> tex/newton-1.csv
	./tabular --metodo newton --p0 10 --muestra data/X2.txt >> tex/newton-2.csv
	./tabular --metodo newton --p0 3  --muestra data/X3.txt >> tex/newton-3.csv
	./tabular --metodo newton --p0 10 --muestra data/X4.txt >> tex/newton-4.csv
	./tabular --metodo newton --p0 10 --muestra data/X5.txt >> tex/newton-5.csv
	./tabular --metodo newton --p0 10 --muestra data/X6.txt >> tex/newton-6.csv
	./tabular --metodo newton --p0 10 --muestra data/X7.txt >> tex/newton-7.csv