/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBinaryTree1Node_AF1C3D6C
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoBinaryTree1Node_AF1C3D6C
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
#include "CEcoBinaryTree1Node.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoBinaryTree1Node
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_QueryInterface(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoBinaryTree1Node) ) {
        *ppv = &pCMe->m_pVTblIEcoBinaryTree1Node;
        pCMe->m_pVTblIEcoBinaryTree1Node->AddRef((IEcoBinaryTree1Node*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoBinaryTree1Node;
        pCMe->m_pVTblIEcoBinaryTree1Node->AddRef((IEcoBinaryTree1Node*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoBinaryTree1Node
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_AddRef(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателя */
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
 *   Функция Release для интерфейса IEcoBinaryTree1Node
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_Release(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    atomicdecrement_int32_t(&pCMe->m_cRef);
    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        pCMe->Delete(pCMe);
        return 0;
    }

    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция get_Data
 * </сводка>
 *
 * <описание>
 *   Функция возвращает данные
 * </описание>
 *
 */
static voidptr_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_get_Data(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Возвращение результата */
    return pCMe->m_pData;
}

/*
 *
 * <сводка>
 *   Функция set_Data
 * </сводка>
 *
 * <описание>
 *   Функция устаналивает данные
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_set_Data(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ voidptr_t value) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    /* Установка значений */
    pCMe->m_pData = value;
}

/*
 *
 * <сводка>
 *   Функция get_Name
 * </сводка>
 *
 * <описание>
 *   Функция возвращает данные
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_get_Name(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Возвращение результата */
    return pCMe->m_pName;
}

/*
 *
 * <сводка>
 *   Функция set_Name
 * </сводка>
 *
 * <описание>
 *   Функция устаналивает данные
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_set_Name(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ char_t* value) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;
    uint32_t len = 0;
    uint32_t i = 0;

    /* Проверка указателей */
    if (me == 0 || value == 0) {
        return;
    }

    /* Освобождаем старое имя, если было */
    if (pCMe->m_pName != 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCMe->m_pName);
        pCMe->m_pName = 0;
    }

    /* Вычисляем длину строки вручную (чтобы не подключать string.h) */
    while (value[len] != 0) {
        len++;
    }

    /* Выделяем память: длина + 1 байт для нуль-терминатора */
    pCMe->m_pName = (char_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, len + 1);

    if (pCMe->m_pName != 0) {
        /* Копируем символы вручную */
        for (i = 0; i <= len; i++) {
            pCMe->m_pName[i] = value[i];
        }
    }
}

/*
 *
 * <сводка>
 *   Функция get_Parent
 * </сводка>
 *
 * <описание>
 *   Функция возвращает родителя узла
 * </описание>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_get_Parent(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Возвращение результата */
    return pCMe->m_pIParent;
}

/*
 *
 * <сводка>
 *   Функция set_Parent
 * </сводка>
 *
 * <описание>
 *   Функция меняет родителя узла
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_set_Parent(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ IEcoBinaryTree1NodePtr_t parent) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    /* Установка родителя */
    pCMe->m_pIParent = parent;
}

/*
 *
 * <сводка>
 *   Функция get_Left
 * </сводка>
 *
 * <описание>
 *   Функция возвращает левый узел
 * </описание>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_get_Left(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Возвращение результата */
    return pCMe->m_pILeft;
}

/*
 *
 * <сводка>
 *   Функция set_Left
 * </сводка>
 *
 * <описание>
 *   Функция устанавливает левый узел
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_set_Left(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ IEcoBinaryTree1NodePtr_t node) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    /* Установка результата */
    pCMe->m_pILeft = node;
}


/*
 *
 * <сводка>
 *   Функция get_Right
 * </сводка>
 *
 * <описание>
 *   Функция возвращает правый узел
 * </описание>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_get_Right(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Возвращение результата */
    return pCMe->m_pIRight;
}

/*
 *
 * <сводка>
 *   Функция set_Right
 * </сводка>
 *
 * <описание>
 *   Функция устанавливает правый узел
 * </описание>
 *
 */
static void ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_set_Right(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ IEcoBinaryTree1NodePtr_t node) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    /* Установка результата */
    pCMe->m_pIRight = node;
}


/*
 *
 * <сводка>
 *   Функция IsRoot
 * </сводка>
 *
 * <описание>
 *   Функция возвращает 1, если вершина является корнем, иначе - 0
 * </описание>
 *
 */
static bool_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_IsRoot(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Проверка наличия родителя */
    if (pCMe->m_pIParent == 0)
        return 1;
    else
        return 0;
}

/*
 *
 * <сводка>
 *   Функция IsLeaf
 * </сводка>
 *
 * <описание>
 *   Функция возвращает 1, если вершина является листом, иначе - 0
 * </описание>
 *
 */
static bool_t ECOCALLMETHOD CEcoBinaryTree1Node_AF1C3D6C_IsLeaf(/* in */ IEcoBinaryTree1NodePtr_t me) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Проверка наличия потомков */
    if ( (pCMe->m_pILeft == 0) && (pCMe->m_pIRight == 0) )
        return 1;
    else
        return 0;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD initCEcoBinaryTree1Node_AF1C3D6C(/*in*/ CEcoBinaryTree1Node_AF1C3D6CPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBinaryTree1Node_AF1C3D6C* pCMe = (CEcoBinaryTree1Node_AF1C3D6C*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = ERR_ECO_POINTER;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);
    /* Проверка */
    if (result != 0 || pCMe->m_pIMem == 0) {
        result = ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

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
static int16_t ECOCALLMETHOD createCEcoBinaryTree1Node_AF1C3D6C(/* in */ CEcoBinaryTree1Node_AF1C3D6CPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
    int16_t result = ERR_ECO_POINTER;

    /* Проверка указателей */
    if (pCMe == 0) {
        return result; /* ERR_ECO_POINTER */
    }

    return ERR_ECO_SUCCESES;
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
static void ECOCALLMETHOD deleteCEcoBinaryTree1Node_AF1C3D6C(/* in */ CEcoBinaryTree1Node_AF1C3D6CPtr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        
		/* РЕКУРСИВНОЕ ОСВОБОЖДЕНИЕ ПОТОМКОВ */
        if (pCMe->m_pILeft != 0) {
            pCMe->m_pILeft->pVTbl->set_Parent(pCMe->m_pILeft, 0); 
            pCMe->m_pILeft->pVTbl->Release(pCMe->m_pILeft);
        }
        if (pCMe->m_pIRight != 0) {
            pCMe->m_pIRight->pVTbl->set_Parent(pCMe->m_pIRight, 0);
            pCMe->m_pIRight->pVTbl->Release(pCMe->m_pIRight);
        }

		if ( pCMe->m_pName != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_pName);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}


/* Виртуальная таблица IEcoBinaryTree1Node */
IEcoBinaryTree1NodeVTbl g_xC77EFA7FF12B4852969E0A1508B62022VTbl_AF1C3D6C = {
    CEcoBinaryTree1Node_AF1C3D6C_QueryInterface,
    CEcoBinaryTree1Node_AF1C3D6C_AddRef,
    CEcoBinaryTree1Node_AF1C3D6C_Release,
    CEcoBinaryTree1Node_AF1C3D6C_get_Data,
    CEcoBinaryTree1Node_AF1C3D6C_set_Data,
    CEcoBinaryTree1Node_AF1C3D6C_get_Name,
    CEcoBinaryTree1Node_AF1C3D6C_set_Name,
    CEcoBinaryTree1Node_AF1C3D6C_get_Parent,
    CEcoBinaryTree1Node_AF1C3D6C_set_Parent,
    CEcoBinaryTree1Node_AF1C3D6C_get_Left,
    CEcoBinaryTree1Node_AF1C3D6C_set_Left,
    CEcoBinaryTree1Node_AF1C3D6C_get_Right,
    CEcoBinaryTree1Node_AF1C3D6C_set_Right,
    CEcoBinaryTree1Node_AF1C3D6C_IsRoot,
    CEcoBinaryTree1Node_AF1C3D6C_IsLeaf,
};

/* Экземпляр объекта */
CEcoBinaryTree1Node_AF1C3D6C g_xCEcoBinaryTree1Node_AF1C3D6C = {
    &g_xC77EFA7FF12B4852969E0A1508B62022VTbl_AF1C3D6C,
    initCEcoBinaryTree1Node_AF1C3D6C,
    createCEcoBinaryTree1Node_AF1C3D6C,
    deleteCEcoBinaryTree1Node_AF1C3D6C,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0, /* m_pILeft */
    0, /* m_pIRight */
    0, /* m_pIParent */
    0, /* m_pData */
    0, /* m_pName */
};