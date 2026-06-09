/*============================================================================
  EQUIPO NARANJA / ORANGE TEAM (Team #3) - ASIGNACION V / ASSIGNMENT V
  Ejercicio: Ranking de Competencia / Competition Ranking
  Tema: Algoritmos de busqueda, ordenamiento y recursividad
        Search, sorting and recursive algorithms
  Lenguaje: C++ - Paradigma Orientado a Objetos (POO) / OOP
----------------------------------------------------------------------------
  ANALISIS DE COMPLEJIDAD ALGORITMICA / ALGORITHMIC TIME COMPLEXITY
  n = numero de participantes / number of participants
  - agregar(n,p)          : O(1)    -> insercion al final del vector
  - ordenarPorPuntaje()   : O(n^2)  -> Selection Sort (descendente)
  - buscarPorNombre(n)    : O(n)    -> busqueda lineal
  - promedio() [recursivo]: O(n)    -> suma recursiva de n puntajes
  - mostrar()             : O(n)    -> recorre la lista
  COMPLEJIDAD GENERAL     : O(n^2)  -> dominada por el ordenamiento
============================================================================*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

int IDIOMA = 1; // 1 = Espanol, 2 = English
string t(const string& es, const string& en){ return IDIOMA == 1 ? es : en; }

// Limpia el buffer de entrada / clears the input buffer (OnlineGDB safe)
void limpiarBuffer(){ cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

// a) Clase Participante / Participant class
class Participante {
public:
    string nombre;
    double puntaje;
    Participante(string n = "", double p = 0) : nombre(n), puntaje(p) {}
};

// Sistema de ranking / Ranking system
class Ranking {
private:
    vector<Participante> lista;

    // d) Suma recursiva de puntajes / recursive sum of scores -- O(n)
    double sumaRecursiva(int i){
        if(i >= (int)lista.size()) return 0;        // caso base / base case
        return lista[i].puntaje + sumaRecursiva(i + 1);
    }

public:
    // Registrar participante / register participant -- O(1)
    void agregar(const string& n, double p){
        lista.push_back(Participante(n, p));
    }

    // b) Ordenar por puntaje de mayor a menor (Selection Sort) -- O(n^2)
    void ordenarPorPuntaje(){
        int n = lista.size();
        for(int i = 0; i < n - 1; i++){
            int mayor = i;
            for(int j = i + 1; j < n; j++)
                if(lista[j].puntaje > lista[mayor].puntaje) mayor = j;
            if(mayor != i) swap(lista[i], lista[mayor]);
        }
    }

    // c) Buscar participante por nombre (busqueda lineal) -- O(n)
    int buscarPorNombre(const string& n){
        for(int i = 0; i < (int)lista.size(); i++)
            if(lista[i].nombre == n) return i;
        return -1; // no encontrado / not found
    }

    // d) Promedio usando suma recursiva / average via recursion -- O(n)
    double promedio(){
        if(lista.empty()) return 0;
        return sumaRecursiva(0) / lista.size();
    }

    // Mostrar el ranking / display the ranking -- O(n)
    void mostrar(){
        if(lista.empty()){
            cout << t("(sin participantes)", "(no participants)") << endl;
            return;
        }
        cout << t("--- Ranking de participantes ---",
                  "--- Participant ranking ---") << endl;
        for(int i = 0; i < (int)lista.size(); i++)
            cout << i + 1 << ". " << lista[i].nombre
                 << " - " << lista[i].puntaje << endl;
    }

    Participante obtener(int i){ return lista[i]; }
};

int main(){
    cout << "Seleccione idioma / Select language:\n";
    cout << "1) Espanol\n2) English\n> ";
    cin >> IDIOMA;
    if(IDIOMA != 2) IDIOMA = 1;

    Ranking ranking;
    // Participantes iniciales / initial participants
    ranking.agregar("Ana", 85);
    ranking.agregar("Luis", 92);
    ranking.agregar("Maria", 78);
    ranking.agregar("Carlos", 95);
    ranking.agregar("Sofia", 88);

    int op;
    do{
        cout << "\n=== " << t("RANKING DE COMPETENCIA", "COMPETITION RANKING") << " ===\n";
        cout << "1) " << t("Agregar participante", "Add participant") << "\n";
        cout << "2) " << t("Ordenar por puntaje (mayor a menor)",
                           "Sort by score (highest to lowest)") << "\n";
        cout << "3) " << t("Buscar participante por nombre",
                           "Search participant by name") << "\n";
        cout << "4) " << t("Calcular promedio (recursivo)",
                           "Calculate average (recursive)") << "\n";
        cout << "5) " << t("Mostrar ranking", "Show ranking") << "\n";
        cout << "0) " << t("Salir", "Exit") << "\n> ";
        cin >> op;

        if(op == 1){
            limpiarBuffer();
            cout << t("Nombre: ", "Name: ");
            string n; getline(cin, n);
            cout << t("Puntaje: ", "Score: ");
            double p; cin >> p;
            ranking.agregar(n, p);
            cout << t("Participante agregado.", "Participant added.") << endl;
        }
        else if(op == 2){
            ranking.ordenarPorPuntaje();
            cout << t("Ranking ordenado de mayor a menor.",
                      "Ranking sorted from highest to lowest.") << endl;
            ranking.mostrar();
        }
        else if(op == 3){
            limpiarBuffer();
            cout << t("Nombre a buscar: ", "Name to search: ");
            string n; getline(cin, n);
            int idx = ranking.buscarPorNombre(n);
            if(idx >= 0){
                Participante pp = ranking.obtener(idx);
                cout << t("Encontrado: ", "Found: ") << pp.nombre << " - " << pp.puntaje
                     << t(" (posicion ", " (position ") << idx + 1 << ")" << endl;
            } else {
                cout << t("Participante no encontrado.", "Participant not found.") << endl;
            }
        }
        else if(op == 4){
            cout << t("Promedio de puntajes: ", "Average score: ")
                 << ranking.promedio() << endl;
        }
        else if(op == 5){
            ranking.mostrar();
        }
    } while(op != 0);

    return 0;
}
