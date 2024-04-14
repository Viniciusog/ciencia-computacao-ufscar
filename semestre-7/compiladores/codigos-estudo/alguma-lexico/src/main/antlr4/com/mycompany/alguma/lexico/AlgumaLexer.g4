lexer grammar AlgumaLexer;

PALAVRA_CHAVE: 'DECLARACOES' | 'ALGORITMO' | 'INT' | 'REAL' | 'ATRIBUIR' | 'A' | 'LER'
    'IMPRIMIR' | 'SE' | 'ENTAO' | 'ENQUANTO' | 'INICIO' | 'FIM' | 'E' | 'OU';

// +- é opcional. ()+ representa o fecho positivo onde temos que ter repetição uma ou mais vezes

NUMINT: ('+'|'-')? ('0'..'9')+;

NUMREAL: ('+'|'-')? ('0'..'9')+ '.' ('0'..'9')+;

// começo com letra seguido de letra ou número uma ou mais vezes
VARIAVEL: ('a'..'z'|'A'..'Z')('a'..'z'|'A'..'Z'|'0'..'9')*;

// a cadeia começa com uma aspas e pode conter uma sequencia de escape e qualquer coisa que não seja aspas ou barra, finalizando com aspas
// começa e termina com aspas e tem qualquer coisa entre. 
// Dessa forma .*? estamos transformando de ganancioso para não ganancioso
// CADEIA: '\'' .*? '\'';
CADEIA: '\'' (ESC_SEQ | ~('\'' | '\\'))* '\'';

// é uma barra e uma aspas
// indica para o antlr que essa regra não é para gerar tokens, é apenas usada como auxiliar
// no nosso caso estamos usando como auxiliar da regra CADEIA   
fragment 
ESC_SEQ:'\\\'';

OP_REL: '>' | '>=' | '<' | '<=' | '<>' | '=';

OP_ARIT: '+' | '-' | '*' | '/';

DELIM: ':';

ABREPAR: '(';

FECHAPAR: ')';

// É uma linha que começa com %, seguida de qualquer coisa que não seja \n e terminando com \n
COMENTARIO: '%' ~('\n')* '\n' -> skip;

WS: (' ' | '\t' | '\r' | '\n') -> skip;





// Letra: 'a'..'z'|'A'..'Z';
// Digito: '0'..'9';

// Se temos ALGORITMOBLA e tem essa regra PCAlgoritmo e Variavel, o antlr identifica o ALGORITMO e identifica o ALGORITMOBLA e escolhe a regra que fica com a maior quantidade de letras, no caso VARIAVEL
// Se temos a regra Variavel antes de PCAlgoritmo e encontramos a palavra ALGORITMO, o antlr tem a opção de marcar como sendo da regra VARIAVEL E PCAlgoritmo, ele escolhe a primeira regra
// Por isso que as palavras chave devem ser definidas antes das variáveis, pois VARIAVEL é uma regra muito ampla

// PCAlgoritmo: 'ALGORITMO' {System.out.println("[Palavra-chave,"+getText()+"]");};
//Temos uma letra seguida de uma letra ou dígito uma ou mais vezes
// o aNTLR TEM CARACTERÍSTICA GANANCIOSA, sempre que reconhecer duas cadeias que tem regras parecidas, ele vai escolher a regra que fica com a maior quantidade de caracteres

// SE temo
// Variavel: Letra (Letra | Digito)* {System.out.println("[Var,"+getText()+"]");};
//Ao fazer o build na parte de projects, iremos compilar o projeto e também como estamos
// usando o maven, o plugin que oconfiguramos do antlr vai gerar os arquivos necessários do antlr
    
