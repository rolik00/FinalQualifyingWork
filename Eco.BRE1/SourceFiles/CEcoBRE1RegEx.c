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
 *
 * <summary>
 *   Match Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_Match(/* in */ IEcoRegEx1Ptr_t me, /* in */ voidptr_t string, /* in */ uint32_t length, /* in */ uint32_t flags, /* out */ EcoRegEx1Match** pMatch) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;

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
int16_t ECOCALLMETHOD createCEcoBRE1RegEx_0E0B7D40(/* in */ CEcoBRE1RegEx_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* in */ IEcoRegEx1Ptr_t* ppIRegex) {
    int16_t result = ERR_ECO_POINTER;
    CEcoBRE1RegEx_0E0B7D40* pNewObj = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
    extern CEcoBRE1RegEx_0E0B7D40 g_xCEcoBRE1RegEx_0E0B7D40;

    if (pIUnkSystem == 0 || ppIRegex == 0) {
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

    *ppIRegex = (IEcoRegEx1Ptr_t)pNewObj;

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
    CEcoBRE1RegEx_0E0B7D40_Match
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
	0 //временно
};
