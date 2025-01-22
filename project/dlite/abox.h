#ifndef __ABOX_H__
#define	__ABOX_H__

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
// File    : abox.h
// Author  : main
// Created : January 19, 2009, 11:07 PM
// 
// Desc    : ABOX Interface
//
// ............................................................................

/*!\file abox.h
 * \brief ABox interface definition
 */

/*!\class DLITE::iABox
 * \brief ABox interface
 *
 * ABox interface definition. The default implementation implements the ABox as
 * a directed graph. Each node represents an individual.
 * Nodes are tagged with concepts IDs
 * Edges are tagged with roles IDs.
 * 
 */

/*!\enum DLITE::iABox::res_t
 * \brief ABox operation result
 */

/*!\var DLITE::iABox::res_t DLITE::iABox::res_inv
 * \brief Invalid value
 */

/*!\var DLITE::iABox::res_t DLITE::iABox::res_done
 * \brief Node/edge updated
 */

/*!\var DLITE::iABox::res_t DLITE::iABox::res_dup
 * \brief Node/edge already contains item
 */

/*!\var DLITE::iABox::res_t DLITE::iABox::res_clash
 * \brief Node/edge already contains item's complement
 */

/*!\var DLITE::iABox::res_t DLITE::iABox::res_none
 * \brief Item ignored
 */

/*!\typedef dword DLITE::iABox::slot_t
 * \brief ABox state slot ID type
 */

/*!\fn virtual DLITE::iABox::~iABox()
 * \brief Destructor
 */

/*!\fn virtual DLITE::iABox::slot_t DLITE::iABox::Save() = 0
 * \brief Save ABox state
 *
 * This method saves the the state of the ABox. It create a new slot and saves
 * the state of the ABox in it.
 * \return Saved state slot ID.
 */

/*!\fn virtual void DLITE::iABox::Restore(const DLITE::iABox::slot_t i_nSlot) = 0
 * \brief Restore ABox state
 *
 * This method restores the state of the ABox saved using the Save method.
 * All states with a slot ID greater than the one restored are discarded.
 * \param i_nSlot Id of the saved state to be restored.
 */

/*!\fn virtual DLITE::iABox::res_t DLITE::iABox::Cache(const DLITE::operator_t i_nConcept) = 0
 * \brief Add concept without filtering
 *
 * This method permit to add a concept to the currently selected node,
 * regardless of the the operator type. This is typically used for caching.
 * \param i_nConcept Concept's operator id.
 * \return ABox operation result,
 */

/*!\fn virtual DLITE::iABox::res_t DLITE::iABox::Add(const operator_t i_nConcept) = 0
 * \brief Add concept with filtering
 *
 * This method permit to add a concept to the currently selected node,
 * with filtering of the type. Only atomic concepts will be taken into account.
 *
 * \param i_nConcept Concept's operator id.
 * \return ABox operation result (iABox::res_none for non atomic concepts).
 */

/*!\fn virtual DLITE::iABox::res_t DLITE::iABox::Add(const operator_t i_nRole, const operator_t i_nNode) = 0
 * \brief Add role
 *
 * This method permits to add a role to the edge defined by the currently selected node
 * and the i_nNode parameter.
 *
 * \param i_nRole Role's operator id.
 * \param i_nNode Node id.
 * \return ABox operation result.
 */

/*!\fn virtual bool DLITE::iABox::Select(const operator_t i_nNode) = 0
 * \brief Select node
 *
 * This method permit to select a node. Subsequent Add and Cache operations will apply to this node.
 *
 * \param i_nNode selected node id (individual id).
 * \return true: found, false: not found.
 */

/*!\fn virtual operator_t DLITE::iABox::CurNode() = 0
 * \brief Select node
 *
 * Thid method returns the name of the currently selected node.
 *
 * \return id of the currently selected node (individual id),
 * 0 if no node is currently selected.
 */

/*!\fn virtual operator_t DLITE::iABox::NewNode(const operator_t i_nNode = 0) = 0
 * \brief Create new node
 *
 * This metod permit to create a new node identified by an individual id.
 * If no id is specified or if i_nNode is set to 0, a new node id will
 * be generated.
 *
 * \param i_nNode (optional) node id (individual id).
 * \return i_nNode if i_nNode not 0 or new node id if i_nNode set to 0.
 *
 */

/*!\fn virtual DLITE::iABox::res_t DLITE::iABox::Check(const operator_t i_nNode, const operator_t i_nConcept) = 0
 * \brief Check if concept belongs to node
 *
 * This methods permits to check if a concept (or its complement) belongs to the
 * selected node. Behaves like the Add method but without modifying the
 * selected noode.
 *
 * \param i_nConcept Concept's operator id.
 * \return ABox operation result (iABox::res_none for non atomic concepts).
 *
 */

/*!\fn virtual list<operator_t> DLITE::iABox::Successors(const operator_t i_nRole) = 0
 * \brief Get node's successors for given role
 *
 * This method permits the retrieve the list of successors of the current node
 * for the specified role,
 *
 * \param i_nRole role operator id.
 * \return list of successors (individual ids) for role i_nRole..
 */

/*!\fn virtual void DLITE::iABox::Clear() = 0
 * \brief Clear ABox
 *
 * This method clears the ABox content.
 *
 */

/*!\fn virtual bool DLITE::iABox::Empty() const = 0
 * \brief Check if ABox is empty
 *
 * This method permits to check if the ABox is empty.
 *
 * \return true: ABox empty, false ABox not empty..
 */

/*!\fn static DLITE::spiABox DLITE::iABox::Create()
 * \brief Factory method for default implementation
 *
 * This static method creates an ABox instance.
 *
 * \return ABox instance smart pointer.
 *
 */

namespace DLITE
{
    // ............................................................................
    // ABOX interface
    class iABox;
    typedef _s_ptr<iABox> spiABox;

    class iABox
    {
    public:

        // ABox assertion result
        enum res_t
        {
            res_inv,    // Invalid
            res_done,   // No clash
            res_dup,    // Already in
            res_clash,  // Clash
            res_none,   // No action
        };

        typedef dword slot_t;

    protected:

        // c'tor
        iABox() {}

    public:

        //Destructor
        virtual ~iABox() {}

        //Save model state
        virtual slot_t Save() = 0;

        // Restore model
        virtual void Restore(const slot_t i_nSlot) = 0;

        // Add concept
        virtual res_t Cache(const operator_t i_nConcept) = 0;

        // Add concept
        virtual res_t Add(const operator_t i_nConcept) = 0;

        // Add role
        virtual res_t Add(const operator_t i_nRole, const operator_t i_nNode) = 0;

        // Select node
        virtual bool Select(const operator_t i_nNode) = 0;

        // Current node
        virtual operator_t CurNode() = 0;

        // New node
        virtual operator_t NewNode(const operator_t i_nNode = 0) = 0;

        // Check if concept belongs to node
        virtual res_t Check(const operator_t i_nNode, const operator_t i_nConcept) = 0;

        // Successors
        virtual list<operator_t> Successors(const operator_t i_nRole) = 0;

        // Clear ABox
        virtual void Clear() = 0;

        // Empty?
        virtual bool Empty() const = 0;

        // Factory method
        static spiABox Create();
    };
}

#endif	//_ABOX_H
