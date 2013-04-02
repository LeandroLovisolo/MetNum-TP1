###############################################################################
# Binario                                                                     #
###############################################################################

CC=g++
CFLAGS=-Wall
BIN=dgg
OBJ=$(addsuffix .o, $(basename $(shell find . -name "*.cpp")))

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

csvs:
	echo "Muestra,Iteraciones,Sigma,Beta,Lambda,Tiempo" > tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X1.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X2.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 1  --muestra data/X3.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X4.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X5.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X6.txt >> tex/final.csv
	./dgg --csv --metodo newton --p0 10 --muestra data/X7.txt >> tex/final.csv