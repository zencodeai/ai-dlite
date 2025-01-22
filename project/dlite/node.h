#ifndef __NODE_H__
#define	__NODE_H__

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
// File    : node.h
// Author  : main
// Created : December 10, 2009, 9:51 PM
//
// Desc    : Node class
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Node
    class tNode
    {
    public:

        // Errors
        enum
        {
            err_node_inv        // Invalid operator type
                = err_off_node,
            err_node_state,     // Invalid state

        };

        // Status code
        enum tStatus
        {
            sts_done,   // All operators processed
            sts_new,    // New node to be created
            sts_same,   // Same node
        };

        // Types
        typedef list<tOperator> tOpList;                    // Operator list
        typedef map<operator_t, sptExpression> tDepMap;     // Dependency map
        typedef map<operator_t, iABox::slot_t> tSlotMap;    // Slot map
        typedef pair<tOperator, tStatus> tPair;             // operator,status pair

    private:

        spiABox       m_spABox;     // ABox
        tOpList       m_oOpList;    // Operator list
        tDepMap       m_oDepMap;    // Depedency map
        tSlotMap      m_oSlotMap;   // Slot map
        tOpList::iterator m_p;      // Current operator
        operator_t    m_nInd;       // Current individual

    protected:

    public:

        // c'tor
        tNode(const spiABox& i_spABox, const operator_t i_nInd);

        // c'tor
        tNode(const tNode& i_oSrc);

        // d'tor
        virtual ~tNode();

        // Add operator
        void add(const tOperator& i_oOp);

        // Add reference
        void addRef(const sptExpression& i_spExpr);

        // Next operator
        tPair next();

        // Select node
        void select();

        // Handle done?
        bool handleDone();

        // Handle clash?
        bool handleClash();
    };
}

#endif	// __NODE_H__
