#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

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

	| Faltaria implementar clase Componente
	| En dfs revisar quien es el ultimo
	| Componente.recorrer();
*/
#define INF numeric_limits<int>::infinity();
#define INFI 80000000

class componente {
	public:
		int ultimo;
		int ganancia;
		bool conectada;
		vector<int> elems;
		vector<int> costos;
		componente() : ganancia(0), ultimo(0), conectada(false) {};
	
	void print(){
		for(vector<int>::iterator it = elems.begin(); it != elems.end(); ++it)
			{ cout << *it << " " ; if (*it == ultimo) break;}
		cout << endl;
		calcular();
		cout << "Ultimo en componente: " << ultimo << endl;
	}

	void calcular(){
		ganancia = 0;
		int i = 0;
		cout << "Sumatoria: " << endl;
		for(vector<int>::iterator it = elems.begin(); it != elems.end(); ++it){ 
			if (*it == ultimo) break;
			cout << costos.at(i) << " ";
			ganancia += costos.at(i);
			i++;
		}
		ganancia = ganancia * -1;
		cout << endl <<  "Ganancia de componente : " << ganancia << endl;
	}

	bool buscar(int r){
		vector<int>::iterator it;
  		it = find (elems.begin(), elems.end(), r);
		if (it != elems.end())
		   return true;
		else
		   return false;
	}

	void agregar(int r){
		if (!buscar(r)){
			ultimo = r;
		}
		elems.push_back(r);
	}

	void agregar_costo(int costo){
		costos.push_back(costo);
	}

};

class lado {
	public:
		int vertex;
		int costo;
		int win;
		int * veces;
		lado(int v, int c, int w) : vertex(v), costo(c), win(w){
			veces = new int(0);
		};
	
	int get_costo(){
		if ( !(*veces) ){
			return -(win - costo);
		}	
		else
			return  costo;
	}

};

class vertice{
	public:
		int index, distancia;
		bool conex;
		vertice * padre;
		vector<lado> adj;
		vertice() : conex(0){ padre = NULL;};
		vertice(int i) : conex(0), index(i){ padre = NULL;};

		void print_adj(){
			cout << " * " << endl;
			for (vector<lado>::iterator it = adj.begin(); it != adj.end(); ++it){
				cout << it->vertex << " " << it->costo << " * " ; 
			}
			cout << endl;
		}

		int return_path(vector<int> * ac){
			if (padre == NULL){
				ac->push_back(index);
				//cout << index << " ";
				return index;
			} else {
				padre->return_path(ac);
				ac->push_back(index);
				//cout << index << " ";
				return index;
			}
		}

		void limpiar(){
			conex = 0;
			padre = NULL;
			distancia = INFI;
		}
};

class compare
{
public:
    bool operator() (vertice * a, vertice * b)
    {

        return a->distancia > b->distancia;
    }
};

class grafo {
	public:
		vector<vertice> v;
		vector<componente> comps;
		vector<int> recorrido;
		int costo;

		grafo() : costo(0){};

		void resize(int n){
			v.resize(n);
		}

		void agregar_recorrido(vector<int> * r){
			vector<int>::iterator g;
			g = r->begin();
			if(!recorrido.empty()){
				g++;
			}
			recorrido.insert( recorrido.end(), g, r->end() );
		}

		void print_recorrido(){
			cout << "Recorrido completo: " <<endl;
			for (vector<int>::iterator it = recorrido.begin(); it != recorrido.end(); ++it){
				cout << *it << " ";
			}
			cout << endl;
		}

		void limpiar(){
			for (vector<vertice>::iterator it = v.begin(); it != v.end(); ++it){
				it->limpiar();
			}
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

		void print_componentes(){
			cout << " -> Imprimiendo componentes * " << endl;
			for (vector<componente>::iterator it = comps.begin(); it != comps.end(); ++it)
				{it->print(); cout << endl;}
			cout << " <- Fin componentes *" << endl;
		}
		
		lado * buscar_lado(int a, int b){
			vector<lado> * lista = &(v[a].adj);
			for (vector<lado>::iterator it = lista->begin(); it != lista->end(); ++it)
				{
					if(it->vertex == b) return &(*it);
				}
		}

		void dfs_rec(vertice * r, componente * ac){
			int tmp;
			ac->agregar(r->index);
			//cout << "Index: " << r->index << endl;
			r->conex = true;
			for (vector<lado>::iterator it = r->adj.begin(); it != r->adj.end(); ++it){
				//cout << "Accediendo: " << it->vertex << endl;
				if (!v[it->vertex].conex){
					//cout << "Agregando lado: " << r->index << " " << it->vertex << " Costos: " <<  it->win << " " << it->costo << endl;
 					ac->agregar_costo(it->get_costo());
					//(*it->veces)++;
					dfs_rec(&v[it->vertex], ac);
				}
				if(ac->elems.back() != r->index){
					ac->agregar_costo(it->get_costo());

					ac->agregar(r->index);
				}
			}
			
		}

		bool misma_componente(int a, int b){
			for (vector<componente>::iterator it = comps.begin(); it != comps.end(); ++it){
				if (it->buscar(a) && it->buscar(b)){
					return true;
				}
				else {
					return false;
				}
			}
		}

		componente * buscar_componente(int a){
			for (vector<componente>::iterator it = comps.begin(); it != comps.end(); ++it){
				if (it->buscar(a)){
					return &(*it);
				}
			}
		}

		void dfs(){
			componente tmp;
			for (vector<vertice>::iterator it = ++v.begin(); it != v.end(); ++it){
				if (!it->conex){
					tmp = componente();
					dfs_rec(&(*it), &tmp);
					comps.push_back(tmp);
				}
				
			}
		}

		int dijkstra(int fuente){
			int min = INFI;
			int g;
			vertice * vmin = NULL;
			vertice * r;
			vertice inicial = v[fuente];
			limpiar();
			(&inicial)->distancia = 0;
			priority_queue<vertice *, vector<vertice*>, compare> pq;
			pq.push(&inicial);
			// cout << " PRINT COL PRIOR" << endl;
			// while(!pq.empty()){
			// 	r = pq.top();
			// 	cout << r->index << " " ;
			// 	pq.pop();
			// }
			// cout << endl;
			
			while(!pq.empty()){
		
				vertice * u = pq.top();
				pq.pop();
				v[u->index].conex = true;
				u->conex=true;
				//cout << "Estoy en el vertice: " << u->index << endl;
				for (vector<lado>::iterator it = u->adj.begin(); it != u->adj.end(); ++it){
					r = &v[it->vertex];
					if (!r->conex && r->distancia > u->distancia + it->get_costo()){
						r->conex = true;
						r->distancia =  u->distancia + it->get_costo();
						if (r->distancia < min) {
							g = (vmin == NULL) ? 0 : vmin->index;
							if ( !misma_componente(g, r->index) && !buscar_componente(r->index)->conectada){
								vmin = r; min = r->distancia;
							}
						}
						//(*it->veces)++;
						//cout << "Nodo : "<< r->index << " Distancia: " << r->distancia << " Veces: " << *it->veces << " Agregando " << it->get_costo() << endl;
						r->padre = &v.at(u->index);
						//r->print_path();
						//cout << endl ;
						pq.push(r);
					}
				}
			}
			//cout << "Minimo " << endl;
			//cout << "Nodo : "<< vmin->index << " Distancia: " << vmin->distancia << endl;
 			vector<int> resultado;
			g = vmin->return_path(&resultado);
			//for ( vector<int>::iterator it = resultado.begin(); it != resultado.end(); ++it )
			//	cout << *it << " ";

			costo-=min;
			//cout << endl;
			recorrer(&resultado);
			buscar_componente(g)->conectada = true;

			return g;
		}

		void recorrer(vector<int> * ac){
			int r = -1;
			for ( vector<int>::iterator it = ac->begin(); it != ac->end(); ++it ){
				cout << *it << " ";
				if (r != -1){
					(*buscar_lado(r,*it)->veces)++ ;
				}
				r = *it;
			}
			cout << endl;
			agregar_recorrido(ac);
		}

		bool componentes_conectadas(){
			for (vector<componente>::iterator it = comps.begin(); it != comps.end(); ++it){
				if (!it->conectada) return false; 
			}
			return true;
		}

		void heuristica(){
			int comienzo = 1;
			while (!componentes_conectadas()){
				//cout << "Ejecutando Dijkstra con " << comienzo << endl;
				comienzo = dijkstra(comienzo);

				//cout << "##########################" << endl;
			}
			componente tmp;
			tmp.elems.push_back(1);
			comps.insert(comps.begin(), tmp);
			//comps.push_back(tmp);
			dijkstra(comienzo);
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
	grafo g,f;
	lado * temp1, * temp2;
	int * rtmp;
	
	nodos = obtener_numero();
	//cout << "Numero de nodos: " << nodos << endl;
	ladosR = obtener_numero();
	//cout << "Lados R: " << ladosR << endl;

	g.resize(nodos+1);
	g.enumerar();
	for(int i = 0; i < ladosR; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		temp1 = new lado(n2,n3,n4);
		temp2 = new lado(n1,n3,n4);
		temp1->veces = temp2->veces;
		g.agregar_lado(n1,*temp1);
		g.agregar_lado(n2,*temp2);
	}
	g.dfs();
	//g.print_componentes();

	ladosE = obtener_numero();
	for(int i = 0; i < ladosE; i++){
		cin >> n1 >> n2 >> n3 >> n4;
		temp1 = new lado(n2,n3,n4);
		temp2 = new lado(n1,n3,n4);
		temp1->veces = temp2->veces;
		g.agregar_lado(n1,*temp1);
		g.agregar_lado(n2,*temp2);
	}
	g.heuristica();
	//g.dijkstra(11);
	return g;
}

int main(){
	grafo g = leer_grafo();
	g.print_recorrido();
	cout << "Costo: " << g.costo << endl;
}