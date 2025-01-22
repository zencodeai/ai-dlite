
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

#include "sample.h"
 
#include "dlite.h"
#include "dltools.h"
#include "dlparser.h"
#include "session.h"

using namespace DLITE;

int main(int argc, char** argv) 
{
    try
    {
		const string stDB = "sample.db";
		if (tFile::exist(stDB))
		{
			cout << "Erase ontologies store" << endl;
	        tFile::erase(stDB);
		}
				
		cout << "Create new store" << endl;
        spiSession spSession = iSession::Create(stDB);

		cout << "Load ontology in store" << endl;
        if (!spSession->Load("family.txt", "family"))
		{
			cout << "Parsing errors : " << endl << endl;
            const list<string>& oErrors = spSession->Errors();

            for(list<string>::const_iterator p = oErrors.begin(); p != oErrors.end(); p ++)
            {
                cout << *p << endl;
            }
		}

		cout << "Dump store" << endl;
        spSession->Dump("sample.h");
    }
    catch(exception& ex)
    {
        cout << "Excpetion : " << ex.what() << endl;
    }
    catch(...)
    {
        cout << "Exception" << endl;
    }

    return (EXIT_SUCCESS);
}
