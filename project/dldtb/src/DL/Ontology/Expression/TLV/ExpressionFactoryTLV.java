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
 * ExpressionFactoryTLV.java
 * 
 * ExpressionTLV factory
 */

package DL.Ontology.Expression.TLV;

import java.io.*;

import DL.Ontology.Expression.*;

/**
 * ExpressionTLV factory
 */
public class ExpressionFactoryTLV implements IExpressionFactory {

    /** c'tor */
    protected ExpressionFactoryTLV() {}
    
    /** Instantiate expression from binary blob */
    @Override public IExpression Create(byte[] blob) throws Exception {
        
        // Read as array of int (4 bytes)
        int size = blob.length / 4;
        
        // Read blob content
        ByteArrayInputStream bstr = new ByteArrayInputStream(blob);
        DataInputStream dstr = new DataInputStream(bstr);
        
        int[] expr = new int[size];
        
        for(int i = 0; i < size; i ++) {
            
            expr[i] = dstr.readInt();
        }
        
        return ExpressionTLV.Create(expr);
    }
    
    /** Factory method */
    public static IExpressionFactory Create() {
        
        return new ExpressionFactoryTLV();
    }
}
