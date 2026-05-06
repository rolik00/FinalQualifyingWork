/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLR1Action_A441A18E
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoLR1Action_A441A18E
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
#include "CEcoLR1Action.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoParser1Action interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLR1Action_A441A18E_QueryInterface(/* in */ IEcoParser1ActionPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoParser1Action) ) {
        *ppv = &pCMe->m_pVTblIAction;
        pCMe->m_pVTblIAction->AddRef((IEcoParser1Action*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIAction;
        pCMe->m_pVTblIAction->AddRef((IEcoParser1Action*)pCMe);
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
 *   AddRef function for the IEcoParser1Action interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLR1Action_A441A18E_AddRef(/* in */ IEcoParser1ActionPtr_t me) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

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
 *   Release function for the IEcoParser1Action interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLR1Action_A441A18E_Release(/* in */ IEcoParser1ActionPtr_t me) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

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

static int16_t ECOCALLMETHOD CEcoLR1Action_A441A18E_get_Type(/* in */ IEcoParser1ActionPtr_t me) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_Type;
}

static uint32_t ECOCALLMETHOD CEcoLR1Action_A441A18E_get_ReduceCount(/* in */ IEcoParser1ActionPtr_t me) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static IEcoBNF1Rule* ECOCALLMETHOD CEcoLR1Action_A441A18E_get_Rule(/* in */ IEcoParser1ActionPtr_t me, uint32_t index) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return pCMe->m_pRule;
}

static uint16_t ECOCALLMETHOD CEcoLR1Action_A441A18E_get_ruleSetId(/* in */ IEcoParser1ActionPtr_t me, uint32_t index) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static IEcoFSM1State* ECOCALLMETHOD CEcoLR1Action_A441A18E_get_State(/* in */ IEcoParser1ActionPtr_t me) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return pCMe->m_pState;
}

static char_t* ECOCALLMETHOD CEcoLR1Action_A441A18E_get_Description(/* in */ IEcoParser1ActionPtr_t me) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
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
static int16_t ECOCALLMETHOD initCEcoLR1Action_A441A18E(/*in*/ CEcoLR1Action_A441A18EPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoLR1Action_A441A18E* pCMe = (CEcoLR1Action_A441A18E*)me;
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
static int16_t ECOCALLMETHOD createCEcoLR1Action_A441A18E(/* in */ CEcoLR1Action_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoLR1Action_A441A18E(/* in */ CEcoLR1Action_A441A18EPtr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoParser1Action Virtual Table */
IEcoParser1ActionVTbl g_xED395A439C1B450F91650AD5DE50D33EVTbl_A441A18E = {
    CEcoLR1Action_A441A18E_QueryInterface,
    CEcoLR1Action_A441A18E_AddRef,
    CEcoLR1Action_A441A18E_Release,
    CEcoLR1Action_A441A18E_get_Type,
    CEcoLR1Action_A441A18E_get_ReduceCount,
    CEcoLR1Action_A441A18E_get_Rule,
    CEcoLR1Action_A441A18E_get_ruleSetId,
    CEcoLR1Action_A441A18E_get_State,
    CEcoLR1Action_A441A18E_get_Description
};



/* Object Instance */
CEcoLR1Action_A441A18E g_xCEcoLR1Action_A441A18E = {
    &g_xED395A439C1B450F91650AD5DE50D33EVTbl_A441A18E,
    initCEcoLR1Action_A441A18E,
    createCEcoLR1Action_A441A18E,
    deleteCEcoLR1Action_A441A18E,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_Type */
    0, /* m_pRule */
    0, /* m_RuleSetId */
    0, /* m_pState */
};
