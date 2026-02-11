/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoBRE1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoBRE1.h"
#include "IdEcoBinaryTree1.h"
#include "IEcoBinaryTree1.h"
#include "IEcoBRE1.h"
#include "IEcoRegEx1.h"
#include "CEcoBRE1RegEx.h"
#include <stdio.h>


void DebugPrintTree(IEcoBinaryTree1Node* node, int depth) {
    EcoRegEx1NodeData* pData = 0;
    int i;
    
    if (node == 0) return;

    /* Получаем данные узла */
    pData = (EcoRegEx1NodeData*)node->pVTbl->get_Data(node);
    
    /* Отступ для визуализации глубины */
    for(i = 0; i < depth; i++) printf("  ");

    if (pData) {
        switch (pData->type) {
            case ECO_REGEX_NODE_LITERAL: 
                printf("LITERAL '%c'\n", (char)pData->data.literal.codePoint); 
                break;
            case ECO_REGEX_NODE_CONCAT: 
                printf("CONCAT\n"); 
                break;
            case ECO_REGEX_NODE_ALTERNATION: 
                printf("OR\n"); 
                break;
            case ECO_REGEX_NODE_QUANTIFIER: 
                printf("QUANTIFIER ");
                if (pData->data.quantifier.max == 0xFFFFFFFF)
                    printf("{%d, inf}", pData->data.quantifier.min);
                else
                    printf("{%d, %d}", pData->data.quantifier.min, pData->data.quantifier.max);
                
                if (pData->data.quantifier.min == 0 && pData->data.quantifier.max == 0xFFFFFFFF) printf(" (*)");
                else if (pData->data.quantifier.min == 1 && pData->data.quantifier.max == 0xFFFFFFFF) printf(" (+)");
                else if (pData->data.quantifier.min == 0 && pData->data.quantifier.max == 1) printf(" (?)");
                printf("\n");
                break;
            case ECO_REGEX_NODE_ANYCHAR: 
                printf("ANY CHAR (.)\n"); 
                break;
            case ECO_REGEX_NODE_RANGE: 
                printf("RANGE [%c-%c]\n", (char)pData->data.range.start, (char)pData->data.range.end); 
                break;
            case ECO_REGEX_NODE_GROUP: 
                printf("GROUP ()\n"); 
                break;
            default: 
                printf("UNKNOWN NODE TYPE %d\n", pData->type); 
                break;
        }
    } else {
        printf("NODE (No Data)\n");
    }

    /* Рекурсивный обход: Сначала левый (child/left), потом правый (next/right) */
    DebugPrintTree(node->pVTbl->get_Left(node), depth + 1);
    DebugPrintTree(node->pVTbl->get_Right(node), depth + 1);
}

void TestRegEx(IEcoBRE1* pBRE, voidptr_t pattern) {
    IEcoRegEx1* pRegEx = 0;
    int16_t result = 0;
	CEcoBRE1RegEx_0E0B7D40* pImpl = 0;

    printf("\n=== TEST PATTERN: \"%s\" ===\n", pattern);

	if (pBRE == 0) {
        return;
    }

    if (pBRE->pVTbl == 0) {
        return;
    }

    if (pBRE->pVTbl->CreateRegEx == 0) {
        return;
    }

    result = pBRE->pVTbl->CreateRegEx(pBRE, pattern, 0, 0, &pRegEx);

    if (result == 0 && pRegEx != 0) {
        pImpl = (CEcoBRE1RegEx_0E0B7D40*)pRegEx;
        
        if (pImpl->m_pRoot != 0) {
            printf("Structure:\n");
            DebugPrintTree(pImpl->m_pRoot, 1);
        }

        pRegEx->pVTbl->Release(pRegEx);
    }
}


/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoBRE1* pIEcoBRE1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBRE1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_755D526AEBF943E9B4AA4F860E0B7D40);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

	result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBinaryTree1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_7CAD4D0215EF4EDFB1FF6A7CAF1C3D6C);
    if (result != 0 ) {
		goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Выделение блока памяти */
    name = (char_t *)pIMem->pVTbl->Alloc(pIMem, 10);

    /* Заполнение блока памяти */
    pIMem->pVTbl->Fill(pIMem, name, 'a', 9);


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBRE1, 0, &IID_IEcoBRE1, (void**) &pIEcoBRE1);
    if (result != 0 || pIEcoBRE1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }


    TestRegEx(pIEcoBRE1, "abc");

    TestRegEx(pIEcoBRE1, "a|b");

    TestRegEx(pIEcoBRE1, "a*");

    TestRegEx(pIEcoBRE1, "(ab)+");

    TestRegEx(pIEcoBRE1, "[0-9]");

    TestRegEx(pIEcoBRE1, "a.c");

    TestRegEx(pIEcoBRE1, "(a|b)*c?");

	TestRegEx(pIEcoBRE1, "abc|(c|(de))");

	TestRegEx(pIEcoBRE1, "ab{2,}");

    printf("\nTests finished.\n");


    /* Освлбождение блока памяти */
    pIMem->pVTbl->Free(pIMem, name);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoBRE1 != 0) {
        pIEcoBRE1->pVTbl->Release(pIEcoBRE1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
