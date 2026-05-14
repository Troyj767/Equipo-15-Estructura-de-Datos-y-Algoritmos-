ALMACENES = 6
PRODUCTOS = 15

nombres_productos = [
    "Aceite de motor", "Llantas", "Baterias", "Filtros de aire", "Bujias",
    "Liquido de frenos", "Refrigerante", "Pastillas de freno", "Amortiguadores",
    "Correas", "Limpiaparabrisas", "Bombillos", "Alternadores", "Radiadores", "Sensores"
]


def cargar_datos():
    # Stock inicial por almacen y producto
    stock = [
        [25, 16, 8, 14, 11, 13, 10, 15, 9, 12, 18, 22, 6, 5, 8],
        [8, 6, 15, 10, 7, 5, 9, 6, 14, 8, 7, 10, 12, 9, 6],
        [18, 20, 4, 16, 15, 14, 17, 5, 7, 18, 9, 8, 4, 6, 5],
        [6, 7, 10, 5, 8, 6, 5, 12, 11, 4, 6, 7, 10, 8, 7],
        [22, 14, 12, 18, 16, 17, 13, 19, 10, 15, 12, 11, 8, 10, 9],
        [9, 11, 7, 6, 5, 8, 6, 9, 13, 7, 10, 9, 5, 4, 6]
    ]

    # Distancia entre almacenes
    distancia = [
        [0, 12, 8, 15, 20, 10],
        [12, 0, 9, 7, 18, 14],
        [8, 9, 0, 11, 16, 6],
        [15, 7, 11, 0, 10, 13],
        [20, 18, 16, 10, 0, 12],
        [10, 14, 6, 13, 12, 0]
    ]

    # Umbral minimo por producto
    umbral = [10, 10, 9, 9, 8, 8, 8, 9, 8, 9, 10, 10, 7, 7, 7]

    return stock, distancia, umbral


def mostrar_matriz_stock(stock, titulo):
    print(f"\n===== {titulo} =====")
    print("Stock (filas=almacenes, columnas=productos):")

    encabezado = "      "
    for p in range(PRODUCTOS):
        encabezado += f"P{p + 1:02} "
    print(encabezado)

    for a in range(ALMACENES):
        fila = f"A{a + 1} -> "
        for p in range(PRODUCTOS):
            fila += f"{stock[a][p]:3} "
        print(fila)


def mostrar_matriz_distancia(distancia):
    print("\nDistancias entre almacenes:")

    encabezado = "      "
    for j in range(ALMACENES):
        encabezado += f"A{j + 1}  "
    print(encabezado)

    for i in range(ALMACENES):
        fila = f"A{i + 1} -> "
        for j in range(ALMACENES):
            fila += f"{distancia[i][j]:3} "
        print(fila)


def buscar_movimientos_necesarios(stock, umbral, producto):
    faltantes = [0] * ALMACENES
    total_faltante = 0

    # Aqui veo que almacenes estan por debajo del minimo para este producto
    for a in range(ALMACENES):
        if stock[a][producto] < umbral[producto]:
            faltantes[a] = umbral[producto] - stock[a][producto]
            total_faltante += faltantes[a]

    return faltantes, total_faltante


def realizar_reasignacion(stock, distancia, umbral):
    movimientos = []
    costo_total = 0.0

    # Greedy: por producto, cubro faltantes con el origen mas cercano con exceso
    for p in range(PRODUCTOS):
        faltantes, total_faltante = buscar_movimientos_necesarios(stock, umbral, p)

        if total_faltante == 0:
            continue

        for destino in range(ALMACENES):
            necesita = faltantes[destino]

            while necesita > 0:
                mejor_origen = -1
                mejor_distancia = 10**9

                # Busco un almacen que tenga exceso y que quede mas cerca
                for origen in range(ALMACENES):
                    if origen == destino:
                        continue

                    exceso = stock[origen][p] - umbral[p]
                    if exceso > 0 and distancia[origen][destino] < mejor_distancia:
                        mejor_distancia = distancia[origen][destino]
                        mejor_origen = origen

                # Si nadie tiene exceso, no puedo completar ese faltante
                if mejor_origen == -1:
                    break

                exceso_disponible = stock[mejor_origen][p] - umbral[p]
                cantidad_mover = min(necesita, exceso_disponible)

                # Restriccion: no mover mas de lo disponible
                if cantidad_mover <= 0:
                    break

                # Restriccion: el origen no puede quedar por debajo del umbral
                stock[mejor_origen][p] -= cantidad_mover
                stock[destino][p] += cantidad_mover
                necesita -= cantidad_mover

                costo = cantidad_mover * distancia[mejor_origen][destino]
                costo_total += costo

                movimientos.append({
                    "producto": p,
                    "almacen_origen": mejor_origen,
                    "almacen_destino": destino,
                    "cantidad_movida": cantidad_mover,
                    "costo_asociado": costo
                })

    return movimientos, costo_total


def mostrar_resumen(movimientos, costo_total):
    print("\n===== RESUMEN DE MOVIMIENTOS =====")

    if not movimientos:
        print("No fue necesario realizar movimientos.")
        print(f"Costo total: {costo_total:.2f}")
        return

    print("#  Producto              Origen  Destino  Cantidad  Costo")
    print("--------------------------------------------------------------")

    for i, mov in enumerate(movimientos, start=1):
        producto = nombres_productos[mov["producto"]][:20]
        origen = f"A{mov['almacen_origen'] + 1}"
        destino = f"A{mov['almacen_destino'] + 1}"
        cantidad = mov["cantidad_movida"]
        costo = mov["costo_asociado"]

        print(f"{i:<2} {producto:<20} {origen:<7} {destino:<8} {cantidad:<9} {costo:.2f}")

    print(f"\nCosto total de reasignacion: {costo_total:.2f}")


def main():
    stock, distancia, umbral = cargar_datos()

    mostrar_matriz_stock(stock, "ESTADO INICIAL")
    mostrar_matriz_distancia(distancia)

    movimientos, costo_total = realizar_reasignacion(stock, distancia, umbral)

    mostrar_matriz_stock(stock, "ESTADO FINAL")
    mostrar_resumen(movimientos, costo_total)


if __name__ == "__main__":
    main()
