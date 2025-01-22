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
 * Expression.java
 *
 * Expression class
 *
 */

package DL.Ontology;

import DL.Common.*;

import java.util.*;

/**
 * Expression class
 *
 */
public class ExpressionTree {

    /** Context */
    protected class Context {
        
        /** Current index */
        int i = 0;
        
        /** Operator */
        Operator op;
        
        /** c'tor */
        public Context(Operator op) {
            
            this.op = op;
        }
        
        /** Next node */
        Operator Next() {
            
            return (i >= op.size()) ? null : op.get(i ++);
        }
    }
    
    /** Context interface */
    public interface IContext {
        
        /** Enter node */
        boolean Enter(Operator op) throws Exception;
        
        /** Leave node */
        void Leave() throws Exception;
    }
    
    /** NNF algo context */
    protected class ContextNNF implements IContext {
        
        /** Enter node */
        @Override public boolean Enter(Operator op) throws DLException{
            
            op.ApplyNot();
            
            return true;
        }
        
        /** Leave node */
        @Override public void Leave() {}
    }
    
    /** Root operator */
    private Operator root;
    
    /** Root operator getter */
    public Operator getRoot() {
        return root;
    }

    /** c'tor */
    protected ExpressionTree(Operator root) {
        
        this.root = root;
    }

    /** Visit expression tree */
    public void Visit(IContext context) throws Exception {
        
        Stack<Context> stack = new Stack<Context>();
        
        if (context.Enter(root)) {
            stack.push(new Context(root));

            while(!stack.empty()) {

                Context cur = stack.peek();

                Operator next = cur.Next();

                if (null == next) {

                    context.Leave();
                    stack.pop();
                } else {

                    if (context.Enter(next)) {

                        stack.push(new Context(next));
                    }
                }
            }
        }
    }
    
    /** NNF */
    public void NNF() throws Exception {
        
        ContextNNF ctx = new ContextNNF();
        Visit(ctx);
    }
    
    /** Factory method */
    public static ExpressionTree Create(Operator root) {
        
        return new ExpressionTree(root);
    }
}
