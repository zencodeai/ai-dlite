#ifndef __FMTPROV_H__
#define	__FMTPROV_H__

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
// File    : fmtprov.h
// Author  : main
// Created : March 12, 2010, 9:12 PM
//
// Desc    : Format providers interfaces
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Expression format provider interface

    class iExprFmtProvider;
    typedef _s_ptr<iExprFmtProvider> spiExprFmtProvider;

    class iExprFmtProvider
    {
    public:

        // Convert expression to string
        virtual string toString(const sptExpression& i_spExpr) = 0;
    };
}

#endif //__FMTPROV_H__

