/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLR1RE_F82A88F6
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBLR1RE_F82A88F6
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */


#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoBLR1RE.h"
#include "CEcoBLD1.h"
#include "IdEcoList1.h"
#include "IdEcoBRE1.h"
#include "IdEcoFSM1.h"
#include <string.h>

extern IEcoLexicalData1VTbl g_xDB2E163758AA4447A843545A8805D3FEVTbl_F82A88F6;

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoLexicalRules1RE interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_QueryInterface(/* in */ IEcoLexicalRules1REPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoLexicalRules1RE) ) {
        *ppv = &pCMe->m_pVTblIRules;
        pCMe->m_pVTblIRules->AddRef((IEcoLexicalRules1RE*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIRules;
        pCMe->m_pVTblIRules->AddRef((IEcoLexicalRules1RE*)pCMe);
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
 *   AddRef function for the IEcoLexicalRules1RE interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_AddRef(/* in */ IEcoLexicalRules1REPtr_t me) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <summary>
 *   Release Function
 * </summary>
 *
 * <description>
 *   Release function for the IEcoLexicalRules1RE interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_Release(/* in */ IEcoLexicalRules1REPtr_t me) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Decrementing the component's reference count */
    --pCMe->m_cRef;
    /* If the count is zero, free the instance data */
    if ( pCMe->m_cRef == 0 ) {
        pCMe->Delete(pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_AddState(IEcoLexicalRules1REPtr_t me, char_t* name, bool_t isExclusive) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static uint32_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_get_StatesCount(IEcoLexicalRules1REPtr_t me) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static char_t* ECOCALLMETHOD CEcoBLR1RE_F82A88F6_get_StateName(IEcoLexicalRules1REPtr_t me, uint32_t index) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}

/*
 * <summary>
 *   Вспомогательная функция для поиска начального состояния в NFA
 * </summary>
 */
static IEcoFSM1State* FindStartState(IEcoFSM1StateMachine* pNFA) {
    IEcoList1* pStates = 0;
    uint32_t count = 0, i = 0;
    IEcoFSM1State* pState = 0;
    
    if (pNFA == 0) return 0;
    
    pStates = pNFA->pVTbl->get_States(pNFA);
    if (pStates == 0) return 0;
    
    count = pStates->pVTbl->Count(pStates);
    
    for (i = 0; i < count; i++) {
        pState = (IEcoFSM1State*)pStates->pVTbl->Item(pStates, i);
        if (pState && pState->pVTbl->IsInitial(pState)) {
            return pState;
        }
    }
    
    return 0;
}

/*
 * <summary>
 *   Вспомогательная функция для сбора всех финальных состояний в NFA
 * </summary>
 */
static IEcoList1* CollectFinalStates(CEcoBLR1RE_F82A88F6* pCMe, IEcoFSM1StateMachine* pNFA) {
    IEcoInterfaceBus1* pIBus = 0;
    IEcoList1* pFinalStates = 0;
    IEcoList1* pStates = 0;
    uint32_t count = 0, i = 0;
    IEcoFSM1State* pState = 0;
    int16_t result = 0;
    
    if (pCMe == 0 || pNFA == 0) return 0;
    
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        return 0;
    }
    
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pFinalStates);
    pIBus->pVTbl->Release(pIBus);
    
    if (result != 0 || pFinalStates == 0) {
        return 0;
    }
    
    pStates = pNFA->pVTbl->get_States(pNFA);
    if (pStates == 0) {
        pFinalStates->pVTbl->Release(pFinalStates);
        return 0;
    }
    
    count = pStates->pVTbl->Count(pStates);
    
    for (i = 0; i < count; i++) {
        pState = (IEcoFSM1State*)pStates->pVTbl->Item(pStates, i);
        if (pState && pState->pVTbl->IsFinal(pState)) {
            pFinalStates->pVTbl->Add(pFinalStates, pState);
            pState->pVTbl->AddRef(pState);
        }
    }
    
    return pFinalStates;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_AddRuleRE(IEcoLexicalRules1REPtr_t me, char_t* stateName, char_t* pattern, uint32_t tokenId) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
	RuleRE* pRule = 0; 
	IEcoRegEx1* pRegex = 0;
	IEcoFSM1StateMachine* pNFA = 0;
	IEcoFSM1State* pStartState;
	IEcoList1* pAcceptingStates;
    int16_t result = 0;
	
    /* Pointer Validation */
    if (me == 0 || pCMe->m_pBRE == 0 || pCMe->m_pRulesList == 0) {
        return ERR_ECO_POINTER;
    }

	result = pCMe->m_pBRE->pVTbl->CreateRegEx(pCMe->m_pBRE, pattern, strlen(pattern), 0, &pRegex);
    if (result != 0 || pRegex == 0) {
        return result;
    }
    
	result = pRegex->pVTbl->QueryInterface(pRegex, &IID_IEcoFSM1StateMachine, (void**)&pNFA);
    if (result != 0 || pNFA == 0) {
        pRegex->pVTbl->Release(pRegex);
        return -1;
    }
    
	pStartState = FindStartState(pNFA);
    if (pStartState == 0) {
        pNFA->pVTbl->Release(pNFA);
        pRegex->pVTbl->Release(pRegex);
        return -1;
    }
    
	pAcceptingStates = CollectFinalStates(pCMe, pNFA);
    if (pAcceptingStates == 0) {
        pNFA->pVTbl->Release(pNFA);
        pRegex->pVTbl->Release(pRegex);
        return -1;
    }
    
    pRule = (RuleRE*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(RuleRE));
    if (pRule == 0) {
        pAcceptingStates->pVTbl->Release(pAcceptingStates);
        pNFA->pVTbl->Release(pNFA);
        pRegex->pVTbl->Release(pRegex);
        return -1;
    }
    
	memset(pRule, 0, sizeof(RuleRE));
    
	pRule->pattern = (char_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (strlen(pattern) + 1) * sizeof(char_t));
    if (pRule->pattern) {
        strcpy(pRule->pattern, pattern);
    }
	if (stateName) {
        pRule->stateName = (char_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (strlen(stateName) + 1) * sizeof(char_t));
        if (pRule->stateName) {
            strcpy(pRule->stateName, stateName);
        }
    }
	pRule->tokenId = tokenId;
    pRule->priority = pCMe->m_pRulesList->pVTbl->Count(pCMe->m_pRulesList);
    pRule->channel = 0;
	pRule->action = 0;
    pRule->actionContext = 0;
    pRule->pNFA = pNFA;
	pRule->pStartState = pStartState;
    pRule->pStartState->pVTbl->AddRef(pRule->pStartState);
    pRule->pAcceptingStates = pAcceptingStates;
	pRule->pRegex = pRegex;
	pRule->pRegex->pVTbl->AddRef(pRule->pRegex);

	result = pCMe->m_pRulesList->pVTbl->Add(pCMe->m_pRulesList, pRule);
    
    pRegex->pVTbl->Release(pRegex);
    
	return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_AddRuleObject(IEcoLexicalRules1REPtr_t me, char_t* stateName, IEcoRegEx1Ptr_t pIRegEx, uint32_t tokenId) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    IEcoFSM1StateMachine* pNFA = 0;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || pIRegEx == 0 || pCMe->m_pRulesList == 0) {
        return ERR_ECO_POINTER;
    }

    pRule = (RuleRE*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(RuleRE));
    if (pRule == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    memset(pRule, 0, sizeof(RuleRE));
    
    if (stateName) {
        pRule->stateName = (char_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, (strlen(stateName) + 1) * sizeof(char_t));
        if (pRule->stateName) {
            strcpy(pRule->stateName, stateName);
        }
    }
    pRule->tokenId = tokenId;
    pRule->priority = pCMe->m_pRulesList->pVTbl->Count(pCMe->m_pRulesList);
    pRule->channel = 0;
    pRule->action = 0;
    pRule->actionContext = 0;
    pRule->pattern = 0;

    result = pIRegEx->pVTbl->QueryInterface(pIRegEx, &IID_IEcoFSM1StateMachine, (void**)&pNFA);
    if (result != 0 || pNFA == 0) {
        if (pRule->stateName) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pRule->stateName);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pRule);
        return result;
    }

    pRule->pNFA = pNFA;
    
    pRule->pStartState = FindStartState(pNFA);
    if (pRule->pStartState) {
        pRule->pStartState->pVTbl->AddRef(pRule->pStartState);
    }

	pRule->pAcceptingStates = CollectFinalStates(pCMe, pNFA);

    result = pCMe->m_pRulesList->pVTbl->Add(pCMe->m_pRulesList, pRule);
    
    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_SetPriority(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, uint32_t priority) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    uint32_t count = 0, i = 0;
    IEcoList1* pList = 0;

    /* Проверка указателя */
    if (me == 0 || pCMe->m_pRulesList == 0) {
        return ERR_ECO_POINTER;
    }

    pList = pCMe->m_pRulesList;
    count = pList->pVTbl->Count(pList);

    for (i = 0; i < count; i++) {
        pRule = (RuleRE*)pList->pVTbl->Item(pList, i);
        if (pRule && pRule->tokenId == tokenId) {
            pRule->priority = priority;
            return ERR_ECO_SUCCESES;
        }
    }

    return -1;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_SetChannel(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, uint32_t channelId) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    uint32_t count = 0, i = 0;
    IEcoList1* pList = 0;

    /* Проверка указателя */
    if (me == 0 || pCMe->m_pRulesList == 0) {
        return ERR_ECO_POINTER;
    }

    pList = pCMe->m_pRulesList;
    count = pList->pVTbl->Count(pList);

    for (i = 0; i < count; i++) {
        pRule = (RuleRE*)pList->pVTbl->Item(pList, i);
        if (pRule && pRule->tokenId == tokenId) {
            pRule->channel = channelId;
            return ERR_ECO_SUCCESES;
        }
    }

    return -1;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_SetAction(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, EcoLexicalAction_t pfnAction, voidptr_t pContext) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    uint32_t count = 0, i = 0;
    IEcoList1* pList = 0;

    /* Проверка указателя */
    if (me == 0 || pCMe->m_pRulesList == 0) {
        return ERR_ECO_POINTER;
    }

    pList = pCMe->m_pRulesList;
    count = pList->pVTbl->Count(pList);

    for (i = 0; i < count; i++) {
        pRule = (RuleRE*)pList->pVTbl->Item(pList, i);
        if (pRule && pRule->tokenId == tokenId) {
            pRule->action = pfnAction;
            pRule->actionContext = pContext;
            return ERR_ECO_SUCCESES;
        }
    }

    return -1;
}

static uint32_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_get_Count(IEcoLexicalRules1REPtr_t me) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Проверка указателя */
    if (me == 0 || pCMe->m_pRulesList == 0) {
        return 0;
    }

    return pCMe->m_pRulesList->pVTbl->Count(pCMe->m_pRulesList);
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_GetRuleInfo(IEcoLexicalRules1REPtr_t me, uint32_t index, EcoLexicalRuleREInfo* pInfo) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    IEcoList1* pList = 0;
    uint32_t count = 0;

    /* Проверка указателей */
    if (me == 0 || pCMe->m_pRulesList == 0 || pInfo == 0) {
        return ERR_ECO_POINTER;
    }

    pList = pCMe->m_pRulesList;
    count = pList->pVTbl->Count(pList);

    if (index >= count) {
        return -1; /* Индекс вне диапазона */
    }

    pRule = (RuleRE*)pList->pVTbl->Item(pList, index);
    if (pRule == 0) {
        return -1;
    }

    pInfo->tokenId = pRule->tokenId;
    pInfo->stateName = pRule->stateName;
    pInfo->priority = pRule->priority;
    pInfo->channelId = pRule->channel;
    pInfo->hasAction = (pRule->action != 0);

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_GetRuleObject(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, IEcoRegEx1Ptr_t* ppIRegEx) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    uint32_t count = 0, i = 0;
    IEcoList1* pList = 0;
    IEcoFSM1StateMachine* pNFA = 0;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || pCMe->m_pRulesList == 0 || ppIRegEx == 0) {
        return ERR_ECO_POINTER;
    }

    *ppIRegEx = 0;
    pList = pCMe->m_pRulesList;
    count = pList->pVTbl->Count(pList);

    for (i = 0; i < count; i++) {
        pRule = (RuleRE*)pList->pVTbl->Item(pList, i);
        if (pRule && pRule->tokenId == tokenId && pRule->pRegex != 0) {
            *ppIRegEx = pRule->pRegex;
			pRule->pRegex->pVTbl->AddRef(pRule->pRegex);
			return ERR_ECO_SUCCESES;
        }
    }

    return -1;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_GetAction(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, EcoLexicalAction_t* ppfnAction, voidptr_t* ppContext) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    uint32_t count = 0, i = 0;
    IEcoList1* pList = 0;

    /* Проверка указателей */
    if (me == 0 || pCMe->m_pRulesList == 0 || ppfnAction == 0 || ppContext == 0) {
        return ERR_ECO_POINTER;
    }

    pList = pCMe->m_pRulesList;
    count = pList->pVTbl->Count(pList);

    for (i = 0; i < count; i++) {
        pRule = (RuleRE*)pList->pVTbl->Item(pList, i);
        if (pRule && pRule->tokenId == tokenId) {
            *ppfnAction = pRule->action;
            *ppContext = pRule->actionContext;
            return ERR_ECO_SUCCESES;
        }
    }

    return -1;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_SetDefaultTokenId(IEcoLexicalRules1REPtr_t me, char_t* stateName, uint32_t tokenId) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_SetDefaultAction(IEcoLexicalRules1REPtr_t me, char_t* stateName, EcoLexicalAction_t pfnAction, voidptr_t pContext) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_RemoveRule(IEcoLexicalRules1REPtr_t me, uint32_t tokenId) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    uint32_t count = 0, i = 0;
    IEcoList1* pList = 0;

    /* Проверка указателя */
    if (me == 0 || pCMe->m_pRulesList == 0) {
        return ERR_ECO_POINTER;
    }

    pList = pCMe->m_pRulesList;
    count = pList->pVTbl->Count(pList);

    for (i = 0; i < count; i++) {
        pRule = (RuleRE*)pList->pVTbl->Item(pList, i);
        if (pRule && pRule->tokenId == tokenId) {
            if (pRule->pStartState) pRule->pStartState->pVTbl->Release(pRule->pStartState);
            if (pRule->pNFA) pRule->pNFA->pVTbl->Release(pRule->pNFA);
            if (pRule->pAcceptingStates) pRule->pAcceptingStates->pVTbl->Release(pRule->pAcceptingStates);
            if (pRule->pattern) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pRule->pattern);
            if (pRule->stateName) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pRule->stateName);
            if (pRule->pRegex) pRule->pRegex->pVTbl->Release(pRule->pRegex);

            pList->pVTbl->RemoveAt(pList, i);
            return ERR_ECO_SUCCESES;
        }
    }

    return -1;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_Clear(IEcoLexicalRules1REPtr_t me) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    RuleRE* pRule = 0;
    uint32_t count = 0, i = 0;
    IEcoList1* pList = 0;

    if (me == 0 || pCMe->m_pRulesList == 0) {
        return ERR_ECO_POINTER;
    }
	
    pList = pCMe->m_pRulesList;
    count = pList->pVTbl->Count(pList);
	
    for (i = 0; i < count; i++) {
        pRule = (RuleRE*)pList->pVTbl->Item(pList, i);
        if (pRule) {
			if (pRule->pAcceptingStates) {
                pRule->pAcceptingStates->pVTbl->Release(pRule->pAcceptingStates);
            }
            if (pRule->pNFA) {
                pRule->pNFA->pVTbl->Release(pRule->pNFA);
            }
            if (pRule->pStartState) {
                pRule->pStartState->pVTbl->Release(pRule->pStartState);
            }
            if (pRule->pattern) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pRule->pattern);
            }
            if (pRule->stateName) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pRule->stateName);
            }
			if (pRule->pRegex) {
				pRule->pRegex->pVTbl->Release(pRule->pRegex);
			}
		}
    }

    pList->pVTbl->Clear(pList);

	return ERR_ECO_SUCCESES;
}

/* Вспомогательная функция – получение кода символа из события */
static void GetSymbolsFromEvent(IEcoFSM1Event* pEvent, uint8_t* chars, int* count) {
    IEcoList1* pSymbolSets = pEvent->pVTbl->get_SymbolSets(pEvent);
    uint32_t numSets;
	uint32_t i = 0;
	*count = 0;

    if (!pSymbolSets) {
        return;
    }
    
	numSets = pSymbolSets->pVTbl->Count(pSymbolSets);
    
	for (i = 0; i < numSets; i++) {
		int isComplement, ch;
        IEcoFL1SymbolSet* pSet = (IEcoFL1SymbolSet*)pSymbolSets->pVTbl->Item(pSymbolSets, i);
        
		if (!pSet) {
			continue;
		}

        isComplement = pSet->pVTbl->IsComplement(pSet);
        if (isComplement) {
            for (ch = 0; ch < 256 && *count < 256; ch++) {
                chars[(*count)++] = (uint8_t)ch;
            }
        } else {
            for (ch = 0; ch < 256 && *count < 256; ch++) {
                if (pSet->pVTbl->IsExist(pSet, (byte_t*)&ch, 1, 0)) {
                    chars[(*count)++] = (uint8_t)ch;
                }
            }
        }
    }
}

/* Вспомогательная функция: проверяет, содержит ли событие данный символ */
static bool_t EventContainsChar(IEcoFSM1Event* pEvent, uint8_t ch) {
	IEcoList1* pSymbolSets;
	uint32_t numSets, i;

    if (!pEvent || pEvent->pVTbl->IsNull(pEvent)) {
		return 0;
	}

    pSymbolSets = pEvent->pVTbl->get_SymbolSets(pEvent);
    if (!pSymbolSets) {
		return 0;
	}

    numSets = pSymbolSets->pVTbl->Count(pSymbolSets);
    for (i = 0; i < numSets; i++) {
		bool_t isComplement;
        IEcoFL1SymbolSet* pSet = (IEcoFL1SymbolSet*)pSymbolSets->pVTbl->Item(pSymbolSets, i);
        
		if (!pSet) {
			continue;
		}

        isComplement = pSet->pVTbl->IsComplement(pSet);
        if (isComplement) {
            return 1;       
        }

        if (pSet->pVTbl->IsExist(pSet, (byte_t*)&ch, 1, 0)) {
            return 1;
        }
    }
    return 0;
}

/* Вспомогательная функция: проверяет, совпадают ли два события по набору символов */
static bool_t EventsHaveSameSymbols(IEcoFSM1Event* ev1, IEcoFSM1Event* ev2) {
    uint8_t sym1[256], sym2[256];
    int cnt1 = 0, cnt2 = 0;
	int i = 0, j = 0;
	
	if (!ev1 || !ev2) {
		return 0;
	}

    if (ev1 == ev2) {
		return 1;
	}

    GetSymbolsFromEvent(ev1, sym1, &cnt1);
    GetSymbolsFromEvent(ev2, sym2, &cnt2);

    if (cnt1 != cnt2) {
		return 0;
	}

    for (i = 0; i < cnt1; i++) {
        bool_t found = 0;
        for (j = 0; j < cnt2; j++) {
            if (sym1[i] == sym2[j]) { 
				found = 1; 
				break; 
			}
        }
        if (!found) {
			return 0;
		}
    }
    return 1;
}

/*
 *
 * <summary>
 *   Вспомогательная функция для построения супер-автомата из всех правил
 * </summary>
 *
 * <description>
 *   Собирает все NFA из правил в один супер-автомат и сохраняет информацию о финальных состояниях
 * </description>
 *
 */
static int16_t BuildSuperNFA(CEcoBLR1RE_F82A88F6* pCMe) {
    RuleRE* pRule = 0;
	IEcoList1* pSuperStates = 0;
    IEcoFSM1State* pState = 0;
    IEcoFSM1State* pNewState = 0;
    FinalStateInfo* pInfo = 0;
    IEcoFSM1* pFSMFactory = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoFSM1Event* pEpsilonEvent = 0;
    IEcoFSM1StateMachine* pSuperNFA = 0;
    IEcoFSM1State* pSuperStartState = 0;
    IEcoList1* pRulesList = pCMe->m_pRulesList;
    IEcoList1* pRuleStates = 0;
    IEcoList1* pRuleTransitions = 0;
    IEcoFSM1State** ppStateMap = 0;
    int16_t result = 0;
    uint32_t count = 0, i = 0, j = 0, k = 0, stateCount = 0, transCount = 0;
    uint32_t ruleIndex;

    if (!pCMe || !pRulesList || !pCMe->m_pFinalStateAttrs) {
        return ERR_ECO_POINTER;
    }

    if (pCMe->m_pSuperNFA) {
        pCMe->m_pSuperNFA->pVTbl->Release(pCMe->m_pSuperNFA);
        pCMe->m_pSuperNFA = 0;
    }
    if (pCMe->m_pFinalStateAttrs) {
        uint32_t infoCount = pCMe->m_pFinalStateAttrs->pVTbl->Count(pCMe->m_pFinalStateAttrs);
        for (i = 0; i < infoCount; i++) {
            pInfo = (FinalStateInfo*)pCMe->m_pFinalStateAttrs->pVTbl->Item(pCMe->m_pFinalStateAttrs, i);
            if (pInfo) {
                if (pInfo->pState) pInfo->pState->pVTbl->Release(pInfo->pState);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pInfo);
            }
        }
        pCMe->m_pFinalStateAttrs->pVTbl->Clear(pCMe->m_pFinalStateAttrs);
    }

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || !pIBus) {
		return -1;
	}

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFSM1, 0, &IID_IEcoFSM1, (void**)&pFSMFactory);
    pIBus->pVTbl->Release(pIBus);
    if (result != 0 || !pFSMFactory) {
		return -1;
	}

    pSuperNFA = pFSMFactory->pVTbl->CreateStateMachine(pFSMFactory, "SuperNFA");
    if (!pSuperNFA) {
        pFSMFactory->pVTbl->Release(pFSMFactory);
        return -1;
    }

    pEpsilonEvent = pSuperNFA->pVTbl->AddEvent(pSuperNFA, "ε", -1, 1);
    pSuperStartState = pSuperNFA->pVTbl->AddState(pSuperNFA, "SuperStart");
    if (pSuperStartState) pSuperStartState->pVTbl->set_Initial(pSuperStartState, 1);

    count = pRulesList->pVTbl->Count(pRulesList);

    for (ruleIndex = 0; ruleIndex < count; ruleIndex++) {
        pRule = (RuleRE*)pRulesList->pVTbl->Item(pRulesList, ruleIndex);
        if (!pRule || !pRule->pNFA) continue;

        pRuleStates = pRule->pNFA->pVTbl->get_States(pRule->pNFA);
        if (!pRuleStates) {
			continue;
		}

        stateCount = pRuleStates->pVTbl->Count(pRuleStates);
        ppStateMap = (IEcoFSM1State**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, stateCount * sizeof(IEcoFSM1State*));
        if (!ppStateMap) {
			continue;
		}
        memset(ppStateMap, 0, stateCount * sizeof(IEcoFSM1State*));

        for (j = 0; j < stateCount; j++) {
            char_t newName[256];

            pState = (IEcoFSM1State*)pRuleStates->pVTbl->Item(pRuleStates, j);
            if (!pState) {
				continue;
			}

            sprintf(newName, "R%u_S%u", ruleIndex, j);

            pNewState = pSuperNFA->pVTbl->AddState(pSuperNFA, newName);
            if (!pNewState) {
				continue;
			}

            if (pState->pVTbl->IsInitial(pState)) pNewState->pVTbl->set_Initial(pNewState, 1);
            if (pState->pVTbl->IsFinal(pState))   pNewState->pVTbl->set_Final(pNewState, 1);

            ppStateMap[j] = pNewState;

            if (pState == pRule->pStartState) {
                pSuperNFA->pVTbl->AddTransition(pSuperNFA, pEpsilonEvent, pSuperStartState, pNewState);
            }
        }

        pRuleTransitions = pRule->pNFA->pVTbl->get_Transitions(pRule->pNFA);
        if (pRuleTransitions) {
            transCount = pRuleTransitions->pVTbl->Count(pRuleTransitions);
            for (j = 0; j < transCount; j++) {
				IEcoFSM1State *src, *tgt;
                IEcoFSM1Event* ev;
                IEcoFSM1State *newSrc = 0, *newTgt = 0;
                IEcoFSM1Transition* tr = (IEcoFSM1Transition*)pRuleTransitions->pVTbl->Item(pRuleTransitions, j);
               
				if (!tr) {
					continue;
				}

                src = tr->pVTbl->get_Source(tr);
                tgt = tr->pVTbl->get_Target(tr);
                ev  = tr->pVTbl->get_Event(tr);

                for (k = 0; k < stateCount; k++) {
                    if ((IEcoFSM1State*)pRuleStates->pVTbl->Item(pRuleStates, k) == src) newSrc = ppStateMap[k];
                    if ((IEcoFSM1State*)pRuleStates->pVTbl->Item(pRuleStates, k) == tgt) newTgt = ppStateMap[k];
                }

                if (newSrc && newTgt && ev) {
                    pSuperNFA->pVTbl->AddTransition(pSuperNFA, ev, newSrc, newTgt);
                }
            }
        }

        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ppStateMap);
    }

    pSuperStates = pSuperNFA->pVTbl->get_States(pSuperNFA);
    if (pSuperStates) {
        uint32_t superCount = pSuperStates->pVTbl->Count(pSuperStates);
        for (i = 0; i < superCount; i++) {
			char_t* name;

            pState = (IEcoFSM1State*)pSuperStates->pVTbl->Item(pSuperStates, i);
            if (!pState || !pState->pVTbl->IsFinal(pState)) continue;

            name = pState->pVTbl->get_Name(pState);
            if (name && name[0] == 'R') {
                if (sscanf(name, "R%u_", &ruleIndex) == 1 && ruleIndex < count) {
                    pRule = (RuleRE*)pRulesList->pVTbl->Item(pRulesList, ruleIndex);
                    if (pRule) {
                        pInfo = (FinalStateInfo*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(FinalStateInfo));
                        if (pInfo) {
                            memset(pInfo, 0, sizeof(FinalStateInfo));
                            pInfo->pState = pState;
                            pState->pVTbl->AddRef(pState);
                            pInfo->tokenId = pRule->tokenId;
                            pInfo->priority = pRule->priority;     
                            pInfo->channel = pRule->channel;
                            pInfo->pfnAction = pRule->action;
                            pInfo->pActionContext = pRule->actionContext;
                            pInfo->ruleIndex = ruleIndex;

                            pCMe->m_pFinalStateAttrs->pVTbl->Add(pCMe->m_pFinalStateAttrs, pInfo);
                        }
                    }
                }
            }
        }
    }

    pCMe->m_pSuperNFA = pSuperNFA;
    pFSMFactory->pVTbl->Release(pFSMFactory);

    return ERR_ECO_SUCCESES;
}

/* Вспомогательная функция, вычисляющая ε-замыкание для состояния S */
static void ComputeEpsilonClosure(CEcoBLR1RE_F82A88F6* pCMe, IEcoFSM1StateMachine* pNFA, IEcoList1* pAllTrans, IEcoList1* set) {
    IEcoFSM1Event* ev;
    IEcoFSM1Transition* tr;
    IEcoFSM1State *st, *target;
    bool_t found, changed;
	uint32_t i, j, k, setSize;
	uint32_t curCount, transCount;

    if (!pAllTrans) {
		return;
	}

    do {
        setSize = set->pVTbl->Count(set);
        changed = 0;
        transCount = pAllTrans->pVTbl->Count(pAllTrans);
        for (i = 0; i < setSize; i++) {
            st = (IEcoFSM1State*)set->pVTbl->Item(set, i);
            for (j = 0; j < transCount; j++) {
                tr = (IEcoFSM1Transition*)pAllTrans->pVTbl->Item(pAllTrans, j);
                ev = tr->pVTbl->get_Event(tr);
                if (ev && ev->pVTbl->IsNull(ev) && tr->pVTbl->get_Source(tr) == st) {
                    target = tr->pVTbl->get_Target(tr);
                    found = 0;
                    curCount = set->pVTbl->Count(set);
                    for (k = 0; k < curCount; k++) {
                        if ((IEcoFSM1State*)set->pVTbl->Item(set, k) == target) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        set->pVTbl->Add(set, target);
                        target->pVTbl->AddRef(target);
                        changed = 1;
                    }
                }
            }
        }
    } while (changed);
}

/* Вспомогательная функция, проверяющая нет ли уже существующего состояния DFA эквивалентного данному множеству состояний NFA */
static DFAState* FindDFAState(CEcoBLR1RE_F82A88F6* pCMe, IEcoList1* nfaSet) {
    DFAState* ds;
    IEcoFSM1State* st;
    bool_t same, found;
    uint32_t i, j, k, dsCount;
	uint32_t dfaCount, nfaCount;

    dfaCount = pCMe->m_pDFAStates->pVTbl->Count(pCMe->m_pDFAStates);
    nfaCount = nfaSet->pVTbl->Count(nfaSet);
    for (i = 0; i < dfaCount; i++) {
        ds = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
        if (ds->nfaStates->pVTbl->Count(ds->nfaStates) != nfaCount) {
			continue;
		}
        same = 1;
        for (j = 0; j < nfaCount; j++) {
            st = (IEcoFSM1State*)nfaSet->pVTbl->Item(nfaSet, j);
            found = 0;
            dsCount = ds->nfaStates->pVTbl->Count(ds->nfaStates);
            for (k = 0; k < dsCount; k++) {
                if ((IEcoFSM1State*)ds->nfaStates->pVTbl->Item(ds->nfaStates, k) == st) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                same = 0;
                break;
            }
        }
        if (same) {
			return ds;
		}
    }
    return 0;
}

/* Вспомогательная функция, создающая состояние DFA эквивалентное данному множеству состояний NFA */
static DFAState* CreateDFAState(CEcoBLR1RE_F82A88F6* pCMe, IEcoList1* nfaSet) {
    DFAState* ds = 0;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = 0;
    uint32_t i, j, nfaCount, finalCount;

    if (!pCMe || !nfaSet) {
		return 0;
	}

    ds = (DFAState*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(DFAState));
    if (!ds) {
		return 0;
	}
    memset(ds, 0, sizeof(DFAState));

    ds->nfaStates = nfaSet;
    nfaSet->pVTbl->AddRef(nfaSet);

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result == 0 && pIBus) {
        pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&ds->acceptingTokens);
        pIBus->pVTbl->Release(pIBus);
    }

    if (!ds->acceptingTokens) {
        if (ds->nfaStates) ds->nfaStates->pVTbl->Release(ds->nfaStates);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds);
        return 0;
    }

	ds->transTable = (int32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(int32_t));
    if (!ds->transTable) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds);
        return 0;
    }
    for (i = 0; i < 256; i++) {
		ds->transTable[i] = -1;
	}

    ds->isAccepting = 0;
    nfaCount = nfaSet->pVTbl->Count(nfaSet);
    finalCount = pCMe->m_pFinalStateAttrs->pVTbl->Count(pCMe->m_pFinalStateAttrs);

    for (i = 0; i < nfaCount; i++) {
        IEcoFSM1State* st = (IEcoFSM1State*)nfaSet->pVTbl->Item(nfaSet, i);
        if (!st || !st->pVTbl->IsFinal(st)) {
			continue;
		}

        for (j = 0; j < finalCount; j++) {
            FinalStateInfo* fi = (FinalStateInfo*)pCMe->m_pFinalStateAttrs->pVTbl->Item(pCMe->m_pFinalStateAttrs, j);
            if (fi && fi->pState == st) {
                AcceptingToken* token = (AcceptingToken*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(AcceptingToken));
                if (token) {
                    memset(token, 0, sizeof(AcceptingToken));
                    token->tokenId = fi->tokenId;
                    token->priority = fi->priority;
                    token->ruleIndex = fi->ruleIndex;
                    token->channel = fi->channel;
                    token->pfnAction = fi->pfnAction;
                    token->pActionContext = fi->pActionContext;

                    ds->acceptingTokens->pVTbl->Add(ds->acceptingTokens, token);
                    ds->isAccepting = 1;
                }
                break;
            }
        }
    }

    return ds;
}

static void SelectBestAcceptingToken(IEcoList1* acceptingTokens, AcceptingToken* pBest) {
	AcceptingToken* best = 0;
    uint32_t i;
    uint32_t count = acceptingTokens ? acceptingTokens->pVTbl->Count(acceptingTokens) : 0;
    
    if (pBest) {
		memset(pBest, 0, sizeof(AcceptingToken));
	}

    for (i = 0; i < count; i++) {
        AcceptingToken* t = (AcceptingToken*)acceptingTokens->pVTbl->Item(acceptingTokens, i);
        if (!t) {
			continue;
		}

        if (best == 0 || t->priority < best->priority || (t->priority == best->priority && t->ruleIndex < best->ruleIndex)) {
            best = t;
        }
    }

    if (best && pBest) {
        memcpy(pBest, best, sizeof(AcceptingToken));
    }
}

/*
 *
 * <summary>
 *   Вспомогательная функция для преобразования NFA в DFA
 * </summary>
 *
 * <description>
 *   Преобразует супер-NFA в DFA
 * </description>
 *
 */
static int16_t ConvertNFAToDFA(CEcoBLR1RE_F82A88F6* pCMe) {
    DFAState* startDFA;
    IEcoFSM1State* pStartNFA;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoList1 *pAllTrans = 0, *pSuperStates, *startSet = 0;
    int32_t** superTrans = 0;
    IEcoList1** pEpsilonClosures = 0;
    int16_t result;
    uint32_t i, s, t, oldCount, superCount, tCount, processed = 0;

    if (!pCMe || !pCMe->m_pSuperNFA || !pCMe->m_pDFAStates) {
        return ERR_ECO_POINTER;
    }

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || !pIBus) {
        return result;
    }

    oldCount = pCMe->m_pDFAStates->pVTbl->Count(pCMe->m_pDFAStates);
    for (i = 0; i < oldCount; i++) {
        DFAState* ds = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
        if (ds) {
            if (ds->nfaStates) {
				ds->nfaStates->pVTbl->Release(ds->nfaStates);
			}
            if (ds->acceptingTokens) {
				ds->acceptingTokens->pVTbl->Release(ds->acceptingTokens);
			}
            if (ds->transTable) {
				pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds->transTable);
			}
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds);
        }
    }
    pCMe->m_pDFAStates->pVTbl->Clear(pCMe->m_pDFAStates);

    pAllTrans = pCMe->m_pSuperNFA->pVTbl->get_Transitions(pCMe->m_pSuperNFA);
    pSuperStates = pCMe->m_pSuperNFA->pVTbl->get_States(pCMe->m_pSuperNFA);
    superCount = pSuperStates->pVTbl->Count(pSuperStates);

    superTrans = (int32_t**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, superCount * sizeof(int32_t*));
    if (!superTrans) {
		goto cleanup;
	}

    for (s = 0; s < superCount; s++) {
        superTrans[s] = (int32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(int32_t));
        if (!superTrans[s]) {
			goto cleanup;
		}
        memset(superTrans[s], -1, 256 * sizeof(int32_t));
    }

    tCount = pAllTrans->pVTbl->Count(pAllTrans);
    for (t = 0; t < tCount; t++) {
        IEcoFSM1Transition* tr = (IEcoFSM1Transition*)pAllTrans->pVTbl->Item(pAllTrans, t);
        IEcoFSM1Event* ev = tr->pVTbl->get_Event(tr);
        if (ev && !ev->pVTbl->IsNull(ev)) {
			uint32_t ch = 0; 
            uint32_t srcIdx = pSuperStates->pVTbl->IndexOf(pSuperStates, tr->pVTbl->get_Source(tr));
            uint32_t tgtIdx = pSuperStates->pVTbl->IndexOf(pSuperStates, tr->pVTbl->get_Target(tr));

            for (ch = 0; ch < 256; ch++) {
                if (EventContainsChar(ev, (uint8_t)ch)) {
                    superTrans[srcIdx][ch] = (int32_t)tgtIdx;
                }
            }
        }
    }

    pEpsilonClosures = (IEcoList1**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, superCount * sizeof(IEcoList1*));
    if (!pEpsilonClosures) {
		goto cleanup;
	}
    memset(pEpsilonClosures, 0, superCount * sizeof(IEcoList1*));

    for (s = 0; s < superCount; s++) {
		IEcoFSM1State* st;
        IEcoList1* closure = 0;

        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&closure);
        if (result != 0 || !closure) {
			goto cleanup;
		}

        st = (IEcoFSM1State*)pSuperStates->pVTbl->Item(pSuperStates, s);
        closure->pVTbl->Add(closure, st);
        st->pVTbl->AddRef(st);

        ComputeEpsilonClosure(pCMe, pCMe->m_pSuperNFA, pAllTrans, closure);
        pEpsilonClosures[s] = closure;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&startSet);
    if (result != 0 || !startSet) {
		goto cleanup;
	}

    pStartNFA = FindStartState(pCMe->m_pSuperNFA);
    if (pStartNFA) {
        startSet->pVTbl->Add(startSet, pStartNFA);
        pStartNFA->pVTbl->AddRef(pStartNFA);
    }
    ComputeEpsilonClosure(pCMe, pCMe->m_pSuperNFA, pAllTrans, startSet);

    startDFA = CreateDFAState(pCMe, startSet);
    if (!startDFA) {
		goto cleanup;
	}

    pCMe->m_pDFAStates->pVTbl->Add(pCMe->m_pDFAStates, startDFA);
    pCMe->m_startStateIdx = 0;

    while (processed < pCMe->m_pDFAStates->pVTbl->Count(pCMe->m_pDFAStates)) {
		uint32_t ch = 0;
        DFAState* cur = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, processed);

        for (ch = 0; ch < 256; ch++) {
			uint32_t nfaCount, j;
            IEcoList1* pNextSet = 0;
            
			result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pNextSet);
            if (result != 0 || !pNextSet) {
				continue;
			}

            nfaCount = cur->nfaStates->pVTbl->Count(cur->nfaStates);
			for (j = 0; j < nfaCount; j++) {
                IEcoFSM1State* st = (IEcoFSM1State*)cur->nfaStates->pVTbl->Item(cur->nfaStates, j);
                uint32_t srcIdx = pSuperStates->pVTbl->IndexOf(pSuperStates, st);
                int32_t tgtIdx = superTrans[srcIdx][ch];

                if (tgtIdx >= 0) {
                    uint32_t m = 0;
                    IEcoList1* tgtClosure = pEpsilonClosures[tgtIdx];
                    uint32_t tc = tgtClosure->pVTbl->Count(tgtClosure);

                    for (m = 0; m < tc; m++) {
						bool_t found = 0;
						uint32_t l = 0;
                        IEcoFSM1State* tgtSt = (IEcoFSM1State*)tgtClosure->pVTbl->Item(tgtClosure, m);
                        uint32_t mcount = pNextSet->pVTbl->Count(pNextSet);

                        for (l = 0; l < mcount; l++) {
                            if ((IEcoFSM1State*)pNextSet->pVTbl->Item(pNextSet, l) == tgtSt) {
                                found = 1;
                                break;
                            }
                        }

                        if (!found) {
                            pNextSet->pVTbl->Add(pNextSet, tgtSt);
                            tgtSt->pVTbl->AddRef(tgtSt);
                        }
                    }
                }
            }

            if (pNextSet->pVTbl->Count(pNextSet) > 0) {
                DFAState* existing = FindDFAState(pCMe, pNextSet);
                if (!existing) {
                    DFAState* newDS = CreateDFAState(pCMe, pNextSet);
                    if (newDS) {
                        pCMe->m_pDFAStates->pVTbl->Add(pCMe->m_pDFAStates, newDS);
                        existing = newDS;
                    }
                }
                if (existing) {
                    cur->transTable[ch] = (int32_t)pCMe->m_pDFAStates->pVTbl->IndexOf(pCMe->m_pDFAStates, existing);
                }
            }

            pNextSet->pVTbl->Release(pNextSet);
        }
        processed++;
    }

    if (pEpsilonClosures) {
        for (s = 0; s < superCount; s++) {
            if (pEpsilonClosures[s]) {
                pEpsilonClosures[s]->pVTbl->Release(pEpsilonClosures[s]);
            }
        }
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pEpsilonClosures);
    }

cleanup:
    if (superTrans) {
        for (s = 0; s < superCount; s++) {
            if (superTrans[s]) {
				pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, superTrans[s]);
			}
        }
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, superTrans);
    }
    if (pAllTrans) {
		pAllTrans->pVTbl->Release(pAllTrans);
	}
    if (pIBus) {
		pIBus->pVTbl->Release(pIBus);
	}

    return ERR_ECO_SUCCESES;
}

/*
 * <summary>
 * Вспомогательная функция для минимизации DFA
 * </summary>
 *
 * <description>
 * Минимизирует DFA табличным методом (Table-filling algorithm)
 * </description>
 */
static int16_t MinimizeDFA(CEcoBLR1RE_F82A88F6* pCMe) {
	IEcoList1* pNewDFAStates = 0;
	IEcoInterfaceBus1* pIBus = 0;
	bool_t* distinguishable;
	uint32_t *newGroup, *groupRep;
	bool_t changed;
    int16_t result;
	uint32_t i, j, g, dfaCount, numGroups = 0;

    if (pCMe == 0 || pCMe->m_pDFAStates == 0) {
        return ERR_ECO_POINTER;
    }

    dfaCount = pCMe->m_pDFAStates->pVTbl->Count(pCMe->m_pDFAStates);
    if (dfaCount <= 1) {
        return ERR_ECO_SUCCESES; 
    }

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || !pIBus) {
		return result;
	}

    distinguishable = (bool_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * dfaCount * sizeof(bool_t));
    if (!distinguishable) {
        pIBus->pVTbl->Release(pIBus);
        return ERR_ECO_OUTOFMEMORY;
    }
    memset(distinguishable, 0, dfaCount * dfaCount * sizeof(bool_t));

    for (i = 0; i < dfaCount; i++) {
        DFAState* ds1 = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
        for (j = i + 1; j < dfaCount; j++) {
            DFAState* ds2 = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, j);

            bool_t diff = (ds1->isAccepting != ds2->isAccepting);
            if (!diff && ds1->isAccepting) {
                AcceptingToken best1 = {0}, best2 = {0};
                SelectBestAcceptingToken(ds1->acceptingTokens, &best1);
                SelectBestAcceptingToken(ds2->acceptingTokens, &best2);

                if (best1.priority != best2.priority || best1.ruleIndex != best2.ruleIndex) {
                    diff = 1;
                }
            }
            distinguishable[i * dfaCount + j] = diff;
            distinguishable[j * dfaCount + i] = diff;
        }
    }

    do {
        changed = 0;
        for (i = 0; i < dfaCount; i++) {
            for (j = i + 1; j < dfaCount; j++) {
				DFAState *ds1, *ds2;
				uint32_t ch = 0;

                if (distinguishable[i * dfaCount + j]) {
					continue;
				}

                ds1 = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
                ds2 = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, j);

                for (ch = 0; ch < 256; ch++) {
                    int32_t t1 = ds1->transTable[ch];
                    int32_t t2 = ds2->transTable[ch];

                    if (t1 != t2) {
                        if (t1 < 0 || t2 < 0 || distinguishable[t1 * dfaCount + t2]) {
                            distinguishable[i * dfaCount + j] = 1;
                            distinguishable[j * dfaCount + i] = 1;
                            changed = 1;
                            break;
                        }
                    }
                }
            }
        }
    } while (changed);

    newGroup = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(uint32_t));
    if (!newGroup) {
		goto cleanup;
	}

    for (i = 0; i < dfaCount; i++) {
		newGroup[i] = 0xFFFFFFFFU;
	}

    for (i = 0; i < dfaCount; i++) {
        if (newGroup[i] != 0xFFFFFFFFU) {
			continue;
		}
        newGroup[i] = numGroups;
        for (j = i + 1; j < dfaCount; j++) {
            if (!distinguishable[i * dfaCount + j]) {
                newGroup[j] = numGroups;
            }
        }
        numGroups++;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pNewDFAStates);
    if (result != 0 || !pNewDFAStates) {
		goto cleanup;
	}

    groupRep = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, numGroups * sizeof(uint32_t));
    if (!groupRep) {
		goto cleanup;
	}
    for (i = 0; i < numGroups; i++) {
		groupRep[i] = 0xFFFFFFFFU;
	}

    for (i = 0; i < dfaCount; i++) {
        g = newGroup[i];
        if (groupRep[g] == 0xFFFFFFFFU || i < groupRep[g]) {
            groupRep[g] = i;
        }
    }

    for (g = 0; g < numGroups; g++) {
		uint32_t ch = 0;
        uint32_t repIdx = groupRep[g];
        DFAState* rep = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, repIdx);

        DFAState* newDS = (DFAState*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(DFAState));
        if (!newDS) {
			goto cleanup;
		}
        memset(newDS, 0, sizeof(DFAState));

        newDS->isAccepting = rep->isAccepting;
        newDS->nfaStates = 0;                
        newDS->transTable = (int32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(int32_t));
        if (!newDS->transTable) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, newDS);
            goto cleanup;
        }

        for (ch = 0; ch < 256; ch++) {
            int32_t oldTarget = rep->transTable[ch];
            newDS->transTable[ch] = (oldTarget >= 0) ? (int32_t)newGroup[oldTarget] : -1;
        }

        if (rep->acceptingTokens) {
            result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&newDS->acceptingTokens);
            if (result == 0 && newDS->acceptingTokens) {
				uint32_t t = 0;
                uint32_t cnt = rep->acceptingTokens->pVTbl->Count(rep->acceptingTokens);
                for (t = 0; t < cnt; t++) {
                    AcceptingToken* src = (AcceptingToken*)rep->acceptingTokens->pVTbl->Item(rep->acceptingTokens, t);
                    AcceptingToken* dst = (AcceptingToken*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(AcceptingToken));
                    if (dst) {
                        memcpy(dst, src, sizeof(AcceptingToken));
                        newDS->acceptingTokens->pVTbl->Add(newDS->acceptingTokens, dst);
                    }
                }
            }
        }

        pNewDFAStates->pVTbl->Add(pNewDFAStates, newDS);
    }

    for (i = 0; i < dfaCount; i++) {
        DFAState* ds = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
        if (ds) {
            if (ds->nfaStates) {
				ds->nfaStates->pVTbl->Release(ds->nfaStates);
			}
            if (ds->acceptingTokens) {
				ds->acceptingTokens->pVTbl->Release(ds->acceptingTokens);
			}
            if (ds->transTable) {
				pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds->transTable);
			}
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds);
        }
    }
    pCMe->m_pDFAStates->pVTbl->Clear(pCMe->m_pDFAStates);
    pCMe->m_pDFAStates->pVTbl->Release(pCMe->m_pDFAStates);

    pCMe->m_pDFAStates = pNewDFAStates;

    if (pCMe->m_startStateIdx < dfaCount) {
        pCMe->m_startStateIdx = newGroup[pCMe->m_startStateIdx];
    }

cleanup:
    if (distinguishable) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, distinguishable);
	}
    if (newGroup) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, newGroup);
	}
    if (groupRep) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, groupRep);
	}
    if (pIBus) {
		pIBus->pVTbl->Release(pIBus);
	}

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Вспомогательная функция для сжатия таблицы
 * </summary>
 *
 * <description>
 *   Формирует таблицу переходов в формате IEcoLexicalData1
 * </description>
 *
 */

static int16_t CompressToIEcoLexicalData1(CEcoBLR1RE_F82A88F6* pCMe, IEcoLexicalData1Ptr_t* ppIData) {
    DFAState** pStates = 0;
    CEcoBLD1_F82A88F6* pLexData = 0;
    IEcoList1* pDFAStates = pCMe->m_pDFAStates;
    EcoLexicalStateClassInfo* stateClassInfo = 0;
    int32_t** fullTrans = 0;
    uint32_t* signatures = 0;
    int32_t* transitionMatrix = 0;
    uint16_t *globalAlphabetMap = 0, *stateClassMap = 0, *charToClass = 0;
	uint32_t dfaCount = 0;
    int16_t result = ERR_ECO_SUCCESES;
    uint32_t i, j, s, matrixSize;
    uint16_t alphabetClassesCount = 0;

    if (!pCMe || !pDFAStates || !ppIData) {
        return ERR_ECO_POINTER;
    }
    *ppIData = 0;

    dfaCount = pDFAStates->pVTbl->Count(pDFAStates);
    if (dfaCount == 0) {
		return -1;
	}

    pStates = (DFAState**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(DFAState*));
    if (!pStates) {
		return ERR_ECO_OUTOFMEMORY;
	}
    for (i = 0; i < dfaCount; i++) {
        pStates[i] = (DFAState*)pDFAStates->pVTbl->Item(pDFAStates, i);
    }

    fullTrans = (int32_t**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(int32_t*));
    if (!fullTrans) {
		goto cleanup;
	}

    for (i = 0; i < dfaCount; i++) {
        fullTrans[i] = (int32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(int32_t));
        if (!fullTrans[i]) {
			goto cleanup;
		}
        for (j = 0; j < 256; j++) {
			fullTrans[i][j] = -1;
		}
    }

    for (i = 0; i < dfaCount; i++) {
		DFAState* state = pStates[i];
		for (j = 0; j < 256; j++) {
			fullTrans[i][j] = state->transTable[j];
		}
	}

    signatures = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(uint32_t));
    if (!signatures) {
		goto cleanup;
	}
    for (i = 0; i < 256; i++) {
        uint32_t hash = 2166136261U;
        for (j = 0; j < dfaCount; j++) {
            hash = (hash ^ (uint32_t)(fullTrans[j][i] + 1)) * 16777619U;
        }
        signatures[i] = hash;
    }

    charToClass = (uint16_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(uint16_t));
    if (!charToClass) {
		goto cleanup;
	}

    alphabetClassesCount = 0;
    for (i = 0; i < 256; i++) {
        uint16_t classId = 0xFFFF;
        for (j = 0; j < i; j++) {
            if (signatures[j] == signatures[i]) {
                classId = charToClass[j];
                break;
            }
        }
        if (classId == 0xFFFF) {
			classId = alphabetClassesCount++;
		}
        charToClass[i] = classId;
    }

    globalAlphabetMap = (uint16_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(uint16_t));
    if (!globalAlphabetMap) {
		goto cleanup;
	}
    for (i = 0; i < 256; i++) {
		globalAlphabetMap[i] = charToClass[i];
	}

    matrixSize = dfaCount * alphabetClassesCount;
    transitionMatrix = (int32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, matrixSize * sizeof(int32_t));
    if (!transitionMatrix) {
		goto cleanup;
	}

    for (i = 0; i < dfaCount; i++) {
        for (j = 0; j < alphabetClassesCount; j++) {
            int32_t target = -1;
            for (s = 0; s < 256; s++) {
                if (charToClass[s] == j) {
                    target = fullTrans[i][s];
                    break;
                }
            }
            transitionMatrix[i * alphabetClassesCount + j] = target;
        }
    }

    stateClassInfo = (EcoLexicalStateClassInfo*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(EcoLexicalStateClassInfo));
    if (!stateClassInfo) {
		goto cleanup;
	}
    memset(stateClassInfo, 0, dfaCount * sizeof(EcoLexicalStateClassInfo));

    for (i = 0; i < dfaCount; i++) {
        DFAState* state = pStates[i];
        stateClassInfo[i].isFinal = state->isAccepting;
        if (state->isAccepting && state->acceptingTokens) {
            AcceptingToken best = {0};
            SelectBestAcceptingToken(state->acceptingTokens, &best);
            stateClassInfo[i].tokenId = best.tokenId;
            stateClassInfo[i].channelId = best.channel;
            stateClassInfo[i].priority = best.priority;
            stateClassInfo[i].pContext = best.pActionContext;
        }
    }

    stateClassMap = (uint16_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(uint16_t));
    if (!stateClassMap) {
		goto cleanup;
	}
    for (i = 0; i < dfaCount; i++) {
		stateClassMap[i] = (uint16_t)i;
	}

    pLexData = (CEcoBLD1_F82A88F6*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBLD1_F82A88F6));
    if (!pLexData) {
		goto cleanup;
	}

    memcpy(pLexData, &g_xCEcoBLD1_F82A88F6, sizeof(CEcoBLD1_F82A88F6));
    pLexData->m_pVTblIData = &g_xDB2E163758AA4447A843545A8805D3FEVTbl_F82A88F6;
    pLexData->m_cRef = 1;
    pLexData->m_pIMem = pCMe->m_pIMem; 
	if (pLexData->m_pIMem) {
		pLexData->m_pIMem->pVTbl->AddRef(pLexData->m_pIMem);
	}
    pLexData->m_pISys = pCMe->m_pISys; 
	if (pLexData->m_pISys) {
		pLexData->m_pISys->pVTbl->AddRef(pLexData->m_pISys);
	}

    pLexData->m_flags = ECO_LEX_DATA_FL_STATE_CLASSES;
    pLexData->m_initialState = pCMe->m_startStateIdx;
    pLexData->m_version = 1;
    pLexData->m_alphabetClassesCount = alphabetClassesCount;
    pLexData->m_pGlobalAlphabetMap = globalAlphabetMap;
    pLexData->m_stateClassesCount = (uint16_t)dfaCount;
    pLexData->m_pStateClassMap = stateClassMap;
    pLexData->m_totalStatesCount = dfaCount;
    pLexData->m_pTransitionMatrix = transitionMatrix;
    pLexData->m_pStateClassInfoArray = stateClassInfo;

    *ppIData = (IEcoLexicalData1Ptr_t)pLexData;
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
    return ERR_ECO_SUCCESES;

cleanup:
    if (fullTrans) {
        for (i = 0; i < dfaCount; i++) {
			if (fullTrans[i]) {
				pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans[i]);
			}
		}
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans);
    }
    if (pStates) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
	}
    if (signatures) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, signatures);
	}
    if (charToClass) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, charToClass);
	}
    if (globalAlphabetMap) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, globalAlphabetMap);
	}
    if (transitionMatrix) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, transitionMatrix);
	}
    if (stateClassInfo) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, stateClassInfo);
	}
    if (stateClassMap) {
		pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, stateClassMap);
	}
    return ERR_ECO_OUTOFMEMORY;
}

static int16_t ECOCALLMETHOD CEcoBLR1RE_F82A88F6_Compile(IEcoLexicalRules1REPtr_t me, IEcoLexicalData1Ptr_t* ppIData) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
	int16_t result = 0;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

	/* Этап 1: Объединение всех NFA в один */
	result = BuildSuperNFA(pCMe);
    if (result != 0) {
        return result;
    }

	/* Этап 2: Преобразование NFA в DFA */
	result = ConvertNFAToDFA(pCMe);
    if (result != 0) {
        return result;
    }
	
    /* Этап 3: Минимизация DFA табличным методом (Table-filling algorithm) */
	result = MinimizeDFA(pCMe);
	if (result != 0) {
		return result;
	}

    /* Этап 4: Построение таблицы переходов в формате IEcoLexicalData1 */ 
	result = CompressToIEcoLexicalData1(pCMe, ppIData);
	if (result != 0) {
		return result;
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
static int16_t ECOCALLMETHOD initCEcoBLR1RE_F82A88F6(/*in*/ CEcoBLR1RE_F82A88F6Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBLR1RE_F82A88F6* pCMe = (CEcoBLR1RE_F82A88F6*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    /* Storing the pointer to the system interface */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Getting the interface for working with the interface bus */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Getting the component ID for working with memory */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Getting the memory allocator interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);
    /* Check */
    if (result != 0 || pCMe->m_pIMem == 0) {
		pIBus->pVTbl->Release(pIBus);
        pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        return result;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pCMe->m_pRulesList);
	if (result != 0 || pCMe->m_pRulesList == 0) {
		pIBus->pVTbl->Release(pIBus);
        pCMe->m_pIMem->pVTbl->Release(pCMe->m_pIMem);
        pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        return result;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBRE1, 0, &IID_IEcoBRE1, (void**)&pCMe->m_pBRE);
	if (result != 0 || pCMe->m_pBRE == 0) {
        pIBus->pVTbl->Release(pIBus);
        pCMe->m_pRulesList->pVTbl->Release(pCMe->m_pRulesList);
        pCMe->m_pIMem->pVTbl->Release(pCMe->m_pIMem);
        pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        return result;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pCMe->m_pFinalStateAttrs);
    if (result != 0 || pCMe->m_pFinalStateAttrs == 0) {
        pCMe->m_pRulesList->pVTbl->Release(pCMe->m_pRulesList);
		pIBus->pVTbl->Release(pIBus);
		pCMe->m_pIMem->pVTbl->Release(pCMe->m_pIMem);
		pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
		return -1;
    }

	pCMe->m_pSuperNFA = 0;

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pCMe->m_pDFAStates);
	if (result != 0 || pCMe->m_pDFAStates == 0) {
        pCMe->m_pRulesList->pVTbl->Release(pCMe->m_pRulesList);
		pIBus->pVTbl->Release(pIBus);
		pCMe->m_pIMem->pVTbl->Release(pCMe->m_pIMem);
		pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
		pCMe->m_pFinalStateAttrs->pVTbl->Release(pCMe->m_pFinalStateAttrs);
		return -1;
    }

	pCMe->m_startStateIdx = 0;

    /* Freeing */
    pIBus->pVTbl->Release(pIBus);

    return ERR_ECO_SUCCESES;
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
static int16_t ECOCALLMETHOD createCEcoBLR1RE_F82A88F6(/* in */ CEcoBLR1RE_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBLR1RE_F82A88F6(/* in */ CEcoBLR1RE_F82A88F6Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

	if (pCMe == 0) return;

    pIMem = pCMe->m_pIMem;
    if (pIMem == 0) return;

	if (pCMe->m_cRef == 0xFFFFFFFFU) return;
    pCMe->m_cRef = 0xFFFFFFFFU;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
		if (pCMe->m_pDFAStates != 0) {
			pCMe->m_pDFAStates->pVTbl->Release(pCMe->m_pDFAStates);
		}
		if (pCMe->m_pFinalStateAttrs != 0) {
            pCMe->m_pFinalStateAttrs->pVTbl->Release(pCMe->m_pFinalStateAttrs);
        }
		if (pCMe->m_pRulesList != 0) {
			CEcoBLR1RE_F82A88F6_Clear((IEcoLexicalRules1REPtr_t)pCMe);
			pCMe->m_pRulesList->pVTbl->Release(pCMe->m_pRulesList);
		}
		if (pCMe->m_pBRE != 0) {
			pCMe->m_pBRE->pVTbl->Release(pCMe->m_pBRE);
		}
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoLexicalRules1RE Virtual Table */
IEcoLexicalRules1REVTbl g_xD3974ACCEAAB4273A1F0E97557E7B138VTbl_F82A88F6 = {
    CEcoBLR1RE_F82A88F6_QueryInterface,
    CEcoBLR1RE_F82A88F6_AddRef,
    CEcoBLR1RE_F82A88F6_Release,
    CEcoBLR1RE_F82A88F6_AddState,
    CEcoBLR1RE_F82A88F6_get_StatesCount,
    CEcoBLR1RE_F82A88F6_get_StateName,
    CEcoBLR1RE_F82A88F6_AddRuleRE,
    CEcoBLR1RE_F82A88F6_AddRuleObject,
    CEcoBLR1RE_F82A88F6_SetPriority,
    CEcoBLR1RE_F82A88F6_SetChannel,
    CEcoBLR1RE_F82A88F6_SetAction,
    CEcoBLR1RE_F82A88F6_get_Count,
    CEcoBLR1RE_F82A88F6_GetRuleInfo,
    CEcoBLR1RE_F82A88F6_GetRuleObject,
    CEcoBLR1RE_F82A88F6_GetAction,
    CEcoBLR1RE_F82A88F6_SetDefaultTokenId,
    CEcoBLR1RE_F82A88F6_SetDefaultAction,
    CEcoBLR1RE_F82A88F6_RemoveRule,
    CEcoBLR1RE_F82A88F6_Clear,
    CEcoBLR1RE_F82A88F6_Compile
};


/* Object Instance */
CEcoBLR1RE_F82A88F6 g_xCEcoBLR1RE_F82A88F6 = {
    &g_xD3974ACCEAAB4273A1F0E97557E7B138VTbl_F82A88F6,
    initCEcoBLR1RE_F82A88F6,
    createCEcoBLR1RE_F82A88F6,
    deleteCEcoBLR1RE_F82A88F6,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0, /* m_Name */
	0, /* m_pBRE */
	0, /* m_pRulesList */      
	0, /* m_pSuperNFA */
	0, /* m_pFinalStateAttrs */
	0, /* m_pDFAStates */
	0  /* m_startStateIdx */
};
