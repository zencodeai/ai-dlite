
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
// Desc    : Node class implementation
//
// ............................................................................

#include "sdep.h"
#include "main.h"
#include "tbox.h"
#include "abox.h"
#include "node.h"

using namespace DLITE;

// ............................................................................
// c'tor
tNode::tNode(const spiABox& i_spABox, const operator_t i_nInd)
{
    m_spABox = i_spABox;
    m_nInd   = i_nInd;
    m_p      = m_oOpList.end();

    _log << "# NewNode   : " << _log_name(m_nInd) << endl;
}

// ............................................................................
// c'tor
tNode::tNode(const tNode& i_oSrc)
{
    m_spABox = i_oSrc.m_spABox;
    m_nInd   = i_oSrc.m_nInd;
    m_p      = m_oOpList.end();

    _log << "# NewNode   : " << _log_name(m_nInd) << endl;
}

// ............................................................................
// d'tor
tNode::~tNode()
{
    _log << "# DelNode   : " << _log_name(m_nInd) << endl;
}

// ............................................................................
// Add operator
void tNode::add(const tOperator& i_oOp)
{
    _log << "# Add       : " << _log_name(i_oOp.op()) << endl;

    if (i_oOp.type() == OP_UNION)
    {
        m_oOpList.push_back(i_oOp);
        if (m_p == m_oOpList.end()) m_p = m_oOpList.begin();
    }
    else
    {
        m_oOpList.push_front(i_oOp);
        m_p = m_oOpList.begin();
    }
}

// ............................................................................
// Add reference
void tNode::addRef(const sptExpression& i_spExpr)
{
    _log << "# AddRef    : " << _log_name(i_spExpr->root().op()) << endl;

    operator_t nOp = i_spExpr->root().op();
    if (m_oDepMap.find(nOp) == m_oDepMap.end())
    {
        m_oDepMap[nOp] = i_spExpr;
    }
}

// ............................................................................
// Next operator
tNode::tPair tNode::next()
{
    tStatus nStatus = sts_done;
    tOperator oOp;

    if (m_p != m_oOpList.end())
    {
        tOperator& oCur = *m_p;
        switch(oCur.type())
        {
            case OP_UNION:
            {
                oOp = oCur.cur();
                m_oSlotMap[oCur.op()] = m_spABox->Save();
                nStatus = sts_new;

                _log << "# Next      : union " << _log_name(oCur.op()) << " : " << _log_name(oOp.op()) << " : " << nStatus << endl;
            }
            break;

            case OP_INTER:
            {
                oOp = oCur.next();
                nStatus = sts_same;
                if (oCur.end())
                {
                    m_oOpList.pop_front();
                    m_p = m_oOpList.begin();

                    _log << "# Next      : inter " << _log_name(oCur.op()) << " : end : " << nStatus << endl;
                }
                else
                {
                    _log << "# Next      : inter " << _log_name(oCur.op()) << " : " << _log_name(oOp.op()) << " : " << nStatus << endl;
                }
            }
            break;

            default:
            {
                oOp = oCur;
                nStatus = sts_same;
                m_oOpList.pop_front();
                m_p = m_oOpList.begin();

                _log << "# Next      : " << _log_name(oOp.op()) << " : " << nStatus << endl;
            }
        }
    }
    else
    {
        _log << "# Next      : done" << endl;
    }
        
    return tPair(oOp, nStatus);
}

// ............................................................................
// Select node
void tNode::select()
{
    m_spABox->Select(m_nInd);
}

// ............................................................................
// Handle done?
bool tNode::handleDone()
{
    bool fRes = false;

    if (m_p != m_oOpList.end())
    {
        if (m_p->type() == OP_UNION)
        {
            m_p ++;
            fRes = (m_p != m_oOpList.end());
        }
    }

    _log << "# HdlDone   : " << fRes << endl;
    return fRes;
}

// ............................................................................
// Handle clash?
bool tNode::handleClash()
{
    bool fRes = false;

    if (m_p != m_oOpList.end())
    {
        if (m_p->type() == OP_UNION && m_oSlotMap.find(m_p->op()) != m_oSlotMap.end())
        {
            while(true)
            {
                tOperator& oCur = *m_p;
                if (!oCur.last())
                {
                    m_spABox->Restore(m_oSlotMap[oCur.op()]);
                    m_spABox->Add(OP_NEG(oCur.cur().op()));
                    oCur.next();
                    fRes = true;
                }
                
                if (m_p == m_oOpList.begin()) break;
                m_p --;
            }
        }
    }

    _log << "# HdlClash  : " << fRes << endl;
    return fRes;
}

