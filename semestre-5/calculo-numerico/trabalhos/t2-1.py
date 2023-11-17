import numpy as np

# Pontos tabelados
x = np.array([-1, -0.8, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.8, 1])
y = np.array([0.774, 0.257, -0.552, 0.418, -0.743, -0.017, -0.018, -0.896, 0.7, -0.023, -0.679])

# Montar matriz X com as potências de x
X = np.column_stack([x ** i for i in range(10)])

# Calcular os parâmetros a usando o método dos mínimos quadrados
A = np.linalg.inv(X.T @ X) @ X.T @ y

# Imprimir os parâmetros encontrados
print("Parâmetros do polinômio de nono grau:")
for i, param in enumerate(A):
    print(f"a{i} = {param:.8f}")