#ifndef __DLPARSER_H__
#define	__DLPARSER_H__

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
// File    : dlparser.h
// Author  : main
// Created : March 14, 2010, 1:38 PM
//
// Desc    : Infix parser
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Infix parser

    class tDLParser : public iParser
    {
        // Parsing errors
        list<string> m_oErrors;

    public:

        // c'tor
        tDLParser();

        // Parse ontology
        bool parse(const string& i_stFile, const string& i_stName, const spiStore& i_spStore);

        // Parse expression
        sptExpression parse(const string& i_stExpr, const spiStore& i_spStore);

        // Get errors
        const list<string>& errors() const { return m_oErrors; }

        // Factory
        static spiParser Create();
    };
}

#endif //__DLPARSER_H__
