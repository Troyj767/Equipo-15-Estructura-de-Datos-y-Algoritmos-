/*
 * ASIGNACION ESCRITA II - ESTRUCTURAS DE DATOS
 * Universidad Abierta para Adultos (UAPA)
 * Escuela de Ingenieria y Tecnologia
 *
 * EQUIPO NARANJA - Equipo #15
 * Integrantes:
 *   - Fernando Enrique  Meson Acosta
 *   - Erasmo Jose       Minaya Taveras
 *   - Hugo Eladio       Montero Fulcar
 *   - Alber Daniel      Montero Ramirez
 *   - Luis Angel        Mora Taveras
 *
 * EJERCICIO 1: Listado dinamico de tareas priorizadas
 * TEMA: Lista Simplemente Enlazada
 */

#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

// ============================================================
// ESTRUCTURA DEL NODO
// ============================================================
struct Tarea {
    string nombre;
    int prioridad;
    string estado; // "pendiente" o "completada"
    Tarea* siguiente;

    Tarea(string n, int p, string e) {
        nombre = n;
        prioridad = p;
        estado = e;
        siguiente = nullptr;
    }
};

// ============================================================
// CLASE LISTA DE TAREAS
// ============================================================
class ListaTareas {
private:
    Tarea* cabeza;

public:
    ListaTareas() {
        cabeza = nullptr;
    }

    // Destructor para liberar memoria
    ~ListaTareas() {
        Tarea* actual = cabeza;
        while (actual != nullptr) {
            Tarea* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // --------------------------------------------------------
    // a) Insertar tareas en orden descendente segun prioridad
    //    Complejidad: O(n) - recorre la lista para encontrar posicion
    // --------------------------------------------------------
    void insertarOrdenado(string nombre, int prioridad, string estado) {
        auto inicio = high_resolution_clock::now();

        Tarea* nueva = new Tarea(nombre, prioridad, estado);

        // Si la lista esta vacia o la nueva tarea tiene mayor prioridad que la cabeza
        if (cabeza == nullptr || prioridad > cabeza->prioridad) {
            nueva->siguiente = cabeza;
            cabeza = nueva;
        } else {
            // Recorrer hasta encontrar la posicion correcta
            Tarea* actual = cabeza;
            while (actual->siguiente != nullptr &&
                   actual->siguiente->prioridad >= prioridad) {
                actual = actual->siguiente;
            }
            nueva->siguiente = actual->siguiente;
            actual->siguiente = nueva;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[insertarOrdenado] Tiempo: " << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // b) Mostrar todas las tareas en estado "pendiente"
    //    Complejidad: O(n) - recorre toda la lista
    // --------------------------------------------------------
    void mostrarPendientes() {
        auto inicio = high_resolution_clock::now();

        cout << "\n--- TAREAS PENDIENTES ---" << endl;
        cout << left;
        cout.width(25); cout << "Nombre";
        cout.width(12); cout << "Prioridad";
        cout.width(15); cout << "Estado" << endl;
        cout << string(52, '-') << endl;

        Tarea* actual = cabeza;
        int contador = 0;
        while (actual != nullptr) {
            if (actual->estado == "pendiente") {
                cout.width(25); cout << actual->nombre;
                cout.width(12); cout << actual->prioridad;
                cout.width(15); cout << actual->estado << endl;
                contador++;
            }
            actual = actual->siguiente;
        }

        if (contador == 0) {
            cout << "No hay tareas pendientes." << endl;
        } else {
            cout << "\nTotal de tareas pendientes: " << contador << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[mostrarPendientes] Tiempo: " << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // c) Eliminar tareas marcadas como "completadas"
    //    Complejidad: O(n) - recorre toda la lista
    // --------------------------------------------------------
    void eliminarCompletadas() {
        auto inicio = high_resolution_clock::now();

        int eliminadas = 0;

        // Eliminar nodos al inicio que sean completadas
        while (cabeza != nullptr && cabeza->estado == "completada") {
            Tarea* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            eliminadas++;
        }

        // Eliminar nodos en el resto de la lista
        if (cabeza != nullptr) {
            Tarea* actual = cabeza;
            while (actual->siguiente != nullptr) {
                if (actual->siguiente->estado == "completada") {
                    Tarea* temp = actual->siguiente;
                    actual->siguiente = temp->siguiente;
                    delete temp;
                    eliminadas++;
                } else {
                    actual = actual->siguiente;
                }
            }
        }

        cout << "\n[eliminarCompletadas] Se eliminaron " << eliminadas
             << " tarea(s) completada(s)." << endl;

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[eliminarCompletadas] Tiempo: " << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // Mostrar todas las tareas (auxiliar para verificacion)
    //    Complejidad: O(n)
    // --------------------------------------------------------
    void mostrarTodas() {
        cout << "\n--- LISTA COMPLETA DE TAREAS ---" << endl;
        cout << left;
        cout.width(25); cout << "Nombre";
        cout.width(12); cout << "Prioridad";
        cout.width(15); cout << "Estado" << endl;
        cout << string(52, '-') << endl;

        Tarea* actual = cabeza;
        if (actual == nullptr) {
            cout << "La lista esta vacia." << endl;
            return;
        }
        while (actual != nullptr) {
            cout.width(25); cout << actual->nombre;
            cout.width(12); cout << actual->prioridad;
            cout.width(15); cout << actual->estado << endl;
            actual = actual->siguiente;
        }
    }
};

// ============================================================
// FUNCION PRINCIPAL
// ============================================================
int main() {
    auto inicioTotal = high_resolution_clock::now();

    cout << "=================================================" << endl;
    cout << "  SISTEMA DE GESTION DE TAREAS PRIORIZADAS       " << endl;
    cout << "  Lista Simplemente Enlazada - Equipo Naranja #15" << endl;
    cout << "=================================================" << endl;

    ListaTareas lista;

    // Insertar tareas de prueba
    cout << "\n>> Insertando tareas en orden de prioridad..." << endl;
    lista.insertarOrdenado("Entregar informe final",   10, "pendiente");
    lista.insertarOrdenado("Revisar correo",            3, "completada");
    lista.insertarOrdenado("Reunion con el cliente",    8, "pendiente");
    lista.insertarOrdenado("Actualizar documentacion",  5, "completada");
    lista.insertarOrdenado("Corregir bug critico",       9, "pendiente");
    lista.insertarOrdenado("Organizar archivos",         2, "pendiente");
    lista.insertarOrdenado("Capacitacion de personal",   6, "completada");

    // Mostrar todas las tareas
    lista.mostrarTodas();

    // Mostrar solo pendientes
    lista.mostrarPendientes();

    // Eliminar completadas
    lista.eliminarCompletadas();

    // Mostrar lista luego de eliminacion
    lista.mostrarTodas();

    auto finTotal = high_resolution_clock::now();
    auto duracionTotal = duration_cast<microseconds>(finTotal - inicioTotal).count();
    cout << "\n[TIEMPO TOTAL DEL PROGRAMA]: " << duracionTotal << " us" << endl;
    cout << "=================================================" << endl;

    return 0;
}
