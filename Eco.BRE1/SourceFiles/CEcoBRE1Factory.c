/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBRE1Factory
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

#include "CEcoBRE1.h"
#include "CEcoBRE1Factory.h"

extern CEcoBRE1_0E0B7D40 g_xCEcoBRE1_0E0B7D40;

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
static int16_t ECOCALLMETHOD CEcoBRE1_0E0B7D40Factory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
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
static uint32_t ECOCALLMETHOD CEcoBRE1_0E0B7D40Factory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoBRE1_0E0B7D40Factory* pCMe = (CEcoBRE1_0E0B7D40Factory*)me;

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
static uint32_t ECOCALLMETHOD CEcoBRE1_0E0B7D40Factory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoBRE1_0E0B7D40Factory* pCMe = (CEcoBRE1_0E0B7D40Factory*)me;

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
static int16_t ECOCALLMETHOD CEcoBRE1_0E0B7D40Factory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoBRE1_0E0B7D40Factory* pCMe = (CEcoBRE1_0E0B7D40Factory*)me;
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
static int16_t ECOCALLMETHOD CEcoBRE1_0E0B7D40Factory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBRE1_0E0B7D40Factory* pCMe = (CEcoBRE1_0E0B7D40Factory*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = ERR_ECO_POINTER;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoBRE1_0E0B7D40* pCObj = 0;
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
    pCObj = (CEcoBRE1_0E0B7D40*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoBRE1_0E0B7D40));
    if (pCObj == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Формирование данных экземпляра */
    pCObj = (CEcoBRE1_0E0B7D40*)pIMem->pVTbl->Copy(pIMem, pCObj, &g_xCEcoBRE1_0E0B7D40, sizeof(CEcoBRE1_0E0B7D40));

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
static char_t* ECOCALLMETHOD CEcoBRE1_0E0B7D40Factory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoBRE1_0E0B7D40Factory* pCMe = (CEcoBRE1_0E0B7D40Factory*)me;

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
static char_t* ECOCALLMETHOD CEcoBRE1_0E0B7D40Factory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoBRE1_0E0B7D40Factory* pCMe = (CEcoBRE1_0E0B7D40Factory*)me;

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
static char_t* ECOCALLMETHOD CEcoBRE1_0E0B7D40Factory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoBRE1_0E0B7D40Factory* pCMe = (CEcoBRE1_0E0B7D40Factory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_x755D526AEBF943E9B4AA4F860E0B7D40FactoryVTbl = {
    CEcoBRE1_0E0B7D40Factory_QueryInterface,
    CEcoBRE1_0E0B7D40Factory_AddRef,
    CEcoBRE1_0E0B7D40Factory_Release,
    CEcoBRE1_0E0B7D40Factory_Alloc,
    CEcoBRE1_0E0B7D40Factory_Init,
    CEcoBRE1_0E0B7D40Factory_get_Name,
    CEcoBRE1_0E0B7D40Factory_get_Version,
    CEcoBRE1_0E0B7D40Factory_get_Manufacturer
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
CEcoBRE1_0E0B7D40Factory g_x755D526AEBF943E9B4AA4F860E0B7D40Factory = {
    &g_x755D526AEBF943E9B4AA4F860E0B7D40FactoryVTbl,
    0,
    "EcoBRE1\0",
    "1.0.0.0\0",
    "CompanyName\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_x755D526AEBF943E9B4AA4F860E0B7D40Factory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_755D526AEBF943E9B4AA4F860E0B7D40 = (IEcoComponentFactory*)&g_x755D526AEBF943E9B4AA4F860E0B7D40Factory;
#endif