
//
//  Copyright 2016 zen.code.ai
//
//  This file is part of dlite.
//
//  dlite is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  dlite is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with dlite.  If not, see <http://www.gnu.org/licenses/>.
//

//
// Ontology grammar definition
// ANTL 3.2 
//

grammar Ontology;

options {
    language = C;
}

@parser::header {
#include <antlr3.h>
#include "dltools.h"
#include "context.h"

using namespace DLITE;
}

@parser::context
{
    sptContext m_spContext;
}

@parser::apifuncs
{
    RECOGNIZER->displayRecognitionError = tContext::errorHdlr;
    PARSER->super = (void *)ctx;
}

@lexer::header {
#include "dltools.h"
}

// -----------------------------------------------------------------------------
// Parser
//

eval : s_ontology;

s_ontology
    :   s_header? (s_bloc)*
        { ctx->m_spContext->s_ontology(); }
    ;

// Header
s_header
    :   lit_name lit_version? (s_attribute)*
        { ctx->m_spContext->s_header(); }
    ;

// Name
lit_name
    :   T_KW_NAME v=T_VAL_STRING T_S_SEMI
        { ctx->m_spContext->lit_name($v); }
    ;

// Version
lit_version
    :   T_KW_VERSION v=T_VAL_VERSION T_S_SEMI
        { ctx->m_spContext->lit_version($v); }
    ;

// Attribute
s_attribute
    :   T_KW_ATTRIBUTE n=F_ID v=T_VAL_STRING T_S_SEMI
        { ctx->m_spContext->s_attribute($n, $v); }
    ;

// Include
s_include
    :   T_KW_INCLUDE v=T_VAL_STRING T_S_SEMI
        { ctx->m_spContext->s_include($v); }
    ;

// Begin namespace
ns_begin
    :   T_KW_NSBEGIN v=F_ID T_S_SEMI
        { ctx->m_spContext->ns_begin($v); }
    ;

// End namespace
ns_end
    :   T_KW_NSEND v=F_ID T_S_SEMI
        { ctx->m_spContext->ns_end(); }
    ;

// Bloc
s_bloc
    :   s_definition | s_def | s_include | ns_begin | ns_end
    ;

// Concept definition
s_definition
    :   n=T_SY_NAME T_OP_DEF s_expr T_S_SEMI
        { ctx->m_spContext->s_definition($n); }
    ;

// Expression
s_expr
    :   op_or
        { ctx->m_spContext->s_expr(); }
    ;

// Disjunction
op_or
    :   (op_and (T_OP_OR op_and { ctx->m_spContext->op_or(); })*)
    ;

// Conjunction
op_and
    :   (s_concept (T_OP_AND s_concept { ctx->m_spContext->op_and(); })*)
    ;

// Top
op_top
    :   T_SY_TOP
        { ctx->m_spContext->op_top(); }
    ;

// Bottom
op_bottom
    :   T_SY_BOTTOM
        { ctx->m_spContext->op_bottom(); }
    ;

// Conditional
op_cond
    :   v=T_SY_COND
        { ctx->m_spContext->op_cond($v); }
    ;

// Atom
op_atom
    :   v=T_SY_NAME
        { ctx->m_spContext->op_atom($v); }
    ;

// Universal
op_univ
    :   T_OP_UNIV r=T_SY_NAME T_S_SLS s_concept
        { ctx->m_spContext->op_univ($r); }
    ;

// Existential
op_exist
    :   T_OP_EXIST r=T_SY_NAME T_S_SLS s_concept
        { ctx->m_spContext->op_exist($r); }
    ;

// Max cardinality
op_maxcard
    :   T_OP_L n=T_VAL_UINT T_S_SLS r=T_SY_NAME T_S_SLS s_concept
        { ctx->m_spContext->op_maxcard($n, $r); }
    ;

// Min cardinality
op_mincard
    :   T_OP_G n=T_VAL_UINT T_S_SLS r=T_SY_NAME T_S_SLS s_concept
        { ctx->m_spContext->op_mincard($n, $r); }
    ;

// Constraint
op_constraint
    :   a=T_SY_ATTRIBUTE o=(T_OP_G|T_OP_GEQ|T_OP_L|T_OP_LEQ|T_OP_EQ|T_OP_NEQ) (lit_value | lit_constant)
        { ctx->m_spContext->op_constraint($a, $o); }
    ;

// Not
op_not
    :   T_OP_NOT s_concept
        { ctx->m_spContext->op_not(); }
    ;

lit_value
    :   v=T_SY_VARIABLE { ctx->m_spContext->lit_value_variable($v); }
    |   v=T_VAL_UINT    { ctx->m_spContext->lit_value_uint($v); }
    |   v=T_VAL_INT     { ctx->m_spContext->lit_value_int($v); }
    |   v=T_VAL_FLOAT   { ctx->m_spContext->lit_value_float($v); }
    |   v=T_VAL_STRING  { ctx->m_spContext->lit_value_string($v); }
    ;

lit_list
    @init
    {
        { ctx->m_spContext->lit_list_begin(); }
    }
    :   T_S_LB lit_listitem (T_S_COM lit_listitem)* T_S_RB
        { ctx->m_spContext->lit_list_end(); }
    ;

op_in
    :   a=T_SY_ATTRIBUTE T_KW_IN (lit_list | lit_constant)
        { ctx->m_spContext->op_in($a); }
    ;

lit_listitem
    :   v=T_SY_NAME
        { ctx->m_spContext->lit_list_iten($v); }
    ;

// Concept
s_concept
    :   op_top | op_bottom | op_cond | op_univ | op_exist | op_maxcard | op_mincard | op_constraint | op_in | op_atom | op_not
    |   T_S_LP s_expr T_S_RP
        { ctx->m_spContext->s_concept(); }
    ;

// Constant definition
s_def
    :   T_KW_DEF v=T_SY_NAME (lit_value | lit_list) T_S_SEMI
        { ctx->m_spContext->s_def($v); }
    ;

// Constant
lit_constant
    :   v=T_SY_NAME
        { ctx->m_spContext->lit_constant($v); }
    ;

// -----------------------------------------------------------------------------
// Lexer
//

//
// Fragments
//
fragment F_ALPHA
    :   'A'..'Z'|'a'..'z'
    ;
    
fragment F_DIGIT
    :   '0'..'9'
    ;

fragment F_HEXDIGIT
    :   (F_DIGIT | 'A'..'F' | 'a'..'f')
    ;
    
// ID
fragment F_ID
    :   ('_'|F_ALPHA)('_'|F_ALPHA|F_DIGIT)*
    ;

//
// Hidden
//

// Whitespaces
T_WS
    :   (' '|'\r'|'\t'|'\u000C'|'\n')
        {$channel=HIDDEN;}
    ;

// Block comment
T_BCOMMENT
    :   '/*' .* '*/'
        {$channel=HIDDEN;}
    ;

// Line comment
T_LCOMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n'
        {$channel=HIDDEN;}
    ;

//
//  Keywords
//

T_KW_NAME           : 'name';
T_KW_VERSION        : 'version';
T_KW_ATTRIBUTE      : 'attr';
T_KW_ALIAS          : 'alias';
T_KW_INCLUDE        : 'include';
T_KW_NSBEGIN        : 'begin';
T_KW_NSEND          : 'end';
T_KW_IN             : 'in';
T_KW_DEF            : 'def';

//
// Symbols
//

// Names
T_SY_NAME
    :   F_ID | (F_ID (':' F_ID)+)
    ;

// Attribute
T_SY_ATTRIBUTE
    :   '.' T_SY_NAME
    ;

// Variable
T_SY_VARIABLE
    :   '@' T_SY_NAME
    ;

// Top
T_SY_TOP
    :   '#1'
    ;

// Bottom
T_SY_BOTTOM
    :   '#0'
    ;

// Conditional
T_SY_COND
    :   '#' T_SY_NAME
    ;

//
// Values
//

// Unsigned int
T_VAL_UINT
    :   F_DIGIT+
    ;

// Unsigned int (hexadecimal)
T_VAL_HINT
    :   F_HEXDIGIT+ ('h'|'H')
    ;

// Signed int
T_VAL_INT
    :   T_VAL_UINT | ('+' T_VAL_UINT) | ('-' T_VAL_UINT)
    ;

// Floating point
T_VAL_FLOAT
    :   T_VAL_INT 'f'|'F'
    |   T_VAL_INT '.' T_VAL_UINT ('f'|'F')?
    |   T_VAL_INT ('.' T_VAL_UINT)? ('e'|'E') T_VAL_INT ('f'|'F')?
    ;

// Version number
T_VAL_VERSION
    :   T_VAL_UINT ('.' T_VAL_UINT)*
    ;

// String
T_VAL_STRING
    :   '"' (~'\"')* '"'
    ;

//
// Operators
//

T_OP_DEF   : '=';
T_OP_INC   : '[=';
T_OP_AND   : '&';
T_OP_OR    : '|';
T_OP_UNIV  : '!';
T_OP_EXIST : '?';
T_OP_EQ    : '==';
T_OP_NEQ   : '~=';
T_OP_G     : '>';
T_OP_L     : '<';
T_OP_GEQ   : '>=';
T_OP_LEQ   : '<=';
T_OP_NOT   : '~';

//
// Separators
//

T_S_LP    : '(';
T_S_RP    : ')';
T_S_LB    : '{';
T_S_RB    : '}';
T_S_LSB   : '[';
T_S_RSB   : ']';
T_S_SLS   : '/';
T_S_COM   : ',';
T_S_SEMI  : ';';
T_S_COL   : ':';
