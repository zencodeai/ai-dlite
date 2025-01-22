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
import java.util.*;
import java.text.*;

import DL.Ontology.*;
import DL.Ontology.Expression.*;
import DL.Ontology.Expression.TLV.*;

/**
 * Text format provider class
 */
public class FormatProviderDef implements IFormatProvider {

    // Symbol table 
    private ISymbolTable table;
    
    // Data stream
    private PrintStream stream;
    
    // Expression factory
    private IExpressionFactory factory;
    
    /** Expression tree encoder */
    private IEncoder encoder;
    
    /** Prefix */
    private String prefix;

    /** Current date time */
    protected static String getDateTime() {

        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        Date date = new Date();
        return dateFormat.format(date);
    }
    
    /** Convert expression to string */
    protected static String Ident2String(String prefix, Identifier ident) {
        
        String s = prefix;
        
        for(String name : ident) {
            
            s += "_" + name;
        }
        
        return s;
    }
    
    // c'tor
    public FormatProviderDef(OutputStream stream) {
        
        this.stream = new PrintStream(stream);
        factory = ExpressionFactoryTLV.Create();
        encoder = EncoderTLV.Create();
    }
    
    // Start ontology dump
    @Override public void Begin(ISymbolTable table, String store, String desc) throws Exception {
        
        this.table = table;

        stream.println("/*");
        stream.println(" *");
        stream.println(" * " + store);
        stream.println(" *");
        stream.println(" * " + desc);
        stream.println(" *");
        stream.println(" * " + getDateTime());
        stream.println(" *");
        stream.println(" */");
        stream.println();

        stream.println("#ifndef __ONTOLOGY__");
        stream.println("#define __ONTOLOGY__");
        stream.println();
        
        stream.format("#define SYM_COUNTER ((unsigned long) %d)\n", table.getCounter());
    }
    
    // Start symbol dump
    @Override public boolean Start(OperatorType type) {
        
        boolean ret = true;
        
        if (type == OperatorType.Ontology) {
            
            stream.println("\n\n/* -------------------------------------------------------------------------- */");
            stream.println("/* -- Ontologies                                                              */\n");
            prefix = "O";
        } else if (type == OperatorType.Namespace) {
            
            ret = false;                        
        } else if (type == OperatorType.Role) {
            
            stream.println("\n\n/* -------------------------------------------------------------------------- */");
            stream.println("/* -- Roles                                                                   */\n");
            prefix = "R";
        } else if (type == OperatorType.Concept) {
            
            stream.println("\n\n/* -------------------------------------------------------------------------- */");
            stream.println("/* -- Concepts                                                                */\n");
            prefix = "C";
        } else {
            
            ret = false;
        }
        
        return ret;
    }

    // Entry
    @Override public void Entry(OperatorID id, Identifier ident) throws Exception {
        
        if (id.getOperatorType() == OperatorType.Concept) {

            stream.format("#define %-30s ((unsigned long) 0x%08X)", Ident2String(prefix, ident), id.toInt());

            IExpression expr = table.getDefinition(id, factory);
            if (null != expr) {
                
                ExpressionTree tree = encoder.Decode(expr);
                String sexpr = Toolkit.Exp2String(table, tree);

                stream.format(" /* %s */\n", sexpr);
            }
            else {
                
                stream.println();
            }
            
        } else {
            
            stream.format("#define %-30s ((unsigned long) 0x%08X)\n", Ident2String(prefix, ident), id.toInt());
        }
    }
    
    // Done
    @Override public void Done() {
        
    }
    
    // Terminate ontology dump
    @Override public void End() {
        
        stream.println();
        stream.println("#endif /*__ONTOLOGY__*/");
    }
    
    // Factory method
    public static IFormatProvider Create(OutputStream stream) {
        
        return new FormatProviderDef(stream);
    } 
}
