package main;

public class Node {
	
	private Double freq;
	private String value;
	private Node left;
	private Node right;
	
	public Node() {
		this.left = null;
		this.right = null;
		this.freq = null;
		this.value = null;
	}
	
	public Node(String value, Double freq) {
		this.freq = freq;
		this.value = value;
	}
	
	public void setFreq(Double freq) {
		this.freq = freq;
	}
	
	public void setValue(String value) {
		this.value = value;
	}
	
	public Double getFreq() {
		return this.freq;
	}
	
	public String getValue() {
		return this.value;
	}
	
	public void setLeft(Node left) {
		this.left = left;
	}
	
	public void setRight(Node right) {
		this.right = right;
	}
	
	public Node getRight() {
		return this.right;
	}
	
	public Node getLeft() {
		return this.left;
	}
	
	public boolean isLeaf() {
		return this.left == null && this.right == null;
	}

	
	@Override
	public String toString() {
		return "[freq=" + freq + ", value=" + value + ", left=" + left + ", right=" + right + "]";
	}
}