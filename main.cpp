#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class lado {
	public:
		int vertex;
		int costo;
		int win;
		lado(int v, int c, int w) : vertex(v), costo(c), win(w) {};
};

class vertice{
	public:
		int index;
		bool conex;
		vector<lado> adj;
		vertice() : conex(0) {};
		vertice(int i) : conex(0), index(i){};
		void print_adj(){
			cout << " * " << endl;
			for (vector<lado>::iterator it = adj.begin(); it != adj.end(); ++it){
				cout << it->vertex << " " << it->costo << " * " ; 
			}
			cout << endl;
		}
};


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

vector<vertice> leer_vector(){
	int number, numero2;
	int n1,n2,n3,n4;
	vector<vertice> grafo;
	
	number = obtener_numero();
	cout << number << endl;
	numero2 = obtener_numero();
	cout << numero2 << endl;

	grafo.resize(number+1);
	for(int i = 0; i < numero2; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		grafo[n1].adj.push_back(lado(n2,n3,n4));
		grafo[n2].adj.push_back(lado(n1,n3,n4));
	}
	numero2 = obtener_numero();
	for(int i = 0; i < numero2; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		grafo[n1].adj.push_back(lado(n2,n3,n4));
		grafo[n2].adj.push_back(lado(n1,n3,n4));
	}
	return grafo;
	//v1 v2 costo valor
	// vertice v1,v2;
	
	// lado b = lado(n2,n3,n4);
	// cout << b.vertex << " " << b.win << endl;
	//cout << "n1 " << n1 << " "<< "n2 " << n2 << " " << "n3 " << n3<< " " << "n4 " << n4 << " " << endl;
}

int main(){
	vector<vertice> g = leer_vector();
	g[1].print_adj();
	g[14].print_adj();

}