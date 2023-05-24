package com.viniciusog.projetotestemaven.projeto_teste_maven;

import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;

import com.google.common.math.LongMath;

public class main {
	
	public static int D = 4;
	public static void GaussJordan(BigDecimal[][] matrix) {
		
		int nLin = matrix.length;
		int nCol = matrix[0].length;
		
		if (nCol != nLin + 1) {
			System.out.println("Quantidade de colunas deve ser igual a linhas+1");
			return;
		}
		
		// armazena o valor unitário de cada variável de cada coluna (Colunas de variáveis)
		BigDecimal[] xx = new BigDecimal[nLin];
		BigDecimal[][] MM = new BigDecimal[nLin][nCol];
		
		for (int i = 0; i < nLin; i++) {
			xx[0] = BigDecimal.ZERO;
			for (int j = 0; j < nCol; j++) {
				MM[i][j] = matrix[i][j];
			}
		}
		
		print(MM);
		System.out.println(MM[2][1]);
		
		for (int i = 0; i < nLin; i++) {
			int pivo = i;
			for (int j = i+1; j < nLin; j++) {
				System.out.println("\nMM["+j+"]["+i+"]: " + MM[j][i] + ", MM["+j+"]["+i+"].abs: " + MM[j][i].abs()+", MM["+i+"]["+i+"].abs: " + MM[i][i].abs());
				if (MM[j][i].abs().compareTo(MM[i][i].abs()) == 1) {
					pivo = j;
				}
			}
			
			if (pivo != i) {
				//trocar linhas
				BigDecimal aux = null;
				for (int k = 0; k < nCol; k++) {
					aux = MM[i][k];
					System.out.println("i: " + i + ", pivo: " + pivo + ", aux: " + aux);
					MM[i][k] = MM[pivo][k];
					MM[pivo][k] = aux;
				}
			} else {
				System.out.println("Não é preciso trocar linhas.");
			}
			
			
			System.out.println("matrix linha trocada pivo");
			print(MM);
			System.out.println("");
			
			// Realizando 
			for (int j = i+1; j < nLin; j++) {
				// System.out.println("MM[j][i]: " + MM[j][i] + ", MM[i][i]: " + MM[i][i]);
				MM[j][i] = MM[j][i].divide(MM[i][i], new MathContext(D, RoundingMode.HALF_DOWN)); // Calcular o multiplicador
				System.out.println("mult: " + MM[j][i]);
				for (int k = i+1; k < nCol; k++) {
					MM[j][k] = MM[j][k].subtract(MM[j][i].multiply(MM[i][k])).round(new MathContext(D, RoundingMode.HALF_DOWN)); 
				}		
			}
			
			System.out.println("matrix após multiplicar");
			print(MM);
		}
		
		for (int i = nLin-1; i > -1; i--) {
			xx[i] = MM[i][nCol-1];
			for (int j = nLin-1; j > i; j--) {
				xx[i] = xx[i].subtract(MM[i][j].multiply(xx[j])).round(new MathContext(D, RoundingMode.HALF_DOWN));
			}
			xx[i] = xx[i].divide(MM[i][i], new MathContext(D, RoundingMode.HALF_DOWN));
		}
		
		
		// imprimindo resultado
		for (int i = 0; i < nLin; i++) {
			System.out.println(xx[i]);
		}
	}
	
	public static final double [][] m = {
			{-7.857, -13.43, -1.429, -13.14, 11.14, -6.571, -2, -12, -8.429, -14.57}, 
			{-13.43, 8.143, 10.71, 0.8571, 13.43, 7.143, -10.57, -12.86, -14, -26.71}, 
			{6.429, 13.71, -13, -2.571, -2, 12, -7.714, -10.14, 11, 21.29}, 
			{4.143, 5.857, 10.29, 5.143, -2.143, -10.57, 6, -11.57, 6.143, 9.286}, 
			{12.71, -8.286, 3.571, 7.714, 4.286, -1.714, -10, -6.286, 6.571, 19.14}, 
			{-5.429, 6, -1.571, -0.8571, 7.143, 5.429, 7, 13.14, 10.57, -3.714}, 
			{3.714, 10.29, -5.143, 12.29, -11.71, 7.143, -0.7143, 2.286, 5.143, 0.5714}, 
			{10.29, 13, 6, -0.5714, -11.43, 5.714, -4.429, -6, 0.7143, -26}, 
			{-5.714, -9.857, -8, 11.86, -6.429, 11.86, 3.143, 1.571, 6.143, -6.286}, 			
		};
	
	public static void print(BigDecimal[][] matrix) {
		System.out.println("imprimindo...");
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix[0].length; j++) {
				System.out.print(matrix[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	public static BigDecimal[][] getBigDecimalMatrix(double[][] matrix) {	
		int lines = matrix.length;
		int columns = matrix[0].length;
		
		BigDecimal[][] r = new BigDecimal[lines][columns];
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				r[i][j] = new BigDecimal(matrix[i][j], new MathContext(D, RoundingMode.DOWN));//.setScale(4, RoundingMode.HALF_EVEN);
			}
		}
		
		print(r);
		
		return r;
	}
	
	public static void main(String[] args) {
		GaussJordan(getBigDecimalMatrix(m));
	}
}
