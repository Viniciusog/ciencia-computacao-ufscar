import numpy as np

def truncate(number, n):
	return int(number * 10**n) / 10**n

def jacobi(A, B):
	x = np.zeros_like(B)  # Matriz das soluções (inicialmente com 0s)
	ant = x.copy()
	k = 0
	ok = 0

	# Limita em 100 iterações
	while k < 100:
		ant = x.copy()
		ok = 0
	 	
		for i in range(len(A)):
			x[i] = B[i]
			for j in range(len(A[0])):
				if i != j:
 					x[i] -= A[i][j] * ant[j]
			x[i] /= A[i][i]

		# Trunca na 4a casa decimal e compara todos os elementos (condição de parada)
		for i, j in zip(x, ant):
			if int(i*10000) == int(j*10000):
				ok += 1
		if ok == len(x): break # Se todos os elementos dos 2 arrays forem iguais, finaliza

		k += 1

	print(f'[Jacobi] {k+1} iterações')

	return x

def gauss_seidel(A, B):
	x = np.zeros_like(B)  # Matriz das soluções (inicialmente com 0s)
	ant = x.copy()
	k = 0
	ok = 0

	# Limita em 100 iterações
	while k < 100:
		print("a")
		ant = x.copy()
		ok = 0
	 	
		for i in range(len(A)):
			x[i] = B[i]
			for j in range(len(A[0])):
				if i != j:
 					x[i] -= A[i][j] * x[j]
			x[i] /= A[i][i]

		# Trunca na 4a casa decimal e compara todos os elementos (condição de parada)
		for i, j in zip(x, ant):
			if int(i*10000) == int(j*10000):
				ok += 1
		if ok == len(x): break # Se todos os elementos dos 2 arrays forem iguais, finaliza

		k += 1

	print(f'[Gauss-Seidel] {k+1} iterações')

	return x

def resolver(A, B):
	# Jacobi
	for k in jacobi(A, B):
		print(f'{round(k.item(), 4)}')
	
	print('\n')
	
	# Gauss-Seidel
	for k in gauss_seidel(A, B):
		print(f'{round(k.item(), 4)}')
		









# ----------------------------------------------------------------------------





# Matriz A
A = '''4.121 0.052 -0.862 0.062 -0.298 0.652 -0.642 0.555 -0.712
0.156 5.708 0.847 -0.378 0.838 -0.56 0.963 -0.96 0.497
-0.852 0.891 4.693 0.217 -0.964 0.132 -0.612 0.726 -0.179
0.601 -0.19 0.71 4.295 0.273 -0.432 0.14 -0.621 0.905
-0.164 0.645 -0.174 0.123 4.108 0.446 -0.695 0.735 -0.37
0.844 -0.293 0.878 -0.746 0.335 5.638 0.946 -0.177 0.718
-0.019 0.485 -0.911 0.055 -0.765 0.031 3.947 0.909 -0.063
0.724 -0.322 0.661 -0.355 0.092 -0.652 0.329 4.763 0.766
-0.971 0.127 -0.614 0.607 -0.133 0.815 -0.806 0.376 5.443'''


B = '''7.3
0.4
6.1
-1.4
9.3
-5.4
-2.7
-0.3
5.7'''

# Transforma os textos em matrizes
A = np.array([[float(num) for num in row.split()] for row in A.split('\n')])
B = np.array([[float(num) for num in row.split()] for row in B.split('\n')])