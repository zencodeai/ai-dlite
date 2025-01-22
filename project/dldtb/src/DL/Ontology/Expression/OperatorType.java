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

/*
 * OperatorType.java
 *
 * DL operators types
 *
 */

package DL.Ontology.Expression;

/**
 * DL operators types enumeration
 *
 */
public enum OperatorType {

    /** Invalid  type */
    Invalid     (0x00, 0x00),

    /** Ontology identifier */
    Ontology    (0x01, 0x00),

    /** Namespace */
    Namespace   (0x02, 0x00),

    /** Concept definition */
    Definition  (0x03, 0x00),

    /** Global concept inclusion */
    GCI         (0x04, 0x00),

    /** Individual */
    Individual  (0x05, 0x00),

    /** Concept */
    Concept     (0x06, 0x01),

    /** Concept with atomic negation */
    ConceptNeg  (0x07, 0x01),

    /** Role */
    Role        (0x08, 0x00),

    /** Role with negation */
    RoleNeg     (0x09, 0x00),

    /** Universal concept */
    Top         (0x0A, 0x01),

    /** Bottom concept */
    Bottom      (0x0B, 0x01),

    /** Universal quantifier */
    Univ        (0x0C, 0x01),

    /** Existential quantifier */
    Exist       (0x0D, 0x01),

    /** Union operator */
    Union       (0x0E, 0x01),

    /** Intersection operator */
    Inter       (0x0F, 0x01);

    /** Operator negation mask */
    public static final int NegMask = 0x01000000;

    /** Operator ID mask */
    public static final int IDMask  = 0x00FFFFFF;

    /** Constant tag id */
    private final int typeID;

    /** Tag complement mask */
    private final int negMask;

    /**
     * c'tor
     * 
     * @param typeID   ID of the tag
     * @param negMask Tag complement mask
     */
    OperatorType(int typeID, int negMask) {

        this.typeID = typeID << 24;
        this.negMask = negMask << 24;
    }

    /**
     * Build operator tag from tag ID
     *
     * @param id Operator unique id
     */
    public int Tag(int id) {

        return (id & IDMask) | typeID;
    }

    /**
     * Get type (tag ID)
     *
     * @param id Operator unique id
     */
    public int TagID() {

        return typeID;
    }

    /** 
     * Apply negation to operator
     *
     * @param tag tag to negate
     */
    public int Neg(int tag) {

        return tag ^ negMask;
    }

    /** 
     * Get operator absolute value 
     *
     * @param tag tag to negate
     */
    public int Abs(int tag) {

        return tag & (~negMask);
    }
}
