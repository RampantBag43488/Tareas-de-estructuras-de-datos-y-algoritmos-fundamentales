#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>

class Funciones {
    private:
    int sum;

    public:
    int sumaIterativa(int);
    int sumaRecursiva(int);
    int sumaDirecta(int);

};


Funciones::sumaIterativa(int n) {
	sum = 0;
	for (int i = 1; i < n+1; ++i){
		sum = sum + i;
	}
	return sum;
	}


Funciones::sumaRecursiva(int n) {
	if (n == 0){
		return 0;
	}
	else if (n == 1){
		return 1;
	}
	else{
		return n + sumaRecursiva(n-1);
	}
}


Funciones::sumaDirecta(int n) {
	sum = (n * (n + 1))/2;
    return sum;
}

#endif