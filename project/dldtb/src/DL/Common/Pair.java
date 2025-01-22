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
 * Pair.java
 *
 * Pair of values
 *
 */

package DL.Common;

/**
 * Pair of values
 */
public class Pair< T1, T2> {
    
    /** First value */
    private T1 first;
    
    /** Second value */
    private T2 second;
    
    /** c'tor */
    public Pair(T1 first, T2 second) {
        
        this.first = first;
        this.second = second;
    }

    /** first accessor */
    public T1 getFirst() {
        return first;
    }

    /** Second accessor */
    public T2 getSecond() {
        return second;
    }
    
    /** Equals implementation */
    public boolean equals(Object anObject) {

        Pair<?,?> pair = (Pair<?,?>) anObject; 
        
        return first.equals( pair.getFirst()) && second.equals( pair.getSecond());
    }
    
    /** Hashcode implementation */
    public int hashCode() {
        
        return (31 * first.hashCode()) ^ second.hashCode();
    }
}
