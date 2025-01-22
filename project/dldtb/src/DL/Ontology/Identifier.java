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
 * Identifier.java
 *
 * Identifier class
 *
 */

package DL.Ontology;

import java.util.*;

/**
 * Concept/role identifier class
 *
 */
public class Identifier extends ArrayList<String> {

    /** Get identifier's name */
    public String getName() { 
        
        String name = "";
        
        if (!isEmpty()) {
            
            name = get(size() - 1);
        }
        
        return name;
    }
    
    /** Get identifier's namespace */
    public ArrayList<String> getNameSpace() {
        
        ArrayList<String> namespace = new ArrayList<String>(this);
        
        if (!namespace.isEmpty()) {
            
            namespace.remove(size() - 1);
        }

        return namespace;
    }

    /** c'tor */
    protected Identifier() {
    }

    /** c'tor */
    protected Identifier(ArrayList<String> list) {
        
        super.addAll(list);
    }

    /** c'tor */
    protected Identifier(String[] list) {
        
        for(String st : list)
            super.add(st);
    }
    
    /** Factory method */
    public static Identifier Create() { 
        
        return new Identifier(); 
    }

    /** Factory method */
    public static Identifier Create(ArrayList<String> list) { 
        
        return new Identifier(list); 
    }

    /** Factory method */
    public static Identifier Create(String[] list) { 
        
        return new Identifier(list); 
    }
}
