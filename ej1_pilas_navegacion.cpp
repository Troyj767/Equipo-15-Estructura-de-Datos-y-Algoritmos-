/*
 * ASIGNACIÓN III - EQUIPO NARANJA
 * Ejercicio 1 - Pilas: Sistema de Navegacion Web
 * Paradigma: POO | Lenguaje: C++
 */

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

class Navegador {
private:
    stack<string> historialAtras;
    stack<string> historialAdelante;
    string paginaActual;

public:
    Navegador() : paginaActual("") {}

    void visitar(const string& url) {   // O(1)
        if (!paginaActual.empty())
            historialAtras.push(paginaActual);
        while (!historialAdelante.empty())
            historialAdelante.pop();
        paginaActual = url;
        cout << "Visitando: " << paginaActual << endl;
    }

    void atras() {   // O(1)
        if (historialAtras.empty()) {
            cout << "No hay paginas anteriores." << endl;
            return;
        }
        historialAdelante.push(paginaActual);
        paginaActual = historialAtras.top();
        historialAtras.pop();
        cout << "Pagina actual: " << paginaActual << endl;
    }

    void adelante() {   // O(1)
        if (historialAdelante.empty()) {
            cout << "No hay paginas adelante." << endl;
            return;
        }
        historialAtras.push(paginaActual);
        paginaActual = historialAdelante.top();
        historialAdelante.pop();
        cout << "Pagina actual: " << paginaActual << endl;
    }

    void mostrar() {   // O(n)
        cout << "Pagina actual: " << (paginaActual.empty() ? "(ninguna)" : paginaActual) << endl;

        stack<string> tmp = historialAtras;
        stack<string> inv;
        while (!tmp.empty()) { inv.push(tmp.top()); tmp.pop(); }
        cout << "Historial atras: [";
        bool p = true;
        while (!inv.empty()) { if (!p) cout << ", "; cout << inv.top(); inv.pop(); p = false; }
        cout << "]" << endl;

        tmp = historialAdelante;
        while (!tmp.empty()) { inv.push(tmp.top()); tmp.pop(); }
        cout << "Historial adelante: [";
        p = true;
        while (!inv.empty()) { if (!p) cout << ", "; cout << inv.top(); inv.pop(); p = false; }
        cout << "]" << endl;
    }
};

int main() {
    Navegador nav;
    string linea, comando, url;

    cout << "=== SISTEMA DE NAVEGACION WEB ===" << endl;
    cout << "Comandos: visitar <url> | atras | adelante | mostrar | salir" << endl;
    cout << "==================================" << endl << endl;

    while (true) {
        cout << "> ";
        getline(cin, linea);

        istringstream iss(linea);
        iss >> comando;

        if (comando == "visitar") {
            iss >> url;
            if (url.empty()) { cout << "Uso: visitar <url>" << endl; }
            else { nav.visitar(url); }
        } else if (comando == "atras") {
            nav.atras();
        } else if (comando == "adelante") {
            nav.adelante();
        } else if (comando == "mostrar") {
            nav.mostrar();
        } else if (comando == "salir") {
            cout << "Cerrando navegador." << endl;
            break;
        } else if (!comando.empty()) {
            cout << "Comando no reconocido: " << comando << endl;
        }
    }
    return 0;
}
