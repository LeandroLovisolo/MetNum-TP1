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
	if(file.is_open()) {
		double sumatoria=0;
		double sumatoriaConLog=0;
		float actualFloat = 0;
		unsigned int size;
		file >> size;
		printf("Size is: %d \n", size);
		for(unsigned int i=0;i<size;i++) {
			file >> actualFloat;
			sumatoria += actualFloat;
			sumatoriaConLog += actualFloat*log(actualFloat);
		}
		sumatoria /= size;
		sumatoriaConLog /= size;
		cout << "Sumatoria: " << sumatoria << endl;
		cout << "SumatoriaConLog: " << sumatoriaConLog << endl;
		file.close();
	}
	else {
		cout << "File not oppened" << endl;
	}
	return 0;
}
