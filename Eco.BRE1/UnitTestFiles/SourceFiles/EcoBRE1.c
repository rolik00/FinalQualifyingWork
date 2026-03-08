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
	IEcoFSM1StateMachine* pStateMachine;
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

    result = pRegEx->pVTbl->QueryInterface(pRegEx, &IID_IEcoFSM1StateMachine, (void**)&pStateMachine);
    if (result != 0 || pStateMachine == 0) {
        pILog->pVTbl->Info(pILog, "FAILED: No NFA state machine available");
        pRegEx->pVTbl->Release(pRegEx);
        return;
    }

	pStates = pStateMachine->pVTbl->get_States(pStateMachine);
    pTransitions = pStateMachine->pVTbl->get_Transitions(pStateMachine);
        
    stateCount = pStates->pVTbl->Count(pStates);
    transCount = pTransitions->pVTbl->Count(pTransitions);
        
    if (stateCount != (uint32_t)expectedStates) {
		pILog->pVTbl->InfoFormat(pILog, "FAILED: State count mismatch for pattern \"%s\". Expected: %d, Actual: %d", pattern, expectedStates, stateCount);
	    pRegEx->pVTbl->Release(pRegEx);
		return;
	}
        
    if (transCount != (uint32_t)expectedTransitions) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Transition count mismatch for pattern \"%s\". Expected: %d, Actual: %d", pattern, expectedTransitions, transCount);
	    pRegEx->pVTbl->Release(pRegEx);
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

/* Тест функции Match */
void TestMatch(IEcoLog1* pILog, IEcoBRE1* pBRE, voidptr_t pattern, voidptr_t text, int expectedIndex) {
    IEcoRegEx1* pRegEx = 0;
    int16_t result = 0;
    EcoRegEx1Match* pMatch;
    
    pILog->pVTbl->InfoFormat(pILog, "\nTEST: pattern - \"%s\", text - \"%s\"", pattern, text);
    
    result = pBRE->pVTbl->CreateRegEx(pBRE, (voidptr_t)pattern, 0, 0, &pRegEx);
    
    if (result != 0 || pRegEx == 0) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Cannot create RegEx, error code: %d", result);
        return;
    }
    
	result = pRegEx->pVTbl->Match(pRegEx, (voidptr_t)text, 0, 0, &pMatch);
	if (result == 0 && pMatch != 0) {
        pILog->pVTbl->InfoFormat(pILog, "Recieved: index = %d, length = %u", pMatch->index, pMatch->length);
        
        if (pMatch->index == expectedIndex) {
            pILog->pVTbl->Info(pILog, "Index check: PASSED");
        } else {
            pILog->pVTbl->InfoFormat(pILog, "Index check: FAILED Expected %d, got %d", expectedIndex, pMatch->index);
        }
	} else {
        pILog->pVTbl->Info(pILog, "No match found");
        if (expectedIndex == -1) {
            pILog->pVTbl->Info(pILog, "No-match check: PASSED");
        } else {
            pILog->pVTbl->Info(pILog, "No-match check: FAILED");
        }
    }

	if (pMatch) {
		IEcoMemoryAllocator1* pIMem = ((CEcoBRE1RegEx_0E0B7D40*)pRegEx)->m_pIMem;
		pIMem->pVTbl->Free(pIMem, pMatch);
	}
    
    pRegEx->pVTbl->Release(pRegEx);
}

/* Тест функции Matches */
void TestMatches(IEcoLog1* pILog, IEcoBRE1* pBRE, voidptr_t pattern, voidptr_t text, int expectedCount, int expectedIndices[], int expectedLengths[]) {
    IEcoRegEx1* pRegEx = 0;
    IEcoRegEx1EnumMatchesPtr_t pEnum = 0;
    int16_t result = 0;
    EcoRegEx1Match matches[20];
    uint32_t fetched = 0;
    uint32_t totalMatches = 0;
    int passed = 1;
    
    pILog->pVTbl->InfoFormat(pILog, "\nTEST: pattern - \"%s\", text - \"%s\"", pattern, text);
    
    result = pBRE->pVTbl->CreateRegEx(pBRE, (voidptr_t)pattern, 0, 0, &pRegEx);
    
    if (result != 0 || pRegEx == 0) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Cannot create RegEx, error code: %d", result);
        return;
    }
    
    result = pRegEx->pVTbl->Matches(pRegEx, (voidptr_t)text, 0, 0, &pEnum);
    
    if (result != 0 || pEnum == 0) {
        if (expectedCount == 0 && result == ERR_ECO_SUCCESES) {
            pILog->pVTbl->Info(pILog, "PASSED: No matches found (expected empty result)");
        } else {
            pILog->pVTbl->InfoFormat(pILog, "FAILED: Matches returned error code: %d", result);
        }
        pRegEx->pVTbl->Release(pRegEx);
        return;
    }
    
    while (totalMatches < (uint32_t)expectedCount && passed) {
        result = pEnum->pVTbl->Next(pEnum, 1, &matches[totalMatches], &fetched);
        if (result != 0 || fetched == 0) {
            break;
        }
        
        if (matches[totalMatches].index != (uint32_t)expectedIndices[totalMatches]) {
            pILog->pVTbl->InfoFormat(pILog, "FAILED: Match %d index mismatch - Expected: %d, Actual: %u", totalMatches + 1, expectedIndices[totalMatches], matches[totalMatches].index);
            passed = 0;
        }
        
        if (matches[totalMatches].length != (uint32_t)expectedLengths[totalMatches]) {
            pILog->pVTbl->InfoFormat(pILog, "FAILED: Match %d length mismatch - Expected: %d, Actual: %u", totalMatches + 1, expectedLengths[totalMatches], matches[totalMatches].length);
            passed = 0;
        }
        
        pILog->pVTbl->InfoFormat(pILog, "  Match %d: index = %d, length = %u", totalMatches + 1, matches[totalMatches].index, matches[totalMatches].length);
        
        totalMatches++;
    }
    
    if (passed) {
        result = pEnum->pVTbl->Next(pEnum, 1, matches, &fetched);
        if (fetched != 0) {
            pILog->pVTbl->InfoFormat(pILog, "FAILED: Found unexpected extra match at index %u", matches[0].index);
            passed = 0;
        }
    }
    
    if (totalMatches != (uint32_t)expectedCount) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Match count mismatch - Expected: %d, Actual: %u", expectedCount, totalMatches);
        passed = 0;
    }
    
    if (passed) {
        pILog->pVTbl->Info(pILog, "PASSED: All matches verified successfully");
    }
    
    if (pEnum != 0) {
        pEnum->pVTbl->Release(pEnum);
    }
    
    pRegEx->pVTbl->Release(pRegEx);
}

/* Тест функции Split */
void TestSplit(IEcoLog1* pILog, IEcoBRE1* pBRE, voidptr_t pattern, voidptr_t text, int expectedCount, const char* expectedParts[]) {
    IEcoRegEx1* pRegEx = 0;
    int16_t result = 0;
    voidptr_t pResult = 0;
    SplitResult* pSplit = 0;
    uint32_t i = 0;
    int passed = 1;
	IEcoMemoryAllocator1* pIMem;
	char* got;
    
    pILog->pVTbl->InfoFormat(pILog, "\nTEST: pattern - \"%s\", text - \"%s\"", pattern, text);
    
    result = pBRE->pVTbl->CreateRegEx(pBRE, (voidptr_t)pattern, 0, 0, &pRegEx);
    
    if (result != 0 || pRegEx == 0) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Cannot create RegEx, error code: %d", result);
        return;
    }
    
	result = pRegEx->pVTbl->Split(pRegEx, (voidptr_t)text, 0, 0, &pResult);
	if (result != 0 || pResult == 0) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Split returned error %d or null result", result);
        pRegEx->pVTbl->Release(pRegEx);
        return;
    }

	pSplit = (SplitResult*)pResult;

    if (pSplit->count != (uint32_t)expectedCount) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Parts count mismatch. Expected %d, got %u", expectedCount, pSplit->count);
        passed = 0;
    }

	if (passed) {
        for (i = 0; i < pSplit->count; i++) {
            got = pSplit->strings[i] ? pSplit->strings[i] : "";
            if (strcmp(got, expectedParts[i]) != 0) {
                pILog->pVTbl->InfoFormat(pILog, "FAILED: Part %u mismatch:  expected: \"%s\",  got: \"%s\"", i, expectedParts[i], got);
                passed = 0;
                break;
            } else {
				pILog->pVTbl->InfoFormat(pILog, "	PASSED: Part %u:  expected: \"%s\",  got: \"%s\"", i, expectedParts[i], got);  
			}
        }
    }

	if (passed) {
        pILog->pVTbl->Info(pILog, "PASSED: All split parts match expected");
    }

	if (pSplit) {
        pIMem = ((CEcoBRE1RegEx_0E0B7D40*)pRegEx)->m_pIMem;
        for (i = 0; i < pSplit->count; i++) {
            if (pSplit->strings[i]) {
                pIMem->pVTbl->Free(pIMem, pSplit->strings[i]);
            }
        }
        pIMem->pVTbl->Free(pIMem, pSplit->strings);
        pIMem->pVTbl->Free(pIMem, pSplit);
    }
    
    pRegEx->pVTbl->Release(pRegEx);
}

/* Тест функции Replace */
void TestReplace(IEcoLog1* pILog, IEcoBRE1* pBRE, voidptr_t pattern, voidptr_t text, voidptr_t replacement, const char* expectedResult) {
    IEcoRegEx1* pRegEx = 0;
    int16_t result = 0;
    voidptr_t pResultStr = 0;
    uint32_t resSize = 0;
    char* got = 0;

    pILog->pVTbl->InfoFormat(pILog, "\nTEST: pattern=\"%s\", replacement=\"%s\", text=\"%s\"", pattern, replacement, text);

    result = pBRE->pVTbl->CreateRegEx(pBRE, pattern, 0, 0, &pRegEx);
    if (result != 0 || pRegEx == 0) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: CreateRegEx failed, error=%d", result);
        return;
    }

    result = pRegEx->pVTbl->Replace(pRegEx, text, 0, replacement, 0, 0, &pResultStr, &resSize);

    if (result != 0 || pResultStr == 0) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: Replace failed, error=%d", result);
        pRegEx->pVTbl->Release(pRegEx);
        return;
    }

    got = (char*)pResultStr;
    if (strcmp(got, expectedResult) == 0) {
        pILog->pVTbl->InfoFormat(pILog, "PASSED: result = \"%s\"", got);
    } else {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: expected \"%s\", got \"%s\"", expectedResult, got);
    }

    if (pResultStr) {
        IEcoMemoryAllocator1* pIMem = ((CEcoBRE1RegEx_0E0B7D40*)pRegEx)->m_pIMem;
        pIMem->pVTbl->Free(pIMem, pResultStr);
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

	/*pILog->pVTbl->Info(pILog, "=== Test 1: NFA Building ===");
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
	pILog->pVTbl->Info(pILog, "\n=== Test 1 Finished ===\n");*/

	/*pILog->pVTbl->Info(pILog, "=== Test 2: IsMatch Test ===");
	TestIsMatch(pILog, pIEcoBRE1, "abc", "abc", 1);
	TestIsMatch(pILog, pIEcoBRE1, "abc", "abd", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a|b", "a", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a|b", "b", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a|b", "c", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a|b|c", "c", 1);
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
	TestIsMatch(pILog, pIEcoBRE1, "[0-9]{2}", "93", 1);
	TestIsMatch(pILog, pIEcoBRE1, "[0-9]{2}", "101", 0);
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
	TestIsMatch(pILog, pIEcoBRE1, "abc|(c|(de))", "abc", 1);
	TestIsMatch(pILog, pIEcoBRE1, "abc|(c|(de))", "c", 1);
	TestIsMatch(pILog, pIEcoBRE1, "abc|(c|(de))", "cde", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a+b+", "aaabbb", 1);
	TestIsMatch(pILog, pIEcoBRE1, "a+b+", "xaaabbbx", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a+b+", "xaaabbb", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a+b+", "aaabbbx", 0);
	TestIsMatch(pILog, pIEcoBRE1, "a+b+", "aaaxbbb", 0);
	pILog->pVTbl->Info(pILog, "\n=== Test 2 Finished ===\n");*/

	/*pILog->pVTbl->Info(pILog, "=== Test 3: Match Test ===");
	TestMatch(pILog, pIEcoBRE1, "abc|(c|(de))", "cde", 0);
	TestMatch(pILog, pIEcoBRE1, "abc|(c|(de))", "ade", 1);
	TestMatch(pILog, pIEcoBRE1, "abc|(c|(de))", "abc", 0);   
	TestMatch(pILog, pIEcoBRE1, "a.c", "kabc", 1);
	TestMatch(pILog, pIEcoBRE1, "a.c", "abbc", -1);     
	TestMatch(pILog, pIEcoBRE1, "a.*c", "abbc", 0);
	TestMatch(pILog, pIEcoBRE1, "ab{2,4}", "aaaaaabbbb", 5);
	TestMatch(pILog, pIEcoBRE1, "a+b+", "aaaxbbb", -1);
	TestMatch(pILog, pIEcoBRE1, "a+b+", "xaaabbbx", 1);
	pILog->pVTbl->Info(pILog, "\n=== Test 3 Finished ===\n");*/

	/*pILog->pVTbl->Info(pILog, "=== Test 4: Matches Test ===");
	{
		int indices[] = {0, 11, 20};  
		int lengths[] = {3, 2, 1};
		TestMatches(pILog, pIEcoBRE1, "abc|de|c", "abcfgrrjtjsdehfkkrhdcjdjrwo", 3, indices, lengths);
	}
	{
		int indices[] = {3, 8};
		int lengths[] = {5, 3};
		TestMatches(pILog, pIEcoBRE1, "ab{2,4}|b+", "aaaabbbbbbb", 2, indices, lengths);
	}
	{
		int indices[] = {0, 2};
		int lengths[] = {2, 2};
		TestMatches(pILog, pIEcoBRE1, "aa", "aaaa", 2, indices, lengths);
	}
	{
		int indices[] = {3, 9, 15};
		int lengths[] = {3, 3, 3};
		TestMatches(pILog, pIEcoBRE1, "[0-9]+", "abc123def456ghi789", 3, indices, lengths);
	}
	{
		int indices[] = {0, 2, 4};
		int lengths[] = {2, 2, 1};
		TestMatches(pILog, pIEcoBRE1, "aa|a", "aaaaa", 3, indices, lengths);
    }
	{
		int indices[] = {0};
		int lengths[] = {3};
		TestMatches(pILog, pIEcoBRE1, "a{2,3}", "aaaa", 1, indices, lengths);
	}
	{
		TestMatches(pILog, pIEcoBRE1, "xyz", "abcdef", 0, 0, 0);
    }
	{
		int indices[] = {3};
		int lengths[] = {3};
		TestMatches(pILog, pIEcoBRE1, "abc", "ABCabcAbc", 1, indices, lengths);
	}
	{
		int indices[] = {0, 5, 15};
		int lengths[] = {4, 5, 4};
		TestMatches(pILog, pIEcoBRE1, "[A-Z][a-z]+", "John Smith and Jane DOE", 3, indices, lengths);
	}
	{
		int indices[] = {0};
		int lengths[] = {0};
		TestMatches(pILog, pIEcoBRE1, "a*", "", 1, indices, lengths);
	}
	pILog->pVTbl->Info(pILog, "\n=== Test 4 Finished ===\n");*/

    /*pILog->pVTbl->Info(pILog, "=== Test 5: Split Test ===");
	{
		const char* expected[] = {"fgrrjtjs", "hfkkrhd", "jdjrwo"};
		TestSplit(pILog, pIEcoBRE1, "abc|de|c", "abcfgrrjtjsdehfkkrhdcjdjrwo", 3, expected);
	}
	{
		const char* expected[] = {"abc", "def", "ghi"};
		TestSplit(pILog, pIEcoBRE1, "[0-9]+", "abc123def456ghi789", 3, expected);
	}
	{
		const char* expected[] = {""};
		TestSplit(pILog, pIEcoBRE1, "aa", "aaaa", 1, expected);
	}
	{
		const char* expected[] = {"abcdef"};
		TestSplit(pILog, pIEcoBRE1, "xyz", "abcdef", 1, expected);
	}
	{
		const char* expected[] = {"ABC", "Abc"};
		TestSplit(pILog, pIEcoBRE1, "abc", "ABCabcAbc", 2, expected);
	}
	{
		const char* expected[] = {" ", " and ", " DOE"};
		TestSplit(pILog, pIEcoBRE1, "[A-Z][a-z]+", "John Smith and Jane DOE", 3, expected);
	}
	pILog->pVTbl->Info(pILog, "\n=== Test 5 Finished ===\n");*/

	pILog->pVTbl->Info(pILog, "=== Test 6: Replace Test ===");
	TestReplace(pILog, pIEcoBRE1, "abc|de|c", "abcfgrrjtjsdehfkkrhdcjdjrwo", "K", "KfgrrjtjsKhfkkrhdKjdjrwo");          
	TestReplace(pILog, pIEcoBRE1, "world", "Hello world, world is beautiful", "earth", "Hello earth, earth is beautiful");
    TestReplace(pILog, pIEcoBRE1, "xyz", "abcdef", "D", "abcdef"); 
	TestReplace(pILog, pIEcoBRE1, "[0-9]+", "abc123def456ghi789", "KK", "abcKKdefKKghiKK");
	TestReplace(pILog, pIEcoBRE1, "a+", "abbbsaaabbaabaaaaaa", "L", "LbbbsLbbLbL");
	TestReplace(pILog, pIEcoBRE1, "a+", "aaa", "", "");
	pILog->pVTbl->Info(pILog, "\n=== Test 6 Finished ===\n");


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
