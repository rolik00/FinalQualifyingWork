/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBRE1Builder_0E0B7D40
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBRE1Builder_0E0B7D40
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
#include "CEcoBRE1Builder.h"
#include "IdEcoBinaryTree1.h"
#include "CEcoBRE1RegEx.h"
#include "IEcoRegEx1Builder.h"

extern int16_t ECOCALLMETHOD createCEcoBRE1RegEx_0E0B7D40(CEcoBRE1RegEx_0E0B7D40Ptr_t, IEcoUnknownPtr_t, IEcoUnknownPtr_t, IEcoRegEx1Ptr_t*);
extern CEcoBRE1RegEx_0E0B7D40 g_xCEcoBRE1RegEx_0E0B7D40;

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoRegEx1Builder interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_QueryInterface(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoRegEx1Builder) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1Builder;
        pCMe->m_pVTblIEcoRegEx1Builder->AddRef((IEcoRegEx1Builder*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1Builder;
        pCMe->m_pVTblIEcoRegEx1Builder->AddRef((IEcoRegEx1Builder*)pCMe);
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
 *   AddRef function for the IEcoRegEx1Builder interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_AddRef(/* in */ IEcoRegEx1BuilderPtr_t me) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;

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
 *   Release function for the IEcoRegEx1Builder interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_Release(/* in */ IEcoRegEx1BuilderPtr_t me) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;

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

/* Вспомогательная функция для выделения и инициализации данных узла */
EcoRegEx1NodeData* AllocNodeData(CEcoBRE1Builder_0E0B7D40* pCMe, EcoRegEx1NodeType type) {
	uint32_t i;
	char* ptr;
    EcoRegEx1NodeData* pData = (EcoRegEx1NodeData*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoRegEx1NodeData));
    if (pData) {
        ptr = (char*)pData;
        for(i = 0; i < sizeof(EcoRegEx1NodeData); i++) ptr[i] = 0;
        pData->type = (uint32_t)type;
    }
    return pData;
}

/* Создание узла дерева с привязкой данных */
IEcoBinaryTree1Node* CreateNodeWithData(CEcoBRE1Builder_0E0B7D40* pCMe, EcoRegEx1NodeData* pData) {
    IEcoBinaryTree1Node* pNode = 0;

    if (pCMe->m_pBinaryTree == 0) return 0;

    pNode = pCMe->m_pBinaryTree->pVTbl->CreateNode(pCMe->m_pBinaryTree, 0, 0);

    if (pNode != 0 && pData != 0) {
        pNode->pVTbl->set_Data(pNode, pData);
    }
    return pNode;
}

/*
 *
 * <summary>
 *   CreateLiteral Function
 * </summary>
 *
 * <description>
 *   CreateLiteral Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateLiteral(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ uint32_t c) {
    CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;

	if (me == 0) return 0;
	
	pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_LITERAL);

    if (pData) pData->data.literal.codePoint = c;

    return CreateNodeWithData(pCMe, pData);
}

/*
 *
 * <summary>
 *   CreateAnyChar Function
 * </summary>
 *
 * <description>
 *   CreateAnyChar (.) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateAnyChar(IEcoRegEx1BuilderPtr_t me) {
	CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;

	if (me == 0) return 0;
	
	pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_ANYCHAR);

    return CreateNodeWithData(pCMe, pData);
}

/*
 *
 * <summary>
 *   CreateRange Function
 * </summary>
 *
 * <description>
 *   CreateRange (a-z) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateRange(IEcoRegEx1BuilderPtr_t me, uint32_t start, uint32_t end) {
    CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;

	if (me == 0) return 0;
    
    pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_RANGE);
    
    if (pData) {
        pData->data.range.start = start;
        pData->data.range.end = end;
    }
    return CreateNodeWithData(pCMe, pData);
}

/*
 *
 * <summary>
 *   CreateConcat Function
 * </summary>
 *
 * <description>
 *   CreateConcat (AB) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateConcat(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t left, IEcoBinaryTree1NodePtr_t right) {
    CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;
	IEcoBinaryTree1Node* pNode = 0;

	if (me == 0) return 0;

	pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_CONCAT);
    pNode = CreateNodeWithData(pCMe, pData);
    
    if (pNode) {
        if (left) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, left);
            left->pVTbl->Release(left); 
        }
        if (right) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, right);
            right->pVTbl->Release(right);
        }
    }

    return pNode;
}

/*
 *
 * <summary>
 *   CreateAlternation Function
 * </summary>
 *
 * <description>
 *   CreateAlternation (A|B) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateAlternation(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t left, IEcoBinaryTree1NodePtr_t right) {
    CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;
	IEcoBinaryTree1Node* pNode = 0;

	if (me == 0) return 0;

	pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_ALTERNATION);
    pNode = CreateNodeWithData(pCMe, pData);
    
    if (pNode) {
        if (left) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, left);
            left->pVTbl->Release(left);
        }
        if (right) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, right);
            right->pVTbl->Release(right);
        }
    }

    return pNode;
}

IEcoBinaryTree1Node* CreateQuantifierNode(CEcoBRE1Builder_0E0B7D40* pCMe, IEcoBinaryTree1Node* child, uint32_t min, uint32_t max) {
    EcoRegEx1NodeData* pData = AllocNodeData(pCMe, ECO_REGEX_NODE_QUANTIFIER);
    IEcoBinaryTree1Node* pNode = 0;
    if (pData) {
        pData->data.quantifier.min = min;
        pData->data.quantifier.max = max; /* 0xFFFFFFFF = infinity */
        pData->data.quantifier.isGreedy = 1;
        pNode = CreateNodeWithData(pCMe, pData);
        if (pNode && child) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, child);
			child->pVTbl->Release(child);
        }
    }
    return pNode;
}

/*
 *
 * <summary>
 *   CreateStar Function
 * </summary>
 *
 * <description>
 *   CreateStar (A*) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateStar(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child) {
    return CreateQuantifierNode((CEcoBRE1Builder_0E0B7D40*)me, child, 0, 0xFFFFFFFF);
}

/*
 *
 * <summary>
 *   CreatePlus Function
 * </summary>
 *
 * <description>
 *   CreatePlus (A+) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreatePlus(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child) {
    return CreateQuantifierNode((CEcoBRE1Builder_0E0B7D40*)me, child, 1, 0xFFFFFFFF);
}

/*
 *
 * <summary>
 *   CreateOptional Function
 * </summary>
 *
 * <description>
 *   CreateOptional (A?) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateOptional(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child) {
    return CreateQuantifierNode((CEcoBRE1Builder_0E0B7D40*)me, child, 0, 1);
}

/*
 *
 * <summary>
 *   CreateRepeat Function
 * </summary>
 *
 * <description>
 *   CreateRepeat (A{n,m}) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateRepeat(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child, uint32_t min, uint32_t max) {
    return CreateQuantifierNode((CEcoBRE1Builder_0E0B7D40*)me, child, min, max);
}

/*
 *
 * <summary>
 *   CreateGroup Function
 * </summary>
 *
 * <description>
 *   CreateGroup () Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateGroup(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child, uint32_t index) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    EcoRegEx1NodeData* pData = AllocNodeData(pCMe, ECO_REGEX_NODE_GROUP);
    IEcoBinaryTree1Node* pNode = 0;
    if (pData) {
        pData->data.group.index = index;
        pNode = CreateNodeWithData(pCMe, pData);
        if (pNode && child) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, child);
			child->pVTbl->Release(child);
		}
    }
    return pNode;
}

/* Строит из синтасического дерева конечный автомат */
static int16_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_Build(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t root, IEcoRegEx1Ptr_t* ppIRegex) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
	int16_t result = ERR_ECO_POINTER;
	CEcoBRE1RegEx_0E0B7D40* pRegExImpl = 0;

    if (me == 0 || root == 0 || ppIRegex == 0) {
        return result;
    }

	result = createCEcoBRE1RegEx_0E0B7D40(&g_xCEcoBRE1RegEx_0E0B7D40, (IEcoUnknown*)pCMe->m_pISys, 0, ppIRegex);
	if (result == 0 && *ppIRegex != 0) {
        pRegExImpl = (CEcoBRE1RegEx_0E0B7D40*)*ppIRegex;
        pRegExImpl->m_pRoot = root;
        root->pVTbl->AddRef(root);
    }

    return result;
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
int16_t ECOCALLMETHOD initCEcoBRE1Builder_0E0B7D40(/*in*/ CEcoBRE1Builder_0E0B7D40Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
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

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBinaryTree1, 0, &IID_IEcoBinaryTree1, (void**)&pCMe->m_pBinaryTree);

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
int16_t ECOCALLMETHOD createCEcoBRE1Builder_0E0B7D40(/* in */ CEcoBRE1Builder_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* in */ IEcoRegEx1BuilderPtr_t* ppIBuilder) {
    int16_t result = ERR_ECO_POINTER;
    CEcoBRE1Builder_0E0B7D40* pNewObj = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    if (pCMe == 0 || pIUnkSystem == 0 || ppIBuilder == 0) {
        return ERR_ECO_POINTER;
    }

    /* Получаем системный интерфейс */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);
    if (result != 0 || pISys == 0) {
        return ERR_ECO_NOSYSTEM;
    }

    /* Получаем интерфейсную шину */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_NOBUS;
    }

    /* Получаем менеджер памяти */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получаем аллокатор памяти */
    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Выделяем память под новый объект */
    pNewObj = (CEcoBRE1Builder_0E0B7D40*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoBRE1Builder_0E0B7D40));
    if (pNewObj == 0) {
        pIMem->pVTbl->Release(pIMem);
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Копируем данные из шаблона */
    pNewObj = (CEcoBRE1Builder_0E0B7D40*)pIMem->pVTbl->Copy(pIMem, pNewObj, pCMe, sizeof(CEcoBRE1Builder_0E0B7D40));
    
    /* Инициализируем поля */
    pNewObj->m_cRef = 1;
    pNewObj->m_pIMem = pIMem;
    pIMem->pVTbl->AddRef(pIMem);
    
    pNewObj->m_pISys = pISys;
    pISys->pVTbl->AddRef(pISys);
    
    pNewObj->m_Name = 0;
    pNewObj->m_pBinaryTree = 0;

    /* Возвращаем указатель на интерфейс */
    *ppIBuilder = (IEcoRegEx1BuilderPtr_t)pNewObj;

    pIBus->pVTbl->Release(pIBus);

    return 0; /* ERR_ECO_SUCCESES */
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
static void ECOCALLMETHOD deleteCEcoBRE1Builder_0E0B7D40(/* in */ CEcoBRE1Builder_0E0B7D40Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
		if (pCMe->m_pBinaryTree != 0) {
            pCMe->m_pBinaryTree->pVTbl->Release(pCMe->m_pBinaryTree);
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

/* IEcoRegEx1Builder Virtual Table */
IEcoRegEx1BuilderVTbl g_x38E665D3C7B94BD098540E96A232BF40VTbl_0E0B7D40 = {
    CEcoBRE1Builder_0E0B7D40_QueryInterface,
    CEcoBRE1Builder_0E0B7D40_AddRef,
    CEcoBRE1Builder_0E0B7D40_Release,
    CEcoBRE1Builder_0E0B7D40_CreateLiteral,
	CEcoBRE1Builder_0E0B7D40_CreateAnyChar,
    CEcoBRE1Builder_0E0B7D40_CreateRange,
	CEcoBRE1Builder_0E0B7D40_CreateConcat,
    CEcoBRE1Builder_0E0B7D40_CreateAlternation,
    CEcoBRE1Builder_0E0B7D40_CreateStar,
    CEcoBRE1Builder_0E0B7D40_CreatePlus,
    CEcoBRE1Builder_0E0B7D40_CreateOptional,
    CEcoBRE1Builder_0E0B7D40_CreateRepeat,
	CEcoBRE1Builder_0E0B7D40_CreateGroup,
    CEcoBRE1Builder_0E0B7D40_Build
};



/* Object Instance */
CEcoBRE1Builder_0E0B7D40 g_xCEcoBRE1Builder_0E0B7D40 = {
    &g_x38E665D3C7B94BD098540E96A232BF40VTbl_0E0B7D40,
    initCEcoBRE1Builder_0E0B7D40,
    createCEcoBRE1Builder_0E0B7D40,
    deleteCEcoBRE1Builder_0E0B7D40,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pIMem */
    0, /* m_Name */
	0  /* m_pBinaryTree */
};
