
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
// File    : session.cpp
// Author  : main
// Created : March 12, 2010, 9:29 PM
//
// Desc    : Session
//
// ............................................................................

#include "dltools.h"
#include "session.h"
#include "dlparser.h"

using namespace DLITE;

// ............................................................................
// Session class
class tSession : public iSession
{
public:

private:

    spiStore            m_spStore;     // Store
    spiSymTable         m_spSymTable;  // Symbol table
    spiExprFmtProvider  m_spFmtProv;   // Format provider
    spiTBox             m_spTBox;      // TBox
    spiParser           m_spParser;    // Parser

protected:

    // Name to string
    string name2string(const char i_cPrefix, const tName& i_oName);

    // Dump block
    void dumpBloc(ofstream& i_str, const char* i_pszTitle, const char i_cPrefix, const operator_t i_nType);

public:
    
    // c'tor
    tSession(const spiStore& i_spStore) :
            m_spStore(i_spStore),
            m_spSymTable(iSymTable::Create(i_spStore)),
            m_spFmtProv(tExprFmtProviderInfixFactory::Create(m_spSymTable)),
            m_spTBox(iTBox::Create(i_spStore)),
            m_spParser(tDLParser::Create())
    {
        _log_store(m_spStore);
    }

    // Load onology
    bool Load(const string& i_stPath, const string& i_stName);

    // Parser errors
    const list<string>& Errors() {return m_spParser->errors(); }

    // Dump symbol table, C style
    void Dump(const string& i_stPath);

    // Parse expression
    sptExpression Parse(const string& i_stExpr);

    // Test expression satisfiability
    bool Satisfiable(const sptExpression& i_spExpr);
};

// ............................................................................
// Open store
spiSession iSession::Open(const string& i_stPath)
{
    spiStore spStore = StoreFactorySQLite::Create(i_stPath.c_str());
    spStore->Open();
    spiSession spSession = new tSession(spStore);

    return spSession;
}

// ............................................................................
// Create store
spiSession iSession::Create(const string& i_stPath)
{
    spiStore spStore = StoreFactorySQLite::CreateNew(i_stPath.c_str());
    spStore->Open();
    spiSession spSession = new tSession(spStore);

    return spSession;
}

// ............................................................................
// Load onology
bool tSession::Load(const string& i_stPath, const string& i_stName)
{
    bool fSuccess = false;

    m_spStore->Begin();

    try
    {
        fSuccess = m_spParser->parse(i_stPath, i_stName, m_spStore);
        if (fSuccess)
        {
            m_spStore->Commit();
        }
        else
        {
            m_spStore->Rollback();
        }
    }
    catch(...)
    {
        m_spStore->Rollback();
        throw;
    }

    return fSuccess;
}

// ............................................................................
// Name to string
string tSession::name2string(const char i_cPrefix, const tName& i_oName)
{
    stringstream sst;

    sst << i_cPrefix;
    for(tName::const_iterator p = i_oName.begin(); p != i_oName.end(); p ++)
        sst << '_' << *p;

    return sst.str();
}
// ............................................................................
// Dump block
void tSession::dumpBloc(ofstream& i_str, const char* i_pszTitle, const char i_cPrefix, const operator_t i_nType)
{
    string st = "// ";
    string stSep = st + string(80, '.');

    i_str << endl << stSep << endl;
    i_str << st << i_pszTitle << endl << endl;

    m_spStore->GetIdList(i_nType);

    operator_t nOp = 0;
    while(0 != (nOp = m_spStore->GetNextId()))
    {
        tName oName = m_spSymTable->GetName(nOp);
        if (!oName.empty())
        {
            i_str << "#define " << setw(40) << setfill(' ') << name2string(i_cPrefix, oName) << " (0x" << hex << setw(8) << setfill('0') << nOp << ')';

            if (OP_CONCEPT == i_nType)
            {
                sptExpression spExpr = m_spTBox->GetDefinition(nOp);
                if (!spExpr.null())
                {
                    i_str << " " << st << m_spFmtProv->toString(spExpr);
                }
            }

            i_str << endl;
        }
    }
}

// ............................................................................
// Dump symbol table, C style
void tSession::Dump(const string& i_stPath)
{
    string st = "// ";
    string stSep = st + string(80, '-');

    try
    {
        ofstream str(i_stPath.c_str());

        str << stSep << endl;
        str << st << endl;
        str << st << i_stPath << endl;
        str << st << endl;
        str << stSep << endl << endl;
        str << endl;
        str << "#ifndef __STORE__" << endl;
        str << "#define __STORE__" << endl;

        dumpBloc(str, "Ontologies", 'O', OP_ONTOLOGY);
        dumpBloc(str, "Roles"     , 'R', OP_ROLE    );
        dumpBloc(str, "Concepts"  , 'C', OP_CONCEPT );

        str << endl << "#endif //__STORE__" << endl;
    }
    catch(...)
    {
        tFile::erase(i_stPath);
        throw;
    }
}

// ............................................................................
// Parse expression
sptExpression tSession::Parse(const string& i_stExpr)
{
    return m_spParser->parse(i_stExpr, m_spStore);
}

// ............................................................................
// Test expression satisfiability
bool tSession::Satisfiable(const sptExpression& i_spExpr)
{
    spiReasoner spReasoner = iReasoner::Create(m_spStore, m_spTBox);

    return spReasoner->Satisfiable(i_spExpr);
}
