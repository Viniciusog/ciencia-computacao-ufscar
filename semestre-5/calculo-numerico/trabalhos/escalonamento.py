from decimal import Decimal, getcontext
import numpy as np

def GaussJordan(M):
    nLin = len(M)
    nCol = len(M[0])

    if (nCol != nLin + 1):
        return "Número de colunas deve ser linhas+1"
    else:
        MM=[]
        xx=[]
        # inicializa xx com zeros e copia M para MM
        for i in range(nLin):
            xx.append(0)
            linha = []
            for j in range(nCol):
                linha.append(M[i][j])
            MM.append(linha)
        # início do escalonamento
        for i in range(nLin):
            # encontranto o pivô na coluna da linha atual
            pivo = i
            for j in range(i+1, nLin):
                if abs(MM[pivo][i]) < abs(MM[j][i]):
                    pivo = j
            # trocando a linha do pivô
            MM[i], MM[pivo] = MM[pivo], MM[i]
            #anulando os elementos abaixo do pivô
            for j in range(i+1, nLin):
                MM[j][i] = MM[j][i] / MM[i][i]
                for k in range(i+1, nCol):
                    MM[j][k] -= MM[j][i] * MM[i][k]
        # fim do escalonamento
        # calculando a solução
        for i in range(nLin-1, -1, -1):
            xx[i] = MM[i][nCol-1]
            for j in range(nLin-1, i, -1):
                xx[i] -= MM[i][j] * xx[j]
            xx[i] /= MM[i][i]
        return xx

def copiarMatriz(M):
    nLin = len(M)
    nCol = len(M[0])
    print(nLin)
    print(nCol)
    print("matrix dentro de copiar matriz")
    print(M)
    MM = []
    for i in range(nLin):
        linha = []
        for j in range(nCol):
            print(str(i) + ", " + str(j) + "\n")
            print("M[i][j]: ", str(M[i][j]))
            linha.append(M[i][j])
        MM.append(linha)
    return MM

def formatarMatriz(M):
    nLin = len(M)
    nCol = len(M[0])

    MM = copiarMatriz(M)   
    print("depois de copiar matriz")
    print(MM)

    for i in range(nLin):
        for j in range(nCol):
            MM[i][j] = Decimal(MM[i][j]) * 1
    return MM

# Tarefa 3
def t3():
    M = [
     [-7.857, -13.43, -1.429, -13.14, 11.14, -6.571, -2, -12, -8.429, -14.57], 
     [-13.43, 8.143, 10.71, 0.8571, 13.43, 7.143, -10.57, -12.86, -14, -26.71], 
     [6.429, 13.71, -13, -2.571, -2, 12, -7.714, -10.14, 11, 21.29],
     [4.143, 5.857, 10.29, 5.143, -2.143, -10.57, 6, -11.57, 6.143, 9.286],
     [12.71, -8.286, 3.571, 7.714, 4.286, -1.714, -10, -6.286, 6.571, 19.14],
     [-5.429, 6, -1.571, -0.8571, 7.143, 5.429, 7, 13.14, 10.57, -3.714],
     [3.714, 10.29, -5.143, 12.29, -11.71, 7.143, -0.7143, 2.286, 5.143, 0.5714],
     [10.29, 13, 6, -0.5714, -11.43, 5.714, -4.429, -6, 0.7143, -26], 
     [-5.714, -9.857, -8, 11.86, -6.429, 11.86, 3.143, 1.571, 6.143, -6.286]
     ]
    getcontext().prec = 4
    MM = formatarMatriz(M)
    print(GaussJordan(MM))

def pegarA(M, qtdLinhasColunas):
    A = []
    for i in range(qtdLinhasColunas):
        linha = []
        for j in range(qtdLinhasColunas):
            linha.append(M[i][j])
        A.append(linha)
    return A

def pegarB(M, qtdLinhas, coluna):
    B = []
    for i in range(qtdLinhas):
        B.append(M[i][coluna])
    return B

def teste():
    getcontext().prec = 3
    Ab = [[3, 1, 2, -1], [1, 1, 0, 2], [2, 2, -1, 1]]
    concatenacao = np.concatenate((Ab, Ab), axis=1)
    print("concatenação")
    print(concatenacao)
    x0 = GaussJordan(formatarMatriz(Ab))
    A = pegarA(Ab, 3)
    b = pegarB(Ab, 3, 3)
    getcontext().prec = 6
    Ax0 = np.dot(A, x0)
    print("Ax0")
    print(Ax0)
    print("b - Ax0")
    print(np.subtract(b, Ax0))



def calcularAx(A, x):
    Ax = np.dot(A, x)
    print(Ax)


# Tarefa 4
def t4():
    M = [
        [2.201, 6.657,2.880,11.35,14.57,-9.068,2.325,0.4063,-7.093, -6.209],
        [1.294,7.633,2.019,12.02,13.76,-8.395,1.658,1.037,-7.874, -5.338],
        [2.035,6.707,2.745,11.28,14.51,-9.020,2.450,0.2363,-7.101, -6.103],
        [1.286,7.453,1.964,12.03,13.79,-8.283,1.515,1.036,-7.809, -5.312],
        [2.080,6.835,2.859,11.34,14.54,-9.061,2.407,0.3073,-6.930, -6.146],
        [1.359,7.532,2.046,12.05,13.75,-8.395,1.657,1.022,-7.845, -5.305],
        [2.154,6.756,2.919,11.37,14.58,-9.085,2.462,0.3763,-7.058, -6.092],
        [1.292,7.627,2.023,12.04,13.82,-8.243,1.577,1.069,-7.731, -5.273],
        [2.077,6.717,2.915,11.29,14.49,-9.093,2.384,0.3603,-6.931, -6.182],
         ]
    quantidadeRefino = 3
    getcontext().prec = 4
    formatada = formatarMatriz(M)
    x = GaussJordan(formatada)
    print("X0")
    print(x)
    A = pegarA(x, 9)
    b = pegarB(x, 9, 9)

    for i in range(quantidadeRefino):
        getcontext().prec = 6
        Ax = np.dot(A, x)
        residuo = np.subtract(b, Ax)

        getcontext().prec = 4
        Ay = formatarMatriz(np.concatenate(A, residuo))
        y = GaussJordan(Ay)
        xi = np.sum(x, y)
        print("X" + str(i+1))
        print(xi)
        x = xi



t4()