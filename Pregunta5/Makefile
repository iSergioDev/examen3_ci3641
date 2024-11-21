# Nombre del archivo de salida
OUTPUT = maldad

# Archivos fuente
SRC = maldad.cpp

# Opciones de compilador
CXXFLAGS = -std=c++14 -Wall -g

# Librerías de Boost necesarias
BOOST_LIBS = -lboost_system -lboost_filesystem

# Ruta de las cabeceras de Boost (si es necesario)
BOOST_INCLUDE = /usr/include/boost

# Ruta de las librerías de Boost (si es necesario)
BOOST_LIB = /usr/lib

# Regla principal para compilar
all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(BOOST_INCLUDE) -L$(BOOST_LIB) $(SRC) -o $(OUTPUT) $(BOOST_LIBS)

# Regla para limpiar los archivos generados
clean:
	rm -f $(OUTPUT)

# Regla para compilar y ejecutar
run: $(OUTPUT)
	./$(OUTPUT)

# Regla para ejecutar solo las pruebas
test: $(OUTPUT)
	./$(OUTPUT) 10000000000000000000
