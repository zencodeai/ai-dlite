
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
// File    : reasoner.cpp
// Author  : main
// Created : February 9, 2009, 9:17 PM
// 
// Desc    : DL reasoner class implemenatation
//
// ............................................................................

#include "sdep.h"
#include "main.h"
#include "tbox.h"
#include "abox.h"
#include "node.h"
#include "reasoner.h"

using namespace DLITE;

// ............................................................................
// Reasoner implementation
class tReasoner : public iReasoner
{    
    
public:
    
    // Errors
    enum
    {
        err_reasnr_inv = err_off_reasnr,    // Invalid operator type
        err_reasnr_status,                  // Invalid ABox operation status
    };

    // Expand method prototype
    typedef iABox::res_t (tReasoner::*pfnExpand)(tOperator& i_oOp);

private:
    
    spiTBox         m_spTBox;   // TBox
    spiABox         m_spABox;   // ABox
    iABox::slot_t   m_nSlot;    // Initial slot
    stack<tNode>    m_oStack;   // Node stack

    pfnExpand       m_apExp[OP_MAX];  // Expand methods

protected:
    
    // Invalid operator
    iABox::res_t expInvalid(tOperator& /*i_oOp*/)
    {
        _check(false, err_reasnr_inv);
        return iABox::res_inv;
    }

    // Expension methods
    iABox::res_t expOP_CONCEPT   (tOperator& i_oOp); // Concept
    iABox::res_t expOP_CONCEPTNEG(tOperator& i_oOp); // Concept neg
    iABox::res_t expOP_TOP       (tOperator& i_oOp); // Top
    iABox::res_t expOP_BOTTOM    (tOperator& i_oOp); // Bottom
    iABox::res_t expOP_UNIV      (tOperator& i_oOp); // Universal
    iABox::res_t expOP_EXIST     (tOperator& i_oOp); // Exitential
    iABox::res_t expOP_UNION     (tOperator& i_oOp); // Or
    iABox::res_t expOP_INTER     (tOperator& i_oOp); // And

    // Clear context
    void clear();

    // Add item to the stack
    void add(const tOperator& i_oOp);

    // Process next item
    tNode::tPair next();

    // Remove processed nodes
    bool done();

    // Backtrack on clash
    bool backtrack();

    // Load expression
    void load(const operator_t i_nOp, const bool i_fNeg);

public:
 
    // c'tor
    tReasoner(const spiStore& i_spStore, const spiTBox& i_spTBox = NULL, const spiABox& i_spABox = NULL);

    // d'tor
    ~tReasoner() {}
    
    // Check expression satifiability
    bool Satisfiable(const sptExpression& i_spExpr); 

    // Restore ABox state
    void Restore();

    // Get reasoner's ABox interface
    spiABox getABox() { return m_spABox; }
};

// ............................................................................
// Factory method
spiReasoner iReasoner::Create(const spiStore& i_spStore, const spiTBox& i_spTBox, const spiABox& i_spABox)
{
    return spiReasoner(new tReasoner(i_spStore, i_spTBox, i_spABox));
}

// ............................................................................
// Factory method
spiReasoner iReasoner::Create(const string& i_stPath)
{
    spiStore spStore = StoreFactorySQLite::Create(i_stPath.c_str());
    spStore->Open();
    
    return spiReasoner(new tReasoner(spStore));
}

// ............................................................................
// c'tor
tReasoner::tReasoner(const spiStore& i_spStore, const spiTBox& i_spTBox, const spiABox& i_spABox)
{
    m_apExp[OP_INVALID   ] = &tReasoner::expInvalid;
    m_apExp[OP_ONTOLOGY  ] = &tReasoner::expInvalid;
    m_apExp[OP_NAMESPACE ] = &tReasoner::expInvalid;
    m_apExp[OP_DEFINITION] = &tReasoner::expInvalid;
    m_apExp[OP_GCI       ] = &tReasoner::expInvalid;
    m_apExp[OP_INDIVIDUAL] = &tReasoner::expInvalid;
    m_apExp[OP_CONCEPT   ] = &tReasoner::expOP_CONCEPT;
    m_apExp[OP_CONCEPTNEG] = &tReasoner::expOP_CONCEPTNEG;
    m_apExp[OP_ROLE      ] = &tReasoner::expInvalid;
    m_apExp[OP_ROLENEG   ] = &tReasoner::expInvalid;
    m_apExp[OP_TOP       ] = &tReasoner::expOP_TOP;
    m_apExp[OP_BOTTOM    ] = &tReasoner::expOP_BOTTOM;
    m_apExp[OP_UNIV      ] = &tReasoner::expOP_UNIV;
    m_apExp[OP_EXIST     ] = &tReasoner::expOP_EXIST;
    m_apExp[OP_UNION     ] = &tReasoner::expOP_UNION;
    m_apExp[OP_INTER     ] = &tReasoner::expOP_INTER;
    
    m_spTBox = i_spTBox.null() ? iTBox::Create(i_spStore) : i_spTBox;
    m_spABox = i_spABox.null() ? iABox::Create() : i_spABox;
}

// ............................................................................
// Clear context
void tReasoner::clear()
{
    m_spABox->Restore(m_nSlot);
    m_oStack = stack<tNode>();
}

// ............................................................................
// Add item to the stack
void tReasoner::add(const tOperator& i_oOp)
{
    tNode& oNode = m_oStack.top();
    oNode.add(i_oOp);
}

// ............................................................................
// Process next item
tNode::tPair tReasoner::next()
{
    tNode& oNode = m_oStack.top();
    return oNode.next();
}

// ............................................................................
// Remove processed nodes
bool tReasoner::done()
{
    _log << "* DONE      : " << endl;
    bool fRes = false;

    do
    {
        if (!(fRes = m_oStack.top().handleDone()))
        {
            m_oStack.pop();
        }
    }
    while(!m_oStack.empty() && !fRes);

    return fRes;
}

// ............................................................................
// Backtrack on clash
bool tReasoner::backtrack()
{
    _log << "* CLASH     : " << endl;
    bool fRes = false;

    do
    {
        if (!(fRes = m_oStack.top().handleClash()))
        {
            m_oStack.pop();
        }
    }
    while(!m_oStack.empty() && !fRes);

    return fRes;
}

// ............................................................................
// Load expression
void tReasoner::load(const operator_t i_nOp, const bool i_fNeg)
{
    _log << "* load      : " << _log_name(i_nOp) << " : " << i_fNeg << endl;

    sptExpression spExpr = m_spTBox->GetDefinition(OP_ABS(i_nOp));
    if (!spExpr.null())
    {
        tNode& oNode = m_oStack.top();
        tOperator oOp = spExpr->root(i_fNeg);
        if (m_spABox->Cache(oOp.op()) == iABox::res_done)
        {
            oNode.add(oOp);
            oNode.addRef(spExpr);
        }

        _log << "* loaded    : " << _log_name(oOp.op()) << endl;
    }
}

// ............................................................................
// Check expression satifiability
bool tReasoner::Satisfiable(const sptExpression& i_spExpr)
{
    bool fRes = true;
    clear();

    m_nSlot = m_spABox->Save();
    operator_t nNew = m_spABox->NewNode();
    m_oStack.push(tNode(m_spABox, nNew));

    tNode& oNode = m_oStack.top();
    oNode.add(i_spExpr->root());
    oNode.addRef(i_spExpr);

    while(!m_oStack.empty())
    {
        tNode::tPair oNext = next();

        if (oNext.second == tNode::sts_done)
        {
            fRes = !done();
            continue;
        }
        else if (oNext.second == tNode::sts_new)
        {
            m_oStack.push(tNode(m_oStack.top()));
        }

        dword nType = oNext.first.type();
        _check(nType < OP_MAX, err_reasnr_inv);

        iABox::res_t nRes = (this->*m_apExp[nType])(oNext.first);

        if (iABox::res_clash == nRes)
        {
            fRes = backtrack();
        }
    }

    return fRes;
}

// ............................................................................
// Restore ABox state
void tReasoner::Restore()
{
    m_spABox->Restore(m_nSlot);
}

// ............................................................................
iABox::res_t tReasoner::expOP_CONCEPT   (tOperator& i_oOp) // Concept
{
    iABox::res_t nRes = iABox::res_done;

    tNode& oNode = m_oStack.top();
    oNode.select();

    operator_t nOp = i_oOp.op();
    _log << "* concept   : " << _log_name(nOp) << endl;

    nRes = m_spABox->Add(nOp);

    if (nRes == iABox::res_done)
    {
        load(nOp, false);
    }

    return nRes;
}

// ............................................................................
iABox::res_t tReasoner::expOP_CONCEPTNEG(tOperator& i_oOp) // Concept neg
{
    iABox::res_t nRes = iABox::res_done;

    tNode& oNode = m_oStack.top();
    oNode.select();

    operator_t nOp = i_oOp.op();
    _log << "* ~concept  : " << _log_name(nOp) << endl;

    nRes = m_spABox->Add(nOp);

    if (nRes == iABox::res_done)
    {
        load(nOp, true);
    }

    return nRes;
}

// ............................................................................
iABox::res_t tReasoner::expOP_TOP       (tOperator& /*i_oOp*/) // Top
{
    _log << "* top       : " << endl;
    return iABox::res_done;
}

// ............................................................................
iABox::res_t tReasoner::expOP_BOTTOM    (tOperator& /*i_oOp*/) // Bottom
{
    _log << "* bottom  : " << endl;
    return iABox::res_clash;
}

// ............................................................................
iABox::res_t tReasoner::expOP_UNIV      (tOperator& i_oOp) // Universal
{
    iABox::res_t nRes = iABox::res_done;

    tNode& oNode = m_oStack.top();
    oNode.select();

    tOperator oRole = i_oOp.next();
    tOperator oCnpt = i_oOp.next();

    _log << "* univ      : " << _log_name(i_oOp.op()) << " : !" << _log_name(oRole.op()) << endl;

    list<operator_t> oSuc = m_spABox->Successors(oRole.op());

    for(list<operator_t>::iterator p = oSuc.begin(); p != oSuc.end(); p ++)
    {
        m_oStack.push(tNode(m_spABox, *p));
        add(oCnpt);
    }

    return nRes;
}

// ............................................................................
iABox::res_t tReasoner::expOP_EXIST     (tOperator& i_oOp) // Exitential
{
    iABox::res_t nRes = iABox::res_done;

    tNode& oNode = m_oStack.top();
    oNode.select();

    tOperator oRole = i_oOp.next();
    tOperator oCnpt = i_oOp.next();

    _log << "* exist     : " << _log_name(i_oOp.op()) << " : ?" << _log_name(oRole.op()) << endl;

    list<operator_t> oSuc = m_spABox->Successors(oRole.op());

    operator_t nCnpt = oCnpt.op();
    operator_t nInd = 0;
    for(list<operator_t>::iterator p = oSuc.begin(); p != oSuc.end() && !nInd; p ++)
    {
        if (m_spABox->Check(*p, nCnpt) == iABox::res_dup)
        {
            nInd = *p;
        }
    }

    if (!nInd)
    {
        nInd = m_spABox->NewNode();
        m_spABox->Add(oRole.op(), nInd);
    }

    m_oStack.push(tNode(m_spABox, nInd));
    add(oCnpt);

    return nRes;
}

// ............................................................................
iABox::res_t tReasoner::expOP_UNION     (tOperator& i_oOp) // Or
{
    _log << "* union     : " << _log_name(i_oOp.op()) << endl;
    add(i_oOp);
    return iABox::res_done;
}

// ............................................................................
iABox::res_t tReasoner::expOP_INTER     (tOperator& i_oOp) // And
{
    _log << "* inter     : " << _log_name(i_oOp.op()) << endl;
    add(i_oOp);
    return iABox::res_done;
}
