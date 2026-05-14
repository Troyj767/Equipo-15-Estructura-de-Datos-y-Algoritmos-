#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int ALMACENES = 6;
const int PRODUCTOS = 15;
const int MAX_MOVIMIENTOS = 500;

string nombresProductos[PRODUCTOS] = {
    "Aceite de motor", "Llantas", "Baterias", "Filtros de aire", "Bujias",
    "Liquido de frenos", "Refrigerante", "Pastillas de freno", "Amortiguadores",
    "Correas", "Limpiaparabrisas", "Bombillos", "Alternadores", "Radiadores", "Sensores"
};

struct Movimiento {
    int producto;
    int almacenOrigen;
    int almacenDestino;
    int cantidadMovida;
    double costoAsociado;
};

void cargarDatos(int stock[ALMACENES][PRODUCTOS], int distancia[ALMACENES][ALMACENES], int umbral[PRODUCTOS]);
void mostrarMatrizStock(int stock[ALMACENES][PRODUCTOS]);
void mostrarMatrizDistancia(int distancia[ALMACENES][ALMACENES]);
void buscarMovimientosNecesarios(int stock[ALMACENES][PRODUCTOS], int umbral[PRODUCTOS], int producto, int faltantes[ALMACENES], int &totalFaltante);
int realizarReasignacion(int stock[ALMACENES][PRODUCTOS], int distancia[ALMACENES][ALMACENES], int umbral[PRODUCTOS], Movimiento movimientos[MAX_MOVIMIENTOS], double &costoTotal);
void mostrarResumen(Movimiento movimientos[MAX_MOVIMIENTOS], int totalMovimientos, double costoTotal);

int main() {
    int stock[ALMACENES][PRODUCTOS];
    int distancia[ALMACENES][ALMACENES];
    int umbral[PRODUCTOS];
    Movimiento movimientos[MAX_MOVIMIENTOS];
    double costoTotal = 0;

    cargarDatos(stock, distancia, umbral);

    cout << "===== ESTADO INICIAL =====" << endl;
    mostrarMatrizStock(stock);
    cout << endl;
    mostrarMatrizDistancia(distancia);

    int totalMovimientos = realizarReasignacion(stock, distancia, umbral, movimientos, costoTotal);

    cout << "\n===== ESTADO FINAL =====" << endl;
    mostrarMatrizStock(stock);

    mostrarResumen(movimientos, totalMovimientos, costoTotal);

    return 0;
}

void cargarDatos(int stock[ALMACENES][PRODUCTOS], int distancia[ALMACENES][ALMACENES], int umbral[PRODUCTOS]) {
    // Stock inicial por almacen y producto
    int datosStock[ALMACENES][PRODUCTOS] = {
        {25, 16, 8, 14, 11, 13, 10, 15, 9, 12, 18, 22, 6, 5, 8},
        {8, 6, 15, 10, 7, 5, 9, 6, 14, 8, 7, 10, 12, 9, 6},
        {18, 20, 4, 16, 15, 14, 17, 5, 7, 18, 9, 8, 4, 6, 5},
        {6, 7, 10, 5, 8, 6, 5, 12, 11, 4, 6, 7, 10, 8, 7},
        {22, 14, 12, 18, 16, 17, 13, 19, 10, 15, 12, 11, 8, 10, 9},
        {9, 11, 7, 6, 5, 8, 6, 9, 13, 7, 10, 9, 5, 4, 6}
    };

    // Distancia entre almacenes
    int datosDistancia[ALMACENES][ALMACENES] = {
        {0, 12, 8, 15, 20, 10},
        {12, 0, 9, 7, 18, 14},
        {8, 9, 0, 11, 16, 6},
        {15, 7, 11, 0, 10, 13},
        {20, 18, 16, 10, 0, 12},
        {10, 14, 6, 13, 12, 0}
    };

    // Umbral minimo por producto
    int datosUmbral[PRODUCTOS] = {10, 10, 9, 9, 8, 8, 8, 9, 8, 9, 10, 10, 7, 7, 7};

    for (int i = 0; i < ALMACENES; i++) {
        for (int j = 0; j < PRODUCTOS; j++) {
            stock[i][j] = datosStock[i][j];
        }
    }

    for (int i = 0; i < ALMACENES; i++) {
        for (int j = 0; j < ALMACENES; j++) {
            distancia[i][j] = datosDistancia[i][j];
        }
    }

    for (int j = 0; j < PRODUCTOS; j++) {
        umbral[j] = datosUmbral[j];
    }
}

void mostrarMatrizStock(int stock[ALMACENES][PRODUCTOS]) {
    cout << "Stock (filas=almacenes, columnas=productos):" << endl;
    cout << "      ";
    for (int p = 0; p < PRODUCTOS; p++) {
        cout << "P" << setw(2) << (p + 1) << " ";
    }
    cout << endl;

    for (int a = 0; a < ALMACENES; a++) {
        cout << "A" << (a + 1) << " -> ";
        for (int p = 0; p < PRODUCTOS; p++) {
            cout << setw(3) << stock[a][p] << " ";
        }
        cout << endl;
    }
}

void mostrarMatrizDistancia(int distancia[ALMACENES][ALMACENES]) {
    cout << "Distancias entre almacenes:" << endl;
    cout << "      ";
    for (int j = 0; j < ALMACENES; j++) {
        cout << "A" << (j + 1) << "  ";
    }
    cout << endl;

    for (int i = 0; i < ALMACENES; i++) {
        cout << "A" << (i + 1) << " -> ";
        for (int j = 0; j < ALMACENES; j++) {
            cout << setw(3) << distancia[i][j] << " ";
        }
        cout << endl;
    }
}

void buscarMovimientosNecesarios(int stock[ALMACENES][PRODUCTOS], int umbral[PRODUCTOS], int producto, int faltantes[ALMACENES], int &totalFaltante) {
    totalFaltante = 0;

    // Aqui detecto que almacenes estan por debajo del minimo
    for (int a = 0; a < ALMACENES; a++) {
        if (stock[a][producto] < umbral[producto]) {
            faltantes[a] = umbral[producto] - stock[a][producto];
            totalFaltante += faltantes[a];
        } else {
            faltantes[a] = 0;
        }
    }
}

int realizarReasignacion(int stock[ALMACENES][PRODUCTOS], int distancia[ALMACENES][ALMACENES], int umbral[PRODUCTOS], Movimiento movimientos[MAX_MOVIMIENTOS], double &costoTotal) {
    int totalMovimientos = 0;
    costoTotal = 0;

    // Por cada producto, cubro deficits con el origen mas cercano que tenga exceso
    for (int p = 0; p < PRODUCTOS; p++) {
        int faltantes[ALMACENES];
        int totalFaltante = 0;

        buscarMovimientosNecesarios(stock, umbral, p, faltantes, totalFaltante);

        if (totalFaltante == 0) {
            continue;
        }

        for (int destino = 0; destino < ALMACENES; destino++) {
            int necesita = faltantes[destino];

            while (necesita > 0) {
                int mejorOrigen = -1;
                int mejorDistancia = 1000000;

                // Busco el almacen con exceso mas cercano al destino
                for (int origen = 0; origen < ALMACENES; origen++) {
                    if (origen == destino) {
                        continue;
                    }

                    int exceso = stock[origen][p] - umbral[p];
                    if (exceso > 0 && distancia[origen][destino] < mejorDistancia) {
                        mejorDistancia = distancia[origen][destino];
                        mejorOrigen = origen;
                    }
                }

                // Si no hay origen con exceso, no se puede completar ese faltante
                if (mejorOrigen == -1) {
                    break;
                }

                int excesoDisponible = stock[mejorOrigen][p] - umbral[p];
                int cantidadMover = necesita;

                if (cantidadMover > excesoDisponible) {
                    cantidadMover = excesoDisponible;
                }

                // Restriccion: no mover mas de lo disponible ni romper el umbral del origen
                if (cantidadMover <= 0) {
                    break;
                }

                stock[mejorOrigen][p] -= cantidadMover;
                stock[destino][p] += cantidadMover;
                necesita -= cantidadMover;

                if (totalMovimientos < MAX_MOVIMIENTOS) {
                    movimientos[totalMovimientos].producto = p;
                    movimientos[totalMovimientos].almacenOrigen = mejorOrigen;
                    movimientos[totalMovimientos].almacenDestino = destino;
                    movimientos[totalMovimientos].cantidadMovida = cantidadMover;
                    movimientos[totalMovimientos].costoAsociado = cantidadMover * distancia[mejorOrigen][destino];

                    costoTotal += movimientos[totalMovimientos].costoAsociado;
                    totalMovimientos++;
                }
            }
        }
    }

    return totalMovimientos;
}

void mostrarResumen(Movimiento movimientos[MAX_MOVIMIENTOS], int totalMovimientos, double costoTotal) {
    cout << "\n===== RESUMEN DE MOVIMIENTOS =====" << endl;

    if (totalMovimientos == 0) {
        cout << "No fue necesario realizar movimientos." << endl;
        cout << "Costo total: " << fixed << setprecision(2) << costoTotal << endl;
        return;
    }

    for (int i = 0; i < totalMovimientos; i++) {
        cout << (i + 1) << ". "
             << nombresProductos[movimientos[i].producto]
             << " | Origen: A" << (movimientos[i].almacenOrigen + 1)
             << " -> Destino: A" << (movimientos[i].almacenDestino + 1)
             << " | Cantidad: " << movimientos[i].cantidadMovida
             << " | Costo: " << fixed << setprecision(2) << movimientos[i].costoAsociado
             << endl;
    }

    cout << "Costo total de reasignacion: " << fixed << setprecision(2) << costoTotal << endl;
}
