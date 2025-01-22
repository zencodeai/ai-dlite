#ifndef __SHARED_H__
#define	__SHARED_H__

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
// File    : shared.h
// Author  : main
// Created : September 1, 2008, 8:25 PM
// 
// Desc    : Common definitions
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Shared definitions

    typedef unsigned char  byte, *pbyte;
    typedef unsigned short word, *pword;
    typedef unsigned long  dword, *pdword;

    // ............................................................................
    // Application exception

    #define __DEBUG_INFO__

    class app_exception : public std::exception
    {
    private:

        int m_code;    // Error code

        #ifdef __DEBUG_INFO__
        const char* m_file; // Source file
        int m_line;         // Line number
        #endif //__DEBUG_INFO__

    protected:

        // Reset
        void reset()
        {
            m_code = 0;    // Error code

            #ifdef __DEBUG_INFO__
            m_file = NULL;
            m_line = 0;
            #endif //__DEBUG_INFO__
        }

        // Clear
        virtual void clear() { reset(); }

        // Assign
        app_exception&  assign(const app_exception& i_src)
        {
            m_code = i_src.m_code;

            #ifdef __DEBUG_INFO__
            m_file = i_src.m_file;
            m_line = i_src.m_line;
            #endif //__DEBUG_INFO__

            return *this;
        }

    public:

        // c'tor
        app_exception() throw() { reset(); }
        app_exception(const int i_code) throw() { reset(); m_code = i_code; }
        app_exception(const app_exception& i_src) throw() { reset(); assign(i_src); }

        #ifdef __DEBUG_INFO__
        app_exception(const int i_code, const char* i_file, const int i_line) throw()
        {
            reset();
            m_code = i_code;
            m_file = i_file;
            m_line = i_line;
        }
        #endif //__DEBUG_INFO__

        // Assign
        app_exception& operator=(const app_exception& i_src) throw()
        {
            clear();
            return assign(i_src);
        }

        // d'tor
        virtual ~app_exception() throw() { clear(); }

        // Error message
        virtual const char* what() const throw()
        {
            try
            {
                stringstream sstr;

                #ifdef __DEBUG_INFO__
                if (m_file) sstr << m_file << " : " << m_line << " : ";
                #endif //__DEBUG_INFO__
                sstr << hex << m_code;

                return sstr.str().c_str();
            }
            catch(...)
            {
                return "exception";
            }
        }
    };

    // ............................................................................
    // Application exception

    template<class _Type> class info_exception : public app_exception
    {
    private:

        _Type m_info;

    protected:

        // Reset
        void reset()
        {
        }

        // Clear
        virtual void clear() { reset(); }

        // Assign
        info_exception&  assign(const info_exception& i_src)
        {
            m_info = i_src.m_info;

            return *this;
        }

    public:

        // c'tor
        info_exception() throw() { reset(); }
        info_exception(const int i_code, const _Type i_info) throw() : app_exception(i_code) { reset(); m_info = i_info; }
        info_exception(const app_exception& i_src) throw() { reset(); assign(i_src); }

        #ifdef __DEBUG_INFO__
        info_exception(const int i_code, const char* i_file, const int i_line, const _Type i_info) throw()
                : app_exception(i_code, i_file, i_line)
        {
            reset();
            m_info = i_info;
        }
        #endif //__DEBUG_INFO__

        // Assign
        info_exception& operator=(const info_exception& i_src) throw()
        {
            clear();
            return assign(i_src);
        }

        // d'tor
        virtual ~info_exception() throw() { clear(); }
    };

    // ............................................................................
    // Error macros

    #ifdef __DEBUG_INFO__
    #define _check(COND, CODE) { if (!(COND)) { throw app_exception((CODE), (__FILE__), (__LINE__)); } }
    #define _check_info(TYPE, COND, CODE, INFO) { if (!(COND)) { throw info_exception<TYPE>((CODE), (__FILE__), (__LINE__), (INFO)); } }
    #else // __DEBUG_INFO__
    #define _check(COND, CODE) { if (!(COND)) throw app_exception((CODE)); }
    #define _check_info(TYPE, COND, CODE, INFO) { if (!(COND)) throw info_exception<TYPE>((CODE), (INFO)); }
    #endif // __DEBUG_INFO__

    // ............................................................................
    // File utils
    class tFile
    {
    private:

        // c'tor
        tFile() {}

    public:

        // Check if file exist
        static bool exist(const string& i_stPath)
        {
            return !access(i_stPath.c_str(), 0);
        }

        // Delete file
        static void erase(const string& i_stPath)
        {
            unlink(i_stPath.c_str());
        }
    };
}

#endif //__SHARED_H__
