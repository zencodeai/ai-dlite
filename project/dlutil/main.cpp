
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

// ............................................................................
// File    : main.cpp
// Author  : main
// Created : March 12, 2010, 9:49 PM
//
// Desc    : Cmd line util
//
// ............................................................................

#include "dlite.h"
#include "dltools.h"
#include "dlparser.h"
#include "session.h"

using namespace DLITE;

// Arcument list
class tArgList
{
public:

    // Option def
    struct tOption
    {
        int   nId;
        char* szCmd;
        char* szHelp;
    };

    // Index type
    typedef map<string, const tOption*> tIndex;

    // Args
    typedef list<string> tList;
    typedef map<int, tList> tArgs;

private:

    tIndex m_oIndex;    // Options def index
    tArgs  m_oArgs;     // Arguments lists
    string m_stReason;  // Reason for failure

protected:

    // Initialize
    void init(const tOption* i_pCmd, const size_t i_nCount)
    {
        for(size_t i = 0; i < i_nCount; i ++)
        {
            const tOption& sOpt = i_pCmd[i];
            m_oIndex[sOpt.szCmd] = &sOpt;
        }        
    }

    // Is it a command line option?
    bool isOpt(const string i_stOpt) const
        { return (!i_stOpt.empty()) && i_stOpt[0] == '-'; }

    // Get option id
    tArgs::iterator getOptId(const string i_stOpt)
    {
        int nId = -1;
        tArgs::iterator q = m_oArgs.end();
        tIndex::iterator p = m_oIndex.find(i_stOpt);
        if (p != m_oIndex.end())
        {
            nId = p->second->nId;
            q = m_oArgs.find(nId);
            if (q == m_oArgs.end())
            {
                q = (m_oArgs.insert(pair<int, tList>(nId, tList()))).first;
            }
        }

        return q;
    }
    
public:

    // c'tor
    tArgList(const tOption* i_pCmd, const size_t i_nCount)
    {
        init(i_pCmd, i_nCount);
    }

    // End of list
    tArgs::iterator end() { return m_oArgs.end(); }

    // Parse arg list
    bool parse(int argc, char** argv)
    {
        bool fSuccess = true;
        tArgs::iterator p = end();

        m_stReason.clear();

        for(int i = 1; i < argc && fSuccess; i ++)
        {
            string stArg = argv[i];

            if (isOpt(stArg))
            {
                p = getOptId(argv[i]);
                if (p == end())
                {
                    fSuccess = false;
                    m_stReason = string("Unknown option ") + stArg;
                }
            }
            else if (p == end())
            {
                fSuccess = false;
                m_stReason = string("Unknown argument ") + stArg;
            }
            else
            {
                p->second.push_back(stArg);
            }
        }

        return fSuccess;
    }

    // Has option?
    bool hasOpt(const int i_nId) const { return m_oArgs.find(i_nId) != m_oArgs.end(); }

    // Get option argguments
    const tList& getArgs(const int i_nId) { return m_oArgs[i_nId]; }

    // Get reason for failure
    const string& reason() const { return m_stReason; }
};

// Cmd param ids
enum
{
    arg_app_help,   // Check satifiability
    arg_dtb_create, // Create database
    arg_dtb_open,   // Open database
    arg_dtb_dump,   // Dump database
    arg_ont_load,   // Load ontology
    arg_exp_satisf, // Check satifiability
    arg_lim         // Arg count
};

// Cmd params definition
tArgList::tOption g_asOpt[] =
{
    { arg_app_help  , "-h", "-h                        : display help" },
    { arg_dtb_create, "-c", "-c <database pathname>    : create database" },
    { arg_dtb_open  , "-o", "-o <database pathname>    : open database" },
    { arg_dtb_dump  , "-d", "-d <dump file pathname>   : dump database" },
    { arg_ont_load  , "-l", "-l <source file pathname> : load ontology" },
    { arg_exp_satisf, "-s", "-s <expression>           : check expression satisfiability" }
};

// Display help
void help()
{
    cout << endl << "Command line options :" << endl << endl;

    for(int i = 0; i < arg_lim; i ++)
    {
        cout << g_asOpt[i].szHelp << endl;
    }

    cout << endl;
}

// Open database
spiSession cmdOpen(const tArgList::tList& i_oArgs)
{
    spiSession spSession;
    const char* pszErr = "Failed to open database ";

    try
    {
        if (i_oArgs.size() != 1)
        {
            cout << pszErr << " : Invalid number of args" << endl;
        }
        else
        {
            string stPath = i_oArgs.front();
            cout << "Open " << stPath << endl;
            spSession = iSession::Open(stPath);
        }
    }
    catch(exception& ex)
    {
        cout << pszErr << " : " << ex.what() << endl;
    }
    catch(...)
    {
        cout << pszErr << endl;
    }

    return spSession;
}

// Create database
spiSession cmdCreate(const tArgList::tList& i_oArgs)
{
    spiSession spSession;
    const char* pszErr = "Failed to create database ";

    try
    {
        if (i_oArgs.size() != 1)
        {
            cout << pszErr << " : Invalid number of args" << endl;
        }
        else
        {
            string stPath = i_oArgs.front();
            cout << "Create " << stPath << endl;
            spSession = iSession::Create(stPath);
        }
    }
    catch(exception& ex)
    {
        cout << pszErr << " : " << ex.what() << endl;
    }
    catch(...)
    {
        cout << pszErr << endl;
    }

    return spSession;
}

// Display errors
void dispErr(const list<string>& i_oErr)
{
    for(list<string>::const_iterator p = i_oErr.begin(); p != i_oErr.end(); p ++)
    {
        cout << *p << endl;
    }
}

// Load ontology
bool cmdLoad(const spiSession& i_spSession, const tArgList::tList& i_oArgs)
{
    bool fSuccess = false;
    const char* pszErr = "Failed to load ontology ";

    try
    {
        if (i_oArgs.size() != 2)
        {
            cout << pszErr << " : Invalid number of args" << endl;
        }
        else
        {
            tArgList::tList::const_iterator p = i_oArgs.begin();
            string stPath = *(p ++);
            string stName = *(p ++);
            cout << "Load " << stPath << " in " << stName << endl;
            if (!i_spSession->Load(stPath, stName))
            {
                cout << pszErr << " :" << endl << endl;

                dispErr(i_spSession->Errors());
            }
            else
            {
                fSuccess = true;
            }
        }
    }
    catch(exception& ex)
    {
        cout << pszErr << " : " << ex.what() << endl;
    }
    catch(...)
    {
        cout << pszErr << endl;
    }

    return fSuccess;
}

// Dump database
bool cmdDump(const spiSession& i_spSession, const tArgList::tList& i_oArgs)
{
    bool fSuccess = false;
    const char* pszErr = "Failed to dump database ";

    try
    {
        if (i_oArgs.size() != 1)
        {
            cout << pszErr << " : Invalid number of args" << endl;
        }
        else
        {
            string stPath = i_oArgs.front();
            cout << "Dump " << stPath << endl;
            i_spSession->Dump(stPath);

            fSuccess = true;
        }
    }
    catch(exception& ex)
    {
        cout << pszErr << " : " << ex.what() << endl;
    }
    catch(...)
    {
        cout << pszErr << endl;
    }

    return fSuccess;
}

// Check stisfiability
bool cmdSatisfiability(const spiSession& i_spSession, const tArgList::tList& i_oArgs)
{
    bool fSuccess = false;
    const char* pszErr = "Failed to check expression ";

    try
    {
        if (i_oArgs.size() != 1)
        {
            cout << pszErr << " : Invalid number of args" << endl;
        }
        else
        {
            string stExpr = i_oArgs.front();
            cout << "Check satisfiability of " << stExpr << endl;

            sptExpression spExpr = i_spSession->Parse(stExpr);
            if (spExpr.null())
            {
                cout << pszErr << " :" << endl << endl;

                dispErr(i_spSession->Errors());
            }
            else
            {
                if (i_spSession->Satisfiable(spExpr))
                {
                    cout << "-> Satifiable" << endl;
                }
                else
                {
                    cout << "-> Non satifiable" << endl;
                }

                fSuccess = true;
            }

            fSuccess = true;
        }
    }
    catch(exception& ex)
    {
        cout << pszErr << " : " << ex.what() << endl;
    }
    catch(...)
    {
        cout << pszErr << endl;
    }

    return fSuccess;
}

/*
 * 
 */
int main(int argc, char** argv) {

    _log_init("dlutil");

    try
    {
        tArgList oArgList(g_asOpt, arg_lim);

        do
        {
            spiSession spSession;

            // Empty command line?
            if (argc < 2)
            {
                help();
                break;
            }

            // Parse arg list
            if (!oArgList.parse(argc, argv))
            {
                cout << endl << oArgList.reason() << endl << endl;
                help();
                break;
            }

            // Help?
            if (oArgList.hasOpt(arg_app_help))
            {
                help();
                break;
            }

            // Open/create store
            bool fOpen   = oArgList.hasOpt(arg_dtb_open);
            bool fCreate = oArgList.hasOpt(arg_dtb_create);

            // No database?
            if (!fOpen && !fCreate)
            {
                cout << endl << "-c or -o option missing" << endl;
                help();
                break;
            }


            // Invalid command?
            if (fOpen && fCreate)
            {
                cout << endl << "-c and -o options are mutually exclusive" << endl;
                help();
                break;
            }

            // Open database
            if (fOpen)
            {
                spSession = cmdOpen(oArgList.getArgs(arg_dtb_open));
                if (spSession.null()) break;
            }

            // Create database
            if (fCreate)
            {
                spSession = cmdCreate(oArgList.getArgs(arg_dtb_create));
                if (spSession.null()) break;
            }

            // Load ontology?
            if (oArgList.hasOpt(arg_ont_load))
            {
                if (!cmdLoad(spSession, oArgList.getArgs(arg_ont_load))) break;
            }

            // Dump database?
            if (oArgList.hasOpt(arg_dtb_dump))
            {
                if (!cmdDump(spSession, oArgList.getArgs(arg_dtb_dump))) break;
            }

            // Check satisfiability?
            if (oArgList.hasOpt(arg_exp_satisf))
            {
                if (!cmdSatisfiability(spSession, oArgList.getArgs(arg_exp_satisf))) break;
            }
        }
        while(false);
    }
    catch(exception& ex)
    {
        cout << endl << "Error " << ex.what() << endl << endl;
    }
    catch(...)
    {
        cout << endl << "Internal error" << endl << endl;
    }

    return (EXIT_SUCCESS);
}
