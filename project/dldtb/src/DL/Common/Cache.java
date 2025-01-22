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
 * Cache.java
 *
 * Caching
 *
 */

package DL.Common;

import java.util.*;

/**
 * Cache class
 *
 */
public class Cache<_Key, _Value> extends LinkedHashMap<_Key, _Value> {

    /** Capacity */
    private int capacity;

    /** Capacity accessor */
    public int getCapacity() {
        
        return capacity;
    }

    /** Remove eldest entry */
    protected boolean removeEldestEntry (Map.Entry<_Key, _Value> eldest) {
        
        return super.size() > capacity; 
    }
    
    /** Get value from key, return null if not in cache */
    public _Value value(_Key key) {
        
        _Value value = null;
        
        if (super.containsKey(key)) value = super.get(key);
        
        return value;
    }
    
    /** c'tor */
    public Cache(int capacity) {
     
        super((int) (capacity / 0.75f), 0.75f, true);
        this.capacity = capacity;
    }
    
    /** Factory methos */
    public static Cache<?, ?> Create(int capacity) {
        
        return new Cache(capacity);
    }
}

