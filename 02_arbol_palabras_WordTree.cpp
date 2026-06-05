/*============================================================================
  EQUIPO NARANJA - ASIGNACION IV / ORANGE TEAM - ASSIGNMENT IV
  Ejercicio: Arbol de Palabras para Buscador (ABB) / Word Tree for Search Engine
  Lenguaje: C++ - Paradigma Orientado a Objetos (POO) / OOP
----------------------------------------------------------------------------
  ANALISIS DE COMPLEJIDAD ALGORITMICA / ALGORITHMIC TIME COMPLEXITY
  - insertar(p)          : O(h)  -> promedio O(log n), peor caso O(n)
  - sugerir() [inorden]  : O(n)  -> lista alfabetica de todas las palabras
  - buscar(p)            : O(h)  -> promedio O(log n), peor caso O(n)
  - palabrasPorNivel()   : O(n)  -> recorre todo el arbol
  COMPLEJIDAD GENERAL    : insercion/busqueda = O(log n) promedio;
                           recorridos = O(n)
============================================================================*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int IDIOMA = 1; // 1 = Espanol, 2 = English
string t(const string& es, const string& en){ return IDIOMA == 1 ? es : en; }

// Nodo con una palabra clave / Node holding a keyword
class NodoP {
public:
    string palabra;
    NodoP* izq;
    NodoP* der;
    NodoP(string p) : palabra(p), izq(nullptr), der(nullptr) {}
};

// ABB de palabras / Word BST
class ArbolPalabras {
private:
    NodoP* raiz;

    NodoP* insertar(NodoP* n, string p){          // O(h)
        if(n == nullptr) return new NodoP(p);
        if(p < n->palabra)      n->izq = insertar(n->izq, p);
        else if(p > n->palabra) n->der = insertar(n->der, p);
        return n; // duplicados ignorados / duplicates ignored
    }

    void inorden(NodoP* n){                        // O(n)
        if(n == nullptr) return;
        inorden(n->izq);
        cout << n->palabra << " ";
        inorden(n->der);
    }

    bool buscar(NodoP* n, const string& p){        // O(h)
        if(n == nullptr) return false;
        if(p == n->palabra) return true;
        if(p < n->palabra)  return buscar(n->izq, p);
        return buscar(n->der, p);
    }

    int altura(NodoP* n){                          // O(n)
        if(n == nullptr) return 0;
        return 1 + max(altura(n->izq), altura(n->der));
    }

    void contarNivel(NodoP* n, int nivel, int conteo[]){ // O(n)
        if(n == nullptr) return;
        conteo[nivel]++;
        contarNivel(n->izq, nivel + 1, conteo);
        contarNivel(n->der, nivel + 1, conteo);
    }

public:
    ArbolPalabras() : raiz(nullptr) {}
    void insertar(string p){ raiz = insertar(raiz, p); }
    void sugerir(){ inorden(raiz); cout << endl; }
    bool buscar(string p){ return buscar(raiz, p); }

    void palabrasPorNivel(){
        int h = altura(raiz);
        if(h == 0){ cout << t("(arbol vacio)", "(empty tree)") << endl; return; }
        int* conteo = new int[h]();
        contarNivel(raiz, 0, conteo);
        for(int i = 0; i < h; i++){
            cout << t("Nivel ", "Level ") << i << ": "
                 << conteo[i] << t(" palabra(s)", " word(s)") << endl;
        }
        delete[] conteo;
    }
};

int main(){
    cout << "Seleccione idioma / Select language:\n";
    cout << "1) Espanol\n2) English\n> ";
    cin >> IDIOMA;
    if(IDIOMA != 2) IDIOMA = 1;

    ArbolPalabras arbol;

    // Palabras clave iniciales / initial keywords
    string iniciales[] = {"computadora","algoritmo","red","datos",
                          "programa","arbol","grafo","busqueda"};
    for(string w : iniciales) arbol.insertar(w);

    int op;
    do{
        cout << "\n=== " << t("ARBOL DE PALABRAS (BUSCADOR)",
                              "WORD TREE (SEARCH ENGINE)") << " ===\n";
        cout << "1) " << t("Insertar palabra", "Insert word") << "\n";
        cout << "2) " << t("Sugerir palabras (orden alfabetico)",
                           "Suggest words (alphabetical)") << "\n";
        cout << "3) " << t("Buscar coincidencia exacta", "Search exact match") << "\n";
        cout << "4) " << t("Mostrar palabras por nivel", "Show words per level") << "\n";
        cout << "0) " << t("Salir", "Exit") << "\n> ";
        cin >> op;

        if(op == 1){
            cout << t("Palabra (sin espacios): ", "Word (no spaces): ");
            string w; cin >> w; arbol.insertar(w);
            cout << t("Palabra insertada.", "Word inserted.") << endl;
        }
        else if(op == 2){
            cout << t("Sugerencias: ", "Suggestions: ");
            arbol.sugerir();
        }
        else if(op == 3){
            cout << t("Palabra a buscar: ", "Word to search: ");
            string w; cin >> w;
            cout << (arbol.buscar(w) ? t("ENCONTRADA", "FOUND")
                                     : t("NO encontrada", "NOT found")) << endl;
        }
        else if(op == 4){
            arbol.palabrasPorNivel();
        }
    } while(op != 0);

    return 0;
}
