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
using namespace std;


int main(int argc, char *argv[]) {
	ifstream file(argv[1]);
	double *dataArr;
	if(file.is_open()) {
		double sumatoria=0;
		double sumatoriaConLog=0;
		float actualFloat = 0;
		unsigned int size;
		file >> size;
		dataArr = new double[size];
		printf("Size is: %d \n", size);
		for(unsigned int i=0;i<size;i++) {
			file >> actualFloat;
			dataArr[i] = actualFloat;
			sumatoria += dataArr[i];
			sumatoriaConLog += dataArr[i]*log(dataArr[i]);
		}
		sumatoria /= size;
		sumatoriaConLog /= size;
		cout << "Sumatoria: " << sumatoria << endl;
		cout << "SumatoriaConLog: " << sumatoriaConLog << endl;
		file.close();
		delete dataArr;
	}
	else {
		cout << "File not oppened" << endl;
	}
	return 0;
}
