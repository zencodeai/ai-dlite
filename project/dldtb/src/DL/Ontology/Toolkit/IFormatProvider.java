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
 * IFormatProvider.java
 * 
 * Ontology dump format provider
 */

package DL.Ontology.Toolkit;

import DL.Ontology.*;
import DL.Ontology.Expression.*;

/**
 * Format provider interface
 */
public interface IFormatProvider {

    // Start ontology dump
    void Begin(ISymbolTable table, String store, String desc) throws Exception;
    
    // Start symbol dump
    boolean Start(OperatorType type) throws Exception;

    // Entry
    void Entry(OperatorID id, Identifier ident) throws Exception;
    
    // Done
    void Done() throws Exception;
    
    // Terminate ontology dump
    void End() throws Exception;
}
