// UAPA - Asignacion IV - Equipo Naranja
// Ejercicio 1: Arbol Binario de Busqueda (ABB) de Numeros Primos
// Lenguaje: C++17
// Compilar: g++ -std=c++17 exercise1_prime_tree.cpp -o programa
//
// Este programa construye un Arbol Binario de Busqueda (ABB) que almacena
// numeros primos. Al iniciar, los primeros 15 numeros primos se insertan
// de forma automatica. El usuario interactua mediante un menu de consola.

#include <iostream>
#include <limits>

using namespace std;

// Nodo del Arbol Binario de Busqueda.
class Nodo {
public:
    int valor;        // Numero primo almacenado en este nodo
    Nodo* izquierdo;  // Puntero al hijo izquierdo (valores menores)
    Nodo* derecho;    // Puntero al hijo derecho (valores mayores)

    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
};

// Arbol Binario de Busqueda especializado en numeros primos.
class ArbolPrimos {
private:
    Nodo* raiz;

    // Metodo auxiliar recursivo usado por el metodo publico insertar.
    Nodo* insertarNodo(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }
        if (valor < nodo->valor) {
            nodo->izquierdo = insertarNodo(nodo->izquierdo, valor);
        } else if (valor > nodo->valor) {
            nodo->derecho = insertarNodo(nodo->derecho, valor);
        }
        // Los duplicados se ignoran para mantener limpio el ABB.
        return nodo;
    }

    // Metodo auxiliar recursivo para liberar memoria al terminar el programa.
    void destruir(Nodo* nodo) {
        if (nodo == nullptr) return;
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }

public:
    ArbolPrimos() : raiz(nullptr) {}

    ~ArbolPrimos() {
        destruir(raiz);
    }

    // Verifica si un numero es primo.
    bool esPrimo(int n) {
        if (n < 2) return false;
        for (int i = 2; (long long)i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
        // Big-O: O(sqrt(n)) - prueba divisores hasta la raiz cuadrada de n.
    }

    // Genera e inserta automaticamente los primeros 15 numeros primos.
    void generarPrimeros15Primos() {
        int cantidad = 0;
        int candidato = 2;
        while (cantidad < 15) {
            if (esPrimo(candidato)) {
                insertar(candidato);
                cantidad++;
            }
            candidato++;
        }
        // Big-O: O(p * sqrt(p)) donde p es el primo mas grande alcanzado,
        // porque cada candidato ejecuta una prueba de primalidad O(sqrt(n)).
    }

    // Metodo publico que inserta un valor en el ABB.
    void insertar(int valor) {
        raiz = insertarNodo(raiz, valor);
        // Big-O: O(h) donde h es la altura del arbol.
        // Promedio: O(log n). Peor caso (arbol degenerado): O(n).
    }

    // Recorrido inorden: muestra los primos en orden ascendente.
    void inorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        inorden(nodo->izquierdo);
        cout << nodo->valor << " ";
        inorden(nodo->derecho);
        // Big-O: O(n) - cada nodo se visita exactamente una vez.
    }

    // Cuenta la cantidad de nodos hoja (nodos sin hijos).
    int contarHojas(Nodo* nodo) {
        if (nodo == nullptr) return 0;
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) return 1;
        return contarHojas(nodo->izquierdo) + contarHojas(nodo->derecho);
        // Big-O: O(n) - cada nodo se visita exactamente una vez.
    }

    // Calcula la altura del arbol (nodos en el camino mas largo).
    int altura(Nodo* nodo) {
        if (nodo == nullptr) return 0;
        int alturaIzquierda = altura(nodo->izquierdo);
        int alturaDerecha = altura(nodo->derecho);
        return 1 + (alturaIzquierda > alturaDerecha ? alturaIzquierda : alturaDerecha);
        // Big-O: O(n) - cada nodo se visita exactamente una vez.
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
            cout << "\n===== MENU ABB DE NUMEROS PRIMOS =====\n";
            cout << "1. Mostrar primos en inorden (ascendente)\n";
            cout << "2. Contar nodos hoja\n";
            cout << "3. Ver altura del arbol\n";
            cout << "4. Insertar un numero primo manualmente\n";
            cout << "5. Salir\n";
            cout << "Seleccione una opcion: ";

            opcion = leerEntero();

            switch (opcion) {
                case 1:
                    cout << "Primos en orden ascendente: ";
                    inorden(raiz);
                    cout << "\n";
                    break;
                case 2:
                    cout << "Cantidad de nodos hoja: " << contarHojas(raiz) << "\n";
                    break;
                case 3:
                    cout << "Altura del arbol: " << altura(raiz) << "\n";
                    break;
                case 4: {
                    cout << "Ingrese un numero primo a insertar: ";
                    int numero = leerEntero();
                    if (esPrimo(numero)) {
                        insertar(numero);
                        cout << numero << " se inserto correctamente.\n";
                    } else {
                        cout << numero << " no es un numero primo. Insercion rechazada.\n";
                    }
                    break;
                }
                case 5:
                    cout << "\n===== RESUMEN DE COMPLEJIDAD DEL PROGRAMA =====\n";
                    cout << "esPrimo(n):                O(sqrt(n))\n";
                    cout << "generarPrimeros15Primos(): O(p * sqrt(p))\n";
                    cout << "insertar(valor):           O(h) prom O(log n), peor O(n)\n";
                    cout << "inorden(nodo):             O(n)\n";
                    cout << "contarHojas(nodo):         O(n)\n";
                    cout << "altura(nodo):              O(n)\n";
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
    ArbolPrimos arbol;
    arbol.generarPrimeros15Primos();  // Los primeros 15 primos listos al iniciar.
    cout << "Los primeros 15 numeros primos se insertaron automaticamente.\n";
    arbol.mostrarMenu();
    return 0;
}
