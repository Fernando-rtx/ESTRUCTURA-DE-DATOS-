# Makefile para compilar la librería de inventario y el programa principal

# --- Variables de Compilación ---
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE_DIR = include
INCLUDES = -I$(INCLUDE_DIR)

# --- Variables de Archivos y Directorios ---
LIB_DIR = lib
SRC_DIR = src
OBJ_DIR = obj
MAIN_SRC = main.cpp
# Se añade la extensión .exe para Windows
TARGET_EXEC = programa_inventario.exe
TARGET_LIB = $(LIB_DIR)/libinventario.a
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))


# --- Objetivos (Targets) ---

.PHONY: all clean

# Objetivo por defecto.
all: $(TARGET_EXEC)

# Objetivo para crear el ejecutable final.
# Depende de main.o y la librería.
$(TARGET_EXEC): $(OBJ_DIR)/main.o $(TARGET_LIB)
	@echo "Enlazando el programa principal: $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ -L$(LIB_DIR) -linventario

# Objetivo para crear el archivo objeto de main.cpp
# La dependencia de orden | $(OBJ_DIR) asegura que el directorio exista antes de compilar.
$(OBJ_DIR)/main.o: $(MAIN_SRC) | $(OBJ_DIR)
	@echo "Compilando $(MAIN_SRC) -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Objetivo para crear la librería estática.
# La dependencia de orden | $(LIB_DIR) asegura que el directorio exista.
$(TARGET_LIB): $(OBJECTS) | $(LIB_DIR)
	@echo "Creando la librería estática: $@"
	ar rcs $@ $^

# Regla de patrón para compilar archivos .cpp a .o.
# La dependencia de orden | $(OBJ_DIR) asegura que el directorio exista.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compilando $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# --- OBJETIVOS DE CREACIÓN DE DIRECTORIOS (Windows CMD Compatible) ---

# Objetivo para asegurar que el directorio obj/ exista.
# Usa el comando nativo de CMD: if not exist
$(OBJ_DIR):
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

# Objetivo para asegurar que el directorio lib/ exista.
$(LIB_DIR):
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)

# Objetivo para limpiar el proyecto.
# Nota: rm -rf funciona en consolas modernas como Git Bash o ciertas configuraciones de MinGW.
clean:
	@echo "Limpiando archivos generados..."
	-rm -rf $(OBJ_DIR) $(LIB_DIR) $(TARGET_EXEC)

# Declara objetivos que no son nombres de archivos reales.
.PHONY: all clean