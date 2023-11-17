import numpy as np
from decimal import Decimal,getcontext

getcontext().prec =10
a = -1
b = 1
n = 32 #METADE DO NUMERO DE SUBDIVISOES!!!

h = (b - a) / (2 * n)
x = np.arange(a, b + h, h)

aux = np.zeros(2 * n+1)

for i in range(1, 2 * n, 2):
    aux[i] = 4 * np.exp(-x[i] ** 2)

for i in range(2, 2 * n, 2):
    aux[i] = 2 * np.exp(-x[i] ** 2)

aux[0] = np.exp(-x[0] ** 2)
aux[2 * n] = np.exp(-x[2 * n] ** 2)

Tn = np.sum(aux)
Tn = (h / 3) * Tn

print(f"Integral = {Tn:.10f}")

alpha = Tn

beta0 = alpha / 2

beta2 = (-np.exp(-1) + alpha / 6) / (8 / 45)

beta4 = ((57 / 140) * alpha - (23 / 14) * np.exp(-1)) / (128 / 11025)

a0 = beta0 - 1 / 3 * beta2 + 3 / 35 * beta4

a2 = beta2 - 6 / 7 * beta4

a4 = beta4

print(f"a0 = {float(1*Decimal(str(a0)))}")
print("a1 = 0")
print(f"a2 = {float(1*Decimal(str(a2)))}")
print("a3 = 0")
print(f"a4 = {float(1*Decimal(str(a4)))}")
