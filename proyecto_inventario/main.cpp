#include <iostream>
#include <limits>   // Necesario para limpiar el buffer
#include <iomanip>  // Necesario para formato de impresión
#include "include/ListaInventario.h" // Incluimos la clase principal

using namespace std;

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n           Sistema de Inventario              " << endl;
    cout << "1. Agregar producto" << endl;
    cout << "2. Eliminar producto (por codigo)" << endl;
    cout << "3. Buscar producto (por codigo)" << endl;
    cout << "4. Modificar cantidad (stock)" << endl;
    cout << "5. Modificar precio" << endl;
    cout << "6. Ver inventario completo" << endl;
    cout << "7. Generar reporte / Calcular valor total" << endl;
    cout << "8. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

// Función principal del programa
int main() {
    ListaInventario inventario;
    int opcion;
    string codigo, nombre;
    int cantidad;
    double precio;

    // Bucle principal del menú
    do {
        mostrarMenu();
        if (!(cin >> opcion)) {
            // Manejo de error: El usuario no ingresa un numero valido
            cout << "\nError de entrada. Ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0; // Para no salir del bucle
            continue;
        }

        // Limpiar el buffer de entrada después de leer el entero 'opcion'
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: { // Opción 1: Agregar producto
                cout << "\nAgregar Producto" << endl;
                cout << "Ingrese codigo: ";
                getline(cin, codigo);
                cout << "Ingrese nombre: ";
                getline(cin, nombre);
                cout << "Ingrese cantidad: ";
                cin >> cantidad;
                cout << "Ingrese precio: ";
                cin >> precio;

                // Crear y agregar el producto
                Producto nuevoProd(nombre, codigo, cantidad, precio);
                inventario.insertar(nuevoProd);
                break;
            }
            case 2: { // Opción 2: Eliminar producto
                cout << "\nEliminar Producto" << endl;
                cout << "Ingrese el codigo del producto a eliminar: ";
                getline(cin, codigo);
                inventario.eliminar(codigo);
                break;
            }
            case 3: { // Opción 3: Buscar producto
                cout << "\nBuscar Producto" << endl;
                cout << "Ingrese el codigo del producto a buscar: ";
                getline(cin, codigo);
                
                Producto* p = inventario.buscar(codigo);
                if (p != nullptr) {
                    cout << "\nProducto Encontrado:" << endl;
                    cout << "Codigo: " << p->codigo 
                        << " | Nombre: " << p->nombre
                        << " | Cantidad: " << p->cantidad
                        << " | Precio: $" << fixed << setprecision(2) << p->precio << endl;
                } else {
                    cout << "Producto con codigo '" << codigo << "' no encontrado." << endl;
                }
                break;
            }
            case 4: { // Opción 4: Modificar cantidad
                cout << "\nModificar Cantidad" << endl;
                cout << "Ingrese el codigo del producto: ";
                getline(cin, codigo);
                cout << "Ingrese la nueva cantidad: ";
                cin >> cantidad;
                inventario.modificarCantidad(codigo, cantidad);
                break;
            }
            case 5: { // Opción 5: Modificar precio
                cout << "\nModificar Precio" << endl;
                cout << "Ingrese el codigo del producto: ";
                getline(cin, codigo);
                cout << "Ingrese el nuevo precio: ";
                cin >> precio;
                inventario.modificarPrecio(codigo, precio);
                break;
            }
            case 6: { // Opción 6: Ver inventario completo
                inventario.mostrarInventario();
                break;
            }
            case 7: { // Opción 7: Generar reporte / Calcular valor total
                inventario.generarReporte();
                break;
            }
            case 8: { // Opción 8: Salir
                cout << "\nSaliendo del sistema de inventario." << endl;
                break;
            }
            default: {
                cout << "\nOpcion no valida. Por favor, intente de nuevo." << endl;
                break;
            }
        }
    } while (opcion != 8);

    return 0;
}