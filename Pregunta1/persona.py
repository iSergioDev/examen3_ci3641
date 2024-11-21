class Persona:
    def __init__(self, nombre, edad):
        self.nombre = nombre
        self.edad = edad

    def __repr__(self):
        return f"{self.nombre} ({self.edad} años)"

class ConjuntoPersonas:
    def __init__(self):
        self.personas = []

    def agregar(self, persona):
        self.personas.append(persona)

    def cantidad(self):
        return len(self.personas)

    def mayores_de_edad(self):
        return [p for p in self.personas if p.edad >= 18]

    def nombre_mas_comun(self):
        from collections import Counter
        nombres = [p.nombre for p in self.personas]
        return Counter(nombres).most_common(1)[0][0]

# Ejemplo de uso:
grupo = ConjuntoPersonas()
grupo.agregar(Persona("Ana", 22))
grupo.agregar(Persona("Juan", 17))
grupo.agregar(Persona("Ana", 20))

print(f"Cantidad de personas: {grupo.cantidad()}")
print(f"Mayores de edad: {grupo.mayores_de_edad()}")
print(f"Nombre más común: {grupo.nombre_mas_comun()}")
