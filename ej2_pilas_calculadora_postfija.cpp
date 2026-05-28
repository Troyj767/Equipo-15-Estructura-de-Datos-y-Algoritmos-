/*
 * ASIGNACIÓN III - EQUIPO NARANJA
 * Ejercicio 2 - Pilas: Calculadora Postfija (RPN)
 * Paradigma: POO | Lenguaje: C++
 */

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

class CalculadoraPostfija {
private:
    bool esOperador(const string& t) {   // O(1)
        return (t == "+" || t == "-" || t == "*" || t == "/");
    }

    bool esNumero(const string& s) {   // O(n)
        if (s.empty()) return false;
        int ini = (s[0] == '-' && s.size() > 1) ? 1 : 0;
        for (int i = ini; i < (int)s.size(); i++)
            if (!isdigit(s[i])) return false;
        return true;
    }

    double operar(double a, double b, const string& op) {   // O(1)
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw runtime_error("Error: division entre cero.");
            return a / b;
        }
        throw runtime_error("Operador desconocido.");
    }

public:
    void evaluar(const string& expr) {   // O(n)
        if (expr.empty()) { cout << "Error: expresion vacia." << endl; return; }
        stack<double> pila;
        istringstream iss(expr);
        string token;

        while (iss >> token) {
            if (esNumero(token)) {
                pila.push(stod(token));
            } else if (esOperador(token)) {
                if (pila.size() < 2) {
                    cout << "Error: expresion invalida (faltan operandos)." << endl;
                    return;
                }
                double b = pila.top(); pila.pop();
                double a = pila.top(); pila.pop();
                try { pila.push(operar(a, b, token)); }
                catch (const exception& e) { cout << e.what() << endl; return; }
            } else {
                cout << "Error: token no reconocido '" << token << "'" << endl;
                return;
            }
        }

        if (pila.size() != 1) { cout << "Error: expresion invalida." << endl; return; }
        double res = pila.top();
        if (res == (int)res) cout << "Resultado: " << (int)res << endl;
        else cout << "Resultado: " << res << endl;
    }
};

int main() {
    CalculadoraPostfija calc;
    string linea;

    cout << "=== CALCULADORA POSTFIJA ===" << endl;
    cout << "Escribe la expresion en notacion postfija." << endl;
    cout << "Ejemplo: 3 4 + 2 *   ->  Resultado: 14" << endl;
    cout << "Escribe 'salir' para terminar." << endl;
    cout << "============================" << endl << endl;

    while (true) {
        cout << "> ";
        getline(cin, linea);
        if (linea == "salir") { cout << "Saliendo." << endl; break; }
        if (!linea.empty()) calc.evaluar(linea);
    }
    return 0;
}
