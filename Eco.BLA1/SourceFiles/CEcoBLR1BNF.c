/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLR1BNF_F82A88F6
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBLR1BNF_F82A88F6
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
#include "CEcoBLR1BNF.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoLexicalRules1BNF interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_QueryInterface(/* in */ IEcoLexicalRules1BNFPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoLexicalRules1BNF) ) {
        *ppv = &pCMe->m_pVTblIRules;
        pCMe->m_pVTblIRules->AddRef((IEcoLexicalRules1BNF*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIRules;
        pCMe->m_pVTblIRules->AddRef((IEcoLexicalRules1BNF*)pCMe);
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
 *   AddRef function for the IEcoLexicalRules1BNF interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_AddRef(/* in */ IEcoLexicalRules1BNFPtr_t me) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

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
 *   Release function for the IEcoLexicalRules1BNF interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_Release(/* in */ IEcoLexicalRules1BNFPtr_t me) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

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

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_AddState(IEcoLexicalRules1BNFPtr_t me, char_t* name, bool_t isExclusive) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static uint32_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_get_StatesCount(IEcoLexicalRules1BNFPtr_t me) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static char_t* ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_get_StateName(IEcoLexicalRules1BNFPtr_t me, uint32_t index) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}
static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_AddRuleBNF(IEcoLexicalRules1BNFPtr_t me, char_t* stateName, IEcoBNF1RulePtr_t pIBNFRule, uint32_t tokenId) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_AddException(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, IEcoBNF1RulePtr_t pExceptRule) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_SetLookahead(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, IEcoBNF1RulePtr_t pFollowRule, bool_t isNegative) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}
static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_SetPriority(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, uint32_t priority) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_SetChannel(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, uint32_t channelId) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_SetGreedy(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, bool_t isGreedy) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_SetAction(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, EcoLexicalAction_t pfnAction, voidptr_t pContext) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static uint32_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_get_Count(IEcoLexicalRules1BNFPtr_t me) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_GetRuleInfo(IEcoLexicalRules1BNFPtr_t me, uint32_t index, EcoLexicalRuleBNFInfo* pInfo) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_GetRuleObject(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, IEcoBNF1RulePtr_t* ppIBNFRule) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_SetDefaultTokenId(IEcoLexicalRules1BNFPtr_t me, char_t* stateName, uint32_t tokenId) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_SetDefaultAction(IEcoLexicalRules1BNFPtr_t me, char_t* stateName, EcoLexicalAction_t pfnAction, voidptr_t pContext) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_Validate(IEcoLexicalRules1BNFPtr_t me) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_RemoveRule(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLR1BNF_F82A88F6_Compile(IEcoLexicalRules1BNFPtr_t me, IEcoLexicalData1Ptr_t* ppIData) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
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
static int16_t ECOCALLMETHOD initCEcoBLR1BNF_F82A88F6(/*in*/ CEcoBLR1BNF_F82A88F6Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBLR1BNF_F82A88F6* pCMe = (CEcoBLR1BNF_F82A88F6*)me;
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
static int16_t ECOCALLMETHOD createCEcoBLR1BNF_F82A88F6(/* in */ CEcoBLR1BNF_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBLR1BNF_F82A88F6(/* in */ CEcoBLR1BNF_F82A88F6Ptr_t pCMe) {
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
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoLexicalRules1BNF Virtual Table */
IEcoLexicalRules1BNFVTbl g_x4A71B41041E74058A8A51C154ACA5CAEVTbl_F82A88F6 = {
    CEcoBLR1BNF_F82A88F6_QueryInterface,
    CEcoBLR1BNF_F82A88F6_AddRef,
    CEcoBLR1BNF_F82A88F6_Release,
    CEcoBLR1BNF_F82A88F6_AddState,
    CEcoBLR1BNF_F82A88F6_get_StatesCount,
    CEcoBLR1BNF_F82A88F6_get_StateName,
    CEcoBLR1BNF_F82A88F6_AddRuleBNF,
    CEcoBLR1BNF_F82A88F6_AddException,
    CEcoBLR1BNF_F82A88F6_SetLookahead,
    CEcoBLR1BNF_F82A88F6_SetPriority,
    CEcoBLR1BNF_F82A88F6_SetChannel,
    CEcoBLR1BNF_F82A88F6_SetGreedy,
    CEcoBLR1BNF_F82A88F6_SetAction,
    CEcoBLR1BNF_F82A88F6_get_Count,
    CEcoBLR1BNF_F82A88F6_GetRuleInfo,
    CEcoBLR1BNF_F82A88F6_GetRuleObject,
    CEcoBLR1BNF_F82A88F6_SetDefaultTokenId,
    CEcoBLR1BNF_F82A88F6_SetDefaultAction,
    CEcoBLR1BNF_F82A88F6_Validate,
    CEcoBLR1BNF_F82A88F6_RemoveRule,
    CEcoBLR1BNF_F82A88F6_Compile
};


/* Object Instance */
CEcoBLR1BNF_F82A88F6 g_xCEcoBLR1BNF_F82A88F6 = {
    &g_x4A71B41041E74058A8A51C154ACA5CAEVTbl_F82A88F6,
    initCEcoBLR1BNF_F82A88F6,
    createCEcoBLR1BNF_F82A88F6,
    deleteCEcoBLR1BNF_F82A88F6,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0  /* m_Name */
};
