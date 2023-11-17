import math

def f(x):
    return x**2 - math.cos(x)

def f_prime(x):
    return 2*x + math.sin(x)

def phi(x, alpha):
    return x + alpha * f(x)

def find_root(alpha):
    max_iterations = 1000
    tolerance = 1e-8
    x0 = math.pi / 4  # Valor inicial dentro do intervalo [0, π/2]
    xk = x0+1

    for k in range(max_iterations):
        xk_plus_1 = phi(xk, alpha)

        # Verifica o critério de parada
        if abs(xk_plus_1 - xk) < tolerance:
            return k

        xk = xk_plus_1

    return -1  # Se não convergir dentro do número máximo de iterações

# Valores de alpha fornecidos
alphas = [-0.00886, -0.20447, -0.39691]

for alpha in alphas:
    root_iteration = find_root(alpha)
    print(f"Para alpha = {alpha:.5f}, K = {root_iteration}")