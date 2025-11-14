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