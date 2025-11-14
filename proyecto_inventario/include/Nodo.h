#ifndef NODO_H
#define NODO_H

#include "Producto.h" // Incluimos la definición de la clase Producto

using namespace std;

// Clase Nodo: Representa un elemento en la lista enlazada.
// Cada nodo contiene un objeto Producto y un puntero al siguiente nodo.
class Nodo {
public:
    Producto producto; // Objeto Producto almacenado en este nodo
    Nodo* siguiente;   // Puntero al siguiente nodo en la lista

    // Constructor por defecto
    Nodo() : siguiente(nullptr) {}

    // Constructor con parámetros para inicializar un nodo con un producto
    Nodo(Producto p) : producto(p), siguiente(nullptr) {}
};

#endif // NODO_H
