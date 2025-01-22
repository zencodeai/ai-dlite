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
 * OntologyStoreSQLite.java
 *
 * Converter data store using SQLite
 *
 */

package DL.Ontology.StoreSQLite;

import DL.Ontology.*;
import java.io.*;
import java.nio.*;
import java.util.*;

import DL.Common.*;
import DL.DataStore.*;
import DL.Ontology.Expression.*;
import SQLite.*;

/**
 * SQLite converter data store class
 *
 * Long description.
 */
public class OntologyStoreSQLite extends DataStoreSQLite implements IOntologyStore, ISymbolTable {
    
    /** SQL Load ID counter */
    private final String stLoadCounter = "select counter from DataStore;";
    
    /** SQL load description */
    private final String stLoadDesc = "select info from DataStore;";

    /** SQL Update ID counter */
    private final String stStoreCounter = "update DataStore set counter = :a;";

    /** SQL Update data store description */
    private final String stUpdateHeader = "update DataStore set counter = :a, info = :b;";
    
    /** SQL Add symbol */
    private final String stAddSymbol = "insert into SymTable values (:a, :b, :c, :d);";
    
    /** SQL Get symbol tag */
    private final String stGetSymbolTag = "select tag from SymTable where nspace = :a and name = :b and type = :c;";

    /** Get symbol */
    private final String stGetSymbol = "select * from SymTable where tag = :a;";

    /** Get symbol list*/
    private final String stGetSymbolList = "select tag from SymTable where type = :a;";

    /** Add concept definition */
    private final String stAddDef = "insert into DefTable values (:a, :b, :c);";

    /** Delete concept definition */
    private final String stDelDef = "delete from DefTable where ontology = :a and tag = :b;";

    /** Get definition */
    private final String stGetDef = "select exp from DefTable where tag = :a;";
    
    /** Cache capacity */
    private final int CacheCapacity = 1024;

    /** Def cache capacity */
    private final int DefCacheCapacity = 128;
    
    /** Current ontology */
    private int ontology = 0;
    
    /** Counter for ID generation */
    private int counter = 1;
    
    /** Description */
    private String desc = "";

    /** Symbol cache */
    private Cache<Pair<Integer, String>, Integer> cacheIdent;

    /** ID cache */
    private Cache<Integer, Pair<Integer, String> > cacheID;

    /** Definition cache */
    private Cache<Integer, ByteBuffer> cacheDef;
    
    /** Load counter prepared statement */
    private Stmt stmtLoadCounter;

    /** SQL load description */
    private Stmt stmtLoadDesc;

    /** Store counter prepared statement */
    private Stmt stmtStoreCounter;

    /** SQL Update data store prepared statement */
    private Stmt stmtUpdateHeader;
    
    /** SQL Add symbol */
    private Stmt stmtAddSymbol;
    
    /** SQL Get symbol tag */
    private Stmt stmtGetSymbolTag;
    
    /** SQL Get symbol  */
    private Stmt stmtGetSymbol;

    /** SQL Get symbol list */
    private Stmt stmtGetSymbolList;

    /** Add definition */
    private Stmt stmtAddDef;
    
    /** Delete definition */
    private Stmt stmtDelDef;

    /** Get definition */
    private Stmt stmtGetDef;
    
    /** Called on database opening */
    @Override protected void onOpen(SQLite.Database db) throws SQLite.Exception { 
        
        stmtLoadCounter  = db.prepare(stLoadCounter);
        stmtLoadDesc     = db.prepare(stLoadDesc);
        stmtStoreCounter = db.prepare(stStoreCounter);        
        stmtUpdateHeader = db.prepare(stUpdateHeader);        
        stmtAddSymbol    = db.prepare(stAddSymbol);
        stmtGetSymbolTag = db.prepare(stGetSymbolTag);
        stmtGetSymbol    = db.prepare(stGetSymbol);
        stmtGetSymbolList= db.prepare(stGetSymbolList);
        stmtAddDef       = db.prepare(stAddDef);
        stmtDelDef       = db.prepare(stDelDef);        
        stmtGetDef       = db.prepare(stGetDef);        
    
        cacheIdent.clear();
    }

    /** Called on database closing */
    @Override protected void onClose(SQLite.Database db) { 

        stmtLoadCounter  = null;
        stmtLoadDesc     = null;
        stmtStoreCounter = null;
        stmtUpdateHeader = null;
        stmtAddSymbol    = null;
        stmtGetSymbolTag = null;
        stmtGetSymbol    = null;
        stmtAddDef       = null;
        stmtDelDef       = null;
        stmtGetDef       = null;
    }
    
    /** Load current counter value from the database */
    protected void loadCounter() throws SQLite.Exception, java.lang.Exception {
        
        counter = ((Long) exec1(stmtLoadCounter)).intValue();
    }

    /** Load current description value from the database */
    protected void loadDesc() throws SQLite.Exception, java.lang.Exception {
        
        desc = (String) exec1(stmtLoadDesc);
    }
    
    /** Store counter */
    protected void storeCounter() throws SQLite.Exception, java.lang.Exception {
        
        exec(stmtStoreCounter, arg(counter));
    }

    /** New ID */
    protected int newID() { return counter ++; }
    
    /** Load current counter value from the database */
    protected void updateHeader(int counter, String desc) throws SQLite.Exception, java.lang.Exception {
                
        exec(stmtUpdateHeader, arg(counter), arg(desc));
    }

    /** Query value from cache */
    protected int queryCache(int namespace, String name, OperatorType type) {
        
        Pair<Integer, String> pair = new Pair<Integer, String>(namespace, name + "." + type.toString());
        Integer id = cacheIdent.get(pair);
        
        return (null == id) ? 0 : id;
    }
    
    /** Update cache */
    protected void updateCache(int namespace, String name, OperatorType type, int id) {
        
        Pair<Integer, String> pair = new Pair<Integer, String>(namespace, name + "." + type.toString());
        cacheIdent.put(pair, id);
    }
    
    /** Get symbol id. 0 if new */
    protected int querySymbolID(int namespace, String name, OperatorType type) throws SQLite.Exception {
        
        int id = queryCache(namespace, name, type);
        
        if (0 == id) {
            
            Object res = exec1(stmtGetSymbolTag, arg(namespace), arg(name), arg(type.TagID()));

            if (null != res) {

                id = ((Long) res).intValue();
            }
        }
        
        return id;
    }
    
    /** Add new symbol */
    protected void addSymbol(int namespace, String name, OperatorType type, int id) throws SQLite.Exception {

        exec(stmtAddSymbol, arg(namespace), arg(name), arg(type.TagID()), arg(id));
        updateCache(namespace, name, type, id);
    }

    /** Get symbol id. Create if new */
    protected int getSymbolID(int namespace, String name, OperatorType type) throws SQLite.Exception {
        
        int id = querySymbolID(namespace, name, type);
        
        if (0 == id) {
            
            id = type.Tag(newID());
            addSymbol(namespace, name, type, id);
        }
        
        return id;
    }
    
    /** Encode namespace */
    protected int getNamespaceID(ArrayList<String> namespace) throws java.lang.Exception {
        
        int id = OperatorType.Namespace.TagID();
        
        for(String name : namespace) {
            
            id = getSymbolID(id, name, OperatorType.Namespace);
        }
        
        return id;
    }
    
    /** Open an ontology for modifications */
    @Override public void OpenOntology(String ontology) throws java.lang.Exception {
        
        CloseOntology();
        
        exec("begin transaction;");
        loadCounter();
        
        this.ontology = getSymbolID(0, ontology, OperatorType.Ontology);
    }
    
    /** Close an opened ontology (and commit changes) */
    @Override public void CloseOntology() throws java.lang.Exception {
        
        try {
                
            if (0 != ontology ) {
                
                storeCounter();
                exec("commit transaction;");
            }
        }
        finally {
            
            ontology = 0;
        }
    }
    
    /** Get store description */
    @Override public String getDesc() throws java.lang.Exception {
        
        if (desc.isEmpty()) loadDesc();
        return desc;
    }
    
    /** Get symbol table interface */
    @Override public ISymbolTable getSymbolTable() {
        
        return (ISymbolTable) this;
    }

    /** Get counter */
    @Override public int getCounter() throws java.lang.Exception {
        
        loadCounter();
        return counter;
    }
    
    /** Get operator id from identifier/type */
    @Override public OperatorID getID(Identifier ident, OperatorType type) throws java.lang.Exception {
        
        int ns = getNamespaceID(ident.getNameSpace());
        int id = getSymbolID(ns, ident.getName(), type);
        
        return OperatorID.Create(id);
    }

    /** Get new operator ID from type */
    @Override public OperatorID newOperatorID(OperatorType type) throws DLException {
        
        return OperatorID.Create(type,newID());
    }
    
    /** Get identifier from operator id  */
    @Override public Identifier getIdent(OperatorID id) throws DLException, SQLite.Exception, java.lang.Exception {
        
        Identifier ident = Identifier.Create();
        
        int next = id.Abs().toInt();
        
        while(0 != next && OperatorType.Namespace.TagID() != next) {
            
            if (cacheID.containsKey(next)) {
                
                Pair<Integer, String> pair = cacheID.get(next);
                ident.add(0, pair.getSecond());
                next = pair.getFirst();
            } else {
                
                bind(stmtGetSymbol, arg(next));
                if (stmtGetSymbol.step()) {
                    
                    Long   lns = (Long)   stmtGetSymbol.column(0);
                    String sym = (String) stmtGetSymbol.column(1);
                    
                    while(stmtGetSymbol.step()) {}
                    
                    cacheID.put(next, new Pair(lns.intValue(), sym));
                    ident.add(0, sym);
                    next = lns.intValue();                    
                } else {
                    if (!ident.isEmpty()) ident.add(0, "#" + Integer.toHexString(next));
                    next = 0;
                }
            }            
        }
        
        return ident;
    }
    
    /** Set id definition */
    @Override public void setDefinition(OperatorID id, IExpression expr) throws DLException, SQLite.Exception, java.lang.Exception {
        
        byte[] blob = expr.ToBinaryBlob();
        
        exec(stmtDelDef, arg(ontology), arg(id.toInt()));
        exec(stmtAddDef, arg(ontology), arg(id.toInt()), arg(blob));
        ByteBuffer data = ByteBuffer.wrap(blob);
        cacheDef.put(id.getID(), data);        
    }

    /** Get id definition */
    @Override public IExpression getDefinition(OperatorID id, IExpressionFactory factory) throws DLException, SQLite.Exception, java.lang.Exception {

        IExpression expr = null;
        byte[] blob = null;
        int op = id.Abs().toInt();
        
        if (cacheDef.containsKey(op)) {
            
            blob = cacheDef.get(op).array();
        } else {
            
            Object res = exec1(stmtGetDef, arg(op));
            if (null != res) {

                blob = (byte[]) res;
                ByteBuffer data = ByteBuffer.wrap(blob);
                cacheDef.put(op, data);                        
            }
        }
        
        if (null != blob) expr = factory.Create(blob);
        
        return expr;
    }
    
    /** Query symbol list */
    @Override public void QuerySymList(OperatorType type) throws DLException, SQLite.Exception, java.lang.Exception  {
        
        bind(stmtGetSymbolList, arg(type.TagID()));
    }
    
    /** Next item */
    @Override public Pair<OperatorID, Identifier> Next() throws DLException, SQLite.Exception, java.lang.Exception  {

        Pair<OperatorID, Identifier> next = null;
        
        if (stmtGetSymbolList.step()) {
        
            Long val = (Long) stmtGetSymbolList.column(0);
            int op = val.intValue();
            OperatorID id = OperatorID.Create(op);
            Identifier ident = getIdent(id);
            
            next = new Pair<OperatorID, Identifier>(id, ident);
        }
        
        return next;
    }
    
    /** c'tor */
    protected OntologyStoreSQLite(String dataFile) {
        
        super(dataFile);
        cacheIdent = new Cache<Pair<Integer, String>, Integer>(CacheCapacity); 
        cacheID    = new Cache<Integer, Pair<Integer, String> >(CacheCapacity); 
        cacheDef   = new Cache<Integer, ByteBuffer >(DefCacheCapacity);
    }

    /** Initialize data store */
    protected void Initialize(String name) throws DLException, SQLite.Exception, java.lang.Exception {
        
        OntologyStoreInit init = OntologyStoreInit.Create(name);
        
        Open();
        
        try {
            
            exec("begin transaction;");
            
            updateHeader(init.getCounter(), init.getDescription());
            
            ArrayList< Pair< Identifier, Integer> > list = init.getMapping();
            
            for(Pair< Identifier, Integer> pair : list) {
                
                Identifier ident = pair.getFirst();
                OperatorID id = OperatorID.Create(pair.getSecond());
                int ns = getNamespaceID(ident.getNameSpace());        

                addSymbol(ns, ident.getName(), id.getOperatorType(), id.toInt());            
            }
            
            exec("commit transaction;");
            Close();
        }
        catch(java.lang.Exception ex) {
            
            Close();
            throw ex;
        } 
    }
    
    /** Factory method */
    public static IOntologyStore Create(String name, String init) throws SQLite.Exception, java.lang.Exception {

        File file = new File(name);
        boolean initialize = !file.exists();
        OntologyStoreSQLite dataStore = (OntologyStoreSQLite) Create(name);
        
        try {

            if (initialize) dataStore.Initialize(init);
        }
        catch(java.lang.Exception ex) {

            file.delete();
            throw ex;
        }
        
        return dataStore;
    }
    
    /** Factory method */
    public static IOntologyStore Create(String name) throws SQLite.Exception, java.lang.Exception {

        File file = new File(name);
        
        // File exists?
        if (!file.exists()) {
            
            // Create new database
            Database db = new SQLite.Database();
	    db.open(name, 0666);
            
            try {
                    
                db.exec("create table SymTable(nspace integer, name varchar(256), type integer, tag integer, primary key(nspace, name, type), unique(tag));", null);
                db.exec("create table DefTable(ontology integer, tag integer, exp blob, primary key(ontology, tag));", null);
                db.exec("create table DataStore(counter integer, info text);", null);
                db.exec("insert into DataStore values (0,'');", null);
            }
            catch(java.lang.Exception ex) {
            
                db.close();
                file.delete();
                throw ex;
            }
            
            db.close();
        }
        
        return new OntologyStoreSQLite(name);
    }
}
