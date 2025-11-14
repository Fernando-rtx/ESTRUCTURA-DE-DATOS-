#ifndef LISTA_INVENTARIO_H
#define LISTA_INVENTARIO_H

#include "Nodo.h"     // Necesario para usar la clase Nodo
#include <string>     // Necesario para usar string
#include <iostream>   // Necesario para usar cout, etc. (para mostrarInventario)

using namespace std;

// Clase ListaInventario: Gestiona una lista enlazada de productos.
// Permite insertar, eliminar, buscar y mostrar productos en el inventario.
class ListaInventario {
private:
    Nodo* primero; // Puntero al primer nodo de la lista (cabeza)

public:
    // Constructor: Inicializa la lista como vacía.
    ListaInventario();

    // Destructor: Libera toda la memoria ocupada por los nodos de la lista.
    ~ListaInventario();

    // Inserta un nuevo producto en la lista.
    void insertar(Producto prod);

    // Elimina un producto de la lista usando su código.
    // Retorna true si el producto fue eliminado, false en caso contrario.
    bool eliminar(string codigo);

    // Busca un producto en la lista usando su código.
    // Retorna un puntero al Producto si lo encuentra, nullptr en caso contrario.
    Producto* buscar(string codigo);

    // Muestra por consola todos los productos en el inventario.
    void mostrarInventario();

    // Verifica si la lista de inventario está vacía.
    // Retorna true si está vacía, false en caso contrario.
    bool estaVacia();
};

#endif // LISTA_INVENTARIO_H
