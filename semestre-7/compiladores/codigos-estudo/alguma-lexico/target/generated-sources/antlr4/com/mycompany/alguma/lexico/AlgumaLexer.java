// Generated from com\mycompany\alguma\lexico\AlgumaLexer.g4 by ANTLR 4.7.2
package com.mycompany.alguma.lexico;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class AlgumaLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		PALAVRA_CHAVE=1, NUMINT=2, NUMREAL=3, VARIAVEL=4, CADEIA=5, OP_REL=6, 
		OP_ARIT=7, DELIM=8, ABREPAR=9, FECHAPAR=10, COMENTARIO=11, WS=12;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"PALAVRA_CHAVE", "NUMINT", "NUMREAL", "VARIAVEL", "CADEIA", "ESC_SEQ", 
			"OP_REL", "OP_ARIT", "DELIM", "ABREPAR", "FECHAPAR", "COMENTARIO", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, "':'", "'('", "')'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "PALAVRA_CHAVE", "NUMINT", "NUMREAL", "VARIAVEL", "CADEIA", "OP_REL", 
			"OP_ARIT", "DELIM", "ABREPAR", "FECHAPAR", "COMENTARIO", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public AlgumaLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "AlgumaLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\16\u00b6\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2"+
		"\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3"+
		"\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2"+
		"\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3"+
		"\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\5\2i\n\2\3\3\5"+
		"\3l\n\3\3\3\6\3o\n\3\r\3\16\3p\3\4\5\4t\n\4\3\4\6\4w\n\4\r\4\16\4x\3\4"+
		"\3\4\6\4}\n\4\r\4\16\4~\3\5\3\5\7\5\u0083\n\5\f\5\16\5\u0086\13\5\3\6"+
		"\3\6\3\6\7\6\u008b\n\6\f\6\16\6\u008e\13\6\3\6\3\6\3\7\3\7\3\7\3\b\3\b"+
		"\3\b\3\b\3\b\3\b\3\b\3\b\3\b\5\b\u009e\n\b\3\t\3\t\3\n\3\n\3\13\3\13\3"+
		"\f\3\f\3\r\3\r\7\r\u00aa\n\r\f\r\16\r\u00ad\13\r\3\r\3\r\3\r\3\r\3\16"+
		"\3\16\3\16\3\16\2\2\17\3\3\5\4\7\5\t\6\13\7\r\2\17\b\21\t\23\n\25\13\27"+
		"\f\31\r\33\16\3\2\t\4\2--//\4\2C\\c|\5\2\62;C\\c|\4\2))^^\5\2,-//\61\61"+
		"\3\2\f\f\5\2\13\f\17\17\"\"\2\u00cf\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2"+
		"\2\2\t\3\2\2\2\2\13\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25"+
		"\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\3h\3\2\2\2\5k\3\2\2\2"+
		"\7s\3\2\2\2\t\u0080\3\2\2\2\13\u0087\3\2\2\2\r\u0091\3\2\2\2\17\u009d"+
		"\3\2\2\2\21\u009f\3\2\2\2\23\u00a1\3\2\2\2\25\u00a3\3\2\2\2\27\u00a5\3"+
		"\2\2\2\31\u00a7\3\2\2\2\33\u00b2\3\2\2\2\35\36\7F\2\2\36\37\7G\2\2\37"+
		" \7E\2\2 !\7N\2\2!\"\7C\2\2\"#\7T\2\2#$\7C\2\2$%\7E\2\2%&\7Q\2\2&\'\7"+
		"G\2\2\'i\7U\2\2()\7C\2\2)*\7N\2\2*+\7I\2\2+,\7Q\2\2,-\7T\2\2-.\7K\2\2"+
		"./\7V\2\2/\60\7O\2\2\60i\7Q\2\2\61\62\7K\2\2\62\63\7P\2\2\63i\7V\2\2\64"+
		"\65\7T\2\2\65\66\7G\2\2\66\67\7C\2\2\67i\7N\2\289\7C\2\29:\7V\2\2:;\7"+
		"T\2\2;<\7K\2\2<=\7D\2\2=>\7W\2\2>?\7K\2\2?i\7T\2\2@i\7C\2\2AB\7N\2\2B"+
		"C\7G\2\2CD\7T\2\2DE\3\2\2\2EF\7K\2\2FG\7O\2\2GH\7R\2\2HI\7T\2\2IJ\7K\2"+
		"\2JK\7O\2\2KL\7K\2\2Li\7T\2\2MN\7U\2\2Ni\7G\2\2OP\7G\2\2PQ\7P\2\2QR\7"+
		"V\2\2RS\7C\2\2Si\7Q\2\2TU\7G\2\2UV\7P\2\2VW\7S\2\2WX\7W\2\2XY\7C\2\2Y"+
		"Z\7P\2\2Z[\7V\2\2[i\7Q\2\2\\]\7K\2\2]^\7P\2\2^_\7K\2\2_`\7E\2\2`a\7K\2"+
		"\2ai\7Q\2\2bc\7H\2\2cd\7K\2\2di\7O\2\2ei\7G\2\2fg\7Q\2\2gi\7W\2\2h\35"+
		"\3\2\2\2h(\3\2\2\2h\61\3\2\2\2h\64\3\2\2\2h8\3\2\2\2h@\3\2\2\2hA\3\2\2"+
		"\2hM\3\2\2\2hO\3\2\2\2hT\3\2\2\2h\\\3\2\2\2hb\3\2\2\2he\3\2\2\2hf\3\2"+
		"\2\2i\4\3\2\2\2jl\t\2\2\2kj\3\2\2\2kl\3\2\2\2ln\3\2\2\2mo\4\62;\2nm\3"+
		"\2\2\2op\3\2\2\2pn\3\2\2\2pq\3\2\2\2q\6\3\2\2\2rt\t\2\2\2sr\3\2\2\2st"+
		"\3\2\2\2tv\3\2\2\2uw\4\62;\2vu\3\2\2\2wx\3\2\2\2xv\3\2\2\2xy\3\2\2\2y"+
		"z\3\2\2\2z|\7\60\2\2{}\4\62;\2|{\3\2\2\2}~\3\2\2\2~|\3\2\2\2~\177\3\2"+
		"\2\2\177\b\3\2\2\2\u0080\u0084\t\3\2\2\u0081\u0083\t\4\2\2\u0082\u0081"+
		"\3\2\2\2\u0083\u0086\3\2\2\2\u0084\u0082\3\2\2\2\u0084\u0085\3\2\2\2\u0085"+
		"\n\3\2\2\2\u0086\u0084\3\2\2\2\u0087\u008c\7)\2\2\u0088\u008b\5\r\7\2"+
		"\u0089\u008b\n\5\2\2\u008a\u0088\3\2\2\2\u008a\u0089\3\2\2\2\u008b\u008e"+
		"\3\2\2\2\u008c\u008a\3\2\2\2\u008c\u008d\3\2\2\2\u008d\u008f\3\2\2\2\u008e"+
		"\u008c\3\2\2\2\u008f\u0090\7)\2\2\u0090\f\3\2\2\2\u0091\u0092\7^\2\2\u0092"+
		"\u0093\7)\2\2\u0093\16\3\2\2\2\u0094\u009e\7@\2\2\u0095\u0096\7@\2\2\u0096"+
		"\u009e\7?\2\2\u0097\u009e\7>\2\2\u0098\u0099\7>\2\2\u0099\u009e\7?\2\2"+
		"\u009a\u009b\7>\2\2\u009b\u009e\7@\2\2\u009c\u009e\7?\2\2\u009d\u0094"+
		"\3\2\2\2\u009d\u0095\3\2\2\2\u009d\u0097\3\2\2\2\u009d\u0098\3\2\2\2\u009d"+
		"\u009a\3\2\2\2\u009d\u009c\3\2\2\2\u009e\20\3\2\2\2\u009f\u00a0\t\6\2"+
		"\2\u00a0\22\3\2\2\2\u00a1\u00a2\7<\2\2\u00a2\24\3\2\2\2\u00a3\u00a4\7"+
		"*\2\2\u00a4\26\3\2\2\2\u00a5\u00a6\7+\2\2\u00a6\30\3\2\2\2\u00a7\u00ab"+
		"\7\'\2\2\u00a8\u00aa\n\7\2\2\u00a9\u00a8\3\2\2\2\u00aa\u00ad\3\2\2\2\u00ab"+
		"\u00a9\3\2\2\2\u00ab\u00ac\3\2\2\2\u00ac\u00ae\3\2\2\2\u00ad\u00ab\3\2"+
		"\2\2\u00ae\u00af\7\f\2\2\u00af\u00b0\3\2\2\2\u00b0\u00b1\b\r\2\2\u00b1"+
		"\32\3\2\2\2\u00b2\u00b3\t\b\2\2\u00b3\u00b4\3\2\2\2\u00b4\u00b5\b\16\2"+
		"\2\u00b5\34\3\2\2\2\16\2hkpsx~\u0084\u008a\u008c\u009d\u00ab\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}