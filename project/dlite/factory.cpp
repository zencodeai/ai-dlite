
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

#include <list>

// ............................................................................
// File    : factory.cpp
// Author  : main
// Created : February 11, 2009, 10:23 PM
// 
// Desc    : Expression factory implemenation
//
// ............................................................................

#include "sdep.h"
#include "main.h"
#include "expression.h"
#include "factory.h"

using namespace DLITE;

// Expression blob class
class tExprBlob
{
public:
    
    typedef list<_buffer<operator_t> > tBlocs;
    
private:
    
    tBlocs m_oBlocs;    // Bloc list
    size_t m_nSize;     // Current buffer size
    
protected:

    // Reset
    void reset()
    {
        m_nSize = 0;
    }

public:

    // c'tor
    tExprBlob() { reset(); }

    // Clear
    void clear()
    {
        m_oBlocs.clear();
        reset();
    }
    
    // Add single value
    size_t add(const operator_t i_nVal)
    {
        m_oBlocs.push_back(_buffer<operator_t>(1, &i_nVal));
        m_nSize += 1;
        
        return m_nSize;
    }

    // Add array of values
    size_t add(const operator_t* i_pnVal, const size_t i_nSize)
    {
        m_oBlocs.push_back(_buffer<operator_t>(i_nSize, i_pnVal));
        m_nSize += i_nSize;
        
        return m_nSize;
    }

    // Add buffer
    size_t add(const _buffer<operator_t>& i_oBuf)
    {
        m_oBlocs.push_back(i_oBuf);
        m_nSize += i_oBuf.size();
        
        return m_nSize;
    }
    
    // Expression
    _buffer<operator_t> buf() const
    {
        _buffer<operator_t> oBuf(m_nSize);
        operator_t* pnOp = oBuf.ptr();
        
        for(tBlocs::const_iterator p = m_oBlocs.begin(); p != m_oBlocs.end(); p ++)
        {
            size_t nSize = p->size();
            memcpy(pnOp, p->ptr(), nSize*sizeof(operator_t));
            pnOp += nSize; 
        }
        
        if (m_nSize >= 2)
        {
            oBuf.ptr()[1] = m_nSize - 2;
        }
        
        return oBuf;
    }
};

// Add #R/C
void tExprFactory::role(const operator_t i_nType, const operator_t i_nRole)
{
    _check(!m_oStack.empty(), err_fact_args);

    tExprBlob oBlob;
    
    operator_t anOp[] = {OP_MAKE(i_nType, nextId()) , 0, i_nRole, 0 };
    
    oBlob.add(anOp, 4);
    oBlob.add(m_oStack.top());
    m_oStack.pop();
    
    m_oStack.push(oBlob.buf());    
}

// Add and/or
void tExprFactory::andor(const operator_t i_nType)
{
     _check(m_oStack.size() >= 2, err_fact_args);

    // Get args from stack
    _buffer<operator_t> oLeft = m_oStack.top();
    m_oStack.pop();
    _buffer<operator_t> oRight = m_oStack.top();
    m_oStack.pop();

    // Process left
    tExprBlob oBlob;
    if (OP_TYPE(oLeft.ptr()[0]) != i_nType)
    {
        operator_t anOp[] = {OP_MAKE(i_nType, nextId()) , 0 };
        oBlob.add(anOp, 2);
    }    

    oBlob.add(oLeft);
    
    // Process right
    if (OP_TYPE(oRight.ptr()[0]) == i_nType)
    {
        oBlob.add(oRight.ptr() + 2, oRight.size() - 2);
    }
    else
    {
        oBlob.add(oRight);        
    }    

    // Update stack 
    m_oStack.push(oBlob.buf());    
}

// Add concept arg
void tExprFactory::concept(const operator_t i_nCpt)
{
    operator_t nType = OP_TYPE(i_nCpt);
    _check(nType == OP_CONCEPT || nType == OP_CONCEPTNEG, err_fact_type);
    
    operator_t anOp[] = {i_nCpt , 0 };
    m_oStack.push(_buffer<operator_t>(2, anOp));
}

// Add top arg
void tExprFactory::top()
{
    operator_t anOp[] = {OP_MAKE(OP_TOP, 0) , 0 };
    m_oStack.push(_buffer<operator_t>(2, anOp));
}

// Add bottom arg
void tExprFactory::bottom()
{
    operator_t anOp[] = {OP_MAKE(OP_BOTTOM, 0) , 0 };
    m_oStack.push(_buffer<operator_t>(2, anOp));    
}

// Add !R/C
void tExprFactory::univ(const operator_t i_nRole)
{
    role(OP_UNIV, i_nRole);
}

// Add ?R/C
void tExprFactory::exist(const operator_t i_nRole)
{
    role(OP_EXIST, i_nRole);
}

// Intersction
void tExprFactory::andop()
{
    andor(OP_INTER);
}

// Union
void tExprFactory::orop()
{
    andor(OP_UNION);
}

// Not
void tExprFactory::neg()
{
    _check(!m_oStack.empty(), err_fact_args);

    _buffer<operator_t>& cur = m_oStack.top();
    size_t nSize = cur.size();

    pdword p = cur.ptr();
    for(size_t i = 0; i < nSize; i ++, p ++)
    {
        *p = OP_NEG(*p);
    }
}

// Get expression
sptExpression tExprFactory::expr() const
{
    _check(!m_oStack.empty(), err_fact_args);

    return tExpression::Create(m_oStack.top());
}
