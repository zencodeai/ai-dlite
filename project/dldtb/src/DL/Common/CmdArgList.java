
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
 * CmdArgList.java
 *
 * Command line parameters parsing
 *
 */

package DL.Common;

import java.util.*;

/**
 * Comand line parameters class
 *
 */
public class CmdArgList {

    public static final String OptDefault  = "-@";    // Default option

    /**
     * Command line args class
     */
    protected class CmdArg
    {
        /** Command line option */
        private String opt;

        /** Option args */
        private ArrayList<String> args;

        /** c'tor */
        public CmdArg(String opt) {

            this.opt = opt;
            args = new ArrayList<String>();
        }

        /** Add arg to list */
        public void add(String arg) {

            this.args.add(arg);
        }

        /** Get arg list */
        public ArrayList<String> get() {

            return args;
        }
    }

    /** Arg list */
    private HashSet<String> opts;

    /** Command line args */
    private HashMap<String, CmdArg> args;

    /** Is this an option or an arg */
    protected boolean isOpt(String opt) throws Exception {

        boolean res = false;

        if (opt.startsWith("-")) {

            res = opts.contains(opt);
            if (!res) throw new Exception(opt + " is not a valid command line option");
        }

        return res;
    }

    /** Set option */
    protected CmdArg setOpt(String opt) {

        CmdArg arg = null;

        if (args.containsKey(opt)) {

            arg = args.get(opt);
        } else {

            arg = new CmdArg(opt);
            args.put(opt, arg);
        }

        return arg;
    }

    /** Get arglist for option */
    public ArrayList<String> getArgs(String opt) {

        ArrayList<String> params = null;

        if (args.containsKey(opt)) {

            params = args.get(opt).get();
        }

        return params;
    }

    /** c'tor */
    public CmdArgList() {

        opts = new HashSet<String>();
        args = new HashMap<String, CmdArg>();
    }

    /** Add an option name to the list */
    public void addOpt(String opt) {

        opts.add(opt);
    }

    /** Parse command line parameters */
    public void parse(String[] args) throws Exception {

        CmdArg cur = setOpt(OptDefault);

        for(String s : args) {

            if (isOpt(s)) {

                cur = setOpt(s);
            } else {

                cur.add(s);
            }
        }
    }
}
