/*! 
\mainpage A Lightweight Description Logic Reasoner
 
 \section main_desc DLITE
 
 DLITE [dih-lahyt] is a set of C++ libraries aimed at easing the integration of description logic reasoning technology in applications.  
 
  \section main_usage Usage
 
 - \subpage man_overview

 \section main_license DLITE Licence
 
 \htmlonly
 <a href="http://www.gnu.org/licenses/gpl-3.0.html" target="_blank">
 <img src="images/gplv3.png" border=0/>
 </a>
 \endhtmlonly
 
 Copyright 2016 by zen.code.ai.

Permission to use, copy, modify, and distribute this software and its documentation under the terms of the GNU General Public License is hereby granted. No representations are made about the suitability of this software for any purpose. It is provided "as is" without express or implied warranty. See the <a href="http://www.gnu.org/licenses/gpl-3.0.html">GNU General Public License</a> for more details.
 
 \section main_version Current Version
 
 Current DLITE version is 0.1 pre-alpha. SVN tag 32.

 \section main_roadmap Current Functionalities and Future Work
 
 This early version of DLITE implements a basic ALC reasoner that allows satisfiability checks. 
 
 Future work will focus on improving the language expressivity and adding functionalities. The following describes the project's roadmap:
 
 - Subsumption trees and concept classification
 - Ontology consistency
 - GCI and GCI optimization
 - ABox reasoning
 - Improve expressivity
 - Concrete domains and complex data types.

\section  main_thirdparty Third Party Libraries and Tools
 
 The implementation of DLITE is based on the following open-source products:

 \htmlonly
 <p>ANTLR V3</p>
 <a href="http://www.antlr.org" target="_blank">
 <img src="images/ANTLR3.png" border=0/>
 </a>

 <p>SQLite</p>
 <a href="http://www.sqlite.org/index.html" target="_blank">
 <img src="images/sqlite.png" border=0/>
 </a>

  <p>Doxygen</p>
 <a href="http://www.doxygen.org" target="_blank">
 <img src="images/doxygen.png" border=0/>
 </a>

  <p>CMake</p>
 <a href="http://www.cmake.org/" target="_blank">
 <img src="images/cmake.png" border=0/>
 </a>
 
 <br>
 <br>
 <a href=" http://www.applied-mathematics.net/tools/xmlParser.html" target="_blank">
XML Parser
 </a>
 
 \endhtmlonly
  
 \page man_overview Overview
 
 \section  overview_dlite What is DLITE?

- DLITE is an easy way to add description logic (DL) reasoning capabilities to any application.
- DLITE is released as a set of C++ libraries and supporting tools.
- DLITE implements a Tableau-based reasoning algorithm.  
- DLITE implements its own ontology language, an easy way to specify the reasoner's rule set.

\section overview_ontologies What is an ontology?

- An ontology is the formal representation of a domain of knowledge.
- The main components of an ontology are:
 - Concepts that are the equivalent of classes in an object model.
 - Roles that describe relationships between concepts
- A concept can be atomic or composed
- Composed concepts are defined with roles and concepts combined using logic connectors. 
  
 \section overview_reasoner What is the purpose of a DL reasoner? 

- A description logic reasoner is basically a classifier.
- A description logic reasoner can be use to perform subsumption tests between concepts (TBox reasoning).  

\section overview_structure DLITE components

- DLITE provides its own ontology language.
- Ontologies are stored in ontology stores. 
- Ontologies are loaded in stores using the dltools API (see dltools/session.h) or the dlutil command line utility.
- DLITE can be invoked in few lines of code using its high level API.
- DLITE also provides a low level API.

\section overview_language DLITE ontology language

- DLITE implements its own ontology language.
- The DLITE langage offers a convenient way to write simple ontologies.
- The DLITE system can be easily extended to other ontology format. See dlparser/context.h and dlparser/context.cpp for an example of parser/store interface.

The following is an example of ontology that describes familly relationships:

\code

animal   = being & ~human;

human    = being & ~animal;

male     = animal & ~female & ~hermaphrodite;

female   = animal & ~male & ~hermaphrodite;

hermaphrodite = animal & ~male & ~female;

man      = human & ~woman;

woman    = human & ~man;

parent   = human & (?has_child/human | ?married_to/parent);

mother   = parent & woman;

father   = parent & man;

husband  = man & ?married_to/woman;

wife     = woman & ?married_to/man;

married  = human & ?married_to/human;

child    = human & ?has_parent/human;

son      = child & man;

daughter = child & woman;

grand_parent = human & ?has_child/parent;

grand_father = man & grand_parent;

grand_mother = woman & grand_parent;

\endcode

\section overview_store Ontology store

- A store can contain several ontologies
- A store is database that contains a symbol table and concept definition encoded as binary blobs.
- The DLITE high level API uses the symbol table to interpret reasoning queries written in the DLITE  langage syntax.
- The DLITE low level API uses directly the binary blobs. The symbol table is repesented as a list of C preprocessor macros 
- Ontologies can be loaded in stores using the dltools API (see iSession::Load in dltools/session.h)
- Ontologies can be loaded in stores using the dlutil command line tool

The following is an example of low-level symbol table:
 
 \code 
 
#ifndef __STORE__
#define __STORE__

// ................................................................................
// Ontologies

#define                                 O_family (0x01000001)

// ................................................................................
// Roles

#define                              R_has_child (0x08000014)
#define                             R_married_to (0x08000017)
#define                             R_has_parent (0x08000028)

// ................................................................................
// Concepts

#define                                  C_being (0x06000002)
#define                                  C_human (0x06000003) // ~animal&being
#define                                 C_animal (0x06000005) // ~human&being
#define                                 C_female (0x06000007) // ~hermaphrodite&~male&animal
#define                          C_hermaphrodite (0x06000009) // ~female&~male&animal
#define                                   C_male (0x0600000b) // ~hermaphrodite&~female&animal
#define                                  C_woman (0x06000010) // ~man&human
#define                                    C_man (0x06000012) // ~woman&human
#define                                 C_parent (0x06000016) // (?married_to/parent|?has_child/human)&human
#define                                 C_mother (0x0600001c) // woman&parent
#define                                 C_father (0x0600001e) // man&parent
#define                                C_husband (0x06000021) // ?married_to/woman&man
#define                                   C_wife (0x06000024) // ?married_to/man&woman
#define                                C_married (0x06000027) // ?married_to/human&human
#define                                  C_child (0x0600002b) // ?has_parent/human&human
#define                                    C_son (0x0600002d) // man&child
#define                               C_daughter (0x0600002f) // woman&child
#define                           C_grand_parent (0x06000032) // ?has_child/parent&human
#define                           C_grand_father (0x06000034) // grand_parent&man
#define                           C_grand_mother (0x06000036) // grand_parent&woman

#endif //__STORE__
 
 \endcode

 Ontologies can be loaded in stores in few lines of code:

\code

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

\endcode

\section overview_highlevel DLITE reasoner invocation using the high-level API

This is an example of reasoner invocation using the high-level API:

\code

// Create store session
spiSession spSession = iSession::Create("sample.db");

// Parse concept
sptExpression spExpr = iSession->Parse("father&~animal");

// Check concept satisfiability
bool fRes = iSession->Satisfiable(spExpr);

\endcode 

\section overview_lowlevel DLITE reasoner invocation using the low-level API

This is an example of reasoner invocation using the low-level API:

\code

// Create store object
spiStore sp = StoreFactorySQLite::Create("test.db");

// Open store
sp->Open();

// Create reasoner object
spiReasoner spReasoner = iReasoner::Create(sp);

// Build concept "grand_parent& ~animal"
tExprFactory oFact;
oFact.concept(C_grand_parent);
oFact.concept(OP_NEG(C_animal));
oFact.andop();
sptExpression spExpr = oFact.expr();

// Check concept satisfiablity
bool fRet = spReasoner->Satisfiable(spExpr);

\endcode 
  
 */
