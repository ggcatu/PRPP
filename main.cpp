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

	El nodo 0 es basura
	El nodo 1 es el deposito

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
	public:
		vector<vertice> v;
		void resize(int n){
			v.resize(n);
		}

		void enumerar(){
			int n = 0;
			for (vector<vertice>::iterator it = v.begin(); it != v.end(); ++it){
				it->index = n++;
			}
		}

		void agregar_lado(int nodo, lado r){
			v[nodo].adj.push_back(r);
		}
		
		void dfs_rec(vertice * r, vector<int> * ac){
			ac->push_back(r->index);
			//cout << "Index: " << r->index << endl;
			r->conex = true;
			for (vector<lado>::iterator it = r->adj.begin(); it != r->adj.end(); ++it){
				//cout << "Accediendo: " << it->vertex << endl;
				if (!v[it->vertex].conex){
					dfs_rec(&v[it->vertex], ac);
				}
			}
		}

		void dfs(){
			vector< vector<int> > cc;
			vector<int> tmp;
			for (vector<vertice>::iterator it = v.begin(); it != v.end(); ++it){
				if (!it->conex){
					tmp.clear();
					dfs_rec(&(*it), &tmp);
					cc.push_back(tmp);
					for (vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it){
						cout << *it << " " ;
					}
					cout << endl;
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

grafo leer_grafo(){
	int nodos, ladosR, ladosE;
	int n1,n2,n3,n4;
	grafo g;
	
	nodos = obtener_numero();
	cout << "Numero de nodos: " << nodos << endl;
	ladosR = obtener_numero();
	cout << ladosR << endl;

	g.resize(nodos+1);
	g.enumerar();
	for(int i = 0; i < ladosR; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		g.agregar_lado(n1,lado(n2,n3,n4));
		g.agregar_lado(n2,lado(n1,n3,n4));
	}
	g.dfs();
	// Hay que buscar las componentes conexas en el grafo hasta este punto.

	ladosE = obtener_numero();
	for(int i = 0; i < ladosE; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		g.agregar_lado(n1,lado(n2,n3,n4));
		g.agregar_lado(n2,lado(n1,n3,n4));
	}
	return g;
}

int main(){
	grafo g = leer_grafo();

}