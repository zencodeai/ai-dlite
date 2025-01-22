
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
// File    : store.h
// Author  : main
// Created : September 20, 2008, 7:09 PM
//
// Desc    : Reasonner store
//
// ............................................................................

#include "sdep.h"
#include "main.h"

using namespace DLITE;

#ifdef LOG_ENABLED

// ............................................................................
// Static members

tLog::logstack    tLog::ms_oStack;       // Log context stack
tLog::nullstream  tLog::ms_oNullStream;  // Null stream
tLog              tLog::ms_oDefLog;      // Default log context

// ............................................................................
// Context file name
string tLog::file() const
{
    string st;

    if (!null())
    {
        st = m_stName + ".log";
    }

    return st;
}

// ............................................................................
// c'tor
tLog::tLog()
{
    m_nFlags = 0;
    m_spStream = new nullstream();
    ms_oStack.push(this);
}

// ............................................................................
// c'tor
tLog::tLog(const string i_stName, const dword i_nFlags)
{
    m_stName = i_stName;
    if (ms_oStack.empty() || ms_oStack.top()->null())
    {
        m_nFlags = i_nFlags;
        m_spStream = new ofstream(file().c_str());
    }
    else if (i_nFlags && log_new)
    {
        tLog& oLog   = *ms_oStack.top();
        m_nFlags     = i_nFlags;
        m_spStore    = oLog.m_spStore;
        m_spSymTable = oLog.m_spSymTable;
        m_spStream   = new ofstream(file().c_str());
    }
    else
    {
        tLog& oLog   = *ms_oStack.top();
        m_nFlags     = oLog.m_nFlags | i_nFlags;
        m_spStore    = oLog.m_spStore;
        m_spSymTable = oLog.m_spSymTable;
        m_spStream   = oLog.m_spStream;
    }

    str() << endl << "++++++++++++++++++++++++++++++ " << m_stName << endl;

    ms_oStack.push(this);
}

// ............................................................................
// d'tor
tLog::~tLog()
{
    if (!ms_oStack.empty() && ms_oStack.top() == this)
    {
        ms_oStack.pop();
        if (!null())
        {
            str() << endl << "------------------------------ " << m_stName << endl;
        }
    }
}

// ............................................................................
// Get stream
ostream& tLog::stream(const dword i_nFlags)
{
    if (ms_oStack.empty())
    {
        return ms_oNullStream;
    }
    else
    {
        tLog& oLog = *ms_oStack.top();

        if (oLog.flags() & i_nFlags & log_all)
        {
            return oLog.str();
        }
        else
        {
            return ms_oNullStream;
        }
    }
}

// ............................................................................
// Set store
void tLog::setStore(const spiStore& i_spStore)
{
    ms_oStack.top()->store(i_spStore);
}

// ............................................................................
// Convert operator to string
string tLog::toString(const operator_t i_nOp)
{
    static const char* s_apszType[] = { "???", "ONT", "NSP",  "DEF ", "CGI", "IND", "CPT", "NCP", "RLE", "NRL", "TOP", "BOT", "UNI", "EXS", "UNI", "INT" };

    stringstream sst;

    operator_t nType = OP_TYPE(i_nOp);
    string stType = (nType >= OP_MAX) ? "???" : s_apszType[nType];
    tName oName = ms_oStack.top()->name(OP_ABS(i_nOp));

    if (oName.empty())
    {
        sst << stType << '[' << dec << OP_IDNT(i_nOp) << ']';
    }
    else
    {
        sst << stType << '[' << oName.toString() << ']';
    }

    return sst.str();
}

// ............................................................................
// Dump binary data
void tLog::dump(const pbyte i_pbData, const size_t i_nSize, const size_t i_nBreak)
{
    ostream& str = stream(tLog::log_info);

    str << endl << "size : " << dec << i_nSize << " bytes" << endl;

    for(size_t i = 0; i < i_nSize; i ++)
    {
        if (!(i % i_nBreak)) str << endl << setw(4) << setfill('0') << hex << i;

        str << ' ' << setw(2) << setfill('0') << hex << (int) i_pbData[i];
    }

    str << endl << endl;
}

// ............................................................................
// Dump expression
void tLog::dump(const sptExpression& i_spExpr)
{
    ostream& str = stream(tLog::log_info);

    stack<tOperator> oStack;

    tOperator oOp = i_spExpr->root();
    operator_t op = oOp.op();
    str << _log_name(op) << "(" << dec << oOp.size() << ")" << endl;

    oStack.push(oOp);

    while(!oStack.empty())
    {
        tOperator& oCur = oStack.top();

        tOperator oNext = oCur.next();

        if (!oNext.null())
        {
            oStack.push(oNext);
            op = oNext.op();
            string st(oStack.size() - 1, '\t');
            str << st << _log_name(op) << "(" << dec << oNext.size() << ")" << endl;
        }
        else
        {
            oStack.pop();
        }
    }
}

#endif //LOG_ENABLED
