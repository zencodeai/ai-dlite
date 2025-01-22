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
 * ExpressionBuilder.java
 *
 */

package DL.Ontology;

import java.util.*;

import DL.Ontology.Expression.*;

/**
 * Expression factory for ALC operators
 * 
 */
public class ExpressionBuilder extends Stack<Operator> {

    /** Symbol table */
    ISymbolTable table;

    /** c'tor */
    protected ExpressionBuilder(ISymbolTable table) {

        this.table = table;
    }

    /** Concept operator */
    public void Concept(Identifier id) throws Exception {

        OperatorConcept.Apply(table, id, this);
    }

    /** Role operator */
    public void Role(Identifier id) throws Exception {

        OperatorRole.Apply(table, id, this);
    }

    /** And operator */
    public void And() throws Exception {

        OperatorAndOr.Apply(table, OperatorType.Inter, this);
    }

    /** Or operator */
    public void Or() throws Exception {
        
        OperatorAndOr.Apply(table, OperatorType.Union, this);
    }

    /** Univ operator */
    public void Univ() throws Exception {

        OperatorUnivExist.Apply(table, OperatorType.Univ, this);
    }

    /** Exist operator */
    public void Exist() throws Exception {
        
        OperatorUnivExist.Apply(table, OperatorType.Exist, this);
    }

    /** Top operator */
    public void Top() throws Exception {

        OperatorTopBottom.Apply(OperatorType.Top, this);        
    }
    
    /** Bottom operator */
    public void Bottom() throws Exception {
        
        OperatorTopBottom.Apply(OperatorType.Bottom, this);
    }

    /** Complement current operator */
    public void Not() throws Exception {
        
        super.peek().Not();
    }
    
    /** Get expression */
    public ExpressionTree Expression() throws Exception {
        
        ExpressionTree tree = null;
        
        if (super.size() > 0) {
            
            tree = ExpressionTree.Create(super.pop());
            tree.NNF();
        }
        
        return tree;
    }
    
    /** Expression factory factory */
    public static ExpressionBuilder Create(ISymbolTable table) {        

        return new ExpressionBuilder(table);
    }        
}
