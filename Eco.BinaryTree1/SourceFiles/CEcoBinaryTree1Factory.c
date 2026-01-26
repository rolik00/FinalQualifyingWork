/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBinaryTree1Factory
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию фабрики для компонента
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"

#include "CEcoBinaryTree1.h"
#include "CEcoBinaryTree1Factory.h"

extern CEcoBinaryTree1_AF1C3D6C g_xCEcoBinaryTree1_AF1C3D6C;

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция возвращает указатель на интерфейс
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6CFactory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция увеличивает количество ссылок на интерфейс
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6CFactory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoBinaryTree1_AF1C3D6CFactory* pCMe = (CEcoBinaryTree1_AF1C3D6CFactory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return atomicincrement_int32_t(&pCMe->m_cRef);
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция уменьшает количество ссылок на интерфейс
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6CFactory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoBinaryTree1_AF1C3D6CFactory* pCMe = (CEcoBinaryTree1_AF1C3D6CFactory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    atomicdecrement_int32_t(&pCMe->m_cRef);

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализирует компонент с параметрами
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6CFactory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoBinaryTree1_AF1C3D6CFactory* pCMe = (CEcoBinaryTree1_AF1C3D6CFactory*)me;
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 ) {
        return result;
    }

    /* Инициализация компонента c параметрами */

    return result;
}

/*
 *
 * <сводка>
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция создает компонент
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6CFactory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBinaryTree1_AF1C3D6CFactory* pCMe = (CEcoBinaryTree1_AF1C3D6CFactory*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = ERR_ECO_POINTER;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoBinaryTree1_AF1C3D6C* pCObj = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    if (me == 0 || pISystem == 0 ) {
        return result; /* ERR_ECO_POINTER */
    }

    /* Агрегирование при условии если IID это IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* не поддерживает агрегирование */
        return ERR_ECO_NOAGGREGATION;
    }

    /* Получение системного интерфейса приложения */
    result = pISystem->pVTbl->QueryInterface(pISystem, &GID_IEcoSystem, (void **)&pISys);
    /* Проверка */
    if (result != 0 || pISys == 0) {
        return ERR_ECO_NOSYSTEM;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    /* Проверка */
    if (result != 0 || pIBus == 0) {
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_NOBUS;
    }

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Выделение памяти для данных экземпляра */
    pCObj = (CEcoBinaryTree1_AF1C3D6C*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoBinaryTree1_AF1C3D6C));
    if (pCObj == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Формирование данных экземпляра */
    pCObj = (CEcoBinaryTree1_AF1C3D6C*)pIMem->pVTbl->Copy(pIMem, pCObj, &g_xCEcoBinaryTree1_AF1C3D6C, sizeof(CEcoBinaryTree1_AF1C3D6C));

    /* Создание компонента */
    pCObj->Create(pCObj, pISystem, pIUnknownOuter);

    /* Инициализация компонента */
    result = pCObj->Init(pCObj, pISystem);

    /* Получение указателя на интерфейс */
    pIUnk = (IEcoUnknown*)pCObj;
    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);

    /* Уменьшение ссылки запрошенной Фабрикой компонентов */
    pIUnk->pVTbl->Release(pIUnk);

    return result;
}

/*
 *
 * <сводка>
 *   Функция get_Name
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6CFactory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoBinaryTree1_AF1C3D6CFactory* pCMe = (CEcoBinaryTree1_AF1C3D6CFactory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Name;
}

/*
 *
 * <сводка>
 *   Функция get_Version
 * </сводка>
 *
 * <описание>
 *   Функция возвращает версию компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6CFactory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoBinaryTree1_AF1C3D6CFactory* pCMe = (CEcoBinaryTree1_AF1C3D6CFactory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Version;
}

/*
 *
 * <сводка>
 *   Функция get_Manufacturer
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование производителя компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6CFactory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoBinaryTree1_AF1C3D6CFactory* pCMe = (CEcoBinaryTree1_AF1C3D6CFactory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_x7CAD4D0215EF4EDFB1FF6A7CAF1C3D6CFactoryVTbl = {
    CEcoBinaryTree1_AF1C3D6CFactory_QueryInterface,
    CEcoBinaryTree1_AF1C3D6CFactory_AddRef,
    CEcoBinaryTree1_AF1C3D6CFactory_Release,
    CEcoBinaryTree1_AF1C3D6CFactory_Alloc,
    CEcoBinaryTree1_AF1C3D6CFactory_Init,
    CEcoBinaryTree1_AF1C3D6CFactory_get_Name,
    CEcoBinaryTree1_AF1C3D6CFactory_get_Version,
    CEcoBinaryTree1_AF1C3D6CFactory_get_Manufacturer
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
CEcoBinaryTree1_AF1C3D6CFactory g_x7CAD4D0215EF4EDFB1FF6A7CAF1C3D6CFactory = {
    &g_x7CAD4D0215EF4EDFB1FF6A7CAF1C3D6CFactoryVTbl,
    0,
    "EcoBinaryTree1\0",
    "1.0.0.0\0",
    "CompanyName\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_x7CAD4D0215EF4EDFB1FF6A7CAF1C3D6CFactory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_7CAD4D0215EF4EDFB1FF6A7CAF1C3D6C = (IEcoComponentFactory*)&g_x7CAD4D0215EF4EDFB1FF6A7CAF1C3D6CFactory;
#endif