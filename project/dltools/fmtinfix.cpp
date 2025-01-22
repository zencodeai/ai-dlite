
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
// File    : fmtinfix.cpp
// Author  : main
// Created : March 12, 2010, 9:29 PM
//
// Desc    : Infix expression format provider
//
// ............................................................................

#include "dltools.h"

using namespace DLITE;

// ............................................................................
// Infix expression format provider class
class tExprFmtProviderInfix : public iExprFmtProvider
{
public:

    // Errors
    enum
    {
        err_expfmt_args = err_off_expfmt,   // Invalid # of arguments
        err_expfmt_type,                    // Invalid oprator type
    };

protected:

   // Arg list
    typedef vector<string> tArgs;

   // Context struct
    struct tContext
    {
        bool      fRoot;
        tArgs     oArgs;
        tOperator oOp;

        // c'tor
        tContext(const tOperator& i_oOp, const bool i_fRoot = false) : oOp(i_oOp), fRoot(i_fRoot) {}

        // Copy c'tor
        tContext(const tContext& i_oSrc) : oOp(i_oSrc.oOp), fRoot(i_oSrc.fRoot) {}
    };

    // Context stack type
    typedef stack<tContext> tStack;

private:

    spiSymTable m_spSymTable;  // Symbol table
    tStack      m_oStack;      // Context stack

protected:

    // process quantifier
    string processQuant(tContext& i_oCtx);

    // process composed (and/or)
    string processComp(tContext& i_oCtx);

public:

    // c'tor
    tExprFmtProviderInfix(const spiSymTable& i_spSymTable) : m_spSymTable(i_spSymTable) {}

    // Convert expression to string
    string toString(const sptExpression& i_spExpr);
};

// ............................................................................
// process quantifier
string tExprFmtProviderInfix::processQuant(tContext& i_oCtx)
{
    stringstream sst;

    tOperator oNext = i_oCtx.oOp.next();

    if (oNext.null())
    {
        tArgs& oArgs = i_oCtx.oArgs;
        _check(oArgs.size() == 2, err_expfmt_args);
        char c = (i_oCtx.oOp.type() == OP_UNIV) ? '!' : '?';
        sst << c << oArgs[0] << '/' << oArgs[1];
        m_oStack.pop();
    }
    else
    {
        m_oStack.push(tContext(oNext));
    }

    return sst.str();
}

// ............................................................................
// process composed (and/or)
string tExprFmtProviderInfix::processComp(tContext& i_oCtx)
{
    stringstream sst;

    tOperator oNext = i_oCtx.oOp.next();

    if (oNext.null())
    {
        tArgs& oArgs = i_oCtx.oArgs;
        char c = (i_oCtx.oOp.type() == OP_UNION) ? '|' : '&';
        _check(oArgs.size() >= 1, err_expfmt_args);

        if (!i_oCtx.fRoot) sst << '(';

        for(tArgs::iterator p = oArgs.begin(); p != oArgs.end(); p ++)
        {
            if (p != oArgs.begin()) sst << c;
            sst << *p;
        }

        if (!i_oCtx.fRoot) sst << ')';

        m_oStack.pop();
    }
    else
    {
        m_oStack.push(tContext(oNext));
    }

    return sst.str();
}

// ............................................................................
// Convert expression to string
string tExprFmtProviderInfix::toString(const sptExpression& i_spExpr)
{
    string stExpr;

    if (i_spExpr.null()) return string();

    //m_oStack = tStack();
    m_oStack.push(tContext(i_spExpr->root(), true));

    while(!m_oStack.empty())
    {
        string st;

        tContext& oCtx = m_oStack.top();
        switch(oCtx.oOp.type())
        {
            case OP_CONCEPT   :
            {
                st = m_spSymTable->GetName(oCtx.oOp.op()).toString();
                m_oStack.pop();
            }
            break;

            case OP_CONCEPTNEG:
            {
                st = string ("~") + m_spSymTable->GetName(OP_ABS(oCtx.oOp.op())).toString();
                m_oStack.pop();
            }
            break;

            case OP_ROLE      :
            {
                st = m_spSymTable->GetName(oCtx.oOp.op()).toString();
                m_oStack.pop();
            }
            break;

            case OP_ROLENEG   :
            {
                st = string ("~") + m_spSymTable->GetName(OP_ABS(oCtx.oOp.op())).toString();
                m_oStack.pop();
            }
            break;

            case OP_TOP       :
            {
                st = "#1";
                m_oStack.pop();
            }
            break;

            case OP_BOTTOM    :
            {
                st = "#0";
                m_oStack.pop();
            }
            break;

            case OP_UNIV      :
            case OP_EXIST     :
                st = processQuant(oCtx);
                break;

            case OP_UNION     :
            case OP_INTER     :
                st = processComp(oCtx);
                break;

            default:
                _check(false, err_expfmt_type);
        }

        if (!st.empty())
        {
            if (m_oStack.empty())
            {
                stExpr = st;
            }
            else
            {
                m_oStack.top().oArgs.push_back(st);
            }
        }
   }

   return stExpr;
}

// ............................................................................
// Factory
spiExprFmtProvider tExprFmtProviderInfixFactory::Create(const spiSymTable& i_spSymTable)
{
   spiExprFmtProvider spExprFmtProvider = new tExprFmtProviderInfix(i_spSymTable);

   return spExprFmtProvider;
}
