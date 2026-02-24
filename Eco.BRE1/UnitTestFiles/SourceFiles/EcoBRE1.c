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
#include "IEcoBRE1.h"
#include "IdEcoBinaryTree1.h"
#include "IEcoBinaryTree1.h"
#include "IEcoRegEx1.h"
#include "CEcoBRE1RegEx.h"
#include "IdEcoList1.h"
#include "IdEcoString1.h"
#include "IdEcoLog1.h"
#include "IEcoLog1FileAffiliate.h"
#include "IEcoLog1ConsoleAffiliate.h"
#include "IEcoLog1SimpleLayout.h"
#include "IdEcoDateTime1.h"
#include "IdEcoFSM1.h"
#include "IEcoFSM1.h"
#include "IdEcoData1.h"

/* Тест построения NFA из синтаксического дерева */
void TestNFABuilding(IEcoLog1* pILog, IEcoBRE1* pBRE, voidptr_t pattern, int expectedStates, int expectedTransitions) {
    IEcoRegEx1* pRegEx = 0;
    int16_t result = 0;
	CEcoBRE1RegEx_0E0B7D40* pImpl = 0;
	IEcoList1* pStates = 0;
    IEcoList1* pTransitions = 0;
    uint32_t stateCount = 0;
    uint32_t transCount = 0;
    int hasFSM = 0;

    pILog->pVTbl->InfoFormat(pILog, "\n=== TEST PATTERN: \"%s\" ===", pattern);

    result = pBRE->pVTbl->CreateRegEx(pBRE, pattern, 0, 0, &pRegEx);

	if (result != 0 || pRegEx == 0) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Failed to create RegEx for pattern \"%s\", error code: %d", pattern, result);
		return;
    }

    pImpl = (CEcoBRE1RegEx_0E0B7D40*)pRegEx;
    hasFSM = (pImpl->m_pStateMachine != 0);
	if (!hasFSM) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: NFA not built for pattern \"%s\"", pattern);
        pRegEx->pVTbl->Release(pRegEx);
		return;
    }

	pStates = pImpl->m_pStateMachine->pVTbl->get_States(pImpl->m_pStateMachine);
    pTransitions = pImpl->m_pStateMachine->pVTbl->get_Transitions(pImpl->m_pStateMachine);
        
    stateCount = pStates->pVTbl->Count(pStates);
    transCount = pTransitions->pVTbl->Count(pTransitions);
        
    if (stateCount != (uint32_t)expectedStates) {
		pILog->pVTbl->InfoFormat(pILog, "FAILED: State count mismatch for pattern \"%s\". Expected: %d, Actual: %d", pattern, expectedStates, stateCount);
	    return;
	}
        
    if (transCount != (uint32_t)expectedTransitions) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Transition count mismatch for pattern \"%s\". Expected: %d, Actual: %d", pattern, expectedTransitions, transCount);
	    return;
    }
   
    pILog->pVTbl->InfoFormat(pILog, "PASSED: Pattern \"%s\" - States: %d, Transitions: %d", pattern, stateCount, transCount);

    /* Освобождаем ресурсы */
    pRegEx->pVTbl->Release(pRegEx);
}

/* Тест функции IsMatch */
void TestIsMatch(IEcoLog1* pILog, IEcoBRE1* pBRE, voidptr_t pattern, voidptr_t text, int expected) {
    IEcoRegEx1* pRegEx = 0;
    int16_t result = 0;
    int isMatch = 0;
    
    pILog->pVTbl->InfoFormat(pILog, "\nTEST: pattern - \"%s\", text - \"%s\"", pattern, text);
    
    result = pBRE->pVTbl->CreateRegEx(pBRE, (voidptr_t)pattern, 0, 0, &pRegEx);
    
    if (result != 0 || pRegEx == 0) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Cannot create RegEx, error code: %d", result);
        return;
    }
    
	isMatch = pRegEx->pVTbl->IsMatch(pRegEx, (voidptr_t)text, 0, 0);
    
    if (isMatch == expected) {
        pILog->pVTbl->InfoFormat(pILog, "PASSED: IsMatch = %d", isMatch);
    } else {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Expected %d, got %d", expected, isMatch);
    }
    
    pRegEx->pVTbl->Release(pRegEx);
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
	/* Регистрация статического компонента для работы с конечным автоматом */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoFSM1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5E7C610CB846447DB59A3C5A2C4F446F);
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
	 /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoData1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5A0F0DD57E6448EC9EE0E5D67572B47E);
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

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBRE1, 0, &IID_IEcoBRE1, (void**) &pIEcoBRE1);
    if (result != 0 || pIEcoBRE1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	pILog->pVTbl->Info(pILog, "=== Test 1: NFA Building ===");
	TestNFABuilding(pILog, pIEcoBRE1, "abc", 6, 5);
	TestNFABuilding(pILog, pIEcoBRE1, "a|b", 6, 6);
	TestNFABuilding(pILog, pIEcoBRE1, "a*", 4, 5);
	TestNFABuilding(pILog, pIEcoBRE1, "(ab)+", 6, 6);
	TestNFABuilding(pILog, pIEcoBRE1, "[0-9]", 2, 1);
	TestNFABuilding(pILog, pIEcoBRE1, "a.c", 6, 5);
	TestNFABuilding(pILog, pIEcoBRE1, "(a|b)*c?", 12, 15);
	TestNFABuilding(pILog, pIEcoBRE1, "abc|(c|(de))", 16, 17);
	TestNFABuilding(pILog, pIEcoBRE1, "ab{2,}", 7, 7);
	TestNFABuilding(pILog, pIEcoBRE1, "(a|b)(c|d)", 12, 13);
	pILog->pVTbl->Info(pILog, "\n=== Test 1 Finished ===\n");

	pILog->pVTbl->Info(pILog, "=== Test 2: IsMatch Test ===");
	TestIsMatch(pILog, pIEcoBRE1, "abc", "abc", 1);
	TestIsMatch(pILog, pIEcoBRE1, "abc", "abd", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a|b", "a", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a|b", "b", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a|b", "c", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a*", "", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a*", "aaa", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a+", "a", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a+", "aaaa", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a+", "", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a?", "a", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a?", "", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a?", "aa", 0);
	TestIsMatch(pILog, pIEcoBRE1, "[0-9]", "5", 1);
	TestIsMatch(pILog, pIEcoBRE1, "[0-9]", "a", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a.c", "abc", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a.c", "abbc", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a.*c", "abbc", 1);
	TestIsMatch(pILog, pIEcoBRE1, "(ab)+", "ab", 1);
	TestIsMatch(pILog, pIEcoBRE1, "(ab)*", "", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a{2,4}", "aa", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a{2,4}", "aaaa", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a{2,4}", "a", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a{2,4}", "aaaaa", 0);
	TestIsMatch(pILog, pIEcoBRE1, "(a|b)*c?", "abc", 1);
	TestIsMatch(pILog, pIEcoBRE1, "(a|b)*c?", "ab", 1);
	TestIsMatch(pILog, pIEcoBRE1, "abc|(c|(de))", "de", 1);
	pILog->pVTbl->Info(pILog, "\n=== Test 2 Finished ===\n");


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
