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
 * OperatorRole.java
 *
 */

package DL.Ontology;

import java.util.*;

import DL.Common.*;
import DL.Ontology.Expression.*;

/**
 * Role operator class
 * 
 */
public class OperatorRole extends Operator {

    /** c'tor */
    protected OperatorRole(OperatorID id) {

        super(id);
    }

    /** Complement not operator flag */
    @Override public void Not() { }

    /** Apply not operator */
    @Override public void ApplyNot() { }
    
    /** Get not operator flag */
    @Override public boolean getNot() { return false; } 
    
    /** Apply concept operator */
    public static void Apply(ISymbolTable table, Identifier ident, Stack<Operator> stack) throws Exception {

        OperatorID id = table.getID(ident, OperatorType.Role);
        stack.push(new OperatorRole(id));
    }
    
    /** Factory method */
    public static Operator Create(OperatorID id, ArrayList<Operator> args) throws DLException {

        if (args.size() > 0) throw new DLException("Invalid number of arguments"); 

        Operator op = new OperatorRole(id);
        op.addAll(args);

        return op;
    } 
}
