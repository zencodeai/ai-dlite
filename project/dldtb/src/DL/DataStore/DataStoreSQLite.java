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
 * DataStoreSQLite.java
 *
 * IDataStore implementation for SQLite database
 *
 */

package DL.DataStore;

import SQLite.*;

/**
 * SQLite IDataStore implementation
 *
 */
public abstract class DataStoreSQLite implements IDataStore {

    /** Generic SQLite statement argument interface */
    protected interface IArg {
        
        void bind(Stmt stmt, int idx) throws SQLite.Exception;
    }
    
    /** IArg implementation for integer */
    protected class ArgInt implements IArg {
        
        /** Argument's value */
        private int value;
        
        /** Bind statement to value */
        @Override public void bind(Stmt stmt, int idx) throws SQLite.Exception { stmt.bind(idx, value); }
            
        /** c'tor*/
        public ArgInt(int value) { this.value = value; }
    }

    /** IArg implementation for string */
    protected class ArgString implements IArg {
        
        /** Argument's value */
        private String value;
        
        /** Bind statement to value */
        @Override public void bind(Stmt stmt, int idx) throws SQLite.Exception { stmt.bind(idx, value); }
            
        /** c'tor*/
        public ArgString(String value) { this.value = value; }
    }

    /** IArg implementation for blobs */
    protected class ArgBlob implements IArg {
        
        /** Argument's value */
        private byte[] value;
        
        /** Bind statement to value */
        @Override public void bind(Stmt stmt, int idx) throws SQLite.Exception { stmt.bind(idx, value); }
            
        /** c'tor*/
        public ArgBlob(byte[] value) { this.value = value; }
    }
    
    /** Int command argument */
    protected IArg arg(int    value) { return new ArgInt(value); }

    /** String command argument */
    protected IArg arg(String value) { return new ArgString(value); }

    /** Blob command argument */
    protected IArg arg(byte[] value) { return new ArgBlob(value); }

    /** Bind arguments to command object */
    protected void bind(Stmt stmt,  IArg ... args) throws SQLite.Exception {
        
        stmt.reset();        
        for(int i = 0; i < args.length; i ++) 
            args[i].bind(stmt, i+1);
    }
    
    /** Execute command, no result expected */
    protected void exec(Stmt stmt,  IArg ... args) throws SQLite.Exception {

        bind(stmt, args);
        while(stmt.step()) {}
    }

    /** Execute command, 1 value expected */
    protected Object exec1(Stmt stmt,  IArg ... args) throws SQLite.Exception {
        
        Object res = null;
        
        bind(stmt, args);
        if (stmt.step()) {
        
            res = stmt.column(0);
            while(stmt.step()) {}
        }
        
        return res;
    }

    /** Execute command with arguments */
    protected void exec(String cmd, Object ... args) throws SQLite.Exception {
        
        String fcmd = String.format(cmd, args);
        db.exec(fcmd, null);
    }
    
    /** Called on database openeing */
    protected void onOpen(SQLite.Database db) throws SQLite.Exception { }

    /** Called on database closing */
    protected void onClose(SQLite.Database db) throws SQLite.Exception { }
    
    /** SQLite database file pathname */
    private String dataFile;
    
    /** SQLite database object */
    protected SQLite.Database db = null;
    
    /** Open datab store session */
    @Override public void Open() throws SQLite.Exception {

        if (this.db == null) {
            
            SQLite.Database db = new SQLite.Database();
            db.open(dataFile, 0x0666);
            onOpen(db);
            this.db = db;
        }            
    }
    
    /** Close current data store session */
    @Override public void Close() throws SQLite.Exception {
        
        try {
            
            if (db != null) {
                onClose(db);
                db.close(); 
            }
        }
        finally {
            
            db = null;
        }
    }    
    
    /** c'tor */
    protected DataStoreSQLite(String dataFile) {
        
        this.dataFile = dataFile;        
    }
}
