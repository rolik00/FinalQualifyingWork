/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1_40BB8A88
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoIDL1_40BB8A88
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IdEcoFileSystemManagement1.h"
#include "CEcoIDL1.h"
#include "IdEcoList1.h"
#include "IdEcoLR1.h"
#include "IdEcoIDL1C.h"
#include "IdEcoIDL1CPP.h"
#include "IdEcoIDL1Java.h"
#include "IdEcoIDL1Python.h"

/*
 *
 * <summary>
 *   SetDefaultLexer Function
 * </summary>
 *
 * <description>
 *   
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_SetDefaultLexer(CEcoIDL1_40BB8A88* pCMe) {
    int16_t result = -1;
    IEcoLexicalData1* pIData = 0;
    IEcoLexicalAnalyzer1Scanner* pScanner = 0;
    IEcoLexicalAnalyzer1Token* pToken = 0;
    IEcoList1* pIRuleSet = 0;
    IEcoList1* pIElementList = 0;
    IEcoList1* pIRuleList = 0;
    IEcoList1* pITerminals = 0;

    IEcoBNF1Element* pIElement = 0;
    bool_t bFound = 0;
    IEcoBNF1Rule* pIRule = 0;
    char_t* Word = 0;
    uint32_t index = 0;
    uint32_t indexRule = 0;
    uint32_t indexSet = 0;
    uint32_t indexElement = 0;
    uint32_t lastId = 0;
    bool_t isAdded[1024]; 
    uint32_t currentId = 0;
    memset(isAdded, 0, sizeof(isAdded));

    result = pCMe->m_pILA->pVTbl->CreateRulesRE(pCMe->m_pILA, &pCMe->m_pILexicalRules);

    if (result == 0 && pCMe->m_pILexicalRules != 0) {
        pIRuleList = pCMe->m_pISyntaxRules->pVTbl->get_RuleList(pCMe->m_pISyntaxRules);
        pITerminals = pCMe->m_pISyntaxRules->pVTbl->get_TerminalAlphabet(pCMe->m_pISyntaxRules);
        for (index = 0; index < pITerminals->pVTbl->Count(pITerminals); index++) {
            Word = (char_t*)pITerminals->pVTbl->Item(pITerminals, index);

            for (indexRule = 0; indexRule < pIRuleList->pVTbl->Count(pIRuleList); indexRule++) {
                pIRule = (IEcoBNF1Rule*)pIRuleList->pVTbl->Item(pIRuleList, indexRule);
                pIRuleSet = pIRule->pVTbl->get_RuleSet(pIRule);
                for (indexSet = 0; indexSet < pIRuleSet->pVTbl->Count(pIRuleSet); indexSet++) {
                    pIElementList = (IEcoList1*)pIRuleSet->pVTbl->Item(pIRuleSet, indexSet);
                    for (indexElement = 0; indexElement < pIElementList->pVTbl->Count(pIElementList); indexElement++) {
                        pIElement = (IEcoBNF1Element*)pIElementList->pVTbl->Item(pIElementList, indexElement);
                        currentId = pIElement->pVTbl->get_Id(pIElement);
                        
                        if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, pIElement->pVTbl->get_Name(pIElement), Word) == 0 && currentId < 1024 && !isAdded[currentId]) {
                            if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "epsilon") == 0) {
                                continue; 
                            }
                            if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "id") == 0) {
                                pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "([A-Z]|[a-z]|_)([A-Z]|[a-z]|[0-9]|_)*", currentId);
                                pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, currentId, 50); 
                            } else if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "string_literal") == 0) {
                                pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\"([A-Z]|[a-z]|[0-9]|_|\\[|\\]| |\\{|\\}|\\(|\\)|;|:|,|\\.|\\*)*\"", currentId);
                                pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, currentId, 5);
                            } else if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "{") == 0 || 
                                     pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "}") == 0 ||
                                     pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "(") == 0 ||
                                     pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, ")") == 0 ||
                                     pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "[") == 0 ||
                                     pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "]") == 0 ||
                                     pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, ":") == 0 ||
                                     pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, "*") == 0 ||
                                     pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, Word, ".") == 0) {
                                char_t escaped[3] = {'\\', 0, 0};
                                escaped[1] = Word[0];
                                pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, escaped, currentId);
                                pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, currentId, 10);
                            } else {
                                pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, Word, currentId);
                                pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, currentId, 10);
                            }
                            isAdded[currentId] = 1; 
                            if (currentId > lastId) lastId = currentId;
                        }
                    }
                }
            }
        }

        lastId++;

        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "( |\t|\r|\n)+", lastId);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, lastId, 100);
        pCMe->m_pILexicalRules->pVTbl->SetChannel(pCMe->m_pILexicalRules, lastId, 1);

        result = 0;

    }

    return result;
}

/*
 *
 * <summary>
 *   SetDefaultSyntax Function
 * </summary>
 *
 * <description>
 *   
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_SetDefaultSyntax(CEcoIDL1_40BB8A88* pCMe) {
    int16_t result = -1;
    IEcoBNF1* pIBNF = 0;
    IEcoBNF1Rule* pIRule = 0;
    IEcoBNF1Rule* pIGroup = 0;
    IEcoBNF1Rule* pIOption = 0;
    IEcoBNF1Element* pIElement = 0;
    uint32_t indexSet = 0;
    uint32_t iSet = 0;

    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoBNF1, 0, &IID_IEcoBNF1, (void**) &pIBNF);
    if (result != 0 || pIBNF == 0) {
        return result;
    }

    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "start");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "intf");

    /* 1. intf */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "intf"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "interface");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "}");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "interface");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "}");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");

    /* 2. methods */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "methods"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "method");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "method");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_EPSILON, "epsilon");

    /* 3. method */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "method"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "params");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");

    /* 4. params */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "params");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "params_list");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_EPSILON, "epsilon");

    /* 5. params_list */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "params_list");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "params_list");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "param");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "param");

    /* 6. param */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "param");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "attr");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "]");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "attr");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "]");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "attr");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "]");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");

    /* 7. attr */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "attr");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "in");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "out");

    /* 8. base_type */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "base_type");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "int16_t");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "char_t");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "voidptr_t");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "void");
    iSet = 0; 
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "uint32_t");

    pCMe->m_pISyntaxRules = pIBNF;

    return result;
}

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoIDL1 interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_QueryInterface(/* in */ IEcoIDL1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoIDL1) ) {
        *ppv = &pCMe->m_pVTblIIDL;
        pCMe->m_pVTblIIDL->AddRef((IEcoIDL1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIIDL;
        pCMe->m_pVTblIIDL->AddRef((IEcoIDL1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   AddRef Function
 * </summary>
 *
 * <description>
 *   AddRef function for the IEcoIDL1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1_40BB8A88_AddRef(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return atomicincrement_int32_t(&pCMe->m_cRef);
}

/*
 *
 * <summary>
 *   Release Function
 * </summary>
 *
 * <description>
 *   Release function for the IEcoIDL1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1_40BB8A88_Release(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Decrementing the component's reference count */
    atomicdecrement_int32_t(&pCMe->m_cRef);
    /* If the count is zero, free the instance data */
    if ( pCMe->m_cRef == 0 ) {
        pCMe->Delete(pCMe);

        return 0;
    }
    return pCMe->m_cRef;
}

static int16_t LoadLexicalRules(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
	int16_t result = 0;
    IEcoFileSystemManagement1* pIFSM = 0;
    IEcoFileManager1* pIFM = 0;
	IEcoFile1* pFile = 0;
    const char_t* binFileName = "idl_core.bin";

	if (me == 0) {
		return ERR_ECO_POINTER;
	}

    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoFileSystemManagement1, 0, &IID_IEcoFileSystemManagement1, (void**)&pIFSM);
	
	if (result == 0 && pIFSM != 0) {
        pIFM = pIFSM->pVTbl->get_FileManager(pIFSM);
        if (pIFM) {
            pFile = pIFM->pVTbl->Open(pIFM, (char_t*)binFileName);
			if (pFile != 0) {
				pFile->pVTbl->Close(pFile);
                
				result = pCMe->m_pILA->pVTbl->LoadRulesFromFile(pCMe->m_pILA, (char_t*)binFileName, &pCMe->m_pIData);
			}
        }
        pIFSM->pVTbl->Release(pIFSM);
    }

    if (pCMe->m_pIData == 0) {
        result = CEcoIDL1_40BB8A88_SetDefaultSyntax(pCMe);
		result = CEcoIDL1_40BB8A88_SetDefaultLexer(pCMe);
        if (result == 0 && pCMe->m_pILexicalRules != 0) {
            result = pCMe->m_pILexicalRules->pVTbl->Compile(pCMe->m_pILexicalRules, &pCMe->m_pIData);
            
            if (result == 0 && pCMe->m_pIData != 0) {
                pCMe->m_pILA->pVTbl->SaveRulesToFile(pCMe->m_pILA, (IEcoUnknown*)pCMe->m_pIData, (char_t*)binFileName);
            }
        }
    }

	return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Initialize Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_Initialize(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
    IEcoList1* pIRuleList = 0;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    if (pCMe->m_pILexicalRules == 0) {
         LoadLexicalRules(me);
    }

    if (pCMe->m_pISyntaxRules == 0) {
		CEcoIDL1_40BB8A88_SetDefaultSyntax(pCMe);
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Terminate Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_Terminate(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   GetLexicalRules Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_GetLexicalRules(/* in */ IEcoIDL1Ptr_t me, /* out */ voidptr_t* ppRules) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   GetSyntaxRules Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_GetSyntaxRules(/* in */ IEcoIDL1Ptr_t me, /* out */ voidptr_t* ppRules) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   ParseFile Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_ParseFile(/* in */ IEcoIDL1Ptr_t me, /* in */ char_t* filePath, /* out */ IEcoAST1Ptr_t* ppAST) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
    IEcoSyntaxAnalyzer1Parser* pIParser = 0;
    IEcoLexicalAnalyzer1Token* pIToken = 0;
    IEcoParser1Action* pIAction = 0;
    IEcoLexicalAnalyzer1Scanner* pScanner = 0;
    IEcoAST1SyntaxObject* pISyntaxObject = 0;
    char_t* pszSourceFileExt = 0;
    IEcoAST1* pIAST;
    int16_t result = 0;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    /* Извлекаем расширение файла из имени */
    pszSourceFileExt = pCMe->m_pIStr->pVTbl->SearchLastCharacter(pCMe->m_pIStr, filePath, '.');
    if (pszSourceFileExt != 0) {
        pCMe->m_Name = pCMe->m_pIStr->pVTbl->Substring(pCMe->m_pIStr, filePath, 0, pszSourceFileExt - filePath);
    } else {
        pCMe->m_Name = pCMe->m_pIStr->pVTbl->Clone(pCMe->m_pIStr, filePath);
    }

    /* Парсер */
    if (pCMe->m_pIData != 0) {
        result = pCMe->m_pILA->pVTbl->new_FileScanner(pCMe->m_pILA, (IEcoUnknownPtr_t)pCMe->m_pIData, filePath, &pScanner);
        if (result != 0) return result;

        pCMe->m_pISA->pVTbl->RegisterAlgorithm(pCMe->m_pISA, &CID_EcoLR1, "LRk");
        pIParser = pCMe->m_pISA->pVTbl->get_Parser(pCMe->m_pISA, pCMe->m_pISyntaxRules, 0);

        if (pIParser == 0) {
            pScanner->pVTbl->Release(pScanner);
            return -1;
        }

        pIToken = pScanner->pVTbl->Scan(pScanner);
        while (pIToken) {
            if (pIToken->pVTbl->get_Channel(pIToken) == 0) {
                pIAction = pIParser->pVTbl->Parse(pIParser, pIToken);
            }
            if (pIToken->pVTbl->IsEOF(pIToken)) break;
            pIToken->pVTbl->Release(pIToken);
            pIToken = pScanner->pVTbl->Scan(pScanner);
        }
        if (pIToken) pIToken->pVTbl->Release(pIToken);

        pIAST = pIParser->pVTbl->get_AST(pIParser);
        if (pIAST) {
            pIAST->pVTbl->AddRef(pIAST);
            *ppAST = pIAST;
        }
    }

    if (pScanner) pScanner->pVTbl->Release(pScanner);
    if (pIParser) pIParser->pVTbl->Release(pIParser);

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   RegisterEmitter Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_RegisterEmitter(/* in */ IEcoIDL1Ptr_t me, /* in */ const UGUID* rcid, /* in */ char_t* langId) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
    uint32_t i;

    /* Pointer Validation */
    if (me == 0 || rcid == 0 || langId == 0) {
		return ERR_ECO_POINTER;
	}
    if (pCMe->m_cEmitters >= 16) {
		return -1; /* Достигнут лимит */
	}

	/* Проверка, нет ли уже такого языка */
    for (i = 0; i < pCMe->m_cEmitters; i++) {
        if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, pCMe->m_Emitters[i].langId, langId) == 0) {
            pCMe->m_Emitters[i].cid = *rcid;
            return ERR_ECO_SUCCESES;
        }
    }

	/* Добавление нового */
    pCMe->m_Emitters[pCMe->m_cEmitters].cid = *rcid;
    for (i = 0; i < 31 && langId[i] != 0; i++) {
        pCMe->m_Emitters[pCMe->m_cEmitters].langId[i] = langId[i];
    }
    pCMe->m_Emitters[pCMe->m_cEmitters].langId[i] = 0;
    
    pCMe->m_cEmitters++;

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   GetEmitter Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_GetEmitter(/* in */ IEcoIDL1Ptr_t me, /* in */ char_t* langId, /* out */ IEcoIDL1Emitter** ppIEmitter) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
	uint32_t i;

    /* Pointer Validation */
    if (me == 0 || langId == 0 || ppIEmitter == 0) {
		return ERR_ECO_POINTER;
	}
    *ppIEmitter = 0;

	for (i = 0; i < pCMe->m_cEmitters; i++) {
        if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, pCMe->m_Emitters[i].langId, langId) == 0) {
            return pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &pCMe->m_Emitters[i].cid, 0, &IID_IEcoIDL1Emitter, (void**)ppIEmitter);
        }
    }

    return -1;
}

/*
 *
 * <summary>
 *   Generate Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_Generate(/* in */ IEcoIDL1Ptr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ IEcoIDL1ProjectLayoutPtr_t pLayout, /* in */ char_t* langId, /* in */ void* commonArgs) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
    IEcoIDL1Emitter* pIEmitter = 0;
    char_t* pszIfaceName = 0;
    uint32_t i;
    bool_t generateAll = 0;
    bool_t foundLanguage = 0;
    uint32_t successCount = 0;
    uint32_t failCount = 0;
    int16_t result = 0;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

	if (langId == 0 || pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, langId, "ALL") == 0) {
        generateAll = 1;
    }

    for (i = 0; i < pCMe->m_cEmitters; i++) {
        if (generateAll || pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, langId, pCMe->m_Emitters[i].langId) == 0) {
            foundLanguage = 1;
			result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &pCMe->m_Emitters[i].cid, 0, &IID_IEcoIDL1Emitter, (void**)&pIEmitter);
            if (result == 0 && pIEmitter != 0) {
				char_t* pszOutDir = (char_t*)commonArgs;
				if (pszOutDir != 0) {
                    pszIfaceName = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszIfaceName, pszOutDir);
                    pszIfaceName = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszIfaceName, "\\");
                }

				pszIfaceName = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszIfaceName, pCMe->m_Name);
                pIEmitter->pVTbl->Emit(pIEmitter, pAST, pszIfaceName);
                pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszIfaceName);
                pszIfaceName = 0;
                pIEmitter->pVTbl->Release(pIEmitter);
				successCount++;
            } else {
				failCount++;
            }
        }
    }

	if (!foundLanguage) {
        return -2;
    }
    if (successCount == 0) {
        return -3;
    }
    if (failCount > 0) {
        return -4; 
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Init Function
 * </summary>
 *
 * <description>
 *   Instance initialization function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD initCEcoIDL1_40BB8A88(/*in*/ CEcoIDL1_40BB8A88Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = ERR_ECO_POINTER;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    /* Pointer Validation */
    if (me == 0 ) {
        return result;
    }

    /* Storing the pointer to the system interface */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Getting the interface for working with the interface bus */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pCMe->m_pIBus);

    /* Getting the component ID for working with memory */
    result = pCMe->m_pIBus->pVTbl->QueryInterface(pCMe->m_pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Getting the memory allocator interface */
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);
    /* Check */
    if (result != 0 || pCMe->m_pIMem == 0) {
        result = ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**) &pCMe->m_pIStr);
    /* Check */
    if (result != 0 || pCMe->m_pIStr == 0) {
        //result = ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoBLA1, 0, &IID_IEcoLexicalAnalyzer1, (void**) &pCMe->m_pILA);
    if (result != 0 || pCMe->m_pILA == 0) {
        //result = ERR_ECO_BLA;
    }
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoBSA1, 0, &IID_IEcoSyntaxAnalyzer1, (void**) &pCMe->m_pISA);
    if (result != 0 || pCMe->m_pILA == 0) {
        //result = ERR_ECO_SA;
    }

    /* Регистрация алгоритма для анализа */
    pCMe->m_pISA->pVTbl->RegisterAlgorithm(pCMe->m_pISA, &CID_EcoLR1, "LR1");
    /* Устанавливаем алгоритм по умолчанию */
    pCMe->m_pISA->pVTbl->set_DefaultAlgorithm(pCMe->m_pISA, "LR1");

    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoAST1, 0, &IID_IEcoAST1, (void**) &pCMe->m_pIAST);
    if (result != 0 || pCMe->m_pIAST == 0) {
        //result = ERR_ECO_AST;
    }

	pCMe->m_pIData = 0;
	pCMe->m_cEmitters = 0;

    return result;
}

/*
 *
 * <summary>
 *   Create Function
 * </summary>
 *
 * <description>
 *   Instance creation function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD createCEcoIDL1_40BB8A88(/* in */ CEcoIDL1_40BB8A88Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
    int16_t result = ERR_ECO_POINTER;

    /* Pointer Validation */
    if (pCMe == 0) {
        return result; /* ERR_ECO_POINTER */
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Delete Function
 * </summary>
 *
 * <description>
 *   Instance freeing function
 * </description>
 *
 */
static void ECOCALLMETHOD deleteCEcoIDL1_40BB8A88(/* in */ CEcoIDL1_40BB8A88Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
		if ( pCMe->m_pIAST != 0 ) {
            pCMe->m_pIAST->pVTbl->Release(pCMe->m_pIAST);
        }
        if ( pCMe->m_pISyntaxRules != 0 ) {
            pCMe->m_pISyntaxRules->pVTbl->Release(pCMe->m_pISyntaxRules);
        }
        if ( pCMe->m_pISA != 0 ) {
            pCMe->m_pISA->pVTbl->Release(pCMe->m_pISA);
        }
		if ( pCMe->m_pILexicalRules != 0 ) {
            pCMe->m_pILexicalRules->pVTbl->Release(pCMe->m_pILexicalRules);
        }
        if ( pCMe->m_pILA != 0 ) {
            pCMe->m_pILA->pVTbl->Release(pCMe->m_pILA);
        }
		if (pCMe->m_pIData != 0) {
            pCMe->m_pIData->pVTbl->Release(pCMe->m_pIData);
        }
		if ( pCMe->m_pIStr != 0 ) {
            pCMe->m_pIStr->pVTbl->Release(pCMe->m_pIStr);
        }
        if ( pCMe->m_pIBus != 0 ) {
            pCMe->m_pIBus->pVTbl->Release(pCMe->m_pIBus);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoIDL1 Virtual Table */
IEcoIDL1VTbl g_x948C13ED820E45389E1EBBDD9308A42CVTbl_40BB8A88 = {
    CEcoIDL1_40BB8A88_QueryInterface,
    CEcoIDL1_40BB8A88_AddRef,
    CEcoIDL1_40BB8A88_Release,
    CEcoIDL1_40BB8A88_Initialize,
    CEcoIDL1_40BB8A88_Terminate,
    CEcoIDL1_40BB8A88_GetLexicalRules,
    CEcoIDL1_40BB8A88_GetSyntaxRules,
    CEcoIDL1_40BB8A88_ParseFile,
    CEcoIDL1_40BB8A88_RegisterEmitter,
    CEcoIDL1_40BB8A88_GetEmitter,
    CEcoIDL1_40BB8A88_Generate
};

/* Object Instance */
CEcoIDL1_40BB8A88 g_xCEcoIDL1_40BB8A88 = {
    &g_x948C13ED820E45389E1EBBDD9308A42CVTbl_40BB8A88,
   
    initCEcoIDL1_40BB8A88,
    createCEcoIDL1_40BB8A88,
    deleteCEcoIDL1_40BB8A88,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_pIBus */
    0, /* m_pIStr */
    0, /* m_pILA */
    0, /* m_pILexicalRules */
	0, /* m_pIData */
    0, /* m_pISA */
    0, /* m_pISynatxRules */
    0, /* m_pIAST */
    0  /* m_Name */
};
