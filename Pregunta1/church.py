class Church:
    def __init__(self, value=0):
        self.value = value

    def suc(self):
        """Devuelve el siguiente numeral de Church."""
        return Church(self.value + 1)

    def __repr__(self):
        return f"Church({self.value})"

def suma(ch1, ch2):
    """Suma dos numerales de Church."""
    return Church(ch1.value + ch2.value)

def multiplicacion(ch1, ch2):
    """Multiplica dos numerales de Church."""
    return Church(ch1.value * ch2.value)

# Ejemplo de uso:
cero = Church()
uno = cero.suc()
dos = uno.suc()
tres = suma(dos, uno)
producto = multiplicacion(dos, tres)

print(f"Tres: {tres}")       # Church(3)
print(f"Producto: {producto}")  # Church(6)
