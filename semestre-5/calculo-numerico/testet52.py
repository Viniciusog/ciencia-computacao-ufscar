import math

# Função para calcular f(x) = e^(-x^2)
def f(x):
    return math.exp(-x**2)

# Função para calcular o valor de S(n) pelo Método do Simpson
def simpson_rule(a, b, n):
    h = (b - a) / (2 * n)
    sum_odd = 0
    sum_even = 0

    for i in range(1, 2 * n):
        x = a + i * h
        if i % 2 == 0:
            sum_even += f(x)
        else:
            sum_odd += f(x)

    integral_approx = (h / 3) * (f(a) + 4 * sum_odd + 2 * sum_even + f(b))
    return integral_approx

# Precisão requerida nas primeiras oito casas decimais
precision = 1e-8

# Intervalo de integração
a = -1.2
b = 2.4

# Inicialização dos valores
n = 2
S_n_minus_1 = simpson_rule(a, b, n - 1)
S_n = simpson_rule(a, b, n)

# Loop para encontrar a convergência nas primeiras oito casas decimais
while abs(S_n_minus_1 - S_n) >= precision and n < 10000:  # Added a limit to prevent an infinite loop
    n += 1
    S_n_minus_1 = S_n
    S_n = simpson_rule(a, b, n)

# Resultado final
print("n:", n)
print("S(n):", S_n)