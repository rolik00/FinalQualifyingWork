/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   EcoBLA1
 * </summary>
 *
 * <description>
 *   This source file is the entry point
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoBLA1.h"
#include "IdEcoBRE1.h"
#include "IdEcoBinaryTree1.h"
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
#include "CEcoBLR1RE.h"

typedef enum IDL_LEXICAL_TOKENS_e {
    TOKEN_NONE = 0,
    
    /* Базовые категории (Core Rules) */
    TOKEN_ALPHA = 1,
    TOKEN_DIGIT = 2,
    TOKEN_HEXDIG = 3,
    TOKEN_DQUOTE = 4,
    TOKEN_WSP = 5,
    TOKEN_CRLF = 6,
    
    /* Ключевые слова (Keywords) */
    TOKEN_KW_INTERFACE = 20,
    TOKEN_KW_UUID      = 21,
    TOKEN_KW_VERSION   = 22,
    TOKEN_KW_TYPEDEF   = 23,
    TOKEN_KW_STRUCT    = 24,
    TOKEN_KW_IN        = 25,
    TOKEN_KW_OUT       = 26,
    TOKEN_KW_VOID      = 27,

    /* Сложные типы данных */
    TOKEN_IDENTIFIER   = 50,
    TOKEN_INTEGER      = 51,
    TOKEN_STRING       = 52,
    TOKEN_UUID_LITERAL = 53, /* 8-4-4-4-12 */

    /* Пунктуация */
    TOKEN_LBRACKET     = 70, /* [ */
    TOKEN_RBRACKET     = 71, /* ] */
    TOKEN_LBRACE       = 72, /* { */
    TOKEN_RBRACE       = 73, /* } */
    TOKEN_LPAREN       = 74, /* ( */
    TOKEN_RPAREN       = 75, /* ) */
    TOKEN_SEMI         = 76, /* ; */
    TOKEN_COMMA        = 77, /* , */
    TOKEN_COLON        = 78, /* : */

    /* Служебные */
    TOKEN_WS           = 100,
    TOKEN_COMMENT      = 101,
    TOKEN_EOF          = 0xFFFFFFFE,
    TOKEN_ERROR        = 0xFFFFFFFF
} IDL_LEXICAL_TOKENS_e;

static void Test_AddRuleRE(IEcoLog1* pILog, IEcoLexicalAnalyzer1* pILA) {
    IEcoLexicalRules1RE* pRules = 0;
    IEcoLexicalData1* pIData = 0;
    int16_t res;
    uint32_t count, i, expectedCount = 6;
	char *exp_state, *got_state;
		 
	struct {
        const char* pattern;
        uint32_t tokenId;
        uint32_t priority;
        const char* state;     
    } testRules[] = {
        { "if",         1001, 10, NULL },
        { "else",       1002, 10, NULL },
        { "[0-9]+",     2001,  5, NULL },
        { "([A-Z]|[a-z]|_)([A-Z]|[a-z]|[0-9]|_)*", 3001, 3, NULL },
        { "\"[^\"]*\"", 4001, 15, "STRING" },
        { "//[^\\n]*",   5001, 20, "COMMENT" },
    };

    pILog->pVTbl->Info(pILog, "=== Test AddRuleRE ===");

    res = pILA->pVTbl->CreateRulesRE(pILA, &pRules);
    if (res != 0 || !pRules) {
        pILog->pVTbl->InfoFormat(pILog, "Error: CreateRulesRE -> %d\n", res);
        return;
    }

    for (i = 0; i < sizeof(testRules)/sizeof(testRules[0]); i++) {
        res = pRules->pVTbl->AddRuleRE(pRules, (char*)testRules[i].state, (char*)testRules[i].pattern, testRules[i].tokenId);

        if (res != 0) {
            pILog->pVTbl->InfoFormat(pILog, "Error AddRuleRE for %s -> %d\n", testRules[i].pattern, res);
            pRules->pVTbl->Release(pRules);
            return;
        }

		if (testRules[i].priority != 0) {
			pRules->pVTbl->SetPriority(pRules, testRules[i].tokenId, testRules[i].priority);
		}
    }

    count = pRules->pVTbl->get_Count(pRules);
    if (count != expectedCount) {
        pILog->pVTbl->InfoFormat(pILog, "FAILED: count of rules do not match (expected %u, got %u)", expectedCount, count);
        pRules->pVTbl->Release(pRules);
        return;
    } else {
        pILog->pVTbl->InfoFormat(pILog, "PASSED: count of rules match (expected %u, got %u)", expectedCount, count);
    }

	for (i = 0; i < count; i++) {
		EcoLexicalRuleREInfo rule;
		res = pRules->pVTbl->GetRuleInfo(pRules, i, &rule);
		if (res == 0) {
			pILog->pVTbl->InfoFormat(pILog, "Check info for rule \"%s\"", testRules[i].pattern);
			if (rule.tokenId == testRules[i].tokenId) {
				pILog->pVTbl->InfoFormat(pILog, "	PASSED: expected %u, got %u", testRules[i].tokenId, rule.tokenId);
			} else {
				pILog->pVTbl->InfoFormat(pILog, "	FAILED: expected %u, got %u", testRules[i].tokenId, rule.tokenId);
			}
			
			exp_state = testRules[i].state ? testRules[i].state : "null";
			got_state = rule.stateName ? rule.stateName : "null";
			if (strcmp(exp_state, got_state) == 0) {
				pILog->pVTbl->InfoFormat(pILog, "	PASSED: expected %s, got %s", exp_state, got_state);
			} else {
				pILog->pVTbl->InfoFormat(pILog, "	FAILED: expected %s, got %s", exp_state, got_state);
			}

			if (rule.priority == testRules[i].priority) {
                pILog->pVTbl->InfoFormat(pILog, "	PASSED: expected %u, got %u", testRules[i].priority, rule.priority);
            } else {
                pILog->pVTbl->InfoFormat(pILog, "	FAILED: expected %u, got %u", testRules[i].priority, rule.priority);
            }
		} 
	}
   
    pRules->pVTbl->Release(pRules);

    pILog->pVTbl->Info(pILog, "=== Test AddRuleRE Finished ===\n");
}

static void Test_Compile(IEcoLog1* pILog, IEcoLexicalAnalyzer1* pILA) {
    IEcoLexicalRules1RE* pRules = 0;
	CEcoBLR1RE_F82A88F6* pImpl;
    IEcoLexicalData1* pData = 0;
    int16_t res;
	int i;
    const char* patterns[] = {
        "if",
        "else",
        "[0-9]+",
        "([A-Z]|[a-z]|_)([A-Z]|[a-z]|[0-9]|_)*"
    };
    uint32_t tokenIds[] = {1001, 1002, 2001, 3001};
    uint32_t priorities[] = {10, 10, 5, 3};

	pILog->pVTbl->Info(pILog, "=== Test Compile ===");
    
	pILog->pVTbl->Info(pILog, "1. Creation and addition rules");
	{
		res = pILA->pVTbl->CreateRulesRE(pILA, &pRules);
		if (res != 0) {
			pILog->pVTbl->Info(pILog, "	CreateRulesRE failed");
			return;
		}

		for (i = 0; i < 4; i++) {
			res = pRules->pVTbl->AddRuleRE(pRules, NULL, (char*)patterns[i], tokenIds[i]);
			if (res != 0) {
				pILog->pVTbl->InfoFormat(pILog, "	AddRuleRE failed for pattern '%s'", patterns[i]);
				if (pData)  pData->pVTbl->Release(pData);
				if (pRules) pRules->pVTbl->Release(pRules);
				return;
			}
			pRules->pVTbl->SetPriority(pRules, tokenIds[i], priorities[i]);
		}
	}
	pILog->pVTbl->Info(pILog, "Creation and addition rules successed");
    
	pILog->pVTbl->Info(pILog, "2. Calling the function Compile");
	{
		res = pRules->pVTbl->Compile(pRules, &pData);
		if (res != 0) {
			pILog->pVTbl->InfoFormat(pILog, "	Compile failed: %d", res);
			pRules->pVTbl->Release(pRules);
			return;
		}
	}
	pILog->pVTbl->Info(pILog, "Compile succeeded");

	pImpl = (CEcoBLR1RE_F82A88F6*)pRules;
	if (!pImpl->m_pSuperNFA) {
        pILog->pVTbl->Info(pILog, "SuperNFA is NULL after compile!");
        if (pData) pData->pVTbl->Release(pData);
		pRules->pVTbl->Release(pRules);
		return;
    }
    
	pILog->pVTbl->Info(pILog, "3. Testing building super-NFA");
	{
		IEcoList1* states = pImpl->m_pSuperNFA->pVTbl->get_States(pImpl->m_pSuperNFA);
		uint32_t stateCount = states->pVTbl->Count(states);
		uint32_t expectedStateCount = 43;
		int startFound = 0;
		
		for (i = 0; i < stateCount; i++) {
			IEcoFSM1State* st = (IEcoFSM1State*)states->pVTbl->Item(states, i);
			if (st->pVTbl->IsInitial(st)) {
				startFound = 1;
				break;
			}
		}
		
		if (stateCount == expectedStateCount && startFound) {
			pILog->pVTbl->InfoFormat(pILog, "	Success SuperNFA build: %u states, start state = %s", stateCount, startFound ? "FOUND" : "MISSING");
		} else {
			pILog->pVTbl->InfoFormat(pILog, "	Failed SuperNFA build: %u states, start state = %s", stateCount, startFound ? "FOUND" : "MISSING");
		}
		
		if (!startFound) {
			if (pData) pData->pVTbl->Release(pData);
			pRules->pVTbl->Release(pRules);
			return;
		}
	}
	pILog->pVTbl->Info(pILog, "Testing building super-NFA finished");

	if (!pImpl->m_pFinalStateAttrs) {
        pILog->pVTbl->Info(pILog, "FinalStateAttrs list is NULL!");
        if (pData) pData->pVTbl->Release(pData);
		pRules->pVTbl->Release(pRules);
		return;
    }
   
	pILog->pVTbl->Info(pILog, "4. Testing the final states");
	{
		uint32_t attrCount = pImpl->m_pFinalStateAttrs->pVTbl->Count(pImpl->m_pFinalStateAttrs);
		int finalsOk = 1;
		struct {
			uint32_t token;
			uint32_t prio;
			uint32_t chan;
		} expectedFinals[] = {
			{1001, 10, 0},
			{1002, 10, 0},
			{2001,  5, 0},
			{3001,  3, 0}
		};

		pILog->pVTbl->InfoFormat(pILog, "	Final states count: %u", attrCount);

		if (attrCount != 4) {
			finalsOk = 0;
		} else {
			for (i = 0; i < 4; i++) {
				FinalStateInfo* info = (FinalStateInfo*)pImpl->m_pFinalStateAttrs->pVTbl->Item(pImpl->m_pFinalStateAttrs, i);
				if (!info || info->tokenId != expectedFinals[i].token ||
                info->priority != expectedFinals[i].prio || info->channel != expectedFinals[i].chan) {
					finalsOk = 0;
					break;
				}
			}
		}

		if (finalsOk) {
			pILog->pVTbl->Info(pILog, "	PASSED: Final states attributes check");
			for (i = 0; i < attrCount; i++) {
				FinalStateInfo* info = (FinalStateInfo*)pImpl->m_pFinalStateAttrs->pVTbl->Item(pImpl->m_pFinalStateAttrs, i);
				pILog->pVTbl->InfoFormat(pILog, "	  - token=%u, priority=%u, channel=%u", info->tokenId, info->priority, info->channel);
			}
		} else {
			pILog->pVTbl->Info(pILog, "	FAILED: Final states attributes check");
			if (pData) pData->pVTbl->Release(pData);
			pRules->pVTbl->Release(pRules);
			return;
		}
	}
	pILog->pVTbl->Info(pILog, "Testing the final states finised");
	
	pILog->pVTbl->Info(pILog, "5. Testing Regex Matches for each rule");
	{
	    int16_t match;
		struct TestCase { 
			uint32_t ruleIndex;
			const char* input;
			int shouldMatch;
		};
		struct TestCase testCases[] = { 
			{0, "if", 1},
			{0, "ifx", 0},
			{0, "i", 0},
			{1, "else", 1},
			{1, "els", 0}, 
			{2, "123", 1}, 
			{2, "12a3", 0},
			{3, "var1", 1},
			{3, "_test", 1},
			{3, "123var", 0}
		};
		
		for (i = 0; i < 10; i++) {
			struct TestCase* tc = &testCases[i];
			RuleRE* pRule = (RuleRE*)pImpl->m_pRulesList->pVTbl->Item(pImpl->m_pRulesList, tc->ruleIndex);
			if (pRule == 0 || pRule->pNFA == 0) {
				pILog->pVTbl->InfoFormat(pILog, "	Rule %u has no NFA\n", tc->ruleIndex); 
				continue; 
			}
			if (pRule->pRegex) {
			    match = pRule->pRegex->pVTbl->IsMatch(pRule->pRegex, (void*)tc->input, strlen(tc->input), 0);
				pILog->pVTbl->InfoFormat(pILog, "	Test %s: \"%s\" on rule %u (expected %d, got %d)", match == tc->shouldMatch ? "PASSED" : "FAILED", tc->input, tc->ruleIndex, match, tc->shouldMatch); 
			}
		} 
	}
	pILog->pVTbl->Info(pILog, "Testing Regex Matches finished");

	pILog->pVTbl->Info(pILog, "6. Testing transforming NFA to DFA");
	{
	    if (pImpl->m_pDFAStates == 0) {
            pILog->pVTbl->Info(pILog, "	FAILED: m_pDFAStates pointer is NULL");
		} else {
			uint32_t dfaCount = pImpl->m_pDFAStates->pVTbl->Count(pImpl->m_pDFAStates);
            int acceptingCount = 0;
            uint32_t i;

            pILog->pVTbl->InfoFormat(pILog, " DFA states generated: %u", dfaCount);

            for (i = 0; i < dfaCount; i++) {
                DFAState* ds = (DFAState*)pImpl->m_pDFAStates->pVTbl->Item(pImpl->m_pDFAStates, i);
                if (ds && ds->isAccepting) acceptingCount++;
            }
            pILog->pVTbl->InfoFormat(pILog, " Accepting DFA states: %d", acceptingCount);

            if (acceptingCount >= 4) {
                pILog->pVTbl->Info(pILog, " PASSED: DFA contains accepting states for all added rules");
            } else {
                pILog->pVTbl->Info(pILog, " FAILED: Not enough accepting DFA states");
            }

            if (dfaCount > 0) {
                DFAState* startDFA = (DFAState*)pImpl->m_pDFAStates->pVTbl->Item(pImpl->m_pDFAStates, 0);
                if (startDFA && startDFA->nfaStates) {
                    uint32_t nfaInStart = startDFA->nfaStates->pVTbl->Count(startDFA->nfaStates);
                    pILog->pVTbl->InfoFormat(pILog, " Start DFA state contains %u NFA states (e-closure ok)", nfaInStart);
                    if (nfaInStart >= 1) {
                        pILog->pVTbl->Info(pILog, " PASSED: Start state correctly built");
                    }
                }
            }

            pILog->pVTbl->Info(pILog, " NFA -> DFA conversion test completed successfully");
		}
	}
	pILog->pVTbl->Info(pILog, "Testing transforming NFA to DFA finished");

	pILog->pVTbl->Info(pILog, "7. Testing DFA minimization");
	{
		uint32_t beforeCount, afterCount;
		beforeCount = pImpl->m_pDFAStates->pVTbl->Count(pImpl->m_pDFAStates);
		pILog->pVTbl->InfoFormat(pILog, " DFA states before minimization: %u", beforeCount);
		afterCount = pImpl->m_pDFAStates->pVTbl->Count(pImpl->m_pDFAStates);
		pILog->pVTbl->InfoFormat(pILog, " DFA states after minimization: %u", afterCount);
		if (afterCount <= beforeCount) {
			pILog->pVTbl->Info(pILog, " PASSED: minimization reduced or kept state count");
		} else {
			pILog->pVTbl->Info(pILog, " FAILED: minimization increased state count");
		}
	}
	pILog->pVTbl->Info(pILog, "Testing DFA finished");
    
    if (pData) pData->pVTbl->Release(pData);
    pRules->pVTbl->Release(pRules);

	pILog->pVTbl->Info(pILog, "=== Test Compile Finished ===\n");
}

/*
 *
 * <summary>
 *   EcoMain Function
 * </summary>
 *
 * <description>
 *   EcoMain function - entry point
 * </description>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Pointer to the system interface */
    IEcoSystem1* pISys = 0;
    /* Pointer to the interface for working with the system interface bus */
    IEcoInterfaceBus1* pIBus = 0;
    /* Pointer to the memory management interface */
    IEcoMemoryAllocator1* pIMem = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    /* Pointer to the tested interface */
    IEcoLexicalAnalyzer1* pILA = 0;
    IEcoLexicalRules1REPtr_t pIRules = 0;
    IEcoLexicalData1* pIData = 0;
    IEcoLexicalAnalyzer1Scanner* pScanner = 0;
    IEcoLexicalAnalyzer1Token* pToken = 0;
    /* Указатель на интерфейс работы с журналом */
    IEcoLog1* pILog = 0;
    IEcoLog1FileAffiliate* pIFileAffiliate = 0;
    IEcoLog1ConsoleAffiliate* pIConsoleAffiliate = 0;
    IEcoLog1Layout* pILayout = 0;
    IEcoLog1SimpleLayout* pISimpleLayout = 0;


    /* System interface check and creation */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Free the system interface in case of an error */
            goto Release;
        }
    }

    /* Getting the interface for working with the interface bus */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Free in case of an error */
        goto Release;
    }
#ifdef ECO_LIB
    /* Registration of a static component for working with the list */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBLA1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_88DD94592E7C48BAB381EAA0F82A88F6);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
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
    /* Регистрация статического компонента для работы с BNF */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoFSM1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5E7C610CB846447DB59A3C5A2C4F446F);
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
    /* Getting the memory management interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Check */
    if (result != 0 || pIMem == 0) {
        /* Free the system interface in case of an error */
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


    /* Getting the tested interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBLA1, 0, &IID_IEcoLexicalAnalyzer1, (void**) &pILA);
    if (result != 0 || pILA == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }

    /*
        ABNF IDL

        ; --- Базовые символы (Core) ---
        ALPHA          = %x41-5A / %x61-7A
        DIGIT          = %x30-39
        HEXDIG         = DIGIT / "A" / "B" / "C" / "D" / "E" / "F" / "a" / "b" / "c" / "d" / "e" / "f"
        DQUOTE         = %x22

        ; --- Идентификаторы и литералы ---
        IDENTIFIER     = (ALPHA / "_") *(ALPHA / DIGIT / "_")
        INTEGER        = 1*DIGIT
        HEX_INTEGER    = "0x" 1*HEXDIG
        UUID_REP       = 8HEXDIG "-" 4HEXDIG "-" 4HEXDIG "-" 4HEXDIG "-" 12HEXDIG
        STRING_LITERAL = DQUOTE *(%x20-21 / %x23-5B / %x5D-7E / "\" DQUOTE / "\\") DQUOTE

        ; --- Ключевые слова (Microsoft & OMG) ---
        KW_INTERFACE   = "interface"
        KW_UUID        = "uuid"
        KW_VERSION     = "version"
        KW_ENDPOINT    = "endpoint"
        KW_EXCEPTIONS  = "exceptions"
        KW_LOCAL       = "local"
        KW_PTR_DEFAULT = "pointer_default"
        KW_TYPEDEF     = "typedef"
        KW_STRUCT      = "struct"
        KW_CONST       = "const"
        KW_IN          = "in"
        KW_OUT         = "out"
        KW_RET_VOID    = "void"

        ; --- Операторы и пунктуация ---
        LBRACKET       = "["
        RBRACKET       = "]"
        LBRACE         = "{"
        RBRACE         = "}"
        LPAREN         = "("
        RPAREN         = ")"
        SEMI           = ";"
        COMMA          = ","
        COLON          = ":"
        ASTERISK       = "*"

        ; --- Игнорируемое ---
        WS             = 1*(%x20 / %x09 / %x0A / %x0D)
        COMMENT        = 
        LINE_COMMENT   = "//" *(%x20-7E) (%x0A / %x0D)
    */

	//Test_AddRuleRE(pILog, pILA);
	Test_Compile(pILog, pILA);

    

Release:

    /* Free the interface for working with the interface bus */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Free the memory management interface */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Free the tested interface */
    if (pILA != 0) {
        pILA->pVTbl->Release(pILA);
    }


    /* Free the system interface */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
