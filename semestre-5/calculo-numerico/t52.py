import math

a = -1.2 
b = 2.4

def truncar(valor):
    return int(valor * 10**8)/10**8

def coincidemNesimaCasaDecimal(valor1, valor2):
    valor1T = truncar(valor1)
    valor2T = truncar(valor2)

    if valor1T == valor2T:
        return True
    return False

def f(x):
    return math.exp(-x**2)

def valor_aproximado_integral(meuN):
    h = (b - a) / (2*meuN)
    somaPar = 0
    somaImpar = 0

    for i in range(1, 2*meuN):
        x = a + i*h
        if (i % 2 == 0):
            somaPar += f(x)
        else:
            somaImpar += f(x)

    return (h / 3) * (f(a) + 4*somaImpar + 2*somaPar + f(b))

continuar = True
n = 2 #como n=3, então n-1 = 2, aí dá certo

snMenos1 = 0
sn = 0

while continuar and n < 1000:
    snMenos1 = valor_aproximado_integral(n-1)
    sn = valor_aproximado_integral(n)
    continuar = abs(snMenos1 - sn) >= 1e-8
    n += 1

print("n: " + str(n))
print("snMenos1: " + str(truncar(snMenos1)))
print("sn: " + str(truncar(sn)))