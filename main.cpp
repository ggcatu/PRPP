#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;


/*
	Idea:
		Leer lados R
			Generar componentes conexas
		Leer otros lados
			Buscar camino de costo minimo (Minima perdida) entre ellas
			Buscar camino de costo minimo entre componentes y fuente.

*/



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
		bool visitado;
		vector<lado> adj;
		vertice() : conex(0){};
		vertice(int i) : conex(0), index(i){};

		void print_adj(){
			cout << " * " << endl;
			for (vector<lado>::iterator it = adj.begin(); it != adj.end(); ++it){
				cout << it->vertex << " " << it->costo << " * " ; 
			}
			cout << endl;
		}

		void limpiar(){
			conex = 0;
		}
};

class grafo {
	vector<vertice> v;

	void resize(int n){
		v.resize(n);
	}

	void agregar_lado(int nodo, lado r){
		v[nodo].adj.push_back(r);
	}

	void dfs(){
		for (vector<vertice>::iterator it = v.begin(); it != v.end(); ++it){
				// cout << it->vertex << " " << it->costo << " * " ; 
			if (!it->conex){

			}
		}
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

vector<vertice> leer_grafo(){
	int nodos, ladosR, ladosE;
	int n1,n2,n3,n4;
	vector<vertice> grafo;
	
	nodos = obtener_numero();
	cout << "Numero de nodos: " << nodos << endl;
	ladosR = obtener_numero();
	cout << ladosR << endl;

	grafo.resize(nodos+1);
	for(int i = 0; i < ladosR; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		grafo[n1].adj.push_back(lado(n2,n3,n4));
		grafo[n2].adj.push_back(lado(n1,n3,n4));
	}

	// Hay que buscar las componentes conexas en el grafo hasta este punto.

	ladosE = obtener_numero();
	for(int i = 0; i < ladosE; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		grafo[n1].adj.push_back(lado(n2,n3,n4));
		grafo[n2].adj.push_back(lado(n1,n3,n4));
	}
	return grafo;
}

int main(){
	vector<vertice> g = leer_grafo();
	g[1].print_adj();
	g[14].print_adj();

}