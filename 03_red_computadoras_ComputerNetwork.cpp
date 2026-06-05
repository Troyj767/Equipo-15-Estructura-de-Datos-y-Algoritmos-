/*============================================================================
  EQUIPO NARANJA - ASIGNACION IV / ORANGE TEAM - ASSIGNMENT IV
  Ejercicio: Red de Computadoras (grafo no dirigido) / Computer Network
  Lenguaje: C++ - Paradigma Orientado a Objetos (POO) / OOP
----------------------------------------------------------------------------
  ANALISIS DE COMPLEJIDAD ALGORITMICA / ALGORITHMIC TIME COMPLEXITY
  V = numero de nodos (vertices), E = numero de aristas (conexiones)
  - conectar(a,b)        : O(1)    -> insercion en lista de adyacencia
  - propagar(inicio)     : O(V+E)  -> recorrido BFS completo
  - saltosMinimos(o,d)   : O(V+E)  -> BFS calcula distancia minima
  COMPLEJIDAD GENERAL    : O(V+E) por cada operacion de recorrido
============================================================================*/
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

int IDIOMA = 1; // 1 = Espanol, 2 = English
string t(const string& es, const string& en){ return IDIOMA == 1 ? es : en; }

// Grafo no dirigido con lista de adyacencia / Undirected graph (adjacency list)
class RedComputadoras {
private:
    map<int, vector<int>> ady;

public:
    // a) Conexion entre computadoras / Connection between computers -- O(1)
    void conectar(int a, int b){
        ady[a].push_back(b);
        ady[b].push_back(a); // no dirigido / undirected
    }

    // b) BFS de propagacion de actualizacion / update propagation -- O(V+E)
    void propagar(int inicio){
        map<int,bool> visit;
        queue<int> q;
        q.push(inicio); visit[inicio] = true;
        cout << t("Orden de propagacion: ", "Propagation order: ");
        while(!q.empty()){
            int u = q.front(); q.pop();
            cout << u << " ";
            for(int v : ady[u])
                if(!visit[v]){ visit[v] = true; q.push(v); }
        }
        cout << endl;
    }

    // c) Saltos minimos entre dos nodos / minimum hops (BFS distance) -- O(V+E)
    int saltosMinimos(int origen, int destino){
        map<int,int> dist;
        map<int,bool> visit;
        queue<int> q;
        q.push(origen); visit[origen] = true; dist[origen] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(u == destino) return dist[u];
            for(int v : ady[u])
                if(!visit[v]){ visit[v] = true; dist[v] = dist[u] + 1; q.push(v); }
        }
        return -1; // sin conexion / no path
    }
};

int main(){
    cout << "Seleccione idioma / Select language:\n";
    cout << "1) Espanol\n2) English\n> ";
    cin >> IDIOMA;
    if(IDIOMA != 2) IDIOMA = 1;

    RedComputadoras red;

    // Conexiones de ejemplo / sample connections
    red.conectar(0,1); red.conectar(0,2);
    red.conectar(1,3); red.conectar(2,3);
    red.conectar(3,4);

    int op;
    do{
        cout << "\n=== " << t("RED DE COMPUTADORAS", "COMPUTER NETWORK") << " ===\n";
        cout << "1) " << t("Conectar dos computadoras", "Connect two computers") << "\n";
        cout << "2) " << t("Propagar actualizacion (BFS)", "Propagate update (BFS)") << "\n";
        cout << "3) " << t("Saltos minimos entre dos nodos",
                           "Minimum hops between two nodes") << "\n";
        cout << "0) " << t("Salir", "Exit") << "\n> ";
        cin >> op;

        if(op == 1){
            int a, b;
            cout << t("Nodo A: ", "Node A: "); cin >> a;
            cout << t("Nodo B: ", "Node B: "); cin >> b;
            red.conectar(a, b);
            cout << t("Computadoras conectadas.", "Computers connected.") << endl;
        }
        else if(op == 2){
            int s; cout << t("Nodo de inicio: ", "Start node: "); cin >> s;
            red.propagar(s);
        }
        else if(op == 3){
            int a, b;
            cout << t("Origen: ", "Source: ");  cin >> a;
            cout << t("Destino: ", "Target: "); cin >> b;
            int d = red.saltosMinimos(a, b);
            if(d < 0) cout << t("No hay conexion entre los nodos.",
                                "No connection between nodes.") << endl;
            else      cout << t("Saltos minimos: ", "Minimum hops: ") << d << endl;
        }
    } while(op != 0);

    return 0;
}
