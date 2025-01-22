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
 * XMLReader.java
 *
 * XML document reader
 *
 */

package DL.DataStore;

import java.io.*;

import org.w3c.dom.*;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException; 

import DL.Common.*;

/**
 * Short description
 *
 * Long description.
 */
public class XMLReader {

    /** XML Document */
    private Document doc;

    /** Doc accessor */
    public Document getDoc() {
        
        return doc;
    }
    
    /** parse file */
    protected void parse(String file) throws DLException {
        
        try
        {
            doc = null;
            
            DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
            doc = docBuilder.parse (new File(file));
        }
        catch (SAXParseException ex) {
            
            throw new DLException("Parsing error"
                    + ", line " + ex.getLineNumber() 
                    + ", uri " + ex.getSystemId ()
                    + ", cause " + ex.getMessage ());
        }
        catch (SAXException ex) {
            
            throw new DLException(ex.getMessage());
        }
        catch (Exception ex) {
            
            throw new DLException(ex.getMessage());
        }
    }

    /** Get node */
    protected Node getNode(String name) throws DLException {
        
        NodeList nodes = doc.getElementsByTagName(name);
        if (nodes.getLength() == 0) throw new DLException("Node " + name + " not found");
        if (nodes.getLength() >  1) throw new DLException("Node " + name + " duplicated");
        
        return nodes.item(0);
    }
    
    /** Get node list */
    protected NodeList getNodes(String name) {
        
        return doc.getElementsByTagName(name);
    }
    
    /** Get attribute */
    protected String getAttr(Node node, String attr) throws DLException {
    
        Node o = node.getAttributes().getNamedItem(attr);
        if (o == null) throw new DLException("Attribute " + attr + "not found");
        
        return node.getAttributes().getNamedItem(attr).getNodeValue();
    }
    
    /** Get attribute as int value */
    protected int getAttInt(Node node, String attr) throws DLException {
        
        String s = getAttr(node, attr);
        return Integer.parseInt(s);
    }
    
    /** c'tor */
    protected XMLReader(String file) throws DLException {
        
        parse(file);
    }
}
