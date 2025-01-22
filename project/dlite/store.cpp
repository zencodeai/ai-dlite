
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
#include "tbox.h"

using namespace DLITE;

#include "sqlite3.h"

// ............................................................................
// Error code bases
enum
{
    err_store_open = err_off_store, // failed to open store
    err_store_create,               // Failed to create store
    err_store_prep,                 // Failed to prepare statement
    err_store_bind,                 // Failed to bind
    err_store_type,                 // Type mismatch    
    err_store_reset,                // Failed to reset
    err_store_exec,                 // Execute failed
    err_store_cnt,                  // Failed to load counter
    err_store_over,                 // Counter overflow
};

// ............................................................................
// Free single instance
template <typename _Type> class _s_ptr_stmt_free
{
public:
    
    inline static void free(const _Type* p) 
        { if (p) sqlite3_finalize(const_cast<_Type*>(p)); }
};

// ............................................................................
// Value class
class tValue
{
private:

    // Statement pointer
    sqlite3_value* m_pvalue;

public:

    // Clear
    void clear() { m_pvalue = NULL; }
    
    // Is null?
    bool null() const { return m_pvalue == NULL || sqlite3_value_type(m_pvalue) == SQLITE_NULL; }
    
    // Set content
    void set(const sqlite3_value* i_pvalue)
    {
        m_pvalue = const_cast<sqlite3_value*>(i_pvalue);
    }
    
    // c'tor
    tValue() : m_pvalue(NULL) {}
    tValue(const sqlite3_value* i_pvalue) { set(i_pvalue); } 
    tValue(const tValue& i_src) { set(i_src.m_pvalue); } 
    
    // Assign 
    tValue& operator=(const tValue& i_src) { set(i_src.m_pvalue); return *this; }
    
    // Convert to int
    operator int() const
    {
        return (m_pvalue) ? sqlite3_value_int(m_pvalue) : 0;
    }

    // Convert to dword
    operator dword() const
    {
        return (m_pvalue) ? (dword) sqlite3_value_int(m_pvalue) : 0;
    }

    // Convert to double
    operator double() const
    {
        return (m_pvalue) ? sqlite3_value_double(m_pvalue) : 0;
    }

    // Convert to string
    operator string() const
    {
        return (m_pvalue) ? string((char*) sqlite3_value_text(m_pvalue)) : string();
    }

    // Convert to byte buffer
    operator _buffer<byte>() const
    {
        _buffer<byte> oVal;
        
        if (m_pvalue)
        {
            pbyte p = (pbyte) sqlite3_value_blob(m_pvalue);
            int size = sqlite3_value_bytes(m_pvalue);
            
            oVal.set((size_t) size, p);
        }
        
        return oVal;
    }
};

// ............................................................................
// Statement class
typedef _s_ptr<sqlite3_stmt, _s_ptr_cnt, _s_ptr_stmt_free<sqlite3_stmt> > sptStmt;

class tStatement
{
private:
    
    sptStmt m_spStmt;   // Statement pointer
    
protected:
    
    // Reset
    void reset()
    {
        
    }
    
    // Assign
    tStatement& assign(const tStatement& i_oSrc)
    {
        m_spStmt = i_oSrc.m_spStmt;         
        return *this;
    }
    
    // Bind int
    inline void _bind(const int i_nIdx, const int i_nArg)
    {
        int ret = sqlite3_bind_int(m_spStmt.ptr(), i_nIdx, i_nArg);
        _check_info(int, !ret, err_store_bind, ret);
    }

    // Bind dword
    inline void _bind(const int i_nIdx, const dword i_nArg)
    {
        int ret = sqlite3_bind_int(m_spStmt.ptr(), i_nIdx, (int) i_nArg);
        _check_info(int, !ret, err_store_bind, ret);
    }

    // Bind double
    inline void _bind(const int i_nIdx, const double i_dArg)
    {
        int ret = sqlite3_bind_double(m_spStmt.ptr(), i_nIdx, i_dArg);
        _check_info(int, !ret, err_store_bind, ret);
    }

    // Bind string
    inline void _bind(const int i_nIdx, const string& i_stArg)
    {
        int ret = sqlite3_bind_text(m_spStmt.ptr(), i_nIdx, i_stArg.data(), i_stArg.size(), SQLITE_TRANSIENT);
        _check_info(int, !ret, err_store_bind, ret);
    }

    // Bind blob
    inline void _bind(const int i_nIdx, const _buffer<byte>& i_oArg)
    {
        int ret = sqlite3_bind_blob(m_spStmt.ptr(), i_nIdx, i_oArg.ptr(), i_oArg.size(), SQLITE_TRANSIENT);
        _check_info(int, !ret, err_store_bind, ret);
    }

public:

    // Clear
    void clear()
    {
        m_spStmt = NULL;
        reset();
    }
    
    // c'tor
    tStatement() : m_spStmt(NULL) {}
    
    // c'tor
    tStatement(const sqlite3* i_pDB, const char* i_pszStmt)
    {
        sqlite3_stmt* pStmt = NULL;
        const char*   pTail = NULL;
        int ret = sqlite3_prepare_v2(const_cast<sqlite3*>(i_pDB), i_pszStmt, -1, &pStmt, &pTail);
        _check_info(int, !ret, err_store_prep, ret);
        m_spStmt = pStmt;
    }
    
    // c'tor
    tStatement(const tStatement& i_oSrc) 
    { 
        reset(); 
        assign(i_oSrc); 
    }

    // Initialize command
    void init()
    {
        int ret = sqlite3_reset(m_spStmt.ptr());
        _check_info(int, !ret, err_store_reset, ret);
    }

    // Bind
    template<class _T1> void bind(const _T1& i_arg1)
    {
        init();
        _bind(1, i_arg1);
    }
    
    // Bind
    template<class _T1, class _T2> void bind(const _T1& i_arg1, const _T2& i_arg2)
    {
        init();
        _bind(1, i_arg1);
        _bind(2, i_arg2);
    }

    // Bind
    template<class _T1, class _T2, class _T3> void bind(const _T1& i_arg1, const _T2& i_arg2, const _T3& i_arg3)
    {
        init();
        _bind(1, i_arg1);
        _bind(2, i_arg2);
        _bind(3, i_arg3);
    }
        
    // Bind
    template<class _T1, class _T2, class _T3, class _T4> void bind(const _T1& i_arg1, const _T2& i_arg2, const _T3& i_arg3, const _T4& i_arg4)
    {
        init();
        _bind(1, i_arg1);
        _bind(2, i_arg2);
        _bind(3, i_arg3);
        _bind(4, i_arg4);
    }

    // Execute command
    void exec()
    {
        init();
        
        int ret = sqlite3_step(m_spStmt.ptr());
        _check_info(int, ret == SQLITE_DONE, err_store_exec, ret);
    }

    // Execute and return value
    tValue exec_scalar()
    {
        int ret = sqlite3_step(m_spStmt.ptr());
        _check_info(int, ret == SQLITE_DONE || ret == SQLITE_ROW, err_store_exec, ret);
        
        sqlite3_value* pvalue = NULL;
        
        if (ret == SQLITE_ROW)
        {
            pvalue = sqlite3_column_value(m_spStmt.ptr(), 0);
        }

        return tValue(pvalue);
    }
    
    // Next row
    bool exec_step()
    {
        int ret = sqlite3_step(m_spStmt.ptr());
        _check_info(int, ret == SQLITE_DONE || ret == SQLITE_ROW, err_store_exec, ret);
        
        return ret == SQLITE_ROW;
    }
    
    // Get column's value
    tValue operator[](const int i_idx)
    {
        sqlite3_value* pvalue = NULL;
        pvalue = sqlite3_column_value(m_spStmt.ptr(), i_idx);
        
        return tValue(pvalue);
    }
};

// ............................................................................
// SQLite store

class tStoreSQLite : public iStore
{
    friend class StoreFactorySQLite;
    
private:
    
    string      m_stPath;           // Store pathname
    sqlite3*    m_pDB;              // DB handler
    dword       m_nCounter;         // Uid counter
    tStatement  m_stmtBeginTrs;     // Begin transcation
    tStatement  m_stmtCommitTrs;    // Commit transcation
    tStatement  m_stmtRollbackTrs;  // Rollback transcation
    tStatement  m_stmtGetCounter;   // Get uid counter
    tStatement  m_stmtUpdCounter;   // Update uid counter
    tStatement  m_stmtGetDef;       // Get definition
    tStatement  m_stmtAddDef;       // Add definition
    tStatement  m_stmtGetDefList;   // Get definition list
    tStatement  m_stmtGetIdent;     // Get Symbol name
    tStatement  m_stmtAddIdent;     // Add Symbol name
    tStatement  m_stmtGetId;        // Get Symbol Id
    tStatement  m_stmtGetIdList;    // Get Id list

protected:

    // Reset
    void reset()
    {
        m_pDB      = NULL;
        m_nCounter = 0;
    }
    
    // Clear object
    void clear()
    {
        if (m_pDB)
        {
            m_stmtBeginTrs.clear();
            m_stmtCommitTrs.clear();
            m_stmtRollbackTrs.clear();
            m_stmtGetCounter.clear();
            m_stmtUpdCounter.clear();
            m_stmtGetDef.clear();
            m_stmtAddDef.clear();
            m_stmtGetDefList.clear();
            m_stmtGetIdent.clear();
            m_stmtAddIdent.clear();
            m_stmtGetId.clear();
            m_stmtGetIdList.clear();

            sqlite3_close(m_pDB);
        }

        reset();
    }

    // Init all
    void initAll()
    {
        m_stmtGetCounter.init();
        m_stmtUpdCounter.init();
        m_stmtGetDef.init();
        m_stmtAddDef.init();
        m_stmtGetDefList.init();
        m_stmtGetIdent.init();
        m_stmtAddIdent.init();
        m_stmtGetId.init();
        m_stmtGetIdList.init();
    }

    // Initialize database
    void initDtb();

public:

    // c'tor 
    tStoreSQLite(const char* i_pszPath) 
    { 
        reset(); 
        m_stPath  = i_pszPath;
    }
    
    // d'tor
    virtual ~tStoreSQLite() { clear(); }
    
    // Open store
    void Open();
    
    // Close store
    void Close() { clear(); }

    // Begin transaction
    void Begin();

    // End transaction
    void Commit();

    // Load uid
    dword LoadUID();

    // Get next uid
    dword NextUID();

    // Update uid
    void UpdateUID();

    // Rollback transaction
    void Rollback();
    
    // Get symbol definition
    bool GetDefinition(const operator_t i_nId, _buffer<byte>& o_oDef);

    // Add symbol definition
    void AddDefinition(const operator_t i_nOntology, const operator_t i_nId, const _buffer<byte>& i_oDef);

    // Get list of definitions of a given ontology
    void GetDefinitionList(const operator_t i_nOntology);

    // Get next id in list
    operator_t GetNextDefinition();

    // Get identifier
    bool GetSymbol(const operator_t i_nId, tIdentifier& o_oIdent);

    // Add identifier
    void AddSymbol(const operator_t i_nId, const tIdentifier& i_oIdent);

    // Get id
    operator_t GetId(const tIdentifier& i_oIdent, const operator_t i_nType);

    // Get list of Ids of a given type
    void GetIdList(const operator_t i_nType);

    // Get next id in list
    operator_t GetNextId();
};

// ............................................................................
// Initialize database
void tStoreSQLite::initDtb()
{
    const char* szScript =
        "create table SymTable(nspace integer, name varchar(256), type integer, tag integer, primary key(nspace, name, type), unique(tag));"
        "create table DefTable(ontology integer, tag integer, exp blob, primary key(ontology, tag));"
        "create table DataStore(counter integer, info text);"
        "insert into DataStore values (0,'');";

    sqlite3* pDB = NULL;
    
    int ret = sqlite3_open(m_stPath.c_str(), &pDB);
    _check_info(int, !ret, err_store_open, ret);

    try
    {
        int ret = sqlite3_exec(pDB, szScript, NULL, NULL, NULL);
        _check_info(int, ret == SQLITE_OK, err_store_exec, ret);
    }
    catch(...)
    {
        sqlite3_close(pDB);
        throw;
    }

    sqlite3_close(pDB);
}

// ............................................................................
// Open store
void tStoreSQLite::Open()
{
    try
    {
        clear();
       int ret = sqlite3_open(m_stPath.c_str(), &m_pDB);
        _check_info(int, !ret, err_store_open, ret);

        m_stmtBeginTrs    = tStatement(m_pDB, "begin transaction;");
        m_stmtCommitTrs   = tStatement(m_pDB, "commit transaction;");
        m_stmtRollbackTrs = tStatement(m_pDB, "rollback transaction;");
        m_stmtGetCounter  = tStatement(m_pDB, "select counter from DataStore;");
        m_stmtUpdCounter  = tStatement(m_pDB, "update DataStore set counter = :a;");
        m_stmtGetDef      = tStatement(m_pDB, "select exp from DefTable where tag = :a;");
        m_stmtAddDef      = tStatement(m_pDB, "insert into DefTable values (:a, :b, :c);");
        m_stmtGetDefList  = tStatement(m_pDB, "select tag from DefTable where ontology = :a;");
        m_stmtGetIdent    = tStatement(m_pDB, "select * from SymTable where tag = :a;");
        m_stmtAddIdent    = tStatement(m_pDB, "insert into SymTable values (:a, :b, :c, :d);");
        m_stmtGetId       = tStatement(m_pDB, "select tag from SymTable where nspace = :a and name = :b and type = :c;");
        m_stmtGetIdList   = tStatement(m_pDB, "select tag from SymTable where type = :a;");

        LoadUID();
    }
    catch(...)
    {
        clear();
        throw;
    }
}

// ............................................................................
// Begin transaction
void tStoreSQLite::Begin()
{
    m_stmtBeginTrs.exec();
    LoadUID();
}

// ............................................................................
// End transaction
void tStoreSQLite::Commit()
{
    initAll();
    m_stmtCommitTrs.exec();
}

// ............................................................................
// Rollback transaction
void tStoreSQLite::Rollback()
{
    initAll();
    m_stmtRollbackTrs.exec();
}

// ............................................................................
// Load uid couter
dword tStoreSQLite::LoadUID()
{
    m_stmtGetCounter.init();
    tValue oCounter = m_stmtGetCounter.exec_scalar();
    _check(!oCounter.null(), err_store_cnt);
    m_nCounter = oCounter;

    return m_nCounter;
}

// ............................................................................
// Get next uid
dword tStoreSQLite::NextUID()
{
    return ++ m_nCounter;
}

// ............................................................................
// Update uid
void tStoreSQLite::UpdateUID()
{
    m_stmtUpdCounter.bind(m_nCounter);
    m_stmtUpdCounter.exec();
}

// ............................................................................
// Get symbol definition
bool tStoreSQLite::GetDefinition(const operator_t  i_nId, _buffer<byte>& o_oDef)
{
    bool fRet = false;
    o_oDef.clear();
    m_stmtGetDef.bind(i_nId);
    if (m_stmtGetDef.exec_step())
    {
        const tValue& oValue = m_stmtGetDef[0];
        
        if (fRet = (!oValue.null())) 
                o_oDef = oValue;
    }

    return fRet;
}

// ............................................................................
// Add symbol definition
void tStoreSQLite::AddDefinition(const operator_t i_nOntology, const operator_t i_nId, const _buffer<byte>& i_oDef)
{
    m_stmtAddDef.bind(i_nOntology, i_nId, i_oDef);
    m_stmtAddDef.exec();
}

// ............................................................................
// Get list of definitions of a given ontology
void tStoreSQLite::GetDefinitionList(const operator_t i_nOntology)
{
    m_stmtGetDefList.bind(i_nOntology);
}

// ............................................................................
// Get next id in list
operator_t tStoreSQLite::GetNextDefinition()
{
    operator_t nOp = 0;
    if (m_stmtGetDefList.exec_step())
    {
        nOp = m_stmtGetDefList[0];
    }

    return nOp;
}

// ............................................................................
// Get identifier
bool tStoreSQLite::GetSymbol(const operator_t i_nId, tIdentifier& o_oIdent)
{
    bool fRet = false;
    m_stmtGetIdent.bind(i_nId);
    if (m_stmtGetIdent.exec_step())
    {
        const tValue& oId = m_stmtGetIdent[0];

        if (fRet = (!oId.null()))
        {
            const tValue& oName = m_stmtGetIdent[1];
            o_oIdent = tIdentifier(oId, oName);
        }
    }
    
    return fRet;
}

// ............................................................................
// Add identifier
void tStoreSQLite::AddSymbol(const operator_t i_nId, const tIdentifier& i_oIdent)
{
    m_stmtAddIdent.bind(i_oIdent.first, i_oIdent.second, OP_MAKE(OP_TYPE(i_nId), 0), i_nId);
    m_stmtAddIdent.exec();
}

// ............................................................................
// Get id
operator_t tStoreSQLite::GetId(const tIdentifier& i_oIdent, const operator_t i_nType)
{
    m_stmtGetId.bind(i_oIdent.first, i_oIdent.second, OP_MAKE(i_nType, 0));
    return (operator_t) m_stmtGetId.exec_scalar();
}

// ............................................................................
// Get list of Ids of a given type
void tStoreSQLite::GetIdList(const operator_t i_nType)
{
    m_stmtGetIdList.bind(OP_MAKE(i_nType, 0));
}

// ............................................................................
// Get next id in list
operator_t tStoreSQLite::GetNextId()
{
    operator_t nOp = 0;
    if (m_stmtGetIdList.exec_step())
    {
        nOp = m_stmtGetIdList[0];
    }

    return nOp;
}

// ............................................................................
// Store factory
spiStore StoreFactorySQLite::Create(const char* i_pszPath)
{
    spiStore sp;

    _check(tFile::exist(i_pszPath), err_dlite_notfnd);

    sp = new tStoreSQLite(i_pszPath);
    return sp;
}

// ............................................................................
// Create/initialize new store
spiStore StoreFactorySQLite::CreateNew(const char* i_pszPath)
{
    spiStore sp;

    _check(!tFile::exist(i_pszPath), err_store_create);

    try
    {
        tStoreSQLite* poStore = new tStoreSQLite(i_pszPath);
        sp = dynamic_cast<iStore*>(poStore);
        poStore->initDtb();
    }
    catch(...)
    {
        sp.clear();
        tFile::erase(i_pszPath);
        throw;
    }
    return sp;
}
