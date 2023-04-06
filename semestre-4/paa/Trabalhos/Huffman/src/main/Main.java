package main;

import java.util.Locale;

public class Main {
	
	public static void main(String[] args) {
		Locale.setDefault(Locale.US);
		
		Huffman h = new Huffman();
		
		System.out.println("PORTUGUÊS");
		h.apply(h.portuguese);
		System.out.println("\nINGLÊS");
		h.apply(h.english);
	}
}