
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
// File    : symtable.cpp
// Author  : main
// Created : February 13, 2010, 8:41 AM
//
// Desc    : Symbol table implementation
//
// ............................................................................

#include "sdep.h"
#include "main.h"

using namespace DLITE;

// ............................................................................
// iSymTable implementation

class tSymTable : public iSymTable
{    
public:

    typedef _lru_cache<operator_t, tIdentifier> tCache;
    
private:
    
    spiStore m_spStore; // DL store
    tCache   m_oCache;  // Expression cache
    
protected:
    
    // Reset
    void reset()
    {
        
    }
    
    // Clear
    void clear()
    {
        
    }

    // Get symbol
    bool getSymbol(const operator_t i_operator, tIdentifier& o_oIdent);

    // Add symbol
    operator_t addSymbol(const tIdentifier& i_oIdent, const operator_t i_nType);

public:
    
    // c'tor
    tSymTable(const spiStore& i_spStore, const size_t i_nCap = 1024) : m_oCache(i_nCap)
        { reset(); m_spStore = i_spStore; }

    // d'tor
    virtual ~tSymTable() { clear(); }
    
    // Get symbol name (empty if none)
    virtual tName GetName(const operator_t i_nId);

    // Get symbol id (invalid if none)
    virtual operator_t GetId(const tName& i_oName, const operator_t i_nType);

    // Add symbol name (return existing))
    virtual operator_t AddName(const tName& i_oName, const operator_t i_nType);
};

// ............................................................................
// Factory method
spiSymTable iSymTable::Create(const spiStore& i_spStore)
{
    return spiSymTable(new tSymTable(i_spStore));
}

// ............................................................................
// Get symbol id
bool tSymTable::getSymbol(const operator_t i_operator, tIdentifier& o_oIdent)
{
    bool fFound = false;

    tCache::const_iterator p = m_oCache.find(i_operator);
    if (p == m_oCache.end())
    {
        if (m_spStore->GetSymbol(i_operator, o_oIdent))
        {
            m_oCache.set(i_operator, o_oIdent);
            fFound = true;
        }
    }
    else
    {
        o_oIdent = p->second;
        fFound = true;
    }

    return fFound;
}

// ............................................................................
// Get symbol id
operator_t tSymTable::addSymbol(const tIdentifier& i_oIdent, const operator_t i_nType)
{
    operator_t nId = OP_MAKE(i_nType, m_spStore->NextUID());
    m_spStore->AddSymbol(nId, i_oIdent);
    m_oCache.set(nId, i_oIdent);

    return nId;
}

// ............................................................................
// Get symbol name (empty if none)
tName tSymTable::GetName(const operator_t i_nId)
{
    tName oName;
    tIdentifier oId;
    operator_t nOp = i_nId;

    while(nOp != OP_ROOT_NS && getSymbol(nOp, oId))
    {
        oName.push_front(oId.second);
        nOp = oId.first;
    }
    
    return oName;
}

// ............................................................................
// Get symbol id (invalid if none)
operator_t tSymTable::GetId(const tName& i_oName, const operator_t i_nType)
{
    if (i_oName.empty()) return OP_INVALID;

    operator_t nOp = OP_ROOT_NS;
    tName::const_iterator last = i_oName.end();
    last --;

    for(tName::const_iterator p = i_oName.begin(); p != i_oName.end(); p ++)
    {
        tIdentifier oIdent(nOp, *p);
        operator_t nType = (p == last) ? i_nType : OP_NAMESPACE;

        if (!(nOp = m_spStore->GetId(oIdent, nType)))
        {
            nOp = OP_INVALID;
            break;
        }
    }

    return nOp;
}
// ............................................................................
// Add symbol name (return existing))
operator_t tSymTable::AddName(const tName& i_oName, const operator_t i_nType)
{
    if (i_oName.empty()) return 0;

    operator_t nOp = OP_ROOT_NS;
    bool fCreate = false;
    tName::const_iterator last = i_oName.end();
    last --;

    for(tName::const_iterator p = i_oName.begin(); p != i_oName.end(); p ++)
    {
        tIdentifier oIdent(nOp, *p);
        operator_t nType = (p == last) ? i_nType : OP_NAMESPACE;
        
        if (fCreate || !(nOp = m_spStore->GetId(oIdent, nType)))
        {
            nOp = addSymbol(oIdent, nType);
            fCreate = true;
        }
    }

    return nOp;
}
