
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
 * File:   main.cpp
 * Author: main
 *
 * Created on September 1, 2008, 7:43 PM
 */

#include "test.h"

#include "dlite.h"
#include "dltools.h"
#include "dlparser.h"
#include "session.h"

#include <iostream>

using namespace DLITE;

#if 0
#define _c(X) oFact.c(X)
#define _u(R,X) oFact.u(R,X)
#define _e(R,X) oFact.e(R,X)

void log(const char* i_pszFile, const int i_nLine)
{
    cout << "*** Test failed at " << i_pszFile << "," << i_nLine << endl;
}

#define TEST(X,R) { oFact = X; if (!test(i_spReasoner, oFact, (R))) { log(__FILE__, __LINE__); break;} }

bool test(spiReasoner& i_spReasoner, tExprFactory& i_oFact, const bool i_fExp)
{
    i_spReasoner->getABox()->Clear();
    return i_fExp == i_spReasoner->Satisfiable(i_oFact);
}

bool test_1(spiReasoner& i_spReasoner)
{
    bool fSuccess = false;
    tExprFactory oFact;

    do
    {
        TEST(_c(C_a) & _c(C_a), true);
        TEST(_c(C_a) & _c(C_b), true);
        TEST(_c(C_a) & _c(OP_NEG(C_b)), true);
        TEST(_c(C_a) & _c(OP_NEG(C_a)), false);
        TEST(_c(C_a) & _c(OP_NEG(C_b)), true);
        TEST(_c(C_a) & _c(C_b), true);
        TEST(_c(C_a) & _c(OP_NEG(C_a)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i), true);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_a)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_b)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_c)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_d)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_e)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_f)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_g)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_h)), false);
        TEST(_c(C_a) & _c(C_b) & _c(C_c) & _c(C_d) & _c(C_e) & _c(C_f) & _c(C_g) & _c(C_h) & _c(C_i) & _c(OP_NEG(C_i)), false);

        TEST((_c(C_a) | _c(C_b)) & _c(OP_NEG(C_a)) , true);
        TEST((_c(C_a) | _c(C_b)) & _c(OP_NEG(C_a)) & _c(OP_NEG(C_b)), false);
        TEST((_c(C_a) | _c(C_b) | _c(C_c)) & _c(OP_NEG(C_a)) & _c(OP_NEG(C_b)), true);
        TEST((_c(C_a) | _c(C_b)) & (_c(OP_NEG(C_c)) | _c(OP_NEG(C_d))) & (_c(C_y) | _c(C_z)) & _c(OP_NEG(C_y)) & _c(OP_NEG(C_z)), true);

        fSuccess = true;
    }
    while(false);
    
    return fSuccess;
}
#endif

class tFormatProvider
{
public:
    struct tContext
    {
        bool fRoot;
        list<string> oList;
        tOperator oOp;
    };
};



/*
 * 
 */
int main(int argc, char** argv) {
    

    string st;
    _log_init("Test");

    try
    {

        tName oName;
        oName.push_back("x");
        oName.push_back("y");
        oName.push_back("z");
        oName.push_back("t");
        _buffer<byte> buf;

        spiStore sp = StoreFactorySQLite::Create("test.db");
        sp->Open();
        spiReasoner spReasoner = iReasoner::Create(sp);
        spiSymTable spSymTable = iSymTable::Create(sp);
        spiExprFmtProvider spExprFmtProvider = tExprFmtProviderInfixFactory::Create(spSymTable);

        _log_store(sp);
        _log << "test : " << _log_name(C_x_b_c3) << endl;

        sp->Begin();
        _log << "UID : " << sp->NextUID() << endl;
        spSymTable->AddName(oName, OP_CONCEPT);
        operator_t newId = spSymTable->AddName(oName, OP_CONCEPT);
        sp->UpdateUID();
        sp->Commit();

        sp->Begin();
        _log << "UID : " << sp->NextUID() << endl;
        sp->UpdateUID();

        {
            spiTBox spTBox = iTBox::Create(sp);
            sptExpression spExpr = spTBox->GetDefinition(C_grand_parent);
            spTBox->AddDefinition(O_FAMILY_TXT, newId, spExpr);
            const _buffer<operator_t>& buff = spExpr->buffer();
            _log_dump(buff.ptr(), buff.size() * sizeof(operator_t));
            _log_expr(spExpr);
        }

        {
            spiTBox spTBox = iTBox::Create(sp);
            sptExpression spExpr = spTBox->GetDefinition(newId);
            const _buffer<operator_t>& buff = spExpr->buffer();
            _log_dump(buff.ptr(), buff.size() * sizeof(operator_t));
            _log_expr(spExpr);
        }

        sp->Rollback();

        sp->Begin();
        _log << "UID : " << sp->NextUID() << endl;
        sp->UpdateUID();
        sp->Rollback();

        sp->GetIdList(OP_CONCEPT);

        operator_t nOp = 0;
        while(0 != (nOp = sp->GetNextId()))
        {
            _log << hex << nOp << " : " << _log_name(nOp) << endl;
        }

        {
            spiTBox spTBox = iTBox::Create(sp);
            sp->GetDefinitionList(O_FAMILY_TXT);

            while(0 != (nOp = sp->GetNextDefinition()))
            {
                _log << hex << nOp << " : " << _log_name(nOp) << " : " << endl << endl;
                sptExpression spExpr = spTBox->GetDefinition(nOp);
                if (!spExpr.null())
                {
                    _log << spExprFmtProvider->toString(spExpr) << endl;
                    _log_expr(spExpr);
                    bool fRet = spReasoner->Satisfiable(spExpr);
                    _log << "Satisfiable : " << (int) fRet << endl;
                    spReasoner->Restore();


                }
                _log << endl;
            }
        }

        tExprFactory oFact;
        oFact.concept(C_grand_parent);
        oFact.concept(OP_NEG(C_animal));
        oFact.andop();
        sptExpression spExpr = oFact.expr();



        //sptExpression spExpr = tExprFactory::CreateExpConcept(C_grand_father, 0x00800000);
        
        _log_expr(spExpr);
        bool fRet = spReasoner->Satisfiable(spExpr);

        sp->Close();
        sp.clear();

        {
            tName oName(":a:b:_c1");
            _log << "--" << endl;
            for(tName::iterator p = oName.begin(); p != oName.end(); p ++)
            {
                _log << *p << endl;
            }
            _log << "--" << endl;
        }

        const char* pszDB = "p:\\test\\new.db";
        tFile::erase(pszDB);
        sp = StoreFactorySQLite::CreateNew(pszDB);
        sp->Open();

        sp->Begin();
        spiParser spParser = tDLParser::Create();
        if (!spParser->parse("p:\\test\\family.txt", "test", sp))
        {
            const list<string>& oErrors = spParser->errors();

            for(list<string>::const_iterator p = oErrors.begin(); p != oErrors.end(); p ++)
            {
                _log << *p << endl;
            }
        }


        sp->Commit();

        _log_store(sp);
        _log << "Parsed Expression" << endl;
        spExpr = spParser->parse("father&~animal", sp);
        _log_expr(spExpr);

        sp->Close();

        tFile::erase(pszDB);
        spiSession spSession = iSession::Create("p:\\test\\new.db");
        spSession->Load("p:\\test\\family.txt", "test");
        spSession->Dump("p:\\test\\new.h");
    }
    catch(exception& ex)
    {
        _log << ex.what() << endl;
    }
    catch(...)
    {
        _log << "Generic exception" << endl;
    }

    return (EXIT_SUCCESS);
}

