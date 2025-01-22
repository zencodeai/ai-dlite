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
 * ISymbolTable.java
 *
 * Symbol table interface
 */

package DL.Ontology;

import DL.Common.*;
import DL.Ontology.Expression.*;

/**
 * Symbol table interface
 */
public interface ISymbolTable {

    /** Get counter */
    int getCounter() throws Exception;
    
    /** Get operator id from identifier/type */
    OperatorID getID(Identifier indent, OperatorType type) throws Exception;

    /** Get identifier from operator id  */
    Identifier getIdent(OperatorID id) throws Exception;
    
    /** Set id definition */
    void setDefinition(OperatorID id, IExpression expr) throws Exception;

    /** Get id definition */
    IExpression getDefinition(OperatorID id, IExpressionFactory factory) throws Exception;
    
    /** Get new operator ID from type */
    OperatorID newOperatorID(OperatorType type) throws Exception;
    
    /** Query symbol list */
    void QuerySymList(OperatorType type) throws Exception;
    
    /** Next item */
    Pair<OperatorID, Identifier> Next() throws Exception;
}
