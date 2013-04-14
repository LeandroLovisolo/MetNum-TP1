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

CSV_FINAL     = tex/final.csv
CSV_BISECCION = tex/biseccion.csv
CSV_NEWTON    = tex/newton.csv
CSV_HEADER    = Muestra,Sigma,Beta,Lambda,Iteraciones,CritParada,CotaError,BitsMantisa,Tiempo
DGG_BISECCION = ./dgg --csv --metodo biseccion --a0 1 --b0 100
DGG_NEWTON    = ./dgg --csv --metodo newton --p0 10
PRECISION_1   = 51
PRECISION_2   = 30
PRECISION_3   = 10
COTA_1        = 0.001
COTA_2        = 0.01
COTA_3        = 0.1

csvs: csv-final csv-biseccion csv-newton

csv-final:
	echo $(CSV_HEADER) > $(CSV_FINAL)
	./dgg --csv --metodo newton --p0 10 --muestra data/X1.txt >> $(CSV_FINAL)
	./dgg --csv --metodo newton --p0 10 --muestra data/X2.txt >> $(CSV_FINAL)
	./dgg --csv --metodo newton --p0 1  --muestra data/X3.txt >> $(CSV_FINAL)
	./dgg --csv --metodo newton --p0 10 --muestra data/X4.txt >> $(CSV_FINAL)
	./dgg --csv --metodo newton --p0 10 --muestra data/X5.txt >> $(CSV_FINAL)
	./dgg --csv --metodo newton --p0 10 --muestra data/X6.txt >> $(CSV_FINAL)
	./dgg --csv --metodo newton --p0 10 --muestra data/X7.txt >> $(CSV_FINAL)

csv-biseccion: csv-biseccion-header $(shell seq -f "csv-biseccion-%g" 1 7)

csv-biseccion-header:
	echo $(CSV_HEADER) > $(CSV_BISECCION)

csv-biseccion-%: N=`echo $@ | cut -b 15`
csv-biseccion-%:
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_1)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_2)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_3)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_1) -r >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_2) -r >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_3) -r >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_1)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_2)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_3)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_1) -r >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_2) -r >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_3) -r >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_1)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_2)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_3)    >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_1) -r >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_2) -r >> $(CSV_BISECCION)
	$(DGG_BISECCION) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_3) -r >> $(CSV_BISECCION)

csv-newton: csv-newton-header $(shell seq -f "csv-newton-%g" 1 7)

csv-newton-header:
	echo $(CSV_HEADER) > $(CSV_NEWTON)

csv-newton-%: N=`echo $@ | cut -b 12`
csv-newton-%:
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_1)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_2)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_3)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_1) -r >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_2) -r >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_1) -e $(COTA_3) -r >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_1)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_2)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_3)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_1) -r >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_2) -r >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_2) -e $(COTA_3) -r >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_1)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_2)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_3)    >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_1) -r >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_2) -r >> $(CSV_NEWTON)
	$(DGG_NEWTON) --muestra data/X$N.txt -t $(PRECISION_3) -e $(COTA_3) -r >> $(CSV_NEWTON)	
