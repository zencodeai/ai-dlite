#ifndef __TBOX_H__
#define	__TBOX_H__

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
// File    : tbox.h
// Author  : main
// Created : September 21, 2008, 8:58 AM
// 
// Desc    : TBOX interface
//
// ............................................................................

/*!\file tbox.h
 * \brief TBox interface definition
 */

/*!\class  DLITE::iTBox
 * \brief TBox interface
 *
 * TBox interface definition.
 *
 */

/*!\fn virtual  DLITE::iTBox::~iTBox()
 * \brief Destructor
 */

/*!\fn virtual DLITE::sptExpression  DLITE::iTBox::GetDefinition(const operator_t i_operator) = 0
 * \brief Retrieves concept's definition
 *
 * This method retrieves the expression associated with a given concept.
 * \param i_operator Concept id.
 * \return Expression object pointer. Null if expression not found.
 */

/*!\fn virtual void  DLITE::iTBox::AddDefinition(const operator_t i_ontology, const operator_t i_operator, const sptExpression& i_spExpr) = 0
 * \brief Add concept definition
 *
 * This methods adds a concept definition to the TBox.
 * \param i_ontology ontology ID
 * \param i_operator concept ID
 * \param i_spExpr expression object pointer
 *
 */

/*!\fn static DLITE::spiTBox DLITE::Create(const spiStore& i_spStore)
 * \brief Create TBox instance
 *
 * This methods creates a TBox instance
 * \param i_spStore ontology store object pointer
 * \return DLITE::spiTBox TBox object pointer
 *
 */

namespace DLITE
{
    // ............................................................................
    // TBOX interface

    class iTBox;
    typedef _s_ptr<iTBox> spiTBox;

    class iTBox
    {
    protected:

        // c'tor
        iTBox() {}

    public:

        // d'tor
        virtual ~iTBox() {}

        // Get definition (sp is null if none)
        virtual sptExpression GetDefinition(const operator_t i_operator) = 0;

        // Add definition
        virtual void AddDefinition(const operator_t i_ontology, const operator_t i_operator, const sptExpression& i_spExpr) = 0;

        // Factory method
        static spiTBox Create(const spiStore& i_spStore);
    };
}

#endif	//__TBOX_H__
