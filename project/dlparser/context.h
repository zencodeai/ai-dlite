#ifndef __CONTEXT_H__
#define	__CONTEXT_H__

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
// File    : context.h
// Author  : main
// Created : March 14, 2010, 11:35 PM
//
// Desc    : Parser context
//
// ............................................................................

namespace DLITE
{
    // ............................................................................
    // Parser context

    class tContext;
    typedef _s_ptr<tContext> sptContext;

    class tContext
    {
    private:

        string          m_stName;      // Ontology name
        operator_t      m_nId;         // Ontology ID
        spiStore        m_spStore;     // Store
        spiTBox         m_spTBox;      // TBox
        spiSymTable     m_spSymTable;  // Symbol table
        list<string>    m_oErrors;     // Errors

        tExprFactory    m_oFactory;    // Expression factory

    protected:

        // Get name id
        operator_t getNameId(const tName& i_oName, const operator_t i_nType)
        {
            operator_t nId = OP_INVALID;
            if (m_spTBox.null())
            {
                nId = m_spSymTable->GetId(i_oName, i_nType);
                if (OP_INVALID == nId)
                {
                    string st = "Unknown symbol " + i_oName.toString();
                    m_oErrors.push_back(st);
                }
            }
            else
            {
                nId = m_spSymTable->AddName(i_oName, i_nType);
            }

            return nId;
        }

    public:

        // c'tor
        tContext(const string& i_stName, const spiStore& i_spStore);

        // c'tor
        tContext(const spiStore& i_spStore);

        // Error list
        list<string> getErrors() const { return m_oErrors; }
        void addError(const string& i_stError) { m_oErrors.push_back(i_stError); }

        // Expression
        sptExpression getExpr() { return m_oFactory.expr(); }

        // Clear context
        void clear()
        {
            m_oFactory.clear();
            m_oErrors.clear();
        }

        // Ontology
        void s_ontology();
        // Header
        void s_header();
        // Name
        void lit_name(const pANTLR3_COMMON_TOKEN v);
        // Version
        void lit_version(const pANTLR3_COMMON_TOKEN v);
        // Attribute
        void s_attribute(const pANTLR3_COMMON_TOKEN n, const pANTLR3_COMMON_TOKEN v);
        // Include
        void s_include(const pANTLR3_COMMON_TOKEN v);
        // Begin namespace
        void ns_begin(const pANTLR3_COMMON_TOKEN v);
        // End namespace
        void ns_end();
        // Concept definition
        void s_definition(const pANTLR3_COMMON_TOKEN n);
        // Expression
        void s_expr();
        // Disjunction
        void op_or();
        // Conjunction
        void op_and();
        // Top
        void op_top();
        // Bottom
        void op_bottom();
        // Conditional
        void op_cond(const pANTLR3_COMMON_TOKEN v);
        // Atom
        void op_atom(const pANTLR3_COMMON_TOKEN v);
        // Universal
        void op_univ(const pANTLR3_COMMON_TOKEN r);
        // Existential
        void op_exist(const pANTLR3_COMMON_TOKEN r);
        // Max cardinality
        void op_maxcard(const pANTLR3_COMMON_TOKEN n, const pANTLR3_COMMON_TOKEN r);
        // Min cardinality
        void op_mincard(const pANTLR3_COMMON_TOKEN n, const pANTLR3_COMMON_TOKEN r);
        // Constraint
        void op_constraint(const pANTLR3_COMMON_TOKEN a, const pANTLR3_COMMON_TOKEN o);
        // Not
        void op_not();
        // Value (var)
        void lit_value_variable(const pANTLR3_COMMON_TOKEN v);
        // Value (uint)
        void lit_value_uint(const pANTLR3_COMMON_TOKEN v);
        // Value (int)
        void lit_value_int(const pANTLR3_COMMON_TOKEN v);
        // Value (float)
        void lit_value_float(const pANTLR3_COMMON_TOKEN v);
        // Value (string)
        void lit_value_string(const pANTLR3_COMMON_TOKEN v);
        // List (begin)
        void lit_list_begin();
        // List (end)
        void lit_list_end();
        // List item
        void lit_list_iten(const pANTLR3_COMMON_TOKEN v);
        // In
        void op_in(const pANTLR3_COMMON_TOKEN a);
        // Concept
        void s_concept();
        // Constant definition
        void s_def(const pANTLR3_COMMON_TOKEN v);
        // Constant
        void lit_constant(const pANTLR3_COMMON_TOKEN v);

        // Error handler
        static void errorHdlr(pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8* tokenNames);

        // Factory
        static sptContext Create(const string& i_stName, const spiStore& i_spStore);

        // Factory
        static sptContext Create(const spiStore& i_spStore);
    };
}

#endif //__CONTEXT_H__
