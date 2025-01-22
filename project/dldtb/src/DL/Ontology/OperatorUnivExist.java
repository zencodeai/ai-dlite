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
 * OperatorUnivExist.java
 *
 */

package DL.Ontology;

import java.util.*;

import DL.Common.*;
import DL.Ontology.Expression.*;

/**
 * Universal/Existential operator class
 * 
 */
public class OperatorUnivExist extends Operator {

    /** Creates a new instance of OperatorAndOr */
    protected OperatorUnivExist(OperatorID id, Operator role, Operator concept) {
        
        super(id);
        add(role);
        add(concept);
    }

    /** Operator instances factory */
    public static void Apply(ISymbolTable table, OperatorType type, Stack<Operator> stack) throws Exception {
        
        if (type != OperatorType.Univ && type != OperatorType.Exist) throw new DLException("Invalid UNIV/EXIST type sepcifier");
        
        Operator concept = stack.pop();
        Operator role    = stack.pop();
        
        if (concept.getID().getOperatorType() == OperatorType.Role) throw new DLException("Concept expected");
        if (role.getID().getOperatorType() != OperatorType.Role) throw new DLException("Role expected");

        OperatorID id = table.newOperatorID(type);
        stack.push(new OperatorUnivExist(id, role, concept));
    }
    
    /** Factory method */
    public static Operator Create(OperatorID id, ArrayList<Operator> args) throws DLException {

        if (args.size() != 2) throw new DLException("Invalid number of arguments"); 

        Operator role    = args.get(0);
        Operator concept = args.get(1);

        if (concept.getID().getOperatorType() == OperatorType.Role) throw new DLException("Concept expected");
        if (role.getID().getOperatorType() != OperatorType.Role) throw new DLException("Role expected");
        
        Operator op = new OperatorUnivExist(id, role, concept);

        return op;
    } 
}
