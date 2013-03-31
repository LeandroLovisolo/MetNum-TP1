#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "lib/getopt_pp.h"

#include "Metodos.h"
#include "Ecuaciones.h"

using namespace std;
using namespace GetOpt;

// Parámetros por defecto
#define PRECISION   51
#define TOLERANCIA  0.0001
#define ITERACIONES 100

// Métodos de aproximación
#define BISECCION "biseccion"
#define NEWTON    "newton"

// Usado en la impresión de la salida en formato CSV
#define tab       "\t"

void Ayuda(string ejecutable) {
	cout << "Uso: " << ejecutable << " --mediciones <archivo> --metodo <metodo> [PARAMETROS] [OPCIONES]" << endl
		 << endl
		 << "  --muestra <archivo>    Ruta al archivo con la muestra de la distribución" << endl
		 << "  --metodo  <metodo>     Alguno de los siguientes métodos: biseccion, newton" << endl
		 << endl
		 << "Parámetros del método de bisección:" << endl
		 << endl
		 << "  --a0 <a0>              Extremo inferior del intervalo inicial (mayor estricto a 0)" << endl
		 << "  --b0 <b0>              Extremo superior del intervalo inicial (mayor estricto a 0)" << endl
		 << endl
		 << "Parámetros del método de Newton:" << endl
		 << endl
		 << "  --p0 <p0>              Aproximación inicial (mayor estricto a 0)" << endl
		 << endl
		 << "Opciones:" << endl
		 << endl
		 << "  -i  --iteraciones <i>  Número máximo de iteraciones a realizar (valor por defecto: " << ITERACIONES << ")" << endl
		 << "  -t  --precision   <t>  Bits de precisión en la mantisa (menor estricto a 52;" << endl
		 << "                         valor por defecto: " << PRECISION << ")" << endl
		 << "  -e  --error       <e>  Cota superior del error a cometer (valor por defecto: " << TOLERANCIA << ")" << endl
		 << "  --csv                  Imprimir resultados en formato CSV separados por tabs en el siguiente orden:" << endl
		 << "                         [archivo], [n], [sigma], [beta], [lambda]; donde [archivo] es la ruta al" << endl
		 << "                         archivo con la muestra, y [n] es la cantidad de iteraciones realizadas" << endl
		 << endl
		 << "Ejemplos de uso:" << endl
		 << endl
		 << "  " << ejecutable << " --muestra datos.txt --metodo biseccion --a0 1 --b0 1000" << endl
		 << "  " << ejecutable << " --muestra datos.txt --metodo newton --p0 15" << endl;
	exit(-1);
}

void ErrorAlAbrirArchivo(string path) {
	cout << "No se pudo abrir el archivo " << path << "." << endl;
	exit(-1);
}

vector<double>* LeerMuestra(ifstream& f) {
	// Inicializo el vector
	int longitud;
	f >> longitud;
	vector<double>* muestra = new vector<double>();

	// Cargo la muestra
	double dato;
	for(int i = 0; i < longitud; i++) {
		f >> dato;
		muestra->push_back(dato);
	}

	return muestra;
}

int main(int argc, char *argv[]) {
	GetOpt_pp args(argc, argv);

	// Parámetros generales
	string path;   // Path al archivo con la muestra
	string metodo; // Método de búsqueda de ceros
	int n;         // Máximo número de iteraciones
	size_t t;      // Dígitos de precisión en la mantisa
	double tol;    // Máximo error tolerable

	// Parámetros del método de bisección
	double a0, b0;

	// Parámetros del método de Newton
	double p0;

	// Lectura de parámetros obligatorios
	if(!(args >> Option("muestra", path)))  Ayuda(argv[0]);
	if(!(args >> Option("metodo", metodo))) Ayuda(argv[0]);

	// Lectura de parámetros de cada método
	if(metodo == BISECCION) {
		if(!(args >> Option("a0", a0))) Ayuda(argv[0]);
		if(!(args >> Option("b0", b0))) Ayuda(argv[0]);
	}else if(metodo == NEWTON) {
		if(!(args >> Option("p0", p0))) Ayuda(argv[0]);
	} else Ayuda(argv[0]);

	// Lectura de parámetros opcionales
	args >> Option('i', "iteraciones", n,   ITERACIONES);
	args >> Option('t', "precision",   t,   (size_t) PRECISION);
	args >> Option('e', "error",       tol, TOLERANCIA);

	// Abrir archivo con la muestra
	ifstream f(path.c_str());
	if(!f.is_open()) ErrorAlAbrirArchivo(path);

	// Leer la muestra y cerrar archivo
	vector<double>* muestra = LeerMuestra(f);
	f.close();

	// Guardamos el reloj en el instante anterior a aproximar beta
	clock_t c = clock();

	// Aproximamos beta
	pair<double, int> beta;
	if(metodo == BISECCION) {
		beta = Biseccion(Ecuacion4, a0, b0, tol, n, *muestra, t);
	} else {
		beta = Newton(Ecuacion4, DEcuacion4, p0, tol, n, *muestra, t);
	}

	// Calculamos la cantidad de ticks de reloj que llevó aproximar beta
	c = clock() - c;

	// Mostramos resultados en pantalla
	if(args >> OptionPresent("csv")) {
		cout << path << tab
		     << beta.second << tab
		     << setprecision(t) << Sigma(beta.first, *muestra, t) << tab
             << setprecision(t) << beta.first << tab
             << setprecision(t) << Lambda(beta.first, *muestra, t) << tab
             << (c * 1000 / CLOCKS_PER_SEC) << endl;
	} else {
		cout << "# de iteraciones    = " << beta.second << endl
			 << "Sigma               = " << setprecision(t) << Sigma(beta.first, *muestra, t) << endl
			 << "Beta                = " << setprecision(t) << beta.first << endl
			 << "Lambda              = " << setprecision(t) << Lambda(beta.first, *muestra, t) << endl
             << "Tiempo de ejecución = " << (c * 1000 / CLOCKS_PER_SEC) << "ms" << endl;
	}

	delete muestra;
	return 0;
}
