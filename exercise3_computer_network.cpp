// UAPA - Asignacion IV - Equipo Naranja
// Ejercicio 3: Red de Computadoras como Grafo No Dirigido
// Lenguaje: C++17
// Compilar: g++ -std=c++17 exercise3_computer_network.cpp -o programa
//
// Este programa modela una red de computadoras como un grafo no dirigido
// usando una lista de adyacencia (map<string, vector<string>>). Puede simular
// la propagacion de una actualizacion usando BFS y calcular la distancia
// minima en saltos entre dos nodos. Al iniciar, se precargan 5 computadoras
// con conexiones de ejemplo.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <limits>

using namespace std;

// Grafo no dirigido que representa una red de computadoras.
class Grafo {
private:
    map<string, vector<string>> listaAdyacencia;  // Lista de adyacencia: nodo -> vecinos

public:
    // Agrega una computadora (vertice) a la red.
    void agregarComputadora(string nombre) {
        if (listaAdyacencia.find(nombre) == listaAdyacencia.end()) {
            listaAdyacencia[nombre] = vector<string>();
            cout << "Computadora \"" << nombre << "\" agregada.\n";
        } else {
            cout << "La computadora \"" << nombre << "\" ya existe.\n";
        }
        // Big-O: O(log V) por la busqueda en el map, donde V es el numero de computadoras.
    }

    // Agrega una conexion no dirigida entre dos computadoras.
    void agregarConexion(string a, string b) {
        if (a == b) {
            cout << "Una computadora no puede conectarse consigo misma.\n";
            return;
        }
        // Asegurar que ambas computadoras existan.
        if (listaAdyacencia.find(a) == listaAdyacencia.end()) listaAdyacencia[a] = vector<string>();
        if (listaAdyacencia.find(b) == listaAdyacencia.end()) listaAdyacencia[b] = vector<string>();

        // Evitar aristas duplicadas.
        for (const string& vecino : listaAdyacencia[a]) {
            if (vecino == b) {
                cout << "La conexion ya existe.\n";
                return;
            }
        }
        listaAdyacencia[a].push_back(b);
        listaAdyacencia[b].push_back(a);  // No dirigido: la conexion va en ambos sentidos.
        cout << "Conectadas \"" << a << "\" <-> \"" << b << "\".\n";
        // Big-O: O(log V + grado) por las busquedas y la verificacion de duplicados.
    }

    // Muestra la lista de adyacencia completa.
    void mostrarConexiones() {
        if (listaAdyacencia.empty()) {
            cout << "La red esta vacia.\n";
            return;
        }
        cout << "----- CONEXIONES DE LA RED -----\n";
        for (const auto& par : listaAdyacencia) {
            cout << par.first << " -> ";
            for (const string& vecino : par.second) {
                cout << vecino << " ";
            }
            cout << "\n";
        }
        // Big-O: O(V + E) - visita cada vertice y cada arista.
    }

    // BFS desde una computadora inicial para simular la propagacion de una actualizacion.
    void bfsActualizacion(string inicio) {
        if (listaAdyacencia.find(inicio) == listaAdyacencia.end()) {
            cout << "La computadora \"" << inicio << "\" no existe.\n";
            return;
        }
        set<string> visitados;
        queue<string> cola;
        cola.push(inicio);
        visitados.insert(inicio);

        cout << "Orden de propagacion de la actualizacion desde \"" << inicio << "\": ";
        while (!cola.empty()) {
            string actual = cola.front();
            cola.pop();
            cout << actual << " ";
            for (const string& vecino : listaAdyacencia[actual]) {
                if (visitados.find(vecino) == visitados.end()) {
                    visitados.insert(vecino);
                    cola.push(vecino);
                }
            }
        }
        cout << "\n";
        // Big-O: O(V + E) - BFS estandar sobre el grafo.
    }

    // Calcula la distancia minima en saltos entre dos computadoras usando BFS.
    int bfsDistancia(string origen, string destino) {
        if (listaAdyacencia.find(origen) == listaAdyacencia.end() ||
            listaAdyacencia.find(destino) == listaAdyacencia.end()) {
            return -1;  // Una de las computadoras no existe.
        }
        if (origen == destino) return 0;

        map<string, int> distancia;
        queue<string> cola;
        cola.push(origen);
        distancia[origen] = 0;

        while (!cola.empty()) {
            string actual = cola.front();
            cola.pop();
            for (const string& vecino : listaAdyacencia[actual]) {
                if (distancia.find(vecino) == distancia.end()) {
                    distancia[vecino] = distancia[actual] + 1;
                    if (vecino == destino) return distancia[vecino];
                    cola.push(vecino);
                }
            }
        }
        return -1;  // No se encontro camino.
        // Big-O: O(V + E) - BFS estandar sobre el grafo.
    }

    // Auxiliar para leer un solo token (sin espacios) de forma segura.
    string leerToken() {
        string token;
        while (!(cin >> token)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un valor: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return token;
    }

    // Auxiliar para leer un entero de forma segura desde el usuario.
    int leerEntero() {
        int valor;
        while (!(cin >> valor)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese un numero entero valido: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return valor;
    }

    // Menu interactivo de consola.
    void mostrarMenu() {
        int opcion = 0;
        do {
            cout << "\n===== MENU RED DE COMPUTADORAS =====\n";
            cout << "1. Agregar una computadora\n";
            cout << "2. Conectar dos computadoras\n";
            cout << "3. Mostrar todas las conexiones\n";
            cout << "4. Simular propagacion de actualizacion (BFS)\n";
            cout << "5. Calcular distancia minima entre dos nodos\n";
            cout << "6. Salir\n";
            cout << "Seleccione una opcion: ";

            opcion = leerEntero();

            switch (opcion) {
                case 1: {
                    cout << "Ingrese el nombre de la computadora: ";
                    string nombre = leerToken();
                    agregarComputadora(nombre);
                    break;
                }
                case 2: {
                    cout << "Ingrese el nombre de la primera computadora: ";
                    string a = leerToken();
                    cout << "Ingrese el nombre de la segunda computadora: ";
                    string b = leerToken();
                    agregarConexion(a, b);
                    break;
                }
                case 3:
                    mostrarConexiones();
                    break;
                case 4: {
                    cout << "Ingrese el nombre de la computadora inicial: ";
                    string inicio = leerToken();
                    bfsActualizacion(inicio);
                    break;
                }
                case 5: {
                    cout << "Ingrese el nombre de la computadora origen: ";
                    string origen = leerToken();
                    cout << "Ingrese el nombre de la computadora destino: ";
                    string destino = leerToken();
                    int distancia = bfsDistancia(origen, destino);
                    if (distancia == -1) {
                        cout << "No hay camino entre esas computadoras (o no existen).\n";
                    } else {
                        cout << "Distancia minima: " << distancia << " salto(s).\n";
                    }
                    break;
                }
                case 6:
                    cout << "\n===== RESUMEN DE COMPLEJIDAD DEL PROGRAMA =====\n";
                    cout << "agregarComputadora(nombre):  O(log V)\n";
                    cout << "agregarConexion(a, b):       O(log V + grado)\n";
                    cout << "mostrarConexiones():         O(V + E)\n";
                    cout << "bfsActualizacion(inicio):    O(V + E)\n";
                    cout << "bfsDistancia(origen, dest):  O(V + E)\n";
                    cout << "Complejidad general del programa: O(V + E) por operacion de\n";
                    cout << "recorrido, el costo estandar de BFS sobre un grafo con lista de adyacencia.\n";
                    cout << "Saliendo del programa. Hasta luego!\n";
                    break;
                default:
                    cout << "Opcion invalida. Elija entre 1 y 6.\n";
                    break;
            }
        } while (opcion != 6);
        // Big-O: O(k * (V + E)) donde k es la cantidad de interacciones del menu.
    }
};

int main() {
    Grafo red;

    // Precargar 5 computadoras con conexiones de ejemplo.
    red.agregarConexion("PC1", "PC2");
    red.agregarConexion("PC1", "PC3");
    red.agregarConexion("PC2", "PC4");
    red.agregarConexion("PC3", "PC4");
    red.agregarConexion("PC4", "PC5");
    cout << "Se precargo una red de ejemplo con 5 computadoras.\n";

    red.mostrarMenu();
    return 0;
}
