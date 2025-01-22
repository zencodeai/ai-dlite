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
 * FilterALCContext.java
 *
 * Ontology parser context
 */

package DL.Ontology.Parser.Compact;

import DL.Ontology.*;
import DL.Ontology.Expression.*;

import DL.Ontology.Toolkit.*;

/**
 * Parser context class
 */
public class ParserContext {
    
    /** Name split regular expression */
    private final static String regExp = "\\.";
    
    /** Symbol table */
    private ISymbolTable table;
    
    /** Expression tree encoder */
    private IEncoder encoder;
    
    /** Expression builder */
    private ExpressionBuilder builder;
    
    /** Definition flag */
    OperatorID operator;
    
    /** Last error */
    Exception error;
    
    /** c'tor */
    protected ParserContext(ISymbolTable table, IEncoder encoder)
    {
        this.table   = table;
        this.encoder = encoder;
        
        builder = ExpressionBuilder.Create(table);
    }

    /** Start new concept definion */
    public void DefinitionNew()
    {
        builder.clear();
    }

    /** Terminate current concept definition */
    public boolean DefinitionEnd() 
    {
        boolean ret = true;
        
        try {
        
            ExpressionTree tree = builder.Expression();
            IExpression expr = encoder.Encode(tree);
            table.setDefinition(operator, expr);
            operator = null;
            
            //ExpressionTree tree1 = encoder.Decode(expr);
            //String s = Toolkit.Exp2String(table, tree1);
            //int i = 0;
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }
    
    /** New concept */
    public boolean NewConcept(String name)
    {
        boolean ret = true;
        
        try {
        
            Identifier id = Identifier.Create(name.split(regExp));

            if (operator == null) {

                operator = table.getID(id, OperatorType.Concept);            
            } else {

                builder.Concept(id);
            }
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** New role */
    public boolean NewRole(String name)
    {
        boolean ret = true;
        
        try {
        
            Identifier id = Identifier.Create(name.split(regExp));
            builder.Role(id);
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** Apply top operator */
    public boolean ApplyTop()
    {
        boolean ret = true;
        
        try {
        
            builder.Top();
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** Apply bottom operator */
    public boolean ApplyBottom()
    {
        boolean ret = true;
        
        try {
        
            builder.Bottom();
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** Apply complement operator */
    public boolean ApplyCmpl()
    {
        boolean ret = true;
        
        try {
        
            builder.Not();
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** Apply univ operator */
    public boolean ApplyUniv()
    {
        boolean ret = true;
        
        try {
        
            builder.Univ();
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** Apply exists operator */
    public boolean ApplyExist()
    {
        boolean ret = true;
        
        try {
        
            builder.Exist();
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** Apply conjunction operator */
    public boolean ApplyCnj()
    {
        boolean ret = true;
        
        try {
        
            builder.And();
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** Apply disjunction operator */
    public boolean ApplyDsj()
    {
        boolean ret = true;
        
        try {
        
            builder.Or();
        }
        catch(Exception ex) {
            
            this.error = ex;
            ret = false;
        }
        
        return ret;                
    }

    /** Factory method */
    public static ParserContext Create(ISymbolTable table, IEncoder encoder)
    {
        return new ParserContext(table, encoder);
    }
}
