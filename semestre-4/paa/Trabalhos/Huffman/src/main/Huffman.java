package main;

import static java.util.Map.entry;

import java.util.HashMap;
import java.util.Map;

public class Huffman {
	public static Map<String, Double> portuguese = Map.ofEntries(
		 	entry("a",  14.63),
		 	entry("b",  1.04),
		 	entry("c",  3.88),
		 	entry("d",  4.99),
		 	entry("e",  12.57),
		 	entry("f",  1.02),
		 	entry("g",  1.3),
		 	entry("h",  1.28),
		 	entry("i",  6.18),
		 	entry("j",  0.4),
		 	entry("k",  0.02),
		 	entry("l",  2.78),
		 	entry("m",  4.74),
		 	entry("n",  5.05),
		 	entry("o",  10.73),
		 	entry("p",  2.52),
		 	entry("q",  1.2),
		 	entry("r",  6.53),
		 	entry("s", 7.81),
		 	entry("t", 4.34),
		 	entry("u", 4.63),
		 	entry("v", 1.67),
		 	entry("w", 0.01),
		 	entry("x", 0.21),
		 	entry("y", 0.01),
		 	entry("z", 0.47)
		 );

	public static Map<String, Double> english = Map.ofEntries(
			entry("a", 8.167), 
			entry("b", 1.492), 
			entry("c", 2.782),
			entry("d", 4.253), 
			entry("e", 12.702), 
			entry("f", 2.228),
			entry("g", 2.015), 
			entry("h", 6.094), 
			entry("i", 6.966),
			entry("j", 0.153), 
			entry("k", 0.772), 
			entry("l", 4.025),
			entry("m", 2.406), 
			entry("n", 6.749), 
			entry("o", 7.507),
			entry("p", 1.929), 
			entry("q", 0.095), 
			entry("r", 5.987),
			entry("s", 6.327), 
			entry("t", 9.056), 
			entry("u", 2.758),
			entry("v", 0.978), 
			entry("w", 2.360), 
			entry("x", 0.150),
			entry("y", 1.974), 
			entry("z", 0.074)
		);
			
	
	// Vai funcionar como a nossa fila de prioridades
	private Map<String, Node> nodeMap = new HashMap<>();
	private Map<String, String> codes = new HashMap<>();
	
	public void apply(Map<String, Double> map) {
		generateNodeMap(map);
		generateTree();
		generateCodesWrapper();
		printCodes();
		printResults(map);
	}
	
	// Pega a lista de frequências e gera um nó para cada caractere
	private void generateNodeMap(Map<String, Double> map) {
		nodeMap.clear();
		for (Object key : map.keySet()) {
			nodeMap.put(String.valueOf(key), new Node(toString().valueOf(key), map.get(key)));
		}
	}
	
	// Retorna o nó que contém a menor frequência 
	private Node getMinNode() { 
		Double minFreq = Double.MAX_VALUE;
		Node minNode = null;
		for (String key : nodeMap.keySet()) {
			if (nodeMap.get(key).getFreq() < minFreq) {
				minFreq = nodeMap.get(key).getFreq();
				minNode = nodeMap.get(key);
			}
		}
		return minNode;
	}
	
	// Gera a árvore de huffman de acordo com a lista de frequências
	private void generateTree() {
		while (nodeMap.size() > 1) {
			Node min1 = getMinNode();
			nodeMap.remove(min1.getValue());
			Node min2 = getMinNode();
			nodeMap.remove(min2.getValue());
			
			Node aux = new Node();
			aux.setValue(min1.getValue().concat(min2.getValue()));
			aux.setFreq(min1.getFreq() + min2.getFreq());
	
			aux.setLeft(min1);
			aux.setRight(min2);
			
			nodeMap.put(aux.getValue(), aux);
		}
	}
	
	// Função wrapper que chama generateCodes para gerar os códigos
	// dos caracteres de acordo com a árvore de huffman
	private void generateCodesWrapper() {
		codes.clear();
		generateCodes(getMinNode(), "");
	}
	
	private void generateCodes(Node node, String code) {
		if (node.getRight() == null && node.getLeft() == null) {
			codes.put(node.getValue(), code);
			return;
		}
		generateCodes(node.getLeft(), code.concat("0"));
		generateCodes(node.getRight(), code.concat("1"));
	}
	
	private void printCodes() {
		System.out.println();
		for (String key : codes.keySet()) {
			System.out.println(key + ": " + codes.get(key));
		}
	}
	
	private void printResults(Map<String, Double> map) {
		int withoutHuffBitsSize = (int)(Math.log(codes.size()) / Math.log(2)) + 1;
		System.out.println("\n--Sem utilizar Huffman--");
		System.out.println("Quantidade de caracteres: " + codes.size());
		System.out.println("Tamanho médio dos códigos dos caracteres: " + withoutHuffBitsSize);
		System.out.println("Total de bits (quantidade de caracteres * média de bits por caractere): " 
		+ withoutHuffBitsSize * codes.size());
		
		double huffAverageBitsSize = 0;
		for (String key : codes.keySet()) {
			// Dividindo por 100 pois os valores estão em porcentagem
			huffAverageBitsSize += (map.get(key) / 100) * codes.get(key).length();
		}
		System.out.println("\n--Utilizando Huffman--");
		System.out.println("Quantidade de caracteres: " + codes.size());
		System.out.printf("Tamanho médio dos códigos dos caracteres: %.3f", huffAverageBitsSize);
		System.out.println("\nTotal de bits (quantidade de caracteres * média de bits por caractere): " 
		+ huffAverageBitsSize * codes.size());
	}
}

