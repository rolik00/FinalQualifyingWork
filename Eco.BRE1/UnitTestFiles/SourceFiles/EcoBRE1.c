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
#include "IdEcoList1.h"
#include "IdEcoString1.h"
#include "IdEcoLog1.h"
#include "IEcoLog1FileAffiliate.h"
#include "IEcoLog1ConsoleAffiliate.h"
#include "IEcoLog1SimpleLayout.h"
#include "IdEcoDateTime1.h"
char* getSymbol(uint32_t min, uint32_t max) {
	if (min == 0 && max == 0xFFFFFFFF) return " (*)";
    else if (min == 1 && max == 0xFFFFFFFF) return " (+)";
    else if (min == 0 && max == 1) return " (?)";
    return "";          
}

void DebugPrintTree(IEcoLog1* pILog, IEcoBinaryTree1Node* node, int depth) {
    EcoRegEx1NodeData* pData = 0;
    int i;
	char buffer[256];
	char* s;
    
    if (node == 0) return;

    pData = (EcoRegEx1NodeData*)node->pVTbl->get_Data(node);
    
    /* Отступ для визуализации глубины */
    for(i = 0; i < depth; i++) printf("  ");

    if (pData) {
        switch (pData->type) {
            case ECO_REGEX_NODE_LITERAL: 
                pILog->pVTbl->InfoFormat(pILog, "LITERAL '%c'", (char)pData->data.literal.codePoint); 
                break;
            case ECO_REGEX_NODE_CONCAT: 
                pILog->pVTbl->Info(pILog, "CONCAT"); 
                break;
            case ECO_REGEX_NODE_ALTERNATION: 
                pILog->pVTbl->Info(pILog, "OR"); 
                break;
            case ECO_REGEX_NODE_QUANTIFIER:
				s =  getSymbol(pData->data.quantifier.min, pData->data.quantifier.max);
				if (pData->data.quantifier.max == 0xFFFFFFFF) {
					sprintf(buffer, "QUANTIFIER %s {%d, inf}", s, pData->data.quantifier.min);
				} else {
					sprintf(buffer, "QUANTIFIER %s {%d, %d}", s, pData->data.quantifier.min, pData->data.quantifier.max);
				}
				pILog->pVTbl->Info(pILog, buffer);
				break;
                /*pILog->pVTbl->InfoFormat(pILog, "QUANTIFIER %s", getSymbol(pData->data.quantifier.min, pData->data.quantifier.max));
                if (pData->data.quantifier.max == 0xFFFFFFFF)
                    pILog->pVTbl->InfoFormat(pILog, "{%d, inf}", pData->data.quantifier.min);
                else
                    pILog->pVTbl->InfoFormat(pILog, "{%d, %d}", pData->data.quantifier.min, pData->data.quantifier.max);
                break;*/
            case ECO_REGEX_NODE_ANYCHAR: 
                pILog->pVTbl->Info(pILog, "ANY CHAR (.)"); 
                break;
            case ECO_REGEX_NODE_RANGE: 
                pILog->pVTbl->InfoFormat(pILog, "RANGE [%c-%c]", (char)pData->data.range.start, (char)pData->data.range.end); 
                break;
            case ECO_REGEX_NODE_GROUP: 
                pILog->pVTbl->Info(pILog, "GROUP ()"); 
                break;
            default: 
                pILog->pVTbl->InfoFormat(pILog, "UNKNOWN NODE TYPE %d", pData->type); 
                break;
        }
    } else {
        pILog->pVTbl->Info(pILog, "NODE (No Data)");
    }

    DebugPrintTree(pILog, node->pVTbl->get_Left(node), depth + 1);
    DebugPrintTree(pILog, node->pVTbl->get_Right(node), depth + 1);
}

void TestRegEx(IEcoLog1* pILog, IEcoBRE1* pBRE, voidptr_t pattern) {
    IEcoRegEx1* pRegEx = 0;
    int16_t result = 0;
	CEcoBRE1RegEx_0E0B7D40* pImpl = 0;

    pILog->pVTbl->InfoFormat(pILog, "\n=== TEST PATTERN: \"%s\" ===\n", pattern);

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
            pILog->pVTbl->Info(pILog, "Structure:");
            DebugPrintTree(pILog, pImpl->m_pRoot, 1);
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
    /* Указатель на тестируемый интерфейс */
    IEcoBRE1* pIEcoBRE1 = 0;
    /* Указатель на интерфейс работы с журналом */
    IEcoLog1* pILog = 0;
    IEcoLog1FileAffiliate* pIFileAffiliate = 0;
    IEcoLog1ConsoleAffiliate* pIConsoleAffiliate = 0;
    IEcoLog1Layout* pILayout = 0;
    IEcoLog1SimpleLayout* pISimpleLayout = 0;

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
    /* Регистрация статического компонента для работы с бинарным деревом */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBinaryTree1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_7CAD4D0215EF4EDFB1FF6A7CAF1C3D6C);
    if (result != 0 ) {
        goto Release;
    }
    /* Регистрация статического компонента для работы со строкой */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoString1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_84CC0A7DBABD44EEBE749C9A8312D37E);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с датой и вреенем */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoDateTime1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5B2BA17BEA704527BC708F88568FE115);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с журналом */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLog1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_97322B6765B74342BBCE38798A0B40B5);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
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

    /* Получение интерфейса работы с журналом */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1, (void**)&pILog);
    if (result != 0 || pILog == 0) {
        goto Release;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1FileAffiliate, (void**)&pIFileAffiliate);
    if (result != 0 || pIFileAffiliate == 0) {
        goto Release;
    }

    //pILayout = pIFileAffiliate->pVTbl->get_Layout(pIFileAffiliate);
    //pILayout->pVTbl->QueryInterface(pILayout, &IID_IEcoLog1SimpleLayout, (void**) &pISimpleLayout);
    //pISimpleLayout->pVTbl->set_Pattern(pISimpleLayout, "%m\n");
    //pISimpleLayout->pVTbl->Release(pISimpleLayout);
    pILog->pVTbl->AddAffiliate(pILog, (IEcoLog1Affiliate*)pIFileAffiliate);
    pIFileAffiliate->pVTbl->Release(pIFileAffiliate);

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1ConsoleAffiliate, (void**) &pIConsoleAffiliate);
    if (result != 0 || pIConsoleAffiliate == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    pILayout = pIConsoleAffiliate->pVTbl->get_Layout(pIConsoleAffiliate);
    pILayout->pVTbl->QueryInterface(pILayout, &IID_IEcoLog1SimpleLayout, (void**) &pISimpleLayout);
    pISimpleLayout->pVTbl->set_Pattern(pISimpleLayout, "%m\n");
    pISimpleLayout->pVTbl->Release(pISimpleLayout);

    pILog->pVTbl->AddAffiliate(pILog, (IEcoLog1Affiliate*)pIConsoleAffiliate);
    pIConsoleAffiliate->pVTbl->Release(pIConsoleAffiliate);

    pILog->pVTbl->Info(pILog, "Start tests!!!");

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBRE1, 0, &IID_IEcoBRE1, (void**) &pIEcoBRE1);
    if (result != 0 || pIEcoBRE1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }


    TestRegEx(pILog, pIEcoBRE1, "abc");

    TestRegEx(pILog, pIEcoBRE1, "a|b");

    TestRegEx(pILog, pIEcoBRE1, "a*");

    TestRegEx(pILog, pIEcoBRE1, "(ab)+");

    TestRegEx(pILog, pIEcoBRE1, "[0-9]");

    TestRegEx(pILog, pIEcoBRE1, "a.c");

    TestRegEx(pILog, pIEcoBRE1, "(a|b)*c?");

    TestRegEx(pILog, pIEcoBRE1, "abc|(c|(de))");

    TestRegEx(pILog, pIEcoBRE1, "ab{2,}");

    pILog->pVTbl->Info(pILog, "\nTests finished.\n");


Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение интерфейса работы с журналом */
    if (pILog != 0) {
        pILog->pVTbl->Release(pILog);
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
