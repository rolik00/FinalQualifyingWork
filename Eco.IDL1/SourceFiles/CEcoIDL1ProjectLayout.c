/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1ProjectLayout_40BB8A88
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoIDL1ProjectLayout_40BB8A88
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
#include "CEcoIDL1ProjectLayout.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoIDL1ProjectLayout interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1ProjectLayout_40BB8A88_QueryInterface(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoIDL1ProjectLayout) ) {
        *ppv = &pCMe->m_pVTblIEcoIDL1ProjectLayout;
        pCMe->m_pVTblIEcoIDL1ProjectLayout->AddRef((IEcoIDL1ProjectLayout*)pCMe);
    }
	
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoIDL1ProjectLayout;
        pCMe->m_pVTblIEcoIDL1ProjectLayout->AddRef((IEcoIDL1ProjectLayout*)pCMe);
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
 *   AddRef function for the IEcoIDL1ProjectLayout interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1ProjectLayout_40BB8A88_AddRef(/* in */ IEcoIDL1ProjectLayoutPtr_t me) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;

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
 *   Release function for the IEcoIDL1ProjectLayout interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1ProjectLayout_40BB8A88_Release(/* in */ IEcoIDL1ProjectLayoutPtr_t me) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;

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
 *
 * <summary>
 *   MyFunction Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1ProjectLayout_40BB8A88_MyFunction(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ char_t* Name, /* out */ char_t** copyName) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Clear Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1ProjectLayout_40BB8A88_Clear(/* in */ IEcoIDL1ProjectLayoutPtr_t me) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   SetRootPath Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1ProjectLayout_40BB8A88_SetRootPath(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ char_t* path) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   SetArtifactPath Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1ProjectLayout_40BB8A88_SetArtifactPath(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ uint32_t artifactType, /* in */ char_t* relPath) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   GetFullPath Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1ProjectLayout_40BB8A88_GetFullPath(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ uint32_t artifactType, /* out */ char_t** pFullPath) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;

    /* Pointer Validation */
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
static int16_t ECOCALLMETHOD initCEcoIDL1ProjectLayout_40BB8A88(/*in*/ CEcoIDL1ProjectLayout_40BB8A88Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoIDL1ProjectLayout_40BB8A88* pCMe = (CEcoIDL1ProjectLayout_40BB8A88*)me;
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
static int16_t ECOCALLMETHOD createCEcoIDL1ProjectLayout_40BB8A88(/* in */ CEcoIDL1ProjectLayout_40BB8A88Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoIDL1ProjectLayout_40BB8A88(/* in */ CEcoIDL1ProjectLayout_40BB8A88Ptr_t pCMe) {
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

/* IEcoIDL1ProjectLayout Virtual Table */
IEcoIDL1ProjectLayoutVTbl g_x151492C58D57490C8E5DFA6168D1C45FVTbl_40BB8A88 = {
    CEcoIDL1ProjectLayout_40BB8A88_QueryInterface,
    CEcoIDL1ProjectLayout_40BB8A88_AddRef,
    CEcoIDL1ProjectLayout_40BB8A88_Release,
    CEcoIDL1ProjectLayout_40BB8A88_Clear,
    CEcoIDL1ProjectLayout_40BB8A88_SetRootPath,
    CEcoIDL1ProjectLayout_40BB8A88_SetArtifactPath,
    CEcoIDL1ProjectLayout_40BB8A88_GetFullPath
};

/* Object Instance */
CEcoIDL1ProjectLayout_40BB8A88 g_xCEcoIDL1ProjectLayout_40BB8A88 = {
    &g_x151492C58D57490C8E5DFA6168D1C45FVTbl_40BB8A88,
    initCEcoIDL1ProjectLayout_40BB8A88,
    createCEcoIDL1ProjectLayout_40BB8A88,
    deleteCEcoIDL1ProjectLayout_40BB8A88,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0  /* m_Name */
};
