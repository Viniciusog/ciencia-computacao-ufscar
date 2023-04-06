#Projeto:   Algoritmo de Kruskal para encontrar uma Minimum Spanning Tree
#Membros:   Vinicius de Oliveira Guimarães  
#           Vitor Enzo Araujo Costa         
#
#Professor: Alexandre Luis Magalhães Levada

import random
import numpy as np
import networkx as nx

#Retorna um grafo F totalmente desconexo
def make_Set(G):
    T = nx.Graph()

    for v in G.nodes():
        T.add_node(v)
        T.nodes[v]['parent'] = v
        T.nodes[v]['rank'] = 0
    
    return T

#Encontra recursivamente o nó raiz ao qual determinado nó v pertence
def find_Set(v, F):
    if v != F.nodes[v]['parent']:
        F.nodes[v]['parent'] = find_Set(F.nodes[v]['parent'], F)

    return F.nodes[v]['parent']

#Conecta dois nós u, v
def link(u, v, F):
    if F.nodes[u]['rank'] > F.nodes[v]['rank']:
        F.nodes[v]['parent'] = u

    else:
        F.nodes[u]['parent'] = v
        if F.nodes[u]['rank'] == F.nodes[v]['rank']:
            F.nodes[v]['rank'] += 1

#Utiliza link() para conectar as raizes de dois nós u, v
def union(u, v, F):
    link(find_Set(u, F), find_Set(v, F), F)


def mst_Kruskal(G):
    #Tree é a lista de vértices que farão parte da MST, ela é inicializada vazia
    Tree = []

    #F é resultado de um grafo desconexo de nós com atributo pai e rank
    F = make_Set(G)

    #Uma breve explicação sobre o funcionamento do sorted():
    #   G.edges retorna uma lista das arestas adicionadas no grafo G, quando a gente define data = True
    #estamos basicamente incluindo o peso que foi definido como terceiro elemento para cada tupla como
    #um dicionário, onde a chave 'weight' é o nome do atributo definido para os pesos das arestas.
    #   A função lambda avalia cada tupla t e compara elas entre si utilizando o terceiro elemento, no
    #caso a chave 'weight', retornando um valor padrão 1 caso a chave não seja encontrada.
    list_of_edges = sorted(G.edges(data = True), key = lambda t: t[2].get('weight', 1))

    for u, v, w in list_of_edges:
        if find_Set(u, F) != find_Set(v, F):
            Tree.append((u, v, w))
            union(u, v, F)
            
    return Tree        


def inicializa_Grafo():
    #Cria grafo vazio
    G = nx.Graph()

    #Adiciona vertices
    G.add_node('a')
    G.add_node('b')
    G.add_node('c')
    G.add_node('d')
    G.add_node('e')
    G.add_node('f')
    G.add_node('g')
    G.add_node('h')
    G.add_node('i')

    #Adiciona aresta
    G.add_edge('a', 'b', weight = 4)
    G.add_edge('a', 'h', weight = 8)

    G.add_edge('b', 'c', weight = 8)
    G.add_edge('b', 'h', weight = 11)

    G.add_edge('c', 'd', weight = 7)
    G.add_edge('c', 'f', weight = 4)
    G.add_edge('c', 'i', weight = 2)

    G.add_edge('d', 'e', weight = 9)
    G.add_edge('d', 'f', weight = 14)

    G.add_edge('e', 'f', weight = 10)

    G.add_edge('f', 'g', weight = 2)

    G.add_edge('g', 'h', weight = 1)
    G.add_edge('g', 'i', weight = 6)

    G.add_edge('h', 'i', weight = 7)


    return G


G = inicializa_Grafo()


for u, v, w in mst_Kruskal(G):
    print(u, v, w)

















