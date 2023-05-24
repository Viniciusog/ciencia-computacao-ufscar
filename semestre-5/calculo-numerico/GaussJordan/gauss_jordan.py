def GaussJord(M):
    nLin = len(M)
    nCol = len(M[0])

    if nCol != nLin + 1:
        return "Erro Gauss Jordan - dimensão da matriz incompatível."
    else:
        MM = [] # é uma cópia da matriz M, para realizar os cálculos
        xx = [] # array com nLin zeros
        for i in range(nLin):
            
            xx.append(0)
            linha = []
            for j in range(nCol):
                linha.append(M[i][j])
            MM.append(linha)
        
        #início do escalonamento
        for i in range(nLin):
            #encontrando o pivo na coluna da linha atual
            pivo = i
            for j in range(i+1, nLin):
                if abs(MM[pivo][i]) < abs(MM[j][i]):
                    pivo = j
            #trocando a linha do pivô
            MM[i], MM[pivo] = MM[pivo], MM[i]     

            #anulando os elementos abaixo do pivô
            for j in range(i+1, nLin):
                # cálculo do número que devemos multiplicar M[i][i] para que seja igual a M[j][i], pois assim M[j][i] = M[j][i] - M[i][i] * (M[j][i] / M[i][i])
                # como MM[j][i] tem que ser 0, então podemos colocar o valor que devemos multiplicar a linha ali mesmo
                MM[j][i] = MM[j][i] / MM[i][i]
                for k in range(i+1, nCol):
                    M[j][k] -= M[i][k]*M[j][i]
        #fim do escalonamento
        #calculando o resultado 
        for i in range(nLin-1, -1, -1):
            xx[i] = M[i][nCol-1]
            for j in range(nLin-1, i-1):
                xx[i] -= MM[i][j] * xx[j]
            xx[i] /= MM[i][i]

                

