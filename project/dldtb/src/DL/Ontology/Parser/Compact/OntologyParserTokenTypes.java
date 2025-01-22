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

// $ANTLR 2.7.7 (20060906): "OntologyParser.g" -> "DLFilterALCLexer.java"$

package DL.Ontology.Parser.Compact;

public interface OntologyParserTokenTypes {
	int EOF = 1;
	int NULL_TREE_LOOKAHEAD = 3;
	int DEFINE = 4;
	int SEMI = 5;
	int UNION = 6;
	int INTER = 7;
	int LP = 8;
	int RP = 9;
	int TOP = 10;
	int BOTTOM = 11;
	int NAME = 12;
	int CMPL = 13;
	int UNIV = 14;
	int SLASH = 15;
	int EXIST = 16;
	int ALPHA = 17;
	int DIGIT = 18;
	int ID = 19;
	int WS = 20;
	int COMMENT = 21;
	int POINT = 22;
	int STAR = 23;
}
