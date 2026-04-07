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
    pRule->priority = 999999U;
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
    pRule->priority = 999999U;
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

            pList->pVTbl->Remove(pList, i);
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
    IEcoFSM1State* pState = 0;
    IEcoFSM1State* pNewState = 0;
    FinalStateInfo* pInfo = 0;
    IEcoFSM1* pFSMFactory = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoFSM1Event* pEpsilonEvent = 0;
    IEcoFSM1StateMachine* pSuperNFA = 0;
    IEcoFSM1State* pSuperStartState = 0;
    IEcoList1 *pRuleAcceptingStates = 0;
    IEcoList1* pRulesList = pCMe->m_pRulesList;
    IEcoList1* pRuleStates = 0;
    IEcoList1* pRuleTransitions = 0;
	IEcoList1* pSuperStates;
    IEcoFSM1Transition* pTrans = 0;
    IEcoFSM1Event* pEvent = 0;
    IEcoFSM1State* pSource = 0;
    IEcoFSM1State* pTarget = 0;
    IEcoFSM1State** ppStateMap = 0; 
    int16_t result = 0;
    uint32_t count = 0, i = 0, j = 0, k = 0, stateCount = 0, transCount = 0;
    uint32_t mapSize = 0;

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
                if (pInfo->pState) {
					pInfo->pState->pVTbl->Release(pInfo->pState);
                }
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pInfo);
            }
        }
        pCMe->m_pFinalStateAttrs->pVTbl->Clear(pCMe->m_pFinalStateAttrs);
    }

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        return -1;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFSM1, 0, &IID_IEcoFSM1, (void**)&pFSMFactory);
    pIBus->pVTbl->Release(pIBus);
    if (result != 0 || pFSMFactory == 0) {
        return -1;
    }

    pSuperNFA = pFSMFactory->pVTbl->CreateStateMachine(pFSMFactory, "SuperNFA");
    if (pSuperNFA == 0) {
        pFSMFactory->pVTbl->Release(pFSMFactory);
        return -1;
    }

    pEpsilonEvent = pSuperNFA->pVTbl->AddEvent(pSuperNFA, "ε", -1, 1);
    if (pEpsilonEvent == 0) {
        pSuperNFA->pVTbl->Release(pSuperNFA);
        pFSMFactory->pVTbl->Release(pFSMFactory);
        return -1;
    }

    pSuperStartState = pSuperNFA->pVTbl->AddState(pSuperNFA, "SuperStart");
    if (pSuperStartState == 0) {
        pSuperNFA->pVTbl->Release(pSuperNFA);
        pFSMFactory->pVTbl->Release(pFSMFactory);
        return -1;
    }
    pSuperStartState->pVTbl->set_Initial(pSuperStartState, 1);
	
    count = pRulesList->pVTbl->Count(pRulesList);
    for (i = 0; i < count; i++) {
        pRule = (RuleRE*)pRulesList->pVTbl->Item(pRulesList, i);
        if (!pRule || !pRule->pNFA) {
            continue;
        }

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
			char_t* stateName;
            char_t newName[256];

            pState = (IEcoFSM1State*)pRuleStates->pVTbl->Item(pRuleStates, j);
            if (!pState) continue;

            stateName = pState->pVTbl->get_Name(pState);
			sprintf(newName, "R%u_%s", i, stateName ? stateName : "state");

            pNewState = pSuperNFA->pVTbl->AddState(pSuperNFA, newName);
            if (!pNewState) {
                continue;
            }

            if (pState->pVTbl->IsInitial(pState)) {
                pNewState->pVTbl->set_Initial(pNewState, 1);
            }
            if (pState->pVTbl->IsFinal(pState)) {
                pNewState->pVTbl->set_Final(pNewState, 1);
            }

            ppStateMap[j] = pNewState;

            if (pState == pRule->pStartState) {
                IEcoFSM1Transition* pTrans = pSuperNFA->pVTbl->AddTransition(pSuperNFA, pEpsilonEvent, pSuperStartState, pNewState);
            }
        }

        pRuleTransitions = pRule->pNFA->pVTbl->get_Transitions(pRule->pNFA);
        if (pRuleTransitions) {
            transCount = pRuleTransitions->pVTbl->Count(pRuleTransitions);

            for (j = 0; j < transCount; j++) {
				IEcoFSM1State* pNewSource = 0;
                IEcoFSM1State* pNewTarget = 0;
                pTrans = (IEcoFSM1Transition*)pRuleTransitions->pVTbl->Item(pRuleTransitions, j);
                if (!pTrans) continue;

                pSource = pTrans->pVTbl->get_Source(pTrans);
                pTarget = pTrans->pVTbl->get_Target(pTrans);
                pEvent = pTrans->pVTbl->get_Event(pTrans);

                if (!pSource || !pTarget || !pEvent) continue;

                for (k = 0; k < stateCount; k++) {
                    pState = (IEcoFSM1State*)pRuleStates->pVTbl->Item(pRuleStates, k);
                    if (pState == pSource) pNewSource = ppStateMap[k];
                    if (pState == pTarget) pNewTarget = ppStateMap[k];
                }

                if (pNewSource && pNewTarget) {
                    pSuperNFA->pVTbl->AddTransition(pSuperNFA, pEvent, pNewSource, pNewTarget);
                }
            }
        }

        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ppStateMap);
    }
   
	pSuperStates = pSuperNFA->pVTbl->get_States(pSuperNFA);
    if (pSuperStates) {
        uint32_t superStateCount = pSuperStates->pVTbl->Count(pSuperStates);
        
        for (i = 0; i < superStateCount; i++) {
			char_t* stateName;

            pState = (IEcoFSM1State*)pSuperStates->pVTbl->Item(pSuperStates, i);
            if (!pState || !pState->pVTbl->IsFinal(pState)) continue;

            stateName = pState->pVTbl->get_Name(pState);
            if (!stateName) continue;

            if (stateName[0] == 'R') {
                uint32_t ruleIndex = 0;
                if (sscanf(stateName, "R%u_", &ruleIndex) == 1 && ruleIndex < count) {
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
        if (same) return ds;
    }
    return 0;
}

/* Вспомогательная функция, создающая состояние DFA эквивалентное данному множеству состояний NFA */
static DFAState* CreateDFAState(CEcoBLR1RE_F82A88F6* pCMe, IEcoList1* nfaSet) {
    DFAState* ds;
    IEcoFSM1State* st;
    FinalStateInfo* fi;
	IEcoInterfaceBus1* pIBus = 0;
    uint32_t i, j;
	int16_t result;
    uint32_t nfaCount;
    uint32_t finalCount;

    ds = (DFAState*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(DFAState));
    if (!ds) {
		return 0;
	}

    memset(ds, 0, sizeof(DFAState));
    ds->nfaStates = nfaSet;
	if (ds->nfaStates) ds->nfaStates->pVTbl->AddRef(ds->nfaStates);
    ds->isAccepting = 0;
    ds->bestPriority = 0xFFFFFFFFU;
	
	result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result == 0 && pIBus) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&ds->transitions);
        pIBus->pVTbl->Release(pIBus);
    }
    if (result != 0 || !ds->transitions) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds);
        return 0;
    }

    nfaCount = nfaSet->pVTbl->Count(nfaSet);
    finalCount = pCMe->m_pFinalStateAttrs->pVTbl->Count(pCMe->m_pFinalStateAttrs);
    for (i = 0; i < nfaCount; i++) {
        st = (IEcoFSM1State*)nfaSet->pVTbl->Item(nfaSet, i);
        if (st->pVTbl->IsFinal(st)) {
            for (j = 0; j < finalCount; j++) {
                fi = (FinalStateInfo*)pCMe->m_pFinalStateAttrs->pVTbl->Item(pCMe->m_pFinalStateAttrs, j);
                if (fi && fi->pState == st) {
                    ds->isAccepting = 1;
                    if (fi->priority < ds->bestPriority) {
                        ds->bestPriority = fi->priority;
                        ds->bestTokenId = fi->tokenId;
                        ds->bestAction = fi->pfnAction;
                        ds->bestActionContext = fi->pActionContext;
                        ds->bestChannel = fi->channel;
                    }
                    break;
                }
            }
        }
    }
    return ds;
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
    DFAState* newDFA;
    DFAState* existing;
    DFAState *ds, *cur;
    DFAState* pStartDFA;
    IEcoFSM1Transition* tr;
    IEcoInterfaceBus1* pIBus;
    IEcoFSM1Event *ev;
	IEcoFSM1State *pStartNFA;
    IEcoFSM1State *nfaState, *target;
    IEcoList1 *pStartSet, *pAllTrans;
    IEcoList1 *moveSet, *pNonEpsilonEvents;
    bool_t found;
    int16_t result;
    uint32_t processed;
    uint32_t i, j, k, l, t;
    uint32_t oldCount, evCount, nfaCount, transCount;

    if (!pCMe || !pCMe->m_pSuperNFA || !pCMe->m_pDFAStates || !pCMe->m_pFinalStateAttrs) {
        return ERR_ECO_POINTER;
	}

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || !pIBus) {
		return result;
	}

    oldCount = pCMe->m_pDFAStates->pVTbl->Count(pCMe->m_pDFAStates);
    for (i = 0; i < oldCount; i++) {
        ds = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
        if (ds) {
            if (ds->nfaStates) ds->nfaStates->pVTbl->Release(ds->nfaStates);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds);
        }
    }
    pCMe->m_pDFAStates->pVTbl->Clear(pCMe->m_pDFAStates);

    pAllTrans = pCMe->m_pSuperNFA->pVTbl->get_Transitions(pCMe->m_pSuperNFA);
    if (!pAllTrans) {
        pIBus->pVTbl->Release(pIBus);
        return -1;
    }
    transCount = pAllTrans->pVTbl->Count(pAllTrans);

    pNonEpsilonEvents = 0;
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pNonEpsilonEvents);
    if (result != 0 || !pNonEpsilonEvents) {
        pAllTrans->pVTbl->Release(pAllTrans);
        pIBus->pVTbl->Release(pIBus);
        return -1;
    }

    for (t = 0; t < transCount; t++) {
		IEcoFSM1Transition* tr = (IEcoFSM1Transition*)pAllTrans->pVTbl->Item(pAllTrans, t);
        IEcoFSM1Event* ev = tr->pVTbl->get_Event(tr);
        if (ev && !ev->pVTbl->IsNull(ev)) {
			bool_t alreadyHave = 0;
            uint32_t e;
            uint32_t evCount = pNonEpsilonEvents->pVTbl->Count(pNonEpsilonEvents);
            for (e = 0; e < evCount; e++) {
				IEcoFSM1Event* existing = (IEcoFSM1Event*)pNonEpsilonEvents->pVTbl->Item(pNonEpsilonEvents, e);
                if (EventsHaveSameSymbols(ev, existing)) {
					alreadyHave = 1;
					break;
				}
			}
			if (!alreadyHave) {
				pNonEpsilonEvents->pVTbl->Add(pNonEpsilonEvents, ev);
                ev->pVTbl->AddRef(ev);
			}
		}
	}

    pStartNFA = FindStartState(pCMe->m_pSuperNFA);
    if (!pStartNFA) {
        pNonEpsilonEvents->pVTbl->Release(pNonEpsilonEvents);
        pAllTrans->pVTbl->Release(pAllTrans);
        pIBus->pVTbl->Release(pIBus);
        return -1;
    }

    pStartSet = 0;
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pStartSet);
    if (result != 0 || !pStartSet) {
        pNonEpsilonEvents->pVTbl->Release(pNonEpsilonEvents);
        pAllTrans->pVTbl->Release(pAllTrans);
        pIBus->pVTbl->Release(pIBus);
        return -1;
    }
    pStartSet->pVTbl->Add(pStartSet, pStartNFA);
    pStartNFA->pVTbl->AddRef(pStartNFA);
    ComputeEpsilonClosure(pCMe, pCMe->m_pSuperNFA, pAllTrans, pStartSet);

    pStartDFA = CreateDFAState(pCMe, pStartSet);
    if (!pStartDFA) {
        pStartSet->pVTbl->Release(pStartSet);
        pNonEpsilonEvents->pVTbl->Release(pNonEpsilonEvents);
        pAllTrans->pVTbl->Release(pAllTrans);
        pIBus->pVTbl->Release(pIBus);
        return ERR_ECO_OUTOFMEMORY;
    }
    pCMe->m_pDFAStates->pVTbl->Add(pCMe->m_pDFAStates, pStartDFA);
	pCMe->m_startStateIdx = 0;

    processed = 0;
    while (processed < pCMe->m_pDFAStates->pVTbl->Count(pCMe->m_pDFAStates)) {
        cur = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, processed);
        evCount = pNonEpsilonEvents->pVTbl->Count(pNonEpsilonEvents);
        for (i = 0; i < evCount; i++) {
            ev = (IEcoFSM1Event*)pNonEpsilonEvents->pVTbl->Item(pNonEpsilonEvents, i);
            moveSet = 0;
            result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&moveSet);
            if (result != 0 || !moveSet) continue;

            nfaCount = cur->nfaStates->pVTbl->Count(cur->nfaStates);
            for (j = 0; j < nfaCount; j++) {
                nfaState = (IEcoFSM1State*)cur->nfaStates->pVTbl->Item(cur->nfaStates, j);
                for (k = 0; k < transCount; k++) {
                    tr = (IEcoFSM1Transition*)pAllTrans->pVTbl->Item(pAllTrans, k);
                    if (tr->pVTbl->get_Source(tr) == nfaState && EventsHaveSameSymbols(tr->pVTbl->get_Event(tr), ev)) {
                        target = tr->pVTbl->get_Target(tr);
                        found = 0;
                        for (l = 0; l < moveSet->pVTbl->Count(moveSet); l++) {
                            if ((IEcoFSM1State*)moveSet->pVTbl->Item(moveSet, l) == target) {
                                found = 1;
                                break;
                            }
                        }
                        if (!found) {
                            moveSet->pVTbl->Add(moveSet, target);
                            target->pVTbl->AddRef(target);
                        }
                    }
                }
            }

            if (moveSet->pVTbl->Count(moveSet) > 0) {
                ComputeEpsilonClosure(pCMe, pCMe->m_pSuperNFA, pAllTrans, moveSet);
                existing = FindDFAState(pCMe, moveSet);
                if (!existing) {
                    newDFA = CreateDFAState(pCMe, moveSet); 
                    if (newDFA) {
                        pCMe->m_pDFAStates->pVTbl->Add(pCMe->m_pDFAStates, newDFA);
						existing = newDFA;
                    } else {
                        moveSet->pVTbl->Release(moveSet);
						continue;
                    }
                } else {
                    moveSet->pVTbl->Release(moveSet);
                }
            } else {
                moveSet->pVTbl->Release(moveSet);
            }

			if (existing && cur && cur->transitions) {
				DFATransition* tr = (DFATransition*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(DFATransition));
                if (tr) {
					tr->pEvent = ev;
					tr->targetStateIdx = pCMe->m_pDFAStates->pVTbl->IndexOf(pCMe->m_pDFAStates, existing);
                    cur->transitions->pVTbl->Add(cur->transitions, tr);
                }
			}
        }
        processed++;
    }

    pNonEpsilonEvents->pVTbl->Release(pNonEpsilonEvents);
    pAllTrans->pVTbl->Release(pAllTrans);
    pIBus->pVTbl->Release(pIBus);
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Вспомогательная функция для минимизации DFA
 * </summary>
 *
 * <description>
 *   Минимизирует DFA табличным методом (Table-filling algorithm)
 * </description>
 *
 */
static int16_t MinimizeDFA(CEcoBLR1RE_F82A88F6* pCMe) {
    IEcoList1* pNewDFAStates = 0;
    IEcoInterfaceBus1* pIBus = 0;
    bool_t* distinguishable = 0;
    uint32_t *newGroup = 0, *groupRep = 0;
    bool_t changed = 1;
    int16_t result = 0;
    uint32_t i, j, s, t;
    uint32_t numGroups = 0, dfaCount = 0;
	uint32_t oldStartState = 0;

    if (pCMe == 0 || pCMe->m_pDFAStates == 0) {
        return ERR_ECO_POINTER;
    }

    dfaCount = pCMe->m_pDFAStates->pVTbl->Count(pCMe->m_pDFAStates);

    if (dfaCount <= 1) {
        return ERR_ECO_SUCCESES;
    }

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || pIBus == 0) {
        return result;
    }

    distinguishable = (bool_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * dfaCount * sizeof(bool_t));
    if (distinguishable == 0) {
        pIBus->pVTbl->Release(pIBus);
        return ERR_ECO_OUTOFMEMORY;
    }
    memset(distinguishable, 0, dfaCount * dfaCount * sizeof(bool_t));

    for (i = 0; i < dfaCount; i++) {
        DFAState* ds1 = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
        for (j = i + 1; j < dfaCount; j++) {
            DFAState* ds2 = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, j);
            bool_t diff = 0;

            if (ds1->isAccepting != ds2->isAccepting) {
                diff = 1;
            } else if (ds1->isAccepting && ds2->isAccepting) {
                if (ds1->bestTokenId != ds2->bestTokenId) {
                    diff = 1;
                }
            }

            distinguishable[i * dfaCount + j] = diff;
            distinguishable[j * dfaCount + i] = diff;
        }
    }

    while (changed) {
		changed = 0;
		for (i = 0; i < dfaCount; i++) {
			for (j = i + 1; j < dfaCount; j++) {
				DFAState *ds1, *ds2;
				if (distinguishable[i * dfaCount + j]) {
					continue;
				}

				ds1 = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
                ds2 = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, j);

				if (ds1->transitions && ds2->transitions) {
					uint32_t tc1 = ds1->transitions->pVTbl->Count(ds1->transitions);
					uint32_t tc2 = ds2->transitions->pVTbl->Count(ds2->transitions);

					for (s = 0; s < tc1; s++) {
						DFATransition* tr1 = (DFATransition*)ds1->transitions->pVTbl->Item(ds1->transitions, s);
                        bool_t foundMatch = 0;

                        for (t = 0; t < tc2; t++) {
							DFATransition* tr2 = (DFATransition*)ds2->transitions->pVTbl->Item(ds2->transitions, t);
                            if (tr1->pEvent == tr2->pEvent) {
								uint32_t target1 = tr1->targetStateIdx;
								uint32_t target2 = tr2->targetStateIdx;
								if (distinguishable[target1 * dfaCount + target2]) {
									distinguishable[i * dfaCount + j] = 1;
									distinguishable[j * dfaCount + i] = 1;
									changed = 1;
									foundMatch = 1;
									break;
								}
							}
						}
						if (foundMatch) {
							break;
						}
					}
				}
            }
        }
    }
   
    newGroup = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(uint32_t));
    if (newGroup == 0) {
		goto cleanup;
	}

    for (i = 0; i < dfaCount; i++) {
		newGroup[i] = 0xFFFFFFFFU;
	}

    numGroups = 0;
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
	oldStartState = pCMe->m_startStateIdx;

    groupRep = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, numGroups * sizeof(uint32_t));
    if (groupRep == 0) {
		goto cleanup;
	}
    for (i = 0; i < numGroups; i++) {
		groupRep[i] = 0xFFFFFFFFU;
	}

    for (i = 0; i < dfaCount; i++) {
        uint32_t g = newGroup[i];
        if (groupRep[g] == 0xFFFFFFFFU || i < groupRep[g]) {
            groupRep[g] = i;
        }
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pNewDFAStates);
    if (result != 0 || pNewDFAStates == 0) {
		goto cleanup;
	}

    for (i = 0; i < numGroups; i++) {
        uint32_t repIdx = groupRep[i];
        DFAState* rep = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, repIdx);
        DFAState* newDS = (DFAState*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(DFAState));

        if (newDS == 0) {
            pNewDFAStates->pVTbl->Release(pNewDFAStates);
            goto cleanup;
        }

        memset(newDS, 0, sizeof(DFAState));

        newDS->isAccepting = rep->isAccepting;
        newDS->bestTokenId = rep->bestTokenId;
        newDS->bestPriority = rep->bestPriority;
        newDS->bestAction = rep->bestAction;
        newDS->bestActionContext = rep->bestActionContext;
        newDS->bestChannel = rep->bestChannel;
        newDS->nfaStates = 0;

        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&newDS->transitions);
        if (result == 0 && newDS->transitions && rep->transitions) {
            uint32_t tc = rep->transitions->pVTbl->Count(rep->transitions);
            for (t = 0; t < tc; t++) {
                DFATransition* oldTr = (DFATransition*)rep->transitions->pVTbl->Item(rep->transitions, t);
                if (oldTr && oldTr->pEvent) {
                    DFATransition* newTr = (DFATransition*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(DFATransition));
                    if (newTr) {
                        newTr->pEvent = oldTr->pEvent;
                        newTr->pEvent->pVTbl->AddRef(newTr->pEvent);
                        newTr->targetStateIdx = newGroup[oldTr->targetStateIdx];
                        newDS->transitions->pVTbl->Add(newDS->transitions, newTr);
                    }
                }
            }
        }
        pNewDFAStates->pVTbl->Add(pNewDFAStates, newDS);
    }

    for (i = 0; i < dfaCount; i++) {
        DFAState* ds = (DFAState*)pCMe->m_pDFAStates->pVTbl->Item(pCMe->m_pDFAStates, i);
        if (ds) {
            if (ds->nfaStates)   ds->nfaStates->pVTbl->Release(ds->nfaStates);
            if (ds->transitions) ds->transitions->pVTbl->Release(ds->transitions);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, ds);
        }
    }
    pCMe->m_pDFAStates->pVTbl->Clear(pCMe->m_pDFAStates);
    pCMe->m_pDFAStates->pVTbl->Release(pCMe->m_pDFAStates);
    pCMe->m_pDFAStates = pNewDFAStates;

	if (oldStartState < dfaCount) {
        pCMe->m_startStateIdx = newGroup[oldStartState];
    } else {
        pCMe->m_startStateIdx = 0;
    }

cleanup:
    if (distinguishable) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, distinguishable);
    if (newGroup) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, newGroup);
    if (groupRep) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, groupRep);
    if (pIBus) pIBus->pVTbl->Release(pIBus);

    return result;
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
	int16_t result = ERR_ECO_SUCCESES;
    IEcoList1* pDFAStates = pCMe->m_pDFAStates;
    uint32_t dfaCount = 0;
    DFAState** pStates = 0;
    uint32_t i, j, s;
    uint16_t alphabetClassesCount = 0;
    uint16_t* globalAlphabetMap = 0;
    int32_t* transitionMatrix = 0;
    uint16_t* stateClassMap = 0;
    EcoLexicalStateClassInfo* stateClassInfo = 0;
    CEcoBLD1_F82A88F6* pLexData = 0;
	int32_t** fullTrans;
	uint32_t* signatures;
	uint16_t* charToClass;
	uint32_t matrixSize;
	static const uint8_t whitespace[] = { ' ', '\t', '\r', '\n' };
    uint32_t wsCount = sizeof(whitespace) / sizeof(whitespace[0]);

    /* Проверка указателей */
    if (!pCMe || !pDFAStates || !ppIData) {
        return ERR_ECO_POINTER;
    }

    *ppIData = 0;
    dfaCount = pDFAStates->pVTbl->Count(pDFAStates);
    if (dfaCount == 0) {
        return -1;
    }

    pStates = (DFAState**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(DFAState*));
    if (!pStates) return ERR_ECO_OUTOFMEMORY;
    for (i = 0; i < dfaCount; i++) {
        pStates[i] = (DFAState*)pDFAStates->pVTbl->Item(pDFAStates, i);
		if (!pStates[i]) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
            return -1;
        }
    }

    fullTrans = (int32_t**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(int32_t*));
    if (!fullTrans) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
        return ERR_ECO_OUTOFMEMORY;
    }
    for (i = 0; i < dfaCount; i++) {
        fullTrans[i] = (int32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(int32_t));
        if (!fullTrans[i]) {
            for (j = 0; j < i; j++) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans[j]);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
            return ERR_ECO_OUTOFMEMORY;
        }
        for (j = 0; j < 256; j++) fullTrans[i][j] = -1;
    }

    for (i = 0; i < dfaCount; i++) {
        DFAState* state = pStates[i];
		uint32_t transCount;

        if (!state->transitions) {
				continue;
		}

        transCount = state->transitions->pVTbl->Count(state->transitions);
        for (j = 0; j < transCount; j++) {
			uint8_t symbols[256];
			int numSymbols = 0, si = 0;
            DFATransition* tr = (DFATransition*)state->transitions->pVTbl->Item(state->transitions, j);
           
			if (!tr || !tr->pEvent) {
				continue;
			}

            GetSymbolsFromEvent(tr->pEvent, symbols, &numSymbols);
			for (si = 0; si < numSymbols; si++) {
				int ch = symbols[si];
				if (ch >= 0 && ch < 256) {
					uint32_t newTarget = (uint32_t)tr->targetStateIdx;
					uint32_t oldTarget = (uint32_t)fullTrans[i][ch];
					if (oldTarget == 0xFFFFFFFFU || pStates[newTarget]->bestPriority < pStates[oldTarget]->bestPriority) {
						fullTrans[i][ch] = (int32_t)newTarget;
					}
				}
			}
        }
    }

	/* Небольшой костыль: любой токен, у которого priority != 0, НЕ может продолжаться на whitespace */
	for (s = 0; s < dfaCount; s++) {
        DFAState* ds = pStates[s];
        if (ds && ds->isAccepting && ds->bestPriority != 0) { 
			uint32_t w = 0;
            for (w = 0; w < wsCount; w++) {
				fullTrans[s][whitespace[w]] = -1;
			}
        }
    }
	
	for (s = 0; s < dfaCount; s++) {
		DFAState* ds = pStates[s];
		if (ds && ds->isAccepting && ds->bestChannel == 1) {
			int ch = 0; 
			for (ch = 0; ch < 256; ch++) {
				bool_t isWS = 0;
				uint32_t w = 0;
				for (w = 0; w < wsCount; w++) {
					if (ch == whitespace[w]) { 
						isWS = 1; 
						break; 
					}
				}
				if (!isWS) {
					fullTrans[s][ch] = -1; 
				}
			}
		}
	}

    signatures = (uint32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256 * sizeof(uint32_t));
    if (!signatures) {
        for (i = 0; i < dfaCount; i++) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans[i]);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
        return ERR_ECO_OUTOFMEMORY;
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
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, signatures);
        for (i = 0; i < dfaCount; i++) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans[i]);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
        return ERR_ECO_OUTOFMEMORY;
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
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, charToClass);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, signatures);
        for (i = 0; i < dfaCount; i++) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans[i]);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
        return ERR_ECO_OUTOFMEMORY;
    }
    for (i = 0; i < 256; i++) {
        globalAlphabetMap[i] = charToClass[i];
    }

    matrixSize = dfaCount * alphabetClassesCount;
    transitionMatrix = (int32_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, matrixSize * sizeof(int32_t));
    if (!transitionMatrix) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, globalAlphabetMap);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, charToClass);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, signatures);
        for (i = 0; i < dfaCount; i++) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans[i]);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
        return ERR_ECO_OUTOFMEMORY;
    }

    for (i = 0; i < dfaCount; i++) {
		uint16_t classId = 0;
        for (classId = 0; classId < alphabetClassesCount; classId++) {
            int32_t target = -1;
			uint16_t ch = 0;
            for (ch = 0; ch < 256; ch++) {
                if (charToClass[ch] == classId) {
                    target = fullTrans[i][ch];
                    break;
                }
            }
            transitionMatrix[i * alphabetClassesCount + classId] = target;
        }
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, charToClass);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, signatures);
    for (i = 0; i < dfaCount; i++) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans[i]);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, fullTrans);

    stateClassInfo = (EcoLexicalStateClassInfo*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(EcoLexicalStateClassInfo));
    if (!stateClassInfo) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, transitionMatrix);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, globalAlphabetMap);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
        return ERR_ECO_OUTOFMEMORY;
    }

    for (i = 0; i < dfaCount; i++) {
        DFAState* state = pStates[i];
        stateClassInfo[i].tokenId = state->bestTokenId;
        stateClassInfo[i].channelId = state->bestChannel;
        stateClassInfo[i].isFinal = state->isAccepting;
        stateClassInfo[i].pContext = state->bestActionContext;
		stateClassInfo[i].priority = state->bestPriority;
    }

    stateClassMap = (uint16_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, dfaCount * sizeof(uint16_t));
    if (!stateClassMap) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, stateClassInfo);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, transitionMatrix);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, globalAlphabetMap);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
        return ERR_ECO_OUTOFMEMORY;
    }
    for (i = 0; i < dfaCount; i++) {
        stateClassMap[i] = (uint16_t)i;
    }

    pLexData = (CEcoBLD1_F82A88F6*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBLD1_F82A88F6));
    if (!pLexData) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, stateClassMap);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, stateClassInfo);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, transitionMatrix);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, globalAlphabetMap);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);
        return ERR_ECO_OUTOFMEMORY;
    }
    memcpy(pLexData, &g_xCEcoBLD1_F82A88F6, sizeof(CEcoBLD1_F82A88F6));

    pLexData->m_pVTblIData = &g_xDB2E163758AA4447A843545A8805D3FEVTbl_F82A88F6;
    pLexData->m_cRef = 1;
    pLexData->m_pIMem = pCMe->m_pIMem;
	if (pLexData->m_pIMem) pLexData->m_pIMem->pVTbl->AddRef(pLexData->m_pIMem);
	pLexData->m_pISys = pCMe->m_pISys;
	if (pLexData->m_pISys) pLexData->m_pISys->pVTbl->AddRef(pLexData->m_pISys);
	pLexData->m_Name = 0;

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

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pStates);

    *ppIData = (IEcoLexicalData1Ptr_t)pLexData;
    return ERR_ECO_SUCCESES;
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
