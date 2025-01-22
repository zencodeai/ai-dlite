
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
// File    : dlparser.cpp
// Author  : main
// Created : March 14, 2010, 1:50 PM
//
// Desc    : Infix parser
//
// ............................................................................

#include "dltools.h"
#include "dlparser.h"
#include "OntologyLexer.h"
#include "OntologyParser.h"
#include "context.h"

// ............................................................................
// Infix parser

// ............................................................................
// c'tor
tDLParser::tDLParser()
{
    
}

// ............................................................................
// Parse ontology
bool tDLParser::parse(const string& i_stFile, const string& i_stName, const spiStore& i_spStore)
{
    pANTLR3_INPUT_STREAM          stream = NULL;
    pOntologyLexer                lexer  = NULL;
    pANTLR3_COMMON_TOKEN_STREAM	  tokens = NULL;
    pOntologyParser               parser = NULL;

    try
    {
        stream = antlr3AsciiFileStreamNew((uint8_t*) i_stFile.c_str());
        _check(stream != (pANTLR3_INPUT_STREAM)ANTLR3_ERR_NOMEM , err_dlite_mem);
        _check(stream != (pANTLR3_INPUT_STREAM)ANTLR3_ERR_NOFILE, err_dlite_notfnd);

        sptContext spContext = tContext::Create(i_stName, i_spStore);

        lexer  = OntologyLexerNew(stream);
        _check(lexer != NULL , err_dlite_mem);

        tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
        _check(tokens != NULL , err_dlite_mem);

        parser = OntologyParserNew(tokens);
        _check(tokens != NULL , err_dlite_mem);

        parser->m_spContext = spContext;

        spContext->clear();

        parser->eval(parser);

        m_oErrors = spContext->getErrors();
    }
    catch(...)
    {
        // Cleanup
        if (NULL != parser) parser->free(parser);
        if (NULL != tokens) tokens->free(tokens);
        if (NULL != lexer ) lexer->free(lexer);
        if (NULL != stream) stream->free(stream);

        throw;
    }

    parser->free(parser);
    tokens->free(tokens);
    lexer->free(lexer);
    stream->free(stream);

    return m_oErrors.empty();
}

// ............................................................................
// Parse expression
sptExpression tDLParser::parse(const string& i_stExpr, const spiStore& i_spStore)
{
    pANTLR3_INPUT_STREAM          stream = NULL;
    pOntologyLexer                lexer  = NULL;
    pANTLR3_COMMON_TOKEN_STREAM	  tokens = NULL;
    pOntologyParser               parser = NULL;

    sptExpression spExpr;

    try
    {
        stream = antlr3NewAsciiStringInPlaceStream((uint8_t*) i_stExpr.c_str(), i_stExpr.size(), (uint8_t*) "Expression");
        _check(stream != (pANTLR3_INPUT_STREAM)ANTLR3_ERR_NOMEM , err_dlite_mem);

        sptContext spContext = tContext::Create(i_spStore);

        lexer  = OntologyLexerNew(stream);
        _check(lexer != NULL , err_dlite_mem);

        tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
        _check(tokens != NULL , err_dlite_mem);

        parser = OntologyParserNew(tokens);
        _check(tokens != NULL , err_dlite_mem);

        parser->m_spContext = spContext;

        spContext->clear();

        parser->s_expr(parser);

        m_oErrors = spContext->getErrors();

        if (m_oErrors.empty())
        {
            spExpr = spContext->getExpr();
        }
    }
    catch(...)
    {
        // Cleanup
        if (NULL != parser) parser->free(parser);
        if (NULL != tokens) tokens->free(tokens);
        if (NULL != lexer ) lexer->free(lexer);
        if (NULL != stream) stream->free(stream);

        throw;
    }

    parser->free(parser);
    tokens->free(tokens);
    lexer->free(lexer);
    stream->free(stream);

    return spExpr;
}

// ............................................................................
// Factory
spiParser tDLParser::Create()
{
    spiParser spParser = new tDLParser();
    return spParser;
}
