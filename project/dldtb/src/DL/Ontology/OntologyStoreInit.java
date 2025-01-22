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
 * OntologyStoreInit.java
 *
 * Description
 *
 */

package DL.Ontology;

import java.util.*;

import org.w3c.dom.*;

import DL.Common.*;
import DL.Ontology.Expression.*;
import DL.DataStore.*;

/**
 * Short description
 *
 * Long description.
 */
public class OntologyStoreInit extends XMLReader {
    
    /** Concept type */
    private final String typeConcept    = "concept";
    
    /** Role type */
    private final String typeRole       = "role";
    
    /** Individual type */
    private final String typeIndividual = "individual";
    
    /** Counter node name */
    private final String counterNode    = "counter";

    /** Value attribute name */
    private final String valueAttr      = "value";

    /** Description node name */
    private final String descriptionNode= "desc";

    /** Symbol node name */
    private final String symbolNode     = "symbol";

    /** Name attribute name */
    private final String nameAttr       = "name";

    /** Type attribute name */
    private final String typeAttr       = "type";

    /** Type attribute name */
    private final String indexAttr      = "index";
    
    /** Initial counter value */
    private int counter;
    
    /** Description */
    private String description;
    
    /** Mapping */
    private ArrayList< Pair<Identifier, Integer> > mapping;
    
    /** Create identifier */
    private Pair<Identifier, Integer> CreateIdentifier(String name, String typeName, int tagID) throws DLException {

        Identifier ident = Identifier.Create();
        
        String[] list = name.split("\\.");        
        
        for(String s : list) { ident.add(s); }
        
        int id = 0;
        
        if (typeName.compareTo(typeConcept) == 0) {
            id = OperatorType.Concept.Tag(tagID);
        }
        else if (typeName.compareTo(typeRole) == 0) {
            id = OperatorType.Role.Tag(tagID);
        }
        else if (typeName.compareTo(typeIndividual) == 0) {
            id = OperatorType.Individual.Tag(tagID);
        }
        else throw new DLException("Unknown symbol type " + typeName);
                
        return new Pair<Identifier, Integer>(ident, id);
    }
    
    /** Initialize object from file content */
    protected void initialize() throws DLException {
     
        // Get initial counter value
        counter = getAttInt(getNode(counterNode), valueAttr);
        
        // Get description
        description = getNode(descriptionNode).getTextContent();
        
        // Get list of symbols
        NodeList nodeList = getNodes(symbolNode);
        mapping = new ArrayList< Pair<Identifier, Integer> >();
        
        for(int i = 0; i < nodeList.getLength(); i ++) {
            
            Node node = nodeList.item(i);
            String name = getAttr(node, nameAttr);
            String type = getAttr(node, typeAttr);
            int id   = getAttInt(node, indexAttr);
            
            mapping.add(CreateIdentifier(name, type, id));
        }
    }
    
    /** c'tor */
    protected OntologyStoreInit(String file) throws DLException {
        
        super(file);
        initialize();
    }

    /** Factory method */
    public static OntologyStoreInit Create(String file) throws DLException {
        
        return new OntologyStoreInit(file); 
    }

    /** Counter accessor */
    public int getCounter() {
        return counter;
    }

    /** Description accessor */
    public String getDescription() {
        return description;
    }

    /** Mapping accessor */
    public ArrayList<Pair<Identifier, Integer>> getMapping() {
        return mapping;
    }
}
