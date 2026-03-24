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
#include "IdEcoList1.h"
#include "IdEcoBRE1.h"
#include "IdEcoFSM1.h"
#include <string.h>

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
    pRule->priority = 0;
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
    pRule->priority = 0;
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

    if (pCMe->m_pSuperNFA) {
        pCMe->m_pSuperNFA->pVTbl->Release(pCMe->m_pSuperNFA);
        pCMe->m_pSuperNFA = 0;
    }

	return ERR_ECO_SUCCESES;
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
    uint32_t i, j, k, l;
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

    for (i = 0; i < transCount; i++) {
        IEcoFSM1Event* ev;
        tr = (IEcoFSM1Transition*)pAllTrans->pVTbl->Item(pAllTrans, i);
        ev = tr->pVTbl->get_Event(tr);
        if (ev && !ev->pVTbl->IsNull(ev)) {
            uint32_t evCount = pNonEpsilonEvents->pVTbl->Count(pNonEpsilonEvents);
            bool_t found = 0;
            for (j = 0; j < evCount; j++) {
                if ((IEcoFSM1Event*)pNonEpsilonEvents->pVTbl->Item(pNonEpsilonEvents, j) == ev) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
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
                    if (tr->pVTbl->get_Source(tr) == nfaState && tr->pVTbl->get_Event(tr) == ev) {
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
 *   Минимизирует DFA на основе алгоритма Хопкрофта
 * </description>
 *
 */
static int16_t MinimizeDFA(CEcoBLR1RE_F82A88F6* pCMe) {
	if (pCMe == 0) {
        return ERR_ECO_POINTER;
    }

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

    /* Этап 3: Минимизация DFA с использованием алгоритма Хопкрофта */
	result = MinimizeDFA(pCMe);
	if (result != 0) {
		return result;
	}

    /* Этап 4: Построение таблицы переходов в формате IEcoLexicalData1 */ 

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

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
		if (pCMe->m_pRulesList != 0) {
			CEcoBLR1RE_F82A88F6_Clear((IEcoLexicalRules1REPtr_t)pCMe);
			pCMe->m_pRulesList->pVTbl->Release(pCMe->m_pRulesList);
		}
		if (pCMe->m_pFinalStateAttrs != 0) {
            pCMe->m_pFinalStateAttrs->pVTbl->Release(pCMe->m_pFinalStateAttrs);
        }
		if (pCMe->m_pBRE != 0) {
			pCMe->m_pBRE->pVTbl->Release(pCMe->m_pBRE);
		}
		if (pCMe->m_pSuperNFA != 0) {
			pCMe->m_pSuperNFA->pVTbl->Release(pCMe->m_pSuperNFA);
		}
		if (pCMe->m_pDFAStates != 0) {
			pCMe->m_pDFAStates->pVTbl->Release(pCMe->m_pDFAStates);
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
	0  /* m_pDFAStates */
};
