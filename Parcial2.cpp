#include <iostream>
#include <fstream>

using namespace std;

double calcularSubtotal(int cantidad, double precio) {
    return cantidad * precio;
}
double calcularDescuento(double subtotal, int tipoPago) {
    double descuento = 0;

    if (subtotal >= 500) {
        descuento = subtotal * 0.05;
    }
    if (tipoPago == 1 && subtotal >= 300) {
        descuento += subtotal * 0.02;
    }
    return descuento;
}
double calcularTotal(double subtotal, double descuento) {
    return subtotal - descuento;
}
void registrarVenta() {

    string cliente, producto;
    int cantidad, tipoPago;
    double precio;

    ofstream archivo("ventas.txt", ios::app);

    cout << "\nNombre del cliente: ";
    getline(cin, cliente);
    cin >> cliente;

    char cancelar;
    cout << "Desea cancelar registro? (s/n): ";
    cin >> cancelar;

    if (cancelar == 's') {
        cout << "Venta cancelada.\n";
        return;
    }
    cout << "\nNombre del producto: ";
    cin >> producto;

    while (true) {
        cout << "Cantidad: ";
        cin >> cantidad;

        if (cantidad <= 0) {
            cout << "Error. Ingrese cantidad valida.\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Precio: ";
        cin >> precio;

        if (precio <= 0) {
            cout << "Error. Ingrese precio valido.\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Tipo de pago (1 Efectivo, 2 Tarjeta, 3 Transferencia): ";
        cin >> tipoPago;

        if (tipoPago == 1 || tipoPago == 2 || tipoPago == 3) {
            break;
        }
        cout << "Error. Tipo de pago invalido.\n";
    }

    double subtotal = calcularSubtotal(cantidad, precio);
    double descuento = calcularDescuento(subtotal, tipoPago);
    double total = calcularTotal(subtotal, descuento);

    string pagoTexto;
    switch (tipoPago) {
        case 1: pagoTexto = "Efectivo"; break;
        case 2: pagoTexto = "Tarjeta"; break;
        case 3: pagoTexto = "Transferencia"; break;
    }
    archivo << cliente << "," << producto << "," << cantidad << ","
            << precio << "," << subtotal << "," << descuento << ","
            << total << "," << pagoTexto << endl;

    archivo.close();

    cout << "Venta registrada correctamente.\n";
}
void mostrarVentas() {
    ifstream archivo("ventas.txt");
    string linea;

    cout << "\n--- VENTAS ---\n";
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}
void generarReporte() {

    ifstream archivo("ventas.txt");

    string cliente, producto, pago;
    string cantidad, precio, subtotal, descuento, total;

    int totalVentas = 0;
    int efectivo = 0, tarjeta = 0, transferencia = 0;
    int conDescuento = 0;

    double sumaTotal = 0;
    double promedio = 0;

    cout << "\n--REPORTE GENERAL --\n";
    while (getline(archivo, cliente, ',')) {

        getline(archivo, producto, ',');
        getline(archivo, cantidad, ',');
        getline(archivo, precio, ',');
        getline(archivo, subtotal, ',');
        getline(archivo, descuento, ',');
        getline(archivo, total, ',');
        getline(archivo, pago);

        totalVentas++;
        sumaTotal += stod(total);

        if (pago == "Efectivo") efectivo++;
        else if (pago == "Tarjeta") tarjeta++;
        else if (pago == "Transferencia") transferencia++;

        if (stod(descuento) > 0) conDescuento++;

        cout << cliente << " - " << producto << " - Q" << total << endl;
    }
    archivo.close();

    for (int i = 1; i <= totalVentas; i++) {
        cout << "Procesando venta #" << i << endl;
    }
    if (totalVentas > 0) {
        promedio = sumaTotal / totalVentas;
    }

    cout << "Total ventas: " << totalVentas << endl;
    cout << "Suma total vendida: Q" << sumaTotal << endl;
    cout << "Promedio de venta: Q" << promedio << endl;
    cout << "Efectivo: " << efectivo << endl;
    cout << "Tarjeta: " << tarjeta << endl;
    cout << "Transferencia: " << transferencia << endl;
    cout << "Con descuento: " << conDescuento << endl;
}
void buscarVentas() {

    ifstream archivo("ventas.txt");

    string cliente, producto, pago;
    string cantidad, precio, subtotal, descuento, total;

    double limite;

    cout << "Mostrar ventas mayores o iguales a Q400: ";
    cin >> limite;

    cout << "\n--- RESULTADOS ---\n";

    while (getline(archivo, cliente, ',')) {

        getline(archivo, producto, ',');
        getline(archivo, cantidad, ',');
        getline(archivo, precio, ',');
        getline(archivo, subtotal, ',');
        getline(archivo, descuento, ',');
        getline(archivo, total, ',');
        getline(archivo, pago);

        if (stod(total) >= limite) {
            cout << cliente << " - " << producto << " - Q" << total << endl;
        }
    }
    archivo.close();
}

int main() {
    int opcion;

    cout << "Nombre del estudiante: Cindy Julissa Carrillo Guarcas\n";

    do {
        cout << "\n== MENU ==\n";
        cout << "1. Registrar venta\n";
        cout << "2. Mostrar ventas\n";
        cout << "3. Reporte\n";
        cout << "4. Buscar ventas\n";
        cout << "5. Salir\n";
        cout << "\nElija una Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarVenta();
                break;
            case 2:
                mostrarVentas();
                break;
            case 3:
                generarReporte();
                break;
            case 4:
                buscarVentas();
                break;
            case 5:
                cout << "Saliendo.\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 5);

    return 0;
}