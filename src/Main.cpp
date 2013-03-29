#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Metodos.h"
#include "Ecuaciones.h"

using namespace std;

void Ayuda(char *programa) {
	cout << "Uso: " << programa << " [MEDICIONES]" << endl
	     << "  donde [MEDICIONES] es el path a un archivo de texto plano con la muestra" << endl
	     << "  de la distribución gamma standard cuyos parámetros se desean estimar." << endl
	     << endl
	     << "Formato del archivo [MEDICIONES]:" << endl
	     << "    Línea 1: [n]" << endl
	     << "    Línea 2: [x1] [x2] ... [xn]" << endl
	     << "  donde [n] es la cantidad de mediciones (entero), y [x1] [x2] ... [xn]" << endl
	     << "  son las n mediciones (reales positivos) separadas por un espacio en blanco." << endl;
}

void ErrorAlAbrirArchivo(char *path) {
	cout << "No se pudo abrir el archivo " << path << "." << endl
	     << "Para obtener instrucciones de uso, invocar el programa sin argumentos." << endl;
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
	// Comprobar línea de comandos
	if(argc != 2) {
		Ayuda(argv[0]);
		return -1;
	}

	// Abrir archivo con la muestra
	ifstream f(argv[1]);
	if(!f.is_open()) {
		ErrorAlAbrirArchivo(argv[1]);
		return -1;
	}

	// Leer la muestra y cerrar archivo
	vector<double>* muestra = LeerMuestra(f);
	f.close();

	size_t t = 51;

	pair<double, int> beta = Biseccion(Ecuacion4, 1.0, 1000.0, 0.00000001, 100, *muestra, t);
	//pair<double, int> beta = Newton(Ecuacion4, DEcuacion4, 7.5, 0.0000000000001, 100, *muestra, t);

	cout << "# de iteraciones = " << beta.second << endl
	     << "f(beta)          = " << setprecision(t) << Ecuacion4(beta.first, *muestra, t) << endl
	     << "Sigma            = " << setprecision(t) << Sigma(beta.first, *muestra, t) << endl
	     << "Beta             = " << setprecision(t) << beta.first << endl
	     << "Lambda           = " << setprecision(t) << Lambda(beta.first, *muestra, t) << endl;

	delete muestra;
	return 0;
}
