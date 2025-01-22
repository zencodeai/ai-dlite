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
 * OperatorConcept.java
 *
 * Concept operator
 */

package DL.Ontology;

import java.util.*;

import DL.Common.*;
import DL.Ontology.Expression.*;



/**
 * Concept operator class
 * 
 */
public class OperatorConcept extends Operator  {
        
    /** c'tor */
    protected OperatorConcept(OperatorID id) {

        super(id);
    }
    
    /** Apply concept operator */
    public static void Apply(ISymbolTable table, Identifier ident, Stack<Operator> stack) throws Exception {

        OperatorID id = table.getID(ident, OperatorType.Concept);
        stack.push(new OperatorConcept(id));
    }
    
    /** Factory method */
    public static Operator Create(OperatorID id, ArrayList<Operator> args) throws DLException {

        if (args.size() > 0) throw new DLException("Invalid number of arguments"); 
        
        Operator op = new OperatorConcept(id);
        op.addAll(args);

        return op;
    } 
}
