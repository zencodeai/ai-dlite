/*
 *  Copyright 2016 zen.code.ai
 *
 *  This file is part of dlite.
 *
 *  dlite is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  dlite is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dlite.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// $ANTLR 2.7.7 (20060906): "OntologyParser.g" -> "OntologyParser.java"$

package DL.Ontology.Parser.Compact;

import antlr.TokenBuffer;
import antlr.TokenStreamException;
import antlr.TokenStreamIOException;
import antlr.ANTLRException;
import antlr.LLkParser;
import antlr.Token;
import antlr.TokenStream;
import antlr.RecognitionException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.ParserSharedInputState;
import antlr.collections.impl.BitSet;

import DL.Ontology.*;
import DL.Ontology.Expression.*;
import DL.Ontology.Parser.*;

public class OntologyParser extends antlr.LLkParser       implements OntologyParserTokenTypes
 {

    // Parser's context
    private ParserContext context;

    // Set context
    public void setContext(ParserContext context) { this.context = context; } 

protected OntologyParser(TokenBuffer tokenBuf, int k) {
  super(tokenBuf,k);
  tokenNames = _tokenNames;
}

public OntologyParser(TokenBuffer tokenBuf) {
  this(tokenBuf,1);
}

protected OntologyParser(TokenStream lexer, int k) {
  super(lexer,k);
  tokenNames = _tokenNames;
}

public OntologyParser(TokenStream lexer) {
  this(lexer,1);
}

public OntologyParser(ParserSharedInputState state) {
  super(state,1);
  tokenNames = _tokenNames;
}

	public final void ontology() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			_loop3:
			do {
				if ((LA(1)==NAME)) {
					definition();
				}
				else {
					break _loop3;
				}
				
			} while (true);
			}
			System.out.println("ontology");
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		}
	}
	
	public final void definition() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			concept();
			context.DefinitionNew();
			match(DEFINE);
			expr();
			match(SEMI);
			}
			System.out.println("definition"); context.DefinitionEnd();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		}
	}
	
	public final void concept() throws RecognitionException, TokenStreamException {
		
		Token  v = null;
		
		try {      // for error handling
			v = LT(1);
			match(NAME);
			System.out.println("concept " + v.getText()); context.NewConcept(v.getText());
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_2);
		}
	}
	
	public final void expr() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			union();
			}
			System.out.println("expression");
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void union() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			inter();
			{
			_loop11:
			do {
				if ((LA(1)==UNION)) {
					match(UNION);
					inter();
					System.out.println("union"); context.ApplyDsj();
				}
				else {
					break _loop11;
				}
				
			} while (true);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_4);
		}
	}
	
	public final void inter() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			argument();
			{
			_loop15:
			do {
				if ((LA(1)==INTER)) {
					match(INTER);
					argument();
					System.out.println("inter"); context.ApplyCnj();
				}
				else {
					break _loop15;
				}
				
			} while (true);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		}
	}
	
	public final void argument() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			switch ( LA(1)) {
			case NAME:
			{
				concept();
				break;
			}
			case TOP:
			{
				top();
				break;
			}
			case BOTTOM:
			{
				bottom();
				break;
			}
			case CMPL:
			{
				complement();
				break;
			}
			case UNIV:
			{
				univ();
				break;
			}
			case EXIST:
			{
				exist();
				break;
			}
			case LP:
			{
				match(LP);
				union();
				match(RP);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			System.out.println("argument");
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		}
	}
	
	public final void top() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(TOP);
			System.out.println("top"); context.ApplyTop();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		}
	}
	
	public final void bottom() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(BOTTOM);
			System.out.println("bottom"); context.ApplyBottom();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		}
	}
	
	public final void complement() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(CMPL);
			argument();
			System.out.println("complement"); context.ApplyCmpl();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		}
	}
	
	public final void univ() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			match(UNIV);
			role();
			match(SLASH);
			argument();
			}
			System.out.println("univ"); context.ApplyUniv();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		}
	}
	
	public final void exist() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			match(EXIST);
			role();
			match(SLASH);
			argument();
			}
			System.out.println("exist"); context.ApplyExist();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		}
	}
	
	public final void role() throws RecognitionException, TokenStreamException {
		
		Token  v = null;
		
		try {      // for error handling
			v = LT(1);
			match(NAME);
			System.out.println("role " + v.getText()); context.NewRole(v.getText());
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		}
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"DEFINE",
		"SEMI",
		"UNION",
		"INTER",
		"LP",
		"RP",
		"TOP",
		"BOTTOM",
		"NAME",
		"CMPL",
		"UNIV",
		"SLASH",
		"EXIST",
		"ALPHA",
		"DIGIT",
		"ID",
		"WS",
		"COMMENT",
		"POINT",
		"STAR"
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { 2L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	private static final long[] mk_tokenSet_1() {
		long[] data = { 4098L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
	private static final long[] mk_tokenSet_2() {
		long[] data = { 752L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
	private static final long[] mk_tokenSet_3() {
		long[] data = { 32L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_3 = new BitSet(mk_tokenSet_3());
	private static final long[] mk_tokenSet_4() {
		long[] data = { 544L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_4 = new BitSet(mk_tokenSet_4());
	private static final long[] mk_tokenSet_5() {
		long[] data = { 608L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_5 = new BitSet(mk_tokenSet_5());
	private static final long[] mk_tokenSet_6() {
		long[] data = { 736L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_6 = new BitSet(mk_tokenSet_6());
	private static final long[] mk_tokenSet_7() {
		long[] data = { 32768L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_7 = new BitSet(mk_tokenSet_7());
	
	}
