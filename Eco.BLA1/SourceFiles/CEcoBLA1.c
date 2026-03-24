/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLA1_F82A88F6
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBLA1_F82A88F6
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
#include "CEcoBLA1.h"
#include "CEcoBLR1RE.h" 

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoBLA1 interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_QueryInterface(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoLexicalAnalyzer1) ) {
        *ppv = &pCMe->m_pVTblILA;
        pCMe->m_pVTblILA->AddRef((IEcoLexicalAnalyzer1Ptr_t)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblILA;
        pCMe->m_pVTblILA->AddRef((IEcoLexicalAnalyzer1Ptr_t)pCMe);
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
 *   AddRef function for the IEcoLexicalAnalyzer1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLA1_F82A88F6_AddRef(/* in */ IEcoLexicalAnalyzer1Ptr_t me) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

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
 *   Release function for the IEcoLexicalAnalyzer1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLA1_F82A88F6_Release(/* in */ IEcoLexicalAnalyzer1Ptr_t me) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

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

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_new_FileScanner(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ char_t* fileName, /* out */ IEcoLexicalAnalyzer1ScannerPtr_t* ppIScanner) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_LoadRulesFromFile(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ char_t* fileName, /* out */ IEcoLexicalData1Ptr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_SaveRulesToFile(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ char_t* fileName) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_new_MemoryScanner(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ voidptr_t buffer, /* in */ uint32_t size, /* out */ IEcoLexicalAnalyzer1ScannerPtr_t* ppIScanner) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_LoadRulesFromMemory(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ voidptr_t pBuffer, /* in */ uint32_t size, /* out */ IEcoLexicalData1Ptr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_SaveRulesToMemory(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ voidptr_t* ppBuffer, /* in */ uint32_t* pSize) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_CreateRulesRE(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1REPtr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;
    CEcoBLR1RE_F82A88F6* pRules = 0;
    int16_t result = ERR_ECO_SUCCESES;

    if (me == 0 || ppIRules == 0) {
        return ERR_ECO_POINTER;
    }

    *ppIRules = 0;

    if (pCMe->m_pIMem == 0) {
        return -1;
    }

    pRules = (CEcoBLR1RE_F82A88F6*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBLR1RE_F82A88F6));
    if (pRules == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    memcpy(pRules, &g_xCEcoBLR1RE_F82A88F6, sizeof(CEcoBLR1RE_F82A88F6));

    pRules->m_pIMem = pCMe->m_pIMem;
    pRules->m_pIMem->pVTbl->AddRef(pRules->m_pIMem);

    pRules->m_pISys = pCMe->m_pISys;
    if (pRules->m_pISys) {
        pRules->m_pISys->pVTbl->AddRef(pRules->m_pISys);
    }
	pRules->m_pBRE = 0;
    pRules->m_pRulesList = 0;
    pRules->m_pSuperNFA = 0;
    pRules->m_pFinalStateAttrs = 0;
    pRules->m_Name = 0;

    result = pRules->Init((CEcoBLR1RE_F82A88F6Ptr_t)pRules, (IEcoUnknown*)pRules->m_pISys);
    if (result != 0) {
        pRules->Delete((CEcoBLR1RE_F82A88F6Ptr_t)pRules);
        return result;
    }

    *ppIRules = (IEcoLexicalRules1REPtr_t)pRules;

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_CreateRulesBNF(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1BNFPtr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_CreateRulesFSM(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1FSMPtr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}
static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_CreateRulesDirect(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1DirectPtr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
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
static int16_t ECOCALLMETHOD initCEcoBLA1_F82A88F6(/*in*/ CEcoBLA1_F82A88F6Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;
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
static int16_t ECOCALLMETHOD createCEcoBLA1_F82A88F6(/* in */ CEcoBLA1_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBLA1_F82A88F6(/* in */ CEcoBLA1_F82A88F6Ptr_t pCMe) {
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

/* IEcoBLA1 Virtual Table */
IEcoLexicalAnalyzer1VTbl g_x78E16240C3354A458D40D896B3F9D73BVTbl_F82A88F6 = {
    CEcoBLA1_F82A88F6_QueryInterface,
    CEcoBLA1_F82A88F6_AddRef,
    CEcoBLA1_F82A88F6_Release,
    CEcoBLA1_F82A88F6_new_FileScanner,
    CEcoBLA1_F82A88F6_LoadRulesFromFile,
    CEcoBLA1_F82A88F6_SaveRulesToFile,
    CEcoBLA1_F82A88F6_new_MemoryScanner,
    CEcoBLA1_F82A88F6_LoadRulesFromMemory,
    CEcoBLA1_F82A88F6_SaveRulesToMemory,
    CEcoBLA1_F82A88F6_CreateRulesRE,
    CEcoBLA1_F82A88F6_CreateRulesBNF,
    CEcoBLA1_F82A88F6_CreateRulesFSM,
    CEcoBLA1_F82A88F6_CreateRulesDirect
};

/* Object Instance */
CEcoBLA1_F82A88F6 g_xCEcoBLA1_F82A88F6 = {
    &g_x78E16240C3354A458D40D896B3F9D73BVTbl_F82A88F6,
   
    initCEcoBLA1_F82A88F6,
    createCEcoBLA1_F82A88F6,
    deleteCEcoBLA1_F82A88F6,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0  /* m_Name */
};
