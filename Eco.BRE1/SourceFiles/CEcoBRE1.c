/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBRE1_0E0B7D40
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoBRE1_0E0B7D40
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
#include "CEcoBRE1Builder.h" 

extern CEcoBRE1Builder_0E0B7D40 g_xCEcoBRE1Builder_0E0B7D40;

/* Вспомогательная функция: парсинг целого числа */
uint32_t ParseInt(ParseContext* ctx) {
    uint32_t num = 0;
    while (*ctx->current >= '0' && *ctx->current <= '9') {
        num = num * 10 + (*ctx->current - '0');
        ctx->current++;
    }
    return num;
}

IEcoBinaryTree1NodePtr_t ParseExpression(ParseContext* ctx);

/*
 * Парсинг группировки в скобках, символьных литералов (в том числе и '.'), а также диапазонов []
 */
IEcoBinaryTree1NodePtr_t ParseAtom(ParseContext* ctx) {
    IEcoBinaryTree1NodePtr_t node = 0;
    char c = *ctx->current;
	uint32_t start, end;

    if (c == 0 || c == '|' || c == ')' || c == '*' || c == '+' || c == '?' || c == '{') {
        return 0;
    }

    if (c == '.') {
        node = ctx->builder->pVTbl->CreateAnyChar(ctx->builder);
        ctx->current++;
    } else if (c == '(') {
        ctx->current++;
        node = ParseExpression(ctx);
        if (*ctx->current == ')') {
            ctx->current++; 
            node = ctx->builder->pVTbl->CreateGroup(ctx->builder, node, 0);
        } else {
            // Ошибка - не закрыта скобка
            if (node) node->pVTbl->Release(node);
            return 0;
        }
    } else if (c == '[') {
		ctx->current++; 
		if (*ctx->current == 0) return 0;

        start = *ctx->current;
        ctx->current++;
        
        if (*ctx->current == '-') {
			ctx->current++; 

			if (*ctx->current == 0) return 0;

            end = *ctx->current;
			ctx->current++;
        } else {
            end = start;
        }

        if (*ctx->current == ']') {
            ctx->current++; 
        } else {
            // Ошибка - не закрыта скобка
			return 0;
        }
        
        node = ctx->builder->pVTbl->CreateRange(ctx->builder, start, end);
    } else if (c == '\\') {
        ctx->current++;
        if (*ctx->current == 0) return 0;
        
        c = *ctx->current;
        ctx->current++;
        
        node = ctx->builder->pVTbl->CreateLiteral(ctx->builder, (uint32_t)c);
    } else {
        node = ctx->builder->pVTbl->CreateLiteral(ctx->builder, (uint32_t)c);
        ctx->current++;
    }

    return node;
}

/*
 * Парсинг унарных операций повторения (*, +, ?, {n,m})
 */
IEcoBinaryTree1NodePtr_t ParseQuantifier(ParseContext* ctx) {
    IEcoBinaryTree1NodePtr_t node = ParseAtom(ctx);
	char c;
	uint32_t min = 0, max = 0;
    
    if (node == 0) return 0;

    c = *ctx->current;

    if (c == '*') {
        node = ctx->builder->pVTbl->CreateStar(ctx->builder, node);
        ctx->current++;
    } else if (c == '+') {
        node = ctx->builder->pVTbl->CreatePlus(ctx->builder, node);
        ctx->current++;
    } else if (c == '?') {
        node = ctx->builder->pVTbl->CreateOptional(ctx->builder, node);
        ctx->current++;
    } else if (c == '{') {
        ctx->current++;
        
        min = ParseInt(ctx);
        
        if (*ctx->current == ',') {
            ctx->current++;
            if (*ctx->current == '}') {
                max = 0xFFFFFFFF; 
            } else {
                max = ParseInt(ctx);
            }
        } else {
            max = min;
        }

        if (*ctx->current == '}') {
            ctx->current++;
        } else {
            // Ошибка - не закрыта скобка
            node->pVTbl->Release(node);
            return 0;
        }

        node = ctx->builder->pVTbl->CreateRepeat(ctx->builder, node, min, max);
    }

    return node;
}

/*
 * Парсинг бинарной операции конкатенации (AB)
 */
IEcoBinaryTree1NodePtr_t ParseConcat(ParseContext* ctx) {
    IEcoBinaryTree1NodePtr_t left = ParseQuantifier(ctx);
    IEcoBinaryTree1NodePtr_t right = 0;
	IEcoBinaryTree1NodePtr_t newLeft = 0;

	if (left == 0) return 0;

    while (*ctx->current != 0 && *ctx->current != '|' && *ctx->current != ')') {
        right = ParseQuantifier(ctx);

        if (right) {
            newLeft = ctx->builder->pVTbl->CreateConcat(ctx->builder, left, right);
			if (newLeft == 0) {
                left->pVTbl->Release(left);
                right->pVTbl->Release(right);
                return 0;
            }
            left = newLeft;
        } else {
            break;
        }
    }

    return left;
}

/*
 * Парсинг операции чередования (A|B)
 */
IEcoBinaryTree1NodePtr_t ParseExpression(ParseContext* ctx) {
    IEcoBinaryTree1NodePtr_t left = ParseConcat(ctx);
	IEcoBinaryTree1NodePtr_t right = 0;
	IEcoBinaryTree1NodePtr_t newLeft = 0;

	if (left == 0) return 0;
	
    while (*ctx->current == '|') {
		ctx->current++;
        right = ParseConcat(ctx);
		if (right) {
            newLeft = ctx->builder->pVTbl->CreateAlternation(ctx->builder, left, right);
            if (newLeft == 0) {
                left->pVTbl->Release(left);
                right->pVTbl->Release(right);
                return 0;
            }
            left = newLeft;
        }
        else {
            left->pVTbl->Release(left);
            return 0;
        }
    }

	return left;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoBRE1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1_0E0B7D40_QueryInterface(/* in */ IEcoBRE1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBRE1_0E0B7D40* pCMe = (CEcoBRE1_0E0B7D40*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoBRE1) ) {
        *ppv = &pCMe->m_pVTblIEcoBRE1;
        pCMe->m_pVTblIEcoBRE1->AddRef((IEcoBRE1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoBRE1;
        pCMe->m_pVTblIEcoBRE1->AddRef((IEcoBRE1*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoBRE1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1_0E0B7D40_AddRef(/* in */ IEcoBRE1Ptr_t me) {
    CEcoBRE1_0E0B7D40* pCMe = (CEcoBRE1_0E0B7D40*)me;

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
 *   Функция Release для интерфейса IEcoBRE1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1_0E0B7D40_Release(/* in */ IEcoBRE1Ptr_t me) {
    CEcoBRE1_0E0B7D40* pCMe = (CEcoBRE1_0E0B7D40*)me;

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

static int16_t ECOCALLMETHOD CEcoBRE1_0E0B7D40_CreateBuilder(IEcoBRE1Ptr_t me, IEcoRegEx1BuilderPtr_t* ppIBuilder) {
    CEcoBRE1_0E0B7D40* pCMe = (CEcoBRE1_0E0B7D40*)me;
    CEcoBRE1Builder_0E0B7D40Ptr_t pCObj = 0;
    int16_t result = 0;

    if (me == 0 || ppIBuilder == 0) {
        return ERR_ECO_POINTER;
    }

    /* Выделение памяти для данных экземпляра */
    pCObj = (CEcoBRE1Builder_0E0B7D40Ptr_t)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBRE1Builder_0E0B7D40));
    /* Формирование данных экземпляра */
    pCObj = (CEcoBRE1Builder_0E0B7D40Ptr_t)pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, pCObj, &g_xCEcoBRE1Builder_0E0B7D40, sizeof(CEcoBRE1Builder_0E0B7D40));
    /* Создание компонента */
    result = pCObj->Create(pCObj, (IEcoUnknown*)pCMe->m_pISys, 0);
    /* Инициализация компонента */
    result = pCObj->Init(pCObj, (IEcoUnknown*)pCMe->m_pISys);
    *ppIBuilder = (IEcoRegEx1BuilderPtr_t)pCObj;

    return result;
}

/*
 *
 * <сводка>
 *   Функция CreateRegEx
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1_0E0B7D40_CreateRegEx(
        /* in */ IEcoBRE1Ptr_t me, 
        /* in */ voidptr_t pattern,        /* Поддержка ASCII/UTF-8/UTF-16 */
        /* in */ uint32_t patSizeInBytes, 
        /* in */ uint32_t flags,           /* Кодировка шаблона и опции компиляции */
        /* out */ IEcoRegEx1Ptr_t* ppIRegex
    ) {
    CEcoBRE1_0E0B7D40* pCMe = (CEcoBRE1_0E0B7D40*)me;
	IEcoRegEx1Builder* pBuilder = 0;
    IEcoBinaryTree1NodePtr_t pRoot = 0;
    ParseContext ctx;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || pattern == 0 || ppIRegex == 0) {
        return ERR_ECO_POINTER;
    }

	result = pCMe->m_pVTblIEcoBRE1->CreateBuilder(me, &pBuilder);
	if (result != 0 || pBuilder == 0) {
		return result;
	}

	ctx.current = (char*)pattern;
    ctx.builder = pBuilder;

	pRoot = ParseExpression(&ctx);

	if (pRoot != 0) {
        result = pBuilder->pVTbl->Build(pBuilder, pRoot, ppIRegex);
		pRoot->pVTbl->Release(pRoot);
    } else {
        result = -1;
    }

    pBuilder->pVTbl->Release(pBuilder);

    return result;
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
static int16_t ECOCALLMETHOD initCEcoBRE1_0E0B7D40(/*in*/ CEcoBRE1_0E0B7D40Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBRE1_0E0B7D40* pCMe = (CEcoBRE1_0E0B7D40*)me;
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
static int16_t ECOCALLMETHOD createCEcoBRE1_0E0B7D40(/* in */ CEcoBRE1_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBRE1_0E0B7D40(/* in */ CEcoBRE1_0E0B7D40Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
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


/* Виртуальная таблица IEcoBRE1 */
IEcoBRE1VTbl g_x25F983424A724CBBB270A4BF6468C8A8VTbl_0E0B7D40 = {
    CEcoBRE1_0E0B7D40_QueryInterface,
    CEcoBRE1_0E0B7D40_AddRef,
    CEcoBRE1_0E0B7D40_Release,
	CEcoBRE1_0E0B7D40_CreateRegEx,
	CEcoBRE1_0E0B7D40_CreateBuilder
};


/* Экземпляр объекта */
CEcoBRE1_0E0B7D40 g_xCEcoBRE1_0E0B7D40 = {
    &g_x25F983424A724CBBB270A4BF6468C8A8VTbl_0E0B7D40,
    initCEcoBRE1_0E0B7D40,
    createCEcoBRE1_0E0B7D40,
    deleteCEcoBRE1_0E0B7D40,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pIMem */
    0  /* m_Name */
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               