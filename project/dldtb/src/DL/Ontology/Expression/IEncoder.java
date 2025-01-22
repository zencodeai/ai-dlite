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
 * IEncoder.java
 * 
 * Expression tree encoder interface
 */

package DL.Ontology.Expression;

import DL.Ontology.*;

/**
 * Expression tree encoder interface
 */
public interface IEncoder {

    /** Encode an expression tree */
    IExpression Encode(ExpressionTree exprTree) throws Exception;

    /** Decode an expression */
    ExpressionTree Decode(IExpression expr) throws Exception;
}
