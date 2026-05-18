/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoASTPrintVisitor
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoASTPrintVisitor
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoASTPrintVisitor.h"
#include "IEcoTree1.h"
#include "IEcoAST1.h"
#include "IEcoTreePrintVisitor.h"
#include "CEcoTreePrintVisitor.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoASTPrintVisitor
 * </описание>
 *
 */
int16_t CEcoASTPrintVisitor_QueryInterface(/* in */ struct IEcoASTPrintVisitor* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoASTPrintVisitor) ) {
        *ppv = &pCMe->m_pVTblIPrint;
        pCMe->m_pVTblIPrint->AddRef((IEcoASTPrintVisitor*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIPrint;
        pCMe->m_pVTblIPrint->AddRef((IEcoASTPrintVisitor*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoVisitor1) ) {
        *ppv = &pCMe->m_pVTblIVisitor;
        pCMe->m_pVTblIPrint->AddRef((IEcoASTPrintVisitor*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoASTPrintVisitor
 * </описание>
 *
 */
uint32_t CEcoASTPrintVisitor_AddRef(/* in */ struct IEcoASTPrintVisitor* me) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoASTPrintVisitor
 * </описание>
 *
 */
uint32_t CEcoASTPrintVisitor_Release(/* in */ struct IEcoASTPrintVisitor* me) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoASTPrintVisitor((IEcoASTPrintVisitor*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoVisitor1
 * </описание>
 *
 */
int16_t CEcoASTPrintVisitor_IEcoVisitor1_QueryInterface(/* in */ struct IEcoVisitor1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)((uint64_t)me - sizeof(struct IEcoASTPrintVisitor*));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoVisitor1) ) {
        *ppv = &pCMe->m_pVTblIVisitor;
        pCMe->m_pVTblIPrint->AddRef((IEcoASTPrintVisitor*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIPrint;
        pCMe->m_pVTblIPrint->AddRef((IEcoASTPrintVisitor*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoASTPrintVisitor) ) {
        *ppv = &pCMe->m_pVTblIPrint;
        pCMe->m_pVTblIPrint->AddRef((IEcoASTPrintVisitor*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoVisitor1
 * </описание>
 *
 */
uint32_t CEcoASTPrintVisitor_IEcoVisitor1_AddRef(/* in */ struct IEcoVisitor1* me) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)((uint64_t)me - sizeof(struct IEcoASTPrintVisitor*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoVisitor1
 * </описание>
 *
 */
uint32_t CEcoASTPrintVisitor_IEcoVisitor1_Release(/* in */ struct IEcoVisitor1* me) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)((uint64_t)me - sizeof(struct IEcoASTPrintVisitor*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoASTPrintVisitor((IEcoASTPrintVisitor*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция set_Logger
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoASTPrintVisitor_set_Logger(/* in */ struct IEcoASTPrintVisitor* me, /* in */ IEcoLog1* pILog) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    /* Присвоение */
    pCMe->m_pILog = pILog;

    return;
}

/*
 *
 * <сводка>
 *   Функция Accept
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t CEcoASTPrintVisitor_IEcoVisitor1_Accept(/* in */ struct IEcoVisitor1* me, /* in */ IEcoUnknown* pIUnk) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)((uint64_t)me - sizeof(struct IEcoASTPrintVisitor*));
    IEcoTreePrintVisitor* pIPrintVisitor = 0;
    IEcoVisitor1* pIVisitor = 0;
    IEcoAST1* pIAST = 0;
    IEcoAST1TranslationUnit* pTU = 0;
    IEcoTree1Node* pRootNode = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;

    if (me == 0 || pIUnk == 0) return -1;

    result = pIUnk->pVTbl->QueryInterface(pIUnk, &IID_IEcoAST1, (void**)&pIAST);
    if (result == 0 && pIAST != 0) {
        pTU = pIAST->pVTbl->get_TranslationUnit(pIAST);
        if (pTU) {
            result = pTU->pVTbl->QueryInterface(pTU, &IID_IEcoTree1Node, (void**)&pRootNode);
            if (result == 0 && pRootNode) {
                createCEcoTreePrintVisitor((IEcoUnknown*)pCMe->m_pISys, 0, &pIPrintVisitor);
                pIPrintVisitor->pVTbl->set_Logger(pIPrintVisitor, pCMe->m_pILog);
                if (pIPrintVisitor->pVTbl->QueryInterface(pIPrintVisitor, &IID_IEcoVisitor1, (void**)&pIVisitor) == 0 && pIVisitor) {
                    if (pRootNode->pVTbl->QueryInterface(pRootNode, &IID_IEcoVisitor1Element, (void**)&pIElement) == 0 && pIElement) {
                        pIElement->pVTbl->Visit(pIElement, pIVisitor);
                        pIElement->pVTbl->Release(pIElement);
                    } else {
                        pCMe->m_pILog->pVTbl->Error(pCMe->m_pILog, "Can't get visitor element from root node");
                    }
                    pIVisitor->pVTbl->Release(pIVisitor);
                } else {
                    pCMe->m_pILog->pVTbl->Error(pCMe->m_pILog, "Can't get tree visitor");
                }
                pIPrintVisitor->pVTbl->Release(pIPrintVisitor);
                pRootNode->pVTbl->Release(pRootNode);
            } else {
                pCMe->m_pILog->pVTbl->Error(pCMe->m_pILog, "Can't get root node from translation unit");
            }
            pTU->pVTbl->Release(pTU);
        } else {
            pCMe->m_pILog->pVTbl->Error(pCMe->m_pILog, "No translation unit in AST");
        }
        pIAST->pVTbl->Release(pIAST);
    } else {
        pCMe->m_pILog->pVTbl->Error(pCMe->m_pILog, "Can't get AST in visitor");
    }
    return result;
}

/* Create Virtual Table */
IEcoASTPrintVisitorVTbl g_x9DC461F530AA4CE6A3734BB7CECF06AAVTbl = {
    CEcoASTPrintVisitor_QueryInterface,
    CEcoASTPrintVisitor_AddRef,
    CEcoASTPrintVisitor_Release,
    CEcoASTPrintVisitor_set_Logger
};

IEcoVisitor1VTbl g_x9DC461F530AA4CE6A3734BB7CECF06AAVTblVisitor = {
    CEcoASTPrintVisitor_IEcoVisitor1_QueryInterface,
    CEcoASTPrintVisitor_IEcoVisitor1_AddRef,
    CEcoASTPrintVisitor_IEcoVisitor1_Release,
    CEcoASTPrintVisitor_IEcoVisitor1_Accept
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t createCEcoASTPrintVisitor(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoASTPrintVisitor** ppIVisitor) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoASTPrintVisitor* pCMe = 0;

    /* Проверка указателей */
    if (ppIVisitor == 0 || pIUnkSystem == 0) {
        return result;
    }

   /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение интерфейса распределителя памяти */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoASTPrintVisitor*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoASTPrintVisitor));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;
    pCMe->m_pIBus = pIBus;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoASTPrintVisitor1 */
    pCMe->m_pVTblIPrint = &g_x9DC461F530AA4CE6A3734BB7CECF06AAVTbl;

    /* Создание таблицы функций интерфейса IEcoVisitor1 */
    pCMe->m_pVTblIVisitor = &g_x9DC461F530AA4CE6A3734BB7CECF06AAVTblVisitor;

    /* Получение интерфейса для работы со строкой */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**) &pCMe->m_pIString);
    if (result != 0 || pCMe->m_pIString == 0) {
        /* Освобождение в случае ошибки */
        deleteCEcoASTPrintVisitor((IEcoASTPrintVisitor*)pCMe);
    }

    /* Инициализация данных */
    pCMe->m_pILog = 0;

    /* Возврат указателя на интерфейс */
    *ppIVisitor = (IEcoASTPrintVisitor*)pCMe;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void deleteCEcoASTPrintVisitor(/* in */ IEcoASTPrintVisitor* pIVisitor) {
    CEcoASTPrintVisitor* pCMe = (CEcoASTPrintVisitor*)pIVisitor;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIVisitor != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_pIString != 0 ) {
            pCMe->m_pIString->pVTbl->Release(pCMe->m_pIString);
        }
        if (pCMe->m_pISys != 0) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        if (pCMe->m_pIBus != 0) {
            pCMe->m_pIBus->pVTbl->Release(pCMe->m_pIBus);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
