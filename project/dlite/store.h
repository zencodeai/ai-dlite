#ifndef __STORE_H__
#define	__STORE_H__

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

namespace DLITE
{
    // ............................................................................
    // Identifier type
    typedef pair<operator_t, string> tIdentifier;

    // ............................................................................
    // Reasonner store interface
    class iStore;
    typedef _s_ptr<iStore> spiStore;

    class iStore
    {
    public:

        // d'tor
        virtual ~iStore() {}

        // Open store
        virtual void Open() = 0;

        // Close store
        virtual void Close() = 0;

        // Begin transaction
        virtual void Begin() = 0;

        // End transaction
        virtual void Commit() = 0;

        // Rollback transaction
        virtual void Rollback() = 0;

        // Load uid
        virtual dword LoadUID() = 0;

        // Get next uid
        virtual dword NextUID() = 0;

        // Update uid
        virtual void UpdateUID() = 0;

        // Get symbol definition
        virtual bool GetDefinition(const operator_t i_nId, _buffer<byte>& o_oDef) = 0;

        // Add symbol definition
        virtual void AddDefinition(const operator_t i_nOntology, const operator_t i_nId, const _buffer<byte>& i_oDef) = 0;

        // Get list of definitions of a given ontology
        virtual void GetDefinitionList(const operator_t i_nOntology) = 0;

        // Get next id in list
        virtual operator_t GetNextDefinition() = 0;

        // Get identifier
        virtual bool GetSymbol(const operator_t i_nId, tIdentifier& o_oIdent) = 0;

        // Add id
        virtual void AddSymbol(const operator_t i_nId, const tIdentifier& i_oIdent) = 0;

        // Get id
        virtual operator_t GetId(const tIdentifier& i_oIdent, const operator_t i_nType) = 0;

        // Get list of Ids of a given type
        virtual void GetIdList(const operator_t i_nType) = 0;

        // Get next id in list
        virtual operator_t GetNextId() = 0;
    };

    // ............................................................................
    // Store factory
    class StoreFactorySQLite
    {
    public:

        // Create store
        static spiStore Create(const char* i_pszPath);

        // Create/initialize new store
        static spiStore CreateNew(const char* i_pszPath);
    };
}

#endif	//__STORE_H__
