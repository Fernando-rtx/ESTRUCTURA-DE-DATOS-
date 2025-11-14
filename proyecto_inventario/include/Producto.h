#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string> // Necesario para usar std::string

using namespace std;

// Clase Producto: Representa un artículo en el inventario.
// Contiene los datos básicos de cada producto.
class Producto {
public:
    string nombre;   // Nombre del producto
    string codigo;   // Código único del producto
    int cantidad;         // Cantidad disponible en inventario
    double precio;        // Precio unitario del producto

    // Constructor por defecto
    Producto() : nombre(""), codigo(""), cantidad(0), precio(0.0) {}

    // Constructor con parámetros para inicializar un producto
    Producto(string _nombre, string _codigo, int _cantidad, double _precio)
        : nombre(_nombre), codigo(_codigo), cantidad(_cantidad), precio(_precio) {}
};

#endif // PRODUCTO_H
