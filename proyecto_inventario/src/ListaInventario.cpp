#include "../include/ListaInventario.h" // Incluimos el archivo de encabezado de la clase
#include <iostream>                     // Necesario para std::cout
#include <iomanip>                      // Necesario para std::fixed y std::setprecision

// --- Constructor y Destructor ---

// Constructor: Inicializa la lista como vacía.
ListaInventario::ListaInventario() {
    primero = nullptr; // Al inicio, la lista no tiene ningún nodo
}

// Destructor: Libera toda la memoria ocupada por los nodos de la lista.
ListaInventario::~ListaInventario() {
    Nodo* actual = primero;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual; // Libera la memoria del nodo actual
        actual = siguiente;
    }
    primero = nullptr; // Asegurarse de que la lista esté vacía después de la destrucción
}

// --- Métodos Públicos ---

// Implementación del método insertar: Inserta un nuevo producto al inicio de la lista.
void ListaInventario::insertar(Producto prod) {
    // 1. Crear un nuevo nodo dinámicamente
    Nodo* nuevoNodo = new Nodo(prod);

    // 2. El nuevo nodo debe apuntar al antiguo primero
    nuevoNodo->siguiente = primero;

    // 3. Actualizar "primero" para que apunte al nuevo nodo
    primero = nuevoNodo;

    // 4. Mostrar mensaje de confirmación
    cout << "Producto '" << prod.nombre << "' insertado correctamente al inicio del inventario." << endl;
}

// Implementación del método eliminar: Busca y elimina un producto de la lista por su código.
// Maneja los casos de eliminación al inicio, en medio o al final de la lista.
bool ListaInventario::eliminar(string codigo) {
    // Punteros auxiliares para recorrer la lista.
    // 'actual' apunta al nodo que estamos revisando.
    // 'anterior' apunta al nodo previo a 'actual'.
    Nodo* actual = primero;
    Nodo* anterior = nullptr;

    // Búsqueda del nodo a eliminar.
    // El bucle se detiene si encontramos el producto o si llegamos al final de la lista.
    while (actual != nullptr && actual->producto.codigo != codigo) {
        anterior = actual;       // Guardamos el nodo actual como el anterior
        actual = actual->siguiente; // Avanzamos al siguiente nodo
    }

    // Caso 3: El nodo no existe en la lista.
    // Si 'actual' es nullptr, significa que recorrimos toda la lista y no encontramos el código.
    if (actual == nullptr) {
        cout << "Producto con codigo '" << codigo << "' no encontrado." << endl;
        return false; // Retornamos false porque no se eliminó nada.
    }

    // Si llegamos aquí, significa que 'actual' apunta al nodo que queremos eliminar.

    // Caso 1: El nodo a eliminar es el primero de la lista.
    // Esto ocurre si 'anterior' sigue siendo nullptr.
    if (anterior == nullptr) {
        primero = actual->siguiente; // El nuevo 'primero' es el nodo que seguía al eliminado.
    } 
    // Caso 2: El nodo a eliminar está en medio o al final de la lista.
    else {
        // El nodo 'anterior' debe ahora apuntar al nodo que sigue a 'actual',
        // "saltándose" el nodo que vamos a eliminar.
        anterior->siguiente = actual->siguiente;
    }

    // Mensaje de confirmación antes de liberar la memoria.
    cout << "Producto '" << actual->producto.nombre << "' con codigo '" << codigo << "' eliminado correctamente." << endl;
    
    // Liberamos la memoria del nodo que ya no está en la lista.
    delete actual;
    
    return true; // Retornamos true para indicar que la eliminación fue exitosa.
}

// Implementación del método buscar: Busca un producto en la lista por su código.
// Recorre la lista desde el inicio hasta encontrar una coincidencia.
Producto* ListaInventario::buscar(string codigo) {
    // Creamos un puntero auxiliar 'actual' que comienza en el primer nodo de la lista.
    // Este puntero nos permitirá recorrer la lista sin modificar 'primero'.
    Nodo* actual = primero;

    // Recorremos la lista mientras 'actual' no sea nullptr (es decir, mientras no lleguemos al final de la lista).
    while (actual != nullptr) {
        // Comparamos el código del producto en el nodo actual con el código que estamos buscando.
        if (actual->producto.codigo == codigo) {
            // Si encontramos una coincidencia, retornamos un puntero al objeto Producto.
            // Usamos '&(actual->producto)' para obtener la dirección de memoria del Producto.
            return &(actual->producto);
        }
        // Si no hay coincidencia, avanzamos al siguiente nodo en la lista.
        actual = actual->siguiente;
    }

    // Si el bucle termina y no hemos retornado, significa que no se encontró ningún producto
    // con el código especificado en la lista.
    return nullptr; // Retornamos nullptr para indicar que el producto no fue encontrado.
}

// Implementación del método mostrarInventario: Recorre y muestra todos los productos en el inventario.
void ListaInventario::mostrarInventario() {
    // Verifica si la lista está vacía.
    if (estaVacia()) {
        cout << "El inventario esta vacio." << endl;
        return; // Si está vacía, muestra el mensaje y sale de la función.
    }

    // Si la lista no está vacía, preparamos para mostrar los productos.
    cout << "--- Inventario Actual ---" << endl;
    Nodo* actual = primero; // Puntero auxiliar para recorrer la lista, comenzando desde el primer nodo.
    int contador = 1;       // Contador para numerar los productos.

    // Recorremos la lista mientras 'actual' no sea nullptr (es decir, hasta el final de la lista).
    while (actual != nullptr) {
        // Imprimimos la información de cada producto con el formato especificado.
        cout << contador << ". "
            << "Codigo: " << actual->producto.codigo
            << " | Nombre: " << actual->producto.nombre
            << " | Cantidad: " << actual->producto.cantidad
            << " | Precio: $" << fixed << setprecision(2) << actual->producto.precio << endl; // fixed y setprecision para formato de precio

        actual = actual->siguiente; // Avanzamos al siguiente nodo.
        contador++;                 // Incrementamos el contador para el siguiente producto.
    }
    cout << "-------------------------" << endl;
}

// Implementación del método estaVacia: Verifica si la lista de inventario está vacía.
// Retorna true si el puntero 'primero' es nullptr (lista vacía), false en caso contrario.
bool ListaInventario::estaVacia() {
    return primero == nullptr;
}

// <--------------->

//Implimentacion del metodo modificarCantidad; Realiza la actualizacion del Stock.
bool ListaInventario::modificarCantidad(string codigo, int nuevaCantidad) {
    // Primero buscamos el producto por código.
    Producto* productoEncontrado = buscar(codigo);

    if (productoEncontrado != nullptr) {
        // Si se encuentra el producto, se actualizia el atributo "Cantidad"
        if (nuevaCantidad >= 0) {
            productoEncontrado->cantidad = nuevaCantidad;
            cout << "Stock de '" << productoEncontrado->nombre 
                << "' actualizado a: " << nuevaCantidad << " unidades." << endl;
            return true;
        } else {
            cout << "Error: La cantidad no puede ser negativa." << endl;
            return false;
        }
    } else {
        // En caso que no se encuentre el producto, se muestra este mensaje
        cout << "Producto con codigo '" << codigo << "' no fue encontrado." << endl;
        return false;
    }
}

//Implementacion del metodo modificarPrecio
bool ListaInventario::modificarPrecio(string codigo, double nuevoPrecio) {
    // Se busca el producto por medio de su codigo
    Producto* productoEncontrado = buscar(codigo);

    if (productoEncontrado != nullptr) {
        // En caso de encontrarlo, se modifica el precio.
        if (nuevoPrecio > 0.0) {
            productoEncontrado->precio = nuevoPrecio;
            cout << fixed << setprecision(2);
            cout << "Precio de '" << productoEncontrado->nombre 
                << "' actualizado a: $" << nuevoPrecio << endl;
            return true;
        } else {
            cout << "Error: El precio debe ser un valor positivo." << endl;
            return false;
        }
    } else {
        // 3. En caso de no encontrar el productor, se muestra un mensaje.
        cout << "Producto con codigo '" << codigo << "' no fue encontrado." << endl;
        return false;
    }
}

// Implementacion del metodo calcularValorTotal
double ListaInventario::calcularValorTotal() {
    double valorTotal = 0.0;
    Nodo* actual = primero; 

    // Recorre toda la lista
    while (actual != nullptr) {
        // Fórmula: Valor = Cantidad * Precio
        valorTotal += actual->producto.cantidad * actual->producto.precio;
        actual = actual->siguiente;
    }

    return valorTotal;
}

// Implementacion del metodo generarReporte
void ListaInventario::generarReporte() {
    if (estaVacia()) {
        cout << "El inventario esta vacio. No se puede generar un reporte." << endl;
        return;
    }

    Nodo* actual = primero;
    int totalProductosDiferentes = 0;
    int totalUnidades = 0;

    // Primer recorrido para calcular unidades y cantidad de ítems
    while (actual != nullptr) {
        totalProductosDiferentes++;
        totalUnidades += actual->producto.cantidad;
        actual = actual->siguiente;
    }

    double valorTotal = calcularValorTotal(); // Usamos el método anterior

    cout << "\nReporte de Inventario" << endl;
    cout << "  - Total de productos diferentes (ítems): " << totalProductosDiferentes << endl;
    cout << "  - Total de unidades en stock: " << totalUnidades << endl;
    cout << fixed << setprecision(2);
    cout << "  - Valor total del inventario: $" << valorTotal << endl;
}