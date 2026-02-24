/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBRE1RegEx_0E0B7D40
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBRE1RegEx_0E0B7D40
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir. All rights reserved.
 * </author>
 *
 */


#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoBRE1RegEx.h"
#include "IdEcoList1.h"

extern CEcoBRE1RegEx_0E0B7D40 g_xCEcoBRE1RegEx_0E0B7D40;

/* Вспомогательная функция для создания списка */
static IEcoList1* CreateList(CEcoBRE1RegEx_0E0B7D40* pCMe) {
    IEcoList1* pList = 0;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result;

	result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        return 0;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, (const UGUID*)&CID_EcoList1, 0, &IID_IEcoList1, (void**)&pList);
    pIBus->pVTbl->Release(pIBus);

	return pList;
}

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoRegEx1 interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_QueryInterface(/* in */ IEcoRegEx1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoRegEx1) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1;
        pCMe->m_pVTblIEcoRegEx1->AddRef((IEcoRegEx1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1;
        pCMe->m_pVTblIEcoRegEx1->AddRef((IEcoRegEx1*)pCMe);
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
 *   AddRef function for the IEcoRegEx1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_AddRef(/* in */ IEcoRegEx1Ptr_t me) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;

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
 *   Release function for the IEcoRegEx1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_Release(/* in */ IEcoRegEx1Ptr_t me) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;

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

/*
 * Функция для вычисления ε-замыкания множества состояний
 */
static IEcoList1* EpsilonClosure(CEcoBRE1RegEx_0E0B7D40* pCMe, IEcoList1* pStates) {
    IEcoList1* pResult = CreateList(pCMe);
    IEcoList1* pWorkList = CreateList(pCMe);
    IEcoFSM1State* pState = 0;
	IEcoFSM1State* pTarget = 0;
	IEcoList1* pTransitions = 0;
	IEcoFSM1Transition* pTrans = 0;
	IEcoFSM1Event* pEvent = 0;
	uint32_t i = 0, j = 0, k = 0;
	bool_t found = 0;

    if (!pResult || !pWorkList) {
		if (pResult) pResult->pVTbl->Release(pResult);
        if (pWorkList) pWorkList->pVTbl->Release(pWorkList);
		return 0;
	}
    
    for (i = 0; i < pStates->pVTbl->Count(pStates); i++) {
        pState = (IEcoFSM1State*)pStates->pVTbl->Item(pStates, i);
        pResult->pVTbl->Add(pResult, pState);
        pWorkList->pVTbl->Add(pWorkList, pState);
    }
    
    while (pWorkList->pVTbl->Count(pWorkList) > 0) {
        pState = (IEcoFSM1State*)pWorkList->pVTbl->Item(pWorkList, 0);
        pWorkList->pVTbl->RemoveAt(pWorkList, 0);
        
        pTransitions = pCMe->m_pStateMachine->pVTbl->get_Transitions(pCMe->m_pStateMachine);

		if (pTransitions == 0) continue;

        for (j = 0; j < pTransitions->pVTbl->Count(pTransitions); j++) {
            pTrans = (IEcoFSM1Transition*)pTransitions->pVTbl->Item(pTransitions, j);
            
            if (pTrans->pVTbl->get_Source(pTrans) == pState) {
                pEvent = pTrans->pVTbl->get_Event(pTrans);
                
                if (pEvent->pVTbl->IsNull(pEvent)) {
                    pTarget = pTrans->pVTbl->get_Target(pTrans);
                    
                    found = 0;
                    for (k = 0; k < pResult->pVTbl->Count(pResult); k++) {
                        if ((IEcoFSM1State*)pResult->pVTbl->Item(pResult, k) == pTarget) {
                            found = 1;
                            break;
                        }
                    }
                    
                    if (!found) {
                        pResult->pVTbl->Add(pResult, pTarget);
                        pWorkList->pVTbl->Add(pWorkList, pTarget);
                    }
                }
            }
        }
    }
    
	pWorkList->pVTbl->Release(pWorkList);
    return pResult;
}

/*
 * Переход по символу из множества состояний
 */
static IEcoList1* Move(CEcoBRE1RegEx_0E0B7D40* pCMe, IEcoList1* pStates, byte_t symbol) {
    IEcoList1* pTransitions = 0;
	IEcoList1* pSymbolSets = 0;
	IEcoFSM1State* pState = 0;
	IEcoFSM1State* pTarget = 0;
	IEcoFSM1Transition* pTrans = 0;
	IEcoFSM1Event* pEvent = 0;
	IEcoFL1SymbolSet* pSet = 0;
	uint32_t i = 0, j = 0, k = 0;
    
	IEcoList1* pResult = CreateList(pCMe);
    if (!pResult) return 0;
    
    pTransitions = pCMe->m_pStateMachine->pVTbl->get_Transitions(pCMe->m_pStateMachine);
    if (pTransitions == 0) {
        pResult->pVTbl->Release(pResult);
        return 0;
    }

    for (i = 0; i < pStates->pVTbl->Count(pStates); i++) {
        pState = (IEcoFSM1State*)pStates->pVTbl->Item(pStates, i);
        
        for (j = 0; j < pTransitions->pVTbl->Count(pTransitions); j++) {
            pTrans = (IEcoFSM1Transition*)pTransitions->pVTbl->Item(pTransitions, j);
            
            if (pTrans->pVTbl->get_Source(pTrans) == pState) {
                pEvent = pTrans->pVTbl->get_Event(pTrans);
                
                if (pEvent == 0 || pEvent->pVTbl->IsNull(pEvent)) continue;
                
                pSymbolSets = pEvent->pVTbl->get_SymbolSets(pEvent);
                if (pSymbolSets == 0) continue;
				for (k = 0; k < pSymbolSets->pVTbl->Count(pSymbolSets); k++) {
                    pSet = (IEcoFL1SymbolSet*)pSymbolSets->pVTbl->Item(pSymbolSets, k);
                    
                    if (pSet->pVTbl->IsExist(pSet, &symbol, 1, 0)) {
                        pTarget = pTrans->pVTbl->get_Target(pTrans);
                        pResult->pVTbl->Add(pResult, pTarget);
                        break;
                    }
                }
            }
        }
    }
    
	return pResult;
}

/*
 * Проверка, содержит ли множество принимающее состояние
 */
static bool_t ContainsAcceptState(CEcoBRE1RegEx_0E0B7D40* pCMe, IEcoList1* pStates) {
    IEcoFSM1State* pState = 0;
	uint32_t i = 0;
	
	for (i = 0; i < pStates->pVTbl->Count(pStates); i++) {
        pState = (IEcoFSM1State*)pStates->pVTbl->Item(pStates, i);
        if (pState->pVTbl->IsFinal(pState)) {
            return 1;
        }
    }
    return 0;
}

/*
 *
 * <summary>
 *   Match Function
 * </summary>
 *
 * <description>
 *   Поиск первого совпадения
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_Match(/* in */ IEcoRegEx1Ptr_t me, /* in */ voidptr_t string, /* in */ uint32_t length, /* in */ uint32_t flags, /* out */ EcoRegEx1Match** pMatch) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;
	char* text = (char*)string;
    uint32_t len = length ? length : strlen(text);
	uint32_t start = 0, pos = 0, matchLen = 0;
	IEcoList1* pStartSet;
	IEcoList1* pCurrent = 0;
	bool_t matched = 0;
	IEcoList1* pMoved = 0;
	IEcoList1* pNext = 0;
	EcoRegEx1Match* pTmpMatch = 0;

	if (me == 0) {
        return ERR_ECO_POINTER;
    }
	
    for (start = 0; start <= len; start++) {
		pStartSet = CreateList(pCMe);
		if (pStartSet == 0) {
			continue;
		}

		pStartSet->pVTbl->Add(pStartSet, pCMe->m_pStartState);
        pCurrent = EpsilonClosure(pCMe, pStartSet);
		pStartSet->pVTbl->Clear(pStartSet);
		
		if (pCurrent == 0) {
            continue;
        }

        pos = start;
        matched = 0;
        matchLen = 0;
        
        while (pos < len) {
			if (ContainsAcceptState(pCMe, pCurrent)) {
                matched = 1;
                matchLen = pos - start;
				break;
            }
            
            pMoved = Move(pCMe, pCurrent, (byte_t)text[pos]);
			if (pMoved == 0 || pMoved->pVTbl->Count(pMoved) == 0) {
                if (pMoved) pMoved->pVTbl->Release(pMoved);
                break;
            }
            
            pNext = EpsilonClosure(pCMe, pMoved);
            pMoved->pVTbl->Release(pMoved);
            
            if (pNext == 0) {
                break;
            }

            if (pCurrent) {
                pCurrent->pVTbl->Release(pCurrent);
            }
            pCurrent = pNext;
            pos++;
        }

		if (!matched && ContainsAcceptState(pCMe, pCurrent)) {
            matched = 1;
            matchLen = pos - start;
        }
        
        if (matched) {
			pTmpMatch = (EcoRegEx1Match*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoRegEx1Match));
            
            if (pTmpMatch) {
                pTmpMatch->index = start;
                pTmpMatch->length = matchLen;
                pTmpMatch->pValue = text + start;
                pTmpMatch->cCookie = 0;
                *pMatch = pTmpMatch;
			}
            
            if (pCurrent) {
                pCurrent->pVTbl->Release(pCurrent);
            }
            if (pStartSet) {
                pStartSet->pVTbl->Release(pStartSet);
            }
            
            return 0;
        }
        
        if (pCurrent) {
            pCurrent->pVTbl->Release(pCurrent);
        }
    }

	if (pStartSet) {
        pStartSet->pVTbl->Release(pStartSet);
    }
	return -1;
}

/*
 *
 * <summary>
 *   IsMatch Function
 * </summary>
 *
 * <description>
 *   Проверка наличия совпадения
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_IsMatch(IEcoRegEx1Ptr_t me, voidptr_t str, uint32_t sizeInBytes, uint32_t flags) {
    CEcoBRE1RegEx_0E0B7D40* pThis = (CEcoBRE1RegEx_0E0B7D40*)me;
    EcoRegEx1Match* pMatch = 0;
	int16_t result = -1;

	if (!pThis || !str) return 0;
    
	result = pThis->m_pVTblIEcoRegEx1->Match(me, str, sizeInBytes, flags, &pMatch);
    
    if (result == 0 && pMatch) {
        pThis->m_pIMem->pVTbl->Free(pThis->m_pIMem, pMatch);
        return 1;
    }
    
    return 0;
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
int16_t ECOCALLMETHOD initCEcoBRE1RegEx_0E0B7D40(/*in*/ CEcoBRE1RegEx_0E0B7D40Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;
    IEcoInterfaceBus1* pIBus = 0;
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
        result = ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Freeing */
    pIBus->pVTbl->Release(pIBus);

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
int16_t ECOCALLMETHOD createCEcoBRE1RegEx_0E0B7D40(/* in */ CEcoBRE1RegEx_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoRegEx1Ptr_t* ppIRegex) {
    int16_t result = ERR_ECO_POINTER;
    CEcoBRE1RegEx_0E0B7D40* pNewObj = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    if (pIUnkSystem == 0) {
        return ERR_ECO_POINTER;
    }

    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);
    if (result != 0 || pISys == 0) {
        return ERR_ECO_NOSYSTEM;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_NOBUS;
    }

    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    pNewObj = (CEcoBRE1RegEx_0E0B7D40*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoBRE1RegEx_0E0B7D40));
    if (pNewObj == 0) {
        pIMem->pVTbl->Release(pIMem);
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }

    pNewObj = (CEcoBRE1RegEx_0E0B7D40*)pIMem->pVTbl->Copy(pIMem, pNewObj, &g_xCEcoBRE1RegEx_0E0B7D40, sizeof(CEcoBRE1RegEx_0E0B7D40));

    pNewObj->m_cRef = 1;
    pNewObj->m_pIMem = pIMem;
    pIMem->pVTbl->AddRef(pIMem);
    
    pNewObj->m_pISys = pISys;
    pISys->pVTbl->AddRef(pISys);
    
    pNewObj->m_Name = 0;
    pNewObj->m_pRoot = 0;
	pNewObj->m_pFSM = 0; 
    pNewObj->m_pStateMachine = 0;
    pNewObj->m_pStartState = 0;

	if (result == 0 && pNewObj != 0) {
        *ppIRegex = (IEcoRegEx1Ptr_t)pNewObj;
    }

    pIBus->pVTbl->Release(pIBus);

    return 0;
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
static void ECOCALLMETHOD deleteCEcoBRE1RegEx_0E0B7D40(/* in */ CEcoBRE1RegEx_0E0B7D40Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
		if (pCMe->m_pRoot != 0) {
            pCMe->m_pRoot->pVTbl->Release(pCMe->m_pRoot);
        }
		if (pCMe->m_pFSM != 0) {
            pCMe->m_pFSM->pVTbl->Release(pCMe->m_pFSM);
        }
        if (pCMe->m_pStateMachine != 0) {
            pCMe->m_pStateMachine->pVTbl->Release(pCMe->m_pStateMachine);
        }
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoRegEx1 Virtual Table */
IEcoRegEx1VTbl g_xA5E921E4E4B64CA3BDD5AFF5EB75F915VTbl_0E0B7D40 = {
    CEcoBRE1RegEx_0E0B7D40_QueryInterface,
    CEcoBRE1RegEx_0E0B7D40_AddRef,
    CEcoBRE1RegEx_0E0B7D40_Release,    
    CEcoBRE1RegEx_0E0B7D40_Match,
	CEcoBRE1RegEx_0E0B7D40_IsMatch
};

/* Object Instance */
CEcoBRE1RegEx_0E0B7D40 g_xCEcoBRE1RegEx_0E0B7D40 = {
    &g_xA5E921E4E4B64CA3BDD5AFF5EB75F915VTbl_0E0B7D40,
    initCEcoBRE1RegEx_0E0B7D40,
    createCEcoBRE1RegEx_0E0B7D40,
    deleteCEcoBRE1RegEx_0E0B7D40,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pIMem */
    0, /* m_Name */
	0, /* m_pRoot */
	0, /* m_pFSM */  
	0, /* m_pStateMachine */
	0  /* m_pStartState */
};
