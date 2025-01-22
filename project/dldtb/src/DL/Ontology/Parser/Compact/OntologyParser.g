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

header {
package DL.Ontology.Parser.Compact;
}

options 
{
    language = "Java";
}

{
import DL.Ontology.*;
import DL.Ontology.Expression.*;
import DL.Ontology.Parser.*;
}

class OntologyParser extends Parser;

options 
{
}

{
    // Parser's context
    private ParserContext context;

    // Set context
    public void setContext(ParserContext context) { this.context = context; } 
}

ontology
    :   (definition)* {System.out.println("ontology");}
    ;

definition
    :   (concept {context.DefinitionNew();} DEFINE expr SEMI) {System.out.println("definition"); context.DefinitionEnd();}
    ;
    
expr:   (union) {System.out.println("expression");}
    ; 

union
    :   (inter (UNION inter {System.out.println("union"); context.ApplyDsj();})*) 
    ;
    
inter
    :   (argument (INTER argument {System.out.println("inter"); context.ApplyCnj();})*) 
    ;

argument
    :
    (   concept
    |   top
    |   bottom
    |   complement
    |   univ
    |   exist
    |   LP union RP
    )   {System.out.println("argument");}
    ;

top :   TOP {System.out.println("top"); context.ApplyTop();}
    ;
    
bottom
    :   BOTTOM {System.out.println("bottom"); context.ApplyBottom();}
    ;

concept
    :   v:NAME {System.out.println("concept " + v.getText()); context.NewConcept(v.getText());}
    ;

role
    :   v:NAME {System.out.println("role " + v.getText()); context.NewRole(v.getText());}
    ;
    
complement
    :   CMPL argument {System.out.println("complement"); context.ApplyCmpl();}
    ;

univ:   (UNIV role SLASH argument) {System.out.println("univ"); context.ApplyUniv();}
    ;

exist
    :   (EXIST role SLASH argument) {System.out.println("exist"); context.ApplyExist();}
    ;


class DLFilterALCLexer extends Lexer;

protected ALPHA
    :   'A'..'Z'|'a'..'z'
    ;
    
protected DIGIT
    :   '0'..'9'
    ;
    
protected ID  
    :   ('_'|ALPHA)('_'|ALPHA|DIGIT)*
    ;

WS	:	(' '
	|	'\t'
	|	'\n'
	|	'\r')
		{ _ttype = Token.SKIP; }
	;

COMMENT : 
	"--" 
	(~'\n')* '\n'
	{ _ttype = Token.SKIP; newline(); }
	;

NAME
    :   ID (POINT ID)*
    ;    

TOP
    :   '1'
    ;

BOTTOM
    :   '0'
    ;

POINT
    :   '.'
    ;
    
CMPL:   '~'
    ;
    
UNION
    :   '|'
    ;
    
INTER
    :   '&'
    ;
    
UNIV:   '!'
    ;
    
EXIST
    :   '?'
    ;
    
STAR:   '*'
    ;

LP  :   '('
    ;

RP  :   ')'
    ;
    
SEMI:   ';'
    ;

DEFINE
    :   ":="
    ;

SLASH
    :   "/"
    ;
