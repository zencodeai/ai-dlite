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
 * IOntologyStore.java
 *
 * Ontology store interface definition 
 *
 */

package DL.Ontology;

import DL.DataStore.*;

/**
 * Converter data store interface definition
 * 
 */
public interface IOntologyStore extends IDataStore {
    
    /** Open an ontology for modifications */
    void OpenOntology(String ontology) throws Exception;
    
    /** Close an opened ontology (and commit changes) */
    void CloseOntology() throws Exception;
            
    /** Get symbol table interface */
    ISymbolTable getSymbolTable() throws Exception;
}
