#ifndef __FACTORY_H__
#define	__FACTORY_H__

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
// File    : factory.h
// Author  : main
// Created : February 11, 2009, 10:23 PM
// 
// Desc    : Expression factory
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Id generator interface
    class iIDGenerator;
    typedef _s_ptr<iIDGenerator> spiIDGenerator;

    class iIDGenerator
    {
    public:

        // d'tor
        virtual ~iIDGenerator() {}

        // Next identifier
        virtual operator_t NextUID() = 0;
    };

    // ............................................................................
    // Id generator default implementation
    class tIDGenerator : public iIDGenerator
    {
    private:

        // Id counter
        operator_t m_nId;

    public:

        // c'tor
        tIDGenerator(const operator_t i_nBase) : m_nId(i_nBase) {}

        // Next identifier
        operator_t NextUID() { return ++m_nId; }

        // Default counter init val
        static const operator_t ms_nBase = 0x00800000;

        // Factory
        static spiIDGenerator Create(const operator_t i_nBase = ms_nBase)
        {
            spiIDGenerator sp = new tIDGenerator(i_nBase);
            return sp;
        }
    };

    // ............................................................................
    // Expression factory class
    class tExprFactory
    {
    public:

        typedef stack<_buffer<operator_t> > tArgStack;

        // Errors
        enum
        {
            err_fact_type = err_off_fact,   // Invalid argument type
            err_fact_args,                  // Arguments missing
        };


    private:

        tArgStack       m_oStack;   // Argument stack
        spiIDGenerator  m_spIdGen;  // Id generator

    protected:

        // Reset object
        void reset() {}

        // Get next id
        operator_t nextId() { return m_spIdGen->NextUID(); }

        // Add #R/C
        void role(const operator_t i_nType, const operator_t i_nRole);

        // Add and/or
        void andor(const operator_t i_nType);

        // Assign
        tExprFactory& assign(const tExprFactory& i_oSrc)
        {
            m_spIdGen = i_oSrc.m_spIdGen;
            return *this;
        }

    public:

        // c'tor
        tExprFactory(const spiIDGenerator& i_spIdGen = spiIDGenerator())
        {
            m_spIdGen = i_spIdGen.null() ? tIDGenerator::Create() : i_spIdGen;
        }

        // c'tor
        tExprFactory(const tExprFactory& i_oSrc) { reset(); assign(i_oSrc); }

        // d'tor
        ~tExprFactory() {}

        // Clear factory
        void clear() { m_oStack = tArgStack(); }

        // Add concept arg
        void concept(const operator_t i_nCpt);

        // Add top arg
        void top();

        // Add bottom arg
        void bottom();

        // Add !R/C
        void univ(const operator_t i_nRole);

        // Add ?R/C
        void exist(const operator_t i_nRole);

        // Intersction
        void andop();

        // Union
        void orop();

        // Not
        void neg();

        // Get expression
        sptExpression expr() const;
        operator sptExpression() const { return expr(); }

        // Operators
        tExprFactory& operator=(tExprFactory& i_oSrc) { clear(); return assign(i_oSrc); }
    };
}

#endif	//_FACTORY_H
