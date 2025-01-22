#ifndef __PARSER_H__
#define	__PARSER_H__

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
// File    : parser.h
// Author  : main
// Created : March 14, 2010, 1:15 PM
//
// Desc    : Parser interface
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Id generator store implementation
    class tStoreIDGenerator : public iIDGenerator
    {
    private:

        // Store
        spiStore m_spStore;

    public:

        // c'tor
        tStoreIDGenerator(const spiStore& i_spStore) : m_spStore(i_spStore) {}

        // Next identifier
        operator_t NextUID() { return m_spStore->NextUID(); }

        // Factory
        static spiIDGenerator Create(const spiStore& i_spStore)
        {
            spiIDGenerator sp = new tStoreIDGenerator(i_spStore);
            return sp;
        }
    };

    // ............................................................................
    // Parser interface

    class iParser;
    typedef _s_ptr<iParser> spiParser;

    class iParser
    {
    public:

        // d'tor
        virtual ~iParser() {}

        // Parse ontology
        virtual bool parse(const string& i_stFile, const string& i_stName, const spiStore& i_spStore) = 0;

        // Parse expression
        virtual sptExpression parse(const string& i_stExpr, const spiStore& i_spStore) = 0;

        // Get errors
        virtual const list<string>& errors() const = 0;
    };
}

#endif //__PARSER_H__
