def ordenar(array, inicio, fim):
    if (inicio < fim):
        meio = int((fim-inicio) / 2) + inicio
        print("Meio: " + str(meio))
        print(array[inicio:fim+1])
        ordenar(array, inicio, meio-1)
        ordenar(array, meio, fim)
        intercala(array, inicio, meio, fim)
        print("Intercala: ")
        print(array)

    
def intercala(array, inicio1, inicio2, fim):
    w = []
    contador = 0
    i = inicio1
    j = inicio2

    while i < j and j <= fim:
        if (array[i] <= array[j]):
            w[contador] = array[i]
            i += 1
            contador += 1
        else: #array[inicio2] < array[inicio1]
           w[contador] = array[j]
           j += 1
           contador += 1
    
    # Quando sair do while, é porque o inicio1 chegou em inicio2 ou inicio2 chegou no fim do array
    while (i < j):
        w[contador] = array[i]
        i += 1
        contador += 1

    while (j <= fim):
        w[contador] = array[j]
        j += 1
        contador += 1

    # se inseriu um elemento, então o contador que era 0 vai ser 1, logo, iremos percorrer de 0 até ser menor do que 1 (contador)
    for it in range(contador):
        array[inicio1 + it] = w[it]


array = [3, 6, 7, 2, 9, 1, 8, 4, 5]
print("começando")
ordenar(array, 0, len(array) - 1)
print(array)