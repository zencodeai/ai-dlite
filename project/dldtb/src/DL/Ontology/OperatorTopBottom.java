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
 * OperatorTopBottom.java
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
public class OperatorTopBottom extends Operator {

    /** c'tor */
    protected OperatorTopBottom(OperatorID id) {

        super(id);
    }
    
    /** Apply concept operator */
    public static void Apply(OperatorType type, Stack<Operator> stack) throws Exception {

        if (type != OperatorType.Top && type != OperatorType.Bottom) throw new DLException("Invalid TOP/BOTTOM type sepcifier");
        
        OperatorID id = OperatorID.Create(type.TagID());
        stack.push(new OperatorTopBottom(id));
    }
    
    /** Factory method */
    public static Operator Create(OperatorID id, ArrayList<Operator> args) throws DLException {

        if (args.size() > 0) throw new DLException("Invalid number of arguments"); 

        Operator op = new OperatorTopBottom(id);
        op.addAll(args);

        return op;
    } 
}
