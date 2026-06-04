// UAPA - Asignacion IV - Equipo Naranja
// Ejercicio 2: Arbol Binario de Busqueda (ABB) de Palabras
// Lenguaje: C++17
// Compilar: g++ -std=c++17 exercise2_word_tree.cpp -o programa
//
// Este programa construye un Arbol Binario de Busqueda (ABB) que almacena
// palabras. Puede sugerir palabras alfabeticamente, buscar palabras y contar
// palabras por nivel. Al iniciar, se precargan 10 palabras de ejemplo.

#include <iostream>
#include <string>
#include <queue>
#include <limits>

using namespace std;

// Nodo del Arbol Binario de Busqueda de palabras.
class NodoPalabra {
public:
    string palabra;        // Palabra almacenada en este nodo
    NodoPalabra* izquierdo;  // Puntero al hijo izquierdo (alfabeticamente menor)
    NodoPalabra* derecho;    // Puntero al hijo derecho (alfabeticamente mayor)

    NodoPalabra(string p) : palabra(p), izquierdo(nullptr), derecho(nullptr) {}
};

// Arbol Binario de Busqueda especializado en palabras.
class ArbolPalabras {
private:
    NodoPalabra* raiz;

    // Metodo auxiliar recursivo usado por el metodo publico insertar.
    NodoPalabra* insertarNodo(NodoPalabra* nodo, string palabra) {
        if (nodo == nullptr) {
            return new NodoPalabra(palabra);
        }
        if (palabra < nodo->palabra) {
            nodo->izquierdo = insertarNodo(nodo->izquierdo, palabra);
        } else if (palabra > nodo->palabra) {
            nodo->derecho = insertarNodo(nodo->derecho, palabra);
        }
        // Las palabras duplicadas se ignoran.
        return nodo;
    }

    // Metodo auxiliar recursivo para liberar memoria al terminar el programa.
    void destruir(NodoPalabra* nodo) {
        if (nodo == nullptr) return;
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }

public:
    ArbolPalabras() : raiz(nullptr) {}

    ~ArbolPalabras() {
        destruir(raiz);
    }

    // Inserta una palabra en el ABB.
    void insertar(string palabra) {
        raiz = insertarNodo(raiz, palabra);
        // Big-O: O(h) donde h es la altura del arbol.
        // Promedio: O(log n). Peor caso (arbol degenerado): O(n).
    }

    // Recorrido inorden: muestra las palabras en orden alfabetico (sugerencias).
    void inorden(NodoPalabra* nodo) {
        if (nodo == nullptr) return;
        inorden(nodo->izquierdo);
        cout << nodo->palabra << " ";
        inorden(nodo->derecho);
        // Big-O: O(n) - cada nodo se visita exactamente una vez.
    }

    // Busqueda exacta de una palabra. Retorna true si la encuentra, false si no.
    bool buscar(string palabra) {
        NodoPalabra* actual = raiz;
        while (actual != nullptr) {
            if (palabra == actual->palabra) return true;
            if (palabra < actual->palabra) {
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }
        return false;
        // Big-O: O(h) prom O(log n), peor caso (arbol degenerado) O(n).
    }

    // Cuenta cuantas palabras hay en cada nivel usando BFS con una cola.
    void contarPorNivel() {
        if (raiz == nullptr) {
            cout << "El arbol esta vacio.\n";
            return;
        }
        queue<NodoPalabra*> cola;
        cola.push(raiz);
        int nivel = 0;
        while (!cola.empty()) {
            int tamanioNivel = (int)cola.size();
            cout << "Nivel " << nivel << ": " << tamanioNivel << " palabra(s) -> ";
            for (int i = 0; i < tamanioNivel; i++) {
                NodoPalabra* actual = cola.front();
                cola.pop();
                cout << actual->palabra << " ";
                if (actual->izquierdo != nullptr) cola.push(actual->izquierdo);
                if (actual->derecho != nullptr) cola.push(actual->derecho);
            }
            cout << "\n";
            nivel++;
        }
        // Big-O: O(n) - cada nodo se encola y desencola exactamente una vez.
    }

    // Auxiliar para leer una sola palabra de forma segura desde el usuario.
    string leerPalabra() {
        string palabra;
        while (!(cin >> palabra)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Ingrese una palabra: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return palabra;
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
            cout << "\n===== MENU ABB DE PALABRAS =====\n";
            cout << "1. Insertar una palabra\n";
            cout << "2. Sugerir palabras (inorden alfabetico)\n";
            cout << "3. Buscar una palabra exacta\n";
            cout << "4. Ver palabras por nivel\n";
            cout << "5. Salir\n";
            cout << "Seleccione una opcion: ";

            opcion = leerEntero();

            switch (opcion) {
                case 1: {
                    cout << "Ingrese una palabra a insertar: ";
                    string palabra = leerPalabra();
                    insertar(palabra);
                    cout << "\"" << palabra << "\" se inserto correctamente.\n";
                    break;
                }
                case 2:
                    cout << "Palabras sugeridas (alfabetico): ";
                    inorden(raiz);
                    cout << "\n";
                    break;
                case 3: {
                    cout << "Ingrese una palabra a buscar: ";
                    string palabra = leerPalabra();
                    if (buscar(palabra)) {
                        cout << "\"" << palabra << "\" se encontro en el arbol.\n";
                    } else {
                        cout << "\"" << palabra << "\" NO se encontro en el arbol.\n";
                    }
                    break;
                }
                case 4:
                    contarPorNivel();
                    break;
                case 5:
                    cout << "\n===== RESUMEN DE COMPLEJIDAD DEL PROGRAMA =====\n";
                    cout << "insertar(palabra):  O(h) prom O(log n), peor O(n)\n";
                    cout << "inorden(nodo):      O(n)\n";
                    cout << "buscar(palabra):    O(h) prom O(log n), peor O(n)\n";
                    cout << "contarPorNivel():   O(n)\n";
                    cout << "Complejidad general del programa: O(n) por operacion de\n";
                    cout << "recorrido, dominada por los recorridos lineales sobre los n nodos.\n";
                    cout << "Saliendo del programa. Hasta luego!\n";
                    break;
                default:
                    cout << "Opcion invalida. Elija entre 1 y 5.\n";
                    break;
            }
        } while (opcion != 5);
        // Big-O: O(k * n) donde k es la cantidad de interacciones del menu.
    }
};

int main() {
    ArbolPalabras arbol;

    // Precargar 10 palabras de ejemplo al iniciar.
    string ejemplo[10] = {
        "mango", "manzana", "naranja", "banana", "uva",
        "limon", "cereza", "durazno", "kiwi", "ciruela"
    };
    for (int i = 0; i < 10; i++) {
        arbol.insertar(ejemplo[i]);
    }
    cout << "Se precargaron 10 palabras de ejemplo automaticamente.\n";

    arbol.mostrarMenu();
    return 0;
}
