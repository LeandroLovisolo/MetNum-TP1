#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>

#include "lib/getopt_pp.h"

#include "Metodos.h"
#include "Ecuaciones.h"
#include "TFloat.h"

using namespace std;
using namespace GetOpt;

// Parámetros por defecto
#define PRECISION   51
#define COTA_ERROR  0.0001
#define ITERACIONES 20

// Métodos de aproximación
#define BISECCION "biseccion"
#define NEWTON    "newton"

// Headers de la salida en formato CSV
#define CSV_HEADERS "Muestra,Sigma,Beta,Lambda,Iteraciones,CritParada,CotaError,BitsMantisa,Tiempo"

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
         << "  -e  --error       <e>  Cota superior del error absoluto a cometer (valor por defecto: " << COTA_ERROR << ")" << endl
         << "  -r  --relativo         Usar error relativo en lugar de error absoluto como criterio de parada." << endl
         << "                         La cota empleada es la provista con la opción anterior (-e ó --error)." << endl
         << "  --csv                  Imprimir resultados en formato CSV en el siguiente orden:" << endl
         << "                         [archivo], [sigma], [beta], [lambda], [n], [tiempo]; donde [archivo] es" << endl
         << "                         la ruta al archivo con la muestra, [n] es la cantidad de iteraciones" << endl
         << "                         realizadas y [tiempo] es el tiempo de ejecución medido en milisegundos." << endl
         << "  --csvheaders           Imprimir línea con los headers correspondientes a la salida producida" << endl
         << "                         con la opción --csv. Ignora el resto de las opciones provistas y" << endl
         << "                         finaliza inmediatamente la ejecución del programa." << endl
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

vector<TFloat>* LeerMuestra(ifstream& f, size_t t) {
    // Inicializo el vector
    int longitud;
    f >> longitud;
    vector<TFloat>* muestra = new vector<TFloat>();

    // Cargo la muestra
    double dato;
    for(int i = 0; i < longitud; i++) {
        f >> dato;
        muestra->push_back(TFloat(dato, t));
    }
    return muestra;
}

int main(int argc, char *argv[]) {
    GetOpt_pp args(argc, argv);

    // Parámetros generales
    string path;       // Path al archivo con la muestra
    string metodo;     // Método de búsqueda de ceros
    int n;             // Máximo número de iteraciones
    size_t t;          // Dígitos de precisión en la mantisa
    double err;        // Cota superior del error absoluto o relativo
    CriterioParada cp; // Criterio de parada

    // Parámetros del método de bisección
    double a0, b0;

    // Parámetros del método de Newton
    double p0;

    // Impresión de headers CSV
    if(args >> OptionPresent("csvheaders")) {
        cout << CSV_HEADERS << endl;
        return 0;
    }

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
    args >> Option('e', "error",       err, COTA_ERROR);
    cp = (args >> OptionPresent('r', "relativo")) ?
        ERROR_RELATIVO : ERROR_ABSOLUTO;

    // Abrir archivo con la muestra
    ifstream f(path.c_str());
    if(!f.is_open()) ErrorAlAbrirArchivo(path);

    // Leer la muestra y cerrar archivo
    vector<TFloat>* muestra = LeerMuestra(f,t);
    f.close();

    // Guardamos el reloj en el instante anterior a aproximar beta
    clock_t c = clock();

    // Aproximamos beta
    pair<TFloat, int> beta;
    if(metodo == BISECCION) {
        beta = Biseccion(Ecuacion4, a0, b0, cp, err, n, *muestra, t);
    } else {
        beta = Newton(Ecuacion4, DEcuacion4, p0, cp, err, n, *muestra, t);
    }

    // Calculamos la cantidad de ticks de reloj que llevó aproximar beta
    c = clock() - c;

    // Precisión decimal en la salida standard
    cout.precision(6);

    // Mostramos resultados en pantalla
    if(args >> OptionPresent("csv")) {
        cout << path                                             << ","
             << Sigma(beta.first, *muestra, t).dbl()             << ","
             << beta.first.dbl()                                 << ","
             << Lambda(beta.first, *muestra, t).dbl()            << ","
             << beta.second                                      << ","
             << (cp == ERROR_RELATIVO ? "Relativo" : "Absoluto") << ","
             << err                                              << ","
             << t                                                << ","
             << (c * 1000 / CLOCKS_PER_SEC)                      << endl;
    } else {
        cout << "              Sigma = " << Sigma(beta.first, *muestra, t).dbl() << endl
             << "               Beta = " << beta.first.dbl() << endl
             << "             Lambda = " << Lambda(beta.first, *muestra, t).dbl() << endl
             << "   # de iteraciones = " << beta.second << endl
             << "Tiempo de ejecución = " << (c * 1000 / CLOCKS_PER_SEC) << "ms" << endl;
    }

    delete muestra;
    return 0;
}
