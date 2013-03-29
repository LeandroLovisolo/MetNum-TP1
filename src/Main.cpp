#include <iostream>
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

TFloat func(const TFloat& x, const vector<double>& muestra, size_t t) {
	return TFloat(x * 2.0 - 1.0);
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

	size_t t = 54;

	TFloat beta = Biseccion(Ecuacion4, 0.0, 20.0, 0.1, 10, *muestra, t);

	cout << "Sigma  = " << Sigma(beta, *muestra, t).dbl() << endl
	     << "Beta   = " << beta.dbl() << endl
	     << "Lambda = " << Lambda(beta, *muestra, t).dbl() << endl;

	delete muestra;
	return 0;
}
