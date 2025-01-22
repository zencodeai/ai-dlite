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
 * Operator.java
 *
 * Expression tree node
 *
 */

package DL.Ontology;

import java.util.*;
import DL.Common.*;
import DL.Ontology.Expression.*;

/**
 * Expression tree node class
 */
public class Operator extends ArrayList<Operator> {
    
    /** Operator id */
    private OperatorID id;
    
    /** Not operator flag */
    private boolean not = false;

    /** c'tor */
    protected Operator(OperatorID id) {
        
        this.id = id;
    }
    
    /** Equals implementation */
    @Override public boolean equals(Object anObject) {
        
        return id.equals(((Operator) anObject).id) && not == ((Operator) anObject).not;
    }
    
    /** Hashcode implmentation */
    @Override public int hashCode() {
        
        return id.hashCode();
    }    
    
    /** Complement not operator flag */
    public void Not() { not = (not) ? false : true; }

    /** Apply not operator */
    public void ApplyNot() throws DLException {
        
        if (not) {
            
            id.Neg();
            for(Operator op : this) { op.Not(); }
            not = false;
        }
    }
    
    /** Get not operator flag */
    public boolean getNot() { return not; } 
    
    /** Get operator type */
    public OperatorType getType() throws DLException {
        
        return (not) ? id.Not().getOperatorType() : id.getOperatorType();
    }
    
    /** Get operator id */
    public OperatorID getID() { return id; }
    
    /** Factory method */
    public static Operator Create(OperatorID id, ArrayList<Operator> args) throws Exception {
        
        Operator op = null;
        OperatorType type = id.getOperatorType();
        
        if (type == OperatorType.Concept || type == OperatorType.ConceptNeg) 
            op = OperatorConcept.Create(id, args);
        else if (type == OperatorType.Role || type == OperatorType.RoleNeg) 
            op = OperatorRole.Create(id, args);
        else if (type == OperatorType.Top || type == OperatorType.Bottom) 
            op = OperatorTopBottom.Create(id, args);
        else if (type == OperatorType.Union || type == OperatorType.Inter) 
            op = OperatorAndOr.Create(id, args);
        else if (type == OperatorType.Univ || type == OperatorType.Exist) 
            op = OperatorUnivExist.Create(id, args);
        else
            throw new DLException("Invalid operator type");
        
        return op;
    }            
}
