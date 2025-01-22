#ifndef __OBJECT_H__
#define	__OBJECT_H__

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
// File    : object.h
// Author  : main
// Created : September 28, 2008, 7:56 PM
// 
// Desc    : Type encapsulation
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Object class
    class tObject
    {
    public:

        tObject() {}
    };

    // ............................................................................
    // Object class
    template<class _Type, _Type _xDefault> class _tObject : public tObject
    {
    private:

        _Type m_xData;

    public:

        // c'tor
        _tObject(const _Type& i_xData = _xDefault) : m_xData(i_xData) {}
        _tObject(const _tObject& i_oSrc) : m_xData(i_oSrc.m_xData) {}

        // Assign
        _tObject& operator=(const _tObject& i_oSrc) { m_xData = i_oSrc.m_xData; return *this; }
        _tObject& operator=(const _Type& i_xData) { m_xData = i_xData; return *this; }

        // Conv
        operator _Type() { return m_xData; }
    };
}

#endif	//__OBJECT_H__
