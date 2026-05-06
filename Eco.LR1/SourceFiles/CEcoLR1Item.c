/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLR1Item_A441A18E
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoLR1Item_A441A18E
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
#include "CEcoLR1Item.h"
#include "IEcoContainer1.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoParser1LRkItem interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLR1Item_A441A18E_QueryInterface(/* in */ IEcoParser1LRkItemPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoParser1LRkItem) ) {
        *ppv = &pCMe->m_pVTblIItem;
        pCMe->m_pVTblIItem->AddRef((IEcoParser1LRkItem*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIItem;
        pCMe->m_pVTblIItem->AddRef((IEcoParser1LRkItem*)pCMe);
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
 *   AddRef function for the IEcoParser1LRkItem interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLR1Item_A441A18E_AddRef(/* in */ IEcoParser1LRkItemPtr_t me) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;

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
 *   Release function for the IEcoParser1LRkItem interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLR1Item_A441A18E_Release(/* in */ IEcoParser1LRkItemPtr_t me) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;

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

static char_t* ECOCALLMETHOD CEcoLR1Item_A441A18E_get_Description(/* in */ IEcoParser1LRkItemPtr_t me) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;
    IEcoBNF1Rule* pIRule = pCMe->m_pIRule;
    IEcoList1* pIElements = 0;
    IEcoBNF1Element* pIElement = 0;
    IEcoContainer1* pIContainer = 0;
    IEcoContainer1Iterator* pIIter = 0;
    uint32_t i = 0;
    char_t* temp = 0;

    /* 1. Если описание актуально — возвращаем кэш */
    if (pCMe->m_Description != 0 && pCMe->m_NeedUpdate == 0) {
        return pCMe->m_Description;
    }

    /* 2. Очистка старого кэша */
    if (pCMe->m_Description != 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCMe->m_Description);
        pCMe->m_Description = 0;
    }

    /* 3. Сборка основной части: "A -> " */
    pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, pIRule->pVTbl->get_Name(pIRule));
    pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, " -> ");

    /* 4. Правая часть с точкой */
    pIElements = (IEcoList1*)pIRule->pVTbl->get_RuleSet(pIRule)->pVTbl->Item(pIRule->pVTbl->get_RuleSet(pIRule), pCMe->m_RuleSetId);
    for (i = 0; i <= pIElements->pVTbl->Count(pIElements); i++) {
        if (i == (uint32_t)pCMe->m_MarkerPosition) {
            pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, ". ");
        }
        if (i < pIElements->pVTbl->Count(pIElements)) {
            pIElement = (IEcoBNF1Element*)pIElements->pVTbl->Item(pIElements, i);
            pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, pIElement->pVTbl->get_Name(pIElement));
            pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, " ");
        }
    }

    /* 5. Добавление Lookahead: ", { a, b }" */
    if (pCMe->m_pINextTerms && pCMe->m_pINextTerms->pVTbl->Count(pCMe->m_pINextTerms) > 0) {
        pCMe->m_pINextTerms->pVTbl->QueryInterface(pCMe->m_pINextTerms, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
        pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, ", { ");
        pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
        while (pIIter && pIIter->pVTbl->Value(pIIter)) {
            temp = (char_t*)pIIter->pVTbl->Value(pIIter);
            pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, temp);
            pIIter->pVTbl->Next(pIIter);
            if (pIIter->pVTbl->Value(pIIter)) {
                pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, ", ");
            }
        }
        if (pIIter) pIIter->pVTbl->Release(pIIter);
        pCMe->m_Description = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pCMe->m_Description, " }");
    }

    pCMe->m_NeedUpdate = 0;
    return pCMe->m_Description;
}


static int16_t ECOCALLMETHOD CEcoLR1Item_A441A18E_get_MarkerPosition(/* in */ IEcoParser1LRkItemPtr_t me) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_MarkerPosition;;
}

static int32_t ECOCALLMETHOD CEcoLR1Item_A441A18E_get_RuleSetId(/* in */ IEcoParser1LRkItemPtr_t me) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_RuleSetId;;
}

static IEcoBNF1Rule* ECOCALLMETHOD CEcoLR1Item_A441A18E_get_Rule(/* in */ IEcoParser1LRkItemPtr_t me) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return pCMe->m_pIRule;
}

static IEcoSet2* ECOCALLMETHOD CEcoLR1Item_A441A18E_get_NextTerms(/* in */ IEcoParser1LRkItemPtr_t me) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return pCMe->m_pINextTerms;
}

static int16_t ECOCALLMETHOD CEcoLR1Item_A441A18E_AddNextTermSet(/* in */ IEcoParser1LRkItemPtr_t me, IEcoSet2* pINewNextTerms) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;
    IEcoContainer1* pIContainer = 0;
    IEcoContainer1Iterator* pIIter = 0;
    void* pValue = 0;
    int16_t changed = -1; /* -1 - изменений нет, 0 - изменения внесены */

    /* 1. Валидация */
    if (pCMe == 0 || pINewNextTerms == 0) return -1;
    if (pCMe->m_pINextTerms == 0) return -1;

    /* 2. Итерация по новому набору символов предпросмотра */
    pINewNextTerms->pVTbl->QueryInterface(pINewNextTerms, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
    pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
    while (pIIter != 0 && pIIter->pVTbl->Value(pIIter) != 0) {
        pValue = pIIter->pVTbl->Value(pIIter);
        
        /* 
           ВАЖНО: IEcoSet1->Add возвращает 0, если элемент РЕАЛЬНО новый.
           Если ваше множество настроено на POINTER_TYPE, убедитесь, 
           что все строки терминалов интернированы (взяты из одной таблицы).
        */
        if (pCMe->m_pINextTerms->pVTbl->Add(pCMe->m_pINextTerms, pValue) == 0) {
            changed = 0;
            pCMe->m_NeedUpdate = 1; /* Описание устарело */
            
            /* Лог для отладки распространения контекста */
            printf("[ITEM_LA] Added '%s' to item %p\n", (char_t*)pValue, (void*)pCMe);
        }
        
        if (pIIter->pVTbl->Next(pIIter) != 0) break;
    }

    if (pIIter) pIIter->pVTbl->Release(pIIter);

    return changed;
}



static int16_t ECOCALLMETHOD CEcoLR1Item_A441A18E_AddNextTerm(/* in */ IEcoParser1LRkItemPtr_t me, char_t* nextTerm) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    if (pCMe->m_pINextTerms->pVTbl->Add(pCMe->m_pINextTerms, nextTerm) == 0) {
        pCMe->m_NeedUpdate = 1; // Помечаем, что описание (строка) устарело
        return ERR_ECO_SUCCESES;
    }
    return ERR_ECO_POINTER;
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
static int16_t ECOCALLMETHOD initCEcoLR1Item_A441A18E(/*in*/ CEcoLR1Item_A441A18EPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoLR1Item_A441A18E* pCMe = (CEcoLR1Item_A441A18E*)me;
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

    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**) &pCMe->m_pIStr);

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
static int16_t ECOCALLMETHOD createCEcoLR1Item_A441A18E(/* in */ CEcoLR1Item_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoLR1Item_A441A18E(/* in */ CEcoLR1Item_A441A18EPtr_t pCMe) {
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

/* IEcoParser1LRkItem Virtual Table */
IEcoParser1LRkItemVTbl g_x70527837F4DD4BFB90B537A41393443CVTbl_A441A18E = {
    CEcoLR1Item_A441A18E_QueryInterface,
    CEcoLR1Item_A441A18E_AddRef,
    CEcoLR1Item_A441A18E_Release,
    CEcoLR1Item_A441A18E_get_Description,
    CEcoLR1Item_A441A18E_get_MarkerPosition,
    CEcoLR1Item_A441A18E_get_RuleSetId,
    CEcoLR1Item_A441A18E_get_Rule,
    CEcoLR1Item_A441A18E_get_NextTerms,
    CEcoLR1Item_A441A18E_AddNextTermSet,
    CEcoLR1Item_A441A18E_AddNextTerm
};



/* Object Instance */
CEcoLR1Item_A441A18E g_xCEcoLR1Item_A441A18E = {
    &g_x70527837F4DD4BFB90B537A41393443CVTbl_A441A18E,
    initCEcoLR1Item_A441A18E,
    createCEcoLR1Item_A441A18E,
    deleteCEcoLR1Item_A441A18E,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0, /* m_pIStr */
    0, /* m_MarkerPosition */
    0, /* m_RuleSetId */
    0, /* m_pIRule */
    0, /* m_Description */
    0, /* m_pINextTerms */
    0 /* m_NeedUpdate */
};
