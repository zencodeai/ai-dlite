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
 * Parser.java
 * 
 * Ontology parser (compact notation)
 */

package DL.Ontology.Parser.Compact;

import DL.Ontology.*;
import DL.Ontology.Expression.*;
import DL.Ontology.Parser.*;

import java.io.*;

/**
 * Ontology parser (compact notation)
 */
public class Parser implements IParser {

    /** Parse ontology */
    @Override public void Parse(InputStream stream, IOntologyStore store, IEncoder encoder) throws Exception {
        
        // Create parser
        DLFilterALCLexer lexer = new DLFilterALCLexer(stream);
        OntologyParser parser = new OntologyParser(lexer);
        ParserContext context = ParserContext.Create(store.getSymbolTable(), encoder);
        parser.setContext(context);

        // Parse input stream
        parser.ontology();
    }

    /** Factory method */
    public static IParser Create() {
        
        return new Parser();
    }
}
