/*
 * ASIGNACIÓN III - EQUIPO NARANJA
 * Ejercicio 1 - Colas: Simulador de Cola de Empaque
 * Paradigma: POO | Lenguaje: C++
 */

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

struct Caja {
    string id;
    string descripcion;
    Caja(const string& i, const string& d) : id(i), descripcion(d) {}
};

class ColaEmpaque {
private:
    queue<Caja> cola;

public:
    void agregar(const string& id, const string& desc) {   // O(1)
        cola.push(Caja(id, desc));
        cout << "Caja " << id << " agregada: " << desc << endl;
    }

    void procesar() {   // O(1)
        if (cola.empty()) { cout << "No hay cajas en la cola." << endl; return; }
        Caja c = cola.front(); cola.pop();
        cout << "Procesando caja " << c.id << ": " << c.descripcion << endl;
    }

    void verCola() {   // O(n)
        if (cola.empty()) { cout << "La cola esta vacia." << endl; return; }
        cout << "--- Cola de Empaque ---" << endl;
        queue<Caja> copia = cola;
        int pos = 1;
        while (!copia.empty()) {
            Caja c = copia.front(); copia.pop();
            cout << pos++ << ". [" << c.id << "] " << c.descripcion << endl;
        }
        cout << "Total: " << cola.size() << " caja(s)" << endl;
        cout << "----------------------" << endl;
    }
};

int main() {
    ColaEmpaque almacen;
    string linea, comando;

    cout << "=== COLA DE EMPAQUE ===" << endl;
    cout << "Comandos:" << endl;
    cout << "  agregar <id> <descripcion>" << endl;
    cout << "  procesar" << endl;
    cout << "  verCola" << endl;
    cout << "  salir" << endl;
    cout << "=======================" << endl << endl;

    while (true) {
        cout << "> ";
        getline(cin, linea);

        istringstream iss(linea);
        iss >> comando;

        if (comando == "agregar") {
            string id, desc;
            iss >> id;
            getline(iss, desc);
            // quitar espacio inicial
            if (!desc.empty() && desc[0] == ' ') desc = desc.substr(1);
            if (id.empty()) { cout << "Uso: agregar <id> <descripcion>" << endl; }
            else { almacen.agregar(id, desc.empty() ? "Sin descripcion" : desc); }
        } else if (comando == "procesar") {
            almacen.procesar();
        } else if (comando == "verCola") {
            almacen.verCola();
        } else if (comando == "salir") {
            cout << "Cerrando sistema." << endl; break;
        } else if (!comando.empty()) {
            cout << "Comando no reconocido: " << comando << endl;
        }
    }
    return 0;
}
