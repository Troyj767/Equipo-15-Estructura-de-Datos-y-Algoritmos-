/*============================================================================
  EQUIPO NARANJA (Equipo #15) - TRABAJO FINAL / FINAL PROJECT
  ISW-305 Estructura de Datos y Algoritmos
  Proyecto: "El arbol de los recuerdos" / "The Tree of Memories"
  Lenguaje: C++ - Paradigma Orientado a Objetos (POO) / OOP
  IDE: OnlineGDB / Dev-C++ / Visual Studio
----------------------------------------------------------------------------
  DESCRIPCION
  Sistema interactivo que organiza la historia familiar de Lucia mediante un
  ARBOL GENEALOGICO GENERAL (n-ario): cada persona puede tener varios hijos.
  Permite registrar familiares, mostrar las generaciones, buscar por nombre,
  ordenar descendientes por fecha de nacimiento y, mediante RECURSIVIDAD,
  contar generaciones, contar descendientes y listar hijos/nietos.
----------------------------------------------------------------------------
  ANALISIS DE COMPLEJIDAD ALGORITMICA / ALGORITHMIC TIME COMPLEXITY
  n = numero de personas en el arbol / number of people in the tree
  - establecerRaiz()              : O(1)
  - agregarPersona()              : O(n)    -> busca al padre en el arbol
  - buscarPorNombre()             : O(n)    -> recorrido (busqueda lineal)
  - mostrarJerarquia()            : O(n)    -> recorre todo el arbol
  - generaciones()  [recursivo]   : O(n)    -> altura del arbol
  - descendientesDeRaiz()[recurs.]: O(n)    -> cuenta todos los nodos
  - mostrarHijos() / mostrarNietos: O(n)    -> ubica persona + recorre hijos
  - ordenarDescendientesPorFecha(): O(n^2)  -> Insertion Sort
  COMPLEJIDAD GENERAL             : O(n^2)  -> dominada por el ordenamiento
============================================================================*/
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

int IDIOMA = 1; // 1 = Espanol, 2 = English
string t(const string& es, const string& en){ return IDIOMA == 1 ? es : en; }

// Limpia el buffer de entrada / clears the input buffer (OnlineGDB safe)
void limpiarBuffer(){ cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

// ---------------------------------------------------------------------------
// Clase Persona: nodo del arbol genealogico / Person: genealogical tree node
// ---------------------------------------------------------------------------
class Persona {
public:
    string nombre;
    string fechaNacimiento;      // formato AAAA-MM-DD / format YYYY-MM-DD
    string relacion;             // relacion familiar / family relationship
    vector<Persona*> hijos;      // descendientes directos / direct children

    Persona(string n, string f, string r)
        : nombre(n), fechaNacimiento(f), relacion(r) {}
};

// ---------------------------------------------------------------------------
// Clase ArbolFamiliar: gestiona el arbol genealogico / family tree manager
// ---------------------------------------------------------------------------
class ArbolFamiliar {
private:
    Persona* raiz;  // Lucia (matriarca) / Lucia (matriarch)

    // Busqueda recursiva por nombre / recursive search by name -- O(n)
    Persona* buscar(Persona* nodo, const string& nombre){
        if(nodo == nullptr) return nullptr;
        if(nodo->nombre == nombre) return nodo;
        for(Persona* h : nodo->hijos){
            Persona* encontrado = buscar(h, nombre);
            if(encontrado != nullptr) return encontrado;
        }
        return nullptr;
    }

    // Muestra el arbol de forma jerarquica e indentada -- O(n)
    void mostrarJerarquia(Persona* nodo, int nivel){
        if(nodo == nullptr) return;
        for(int i = 0; i < nivel; i++) cout << "    ";
        if(nivel > 0) cout << "|-- ";
        cout << nodo->nombre << " (" << nodo->relacion
             << ", " << nodo->fechaNacimiento << ")" << endl;
        for(Persona* h : nodo->hijos) mostrarJerarquia(h, nivel + 1);
    }

    // Recursivo: numero de generaciones (altura) -- O(n)
    int contarGeneraciones(Persona* nodo){
        if(nodo == nullptr) return 0;
        int maxSub = 0;
        for(Persona* h : nodo->hijos)
            maxSub = max(maxSub, contarGeneraciones(h));
        return 1 + maxSub;
    }

    // Recursivo: cantidad de descendientes de un nodo -- O(n)
    int contarDescendientes(Persona* nodo){
        if(nodo == nullptr) return 0;
        int total = 0;
        for(Persona* h : nodo->hijos)
            total += 1 + contarDescendientes(h);
        return total;
    }

    // Recolecta recursivamente todos los descendientes en un vector -- O(n)
    void recolectar(Persona* nodo, vector<Persona*>& v){
        if(nodo == nullptr) return;
        for(Persona* h : nodo->hijos){
            v.push_back(h);
            recolectar(h, v);
        }
    }

public:
    ArbolFamiliar() : raiz(nullptr) {}

    void establecerRaiz(string n, string f, string r){
        raiz = new Persona(n, f, r);
    }

    // b) Registrar persona como hijo de un familiar existente -- O(n)
    bool agregarPersona(const string& nombrePadre, string n, string f, string r){
        Persona* padre = buscar(raiz, nombrePadre);
        if(padre == nullptr) return false;
        padre->hijos.push_back(new Persona(n, f, r));
        return true;
    }

    // d) Buscar familiar por nombre -- O(n)
    Persona* buscarPorNombre(const string& nombre){ return buscar(raiz, nombre); }

    // c) Mostrar generaciones en orden jerarquico -- O(n)
    void mostrarJerarquia(){
        if(raiz == nullptr){ cout << t("(arbol vacio)", "(empty tree)") << endl; return; }
        mostrarJerarquia(raiz, 0);
    }

    // g) Calcular cuantas generaciones hay (recursivo) -- O(n)
    int generaciones(){ return contarGeneraciones(raiz); }

    // h) Contar cuantos descendientes tiene Lucia (recursivo) -- O(n)
    int descendientesDeRaiz(){ return contarDescendientes(raiz); }

    Persona* obtenerRaiz(){ return raiz; }

    // e) Ordenar descendientes por fecha de nacimiento (Insertion Sort) -- O(n^2)
    void ordenarDescendientesPorFecha(){
        vector<Persona*> v;
        recolectar(raiz, v);
        if(v.empty()){ cout << t("(sin descendientes)", "(no descendants)") << endl; return; }
        for(int i = 1; i < (int)v.size(); i++){
            Persona* clave = v[i];
            int j = i - 1;
            while(j >= 0 && v[j]->fechaNacimiento > clave->fechaNacimiento){
                v[j + 1] = v[j];
                j--;
            }
            v[j + 1] = clave;
        }
        cout << t("Descendientes ordenados por fecha de nacimiento:",
                  "Descendants sorted by birth date:") << endl;
        for(Persona* p : v)
            cout << "  " << p->fechaNacimiento << "  -  " << p->nombre
                 << " (" << p->relacion << ")" << endl;
    }

    // i) Mostrar todos los hijos de una persona -- O(n)
    void mostrarHijos(const string& nombre){
        Persona* p = buscar(raiz, nombre);
        if(p == nullptr){ cout << t("Persona no encontrada.", "Person not found.") << endl; return; }
        if(p->hijos.empty()){
            cout << t("No tiene hijos registrados.", "No registered children.") << endl; return;
        }
        cout << t("Hijos de ", "Children of ") << p->nombre << ":" << endl;
        for(Persona* h : p->hijos)
            cout << "  - " << h->nombre << " (" << h->fechaNacimiento << ")" << endl;
    }

    // i) Mostrar todos los nietos de una persona -- O(n)
    void mostrarNietos(const string& nombre){
        Persona* p = buscar(raiz, nombre);
        if(p == nullptr){ cout << t("Persona no encontrada.", "Person not found.") << endl; return; }
        bool hay = false;
        cout << t("Nietos de ", "Grandchildren of ") << p->nombre << ":" << endl;
        for(Persona* h : p->hijos)
            for(Persona* n : h->hijos){
                cout << "  - " << n->nombre << " (" << n->fechaNacimiento << ")" << endl;
                hay = true;
            }
        if(!hay) cout << t("  (sin nietos registrados)", "  (no registered grandchildren)") << endl;
    }
};

// ---------------------------------------------------------------------------
// Programa principal / main program
// ---------------------------------------------------------------------------
int main(){
    cout << "Seleccione idioma / Select language:\n";
    cout << "1) Espanol\n2) English\n> ";
    cin >> IDIOMA;
    if(IDIOMA != 2) IDIOMA = 1;

    ArbolFamiliar familia;

    // a) Arbol genealogico de Lucia (datos de ejemplo) / Lucia's family tree (sample)
    familia.establecerRaiz("Lucia", "1956-03-12", "Matriarca");
    familia.agregarPersona("Lucia",   "Carmen",  "1978-07-20", "Hija");
    familia.agregarPersona("Lucia",   "Roberto", "1980-11-05", "Hijo");
    familia.agregarPersona("Carmen",  "Sofia",   "2002-02-14", "Nieta");
    familia.agregarPersona("Carmen",  "Diego",   "2005-09-30", "Nieto");
    familia.agregarPersona("Roberto", "Elena",   "2008-04-18", "Nieta");
    familia.agregarPersona("Elena",   "Mateo",   "2024-01-10", "Bisnieto");

    int op;
    do{
        cout << "\n===== " << t("EL ARBOL DE LOS RECUERDOS",
                                "THE TREE OF MEMORIES") << " =====\n";
        cout << "1) " << t("Registrar persona", "Register person") << "\n";
        cout << "2) " << t("Mostrar arbol genealogico (jerarquia)",
                           "Show family tree (hierarchy)") << "\n";
        cout << "3) " << t("Buscar familiar por nombre",
                           "Search relative by name") << "\n";
        cout << "4) " << t("Ordenar descendientes por fecha de nacimiento",
                           "Sort descendants by birth date") << "\n";
        cout << "5) " << t("Contar generaciones (recursivo)",
                           "Count generations (recursive)") << "\n";
        cout << "6) " << t("Contar descendientes de Lucia (recursivo)",
                           "Count Lucia's descendants (recursive)") << "\n";
        cout << "7) " << t("Mostrar hijos de una persona",
                           "Show a person's children") << "\n";
        cout << "8) " << t("Mostrar nietos de una persona",
                           "Show a person's grandchildren") << "\n";
        cout << "0) " << t("Salir", "Exit") << "\n> ";
        cin >> op;

        if(op == 1){
            limpiarBuffer();
            cout << t("Nombre del familiar (padre/madre) ya registrado: ",
                      "Name of an already registered relative (parent): ");
            string padre; getline(cin, padre);
            cout << t("Nombre de la nueva persona: ", "Name of the new person: ");
            string nom; getline(cin, nom);
            cout << t("Fecha de nacimiento (AAAA-MM-DD): ", "Birth date (YYYY-MM-DD): ");
            string fec; getline(cin, fec);
            cout << t("Relacion familiar (Hijo, Nieta, etc.): ",
                      "Family relationship (Son, Granddaughter, etc.): ");
            string rel; getline(cin, rel);
            if(familia.agregarPersona(padre, nom, fec, rel))
                cout << t("Persona registrada correctamente.", "Person registered successfully.") << endl;
            else
                cout << t("No se encontro al familiar indicado.", "The indicated relative was not found.") << endl;
        }
        else if(op == 2){
            cout << endl;
            familia.mostrarJerarquia();
        }
        else if(op == 3){
            limpiarBuffer();
            cout << t("Nombre a buscar: ", "Name to search: ");
            string nom; getline(cin, nom);
            Persona* p = familia.buscarPorNombre(nom);
            if(p != nullptr)
                cout << t("Encontrado: ", "Found: ") << p->nombre
                     << " - " << p->relacion << " - " << p->fechaNacimiento << endl;
            else
                cout << t("Familiar no encontrado.", "Relative not found.") << endl;
        }
        else if(op == 4){
            familia.ordenarDescendientesPorFecha();
        }
        else if(op == 5){
            cout << t("Numero de generaciones: ", "Number of generations: ")
                 << familia.generaciones() << endl;
        }
        else if(op == 6){
            cout << t("Lucia tiene ", "Lucia has ") << familia.descendientesDeRaiz()
                 << t(" descendientes.", " descendants.") << endl;
        }
        else if(op == 7){
            limpiarBuffer();
            cout << t("Nombre de la persona: ", "Person's name: ");
            string nom; getline(cin, nom);
            familia.mostrarHijos(nom);
        }
        else if(op == 8){
            limpiarBuffer();
            cout << t("Nombre de la persona: ", "Person's name: ");
            string nom; getline(cin, nom);
            familia.mostrarNietos(nom);
        }
    } while(op != 0);

    cout << t("\nGracias por preservar la historia de Lucia.",
              "\nThank you for preserving Lucia's story.") << endl;
    return 0;
}
