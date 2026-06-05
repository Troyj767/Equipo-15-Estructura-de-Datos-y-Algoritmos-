/*============================================================================
  EQUIPO NARANJA - ASIGNACION IV / ORANGE TEAM - ASSIGNMENT IV
  Ejercicio: Distribucion de Documentos en Red de Oficinas
             Document Distribution in an Office Network
  Lenguaje: C++ - Paradigma Orientado a Objetos (POO) / OOP
----------------------------------------------------------------------------
  ANALISIS DE COMPLEJIDAD ALGORITMICA / ALGORITHMIC TIME COMPLEXITY
  V = numero de oficinas (nodos), E = numero de rutas (aristas)
  - agregarConexion(a,b) : O(1)    -> insercion en lista de adyacencia
  - construccion (input) : O(E)    -> se leen E rutas
  - mostrarLista()       : O(V+E)  -> imprime todas las listas
  - bfsDistribucion(0)   : O(V+E)  -> recorrido BFS de entrega
  COMPLEJIDAD GENERAL    : O(V+E)
============================================================================*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int IDIOMA = 1; // 1 = Espanol, 2 = English
string t(const string& es, const string& en){ return IDIOMA == 1 ? es : en; }

// Grafo no dirigido de oficinas / Undirected office graph
class RedOficinas {
private:
    int numOficinas;
    vector<vector<int>> ady; // lista de adyacencia / adjacency list

public:
    RedOficinas(int n) : numOficinas(n), ady(n) {}

    // a) Conexion directa entre oficinas / direct route -- O(1)
    void agregarConexion(int a, int b){
        ady[a].push_back(b);
        ady[b].push_back(a); // ruta no dirigida / undirected route
    }

    // Mostrar lista de adyacencia / display adjacency list -- O(V+E)
    void mostrarLista(){
        cout << t("\n--- Lista de adyacencia ---\n",
                  "\n--- Adjacency list ---\n");
        for(int i = 0; i < numOficinas; i++){
            cout << t("Oficina ", "Office ") << i << ": ";
            for(int v : ady[i]) cout << v << " ";
            cout << endl;
        }
    }

    // b) BFS desde la oficina central (nodo 0) / BFS from central office -- O(V+E)
    void bfsDistribucion(int inicio){
        vector<bool> visit(numOficinas, false);
        queue<int> q;
        q.push(inicio); visit[inicio] = true;
        cout << t("Orden de entrega (BFS desde oficina ",
                  "Delivery order (BFS from office ") << inicio << "): ";
        while(!q.empty()){
            int u = q.front(); q.pop();
            cout << u << " ";
            for(int v : ady[u])
                if(!visit[v]){ visit[v] = true; q.push(v); }
        }
        cout << endl;
    }
};

int main(){
    cout << "Seleccione idioma / Select language:\n";
    cout << "1) Espanol\n2) English\n> ";
    cin >> IDIOMA;
    if(IDIOMA != 2) IDIOMA = 1;

    int n, m;
    cout << t("Numero de oficinas: ", "Number of offices: ");
    cin >> n;
    RedOficinas red(n);

    cout << t("Numero de conexiones (rutas): ", "Number of connections (routes): ");
    cin >> m;

    cout << t("Ingrese cada ruta como dos numeros de oficina (0 a ",
              "Enter each route as two office numbers (0 to ")
         << n - 1 << "):\n";

    for(int i = 0; i < m; i++){
        int a, b;
        cout << t("Ruta ", "Route ") << i + 1 << ": ";
        cin >> a >> b;
        if(a >= 0 && a < n && b >= 0 && b < n){
            red.agregarConexion(a, b);
        } else {
            cout << t("Oficina invalida, intente de nuevo.",
                      "Invalid office, please try again.") << endl;
            i--; // repetir esta ruta / retry this route
        }
    }

    red.mostrarLista();
    red.bfsDistribucion(0); // oficina central = nodo 0 / central office = node 0

    return 0;
}
