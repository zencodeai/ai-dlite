#ifndef __SPTR_H__
#define	__SPTR_H__

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
// File    : sptr.h
// Author  : main
// Created : September 1, 2008, 8:25 PM
//
// Desc    : Smart pointers
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Instance counter
    class _s_ptr_cnt
    {
    private:

        int cnt;

    public:

        _s_ptr_cnt() : cnt(1) {}

        inline void inc() { cnt ++; }

        inline bool dec() { return (-- cnt > 0) ? true : (cnt = 0, false); }

        inline bool last() const { return cnt == 1; }

        static _s_ptr_cnt* create() { return new _s_ptr_cnt(); }

        static void free(const _s_ptr_cnt* p) { if (p) delete p; }
    };

    // Free single instance
    template <typename _Type> class _s_ptr_free
    {
    public:

        inline static void free(const _Type* p) { if (p) delete p; }
    };

    // Free array
    template <typename _Type> class _s_ptr_free_arr
    {
    public:

        inline static void free(const _Type* p) { if (p) delete[] p; }
    };

    // Smart pointers class template
    template <typename _Type, class _Cnt = _s_ptr_cnt, class _Del = _s_ptr_free<_Type> > class _s_ptr
    {
    public:

        typedef _Type* _pType;
        typedef _Cnt*  _pCnt;

    private:

        _pType m_ptr;
        _pCnt  m_cnt;

    protected:

        void reset()
        {
            m_ptr = NULL;
            m_cnt = NULL;
        }

        _s_ptr& assign(const _s_ptr& right)
        {
            m_ptr = right.m_ptr;
            m_cnt = right.m_cnt;

            if (m_cnt) m_cnt->inc();

            return *this;
        }

        _s_ptr& assign(const _pType right)
        {
            m_ptr = right;
            if (m_ptr) m_cnt = _Cnt::create();

            return *this;
        }

    public:

        void clear()
        {
            if (m_cnt && !m_cnt->dec())
            {
                _Del::free(m_ptr);
                _Cnt::free(m_cnt);
            }

            reset();
        }

        _s_ptr() { reset(); }

        _s_ptr(const _s_ptr& sp) { reset(); assign(sp); }

        _s_ptr(const _pType  p ) { reset(); assign(p); }

        ~_s_ptr() { clear(); }

        _s_ptr& operator=(const _s_ptr& right) { clear(); return assign(right); }

        _s_ptr& operator=(const _pType  right) { clear(); return assign(right); }

        bool null() const { return m_ptr == NULL; }

        bool last() const { return (m_cnt) ? m_cnt->last() : false; }

        _pType ptr() const { return m_ptr; }

        operator _pType() const { return m_ptr; }

        operator const _pType() const { return (const _pType) m_ptr; }

        _Type& operator*() const { return *m_ptr; }

        _pType operator->() const { return m_ptr; }
    };

    // ............................................................................
    // Allocator
    template <typename _Type> class _buffer_alloc
    {
    public:

        static _Type* alloc(const size_t i_sz) { return (i_sz) ? new _Type[i_sz] : NULL; }
    };

    // Buffer class template
    template <  typename _Type,
                class _Cnt = _s_ptr_cnt,
                class _Alloc = _buffer_alloc<_Type>,
                class _Del = _s_ptr_free_arr<_Type> >
    class _buffer
    {
    public:

        typedef _s_ptr<_Type, _Cnt, _Del> _Ptr;

    private:

        _Ptr   m_sp;
        size_t m_sz;

    protected:

        void reset()
        {
            m_sz = 0;
        }

        _buffer& assign(const _buffer& right)
        {
            m_sp = right.m_sp;
            m_sz = right.m_sz;

            return *this;
        }

        _buffer& assign(const size_t i_sz, const _Type* i_p)
        {
            m_sp = _Alloc::alloc(i_sz);
            m_sz = i_sz;

            if (i_sz && i_p) memcpy(m_sp.ptr(), i_p, i_sz*sizeof(_Type));

            return *this;
        }

    public:

        void clear()
        {
            m_sp.clear();
            reset();
        }

        _buffer() { reset(); }

        _buffer(const _buffer& buf) { reset(); assign(buf); }

        _buffer(const size_t i_sz, const _Type* i_p = NULL) { reset(); assign(i_sz, i_p); }

        ~_buffer() { clear(); }

        _buffer& operator=(const _buffer& i_buf) { clear(); return assign(i_buf); }

        _buffer& set(const size_t i_sz, const _Type* i_p = NULL) { clear(); return assign(i_sz, i_p); }

        _Type* ptr() const { return m_sp.ptr(); }

        _Type* end() const { return m_sp.null() ? NULL : m_sp.ptr() + m_sz; }

        size_t size() const { return m_sz; }

        bool null() const { return m_sp.null(); }

        _buffer clone() const { return _buffer(m_sz, m_sp.ptr()); }
    };
}

#endif	// __SPTR_H__
