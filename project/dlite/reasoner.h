#ifndef __REASONER_H__
#define	__REASONER_H__

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
// File    : reasoner.h
// Author  : main
// Created : February 9, 2009, 9:17 PM
// 
// Desc    : DL reasoner interface
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Reasoner interface
    class iReasoner;
    typedef _s_ptr<iReasoner> spiReasoner;

    class iReasoner
    {

    protected:

        // c'tor
        iReasoner() {}

    public:

        // d'tor
        virtual ~iReasoner() {}

        // Check expression satifiability
        virtual bool Satisfiable(const sptExpression& i_spExpr) = 0;

        // Restore ABox state
        virtual void Restore() = 0;

        // Get reasoner's ABox interface
        virtual spiABox getABox() = 0;

        // Factory method
        static spiReasoner Create(const spiStore& i_spStore, const spiTBox& i_spTBox = NULL, const spiABox& i_spABox = NULL);

        // Factory method
        static spiReasoner Create(const string& i_stPath);
    };
}

#endif	//_REASONER_H

