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
 * ExpressionTLV.java
 * 
 * TLV encoded expression tree
 */

package DL.Ontology.Expression.TLV;

import java.io.*;

import DL.Ontology.Expression.*;

/**
 *
 * @author main
 */
public class ExpressionTLV implements IExpression {

    /** TLV encoded expression */
    private int[] expr;
    
    /** c'tor */
    protected ExpressionTLV(int[] expr, int size) {
        
        this.expr = new int[size];
        System.arraycopy(expr, 0, this.expr, 0, size);
    }
    
    /** c'tor */
    protected ExpressionTLV(int[] expr) {
        
        this.expr = expr;
    }

    /** Get expression buffer */
    int[] getExpr() { return expr; }
    
    /** Get encoded expression as binary blob */
    @Override public byte[] ToBinaryBlob() throws Exception
    {
        ByteArrayOutputStream astr = new ByteArrayOutputStream();
        DataOutputStream dstr = new DataOutputStream(astr);

        for(int n : expr) {
            
            dstr.writeInt(n);
        }
                
        return astr.toByteArray();
    }
    
    /** Factory method */
    public static IExpression Create(int[] expr, int size)
    {
        return new ExpressionTLV(expr, size);
    }

    /** Factory method */
    public static IExpression Create(int[] expr)
    {
        return new ExpressionTLV(expr);
    }
}

