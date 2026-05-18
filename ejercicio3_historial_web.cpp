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
 * EJERCICIO COMUN: Navegacion de historial web
 * TEMA: Lista Doblemente Enlazada
 */

#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

// ============================================================
// ESTRUCTURA DEL NODO
// ============================================================
struct Pagina {
    string url;
    string fechaHora;
    Pagina* siguiente;
    Pagina* anterior;

    Pagina(string u, string fh) {
        url = u;
        fechaHora = fh;
        siguiente = nullptr;
        anterior = nullptr;
    }
};

// ============================================================
// CLASE HISTORIAL WEB (Lista Doblemente Enlazada)
// ============================================================
class HistorialWeb {
private:
    Pagina* cabeza;
    Pagina* cola;
    Pagina* paginaActual;  // Puntero a la pagina donde esta el usuario
    int tamanio;

public:
    HistorialWeb() {
        cabeza = nullptr;
        cola = nullptr;
        paginaActual = nullptr;
        tamanio = 0;
    }

    ~HistorialWeb() {
        Pagina* actual = cabeza;
        while (actual != nullptr) {
            Pagina* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // --------------------------------------------------------
    // a) Insertar cada nueva visita al final de la lista
    //    Complejidad: O(1) - acceso directo a la cola
    // --------------------------------------------------------
    void insertarVisita(string url, string fechaHora) {
        auto inicio = high_resolution_clock::now();

        Pagina* nueva = new Pagina(url, fechaHora);

        if (cabeza == nullptr) {
            cabeza = nueva;
            cola = nueva;
        } else {
            nueva->anterior = cola;
            cola->siguiente = nueva;
            cola = nueva;
        }

        paginaActual = cola;  // Al visitar, la pagina actual es la ultima
        tamanio++;

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[insertarVisita] \"" << url << "\" - Tiempo: "
             << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // b) Desplazarse hacia adelante o atras desde pagina actual
    //    Complejidad: O(1) - acceso directo mediante punteros
    // --------------------------------------------------------
    void navegarAtras() {
        auto inicio = high_resolution_clock::now();

        if (paginaActual == nullptr) {
            cout << "[navegarAtras] Historial vacio." << endl;
        } else if (paginaActual->anterior == nullptr) {
            cout << "[navegarAtras] Ya estas en la primera pagina: "
                 << paginaActual->url << endl;
        } else {
            paginaActual = paginaActual->anterior;
            cout << "[navegarAtras] Pagina actual: "
                 << paginaActual->url << " (" << paginaActual->fechaHora << ")" << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[navegarAtras] Tiempo: " << duracion << " ns" << endl;
    }

    void navegarAdelante() {
        auto inicio = high_resolution_clock::now();

        if (paginaActual == nullptr) {
            cout << "[navegarAdelante] Historial vacio." << endl;
        } else if (paginaActual->siguiente == nullptr) {
            cout << "[navegarAdelante] Ya estas en la ultima pagina: "
                 << paginaActual->url << endl;
        } else {
            paginaActual = paginaActual->siguiente;
            cout << "[navegarAdelante] Pagina actual: "
                 << paginaActual->url << " (" << paginaActual->fechaHora << ")" << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[navegarAdelante] Tiempo: " << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // c) Eliminar una URL especifica del historial
    //    Complejidad: O(n) - busqueda lineal por URL
    // --------------------------------------------------------
    void eliminarURL(string url) {
        auto inicio = high_resolution_clock::now();

        Pagina* actual = cabeza;
        bool encontrado = false;

        while (actual != nullptr) {
            if (actual->url == url) {
                encontrado = true;

                // Ajustar paginaActual si se esta eliminando esa pagina
                if (paginaActual == actual) {
                    if (actual->anterior != nullptr)
                        paginaActual = actual->anterior;
                    else if (actual->siguiente != nullptr)
                        paginaActual = actual->siguiente;
                    else
                        paginaActual = nullptr;
                }

                // Reconectar los nodos vecinos
                if (actual->anterior != nullptr)
                    actual->anterior->siguiente = actual->siguiente;
                else
                    cabeza = actual->siguiente;  // Era la cabeza

                if (actual->siguiente != nullptr)
                    actual->siguiente->anterior = actual->anterior;
                else
                    cola = actual->anterior;  // Era la cola

                delete actual;
                tamanio--;
                cout << "[eliminarURL] \"" << url << "\" eliminada del historial." << endl;
                break;
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            cout << "[eliminarURL] URL \"" << url << "\" no encontrada." << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[eliminarURL] Tiempo: " << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // d) Mostrar historial en orden cronologico inverso
    //    Complejidad: O(n) - recorre desde cola hasta cabeza
    // --------------------------------------------------------
    void mostrarInverso() {
        auto inicio = high_resolution_clock::now();

        cout << "\n--- HISTORIAL (ultima a primera visita) ---" << endl;
        cout << left;
        cout.width(40); cout << "URL";
        cout.width(22); cout << "Fecha y Hora" << endl;
        cout << string(62, '-') << endl;

        Pagina* actual = cola;
        int num = 1;
        while (actual != nullptr) {
            cout << num++ << ". ";
            cout.width(38); cout << actual->url;
            cout.width(22); cout << actual->fechaHora << endl;
            actual = actual->anterior;
        }

        if (tamanio == 0) {
            cout << "El historial esta vacio." << endl;
        } else {
            cout << "\nTotal de paginas en historial: " << tamanio << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[mostrarInverso] Tiempo: " << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // Mostrar historial cronologico (auxiliar)
    //    Complejidad: O(n)
    // --------------------------------------------------------
    void mostrarCronologico() {
        cout << "\n--- HISTORIAL (primera a ultima visita) ---" << endl;
        cout << left;
        cout.width(40); cout << "URL";
        cout.width(22); cout << "Fecha y Hora" << endl;
        cout << string(62, '-') << endl;

        Pagina* actual = cabeza;
        int num = 1;
        while (actual != nullptr) {
            string marca = "";
            if (actual == paginaActual) marca = " << ACTUAL";
            cout << num++ << ". ";
            cout.width(38); cout << actual->url;
            cout.width(22); cout << actual->fechaHora;
            cout << marca << endl;
            actual = actual->siguiente;
        }

        if (tamanio == 0) {
            cout << "El historial esta vacio." << endl;
        }
    }
};

// ============================================================
// FUNCION PRINCIPAL
// ============================================================
int main() {
    auto inicioTotal = high_resolution_clock::now();

    cout << "=================================================" << endl;
    cout << "  SISTEMA DE HISTORIAL WEB                       " << endl;
    cout << "  Lista Doblemente Enlazada - Equipo Naranja #15 " << endl;
    cout << "=================================================" << endl;

    HistorialWeb historial;

    // Insertar visitas
    cout << "\n>> Registrando visitas al historial..." << endl;
    historial.insertarVisita("https://www.uapa.edu.do",         "2025-05-14 08:00");
    historial.insertarVisita("https://www.google.com",           "2025-05-14 08:05");
    historial.insertarVisita("https://www.github.com",           "2025-05-14 08:10");
    historial.insertarVisita("https://www.stackoverflow.com",    "2025-05-14 08:20");
    historial.insertarVisita("https://www.cplusplus.com",        "2025-05-14 08:35");
    historial.insertarVisita("https://www.onlinegdb.com",        "2025-05-14 08:50");

    // Mostrar historial cronologico
    historial.mostrarCronologico();

    // Navegar hacia atras y adelante
    cout << "\n>> Navegando en el historial..." << endl;
    historial.navegarAtras();
    historial.navegarAtras();
    historial.navegarAtras();
    historial.navegarAdelante();

    // Eliminar una URL
    cout << "\n>> Eliminando URL del historial..." << endl;
    historial.eliminarURL("https://www.google.com");
    historial.eliminarURL("https://www.yahoo.com");  // Inexistente

    // Mostrar historial inverso
    historial.mostrarInverso();

    // Mostrar cronologico final
    historial.mostrarCronologico();

    auto finTotal = high_resolution_clock::now();
    auto duracionTotal = duration_cast<microseconds>(finTotal - inicioTotal).count();
    cout << "\n[TIEMPO TOTAL DEL PROGRAMA]: " << duracionTotal << " us" << endl;
    cout << "=================================================" << endl;

    return 0;
}
