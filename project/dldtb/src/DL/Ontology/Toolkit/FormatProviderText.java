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
 * FormatProviderText.java
 * 
 * Dump ontology in text format
 */

package DL.Ontology.Toolkit;

import java.io.*;

import DL.Ontology.*;
import DL.Ontology.Expression.*;
import DL.Ontology.Expression.TLV.*;

/**
 * Text format provider class
 */
public class FormatProviderText implements IFormatProvider {

    // Symbol table 
    private ISymbolTable table;
    
    // Data stream
    private PrintStream stream;
    
    // Expression factory
    private IExpressionFactory factory;
    
    /** Expression tree encoder */
    private IEncoder encoder;
    
    // c'tor
    public FormatProviderText(OutputStream stream) {
        
        this.stream = new PrintStream(stream);
        factory = ExpressionFactoryTLV.Create();
        encoder = EncoderTLV.Create();
    }
    
    // Start ontology dump
    @Override public void Begin(ISymbolTable table, String store, String desc) {
        
        this.table = table;
    }
    
    // Start symbol dump
    @Override public boolean Start(OperatorType type) {
        
        stream.println("\n\n-----------------------------------------------------\n");
        
        if (type == OperatorType.Ontology) {
            
            stream.println("Ontologies\n");
        } else if (type == OperatorType.Namespace) {
            
            stream.println("Namespaces\n");            
        } else if (type == OperatorType.Role) {
            
            stream.println("Roles\n");            
        } else if (type == OperatorType.Concept) {
            
            stream.println("Concepts\n");            
        }
        
        return true;
    }

    // Entry
    @Override public void Entry(OperatorID id, Identifier ident) throws Exception {
        
        if (id.getOperatorType() == OperatorType.Concept) {

            stream.format("%30s : %08X", Toolkit.Ident2String(ident), id.toInt());

            IExpression expr = table.getDefinition(id, factory);
            if (null != expr) {
                
                ExpressionTree tree = encoder.Decode(expr);
                String sexpr = Toolkit.Exp2String(table, tree);

                stream.format(" : %s\n", sexpr);
            }
            else {
                
                stream.println();
            }
            
        } else {
            
            stream.format("%30s : %08X\n", Toolkit.Ident2String(ident), id.toInt());
        }
    }
    
    // Done
    @Override public void Done() {
        
    }
    
    // Terminate ontology dump
    @Override public void End() {
        
    }
    
    // Factory method
    public static IFormatProvider Create(OutputStream stream) {
        
        return new FormatProviderText(stream);
    } 
}
