
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
// File    : abox.h
// Author  : main
// Created : January 19, 2009, 11:07 PM
// 
// Desc    : ABOX Interface
//
// ............................................................................

#include "sdep.h"
#include "main.h"
#include "expression.h"
#include "store.h"
#include "symtable.h"
#include "abox.h"

using namespace DLITE;

// ............................................................................
// tConceptAttr class implementtion
class tConceptAttr
{
private:
    
    operator_t m_nVal;  // Operator's value
    
protected:
    
    // Reset
    void reset()
    {
        m_nVal = 0;
    }

    // Clear
    void clear()
    {
        reset();
    }
    
    // Assign
    tConceptAttr& assign(const tConceptAttr& i_oSrc)
    {
        m_nVal = i_oSrc.m_nVal;
        return *this;
    }
    
public:
    
    // c'tor
    tConceptAttr() { reset(); }
    tConceptAttr(const operator_t i_nVal) { reset(); m_nVal = i_nVal; }
    tConceptAttr(const tConceptAttr& i_oSrc) { reset(); assign(i_oSrc); }
    
    // d'tor
    ~tConceptAttr() { clear(); }
    
    // = operator
    tConceptAttr& operator=(const tConceptAttr& i_oSrc) { clear(); return assign(i_oSrc); }
    
    // Attributes
    operator_t getVal() const { return m_nVal; }
};

// ............................................................................
// tEdgeAttr class implementtion
class tEdgeAttr
{
private:
    
    operator_t m_nVal;  // Operator's value
    
protected:
    
    // Reset
    void reset()
    {
        m_nVal = 0;
    }

    // Clear
    void clear()
    {
        reset();
    }
    
    // Assign
    tEdgeAttr& assign(const tEdgeAttr& i_oSrc)
    {
        m_nVal = i_oSrc.m_nVal;
        return *this;
    }
    
public:
    
    // c'tor
    tEdgeAttr() { reset(); }
    tEdgeAttr(const operator_t i_nVal) { reset(); m_nVal = i_nVal; }
    tEdgeAttr(const tEdgeAttr& i_oSrc) { reset(); assign(i_oSrc); }
    
    // d'tor
    ~tEdgeAttr() { clear(); }
    
    // = operator
    tEdgeAttr& operator=(const tEdgeAttr& i_oSrc) { clear(); return assign(i_oSrc); }
    
    // Attributes
    operator_t getVal() const { return m_nVal; }
};

// ............................................................................
// tRoleAttr class implementtion
class tRoleAttr : public map<operator_t, tEdgeAttr>
{
private:
    
    operator_t m_nVal;  // Operator's value
    
protected:
    
    // Reset
    void reset()
    {
        m_nVal = 0;
    }

    // Clear
    void clear()
    {
        reset();
    }
    
    // Assign
    tRoleAttr& assign(const tRoleAttr& i_oSrc)
    {
        map<operator_t, tEdgeAttr>::operator=(i_oSrc);
        m_nVal = i_oSrc.m_nVal;
        return *this;
    }
    
public:
    
    // c'tor
    tRoleAttr() { reset(); }
    tRoleAttr(const operator_t i_nVal) { reset(); m_nVal = i_nVal; }
    tRoleAttr(const tRoleAttr& i_oSrc) { reset(); assign(i_oSrc); }
    
    // d'tor
    ~tRoleAttr() { clear(); }
    
    // = operator
    tRoleAttr& operator=(const tRoleAttr& i_oSrc) { clear(); return assign(i_oSrc); }
    
    // Attributes
    operator_t getVal() const { return m_nVal; }
};

// ............................................................................
// tNode class implementtion
class tNodeAttr;
typedef _s_ptr<tNodeAttr> sptNode;

class tNodeAttr
{
public:
    
    typedef map<operator_t, tConceptAttr> tConceptMap;
    typedef map<operator_t, tRoleAttr>    tRoleMap;
    
private:
    
    operator_t  m_nInd;     // Node id
    tConceptMap m_oCMap;    // Concept map
    tRoleMap    m_oRMap;    // Concept map
    
protected:
    
    // Reset
    void reset()
    {
        m_nInd = 0;
    }

    // Clear
    void clear()
    {
        reset();
    }

    // c'tor
    tNodeAttr(const operator_t i_nInd) { reset(); m_nInd = i_nInd; }
    
public:
    
    // d'tor
    ~tNodeAttr() { clear(); }
    
    // Get node Id
    operator_t getNodeId() const { return m_nInd; }
    
    // Add concept
    iABox::res_t AddConcept(const operator_t i_nCpt, const bool i_fUpdate = true)
    {
        iABox::res_t nRes = iABox::res_inv;
        
        operator_t nCId  = OP_IDNT(i_nCpt);
        operator_t nType = OP_TYPE(i_nCpt);
        
        if (nType == OP_TOP)
        {
            nRes = iABox::res_dup;
        }
        else if (nType == OP_BOTTOM)
        {
            nRes = iABox::res_clash;
        }
        else
        {
            tConceptMap::iterator p = m_oCMap.find(nCId);

            if (p != m_oCMap.end())
            {
                nRes = (p->second.getVal() == i_nCpt) ? iABox::res_dup : iABox::res_clash;
            }
            else
            {
                if (i_fUpdate)
                    m_oCMap[nCId] = tConceptAttr(i_nCpt);

                nRes = iABox::res_done;
            }
        }

        return nRes;
    }

    // Test concept
    iABox::res_t Check(const operator_t i_nCpt)
    {
        return AddConcept(i_nCpt, false);
    }
    
    // Remove concept
    void RemConcept(const operator_t i_nCpt)
    {
        m_oCMap.erase(OP_IDNT(i_nCpt));
    }
    
    // Add role
    iABox::res_t AddRole(const operator_t i_nRol, const operator_t i_nInd)
    {
        iABox::res_t nRes = iABox::res_inv;
        
        operator_t i_nRId = OP_IDNT(i_nRol);
        operator_t i_nIId = OP_IDNT(i_nInd);
        
        tRoleMap::iterator p = m_oRMap.find(i_nRId);

        if (p != m_oRMap.end())
        {
            tRoleAttr& oRoleAttr = p->second;
            if (oRoleAttr.find(i_nIId) != oRoleAttr.end())
            {
                nRes = iABox::res_dup;
            }
            else
            {
                oRoleAttr[i_nIId] = tEdgeAttr(i_nInd);
                nRes = iABox::res_done;
            }
        }
        else
        {
            tRoleAttr oRoleAttr(i_nRol);
            oRoleAttr[i_nIId] = tEdgeAttr(i_nInd);
            m_oRMap[i_nRId] = oRoleAttr;
            nRes = iABox::res_done;
        }
         
        return nRes;
    }

    // Remove role
    void RemRole(const operator_t i_nRol, const operator_t i_nInd)
    {
        operator_t i_nRId = OP_IDNT(i_nRol);
        operator_t i_nIId = OP_IDNT(i_nInd);
        
        tRoleMap::iterator p = m_oRMap.find(i_nRId);

        if (p != m_oRMap.end())
        {
            tRoleAttr& oRoleAttr = p->second;
            tRoleAttr::iterator q = oRoleAttr.find(i_nIId);
            if (q != oRoleAttr.end())
            {
                oRoleAttr.erase(q);
                if (oRoleAttr.empty()) m_oRMap.erase(p); 
            }
        }
    }
    
    // Get successors
    bool GetSucc(const operator_t i_nRol, list<operator_t>& o_oSucc)
    {
        bool fFound = false;
        o_oSucc.clear();
        
        operator_t i_nRId = OP_IDNT(i_nRol);
        
        tRoleMap::iterator p = m_oRMap.find(i_nRId);

        if (p != m_oRMap.end())
        {
            fFound = true;
            tRoleAttr& oRoleAttr = p->second;
            for(tRoleAttr::iterator q = oRoleAttr.begin(); q != oRoleAttr.end(); q ++)
            {
                o_oSucc.push_back(q->second.getVal());
            }
        }
        
        return fFound;
    }
    
    // Factory
    static sptNode Create(const operator_t i_nInd) { return sptNode(new tNodeAttr(i_nInd)); }
};

// ............................................................................
// ABox class implementtion
class tABox : public iABox
{   
public:

    typedef map<operator_t, sptNode> tNodeMap;  // Node map
    typedef void (tABox::*pfnAction)();         // Action method pointer
    typedef stack<operator_t> tActStack;        // Action stack

    // Errors
    enum
    {
        err_abox_state      // Invalid state
            = err_off_abox,
    };
    
    // Action codes
    enum
    {
        act_counter = 0,
        act_select  = 1,
        act_delnode = 2,
        act_delcpt  = 3,
        act_delrle  = 4,
        act_count   = 5,
    };
    
private:
    
    tActStack   m_oStack;       // Action stack
    tNodeMap    m_oNodeMap;     // Node map
    sptNode     m_spNode;       // Selected node
    operator_t  m_nBase;        // Individuals generation base
    operator_t  m_nCur;         // Individuals generation counter
    pfnAction   m_apAct[act_count]; // Action methods pointers
    
protected:

    // Restore counter
    void actCounter();

    // Restore selected node
    void actSelect();

    // Delete node
    void actDelNode();

    // Delete concept
    void actDelConcept();

    // Delete role
    void actDelRole();

    void reset()
    {
        m_nBase = OP_MAKE(OP_INDIVIDUAL, 1);
        m_nCur  = m_nBase;

        m_apAct[act_counter] = &tABox::actCounter;
        m_apAct[act_select ] = &tABox::actSelect;
        m_apAct[act_delnode] = &tABox::actDelNode;
        m_apAct[act_delcpt ] = &tABox::actDelConcept;
        m_apAct[act_delrle ] = &tABox::actDelRole;
    }
    
    void clear()
    {
        m_oStack = tActStack();
        m_oNodeMap.clear();
        m_spNode.clear();
        m_nBase = m_nCur;        // Individuals generation base
    }

    // New individual
    inline operator_t newInd() { return m_nCur ++; }
    
    // Is named concept
    static inline bool isNamed(const operator_t i_nConcept) 
    {
        return OP_TYPE(OP_ABS(i_nConcept)) == OP_CONCEPT;
    }
    
public:
    
    // c'tor
    tABox() { reset(); }
    
    // d'tor
    ~tABox() { clear(); }

    // Save model
    slot_t Save();
    
    // Restore model
    void Restore(const slot_t i_nSlot);

    // Add concept
    res_t Cache(const operator_t i_nConcept);
    
    // Add concept
    res_t Add(const operator_t i_nConcept);

    // Add role
    res_t Add(const operator_t i_nRole, const operator_t i_nNode);

    // Select node
    bool Select(const operator_t i_nNode);

    // Clear ABox
    void Clear();

    // Empty?
    bool Empty() const { return m_oNodeMap.empty(); }

    // Current node
    operator_t CurNode();

    // New node
    operator_t NewNode(const operator_t i_nNode = 0);

    // Check if concept belongs to node
    res_t Check(const operator_t i_nNode, const operator_t i_nConcept);

    // Successors
    list<operator_t> Successors(const operator_t i_nRole);
};

// ............................................................................
// Factory method
spiABox iABox::Create()
{
    return spiABox(new tABox());
}

// ............................................................................
// Restore counter
void tABox::actCounter()
{
    m_nCur = m_oStack.top();
    m_oStack.pop();        
}

// ............................................................................
// Restore selected node
void tABox::actSelect()
{
    operator_t nNode = m_oStack.top();
    m_oStack.pop();
    
    Select(nNode);
}

// ............................................................................
// Delete node
void tABox::actDelNode()
{
    operator_t nNode = m_oStack.top();
    m_oStack.pop();
    
    m_oNodeMap.erase(nNode);
}

// ............................................................................
// Delete concept
void tABox::actDelConcept()
{
    operator_t nNode = m_oStack.top();
    m_oStack.pop();
    operator_t nCpt  = m_oStack.top();
    m_oStack.pop();
    
    Select(nNode);
    m_spNode->RemConcept(nCpt);
}

// ............................................................................
// Delete role
void tABox::actDelRole()
{
    operator_t nNode = m_oStack.top();
    m_oStack.pop();
    operator_t nRle  = m_oStack.top();
    m_oStack.pop();
    operator_t nInd  = m_oStack.top();
    m_oStack.pop();
    
    Select(nNode);
    m_spNode->RemRole(nRle, nInd);
}

// ............................................................................
// Save model
iABox::slot_t tABox::Save()
{
    slot_t nSlot = m_oStack.size();
    
    m_oStack.push(m_nCur);
    m_oStack.push(act_counter);
    
    if (!m_spNode.null())
    {
        m_oStack.push(m_spNode->getNodeId());
        m_oStack.push(act_select);
    }
    
    _log << "> Save      : " << nSlot << endl;
    return nSlot;
}

// ............................................................................
// Restore model
void tABox::Restore(const slot_t i_nSlot)
{
    _log << "> Restore   : " << i_nSlot << endl;

    while(m_oStack.size() > i_nSlot)
    {
        operator_t nAction = m_oStack.top();
        m_oStack.pop();
        
        if (nAction < act_count)
        {
            (this->*m_apAct[nAction])();
        }
    }
}

// ............................................................................
// Add concept
iABox::res_t tABox::Cache(const operator_t i_nConcept)
{
    res_t nRes = res_inv;

    _check(!m_spNode.null(), err_abox_state);

    nRes = m_spNode->AddConcept(i_nConcept);

    if (nRes == res_done)
    {
        m_oStack.push(i_nConcept);
        m_oStack.push(m_spNode->getNodeId());
        m_oStack.push(act_delcpt);
    }

    return nRes;
}

// ............................................................................
// Add concept
iABox::res_t tABox::Add(const operator_t i_nConcept)
{
    res_t nRes = res_inv;

    if (isNamed(i_nConcept))
    {
        _check(!m_spNode.null(), err_abox_state);

        nRes = m_spNode->AddConcept(i_nConcept);

        if (nRes == res_done)
        {
            m_oStack.push(i_nConcept);
            m_oStack.push(m_spNode->getNodeId());
            m_oStack.push(act_delcpt);
        }
    }
    else
    {
        nRes = res_none;
    }

    _log << "> Add       : " << _log_name(i_nConcept) << " : " << nRes << endl;
    return nRes;
}

// ............................................................................
// Add role
iABox::res_t tABox::Add(const operator_t i_nRole, const operator_t i_nNode)
{
    res_t nRes = res_inv;

    _check(!m_spNode.null(), err_abox_state);
    
    nRes = m_spNode->AddRole(i_nRole, i_nNode);
    
    if (nRes == res_done)
    {
        m_oStack.push(i_nNode);
        m_oStack.push(i_nRole);
        m_oStack.push(m_spNode->getNodeId());
        m_oStack.push(act_delrle);
    }
    
    _log << "> Add       : " << _log_name(i_nRole) << " - " << _log_name(i_nNode) << " : " << nRes << endl;
    return nRes;
}

// ............................................................................
// Select node
bool tABox::Select(const operator_t i_nNode)
{
    bool fFound = false;

    if (m_spNode.null() || m_spNode->getNodeId() != i_nNode)
    {
        tNodeMap::iterator p = m_oNodeMap.find(i_nNode);

        if (p != m_oNodeMap.end())
        {
            m_spNode = p->second;
            fFound = true;
        }
        else
        {
            m_spNode.clear();
            fFound = false;
        }
    }
    else
    {
        fFound = true;        
    }
    
    _log << "> Select    : " << _log_name(i_nNode) << " : " << fFound << endl;
    return fFound;
}

// ............................................................................
// Current node
operator_t tABox::CurNode()
{
    operator_t nInd = 0;

    if (!m_spNode.null())
    {
        nInd = m_spNode->getNodeId();
    }

    _log << "> CurNode   : " << _log_name(nInd) << endl;
    return nInd;
}

// ............................................................................
// New node
operator_t tABox::NewNode(const operator_t i_nNode)
{
    operator_t nInd = i_nNode ? i_nNode : newInd();
    
    sptNode spNode = tNodeAttr::Create(nInd);
    m_oNodeMap[nInd] = spNode;
    m_spNode = spNode;
    
    m_oStack.push(nInd);
    m_oStack.push(act_delnode);
        
    _log << "> NewNode   : " << _log_name(nInd) << endl;
    return nInd;
}

// Clear ABox
void tABox::Clear()
{
    clear();
}

// Check if concept belongs to node
iABox::res_t tABox::Check(const operator_t i_nNode, const operator_t i_nConcept)
{
    res_t nRes = iABox::res_inv;

    tNodeMap::iterator p = m_oNodeMap.find(i_nNode);

    if (p != m_oNodeMap.end())
    {
        nRes = p->second->Check(i_nConcept);
    }
    // else nRes = iABox::res_inv    
    
    _log << "> Check     : " << _log_name(i_nNode) << " : "  << _log_name(i_nConcept) << " : " << nRes << endl;
    return nRes;
}

// Successors
list<operator_t> tABox::Successors(const operator_t i_nRole)
{
    list<operator_t> oSuc;
    
    _check(!m_spNode.null(), err_abox_state);

    m_spNode->GetSucc(i_nRole, oSuc);
    
    _log << "> Successors: " << _log_name(i_nRole) << dec << " : " << oSuc.size() << endl;
    return oSuc;
}
