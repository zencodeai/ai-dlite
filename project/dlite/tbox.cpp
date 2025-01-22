
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
// File    : tbox.cpp
// Author  : main
// Created : September 20, 2008, 7:09 PM
// 
// Desc    : tbox class implementation 
//
// ............................................................................

#include "sdep.h"
#include "main.h"
#include "tbox.h"

using namespace DLITE;

// ............................................................................
// Operator definition table
tOperatorDef DLITE::g_asOp[] =
{
    OP_DEF(OP_INVALID    , 0), // Invalid
    OP_DEF(OP_ONTOLOGY   , 0), // Ontology
    OP_DEF(OP_NAMESPACE  , 0), // Namespace
    OP_DEF(OP_DEFINITION , 0), // Concept definition
    OP_DEF(OP_GCI        , 0), // Global concept inclusion
    OP_DEF(OP_INDIVIDUAL , 0), // Individual
    OP_DEF(OP_CONCEPT    , 1), // Concept
    OP_DEF(OP_CONCEPTNEG , 1), // Concept neg
    OP_DEF(OP_ROLE       , 0), // Role
    OP_DEF(OP_ROLENEG    , 0), // Role neg
    OP_DEF(OP_TOP        , 1), // Top
    OP_DEF(OP_BOTTOM     , 1), // Bottom
    OP_DEF(OP_UNIV       , 1), // Universal
    OP_DEF(OP_EXIST      , 1), // Exitential
    OP_DEF(OP_UNION      , 1), // Or
    OP_DEF(OP_INTER      , 1)  // And
};


// ............................................................................
// iTBox implementation

class tTBox : public iTBox
{    
public:
    
    typedef _lru_cache<operator_t, sptExpression> tCache;
    
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
    
public:
    
    // c'tor
    tTBox(const spiStore& i_spStore, const size_t i_nCap = 1024) : m_oCache(i_nCap) 
        { reset(); m_spStore = i_spStore; }

    // d'tor
    virtual ~tTBox() { clear(); }
    
    // Get definition (sp is null if none)
    sptExpression GetDefinition(const operator_t i_operator);

    // Add definition
    void AddDefinition(const operator_t i_ontology, const operator_t i_operator, const sptExpression& i_spExpr);
};

// ............................................................................
// Factory method
spiTBox iTBox::Create(const spiStore& i_spStore)
{
    return spiTBox(new tTBox(i_spStore));
}

// ............................................................................
// Get definition (sp is null if none)
sptExpression tTBox::GetDefinition(const operator_t i_operator)
{
    sptExpression spExpr;
    
    tCache::const_iterator p = m_oCache.find(i_operator);
    if (p == m_oCache.end())
    {
        _buffer<byte> oBlob;
        if (m_spStore->GetDefinition(i_operator, oBlob))
        {
            spExpr = tExpression::Create(oBlob);
        }
        
        m_oCache.set(i_operator, spExpr);
    }
    else
    {
        spExpr = p->second;
    }
    
    return spExpr;
}

// ............................................................................
// Add definition
void tTBox::AddDefinition(const operator_t i_ontology, const operator_t i_operator, const sptExpression& i_spExpr)
{
    _buffer<byte> oBlob = i_spExpr->serialize();
    m_spStore->AddDefinition(i_ontology, i_operator, oBlob);
    m_oCache.set(i_operator, i_spExpr);
}
