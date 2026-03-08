/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBRE1EnumMatches_0E0B7D40
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBRE1EnumMatches_0E0B7D40
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
#include "CEcoBRE1EnumMatches.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoRegEx1EnumMatches interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1EnumMatches_0E0B7D40_QueryInterface(/* in */ IEcoRegEx1EnumMatchesPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBRE1EnumMatches_0E0B7D40* pCMe = (CEcoBRE1EnumMatches_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoRegEx1EnumMatches) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1EnumMatches;
        pCMe->m_pVTblIEcoRegEx1EnumMatches->AddRef((IEcoRegEx1EnumMatches*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1EnumMatches;
        pCMe->m_pVTblIEcoRegEx1EnumMatches->AddRef((IEcoRegEx1EnumMatches*)pCMe);
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
 *   AddRef function for the IEcoRegEx1EnumMatches interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1EnumMatches_0E0B7D40_AddRef(/* in */ IEcoRegEx1EnumMatchesPtr_t me) {
    CEcoBRE1EnumMatches_0E0B7D40* pCMe = (CEcoBRE1EnumMatches_0E0B7D40*)me;

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
 *   Release function for the IEcoRegEx1EnumMatches interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1EnumMatches_0E0B7D40_Release(/* in */ IEcoRegEx1EnumMatchesPtr_t me) {
    CEcoBRE1EnumMatches_0E0B7D40* pCMe = (CEcoBRE1EnumMatches_0E0B7D40*)me;

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
 *   Next Function
 * </summary>
 *
 * <description>
 *   Получает следующие cMatchs совпадений из перечислителя
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1EnumMatches_0E0B7D40_Next(/* in */ IEcoRegEx1EnumMatchesPtr_t me, /* in */ uint32_t cMatchs, /* out */ struct EcoRegEx1Match *rgcd, /* out */ uint32_t *pcFetched) {
    CEcoBRE1EnumMatches_0E0B7D40* self = (CEcoBRE1EnumMatches_0E0B7D40*)me;
    uint32_t can_fetch, i;

    if (!self || !rgcd) return ERR_ECO_POINTER;
    if (pcFetched) *pcFetched = 0;

    if (self->m_current >= self->m_count) {
        return 0;
    }

    can_fetch = self->m_count - self->m_current;
    if (can_fetch > cMatchs) can_fetch = cMatchs;

    for (i = 0; i < can_fetch; i++) {
        rgcd[i] = self->m_matches[self->m_current + i];
    }

    self->m_current += can_fetch;
    if (pcFetched) *pcFetched = can_fetch;

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Skip Function
 * </summary>
 *
 * <description>
 *   Пропускает указанное количество совпадений в перечислителе
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1EnumMatches_0E0B7D40_Skip(/* in */ IEcoRegEx1EnumMatchesPtr_t me, /* in */ uint32_t cMatchs) {
    CEcoBRE1EnumMatches_0E0B7D40* pCMe = (CEcoBRE1EnumMatches_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    /* Здесь должна быть реализация пропуска элементов */
    
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Reset Function
 * </summary>
 *
 * <description>
 *   Сбрасывает перечислитель в начальное положение
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1EnumMatches_0E0B7D40_Reset(/* in */ IEcoRegEx1EnumMatchesPtr_t me) {
    CEcoBRE1EnumMatches_0E0B7D40* pCMe = (CEcoBRE1EnumMatches_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    /* Здесь должна быть реализация сброса позиции */
    
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Clone Function
 * </summary>
 *
 * <description>
 *   Создает копию перечислителя
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1EnumMatches_0E0B7D40_Clone(/* in */ IEcoRegEx1EnumMatchesPtr_t me, /* out */ IEcoRegEx1EnumMatchesPtr_t* ppEnum) {
    CEcoBRE1EnumMatches_0E0B7D40* pCMe = (CEcoBRE1EnumMatches_0E0B7D40*)me;
    CEcoBRE1EnumMatches_0E0B7D40* pNewEnum = 0;

    /* Pointer Validation */
    if (me == 0 || ppEnum == 0) {
        return ERR_ECO_POINTER;
    }

    *ppEnum = 0;

    pNewEnum = (CEcoBRE1EnumMatches_0E0B7D40*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBRE1EnumMatches_0E0B7D40));
    if (pNewEnum == 0) {
        return -1;
    }

    memcpy(pNewEnum, pCMe, sizeof(CEcoBRE1EnumMatches_0E0B7D40));
    
    pNewEnum->m_cRef = 1;
    if (pNewEnum->m_pISys != 0) {
        pNewEnum->m_pISys->pVTbl->AddRef(pNewEnum->m_pISys);
    }
    if (pNewEnum->m_pIMem != 0) {
        pNewEnum->m_pIMem->pVTbl->AddRef(pNewEnum->m_pIMem);
    }

    *ppEnum = (IEcoRegEx1EnumMatchesPtr_t)pNewEnum;

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
static int16_t ECOCALLMETHOD initCEcoBRE1EnumMatches_0E0B7D40(/*in*/ CEcoBRE1EnumMatches_0E0B7D40Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBRE1EnumMatches_0E0B7D40* pCMe = (CEcoBRE1EnumMatches_0E0B7D40*)me;
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
static int16_t ECOCALLMETHOD createCEcoBRE1EnumMatches_0E0B7D40(/* in */ CEcoBRE1EnumMatches_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBRE1EnumMatches_0E0B7D40(/* in */ CEcoBRE1EnumMatches_0E0B7D40Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
		if (pCMe->m_matches != 0) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_matches);
            pCMe->m_matches = 0;
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

/* IEcoRegEx1EnumMatches Virtual Table */
IEcoRegEx1EnumMatchesVTbl g_x784F264DDE1444F4B1FF94430059B13BVTbl_0E0B7D40 = {
    CEcoBRE1EnumMatches_0E0B7D40_QueryInterface,
    CEcoBRE1EnumMatches_0E0B7D40_AddRef,
    CEcoBRE1EnumMatches_0E0B7D40_Release,
    CEcoBRE1EnumMatches_0E0B7D40_Next,
    CEcoBRE1EnumMatches_0E0B7D40_Skip,
    CEcoBRE1EnumMatches_0E0B7D40_Reset,
    CEcoBRE1EnumMatches_0E0B7D40_Clone
};


/* Object Instance */
CEcoBRE1EnumMatches_0E0B7D40 g_xCEcoBRE1EnumMatches_0E0B7D40 = {
    &g_x784F264DDE1444F4B1FF94430059B13BVTbl_0E0B7D40,
    initCEcoBRE1EnumMatches_0E0B7D40,
    createCEcoBRE1EnumMatches_0E0B7D40,
    deleteCEcoBRE1EnumMatches_0E0B7D40,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0, /* m_Name */
	0, /* m_matches */
    0, /* m_count */
    0  /* m_current */
};
