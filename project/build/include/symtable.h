#ifndef __SYMTABLE_H__
#define	__SYMTABLE_H__

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
// File    : symtable.h
// Author  : main
// Created : February 13, 2010, 8:41 AM
// 
// Desc    : Symbol table interface
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Name class
    class tName : public list<string>
    {
    protected:

        // Split string
        void split(const string& i_st, const char* i_sep = ":")
        {
            _buffer<char> buf(i_st.size() + 1, i_st.c_str());

            clear();
            char* tok = strtok (buf.ptr(), i_sep);
            while (tok != NULL)
            {
                push_back(tok);
                tok = strtok (NULL, i_sep);
            }
        }

    public:

        // c'tor
        tName() {}
        tName(const string& i_stId) { split(i_stId); }
        tName(const tName& i_oName) : list<string>(i_oName) {}

        // String rep
        string toString() const
        {
            stringstream sst;
            string st;
            for(const_iterator p = begin(); p != end(); p ++)
            {
                sst << st << *p;
                if (st.empty()) st = ":";
            }

            return sst.str();
        }
    };

    // ............................................................................
    // Symbol table interface

    class iSymTable;
    typedef _s_ptr<iSymTable> spiSymTable;

    class iSymTable
    {
    protected:

        // c'tor
        iSymTable() {}

    public:

        // d'tor
        virtual ~iSymTable() {}

        // Get symbol name (empty if none)
        virtual tName GetName(const operator_t i_nId) = 0;

        // Get symbol id (invalid if none)
        virtual operator_t GetId(const tName& i_oName, const operator_t i_nType) = 0;

        // Add symbol name (return existing))
        virtual operator_t AddName(const tName& i_oName, const operator_t i_nType) = 0;

        // Factory method
        static spiSymTable Create(const spiStore& i_spStore);
    };
}

#endif	//__SYMTABLE_H__
