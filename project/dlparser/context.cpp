
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

// ............................................................................
// File    : context.cpp
// Author  : main
// Created : March 14, 2010, 11:43 PM
//
// Desc    : Parser context
//
// ............................................................................

#include "dltools.h"
#include "OntologyLexer.h"
#include "OntologyParser.h"
#include "context.h"

// ............................................................................
// c'tor
tContext::tContext(const string& i_stName, const spiStore& i_spStore)
    : m_oFactory(tStoreIDGenerator::Create(i_spStore))
{
    m_stName     = i_stName;
    m_spStore    = i_spStore;
    m_spTBox     = iTBox::Create(i_spStore);
    m_spSymTable = iSymTable::Create(i_spStore);
    m_nId        = m_spSymTable->AddName(tName(i_stName), OP_ONTOLOGY);

    _log << "Ontology : " << i_stName << " : " << hex << setfill('0') << setw(8) << m_nId << endl;
}

// ............................................................................
// c'tor
tContext::tContext(const spiStore& i_spStore)
    : m_oFactory(tIDGenerator::Create())
{
    m_spStore    = i_spStore;
    m_spSymTable = iSymTable::Create(i_spStore);
}

// ............................................................................
// Factory
sptContext tContext::Create(const string& i_stName, const spiStore& i_spStore)
{
    sptContext spContext = new tContext(i_stName, i_spStore);
    return spContext;
}

// ............................................................................
// Factory
sptContext tContext::Create(const spiStore& i_spStore)
{
    sptContext spContext = new tContext(i_spStore);
    return spContext;
}

// ............................................................................
// Ontology
void tContext::s_ontology()
{
    _log << "Ontology        :" << endl;
}

// ............................................................................
// Header
void tContext::s_header()
{
    _log << "Header          :" << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Name
void tContext::lit_name(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Name            : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Version
void tContext::lit_version(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Version         : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Attribute
void tContext::s_attribute(const pANTLR3_COMMON_TOKEN n, const pANTLR3_COMMON_TOKEN v)
{
    _log << "Name            : " << (char*) n->getText(n)->chars << " : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Include
void tContext::s_include(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Include         : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Begin namespace
void tContext::ns_begin(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Namespace begin : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// End namespace
void tContext::ns_end()
{
    _log << "Namespace end   : " << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Concept definition
void tContext::s_definition(const pANTLR3_COMMON_TOKEN n)
{
    tName oName((char*) n->getText(n)->chars);
    operator_t nId = m_spSymTable->AddName(oName, OP_CONCEPT);
    sptExpression spExpr = m_oFactory.expr();

    m_spTBox->AddDefinition(m_nId, nId, spExpr);

    _log << "Def concept     : " << oName.toString() << " : " << hex << setfill('0') << setw(8) << nId << endl;
}

// ............................................................................
// Expression
void tContext::s_expr()
{
    _log << "Expression      : " << endl;
}

// ............................................................................
// Disjunction
void tContext::op_or()
{
    m_oFactory.orop();
    _log << "Or              : " << endl;
}

// ............................................................................
// Conjunction
void tContext::op_and()
{
    m_oFactory.andop();
    _log << "And             : " << endl;
}

// ............................................................................
// Top
void tContext::op_top()
{
    m_oFactory.top();
    _log << "Top             : " << endl;
}

// ............................................................................
// Bottom
void tContext::op_bottom()
{
    m_oFactory.bottom();
    _log << "Bottom          : " << endl;
}

// ............................................................................
// Conditional
void tContext::op_cond(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Cond            : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Atom
void tContext::op_atom(const pANTLR3_COMMON_TOKEN v)
{
    tName oName((char*) v->getText(v)->chars);    
    operator_t nId = getNameId(oName, OP_CONCEPT);
    m_oFactory.concept(nId);

    _log << "Atom            : " << oName.toString() << " : " << hex << setfill('0') << setw(8) << nId << endl;
}

// ............................................................................
// Universal
void tContext::op_univ(const pANTLR3_COMMON_TOKEN r)
{
    tName oName((char*) r->getText(r)->chars);
    operator_t nId = getNameId(oName, OP_ROLE);
    m_oFactory.univ(nId);

    _log << "Univ            : " << oName.toString() << " : " << hex << setfill('0') << setw(8) << nId << endl;
}

// ............................................................................
// Existential
void tContext::op_exist(const pANTLR3_COMMON_TOKEN r)
{
    tName oName((char*) r->getText(r)->chars);
    operator_t nId = getNameId(oName, OP_ROLE);
    m_oFactory.exist(nId);

    _log << "Exist           : " << oName.toString() << " : " << hex << setfill('0') << setw(8) << nId << endl;
}

// ............................................................................
// Max cardinality
void tContext::op_maxcard(const pANTLR3_COMMON_TOKEN n, const pANTLR3_COMMON_TOKEN r)
{
    _log << "Max card        : " << (char*) n->getText(n)->chars << " : " << (char*) r->getText(r)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Min cardinality
void tContext::op_mincard(const pANTLR3_COMMON_TOKEN n, const pANTLR3_COMMON_TOKEN r)
{
    _log << "Min card        : " << (char*) n->getText(n)->chars << " : " << (char*) r->getText(r)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Constraint
void tContext::op_constraint(const pANTLR3_COMMON_TOKEN a, const pANTLR3_COMMON_TOKEN o)
{
    _log << "Constraint      : " << (char*) a->getText(a)->chars << " : " << (char*) o->getText(o)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Not
void tContext::op_not()
{
    m_oFactory.neg();
    _log << "Not             : " << endl;
}

// ............................................................................
// Value (var)
void tContext::lit_value_variable(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Variable        : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Value (uint)
void tContext::lit_value_uint(const pANTLR3_COMMON_TOKEN v)
{
    _log << "uint            : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Value (int)
void tContext::lit_value_int(const pANTLR3_COMMON_TOKEN v)
{
    _log << "int             : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Value (float)
void tContext::lit_value_float(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Float           : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Value (string)
void tContext::lit_value_string(const pANTLR3_COMMON_TOKEN v)
{
    _log << "String          : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// List (begin)
void tContext::lit_list_begin()
{
    _log << "List begin      : " << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// List (end)
void tContext::lit_list_end()
{
    _log << "List end        : " << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// List item
void tContext::lit_list_iten(const pANTLR3_COMMON_TOKEN v)
{
    _log << "List item       : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// In
void tContext::op_in(const pANTLR3_COMMON_TOKEN a)
{
    _log << "In              : " << (char*) a->getText(a)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Concept
void tContext::s_concept()
{
    _log << "Concept         : " << endl;
}

// ............................................................................
// Constant definition
void tContext::s_def(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Def const       : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Constant
void tContext::lit_constant(const pANTLR3_COMMON_TOKEN v)
{
    _log << "Constant        : " << (char*) v->getText(v)->chars << endl;
    _check(false, err_dlite_unsup);
}

// ............................................................................
// Error handler
void tContext::errorHdlr(pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8* tokenNames)
{
    stringstream sst;

    pANTLR3_PARSER       parser;
    pANTLR3_TREE_PARSER  tparser;
    pANTLR3_INT_STREAM   is;
    pANTLR3_STRING       ttext;
    pANTLR3_STRING       ftext;
    pANTLR3_EXCEPTION    ex;
    pANTLR3_COMMON_TOKEN theToken;

    // Retrieve some info for easy reading.
    //
    ex    = recognizer->state->exception;
    ttext = NULL;

    // See if there is a 'filename' we can use
    //
    if (ex->streamName == NULL)
    {
        if (((pANTLR3_COMMON_TOKEN)(ex->token))->type == ANTLR3_TOKEN_EOF)
        {
            sst << "-end of input-(";
        }
        else
        {
            sst << "-unknown source-(";
        }
    }
    else
    {
        ftext = ex->streamName->to8(ex->streamName);
        sst << ftext->chars << '(';
    }

    // Next comes the line number
    //
    sst << recognizer->state->exception->line << ')';
    sst << " : error " << recognizer->state->exception->type << " : ";
    sst << (pANTLR3_UINT8) (recognizer->state->exception->message);

    // How we determine the next piece is dependent on which thing raised the
    // error.
    //
    // Prepare the knowledge we know we have
    //
    parser    = (pANTLR3_PARSER) (recognizer->super);
    tparser   = NULL;
    is        = parser->tstream->istream;
    theToken  = (pANTLR3_COMMON_TOKEN)(recognizer->state->exception->token);
    ttext     = theToken->toString(theToken);

    sst << ", at offset " << recognizer->state->exception->charPositionInLine;
    if  (theToken != NULL)
    {
        if (theToken->type == ANTLR3_TOKEN_EOF)
        {
            sst << ", at <EOF>";
        }
        else
        {
            // Guard against null text in a token
            //
            sst << " near " << (char*) (ttext == NULL ? (pANTLR3_UINT8)"<no text for the token>" : ttext->chars);
        }
    }

    _log << sst.str() << endl;

    pOntologyParser pParser = (pOntologyParser) (parser->super);
    pParser->m_spContext->addError(sst.str());
}
