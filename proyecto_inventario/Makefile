# Makefile para compilar la librería de inventario y el programa principal

# --- Variables de Compilación ---

# Compilador de C++ a utilizar
CXX = g++

# Flags del compilador:
# -Wall: Activa todas las advertencias (muy recomendado).
# -g: Genera información de depuración (para usar con gdb).
# -std=c++11: Especifica el estándar de C++ a utilizar.
CXXFLAGS = -Wall -g -std=c++11

# Directorio de archivos de encabezado (.h)
INCLUDE_DIR = include

# Flags para el preprocesador, -I indica al compilador dónde buscar los encabezados.
INCLUDES = -I$(INCLUDE_DIR)

# --- Variables de Archivos y Directorios ---

# Directorio donde se guardará la librería estática
LIB_DIR = lib

# Directorio donde se encuentran los archivos fuente (.cpp) de la librería
SRC_DIR = src

# Directorio donde se guardarán los archivos objeto (.o)
OBJ_DIR = obj

# Archivo fuente principal
MAIN_SRC = main.cpp

# Nombre del ejecutable final
TARGET_EXEC = programa_inventario

# Nombre de la librería estática que se va a crear
TARGET_LIB = $(LIB_DIR)/libinventario.a

# Lista de todos los archivos fuente (.cpp) de la librería
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de archivos objeto (.o) correspondiente a cada archivo fuente de la librería.
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))


# --- Objetivos (Targets) ---

# Objetivo por defecto: se ejecuta cuando solo escribes "make" en la terminal.
# Ahora depende del ejecutable final.
all: $(TARGET_EXEC)

# Objetivo para crear el ejecutable final.
# Depende del archivo fuente principal (main.cpp) y de la librería estática.
# Si main.cpp o libinventario.a cambian, esta regla se ejecutará.
$(TARGET_EXEC): $(MAIN_SRC) $(TARGET_LIB)
	@echo "Enlazando el programa principal: $@"
	# Comando de compilación y enlazado.
	# -L$(LIB_DIR): Le dice al enlazador que busque librerías en el directorio 'lib'.
	# -linventario: Le dice al enlazador que enlace con la librería 'libinventario.a'.
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ -L$(LIB_DIR) -linventario

# Objetivo para crear la librería estática.
# Depende de todos los archivos objeto.
$(TARGET_LIB): $(OBJECTS)
	@echo "Creando la librería estática: $@"
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

# Regla de patrón para compilar archivos .cpp a .o.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compilando $< -> $@"
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Objetivo para limpiar el proyecto.
# Ahora también elimina el ejecutable final.
clean:
	@echo "Limpiando archivos generados..."
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TARGET_EXEC)

# Declara objetivos que no son nombres de archivos reales.
.PHONY: all clean
