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
 * OperatorID.java
 *
 * Operator unique identifier
 *
 */

package DL.Ontology.Expression;

import DL.Common.*;

/**
 * Operator unique identifier class
 *
 */
public class OperatorID {

    /** OperatorTypes table */
    private static final OperatorType[] OperatorTypeTable = {
    
        OperatorType.Invalid,
        OperatorType.Ontology,
        OperatorType.Namespace,
        OperatorType.Definition,
        OperatorType.GCI,
        OperatorType.Individual,
        OperatorType.Concept,
        OperatorType.ConceptNeg,
        OperatorType.Role,
        OperatorType.RoleNeg,
        OperatorType.Top,
        OperatorType.Bottom,
        OperatorType.Univ,
        OperatorType.Exist,
        OperatorType.Union,
        OperatorType.Inter
    };

    /** Operator unique ID */
    private int id = 0;
    
    /** Operator type */
    private OperatorType operatorType = OperatorType.Invalid;

    /** Extract type from id */
    protected OperatorType getType() throws DLException {
        
        int idx = id >> 24;
        if (idx <= 0 || idx >= OperatorTypeTable.length) throw new DLException("Invalid type : " + idx);
        
        return OperatorTypeTable[idx];
    }
    
    /** Operator unique ID getter */
    public int toInt() {
        return id;
    }

    /** Get operator type */
    public OperatorType getOperatorType() {
        return operatorType;
    }
    
    /** Extract ID from id */
    public int getID() {
        
        return id & OperatorType.IDMask;
    }

    /** c'tor */
    protected OperatorID(int id) throws DLException {
        
        this.id = id;
        operatorType = getType();
    }

    /** c'tor */
    protected OperatorID(OperatorType type, int id) {
        
        this.id = type.Tag(id);
        operatorType = type;
    }

    /** Equals implementation */
    @Override public boolean equals(Object anObject) {
        
        return id == ((OperatorID) anObject).id;
    }
    
    /** Hashcode implmentation */
    @Override public int hashCode() {
        
        return id;
    }

    /** Get absolute id value */
    public OperatorID Abs() throws DLException {
        
        return OperatorID.Create(operatorType.Abs(id));
    }

    /** Get negated tag value */
    public OperatorID  Not() throws DLException {
        
        return OperatorID.Create(operatorType.Neg(id));
    }

    /** Negate tag value */
    public void Neg() throws DLException {
        
        id = operatorType.Neg(id);
    }

    /** Check if Neg flag set */
    public boolean isNeg() {
        
        return (id & OperatorType.NegMask) != 0;
    }
    
    /** Factory method */
    public static OperatorID Create(int id) throws DLException  {        
        return new OperatorID(id);
    }

    /** Factory method */
    public static OperatorID Create(OperatorType type, int id) {        
        return new OperatorID(type, id);
    }
}
