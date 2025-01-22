#ifndef __CACHE_H__
#define	__CACHE_H__

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
// File    : cache.h
// Author  : main
// Created : September 13, 2008, 4:32 PM
// 
// Desc    : LRU Cache
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // LRU Cache template

    template <class _Key, class _Data> class _lru_cache
    {
    protected:

        // Types
        class _entry;

        typedef map<_Key, _entry>              _map;
        typedef pair<_Key, _entry>             _map_ent;
        typedef typename _map::iterator        _map_it;
        typedef typename _map::const_iterator  _map_it_c;
        typedef pair<_map_it, bool>            _map_ret;
        typedef list<_map_it >                 _list;
        typedef typename _list::iterator       _list_it;

        // Cache entry
        class _entry
        {
        private:

            _Data       m_data;     // Data
            _list_it    m_list_it;  // List iterator

        protected:

            // Assign
            _entry& assign(const _entry& i_entry)
            {
                m_data    = i_entry.m_data;
                m_list_it = i_entry.m_list_it;

                return *this;
            }

        public:

            // c'tor
            _entry() : m_data(_Data()), m_list_it(_list().end()) {}
            _entry(const _Data& i_data, const _list_it i_list_it) : m_data(i_data), m_list_it(i_list_it) {}
            _entry(const _entry& i_entry) { assign(i_entry); }

            // Attributes
            _Data& getData() const { return m_data; }
            void setData(const _Data& i_data) { m_data = i_data; }

            _list_it getListIt() const { return m_list_it; }
            void setListIt(const _list_it i_list_it) { m_list_it = i_list_it; }

            // Conv
            operator _Data&() { return m_data; }
            operator const _Data&() const { return m_data; }
        };

    private:

        _map   m_map;
        _list  m_list;
        size_t m_cap;

    protected:

        // Erase cache entry
        void erase(const _list_it& i_list_it)
        {
            _map_it map_it = *i_list_it;
            m_list.erase(i_list_it);
            m_map.erase(map_it);
        }

        // Promote cache entry
        void promote(const _list_it& i_list_it)
        {
            _map_it map_it = *i_list_it;
            m_list.erase(i_list_it);
            m_list.push_front(map_it);
            map_it->second.setListIt(m_list.begin());
        }

        // New cache entry
        void new_entry(const _map_it& i_map_it)
        {
            m_list.push_front(i_map_it);
            i_map_it->second.setListIt(m_list.begin());

            if (m_list.size() > m_cap)
            {
                _map_it p = m_list.back();
                erase(p->second.getListIt());
            }
        }

    public:

        // Public iterator type
        typedef typename _map::const_iterator const_iterator;

        // c'tor
        _lru_cache(const size_t i_cap) : m_cap(i_cap) {}

        // Add value
        void set(const _Key& i_key, const _Data& i_data)
        {
            _map_it p = m_map.find(i_key);
            if (p != m_map.end())
            {
                _entry& entry = p->second;
                entry.setData(i_data);
                _list_it q = entry.getListIt();
                promote(q);
            }
            else
            {
                _map_ret ret = m_map.insert(make_pair(i_key, _entry(i_data, m_list.end())));
                new_entry(ret.first);
            }
        }

        // Get value
        const _Data& get(const _Key& i_key)
        {
            static const _entry s_def;

            _map_it p = m_map.find(i_key);
            if (p != m_map.end())
            {
                promote(p->second.getListIt());
                return p->second;
            }
            else
            {
                return s_def;
            }
        }

        // Test if contains value
        bool contains(const _Key& i_key) const
        {
            return m_map.find(i_key) != m_map.end();
        }

        // Get value
        const _Data& operator[](const _Key& i_key) const { get(i_key); }

        // Get collection
        const _map& collection() const { return m_map; }

        // Count of entries in cache
        size_t count() const { return m_map.size(); }

        // Iterator
        const_iterator begin() const { return m_map.begin(); }

        // Iterator
        const_iterator end() const { return m_map.end(); }

        // Find value
        const_iterator find(const _Key& i_key) const { return m_map.find(i_key); }
    };
}

#endif	//_CACHE_H
