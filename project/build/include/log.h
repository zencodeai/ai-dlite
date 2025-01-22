#ifndef __LOG_H__
#define	__LOG_H__

#include "symtable.h"


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
// File    : log.h
// Author  : main
// Created : September 1, 2008, 8:25 PM
//
// Desc    : Logs
//
// ............................................................................

#define LOG_ENABLED

namespace DLITE
{
    // ............................................................................
    // Log flags
    enum tLogFlags
    {
        log_lev1    = 0x00000001,
        log_lev2    = 0x00000002,
        log_lev3    = 0x00000004,
        log_lev4    = 0x00000008,
        log_levall  = 0x0000000F,
        log_entry   = 0x00000010,
        log_exit    = 0x00000020,
        log_info    = 0x00000040,
        log_rsnr    = 0x00000080,
    };

    // ............................................................................
    // Logs

    #ifdef LOG_ENABLED

    // Log macros
    #define _log_init(NAME)           tLog oLog(NAME)
    #define _log_init_flg(NAME,FLAGS) tLog oLog(NAME, FLAGS)
    #define _log_store(STORE)         tLog::setStore(STORE)
    #define _log_name(OP)             tLog::toString(OP)
    #define _log                      tLog::stream(tLog::log_info)
    #define _log_entry                tLog::stream(tLog::log_entry)
    #define _log_exit                 tLog::stream(tLog::log_exit)
    #define _log_err                  tLog::stream(tLog::log_err)
    #define _log_dump(DATA,LEN)       tLog::dump((const pbyte) (DATA), (size_t) (LEN))
    #define _log_expr(EXPR)           tLog::dump(EXPR)

    // Log class
    class tLog
    {
    public:

        // Stream smart pointer
        typedef _s_ptr<ostream> spostream;

        // Log stack
        typedef stack<tLog*> logstack;

        // Null stream
        struct nullstream : ostream
        {
            nullstream(): std::ios(0), std::ostream(0) {}
        };

        // Log flags
        enum flag_t
        {
            log_null    = 0x00000000,
            log_lev1    = 0x00000001,
            log_lev2    = 0x00000002,
            log_lev3    = 0x00000004,
            log_lev4    = 0x00000008,
            log_levall  = 0x0000000F,
            log_entry   = 0x00000010,
            log_exit    = 0x00000020,
            log_info    = 0x00000040,
            log_err     = 0x00000080,
            log_all     = 0x000000FF,
            log_new     = 0x000000FF,
        };

    private:

        static logstack    ms_oStack;       // Log context stack
        static nullstream  ms_oNullStream;  // Null stream
        static tLog        ms_oDefLog;      // Default log context

        dword       m_nFlags;               // Context flags
        string      m_stName;               // Context name
        spostream   m_spStream;             // Context stream
        spiStore    m_spStore;              // Store
        spiSymTable m_spSymTable;           // Symbol table

    protected:

        // Context file name
        string file() const;

    public:

        // c'tor
        tLog();
        tLog(const string i_stName, const dword i_nFlags = log_all);

        // d'tor
        ~tLog();

        // Attributes
        bool null() const { return m_stName.empty(); }
        string name() const { return m_stName; }
        dword flags() const { return m_nFlags; }
        ostream& str() { return *m_spStream; }

        // Set store
        void store(const spiStore& i_spStore)
        {
            m_spSymTable.clear();
            m_spStore = i_spStore;
            if (!m_spStore.null())
            {
                m_spSymTable = iSymTable::Create(m_spStore);
            }
        }

        // Get operator name
        tName name(const operator_t i_nOp)
        {
            tName oName;
            if (!m_spSymTable.null())
            {
                oName = m_spSymTable->GetName(i_nOp);
            }

            return oName;
        }

        // Get stream
        static ostream& stream(const dword i_nFlags = log_all);

        // Set store
        static void setStore(const spiStore& i_spStore);

        // Convert operator to string
        static string toString(const operator_t i_nOp);

        // Dump binary data
        static void dump(const pbyte i_pbData, const size_t i_nSize, const size_t i_nBreak = 16);

        // Dump expression
        static void dump(const sptExpression& i_spExpr);
    };

    #else

    // Log macros
    #define _log_init(NAME)           //
    #define _log_init_flg(NAME,FLAGS) //
    #define _log_store(STORE)         {}
    #define _log_name(OP)             ("")
    #define _log                      //
    #define _log_entry                //
    #define _log_exit                 //
    #define _log_err                  //
    #define _log_dump(DATA,LEN)       //
    #define _log_expr(EXPR)           //

    #endif
}

#endif // __LOG_H__
