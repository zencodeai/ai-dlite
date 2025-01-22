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
 * Expession class
 *
 */

package DL.Ontology.Expression.TLV;

import DL.Common.*;
import DL.Ontology.*;
import DL.Ontology.Expression.*;

import java.util.*;

/**
 * Expression class
 */
public class EncoderTLV implements IEncoder {
    
    /** Expression visitor context */
    protected class Encoder implements ExpressionTree.IContext {

        /** Encoder context */
        protected class Context {
            
            public int   offset;
            public int   size;
            
            /** c'tor */
            public Context(int offset) {
                
                this.offset = offset;
                this.size = 0;
            }
        } 

        /** Encoder buffer */
        private int[] buffer;

        /** Size */
        private int size = 0;

        /** Encoder buffer */
        public int[] getBuffer() { return buffer; }

        /** Size */
        public int getSize() { return size; }
        
        /** Context stack */
        Stack<Context> stack = new Stack<Context>();
        
        /** Enter node */
        @Override public boolean Enter(Operator op) throws Exception {
            
            int offset = 0;
            
            if (!stack.empty()) {
                
                Context cur = stack.peek(); 
                offset = cur.offset + 2 + cur.size;
            }

            stack.push(new Context(offset));
            buffer[offset] = op.getID().toInt();
            
            return true;
        }
        
        /** Leave node */
        @Override public void Leave() throws Exception {
         
            Context cur = stack.pop();
            buffer[cur.offset + 1] = cur.size;
            
            if (stack.empty()) {
                
                size = 2 + cur.size;
            } else {
                
                Context sup = stack.peek();
                sup.size += 2 + cur.size;
            }
        }
        
        /** c'tor */
        Encoder() {
            
            buffer = new int[1024];
        }
    }
        
    /** c'tor */
    protected EncoderTLV() {
    }
    
    /** Encode an expression tree */
    @Override public IExpression Encode(ExpressionTree exprTree) throws Exception
    {
        Encoder encoder = new Encoder();
        exprTree.Visit(encoder);
        
        return ExpressionTLV.Create(encoder.getBuffer(), encoder.getSize());
    }

    /** Decoder context */
    protected class Context {

        public OperatorID   id;
        public int          offset;
        public int          lim;
        public int[]        expr;

        public ArrayList<Operator> args;
        
        /** c'tor */
        public Context(int[] expr, int offset) throws DLException {

            this.args = new ArrayList<Operator>();
            this.expr   = expr;
            this.offset = offset;
            this.id = OperatorID.Create(expr[offset]);
            int size = expr[offset + 1];
            this.offset += 2;            
            this.lim = this.offset + size; 

            if (size < 0 || this.lim > expr.length) throw new DLException("Incorrect size");
        }
        
        /** Next operator */
        public Context Next() throws DLException {
            
            if (offset >= lim) return null;
            
            Context next = new Context(expr, offset);
            offset = next.lim;
            
            return next;
        }                
        
        /** Operator from context data */
        public Operator getOperator() throws Exception {
            
            return Operator.Create(id, args);
        }
    }
    
    /** Decode an expression */
    @Override public ExpressionTree Decode(IExpression expr) throws Exception
    {
        // Downcasting ...
        ExpressionTLV exprTLV = (ExpressionTLV) expr;
        
        int[] buffer = exprTLV.getExpr();        
        Stack<Context> stack = new Stack<Context>();
        Operator root = null;
        
        stack.push(new Context(buffer, 0));
        
        while(!stack.empty()) {
            
            Context cur = stack.peek();
            Context next = cur.Next();
            
            if (next != null) {
                
                stack.push(next);
            } else {

                
                Operator op = cur.getOperator();
                stack.pop();
                
                if (stack.empty()) {
                    
                    root = op;
                } else {
                    
                    Context parent = stack.peek();
                    parent.args.add(op);
                }
            }
        }
        
        return ExpressionTree.Create(root);
    }
    
    /** Factory method */
    public static IEncoder Create() {
        
        return new EncoderTLV();
    }
}
