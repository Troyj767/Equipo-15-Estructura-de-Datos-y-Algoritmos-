#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

const int TOTAL_ALMACENES = 6;
const int TOTAL_PRODUCTOS = 15;

string nombresProductos[TOTAL_PRODUCTOS] = {
    "Aceite de motor",
    "Llantas",
    "Baterias",
    "Filtros de aire",
    "Bujias",
    "Liquido de frenos",
    "Refrigerante",
    "Pastillas de freno",
    "Amortiguadores",
    "Correas",
    "Limpiaparabrisas",
    "Bombillos",
    "Alternadores",
    "Radiadores",
    "Sensores"
};

class Almacen {
private:
    // Filas: almacenes, columnas: productos
    int stock[TOTAL_ALMACENES][TOTAL_PRODUCTOS];

    bool indicesValidos(int almacen, int producto) const {
        // Validacion basica para no salirnos de la matriz
        if (almacen < 0 || almacen >= TOTAL_ALMACENES) {
            cout << "Almacen fuera de rango. Debe ser entre 1 y " << TOTAL_ALMACENES << "." << endl;
            return false;
        }

        if (producto < 0 || producto >= TOTAL_PRODUCTOS) {
            cout << "Producto fuera de rango. Debe ser entre 1 y " << TOTAL_PRODUCTOS << "." << endl;
            return false;
        }

        return true;
    }

public:
    Almacen() {
        // Inventario inicial de ejemplo
        int datosIniciales[TOTAL_ALMACENES][TOTAL_PRODUCTOS] = {
            {40, 25, 18, 35, 42, 22, 30, 28, 14, 26, 50, 60, 8, 6, 20},
            {32, 20, 12, 30, 38, 18, 24, 21, 11, 19, 45, 48, 6, 5, 16},
            {28, 16, 10, 22, 30, 15, 20, 18, 9, 15, 37, 40, 5, 4, 14},
            {36, 22, 15, 29, 35, 19, 26, 23, 13, 21, 42, 52, 7, 6, 18},
            {24, 14, 8, 18, 26, 12, 16, 15, 7, 12, 30, 35, 4, 3, 11},
            {30, 19, 13, 25, 33, 17, 22, 20, 10, 18, 39, 44, 6, 5, 15}
        };

        for (int i = 0; i < TOTAL_ALMACENES; i++) {
            for (int j = 0; j < TOTAL_PRODUCTOS; j++) {
                // Copio los datos a la matriz principal
                stock[i][j] = datosIniciales[i][j];
            }
        }
    }

    void registrarExistencia(int almacen, int producto, int cantidad) {
        if (!indicesValidos(almacen, producto)) {
            return;
        }

        if (cantidad < 0) {
            cout << "La cantidad no puede ser negativa." << endl;
            return;
        }

        stock[almacen][producto] = cantidad;
        cout << "Existencia registrada correctamente." << endl;
    }

    int obtenerExistencia(int almacen, int producto) const {
        if (!indicesValidos(almacen, producto)) {
            return -1;
        }
        return stock[almacen][producto];
    }

    void mostrarStockCompleto() const {
        // Muestra la matriz completa para ver todo de una vez
        cout << "\n===== MATRIZ DE STOCK (Almacen x Producto) =====" << endl;
        cout << "     ";
        for (int j = 0; j < TOTAL_PRODUCTOS; j++) {
            cout << "P" << setw(2) << (j + 1) << " ";
        }
        cout << endl;

        for (int i = 0; i < TOTAL_ALMACENES; i++) {
            cout << "A" << (i + 1) << " -> ";
            for (int j = 0; j < TOTAL_PRODUCTOS; j++) {
                cout << setw(3) << stock[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nLeyenda de productos:" << endl;
        for (int j = 0; j < TOTAL_PRODUCTOS; j++) {
            cout << "P" << (j + 1) << ": " << nombresProductos[j] << endl;
        }
    }

    void detectarProductosAgotados() const {
        bool hayAgotados = false;

        // Busca productos con cantidad 0
        cout << "\n===== PRODUCTOS AGOTADOS =====" << endl;
        for (int i = 0; i < TOTAL_ALMACENES; i++) {
            for (int j = 0; j < TOTAL_PRODUCTOS; j++) {
                if (stock[i][j] == 0) {
                    cout << "Almacen " << (i + 1)
                         << " - " << nombresProductos[j]
                         << " (P" << (j + 1) << ")" << endl;
                    hayAgotados = true;
                }
            }
        }

        if (!hayAgotados) {
            cout << "No hay productos agotados en este momento." << endl;
        }
    }

    int obtenerStockTotalAlmacen(int almacen) const {
        if (almacen < 0 || almacen >= TOTAL_ALMACENES) {
            return -1;
        }

        int total = 0;
        for (int j = 0; j < TOTAL_PRODUCTOS; j++) {
            total += stock[almacen][j];
        }
        return total;
    }

    int obtenerAlmacenConMenorStock() const {
        // Empiezo con el almacen 1 como referencia
        int posMenor = 0;
        int menor = obtenerStockTotalAlmacen(0);

        for (int i = 1; i < TOTAL_ALMACENES; i++) {
            int totalActual = obtenerStockTotalAlmacen(i);
            if (totalActual < menor) {
                menor = totalActual;
                posMenor = i;
            }
        }

        return posMenor;
    }

    void emitirAlertasPorUmbral(int umbral) const {
        bool hayAlertas = false;

        if (umbral < 0) {
            cout << "El umbral no puede ser negativo." << endl;
            return;
        }

        // Lista los productos que estan por debajo o igual al umbral
        cout << "\n===== ALERTAS POR UMBRAL (<= " << umbral << ") =====" << endl;
        for (int i = 0; i < TOTAL_ALMACENES; i++) {
            for (int j = 0; j < TOTAL_PRODUCTOS; j++) {
                if (stock[i][j] <= umbral) {
                    cout << "Almacen " << (i + 1)
                         << " - " << nombresProductos[j]
                         << " (P" << (j + 1) << "): "
                         << stock[i][j] << endl;
                    hayAlertas = true;
                }
            }
        }

        if (!hayAlertas) {
            cout << "No hay alertas para ese umbral." << endl;
        }
    }
};

void mostrarMenu() {
    cout << "\n===== INVENTARIO MULTISUCURSAL =====" << endl;
    cout << "1. Registrar existencia" << endl;
    cout << "2. Ver matriz de stock" << endl;
    cout << "3. Detectar productos agotados" << endl;
    cout << "4. Almacen con menor stock total" << endl;
    cout << "5. Emitir alertas por umbral" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

bool leerEntero(const string &mensaje, int &valor) {
    // Lee la linea completa para evitar errores raros de entrada
    cout << mensaje;
    string linea;
    getline(cin, linea);

    stringstream ss(linea);
    if (!(ss >> valor) || (ss >> ws && !ss.eof())) {
        cout << "Entrada invalida. Debe escribir un numero entero." << endl;
        return false;
    }

    return true;
}

int main() {
    Almacen sistema;
    int opcion = 0;

    do {
        mostrarMenu();

        // Leo la opcion como texto y luego la convierto a numero
        string linea;
        getline(cin, linea);
        stringstream ss(linea);

        if (!(ss >> opcion) || (ss >> ws && !ss.eof())) {
            cout << "Opcion invalida. Intente de nuevo." << endl;
            continue;
        }

        if (opcion == 1) {
            int almacen, producto, cantidad;

            if (!leerEntero("Numero de almacen (1-6): ", almacen)) {
                continue;
            }
            if (!leerEntero("Numero de producto (1-15): ", producto)) {
                continue;
            }
            if (!leerEntero("Cantidad nueva: ", cantidad)) {
                continue;
            }

            // El usuario escribe 1-6 y 1-15, por eso resto 1
            sistema.registrarExistencia(almacen - 1, producto - 1, cantidad);
        } else if (opcion == 2) {
            sistema.mostrarStockCompleto();
        } else if (opcion == 3) {
            sistema.detectarProductosAgotados();
        } else if (opcion == 4) {
            int pos = sistema.obtenerAlmacenConMenorStock();
            int total = sistema.obtenerStockTotalAlmacen(pos);
            cout << "El almacen con menor stock total es el almacen " << (pos + 1)
                 << " con " << total << " unidades en total." << endl;
        } else if (opcion == 5) {
            int umbral;
            if (!leerEntero("Umbral de alerta: ", umbral)) {
                continue;
            }
            sistema.emitirAlertasPorUmbral(umbral);
        } else if (opcion == 6) {
            cout << "Saliendo del sistema..." << endl;
        } else {
            cout << "Opcion fuera de rango. Intente otra vez." << endl;
        }
    } while (opcion != 6);

    return 0;
}
