/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBinaryTree1_AF1C3D6C
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoBinaryTree1_AF1C3D6C
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
#include "CEcoBinaryTree1Node.h"

extern CEcoBinaryTree1Node_AF1C3D6C g_xCEcoBinaryTree1Node_AF1C3D6C;

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoBinaryTree1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6C_QueryInterface(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBinaryTree1_AF1C3D6C* pCMe = (CEcoBinaryTree1_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoBinaryTree1) ) {
        *ppv = &pCMe->m_pVTblIEcoBinaryTree1;
        pCMe->m_pVTblIEcoBinaryTree1->AddRef((IEcoBinaryTree1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoBinaryTree1;
        pCMe->m_pVTblIEcoBinaryTree1->AddRef((IEcoBinaryTree1*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoBinaryTree1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6C_AddRef(/* in */ IEcoBinaryTree1Ptr_t me) {
    CEcoBinaryTree1_AF1C3D6C* pCMe = (CEcoBinaryTree1_AF1C3D6C*)me;

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
 *   Функция Release для интерфейса IEcoBinaryTree1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6C_Release(/* in */ IEcoBinaryTree1Ptr_t me) {
    CEcoBinaryTree1_AF1C3D6C* pCMe = (CEcoBinaryTree1_AF1C3D6C*)me;

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
 *   Функция CreateNode
 * </сводка>
 *
 * <описание>
 *   Функция создает новую корневую вершину
 * </описание>
 *
 */
IEcoBinaryTree1Node* ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6C_CreateNode(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ voidptr_t data, /* in */ char_t* name) {
    CEcoBinaryTree1_AF1C3D6C* pCMe = (CEcoBinaryTree1_AF1C3D6C*)me;
    CEcoBinaryTree1Node_AF1C3D6C* pCObj= 0;
    IEcoBinaryTree1NodePtr_t pINode = 0;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    /* Создание нового экземпляра узла (вершины дерева) */

    /* Выделение памяти для данных экземпляра */
    pCObj = (CEcoBinaryTree1Node_AF1C3D6C*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBinaryTree1Node_AF1C3D6C));
    if (pCObj == 0) {
        return 0; /* ERR_ECO_OUTOFMEMORY */
    }

    /* Формирование данных экземпляра */
    pCObj = (CEcoBinaryTree1Node_AF1C3D6C*)pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, pCObj, &g_xCEcoBinaryTree1Node_AF1C3D6C, sizeof(CEcoBinaryTree1Node_AF1C3D6C));
    result = pCObj->Create(pCObj, (IEcoUnknownPtr_t)pCMe->m_pISys, 0);
    result = pCObj->Init(pCObj, (IEcoUnknownPtr_t)pCMe->m_pISys);
	pINode = (IEcoBinaryTree1NodePtr_t)pCObj;
	
    if (result == 0 && pINode != 0) {
        /* Установка данных узла */
        pINode->pVTbl->set_Data(pINode, data);
        pINode->pVTbl->set_Name(pINode, name);
        
		if (pCMe->m_pRoot == 0) {
            pCMe->m_pRoot = pINode;
            pINode->pVTbl->AddRef(pINode);
        }
    }
	else {
        if (pCObj != 0) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCObj);
        }
        return 0;
    }

    return pINode;
}

/*
 *
 * <сводка>
 *   Функция InsertNode
 * </сводка>
 *
 * <описание>
 *   Функция подвешивает вершину child к вершине parent  
 * </описание>
 *
 */
IEcoBinaryTree1Node* ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6C_InsertNode(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ IEcoBinaryTree1NodePtr_t parent, /* in */ IEcoBinaryTree1NodePtr_t child) {
    CEcoBinaryTree1_AF1C3D6C* pCMe = (CEcoBinaryTree1_AF1C3D6C*)me;

    /* Проверка указателей */
    if (me == 0 || child == 0) {
        return 0;
    }

    /* Если родитель не указан, пытаемся сделать корнем */
    if (parent == 0) {
        if (pCMe->m_pRoot == 0) {
            pCMe->m_pRoot = child;
            child->pVTbl->AddRef(child);
            return child;
        } else {
            return 0; /* Корень уже есть */
        }
    }

	/* Логика бинарной вставки */
    if (parent->pVTbl->get_Left(parent) == 0) {
        parent->pVTbl->set_Left(parent, child);
        child->pVTbl->set_Parent(child, parent);
    } 
    else if (parent->pVTbl->get_Right(parent) == 0) {
        parent->pVTbl->set_Right(parent, child);
        child->pVTbl->set_Parent(child, parent);
    }
    else {
        return 0; /* У узла уже два потомка */
    }

    child->pVTbl->AddRef(child);

    return child;
}

/*
 *
 * <сводка>
 *   Функция InsertNodeByData
 * </сводка>
 *
 * <описание>
 *   Функция cоздает вершину с данными, как потомка вершины parent
 * </описание>
 *
 */
IEcoBinaryTree1Node* ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6C_InsertNodeByData(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ IEcoBinaryTree1NodePtr_t parent, /* in */ voidptr_t data, /* in */ char_t* name) {
    IEcoBinaryTree1NodePtr_t pINode = 0;

    /* Проверка указателей */
    if (me == 0 || parent == 0) {
        return 0; 
    }

    /* Создание и добавление нового узла */
    pINode = me->pVTbl->CreateNode(me, data, name);
    if (pINode != 0 && parent != 0) {
        IEcoBinaryTree1NodePtr_t inserted = me->pVTbl->InsertNode(me, parent, pINode);
        if (inserted == 0) {
            pINode->pVTbl->Release(pINode);
            return 0;
        } 
    }

    /* Возвращение результата*/
    return pINode;
}

/*
 *
 * <сводка>
 *   Функция DeleteNode
 * </сводка>
 *
 * <описание>
 *   Функция удаляет вершину (и ее поддерево) из дерева
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6C_DeleteNode(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ IEcoBinaryTree1NodePtr_t node) {
    CEcoBinaryTree1_AF1C3D6C* pCMe = (CEcoBinaryTree1_AF1C3D6C*)me;
    IEcoBinaryTree1NodePtr_t parent = 0;

    /* Проверка указателей */
    if (me == 0 || node == 0) {
        return 0;
    }

    /* Если удаляем корень */
    if (node == pCMe->m_pRoot) {
        pCMe->m_pRoot = 0;
    }
    else {
        /* Отвязываем от родителя */
        parent = node->pVTbl->get_Parent(node);
        if (parent != 0) {
            if (parent->pVTbl->get_Left(parent) == node) {
                parent->pVTbl->set_Left(parent, 0);
            }
            else if (parent->pVTbl->get_Right(parent) == node) {
                parent->pVTbl->set_Right(parent, 0);
            }
        }
    }

    /* Удаление вершины */
    return node->pVTbl->Release(node);
}

/* <метод>
 *   Clear
 * </метод>
 * <описание>
 *   Очищает дерево
 * </описание>
 */
int16_t ECOCALLMETHOD CEcoBinaryTree1_AF1C3D6C_Clear(/* in */ IEcoBinaryTree1Ptr_t me) {
    CEcoBinaryTree1_AF1C3D6C* pCMe = (CEcoBinaryTree1_AF1C3D6C*)me;
    
    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    /* Очистка */
    if (pCMe->m_pRoot != 0) {
        pCMe->m_pRoot->pVTbl->Release(pCMe->m_pRoot);
        pCMe->m_pRoot = 0;
    }

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
static int16_t ECOCALLMETHOD initCEcoBinaryTree1_AF1C3D6C(/*in*/ CEcoBinaryTree1_AF1C3D6CPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBinaryTree1_AF1C3D6C* pCMe = (CEcoBinaryTree1_AF1C3D6C*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = ERR_ECO_POINTER;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    if (me == 0 ) return result;

    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение MemoryAllocator */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }
    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);

    pIBus->pVTbl->Release(pIBus);
    
    pCMe->m_pRoot = 0; /* Обнуляем корень */

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
static int16_t ECOCALLMETHOD createCEcoBinaryTree1_AF1C3D6C(/* in */ CEcoBinaryTree1_AF1C3D6CPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBinaryTree1_AF1C3D6C(/* in */ CEcoBinaryTree1_AF1C3D6CPtr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
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

/* Виртуальная таблица IEcoBinaryTree1 */
IEcoBinaryTree1VTbl g_xCEFEBA6D8A9546EBBE4C1EE7F6195168VTbl_AF1C3D6C = {
    CEcoBinaryTree1_AF1C3D6C_QueryInterface,
    CEcoBinaryTree1_AF1C3D6C_AddRef,
    CEcoBinaryTree1_AF1C3D6C_Release,
    CEcoBinaryTree1_AF1C3D6C_CreateNode,
    CEcoBinaryTree1_AF1C3D6C_InsertNode,
    CEcoBinaryTree1_AF1C3D6C_InsertNodeByData,
    CEcoBinaryTree1_AF1C3D6C_DeleteNode,
    CEcoBinaryTree1_AF1C3D6C_Clear
};

/* Экземпляр объекта */
CEcoBinaryTree1_AF1C3D6C g_xCEcoBinaryTree1_AF1C3D6C = {
    &g_xCEFEBA6D8A9546EBBE4C1EE7F6195168VTbl_AF1C3D6C,
    initCEcoBinaryTree1_AF1C3D6C,
    createCEcoBinaryTree1_AF1C3D6C,
    deleteCEcoBinaryTree1_AF1C3D6C,
    1, /* m_cRef */
    0, /* m_pIMem */
	0, /* m_pIString */
    0, /* m_pISys */
    0, /* m_Name */
	0  /* m_pRoot */
};