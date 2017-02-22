#include <iostream>
#include <stdio.h>

using namespace std;

int obtener_numero(){
	int numero;
    while(1){
    	cin >> numero;
    	if (cin.fail()){
    		cin.clear();
        	cin.ignore(256,' ');
    	} else {
    		return numero;
    	}
    }
	return numero;
}

void leer_vector(int tipo){
	//v1 v2 costo valor
	int n1,n2,n3,n4;
	cin >> n1 >> n2 >> n3 >> n4;
	cout << "n1 " << n1 << " "<< "n2 " << n2 << " " << "n3 " << n3<< " " << "n4 " << n4 << " " << endl;
}

int main(){
	int number, numero2;
	
	number = obtener_numero();
	cout << number << endl;
	numero2 = obtener_numero();
	cout << numero2 << endl;
	for(int i = 0; i < numero2; i++)
		leer_vector(1);
	numero2 = obtener_numero();
	for(int i = 0; i < numero2; i++)
		leer_vector(1);

}