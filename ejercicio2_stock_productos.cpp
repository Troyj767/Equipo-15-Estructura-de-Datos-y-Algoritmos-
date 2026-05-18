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
 * EJERCICIO 2: Control de stock minimo de productos
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
struct Producto {
    int codigo;
    string nombre;
    int cantidad;
    Producto* siguiente;

    Producto(int cod, string nom, int cant) {
        codigo = cod;
        nombre = nom;
        cantidad = cant;
        siguiente = nullptr;
    }
};

// ============================================================
// CLASE INVENTARIO
// ============================================================
class Inventario {
private:
    Producto* cabeza;

public:
    Inventario() {
        cabeza = nullptr;
    }

    ~Inventario() {
        Producto* actual = cabeza;
        while (actual != nullptr) {
            Producto* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // --------------------------------------------------------
    // a) Insertar productos con sus datos completos (al final)
    //    Complejidad: O(n) - recorre hasta el ultimo nodo
    // --------------------------------------------------------
    void insertarProducto(int codigo, string nombre, int cantidad) {
        auto inicio = high_resolution_clock::now();

        Producto* nuevo = new Producto(codigo, nombre, cantidad);

        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Producto* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[insertarProducto] Cod " << codigo << " - Tiempo: "
             << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // b) Mostrar productos con stock menor a 5 unidades
    //    Complejidad: O(n) - recorre toda la lista
    // --------------------------------------------------------
    void mostrarStockCritico() {
        auto inicio = high_resolution_clock::now();

        cout << "\n--- PRODUCTOS CON STOCK CRITICO (< 5 unidades) ---" << endl;
        cout << left;
        cout.width(8);  cout << "Codigo";
        cout.width(25); cout << "Nombre";
        cout.width(12); cout << "Cantidad" << endl;
        cout << string(45, '-') << endl;

        Producto* actual = cabeza;
        int contador = 0;
        while (actual != nullptr) {
            if (actual->cantidad < 5) {
                cout.width(8);  cout << actual->codigo;
                cout.width(25); cout << actual->nombre;
                cout.width(12); cout << actual->cantidad << endl;
                contador++;
            }
            actual = actual->siguiente;
        }

        if (contador == 0) {
            cout << "Ningun producto tiene stock critico." << endl;
        } else {
            cout << "\nTotal productos con stock critico: " << contador << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[mostrarStockCritico] Tiempo: " << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // c) Actualizar el stock de un producto dado su codigo
    //    Complejidad: O(n) - busqueda lineal por codigo
    // --------------------------------------------------------
    void actualizarStock(int codigo, int nuevaCantidad) {
        auto inicio = high_resolution_clock::now();

        Producto* actual = cabeza;
        bool encontrado = false;

        while (actual != nullptr) {
            if (actual->codigo == codigo) {
                int anterior = actual->cantidad;
                actual->cantidad = nuevaCantidad;
                cout << "\n[actualizarStock] Producto \"" << actual->nombre
                     << "\" actualizado: " << anterior << " -> "
                     << nuevaCantidad << " unidades." << endl;
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            cout << "\n[actualizarStock] Codigo " << codigo
                 << " no encontrado en inventario." << endl;
        }

        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<nanoseconds>(fin - inicio).count();
        cout << "[actualizarStock] Tiempo: " << duracion << " ns" << endl;
    }

    // --------------------------------------------------------
    // Mostrar inventario completo (auxiliar)
    //    Complejidad: O(n)
    // --------------------------------------------------------
    void mostrarInventario() {
        cout << "\n--- INVENTARIO COMPLETO ---" << endl;
        cout << left;
        cout.width(8);  cout << "Codigo";
        cout.width(25); cout << "Nombre";
        cout.width(12); cout << "Cantidad" << endl;
        cout << string(45, '-') << endl;

        Producto* actual = cabeza;
        if (actual == nullptr) {
            cout << "El inventario esta vacio." << endl;
            return;
        }
        while (actual != nullptr) {
            cout.width(8);  cout << actual->codigo;
            cout.width(25); cout << actual->nombre;
            cout.width(12); cout << actual->cantidad << endl;
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
    cout << "  SISTEMA DE CONTROL DE STOCK - MINIMERCADO      " << endl;
    cout << "  Lista Simplemente Enlazada - Equipo Naranja #15" << endl;
    cout << "=================================================" << endl;

    Inventario inv;

    // Insertar productos de prueba
    cout << "\n>> Registrando productos en inventario..." << endl;
    inv.insertarProducto(101, "Arroz Premium 5lb",      12);
    inv.insertarProducto(102, "Aceite de Maiz 1L",       3);
    inv.insertarProducto(103, "Azucar Blanca 2lb",       7);
    inv.insertarProducto(104, "Sal Refinada 1lb",        2);
    inv.insertarProducto(105, "Pasta Espagueti 400g",    9);
    inv.insertarProducto(106, "Leche Evaporada 400ml",   1);
    inv.insertarProducto(107, "Habichuelas Negras 1lb",  4);
    inv.insertarProducto(108, "Jabon de Lavanderia",    15);

    // Mostrar inventario completo
    inv.mostrarInventario();

    // Mostrar productos con stock critico
    inv.mostrarStockCritico();

    // Actualizar stock de un producto
    cout << "\n>> Actualizando stock de productos..." << endl;
    inv.actualizarStock(102, 20);
    inv.actualizarStock(104, 10);
    inv.actualizarStock(999, 5);  // Codigo inexistente

    // Mostrar inventario actualizado
    inv.mostrarInventario();

    // Verificar stock critico luego de actualizacion
    inv.mostrarStockCritico();

    auto finTotal = high_resolution_clock::now();
    auto duracionTotal = duration_cast<microseconds>(finTotal - inicioTotal).count();
    cout << "\n[TIEMPO TOTAL DEL PROGRAMA]: " << duracionTotal << " us" << endl;
    cout << "=================================================" << endl;

    return 0;
}
