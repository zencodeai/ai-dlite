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
 * Toolkit.java
 * 
 * Ontology handling utilities
 */

package DL.Ontology.Toolkit;

import DL.Common.*;
import DL.Ontology.*;
import DL.Ontology.Expression.*;
import DL.Ontology.Expression.TLV.*;
import DL.Ontology.Parser.*;
import DL.Ontology.Parser.Compact.*;
import DL.Ontology.StoreSQLite.*;

import java.io.*;
import java.util.*;

/**
 * Toolkit class
 */
public class Toolkit {

    /** Create store */
    public static void CreateStore(String storeFile, String initFile) throws Exception {
        
        // Create store
        File file = new File(storeFile);
        file.delete();
        OntologyStoreSQLite.Create(storeFile, initFile);
    }
    
    /** Load ontology in existing store */
    public static void LoadOntology(String ontologyName, String defFile, String storeFile) throws Exception {
        
        // Open definition file
        File file = new File(defFile);
        FileInputStream stream = new FileInputStream(file);
        
        // Open store
        IOntologyStore store = OntologyStoreSQLite.Create(storeFile);
        
        store.Open();
        store.OpenOntology(ontologyName);
        
        IParser parser = Parser.Create();
        IEncoder encoder = EncoderTLV.Create();
        parser.Parse(stream, store, encoder);
        
        store.CloseOntology();
        store.Close();
    }
    
    /** Expression visitor context */
    protected static class Tree2StringCtx implements ExpressionTree.IContext {

        /** Encoder context */
        protected class Context {

            public Operator op;
            public ArrayList<Operator> args;
            public ArrayList<String> list;
            
            /** c'tor */
            public Context(Operator op) {

                this.op = op;
                args = new ArrayList<Operator>();
                list = new ArrayList<String>();
                
                args.addAll(op);
            }

            // Identifier 
            public String Identifier2String(Identifier ident, OperatorID id) {
                
                String s;
                
                if (ident == null) {
                    
                    int n = id.toInt();
                    s = "#" + Integer.toHexString(n);                    
                } else {
                    
                    s = new String();
                    for(String st : ident) {
                        
                        if (!s.isEmpty()) s += ".";
                        s += st;
                    }
                }
                
                return s;
            }
            
            // List of converted string 2 string
            public String List2String(ArrayList<String> list, char op) {
                
                String s = new String();
                
                for(String st : list) {
                    
                    if (!s.isEmpty()) s += op;
                    s += st;
                }
                
                return s;
            }
            
            // Context to string
            public String toString(ISymbolTable table) throws Exception {
            
                String arg;
                OperatorID id = op.getID();
                OperatorType type = op.getID().getOperatorType();
        
                if (type == OperatorType.Concept) {

                    arg = Identifier2String(table.getIdent(id), id);
                }
                else if (type == OperatorType.ConceptNeg) {

                    arg = "~" + Identifier2String(table.getIdent(id), id);
                }
                else if (type == OperatorType.Role || type == OperatorType.RoleNeg) {

                    arg = Identifier2String(table.getIdent(id), id);
                }
                else if (type == OperatorType.Top) {

                    arg = "1";
                }
                else if (type == OperatorType.Bottom) {

                    arg = "0";
                }
                else if (type == OperatorType.Union) {

                    arg = List2String(list, '|');
                }
                else if (type == OperatorType.Inter) {

                    arg = List2String(list, '&');
                }
                else if (type == OperatorType.Univ) {

                    arg = "!" + list.get(0) + "/" + list.get(1);
                }
                else if (type == OperatorType.Exist) {

                    arg = "?" + list.get(0) + "/" + list.get(1);
                }
                else {
                    
                    arg = "?" + Integer.toHexString(id.toInt());
                }
                
                return arg;
            }
            
            // Enclose in parentheses
            public boolean Enclose(Operator arg) throws Exception {
                
                boolean enclose = false;
                
                OperatorType t1 = op.getType();
                OperatorType t2 = arg.getType();
                
                if (t2 == OperatorType.Inter || t2 == OperatorType.Union) {
                    
                    enclose = (t1 != t2 && t1 == OperatorType.Inter) 
                              || (t1 != OperatorType.Inter && t1 != OperatorType.Union);
                }
                
                return enclose;
            }
        }
        
        /** Symbol table */
        ISymbolTable table;
        
        /** Context stack */
        Stack<Context> stack = new Stack<Context>();
        
        /** */
        String expr;
        
        /** Enter node */
        @Override public boolean Enter(Operator op) throws Exception {
            
            stack.push(new Context(op));
            
            return true;
        }
        
        /** Leave node */
        @Override public void Leave() throws Exception {
         
            Context cur = stack.pop();
            
            if (stack.empty()) {

                expr = cur.toString(table);
            } else {
                
                Context sup = stack.peek();
                
                String s = cur.toString(table);
                if (sup.Enclose(cur.op))
                    s = "(" + s + ")";
                
                sup.list.add(s);
            }
        }
        
        /** c'tor */
        Tree2StringCtx(ISymbolTable table) {
            
            this.table = table;
        }
        
        /** Get expression */
        public String getExpr() { return expr; }
    }
    
    // Convert expression to string
    public static String Exp2String(ISymbolTable table, ExpressionTree expr) throws Exception {
        
        Tree2StringCtx ctx = new Tree2StringCtx(table);
        expr.Visit(ctx);
                
        return ctx.getExpr();
    }
    
    // Convert expression to string
    public static String Ident2String(Identifier ident) {
        
        String s = new String();
        
        for(String name : ident) {
            
            if (!s.isEmpty()) s += ".";
            s += name;
        }
        
        return s;
    }
    
    // Dump symbol type
    protected static void DumpType(OperatorType type, ISymbolTable table, IFormatProvider prov) throws Exception {
        
        if (prov.Start(type)) {
            
            table.QuerySymList(type);
            Pair<OperatorID, Identifier> entry = table.Next();
            
            while(entry != null) {
                
                prov.Entry(entry.getFirst(), entry.getSecond());
                entry = table.Next();
            }
            
            prov.Done();
        }
    }
    
    // Dump ontology
    public static void Dump(String storeFile, IOntologyStore store, IFormatProvider prov) throws Exception {

        store.Open();               
        
        // Begin
        ISymbolTable table = store.getSymbolTable();
        prov.Begin(table, storeFile, store.getDesc());
        
        // Dump ontologies
        DumpType(OperatorType.Ontology, table, prov);
        
        // Dump namespaces
        DumpType(OperatorType.Namespace, table, prov);

        // Dump roles
        DumpType(OperatorType.Role, table, prov);

        // Dump concepts
        DumpType(OperatorType.Concept, table, prov);
        
        // End
        prov.End();
        
        store.Close();
        
    }
    
    // Dump store
    public static void DumpStore(String storeFile, String dumpFile) throws Exception {
        
        IOntologyStore store = OntologyStoreSQLite.Create(storeFile);
        File file = new File(dumpFile);
        file.delete();
        OutputStream stream = new FileOutputStream(file);

        IFormatProvider prov = FormatProviderText.Create(stream);
        
        store.Open();
        Dump(storeFile, store, prov);
        store.Close();
        stream.close();
    }

    // Dump store
    public static void DumpDefs(String storeFile, String dumpFile) throws Exception {
        
        IOntologyStore store = OntologyStoreSQLite.Create(storeFile);
        File file = new File(dumpFile);
        file.delete();
        OutputStream stream = new FileOutputStream(file);

        IFormatProvider prov = FormatProviderDef.Create(stream);
        
        store.Open();
        Dump(storeFile, store, prov);
        store.Close();
        stream.close();
    }
}
