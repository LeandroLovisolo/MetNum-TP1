//============================================================================
// Name        : metnumTP1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cmath>
#include <fstream>
#include <iostream>
#include "TFloat.h"
using namespace std;
double *dataArr; //Hechos globales para poder usar M en los metodos
unsigned int dataSize;

TFloat f(const TFloat &x) { //Funcion ilustrativa
       TFloat result = x*x*x;
       return result;
}

TFloat MDif(const TFloat &beta, const int precision=52) { //Se utiliza regla de la cadena para derivar, ver  si está bien
	//sum(xi^beta) = beta*sum(xi^beta-1)/n =
	TFloat result(0.0, precision);
	for(unsigned int i=0;i<dataSize;i++) {
		result = beta*pow(dataArr[i], beta.dbl()-1); //Ver que onda con la precision en las potencias
	}
	return result*(1/dataSize);
}

TFloat M(const TFloat &beta, const int precision=52) { //Beta vendria a ser S
	//beta es TFloat porque es el parametro a aproximar
	TFloat result(0.0, precision);
	for(unsigned int i=0;i<dataSize;i++) {
		result+pow(dataArr[i], beta.dbl()-1); //Ver que onda con la precision en las potencias
	}
	return result*(beta/dataSize);
}

TFloat mSombreroDif(const TFloat &beta, const int precision=52) { //Ver si está bien
	TFloat result(0.0, precision);
	//la derivada de sum(x^beta*log(x)) = sum(x^(beta-1)*(beta*log(x)+1)))*beta
	for(unsigned int i=0;i<dataSize;i++) {
		result+( (TFloat(pow(dataArr[i], beta.dbl()-1)) *  (beta*log(dataArr[i])) +1)); //Ver si es log o ln
	}
	return result*(beta/dataSize);
}

TFloat mSombrero(const TFloat &beta, const int precision=52) {
	//beta es TFloat porque es el parametro a aproximar
	TFloat result(0.0, precision);
	for(unsigned int i=0;i<dataSize;i++) {
		result+((pow(dataArr[i], beta.dbl())*log(dataArr[i]))); //Ver si es log o ln
	}
	return result*(1/dataSize);
}

TFloat R(const TFloat &beta,const int precision=52) {
	return mSombrero(beta)/mSombrero(beta);
}

TFloat funcionDespeje(const TFloat &beta, const int precision=52) {
	//Asumimos que log es ln, hay que ver eso
	TFloat result(log(1 + (beta*(R(beta)-R(0))).dbl()) + 2*log(M(beta).dbl()) - log(M(beta*2).dbl()), precision);
	return result;
}

TFloat newton(const double x0, const double tol, const int maxIter, const int precision=52) {
	int noIter = 0;
	TFloat x0TF(tol, precision);
	TFloat tolTF(tol, precision);
	TFloat pTF(tol, precision);
	cout <<"It\t"<<"X0\t"<<"F(X0)\t"<<"FDif(X0)\t"<<"P"<<endl;
	do {
		//pTF = x0TF-(funcionDespeje(x0TF)/fDif(x0TF)); vamos a necesitar la derivada de lo que usemos, hay que ver como se derivan
		x0TF = pTF;
		cout <<noIter<<"\t"<<x0TF.dbl()<<"\t"<<f(x0TF).dbl()<<"\t"<</*fDif.dbl()*/"Nada"<<"\t"<<pTF.dbl()<<endl;
		noIter++;
	}
	while((abs((pTF-x0TF).dbl())/abs(pTF.dbl())<tolTF.dbl())&&(noIter<maxIter)); //Cota de error |pn - pn-1|/|pn|
	return pTF;
}

TFloat biseccion(const double a, const double b, const double tol, const int maxIter, const int precision=52) {
	TFloat c(0.0, precision);
	TFloat aTF(a, precision);
	TFloat bTF(b, precision);
	TFloat tolTF(tol, precision);
	int noIter=0;
	cout <<"It\t"<<"Punto A\t"<<"Punto B\t"<<"Punto C\t"<<"F(C)"<<endl;
	do {
		c=(aTF+bTF)/2;
		if((f(aTF)*f(c)).dbl()<0) {
			bTF=c;
		}
		else {
			aTF=c;
		}
		cout <<noIter<<"\t"<<aTF.dbl()<<"\t"<<bTF.dbl()<<"\t"<<c.dbl()<<"\t"<<f(c).dbl()<<endl;
		noIter++;
	}
	while((abs(f(c).dbl())>tolTF.dbl())&&(noIter<maxIter));
	return c;
}


int main(int argc, char *argv[]) {
	ifstream file(argv[1]);
	if(file.is_open()) {
		double sumatoria=0;
		double sumatoriaConLog=0;
		double actualDouble = 0;
		file >> dataSize;
		dataArr = new double[dataSize];
		printf("Size is: %d \n", dataSize);
		for(unsigned int i=0;i<dataSize;i++) {
			file >> actualDouble;
			dataArr[i] = actualDouble;
			sumatoria += dataArr[i];
			sumatoriaConLog += dataArr[i]*log(dataArr[i]);
		}
		sumatoria /= dataSize;
		sumatoriaConLog /= dataSize;
		cout << "Sumatoria: " << sumatoria << endl;
		cout << "SumatoriaConLog: " << sumatoriaConLog << endl;
		file.close();
		cout << "Biseccion: " << endl;
		cout << "Resultado: " << biseccion(-5, 15, 0.02, 30).dbl() << endl;
		delete dataArr;
	}
	else {
		cout << "File not oppened" << endl;
	}
	return 0;
}
