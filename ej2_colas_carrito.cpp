/*
 * ASIGNACIÓN III - EQUIPO NARANJA
 * Ejercicio 2 - Colas: Carrito de Compras en Linea
 * Paradigma: POO | Lenguaje: C++
 */

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

struct Producto {
    string nombre;
    int cantidad;
    Producto(const string& n, int c) : nombre(n), cantidad(c) {}
};

class CarritoCompras {
private:
    queue<Producto> carrito;

public:
    void agregar(const string& nombre, int cantidad) {   // O(1)
        if (cantidad <= 0) { cout << "Error: cantidad debe ser mayor a 0." << endl; return; }
        carrito.push(Producto(nombre, cantidad));
        cout << "Agregado: " << cantidad << " " << nombre << endl;
    }

    void pagar() {   // O(1)
        if (carrito.empty()) { cout << "El carrito esta vacio." << endl; return; }
        Producto p = carrito.front(); carrito.pop();
        cout << "Procesando pago de " << p.cantidad << " " << p.nombre << endl;
    }

    void mostrarCarrito() {   // O(n)
        if (carrito.empty()) { cout << "El carrito esta vacio." << endl; return; }
        cout << "--- Carrito de Compras ---" << endl;
        queue<Producto> copia = carrito;
        int pos = 1;
        while (!copia.empty()) {
            Producto p = copia.front(); copia.pop();
            cout << pos++ << ". " << p.cantidad << "x " << p.nombre << endl;
        }
        cout << "Productos en carrito: " << carrito.size() << endl;
        cout << "-------------------------" << endl;
    }
};

int main() {
    CarritoCompras tienda;
    string linea, comando;

    cout << "=== CARRITO DE COMPRAS ===" << endl;
    cout << "Comandos:" << endl;
    cout << "  agregar <nombre> <cantidad>" << endl;
    cout << "  pagar" << endl;
    cout << "  mostrarCarrito" << endl;
    cout << "  salir" << endl;
    cout << "==========================" << endl << endl;

    while (true) {
        cout << "> ";
        getline(cin, linea);

        istringstream iss(linea);
        iss >> comando;

        if (comando == "agregar") {
            string nombre;
            int cantidad = 0;
            iss >> nombre >> cantidad;
            if (nombre.empty() || cantidad == 0) {
                cout << "Uso: agregar <nombre> <cantidad>" << endl;
            } else {
                tienda.agregar(nombre, cantidad);
            }
        } else if (comando == "pagar") {
            tienda.pagar();
        } else if (comando == "mostrarCarrito") {
            tienda.mostrarCarrito();
        } else if (comando == "salir") {
            cout << "Cerrando tienda." << endl; break;
        } else if (!comando.empty()) {
            cout << "Comando no reconocido: " << comando << endl;
        }
    }
    return 0;
}
