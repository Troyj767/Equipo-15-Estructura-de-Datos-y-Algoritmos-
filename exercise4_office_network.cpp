// UAPA - Asignacion IV - Equipo Naranja
// Ejercicio 4: Red de Oficinas como Grafo No Dirigido
// Lenguaje: C++17
// Compilar: g++ -std=c++17 exercise4_office_network.cpp -o programa
//
// Este programa modela una red de oficinas como un grafo no dirigido usando
// una lista de adyacencia indexada por enteros (vector<vector<int>>). Simula
// la distribucion de documentos desde la oficina central (nodo 0) usando BFS.
// Al iniciar, se precarga una red de ejemplo con 6 oficinas.

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Grafo no dirigido que representa una red de oficinas.
class GrafoOficinas {
private:
    int numOficinas;                       // Numero total de oficinas (vertices)
    vector<vector<int>> listaAdyacencia;   // Lista de adyacencia indexada por numero de oficina

public:
    GrafoOficinas() : numOficinas(0) {}

    // Define el numero de oficinas y reinicia la lista de adyacencia.
    void agregarOficina(int total) {
        if (total <= 0) {
            cout << "El numero de oficinas debe ser positivo.\n";
            return;
        }
        numOficinas = total;
        listaAdyacencia.assign(total, vector<int>());
        cout << "La red ahora tiene " << total << " oficina(s) (0 a "
             << total - 1 << ").\n";
        // Big-O: O(V) - asigna una lista por cada oficina.
    }

    // Agrega una ruta no dirigida entre dos oficinas.
    void agregarRuta(int a, int b) {
        if (a < 0 || b < 0 || a >= numOficinas || b >= numOficinas) {
            cout << "Indice de oficina invalido. El rango valido es 0 a "
                 << numOficinas - 1 << ".\n";
            return;
        }
        if (a == b) {
            cout << "Una oficina no puede conectarse consigo misma.\n";
            return;
        }
        // Evitar aristas duplicadas.
        for (int vecino : listaAdyacencia[a]) {
            if (vecino == b) {
                cout << "La ruta ya existe.\n";
                return;
            }
        }
        listaAdyacencia[a].push_back(b);
        listaAdyacencia[b].push_back(a);  // No dirigido: la ruta va en ambos sentidos.
        cout << "Ruta agregada entre la oficina " << a << " y la oficina " << b << ".\n";
        // Big-O: O(grado) por la verificacion de duplicados en la lista de adyacencia.
    }

    // Muestra la lista de adyacencia de la red de oficinas.
    void mostrarListaAdyacencia() {
        if (numOficinas == 0) {
            cout << "Aun no se han definido oficinas.\n";
            return;
        }
        cout << "----- LISTA DE ADYACENCIA DE OFICINAS -----\n";
        for (int i = 0; i < numOficinas; i++) {
            cout << "Oficina " << i << " -> ";
            for (int vecino : listaAdyacencia[i]) {
                cout << vecino << " ";
            }
            cout << "\n";
        }
        // Big-O: O(V + E) - visita cada oficina y cada ruta.
    }

    // BFS desde la oficina central (nodo 0) para mostrar el orden de entrega.
    void bfsEntrega(int inicio) {
        if (numOficinas == 0) {
            cout << "Aun no se han definido oficinas.\n";
            return;
        }
        if (inicio < 0 || inicio >= numOficinas) {
            cout << "Oficina inicial invalida.\n";
            return;
        }
        vector<bool> visitados(numOficinas, false);
        queue<int> cola;
        cola.push(inicio);
        visitados[inicio] = true;

        cout << "Orden de entrega de documentos desde la oficina " << inicio << ": ";
        while (!cola.empty()) {
            int actual = cola.front();
            cola.pop();
            cout << actual << " ";
            for (int vecino : listaAdyacencia[actual]) {
                if (!visitados[vecino]) {
                    visitados[vecino] = true;
                    cola.push(vecino);
                }
            }
        }
        cout << "\n";
        // Big-O: O(V + E) - BFS estandar sobre el grafo.
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
            cout << "\n===== MENU RED DE OFICINAS =====\n";
            cout << "1. Definir el numero de oficinas\n";
            cout << "2. Agregar una ruta entre oficinas\n";
            cout << "3. Mostrar la lista de adyacencia\n";
            cout << "4. Simular distribucion de documentos desde la oficina central (BFS desde 0)\n";
            cout << "5. Salir\n";
            cout << "Seleccione una opcion: ";

            opcion = leerEntero();

            switch (opcion) {
                case 1: {
                    cout << "Ingrese el numero total de oficinas: ";
                    int total = leerEntero();
                    agregarOficina(total);
                    break;
                }
                case 2: {
                    cout << "Ingrese el indice de la primera oficina: ";
                    int a = leerEntero();
                    cout << "Ingrese el indice de la segunda oficina: ";
                    int b = leerEntero();
                    agregarRuta(a, b);
                    break;
                }
                case 3:
                    mostrarListaAdyacencia();
                    break;
                case 4:
                    bfsEntrega(0);  // La oficina central siempre es el nodo 0.
                    break;
                case 5:
                    cout << "\n===== RESUMEN DE COMPLEJIDAD DEL PROGRAMA =====\n";
                    cout << "agregarOficina(total):       O(V)\n";
                    cout << "agregarRuta(a, b):           O(grado)\n";
                    cout << "mostrarListaAdyacencia():    O(V + E)\n";
                    cout << "bfsEntrega(0):               O(V + E)\n";
                    cout << "Complejidad general del programa: O(V + E) por operacion de\n";
                    cout << "recorrido, el costo estandar de BFS sobre un grafo con lista de adyacencia.\n";
                    cout << "Saliendo del programa. Hasta luego!\n";
                    break;
                default:
                    cout << "Opcion invalida. Elija entre 1 y 5.\n";
                    break;
            }
        } while (opcion != 5);
        // Big-O: O(k * (V + E)) donde k es la cantidad de interacciones del menu.
    }
};

int main() {
    GrafoOficinas red;

    // Precargar una red de ejemplo con 6 oficinas y algunas rutas.
    red.agregarOficina(6);
    red.agregarRuta(0, 1);
    red.agregarRuta(0, 2);
    red.agregarRuta(1, 3);
    red.agregarRuta(2, 4);
    red.agregarRuta(3, 5);
    red.agregarRuta(4, 5);
    cout << "Se precargo una red de ejemplo con 6 oficinas.\n";

    red.mostrarMenu();
    return 0;
}
