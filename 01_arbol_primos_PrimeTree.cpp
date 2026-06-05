/*============================================================================
  EQUIPO NARANJA - ASIGNACION IV / ORANGE TEAM - ASSIGNMENT IV
  Ejercicio: Arbol de Numeros Primos (ABB)  /  Prime Number Tree (BST)
  Lenguaje: C++ - Paradigma Orientado a Objetos (POO) / OOP
----------------------------------------------------------------------------
  ANALISIS DE COMPLEJIDAD ALGORITMICA / ALGORITHMIC TIME COMPLEXITY
  - insertar(v)        : O(h)  -> promedio O(log n), peor caso O(n)
  - mostrarInorden()   : O(n)  -> visita cada nodo una vez
  - hojas()            : O(n)  -> recorre todo el arbol
  - altura()           : O(n)  -> recorre todo el arbol
  COMPLEJIDAD GENERAL  : construir el arbol = O(n log n) promedio;
                         consultas (recorridos) = O(n)
============================================================================*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int IDIOMA = 1; // 1 = Espanol, 2 = English
string t(const string& es, const string& en){ return IDIOMA == 1 ? es : en; }

// Nodo del arbol / Tree node
class Nodo {
public:
    int valor;
    Nodo* izq;
    Nodo* der;
    Nodo(int v) : valor(v), izq(nullptr), der(nullptr) {}
};

// Arbol Binario de Busqueda de primos / Binary Search Tree of primes
class ArbolPrimos {
private:
    Nodo* raiz;

    // Insercion recursiva / Recursive insertion -- O(h)
    Nodo* insertar(Nodo* nodo, int v){
        if(nodo == nullptr) return new Nodo(v);
        if(v < nodo->valor)      nodo->izq = insertar(nodo->izq, v);
        else if(v > nodo->valor) nodo->der = insertar(nodo->der, v);
        return nodo; // se ignoran duplicados / duplicates ignored
    }

    // Recorrido inorden (orden ascendente) / Inorder traversal -- O(n)
    void inorden(Nodo* nodo){
        if(nodo == nullptr) return;
        inorden(nodo->izq);
        cout << nodo->valor << " ";
        inorden(nodo->der);
    }

    // Conteo de hojas / Count leaf nodes -- O(n)
    int contarHojas(Nodo* nodo){
        if(nodo == nullptr) return 0;
        if(nodo->izq == nullptr && nodo->der == nullptr) return 1;
        return contarHojas(nodo->izq) + contarHojas(nodo->der);
    }

    // Altura del arbol (en numero de niveles) / Tree height -- O(n)
    int altura(Nodo* nodo){
        if(nodo == nullptr) return 0;
        return 1 + max(altura(nodo->izq), altura(nodo->der));
    }

public:
    ArbolPrimos() : raiz(nullptr) {}
    void insertar(int v){ raiz = insertar(raiz, v); }
    void mostrarInorden(){ inorden(raiz); cout << endl; }
    int hojas(){ return contarHojas(raiz); }
    int altura(){ return altura(raiz); }
};

int main(){
    cout << "Seleccione idioma / Select language:\n";
    cout << "1) Espanol\n2) English\n> ";
    cin >> IDIOMA;
    if(IDIOMA != 2) IDIOMA = 1;

    ArbolPrimos arbol;

    /* Primeros 15 numeros primos. Se insertan en un orden que produce un
       arbol balanceado, de modo que la altura y el numero de hojas sean
       representativos. El inorden siempre los devuelve ordenados.
       First 15 primes inserted in a balanced order; inorder still returns
       them sorted. */
    int primos[] = {19,7,37,3,13,29,43,2,5,11,17,23,31,41,47};
    for(int p : primos) arbol.insertar(p);

    cout << "\n=== " << t("ARBOL DE NUMEROS PRIMOS (ABB)",
                          "PRIME NUMBER TREE (BST)") << " ===\n";

    cout << t("a) Primos en inorden: ", "a) Primes in inorder: ");
    arbol.mostrarInorden();

    cout << t("b) Numero de hojas: ", "b) Number of leaf nodes: ")
         << arbol.hojas() << endl;

    cout << t("c) Altura del arbol (niveles): ", "c) Height of the tree (levels): ")
         << arbol.altura() << endl;

    return 0;
}
