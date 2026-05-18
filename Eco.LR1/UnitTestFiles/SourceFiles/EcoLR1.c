/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   EcoLR1
 * </summary>
 *
 * <description>
 *   This source file is the entry point
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLR1.h"
#include "IdEcoLog1.h"
#include "IEcoLog1FileAffiliate.h"
#include "IdEcoFSM1.h"
#include "IdEcoPDA1.h"
#include "IdEcoString1.h"
#include "IdEcoList1.h"
#include "IdEcoData1.h"
#include "IdEcoStack1.h"
#include "IdEcoDictionary1.h"
#include "IdEcoBNF1.h"
#include "IdEcoDateTime1.h"
#include "IdEcoMap2.h"
#include "IdEcoSet2.h"
#include "IdEcoComparator1.h"
#include "IEcoContainer1.h"
#include "IdEcoQueue1.h"

bool_t OutputDiagnosticInfoOfBNF(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoBNF1* pGrammar);
bool_t OutputDiagnosticInfoOfParser(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoParser1LRk* pILRk);
bool_t OutputDiagnosticInfoOfFSM(IEcoLog1* pILog, IEcoString1* pIStr, IEcoParser1LRk* pILRk);

IEcoBNF1* GetTestBNF(/* in */ IEcoBNF1* pIBNF);
IEcoBNF1* GetTestBNF2(/* in */ IEcoBNF1* pIBNF);
IEcoBNF1* GetTestLR0_1(/* in */ IEcoBNF1* pIBNF);
IEcoBNF1* GetTestLR0_2(/* in */ IEcoBNF1* pIBNF);
IEcoBNF1* GetTestC(/* in */ IEcoBNF1* pIBNF);
IEcoBNF1* GetFullTestC(/* in */ IEcoBNF1* pIBNF);
IEcoBNF1* GetTestIDL(/* in */ IEcoBNF1* pIBNF);
IEcoBNF1* GetTestIDL2(/* in */ IEcoBNF1* pIBNF);

bool_t testLR0_1(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);
bool_t testLR0_2(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);
bool_t testFailLR1_as_LR0(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);
bool_t testLR1_1(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);
bool_t testLR1_2(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);
bool_t testC(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);
bool_t testFullC(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);
bool_t testIDL(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);
bool_t testIDL2(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk);

/*
 *
 * <summary>
 *   EcoMain Function
 * </summary>
 *
 * <description>
 *   EcoMain function - entry point
 * </description>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoString1* pIStr = 0;
    IEcoLog1* pILog = 0;
    IEcoLog1FileAffiliate* pIFileAffiliate = 0;
    IEcoBNF1* pIBNF = 0;
    IEcoParser1LRk* pILRk = 0;

    /* System interface check and creation */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
            goto Release;
        }
    }

    /* Getting the interface for working with the interface bus */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        goto Release;
    }

#ifdef ECO_LIB
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLR1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_F4561FD215A34CC5BA1D8791A441A18E);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoDictionary1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_2912A7C7E0B84B4D9BFE9500EF4667D3);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoFSM1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5E7C610CB846447DB59A3C5A2C4F446F);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoPDA1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_A03120BB3AF5425EBDE0A5535B423579);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoString1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_84CC0A7DBABD44EEBE749C9A8312D37E);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLog1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_97322B6765B74342BBCE38798A0B40B5);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoDateTime1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5B2BA17BEA704527BC708F88568FE115);
    if (result != 0) goto Release;
   
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoStack1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_18129B1DCF9248D9A7787F9206E2D6DC);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoData1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5A0F0DD57E6448EC9EE0E5D67572B47E);
    if (result != 0 ) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBNF1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_323DD55E33D040FA98068E2FCB1CBD49);
    if (result != 0 ) goto Release;
   
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMap2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_715AF131CD174E90AAF3B753221B9B73);
    if (result != 0) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoSet2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_58CDC2713209420CAC919BE1E16F4CA4);
    if (result != 0) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoComparator1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_44CE56A815DF433EB567D8943DA32D8E);
    if (result != 0) goto Release;
    
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoQueue1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_25D72F83A2564F4E9F59E489BE85E2A4);
    if (result != 0) goto Release;
#endif
   
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) goto Release;
    
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLR1, 0, &IID_IEcoParser1LRk, (void**) &pILRk);
    if (result != 0 || pILRk == 0) goto Release;
    
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1, (void**) &pILog);
    if (result != 0 || pILog == 0) goto Release;
   
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**) &pIStr);
    if (result != 0 || pIStr == 0) goto Release;
    
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1FileAffiliate, (void**) &pIFileAffiliate);
    if (result != 0 || pIFileAffiliate == 0) goto Release;
   
    pILog->pVTbl->AddAffiliate(pILog, (IEcoLog1Affiliate*)pIFileAffiliate);
    pIFileAffiliate->pVTbl->Release(pIFileAffiliate);

    pILog->pVTbl->Info(pILog, "Start Testing LR Parser Algorithms");
    
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBNF1, 0, &IID_IEcoBNF1, (void**) &pIBNF);
    if (result != 0 || pIBNF == 0) goto Release;
    
    /* Выполнение тестов */
    //testLR0_1(pILog, pIStr, pIMem, pIBNF, pILRk);
    //testLR0_2(pILog, pIStr, pIMem, pIBNF, pILRk);
    //testFailLR1_as_LR0(pILog, pIStr, pIMem, pIBNF, pILRk);
    //testLR1_1(pILog, pIStr, pIMem, pIBNF, pILRk);
    //testLR1_2(pILog, pIStr, pIMem, pIBNF, pILRk);
    //testC(pILog, pIStr, pIMem, pIBNF, pILRk);
	//testFullC(pILog, pIStr, pIMem, pIBNF, pILRk);
    //testIDL(pILog, pIStr, pIMem, pIBNF, pILRk);
    testIDL2(pILog, pIStr, pIMem, pIBNF, pILRk);

    pILog->pVTbl->Info(pILog, "End Testing LR Parser Algorithms");

Release:
    if (pIBus != 0) pIBus->pVTbl->Release(pIBus);
    if (pIMem != 0) pIMem->pVTbl->Release(pIMem);
    if (pILRk != 0) pILRk->pVTbl->Release(pILRk);
    if (pISys != 0) pISys->pVTbl->Release(pISys);
    return result;
}

IEcoBNF1* GetTestBNF(IEcoBNF1* pIBNF) {
    IEcoBNF1Rule* pIRule = 0;
    IEcoBNF1Element* pIElement = 0;
    uint32_t indexSet = 0;
    
    /* H ::= S */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "H");
    indexSet = 0;
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "S");
    
    /* S ::= L = R | R */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "S");
    indexSet = 0;
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "L");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "=");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "R");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "R");
    
    /* L ::= * R | i */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "L");
    indexSet = 0;
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "R");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "i");
    
    /* R ::= L */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "R");
    indexSet = 0;
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "L"); 
    
    return pIBNF;
}
   
IEcoBNF1* GetTestBNF2(IEcoBNF1* pIBNF) {
    IEcoBNF1Rule* pIRule = 0;
    IEcoBNF1Element* pIElement = 0;
    uint32_t indexSet = 0;

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "assign");
    indexSet = 0;
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "target");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_TERMINAL, "=");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "value");
   
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "target");
    indexSet = 0;
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_TERMINAL, "*");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "target");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_TERMINAL, "id");
   
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "value");
    indexSet = 0;
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "target");
    
    return pIBNF;
}

IEcoBNF1* GetTestLR0_1(IEcoBNF1* pIBNF) {
    IEcoBNF1Rule* pIRule = 0;
    uint32_t iSet = 0;
    
    /* S -> a A b */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "S"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "a");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "A");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "b");

    /* A -> c */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "A"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "c");
    
    return pIBNF;
}

IEcoBNF1* GetTestLR0_2(IEcoBNF1* pIBNF) {
    IEcoBNF1Rule* pIRule = 0;
    uint32_t iSet = 0;

    /* S -> A B */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "S"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "A");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "B");

    /* A -> a */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "A"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "a");

    /* B -> b */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "B"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "b");

    return pIBNF;
}

IEcoBNF1* GetTestC(IEcoBNF1* pIBNF) {
    IEcoBNF1Rule* pIRule = 0;
    uint32_t iSet = 0;

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "func");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "stmts");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "}");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "int");
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "void");
   
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "stmts"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "stmt");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "stmts");
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "stmt");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "stmt"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "return");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");
    
    return pIBNF;
}

/* Вспомогательная функция для создания опциональных правил (Flattening) */
static void CreateOptRule(IEcoBNF1* pIBNF, char_t* optName, char_t* contentName) {
    IEcoBNF1Rule* pIRule = pIBNF->pVTbl->AddRule(pIBNF, optName);
    uint32_t indexSet = 0;

    if (contentName != 0) {
        pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, contentName);
    }
    indexSet = 0;

    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0); 
}

IEcoBNF1* GetFullTestC(IEcoBNF1* pIBNF) {
    IEcoBNF1Rule *pIRule = 0;
    uint32_t indexSet = 0;

    CreateOptRule(pIBNF, "opt-argument-expression-list", "argument-expression-list");
    CreateOptRule(pIBNF, "opt-init-declarator-list", "init-declarator-list");
    CreateOptRule(pIBNF, "opt-declaration-list", "declaration-list");
    CreateOptRule(pIBNF, "opt-statement-list", "statement-list");
    CreateOptRule(pIBNF, "opt-expression", "expression");
    CreateOptRule(pIBNF, "opt-constant-expression", "constant-expression");
    CreateOptRule(pIBNF, "opt-identifier-list", "identifier-list");
    CreateOptRule(pIBNF, "opt-parameter-type-list", "parameter-type-list");
    CreateOptRule(pIBNF, "opt-abstract-declarator", "abstract-declarator");
    CreateOptRule(pIBNF, "opt-type-qualifier-list", "type-qualifier-list");
    CreateOptRule(pIBNF, "opt-pointer", "pointer");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "opt-identifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "opt-base-interface");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0);

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "c0-begin-state");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "translation-unit");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "primary-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "constant");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "string-literal");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "postfix-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "primary-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "]");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-argument-expression-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ".");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "->");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "++");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "--");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "argument-expression-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "argument-expression-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "unary-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "++");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "--");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "unary-operator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "sizeof");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "sizeof");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "type-name");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "unary-operator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "&");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "+");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "-");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "~");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "!");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "cast-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "type-name");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "multiplicative-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "cast-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "/");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "%");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "additive-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "additive-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "+");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "additive-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "-");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "shift-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "additive-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "<<");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "additive-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ">>");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "additive-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "relational-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "<");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ">");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "<=");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ">=");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "shift-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "equality-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "equality-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "==");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "equality-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "!=");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "relational-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "AND-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "equality-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "AND-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "&");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "equality-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "exclusive-OR-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "AND-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "exclusive-OR-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "^");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "AND-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "inclusive-OR-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "exclusive-OR-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "inclusive-OR-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "|");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "exclusive-OR-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "logical-AND-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "inclusive-OR-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-AND-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "&&");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "inclusive-OR-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "logical-OR-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-AND-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-OR-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "||");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "logical-AND-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "conditional-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-OR-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-OR-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "?");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "conditional-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "assignment-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "conditional-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "assignment-operator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "assignment-operator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "/=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "%=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "+=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "-=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "<<=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, ">>=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "&=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "^=");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "|=");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "constant-expression");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "conditional-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-init-declarator-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-specifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-specifiers");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "storage-class-specifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-specifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "storage-class-specifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-specifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "init-declarator-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "init-declarator");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "init-declarator-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "init-declarator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "init-declarator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "=");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "initializer");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "storage-class-specifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "typedef");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "extern");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "static");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "auto");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "register");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-specifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "void");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "char");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "short");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "int");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "long");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "float");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "double");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "signed");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "unsigned");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-or-union-specifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enum-specifier");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-or-union-specifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-or-union");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-identifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-base-interface");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "struct-declaration-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-or-union");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-or-union");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "interface");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "union");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declaration-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-declaration");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-declaration-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "struct-declaration");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declaration");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "struct-declarator-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "specifier-qualifier-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-specifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier-list");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier-list");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-specifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declarator-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-declarator");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-declarator-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "struct-declarator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declarator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "opt-declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "constant-expression");
    CreateOptRule(pIBNF, "opt-declarator", "declarator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enum-specifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enum");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-identifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "enumerator-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enum");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enumerator-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enumerator");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enumerator-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "enumerator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enumerator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "=");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "constant-expression");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-qualifier");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "const");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "volatile");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declarator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "opt-pointer");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "direct-declarator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "direct-declarator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "direct-declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-constant-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "]");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "direct-declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-parameter-type-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "direct-declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-identifier-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "pointer");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-type-qualifier-list");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-type-qualifier-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "pointer");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-qualifier-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-type-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "parameter-list");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "parameter-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "...");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "parameter-declaration");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "parameter-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "parameter-declaration");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-declaration");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");  
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers"); 
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-abstract-declarator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "identifier-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-name");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-abstract-declarator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "abstract-declarator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "pointer");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "opt-pointer");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "direct-abstract-declarator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "direct-abstract-declarator");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "abstract-declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "opt-direct-abstract-declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-constant-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "]");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "opt-direct-abstract-declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-parameter-type-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    CreateOptRule(pIBNF, "opt-direct-abstract-declarator", "direct-abstract-declarator");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "initializer");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "initializer-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "initializer-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "initializer-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "initializer");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "initializer-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "initializer");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "statement");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "labeled-statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "compound-statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "expression-statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "selection-statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "iteration-statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "jump-statement");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "labeled-statement");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "case");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "constant-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "default");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "compound-statement");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-declaration-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-statement-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declaration");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "statement-list");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "statement-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "expression-statement");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "opt-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "selection-statement");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "if");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "if");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "else");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "switch");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "iteration-statement");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "while");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "do");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "while");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "for-init");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "for");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "jump-statement");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "goto");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "continue");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "break");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "return");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-expression");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "translation-unit");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "external-declaration");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "translation-unit");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "external-declaration");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "external-declaration");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "function-definition");
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "function-definition");
    indexSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "opt-declaration-specifiers");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "opt-declaration-list");
    pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "compound-statement");
    CreateOptRule(pIBNF, "opt-declaration-specifiers", "declaration-specifiers");

    return pIBNF;
}

IEcoBNF1* GetTestIDL(IEcoBNF1* pIBNF) {
    IEcoBNF1Rule* pIRule = 0;
    uint32_t iSet = 0;

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "intf"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "interface");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "}");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "methods"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "method");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "method");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "method"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "int");

    return pIBNF;
}


IEcoBNF1* GetTestIDL2(IEcoBNF1* pIBNF) {
    IEcoBNF1Rule* pIRule = 0;
    uint32_t iSet = 0;

    /* 1. Интерфейс: interface id [inheritance] { methods } */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "intf"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "interface");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "}");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "interface");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "}");

    /* 2. Список методов: ЛЕВАЯ РЕКУРСИЯ (Стабильно для LR) */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "methods"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "method");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "method");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_EPSILON, "epsilon");

    /* 3. Метод */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "method"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "full_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "params");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");

    /* 4. Список параметров: ЛЕВАЯ РЕКУРСИЯ */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "params");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "params");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "param");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "param");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_EPSILON, "epsilon");

    /* 5. Параметр */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "param");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "attr");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "]");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "full_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "full_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");

    /* 6. Атрибуты */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "attr");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "in");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "out");

    /* 7. Типы */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "full_type");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "base_type");

    /* 8. Базовые типы */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "base_type");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "int16_t");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "char_t");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "voidptr_t");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "void");

    return pIBNF;
}


/* ТЕСТ 1: Базовый тест для LR(0) проверяет способность алгоритма сделать операции SHIFT */
bool_t testLR0_1(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST LR(0) Grammar 1 ] ---");
    
    pIBNF = GetTestLR0_1(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 0);
    if (result == 0) {
        OutputDiagnosticInfoOfParser(pILog, pIStr, pILRk);
        OutputDiagnosticInfoOfFSM(pILog, pIStr, pILRk);
    } else {
        pILog->pVTbl->ErrorFormat(pILog, "LR(0) build failed with code: %d", result);
    }
    
    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}

/* ТЕСТ 2: Базовый тест для LR(0) проверяет корректность GOTO-переходов по не терминалам */
bool_t testLR0_2(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST LR(0) Grammar 2 ] ---");
    
    pIBNF = GetTestLR0_2(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 0);
    if (result == 0) {
        OutputDiagnosticInfoOfParser(pILog, pIStr, pILRk);
        OutputDiagnosticInfoOfFSM(pILog, pIStr, pILRk);
    } else {
        pILog->pVTbl->ErrorFormat(pILog, "LR(0) build failed with code: %d", result);
    }
    
    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}

/* ТЕСТ 3: Проверка механизма детекции конфликтов */
bool_t testFailLR1_as_LR0(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST LR(1) Grammar evaluated as LR(0) - EXPECTING CONFLICT ] ---");
    
    pIBNF = GetTestBNF(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 0); 
    if (result != 0) {
        pILog->pVTbl->Info(pILog, "SUCCESS: Grammar properly detected as NON-LR(0) (Conflict generated)!");
    } else {
        pILog->pVTbl->Error(pILog, "FAIL: Grammar was accepted as LR(0) but it is actually LR(1)!");
    }

    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}

/* ТЕСТ 4: Проверяет способность LR(1) алгоритма разрешать конфликты */
bool_t testLR1_1(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST LR(1) Grammar 1 ] ---");
    
    pIBNF = GetTestBNF(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 1);
    if (result == 0) {
        OutputDiagnosticInfoOfParser(pILog, pIStr, pILRk);
        OutputDiagnosticInfoOfFSM(pILog, pIStr, pILRk);
    } else {
        pILog->pVTbl->ErrorFormat(pILog, "InitByGrammar failed with code: %d", result);
    }
    
    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}

/* ТЕСТ 5: Проверяет глубокую регурсию и правостороннюю ассоциативность для алгоритма LR(1) */
bool_t testLR1_2(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST LR(1) Grammar 2 ] ---");
    
    pIBNF = GetTestBNF2(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 1);
    if (result == 0) {
        OutputDiagnosticInfoOfParser(pILog, pIStr, pILRk);
        OutputDiagnosticInfoOfFSM(pILog, pIStr, pILRk);
    } else {
        pILog->pVTbl->ErrorFormat(pILog, "InitByGrammar failed with code: %d", result);
    }
    
    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}

/* ТЕСТ 6: Тест для С грамматики */
bool_t testC(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST C Subset Grammar LR(1) ] ---");
   
    pIBNF = GetTestC(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 1);
    if (result == 0) {
        OutputDiagnosticInfoOfParser(pILog, pIStr, pILRk);
        OutputDiagnosticInfoOfFSM(pILog, pIStr, pILRk);
    } else {
        pILog->pVTbl->ErrorFormat(pILog, "InitByGrammar failed with code: %d", result);
    }

    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}

/* ТЕСТ 7: Тест для С полная грамматика из SetDefaultSyntax (Eco.IDL1) */
bool_t testFullC(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST FULL C Grammar LR(1) ] ---");
   
    pIBNF = GetFullTestC(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 1);
    if (result == 0) {
        OutputDiagnosticInfoOfParser(pILog, pIStr, pILRk);
        OutputDiagnosticInfoOfFSM(pILog, pIStr, pILRk);
    } else {
        pILog->pVTbl->ErrorFormat(pILog, "InitByGrammar failed with code: %d", result);
    }

    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}

/* ТЕСТ 8: Тест для idl */
bool_t testIDL(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST Simplified IDL Grammar LR(1) ] ---");
    
    pIBNF = GetTestIDL(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 1);
    if (result == 0) {
        OutputDiagnosticInfoOfParser(pILog, pIStr, pILRk);
        OutputDiagnosticInfoOfFSM(pILog, pIStr, pILRk);
    } else {
        pILog->pVTbl->ErrorFormat(pILog, "InitByGrammar failed with code: %d", result);
    }
    
    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}


/* ТЕСТ 9: Тест для idl2 */
bool_t testIDL2(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoMemoryAllocator1* pIMem, /* in */ IEcoBNF1* pIBNF, /* in */ IEcoParser1LRk* pILRk) {
    int16_t result = 0;
    pILog->pVTbl->Info(pILog, "--- [ TEST Simplified IDL Grammar LR(1) ] ---");
    
    pIBNF = GetTestIDL2(pIBNF);
    
    OutputDiagnosticInfoOfBNF(pILog, pIStr, pIBNF);
    
    result = pILRk->pVTbl->InitByGrammar(pILRk, pIBNF, 1);
    if (result == 0) {
        OutputDiagnosticInfoOfParser(pILog, pIStr, pILRk);
        OutputDiagnosticInfoOfFSM(pILog, pIStr, pILRk);
    } else {
        pILog->pVTbl->ErrorFormat(pILog, "InitByGrammar failed with code: %d", result);
    }
    
    pIBNF->pVTbl->Clear(pIBNF);
    return 0;
}

bool_t OutputDiagnosticInfoOfBNF(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoBNF1* pGrammar) {
    bool_t bResult = 0;
    IEcoBNF1Rule* pIRule = 0;
    IEcoBNF1Element* pIElement = 0;
    IEcoList1* pIAlphabet = 0;
    IEcoList1* pIRules = 0;
    IEcoList1* pIRuleSet = 0;
    IEcoList1* pIElements = 0;
    char_t* word = 0;
    char_t* Rule = 0;
    uint32_t index = 0;
    uint32_t indexSet = 0;
    uint32_t indexElement = 0;
    
    if (pGrammar != 0) {
        pILog->pVTbl->InfoFormat(pILog, "*** GRAMMAR ***");
        pILog->pVTbl->InfoFormat(pILog, "Alphabet :");
        pIAlphabet = pGrammar->pVTbl->get_Alphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t *)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }
        pILog->pVTbl->InfoFormat(pILog, "NonTerminal :");
        pIAlphabet = pGrammar->pVTbl->get_NonTerminalAlphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t *)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }
        pILog->pVTbl->InfoFormat(pILog, "Terminal :");
        pIAlphabet = pGrammar->pVTbl->get_TerminalAlphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t *)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }
        
        pIRules = pGrammar->pVTbl->get_RuleList(pGrammar);
        for (index = 0; index < pIRules->pVTbl->Count(pIRules); index++) {
            pIRule = (IEcoBNF1Rule*)pIRules->pVTbl->Item(pIRules, index);
            Rule = pIStr->pVTbl->Append(pIStr, Rule, (char_t *)pIRule->pVTbl->get_Name(pIRule));
            pIRuleSet = pIRule->pVTbl->get_RuleSet(pIRule);
            for (indexSet = 0; indexSet < pIRuleSet->pVTbl->Count(pIRuleSet); indexSet++) {
                pIElements = (IEcoList1*)pIRuleSet->pVTbl->Item(pIRuleSet, indexSet);
                if (indexSet == 0) {
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, ":\r\n\t");
                }
                else {
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, "\r\n\t");
                }
                for (indexElement = 0; indexElement < pIElements->pVTbl->Count(pIElements); indexElement++) {
                    pIElement = (IEcoBNF1Element*)pIElements->pVTbl->Item(pIElements, indexElement);
					if (pIElement == 0) {
                        Rule = pIStr->pVTbl->Append(pIStr, Rule, "epsilon ");
                        continue;
                    }
                    if (pIElement->pVTbl->CheckFlag(pIElement, ECO_BNF_1_EF_OPTIONAL)) {
                        Rule = pIStr->pVTbl->Append(pIStr, Rule, "[");
                    }
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, (char_t *)pIElement->pVTbl->get_Name(pIElement));
                    if (pIElement->pVTbl->CheckFlag(pIElement, ECO_BNF_1_EF_OPTIONAL)) {
                        Rule = pIStr->pVTbl->Append(pIStr, Rule, "]");
                    }
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, " ");
                }
            }
            pILog->pVTbl->InfoFormat(pILog, "Rule [%d]\r\n%s", pIRule->pVTbl->get_Id(pIRule), Rule);
        }
            pIStr->pVTbl->Free(pIStr, Rule);
            Rule = 0;
        bResult = 1;
    }
    return bResult;
}

bool_t OutputDiagnosticInfoOfParser(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoParser1LRk* pILRk) {
    IEcoMap2* pIFirstMap = 0;
    IEcoMap2* pIFollowMap = 0;
    IEcoBNF1* pIGrammar = 0;
    IEcoList1* pINonTerminals = 0;
    IEcoList1* pIItemSets = 0;
    IEcoSet2* pISet = 0;
    IEcoContainer1* pIContainer = 0;
    IEcoContainer1Iterator* pIIter = 0;
    char_t* ntName = 0;
    char_t* symName = 0;
    char_t* line = 0;
    uint32_t i = 0;

    if (pILRk == 0 || pILog == 0) return 0;

    pILog->pVTbl->Info(pILog, "*** PARSER LR(k) ***");
    pIGrammar = pILRk->pVTbl->get_Grammar(pILRk);
    pINonTerminals = pIGrammar->pVTbl->get_NonTerminalAlphabet(pIGrammar);

    pILog->pVTbl->Info(pILog, "FIRST Sets:");
    pIFirstMap = pILRk->pVTbl->get_First(pILRk);
    for (i = 0; i < pINonTerminals->pVTbl->Count(pINonTerminals); i++) {
        ntName = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, i);
        pISet = (IEcoSet2*)pIFirstMap->pVTbl->Get(pIFirstMap, ntName);
        if (pISet) {
            pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
            line = pIStr->pVTbl->Append(pIStr, 0, "  FIRST(");
            line = pIStr->pVTbl->Append(pIStr, line, ntName);
            line = pIStr->pVTbl->Append(pIStr, line, ") = { ");
            pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
            if (pIIter) {
                while (pIIter->pVTbl->Value(pIIter)) {
                    symName = (char_t*)pIIter->pVTbl->Value(pIIter);
                    line = pIStr->pVTbl->Append(pIStr, line, symName);
                    pIIter->pVTbl->Next(pIIter);
                    if (pIIter->pVTbl->Value(pIIter)) line = pIStr->pVTbl->Append(pIStr, line, ", ");
                }
                pIIter->pVTbl->Release(pIIter);
            }
            line = pIStr->pVTbl->Append(pIStr, line, " }");
            pILog->pVTbl->Info(pILog, line);
            pIStr->pVTbl->Free(pIStr, line);
        }
    }

    pILog->pVTbl->Info(pILog, "FOLLOW Sets:");
    pIFollowMap = pILRk->pVTbl->get_Follow(pILRk);
    for (i = 0; i < pINonTerminals->pVTbl->Count(pINonTerminals); i++) {
        ntName = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, i);
        pISet = (IEcoSet2*)pIFollowMap->pVTbl->Get(pIFollowMap, ntName);
        if (pISet) {
            pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
            line = pIStr->pVTbl->Append(pIStr, 0, "  FOLLOW(");
            line = pIStr->pVTbl->Append(pIStr, line, ntName);
            line = pIStr->pVTbl->Append(pIStr, line, ") = { ");
            pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
            if (pIIter) {
                while (pIIter->pVTbl->Value(pIIter)) {
                    symName = (char_t*)pIIter->pVTbl->Value(pIIter);
                    line = pIStr->pVTbl->Append(pIStr, line, symName);
                    pIIter->pVTbl->Next(pIIter);
                    if (pIIter->pVTbl->Value(pIIter)) line = pIStr->pVTbl->Append(pIStr, line, ", ");
                }
                pIIter->pVTbl->Release(pIIter);
            }
            line = pIStr->pVTbl->Append(pIStr, line, " }");
            pILog->pVTbl->Info(pILog, line);
            pIStr->pVTbl->Free(pIStr, line);
        }
    }

    pILog->pVTbl->Info(pILog, "Item Sets (States):");
    pIItemSets = pILRk->pVTbl->get_ItemSets(pILRk);
    if (pIItemSets) {
        for (i = 0; i < pIItemSets->pVTbl->Count(pIItemSets); i++) {
            pISet = (IEcoSet2*)pIItemSets->pVTbl->Item(pIItemSets, i);
            pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
            pILog->pVTbl->InfoFormat(pILog, "  State %d:", i);
            pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
            if (pIIter) {
                while (pIIter->pVTbl->Value(pIIter)) {
                    IEcoParser1LRkItem* pItem = (IEcoParser1LRkItem*)pIIter->pVTbl->Value(pIIter);
                    char_t* desc = pItem->pVTbl->get_Description(pItem);
                    pILog->pVTbl->InfoFormat(pILog, "    %s", desc);
                    pIIter->pVTbl->Next(pIIter);
                }
                pIIter->pVTbl->Release(pIIter);
            }
        }
    }

    pILog->pVTbl->Info(pILog, "********************");
    return 1;
}

bool_t OutputDiagnosticInfoOfFSM(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoParser1LRk* pILRk) {
    IEcoBNF1* pIGrammar = 0;
    IEcoList1* pITerminals = 0;
    IEcoList1* pINonTerminals = 0;
    IEcoList1* pIItemSets = 0;
    uint32_t numStates = 0;
    uint32_t i = 0, j = 0;
    char_t* symName = 0;
    int32_t actionValue = 0;

    if (pILRk == 0 || pILog == 0) return 0;

    /* 1. Извлекаем необходимые данные через интерфейсы */
    pIGrammar = pILRk->pVTbl->get_Grammar(pILRk);
    pITerminals = pIGrammar->pVTbl->get_TerminalAlphabet(pIGrammar);
    pINonTerminals = pIGrammar->pVTbl->get_NonTerminalAlphabet(pIGrammar);
    pIItemSets = pILRk->pVTbl->get_ItemSets(pILRk);
    numStates = pIItemSets->pVTbl->Count(pIItemSets);

    pILog->pVTbl->Info(pILog, "*** GOTO/ACTION TABLE (FSM) ***");
    pILog->pVTbl->Info(pILog, "  Source   |   Symbol       |   Target   |  Action ");
    pILog->pVTbl->Info(pILog, "-----------+----------------+------------+----------");

    /* 2. Проход по всем состояниям (строкам таблицы) */
    for (i = 0; i < numStates; i++) {
        
        /* 2.1. Проверяем действия по Терминалам (ACTION) */
        for (j = 0; j < pITerminals->pVTbl->Count(pITerminals); j++) {
            symName = (char_t*)pITerminals->pVTbl->Item(pITerminals, j);
            actionValue = pILRk->pVTbl->get_Action(pILRk, i, symName);

            if (actionValue != 0) { /* 0 - это Error, пропускаем для чистоты лога */
                if (actionValue == 0x7FFFFFFF) {
                    /* ACCEPT */
                    pILog->pVTbl->InfoFormat(pILog, "  State %-3u | %-14s |            | [ ACCEPT ]", i, symName);
                } else if (actionValue > 0) {
                    /* SHIFT */
                    pILog->pVTbl->InfoFormat(pILog, "  State %-3u | %-14s | State %-3d | SHIFT", i, symName, actionValue);
                } else {
                    /* REDUCE (отрицательное значение) */
                    pILog->pVTbl->InfoFormat(pILog, "  State %-3u | %-14s | Rule %-5d | REDUCE", i, symName, -actionValue);
                }
            }
        }

        /* 2.2. Проверяем переходы по Нетерминалам (GOTO) */
        for (j = 0; j < pINonTerminals->pVTbl->Count(pINonTerminals); j++) {
            symName = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, j);
            actionValue = pILRk->pVTbl->get_Goto(pILRk, i, symName);

            if (actionValue != -1) { /* -1 - перехода нет */
                pILog->pVTbl->InfoFormat(pILog, "  State %-3u | %-14s | State %-3d | GOTO", i, symName, actionValue);
            }
        }
    }

    pILog->pVTbl->Info(pILog, "-----------+----------------+------------+----------");
    return 1;
}
