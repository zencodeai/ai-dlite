#ifndef __SESSION_H__
#define	__SESSION_H__

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
// File    : session.h
// Author  : main
// Created : March 14, 2010, 1:15 PM
//
// Desc    : Session interface
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Session interface

    class iSession;
    typedef _s_ptr<iSession> spiSession;

    class iSession
    {
    public:

        // c'tor
        iSession() {}

        // d'tor
        virtual ~iSession() {}

        // Open store
        static spiSession Open(const string& i_stPath);

        // Create store
        static spiSession Create(const string& i_stPath);

        // Load onology
        virtual bool Load(const string& i_stPath, const string& i_stName) = 0;

        // Parser errors
        virtual const list<string>& Errors() = 0;

        // Dump symbol table, C style
        virtual void Dump(const string& i_stPath) = 0;

        // Parse expression
        virtual sptExpression Parse(const string& i_stExpr) = 0;

        // Test expression satisfiability
        virtual bool Satisfiable(const sptExpression& i_spExpr) = 0;
    };
}

#endif //__SESSION_H__
