# Nombre del archivo ejecutable
OUTPUT = simulador

# Archivos fuente
SRC_SIMULADOR = simulador.c
SRC_H = simulador.h

# Librerías necesarias (si usas algunas librerías, por ejemplo, matemáticas)
LIBS = -lm

# Regla por defecto (compila y genera el ejecutable)
all: $(OUTPUT)

# Crear el ejecutable final directamente desde el código fuente
$(OUTPUT): $(SRC_SIMULADOR) $(SRC_H)
	$(CC) $(SRC_SIMULADOR) -o $(OUTPUT) $(LIBS)

# Limpiar archivos generados
clean:
	rm -f $(OUTPUT)

# Ejecutar el programa
run: $(OUTPUT)
	./$(OUTPUT)
