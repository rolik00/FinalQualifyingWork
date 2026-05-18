/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBSA1_F6E9D8E1
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBSA1_F6E9D8E1
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
#include "CEcoBSA1.h"
#include "CEcoBSA1Parser.h"

extern CEcoBSA1Parser_F6E9D8E1 g_xCEcoBSA1Parser_F6E9D8E1;

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoSyntaxAnalyzer1 interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBSA1_F6E9D8E1_QueryInterface(/* in */ IEcoSyntaxAnalyzer1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBSA1_F6E9D8E1* pCMe = (CEcoBSA1_F6E9D8E1*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoSyntaxAnalyzer1) ) {
        *ppv = &pCMe->m_pVTblISyntax;
        pCMe->m_pVTblISyntax->AddRef((IEcoSyntaxAnalyzer1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblISyntax;
        pCMe->m_pVTblISyntax->AddRef((IEcoSyntaxAnalyzer1*)pCMe);
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
 *   AddRef function for the IEcoSyntaxAnalyzer1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBSA1_F6E9D8E1_AddRef(/* in */ IEcoSyntaxAnalyzer1Ptr_t me) {
    CEcoBSA1_F6E9D8E1* pCMe = (CEcoBSA1_F6E9D8E1*)me;

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
 *   Release function for the IEcoSyntaxAnalyzer1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBSA1_F6E9D8E1_Release(/* in */ IEcoSyntaxAnalyzer1Ptr_t me) {
    CEcoBSA1_F6E9D8E1* pCMe = (CEcoBSA1_F6E9D8E1*)me;

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

/*
 *
 * <сводка>
 *   Функция RegisterAlgorithm
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoBSA1_F6E9D8E1_RegisterAlgorithm(/* in */ struct IEcoSyntaxAnalyzer1* me, /*in*/ const UGUID* rcid, /*in*/ char_t* algmName) {
    CEcoBSA1_F6E9D8E1* pCMe = (CEcoBSA1_F6E9D8E1*)me;

    /* Проверка указателей */
    if (me == 0 || rcid == 0 || algmName == 0) {
        return -1;
    }

    pCMe->m_Algorithms->pVTbl->set_Item(pCMe->m_Algorithms, algmName, (void*)rcid);
    if (pCMe->m_AlgorithmName == 0) {
        pCMe->m_AlgorithmName = pCMe->m_pIStr->pVTbl->Clone(pCMe->m_pIStr, algmName);
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция set_DefaultAlgorithm
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoBSA1_F6E9D8E1_set_DefaultAlgorithm(/* in */ struct IEcoSyntaxAnalyzer1* me, /*in*/ char_t* algmName) {
    CEcoBSA1_F6E9D8E1* pCMe = (CEcoBSA1_F6E9D8E1*)me;

    /* Проверка указателей */
    if (me == 0 || algmName == 0) {
        return;
    }

    if (pCMe->m_AlgorithmName != 0) {
        pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pCMe->m_AlgorithmName);
        pCMe->m_AlgorithmName = 0;
    }
    pCMe->m_AlgorithmName = pCMe->m_pIStr->pVTbl->Clone(pCMe->m_pIStr, algmName);

    return;
}

/*
 *
 * <сводка>
 *   Функция get_DefaultAlgorithm
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
char_t* ECOCALLMETHOD CEcoBSA1_F6E9D8E1_get_DefaultAlgorithm(/* in */ struct IEcoSyntaxAnalyzer1* me) {
    CEcoBSA1_F6E9D8E1* pCMe = (CEcoBSA1_F6E9D8E1*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    return pCMe->m_AlgorithmName;
}

/*
 *
 * <сводка>
 *   Функция get_Parser
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
IEcoSyntaxAnalyzer1Parser* ECOCALLMETHOD CEcoBSA1_F6E9D8E1_get_Parser(/* in */ struct IEcoSyntaxAnalyzer1* me, /* in */ IEcoBNF1* pIGrammar, /* in */ char_t* algmName /* 0 - алгоритм по умолчанию */) {
    CEcoBSA1_F6E9D8E1* pCMe = (CEcoBSA1_F6E9D8E1*)me;
    CEcoBSA1Parser_F6E9D8E1Ptr_t pCObj = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoParser1LRk* pIAlgorithm = 0;
    IEcoSyntaxAnalyzer1Parser* pIParser = 0;
    int16_t result = 0;
    UGUID* cidAlgorithm = 0;

    /* Проверка указателей */
    if (me == 0 || pIGrammar == 0) {
        return 0;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    if (algmName != 0) {
        cidAlgorithm = (UGUID*)pCMe->m_Algorithms->pVTbl->get_Item(pCMe->m_Algorithms, algmName);
    }
    else if (pCMe->m_AlgorithmName != 0){
        cidAlgorithm = (UGUID*)pCMe->m_Algorithms->pVTbl->get_Item(pCMe->m_Algorithms, pCMe->m_AlgorithmName);
    }
    else {
        return 0;
    }

    /* Получение интерфейса синтаксического разбора для заданного алгоритма */
    result = pIBus->pVTbl->QueryComponent(pIBus, cidAlgorithm, 0, &IID_IEcoParser1LRk, (void**) &pIAlgorithm);
    if (result != 0 || pIAlgorithm == 0) {
        return 0;
    }
    /* Инициализаци интерфейса синтаксического разбора для заданного алгоритма */
    result = pIAlgorithm->pVTbl->InitByGrammar(pIAlgorithm, pIGrammar, 1); // Refactoring
    if (result != 0) {
        return 0;
    }

    /* Создание обработчика синтаксического разбора */

    /* Выделение памяти для данных экземпляра */
    pCObj = (CEcoBSA1Parser_F6E9D8E1Ptr_t)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBSA1Parser_F6E9D8E1));
    /* Формирование данных экземпляра */
    pCObj = (CEcoBSA1Parser_F6E9D8E1Ptr_t)pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, pCObj, &g_xCEcoBSA1Parser_F6E9D8E1, sizeof(CEcoBSA1Parser_F6E9D8E1));
    /* Создание компонента */
    result = pCObj->Create(pCObj, (IEcoUnknown*)pCMe->m_pISys, 0);
    if (result != 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCObj);
        return 0;
    }
    /* Инициализация компонента */
    result = pCObj->Init(pCObj, (IEcoUnknown*)pCMe->m_pISys,  pIAlgorithm);
    if (result != 0) {
        pCObj->Delete(pCObj);
        return 0;
    }

    pIParser = (IEcoSyntaxAnalyzer1ParserPtr_t)pCObj;
 

    pIBus->pVTbl->Release(pIBus);
    pIAlgorithm->pVTbl->Release(pIAlgorithm);

    return pIParser;
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
static int16_t ECOCALLMETHOD initCEcoBSA1_F6E9D8E1(/*in*/ CEcoBSA1_F6E9D8E1Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBSA1_F6E9D8E1* pCMe = (CEcoBSA1_F6E9D8E1*)me;
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

    /* Получение интерфейса для работы со строкой */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void **)&pCMe->m_pIStr);
    if (result != 0 || pCMe->m_pIStr == 0) {
        /* Освобождение в случае ошибки */
        return result;
    }

    /* Создание экземпляра для работы со словарем */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoDictionary1, 0, &IID_IEcoDictionary1, (void **)&pCMe->m_Algorithms);
    if (result != 0 || pCMe->m_Algorithms == 0) {
        /* Освобождение в случае ошибки */
        return result;
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
static int16_t ECOCALLMETHOD createCEcoBSA1_F6E9D8E1(/* in */ CEcoBSA1_F6E9D8E1Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBSA1_F6E9D8E1(/* in */ CEcoBSA1_F6E9D8E1Ptr_t pCMe) {
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

/* IEcoSyntaxAnalyzer1 Virtual Table */
IEcoSyntaxAnalyzer1VTbl g_x223B5731DC7A4109A426AA10962400ABVTbl_F6E9D8E1 = {
    CEcoBSA1_F6E9D8E1_QueryInterface,
    CEcoBSA1_F6E9D8E1_AddRef,
    CEcoBSA1_F6E9D8E1_Release,
    CEcoBSA1_F6E9D8E1_RegisterAlgorithm,
    CEcoBSA1_F6E9D8E1_set_DefaultAlgorithm,
    CEcoBSA1_F6E9D8E1_get_DefaultAlgorithm,
    CEcoBSA1_F6E9D8E1_get_Parser
};


/* Object Instance */
CEcoBSA1_F6E9D8E1 g_xCEcoBSA1_F6E9D8E1 = {
    &g_x223B5731DC7A4109A426AA10962400ABVTbl_F6E9D8E1,
    initCEcoBSA1_F6E9D8E1,
    createCEcoBSA1_F6E9D8E1,
    deleteCEcoBSA1_F6E9D8E1,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_pIStr */
    0, /* m_Algorithms */
    0, /* m_AlgorithmName */
};