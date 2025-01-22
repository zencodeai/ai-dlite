#ifndef __FMTINFIX_H__
#define	__FMTINFIX_H__

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
// File    : fmtinfix.h
// Author  : main
// Created : March 12, 2010, 9:29 PM
//
// Desc    : Infix expression format provider
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Factory
    class tExprFmtProviderInfixFactory
    {
    public:

        // Factory
        static spiExprFmtProvider Create(const spiSymTable& i_spSymTable);
    };
}

#endif //__FMTINFIX_H__
