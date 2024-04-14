/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.alguma.lexico;

import java.io.IOException;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.Token;

/**
 *
 * @author vinij
 */
public class Principal {

    public static void main(String[] args) throws IOException {
        System.out.println("Hello World!");
        
        // mvn clean --> limpa os arquivos da pasta target que são criados através do build (como classes compiladas e o pacote final do projeto)
        // mvn generate-sources --> gera fontes de código necessárias para o projeto antes da compilação, quando o projeto precisa de códigos que precisam ser gerados dinamicamente antes da compilação
        // mvn package --> compila
        CharStream cs = CharStreams.fromFileName(args[0]);
        AlgumaLexer lex = new AlgumaLexer(cs);
        
        Token t = null;
        
        while ((t = lex.nextToken()).getType() != Token.EOF) {
            System.out.print("<"+AlgumaLexer.VOCABULARY.getDisplayName(t.getType())+","+t.getText()+'>');
        }
        
        
        
                
    }
}
