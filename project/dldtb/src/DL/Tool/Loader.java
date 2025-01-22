
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

package DL.Tool;

import DL.Common.*;
import DL.Ontology.Toolkit.*;

import java.io.*;
import java.util.*;

/**
 * Toolkit class
 */
public class Loader {

    /** Command line options */
    private static final String OptInput  = "-i";    // Input file
    private static final String OptCreate = "-c";    // Create new database
    private static final String OptData   = "-d";    // Database file
    private static final String OptLog    = "-l";    // Log file
    private static final String OptHdr    = "-h";    // Header file

    // Get ontology name from ontology file name
    protected static String getName(String path) throws Exception {

        File file = new File(path);
        String name = file.getName();
        name = name.replaceAll("[:\\.-]", "_").toUpperCase();
        return name;
    }

    /**
     * main
     */
    public static void main(String args[]) {

        try {
            CmdArgList opts = new CmdArgList();

            opts.addOpt(OptInput);
            opts.addOpt(OptCreate);
            opts.addOpt(OptData);
            opts.addOpt(OptLog);
            opts.addOpt(OptHdr);

            opts.parse(args);

            boolean action = false;
            ArrayList<String> list = null;

            // Orphan parameters?
            list = opts.getArgs(opts.OptDefault);

            if (!list.isEmpty()) {

                throw new Exception("Invalid parameter: " + list.get(0));
            }

            // Get database name
            list = opts.getArgs(OptData);

            if (list == null || list.isEmpty()) throw new Exception("Store name is missing: -d <file name>");
            if (list.size() != 1) throw new Exception("Invalid store name");

            String store = list.get(0);

            // Create database?
            list = opts.getArgs(OptCreate);

            if (list != null) {

                if (list.size() != 1) throw new Exception("Invalid definition file name");
                String defs = list.get(0);

                System.out.println("Create store " + store + " with def file " + defs);
                Toolkit.CreateStore(store, defs);

                action = true;
            } 

            // Load definitions?
            list = opts.getArgs(OptInput);

            if (list != null) {

                if (list.isEmpty()) throw new Exception("Input file name missing: -i <file name>");

                for(String input : list) {
                    System.out.println("Process input file " + input);
                    Toolkit.LoadOntology(getName(input), input, store);
                }

                action = true;
            }

            // Create log file?
            list = opts.getArgs(OptLog);

            if (list != null) {

                if (list.size() != 1) throw new Exception("Invalid log file name: -l <file name>");

                String logs = list.get(0);
                System.out.println("Create log file " + logs);
                Toolkit.DumpStore(store, logs);

                action = true;
            }

            // Create header file?
            list = opts.getArgs(OptHdr);

            if (list != null) {

                if (list.size() != 1) throw new Exception("Invalid header file name: -h <file name>");

                String header = list.get(0);

                System.out.println("Create header file " + header);
                Toolkit.DumpDefs(store, header);

                action = true;
            }

            // Anything done?
            if (!action) {

                throw new Exception("No action performed on " + store);
            }
        }
        catch(Exception ex) {
            
            System.out.println(ex.getMessage());
        }
    }
}
