
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

const int MAX_COMPONENTES = 50;

class Componente {
private:
    int codigo;
    string nombre;
    double precioCosto;
    int cantidad;
    int nivelMinimo;
    char tipo;
    string paisOrigen;
    double precioEnUSD;
    string empresaProductora;

public:
    Componente() {
        codigo = 0;
        nombre = "";
        precioCosto = 0;
        cantidad = 0;
        nivelMinimo = 0;
        tipo = 'N';
        paisOrigen = "";
        precioEnUSD = 0;
        empresaProductora = "";
    }

    Componente(int c, string n, double pc, int cant, int minimo, char t, string pais, double usd, string empresa) {
        codigo = c;
        nombre = n;
        precioCosto = pc;
        cantidad = cant;
        nivelMinimo = minimo;
        tipo = t;
        paisOrigen = pais;
        precioEnUSD = usd;
        empresaProductora = empresa;
    }

    int getCodigo() const {
        return codigo;
    }

    string getNombre() const {
        return nombre;
    }

    double getPrecioCosto() const {
        return precioCosto;
    }

    int getCantidad() const {
        return cantidad;
    }

    int getNivelMinimo() const {
        return nivelMinimo;
    }

    char getTipo() const {
        return tipo;
    }

    string getPaisOrigen() const {
        return paisOrigen;
    }

    double getPrecioEnUSD() const {
        return precioEnUSD;
    }

    string getEmpresaProductora() const {
        return empresaProductora;
    }

    void setNombre(string nuevoNombre) {
        nombre = nuevoNombre;
    }

    void setPrecioCosto(double nuevoPrecio) {
        precioCosto = nuevoPrecio;
    }

    void setCantidad(int nuevaCantidad) {
        cantidad = nuevaCantidad;
    }

    void setNivelMinimo(int nuevoNivel) {
        nivelMinimo = nuevoNivel;
    }

    double calcularPrecioVenta() const {
        // Para importados: costo + 5% + (27 * precio en USD).
        if (tipo == 'I' || tipo == 'i') {
            return precioCosto + (precioCosto * 0.05) + (27.0 * precioEnUSD);
        }
        // Si es nacional solo se le agrega un 5% al costo.
        return precioCosto + (precioCosto * 0.05);
    }

    void mostrar() const {
        cout << "Codigo: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Precio costo: RD$" << fixed << setprecision(2) << precioCosto << endl;
        cout << "Cantidad: " << cantidad << endl;
        cout << "Nivel minimo: " << nivelMinimo << endl;

        if (tipo == 'I' || tipo == 'i') {
            cout << "Tipo: Importado" << endl;
            cout << "Pais de origen: " << paisOrigen << endl;
            cout << "Precio en USD: US$" << precioEnUSD << endl;
            cout << "Costo importacion (27 x USD): RD$" << (27.0 * precioEnUSD) << endl;
        } else {
            cout << "Tipo: Nacional" << endl;
            cout << "Empresa productora: " << empresaProductora << endl;
        }

        cout << "Precio de venta: RD$" << calcularPrecioVenta() << endl;
        cout << "-----------------------------" << endl;
    }
};

void mostrarMenu();
void cargarDatosIniciales(Componente inventario[], int &total);
void registrarComponente(Componente inventario[], int &total);
void modificarComponente(Componente inventario[], int total);
void listarNacionalesPorPrecio(Componente inventario[], int total);
void listarImportadosPorPais(Componente inventario[], int total);
void detectarBajoStock(Componente inventario[], int total);
void verTodos(Componente inventario[], int total);
int buscarPorCodigo(Componente inventario[], int total, int codigo);

int main() {
    Componente inventario[MAX_COMPONENTES];
    int total = 0;
    int opcion = 0;

    cargarDatosIniciales(inventario, total);

    do {
        mostrarMenu();

        // Si alguna entrada anterior fallo, limpio el estado para poder leer bien el menu.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string linea;
        getline(cin, linea);
        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);
        if (!(ss >> opcion) || (ss >> std::ws && !ss.eof())) {
            // Si no es número, o hay basura después, aviso y repito
            cout << "Por favor escribe solo numeros para elegir una opcion." << endl;
            opcion = 0;
            continue;
        }

        switch (opcion) {
            case 1:
                registrarComponente(inventario, total);
                break;
            case 2:
                modificarComponente(inventario, total);
                break;
            case 3:
                listarNacionalesPorPrecio(inventario, total);
                break;
            case 4:
                listarImportadosPorPais(inventario, total);
                break;
            case 5:
                detectarBajoStock(inventario, total);
                break;
            case 6:
                verTodos(inventario, total);
                break;
            case 7:
                cout << "Saliendo del sistema." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 7);

    return 0;
}

void mostrarMenu() {
    cout << "\n===== SISTEMA DE ALMACEN =====" << endl;
    cout << "1. Registrar componente" << endl;
    cout << "2. Modificar componente" << endl;
    cout << "3. Listar nacionales por precio" << endl;
    cout << "4. Listar importados por pais" << endl;
    cout << "5. Detectar bajo stock" << endl;
    cout << "6. Ver todos" << endl;
    cout << "7. Salir" << endl;
    cout << "--Tarea 1 ISW 305 Equipo 15--" << endl;
    cout << "Seleccione una opcion: ";
    
}

void cargarDatosIniciales(Componente inventario[], int &total) {
    inventario[total++] = Componente(101, "RTX4060", 19800.00, 10, 5, 'I', "Taiwan", 700.37, "");
    inventario[total++] = Componente(102, "SSD1TB", 3350.00, 18, 6, 'I', "China", 131.04, "");
    inventario[total++] = Componente(103, "BoardB650", 7900.00, 12, 4, 'I', "Taiwan", 289.19, "");
    inventario[total++] = Componente(104, "RAM16GB", 3750.00, 20, 8, 'I', "China", 149.11, "");
    inventario[total++] = Componente(105, "Ryzen7600", 12800.00, 7, 4, 'I', "USA", 485.74, "");
    inventario[total++] = Componente(106, "Monitor24", 8450.00, 9, 3, 'N', "", 0.00, "Samsung");
    inventario[total++] = Componente(107, "Fuente650W", 4200.00, 3, 5, 'N', "", 0.00, "Corsair");
    inventario[total++] = Componente(108, "CoolerCPU", 2200.00, 15, 5, 'I', "China", 85.85, "");
}

int buscarPorCodigo(Componente inventario[], int total, int codigo) {
    // Aqui busco un componente por su codigo y devuelvo la posicion.
    for (int i = 0; i < total; i++) {
        if (inventario[i].getCodigo() == codigo) {
            return i;
        }
    }
    return -1;
}

void registrarComponente(Componente inventario[], int &total) {
    if (total >= MAX_COMPONENTES) {
        cout << "No hay espacio para mas componentes." << endl;
        return;
    }

    int codigo;
    string nombre;
    double precioCosto;
    int cantidad;
    int nivelMinimo;
    char tipo;
    string paisOrigen;
    double precioEnUSD;
    string empresaProductora;

    cout << "\n--- Registrar componente ---" << endl;
    cout << "Codigo: ";
    cin >> codigo;

    // Esto es para que no se repita el mismo codigo.
    if (buscarPorCodigo(inventario, total, codigo) != -1) {
        cout << "Ese codigo ya existe." << endl;
        return;
    }

    cout << "Nombre: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombre);
    cout << "Precio de costo en pesos: ";
    cin >> precioCosto;
    cout << "Cantidad: ";
    cin >> cantidad;
    cout << "Nivel minimo: ";
    cin >> nivelMinimo;
    cout << "Tipo (N/I): ";
    cin >> tipo;

    // Si es importado pide pais y precio en USD.
    if (tipo == 'I' || tipo == 'i') {
        cout << "Pais de origen: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, paisOrigen);
        cout << "Precio en USD: ";
        cin >> precioEnUSD;
        empresaProductora = "";
    } else {
        // Si es nacional solo guarda la empresa productora.
        cout << "Empresa productora: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, empresaProductora);
        paisOrigen = "";
        precioEnUSD = 0;
        tipo = 'N';
    }

    inventario[total] = Componente(codigo, nombre, precioCosto, cantidad, nivelMinimo, tipo, paisOrigen, precioEnUSD, empresaProductora);
    total++;
    cout << "Componente registrado." << endl;
}

void modificarComponente(Componente inventario[], int total) {
    int codigo;
    int opcion;

    cout << "\n--- Modificar componente ---" << endl;
    cout << "Codigo del componente: ";
    cin >> codigo;

    int posicion = buscarPorCodigo(inventario, total, codigo);

    if (posicion == -1) {
        cout << "Componente no encontrado." << endl;
        return;
    }

    cout << "1. Nombre" << endl;
    cout << "2. Precio de costo" << endl;
    cout << "3. Cantidad" << endl;
    cout << "4. Nivel minimo" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        string nuevoNombre;
        cout << "Nuevo nombre: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nuevoNombre);
        inventario[posicion].setNombre(nuevoNombre);
        cout << "Nombre modificado." << endl;
    } else if (opcion == 2) {
        double nuevoPrecio;
        cout << "Nuevo precio: ";
        cin >> nuevoPrecio;
        inventario[posicion].setPrecioCosto(nuevoPrecio);
        cout << "Precio modificado." << endl;
    } else if (opcion == 3) {
        int nuevaCantidad;
        cout << "Nueva cantidad: ";
        cin >> nuevaCantidad;
        inventario[posicion].setCantidad(nuevaCantidad);
        cout << "Cantidad modificada." << endl;
    } else if (opcion == 4) {
        int nuevoNivel;
        cout << "Nuevo nivel minimo: ";
        cin >> nuevoNivel;
        inventario[posicion].setNivelMinimo(nuevoNivel);
        cout << "Nivel minimo modificado." << endl;
    } else {
        cout << "Opcion invalida." << endl;
    }
}

void listarNacionalesPorPrecio(Componente inventario[], int total) {
    double precioMinimo;
    bool encontrado = false;

    cout << "\n--- Nacionales por precio ---" << endl;
    // Aqui solo muestro los nacionales que pasen de ese precio.
    cout << "Precio minimo en pesos: ";
    cin >> precioMinimo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpio el salto de linea

    for (int i = 0; i < total; i++) {
        if ((inventario[i].getTipo() == 'N' || inventario[i].getTipo() == 'n') && inventario[i].calcularPrecioVenta() > precioMinimo) {
            inventario[i].mostrar();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay componentes nacionales con ese precio." << endl;
    }
    // Pausa para que puedas ver los resultados
    cout << "Presiona Enter para continuar...";
    string dummy;
    getline(cin, dummy);
}

// Muestra los paises de los importados sin repetir
void mostrarPaisesDisponibles(Componente inventario[], int total) {
    string paises[50];
    int numPaises = 0;
    // Recorro el inventario y guardo los paises unicos
    for (int i = 0; i < total; i++) {
        if (inventario[i].getTipo() == 'I' || inventario[i].getTipo() == 'i') {
            string pais = inventario[i].getPaisOrigen();
            bool repetido = false;
            for (int j = 0; j < numPaises; j++) {
                if (paises[j] == pais) {
                    repetido = true;
                    break;
                }
            }
            if (!repetido && pais != "") {
                paises[numPaises++] = pais;
            }
        }
    }
    cout << "Paises disponibles:" << endl;
    for (int i = 0; i < numPaises; i++) {
        cout << "- " << paises[i] << endl;
    }
}

void listarImportadosPorPais(Componente inventario[], int total) {
    string pais;
    bool encontrado = false;

    cout << "\n--- Importados por pais ---" << endl;
    // Primero muestro los paises que hay en el inventario
    mostrarPaisesDisponibles(inventario, total);
    // Aqui filtro los importados segun el pais que escriba.
    cout << "\nPais: ";
    getline(cin, pais);

    for (int i = 0; i < total; i++) {
        if ((inventario[i].getTipo() == 'I' || inventario[i].getTipo() == 'i') && inventario[i].getPaisOrigen() == pais) {
            inventario[i].mostrar();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay importados de ese pais." << endl;
    }
    // Pausa para que puedas ver los resultados
    cout << "Presiona Enter para continuar...";
    string dummy;
    getline(cin, dummy);
}

void detectarBajoStock(Componente inventario[], int total) {
    bool encontrado = false;

    cout << "\n--- Componentes con bajo stock ---" << endl;
    // Revisa cuales tienen menos cantidad que el nivel minimo.
    for (int i = 0; i < total; i++) {
        if (inventario[i].getCantidad() < inventario[i].getNivelMinimo()) {
            inventario[i].mostrar();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay componentes con bajo stock." << endl;
    }

    cout << "Presiona Enter para continuar...";
    string dummy;
    getline(cin, dummy);
}

void verTodos(Componente inventario[], int total) {
    cout << "\n--- Todos los componentes ---" << endl;

    // Si no hay nada guardado, avisa que esta vacio.
    if (total == 0) {
        cout << "No hay componentes registrados." << endl;
        return;
    }

    for (int i = 0; i < total; i++) {
        inventario[i].mostrar();
    }

    cout << "Presiona Enter para continuar...";
    string vacio;
    getline(cin, vacio);
}