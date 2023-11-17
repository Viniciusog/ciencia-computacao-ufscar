import math

a = 1.3 
b = 2.6

def truncar(valor):
    return int(valor * 10**8)/10**8

def coincidemNesimaCasaDecimal(valor1, valor2):
    valor1T = truncar(valor1)
    valor2T = truncar(valor2)

    if valor1T == valor2T:
        return True
    return False

def f(x):
    return math.exp(x)/x

def meuX(meuI, meuN):
    return a + ((b-a)/meuN)*meuI

def t(meuN):
    resultado = 0
    resultado += f(a) / 2
    resultado += f(b) / 2

    for Iatual in range(1, meuN):
        Xatual = meuX(Iatual, meuN)
        resultado += f(Xatual)

    h = (b-a)/meuN

    return h * resultado

continuar = True
n = 2 #como n=3, então n-1 = 2, aí dá certo

tnMenos1 = 0
tn = 0

while continuar:
    tnMenos1 = t(n-1)
    tn = t(n)
    continuar = not coincidemNesimaCasaDecimal(tnMenos1, tn)
    n += 1

print("n: " + str(n))
print("tnMenos1: " + str(truncar(tnMenos1)))
print("tn: " + str(truncar(tn)))