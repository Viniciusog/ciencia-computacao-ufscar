from decimal import Decimal, getcontext
import numpy as np

# Escalonamento
def GaussJord(M):
    nLin = len(M)
    nCol = len(M[0])
    if nCol != nLin + 1:
        return 'erro - dimensao incompativel'
    else:
        MM = []
        xx = []
        for i in range(nLin):
            xx.append(0)
            linha = []
            for j in range(nCol):
                linha.append(M[i][j])
            MM.append(linha)
        for i in range(nLin):
            pivo = i
            for j in range(i+1, nLin):
                if abs(MM[pivo][i]) < abs(MM[j][i]):
                    pivo = j
            MM[i] , MM[pivo] = MM[pivo] , MM[i]
            for j in range(i+1,nLin):
                MM[j][i] = MM[j][i] / MM[i][i]
                for k in range(i+1, nCol):
                    MM[j][k] -= MM[j][i]*MM[i][k]

        for i in range(nLin-1,-1,-1):
            xx[i] = MM[i][nCol-1]
            for j in range(nLin-1,i,-1):
                xx[i] -= MM[i][j]*xx[j]
            xx[i] /= MM[i][i]
        return np.array(xx)

def arredondar(array):
    decimal_array = np.empty_like(array, dtype=object)
    iterator = np.nditer(array, flags=['multi_index', 'refs_ok'])
    
    for x in iterator:
        decimal_array[iterator.multi_index] = Decimal(str(x))
    
    return decimal_array

def resolver(A, B):
	# Elementos se tornam objetos Decimal()
	getcontext().prec = 4
	A = arredondar(A)
	B = arredondar(B)
	
	# Primeiro escalonamento
	x = np.concatenate((A, B), axis=1)
	x = GaussJord(x)
		
	print('Primeiro set de respostas:')
	for i in x: print(i)
		
	# Resposta
	for i in range(3):
		# Dobra a precisão
		getcontext().prec = 8
		
		# Calcula o resíduo
		r = B - (A.dot(x)).reshape((9, 1))
		
		# Retorna à precisão original
		getcontext().prec = 4
		
		# Reescalona
		y = np.concatenate((A, r), axis=1) # Une as matrizes
		y = GaussJord(y) # Escalona
		
		# Soma o resíduo com a resposta: refinamento
		x = x.reshape((9,1)) + y.reshape((9,1))
			
		print(f'\nRefinamento: {i+1}')
		for j in x: print(j[0])
# ----------------------------------------------------------------------------

# Matriz A

A = '''2.201 6.657 2.880 11.35 14.57 -9.068 2.325 0.4063 -7.093 
1.294 7.633 2.019 12.02 13.76 -8.395 1.658 1.037 -7.874  
2.035 6.707 2.745 11.28 14.51 -9.020 2.450 0.2363 -7.101  
1.286 7.453 1.964 12.03 13.79 -8.283 1.515 1.036 -7.809 
2.080 6.835 2.859 11.34 14.54 -9.061 2.407 0.3073 -6.930  
1.359 7.532 2.046 12.05 13.75 -8.395 1.657 1.022 -7.845  
2.154 6.756 2.919 11.37 14.58 -9.085 2.462 0.3763 -7.058  
1.292 7.627 2.023 12.04 13.82 -8.243 1.577 1.069 -7.731  
2.077 6.717 2.915 11.29 14.49 -9.093 2.384 0.3603 -6.931'''

B = '''-6.209
-5.338
-6.103
-5.312
-6.146
-5.305
-6.092
-5.273
-6.182'''
    
# Transforma os textos em matrizes
A = np.array([[float(num) for num in row.split()] for row in A.split('\n')])
B = np.array([[float(num) for num in row.split()] for row in B.split('\n')])

resolver(A, B)