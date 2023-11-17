import sympy as sp

x = sp.symbols('x')
a0, a1, a2, a3 = sp.symbols('a0 a1 a2 a3')

p0 = 1/2
p1 = 2/3 * x
p2 = 8/45 * (x**2 - 1/3)
p3 = 8/175 * (x**3 - 3/5 * x)

f = 4.4 * sp.cos(x) -1 * sp.sin(x)
p = a0 * p0 + a1 * p1 + a2 * p2 + a3 * p3

error = sp.integrate((f - p)**2, (x, -1, 1))  # Calcula o erro quadrático

# Encontra os valores dos coeficientes que minimizam o erro
solution = sp.solve([sp.diff(error, a0), sp.diff(error, a1), sp.diff(error, a2), sp.diff(error, a3)], (a0, a1, a2, a3))

# Imprime os valores dos coeficientes com 6 casas decimais
print(f"Coeficientes: a0 = {solution[a0]:.6f}, a1 = {solution[a1]:.6f}, a2 = {solution[a2]:.6f}, a3 = {solution[a3]:.6f}")