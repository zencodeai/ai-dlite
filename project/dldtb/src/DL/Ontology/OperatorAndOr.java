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
 * OperatorAndOr.java
 *
 * AND/OR operator
 */

package DL.Ontology;

import java.util.*;

import DL.Common.*;
import DL.Ontology.Expression.*;

/**
 * And/Or operator class
 * 
 */
public class OperatorAndOr extends Operator {

    /*
    public void Apply(ExpressionBuilder expressionFactory) {
        
        IExpressionBuilderOperator right = expressionFactory.pop();
        IExpressionBuilderOperator left = expressionFactory.pop();
        add(left.getOperator());
        add(right.getOperator());
        expressionFactory.push(this);
    }
    */

    /** Creates a new instance of OperatorAndOr */
    protected OperatorAndOr(OperatorID id) {
        
        super(id);
    }

    /** Add operator */
    protected void add(OperatorType type, OperatorType typeArg, Operator arg) {
        
        if (type == typeArg) {
            
            if (arg.getNot()) {
             
                for(Operator op : arg) op.Not();
            }
            
            addAll(arg);
        }
        else {
            
            add(arg);
        }
    }
    
    /** Operator instances factory */
    public static void Apply(ISymbolTable table, OperatorType type, Stack<Operator> stack) throws Exception, DLException {
        
        if (type != OperatorType.Inter && type != OperatorType.Union) throw new DLException("Invalid AND/OR type sepcifier");

        Operator right = stack.pop();
        Operator left = stack.pop();
        
        OperatorType typeLeft = left.getType();
        OperatorType typeRight = right.getType();
        
        if (type == OperatorType.Inter && (typeLeft == OperatorType.Bottom || typeRight == OperatorType.Bottom)) {
            
            OperatorTopBottom.Apply(OperatorType.Bottom, stack);
        }
        else if (type == OperatorType.Union && (typeLeft == OperatorType.Top || typeRight == OperatorType.Top)) {
            
            OperatorTopBottom.Apply(OperatorType.Top, stack);
        }
        else {
            
            OperatorID id = table.newOperatorID(type);
            OperatorAndOr op = new OperatorAndOr(id);

            op.add(type, typeLeft, left);
            op.add(type, typeRight, right);
            
            stack.push(op);
        }        
    }
    
    /** Factory method */
    public static Operator Create(OperatorID id, ArrayList<Operator> args) throws DLException {

        if (args.size() < 2) throw new DLException("Invalid number of arguments"); 

        Operator op = new OperatorAndOr(id);
        op.addAll(args);

        return op;
    } 
}
