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
	TOKEN_KW_IMPORT    = 28,

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
	TOKEN_STAR         = 79,
	TOKEN_POINT        = 80,

    /* Служебные */
    TOKEN_WS           = 100,
    TOKEN_COMMENT      = 101,
    TOKEN_EOF          = 0xFFFFFFFE,
    TOKEN_ERROR        = 0xFFFFFFFF
} IDL_LEXICAL_TOKENS_e;

static void TestLexicalAnalyzerFromStringScan(IEcoLog1* pILog, IEcoLexicalAnalyzer1* pILA) {
    IEcoLexicalRules1REPtr_t pIRules = 0;
    IEcoLexicalData1* pIData = 0;
    IEcoLexicalAnalyzer1Scanner* pScanner = 0;
    IEcoLexicalAnalyzer1Token* pToken = 0;
	int16_t result;

	pILog->pVTbl->Info(pILog, "\n=== Start test lexical analyzer from string ===");

	result = pILA->pVTbl->CreateRulesRE(pILA, &pIRules);

    if (result == 0 && pIRules != 0) {
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "[0-9]+", 1001);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "([A-Z]|[a-z]|_)([A-Z]|[a-z]|[0-9]|_)*", 1002);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\{", 1003);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\}", 1004);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "( |\t|\r|\n)+", 1005);
		
		pIRules->pVTbl->SetChannel(pIRules, 1005, 1);

		pIRules->pVTbl->SetPriority(pIRules, 1005, 0);
		pIRules->pVTbl->SetPriority(pIRules, 1003, 1);
		pIRules->pVTbl->SetPriority(pIRules, 1004, 1);
		pIRules->pVTbl->SetPriority(pIRules, 1001, 2);
		pIRules->pVTbl->SetPriority(pIRules, 1002, 3);
		pILog->pVTbl->Info(pILog, "Rules added");

        result = pIRules->pVTbl->Compile(pIRules, &pIData);
		if (result != 0) {
			pILog->pVTbl->InfoFormat(pILog, "Compile failed with code %d", result);
			return;
		} else {
			pILog->pVTbl->Info(pILog, "Compile successed");
		}
		
		if (result == 0 && pIData != 0) {
			const char* test_input = "  123   abc { }  abG67";
			uint32_t input_len = (uint32_t)strlen(test_input);
			
			result = pILA->pVTbl->new_MemoryScanner(pILA, (IEcoUnknownPtr_t)pIData, (void*)test_input, input_len, &pScanner);
			if (result != 0 || pScanner == 0) {
				pILog->pVTbl->InfoFormat(pILog, "new_MemoryScanner failed with code %d", result);
				return;
			}
			pILog->pVTbl->Info(pILog, "Memory scanner created");

			pToken = pScanner->pVTbl->Scan(pScanner);
			while (pToken && !pToken->pVTbl->IsEOF(pToken)) {
				uint32_t type = pToken->pVTbl->get_Type(pToken);
				char_t* lexeme = pToken->pVTbl->get_Lexeme(pToken);
				uint32_t line = pToken->pVTbl->get_Line(pToken);
				uint32_t col = pToken->pVTbl->get_Column(pToken);
				uint32_t channel = pToken->pVTbl->get_Channel(pToken);
				
				pILog->pVTbl->InfoFormat(pILog, "Token: type=%u, lexeme='%s', line=%u, col=%u, channel=%u", type, lexeme ? lexeme : "", line, col, channel);
				
				pToken->pVTbl->Release(pToken);
				pToken = 0;
				pToken = pScanner->pVTbl->Scan(pScanner);
				
			}
			if (pToken) {
				pToken->pVTbl->Release(pToken);
				pToken = 0;
			}
		}
	}
    if (pScanner) pScanner->pVTbl->Release(pScanner);
	if (pIData) pIData->pVTbl->Release(pIData);
    if (pIRules) pIRules->pVTbl->Release(pIRules);
	pILog->pVTbl->Info(pILog, "=== Finish test lexical analyzer from string ===");
}

static void TestLexicalAnalyserFromFileScan(IEcoLog1* pILog, IEcoLexicalAnalyzer1* pILA, char_t* fileName) {
	IEcoLexicalRules1REPtr_t pIRules = 0;
    IEcoLexicalData1* pIData = 0;
    IEcoLexicalAnalyzer1Scanner* pScanner = 0;
    IEcoLexicalAnalyzer1Token* pToken = 0;
	int16_t result;

	pILog->pVTbl->Info(pILog, "\n=== Start test lexical analyzer from file ===");

	result = pILA->pVTbl->CreateRulesRE(pILA, &pIRules);

    if (result == 0 && pIRules != 0) {
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\[", TOKEN_LBRACKET);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\]", TOKEN_RBRACKET);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\{", TOKEN_LBRACE);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\}", TOKEN_RBRACE);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\(", TOKEN_LPAREN);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\)", TOKEN_RPAREN);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, ";", TOKEN_SEMI);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, ",", TOKEN_COMMA);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, ":", TOKEN_COLON);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\.", TOKEN_POINT);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\*", TOKEN_STAR);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "interface", TOKEN_KW_INTERFACE);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "uuid", TOKEN_KW_UUID);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "import", TOKEN_KW_IMPORT);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "in", TOKEN_KW_IN);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "out", TOKEN_KW_OUT);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "void", TOKEN_KW_VOID);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\"([A-Z]|[a-z]|[0-9]|_|\\[|\\]| |\\{|\\}|\\(|\\)|;|:|,|\\.|\\*)*\"", TOKEN_STRING);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "[0-9]+", TOKEN_INTEGER);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "([A-Z]|[a-z]|_)([A-Z]|[a-z]|[0-9]|_)*", TOKEN_IDENTIFIER);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "([0-9]|[a-f]|[A-F]){8}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){12}", TOKEN_UUID_LITERAL);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "( |\t|\r|\n)+", TOKEN_WS);

		pIRules->pVTbl->SetPriority(pIRules, TOKEN_STRING, 5);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_UUID_LITERAL, 6);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_INTERFACE, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_UUID, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_IMPORT, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_IN, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_OUT, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_VOID, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_LBRACKET, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_RBRACKET, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_LBRACE, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_RBRACE, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_LPAREN, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_RPAREN, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_SEMI, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_COMMA, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_COLON, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_STAR, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_POINT, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_INTEGER, 25);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_IDENTIFIER, 25); 
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_WS, 100); 
		pIRules->pVTbl->SetChannel(pIRules, TOKEN_WS, 1);
		pILog->pVTbl->Info(pILog, "Rules added");

        result = pIRules->pVTbl->Compile(pIRules, &pIData);
		if (result != 0) {
			pILog->pVTbl->InfoFormat(pILog, "Compile failed with code %d", result);
			return;
		} else {
			pILog->pVTbl->Info(pILog, "Compile successed");
		}

		if (result == 0 && pIData != 0) {
			result = pILA->pVTbl->new_FileScanner(pILA, (IEcoUnknownPtr_t)pIData, fileName, &pScanner);
			if (result != 0) {
				pILog->pVTbl->InfoFormat(pILog, "ERROR: failed when scanning a file with code %d", result);
				return;
			} else {
				pILog->pVTbl->Info(pILog, "SUCCESS scanned a file");
			}

			pToken = pScanner->pVTbl->Scan(pScanner);
			while (pToken && !pToken->pVTbl->IsEOF(pToken)) {
				uint32_t type = pToken->pVTbl->get_Type(pToken);
				char_t* lexeme = pToken->pVTbl->get_Lexeme(pToken);
				uint32_t line = pToken->pVTbl->get_Line(pToken);
				uint32_t col = pToken->pVTbl->get_Column(pToken);
				uint32_t channel = pToken->pVTbl->get_Channel(pToken);
				
				pILog->pVTbl->InfoFormat(pILog, "Token: type=%u, lexeme='%s', line=%u, col=%u, channel=%u", type, lexeme ? lexeme : "", line, col, channel);
				
				pToken->pVTbl->Release(pToken);
				pToken = 0;
				pToken = pScanner->pVTbl->Scan(pScanner);
				
			}
			if (pToken) {
				pToken->pVTbl->Release(pToken);
				pToken = 0;
			}
		}
	}
    if (pScanner) pScanner->pVTbl->Release(pScanner);
	if (pIData) pIData->pVTbl->Release(pIData);
    if (pIRules) pIRules->pVTbl->Release(pIRules);
	pILog->pVTbl->Info(pILog, "=== Finish test lexical analyzer from file ===");
}

static void TestLexicalAnalyserSaveToFile(IEcoLog1* pILog, IEcoLexicalAnalyzer1* pILA) {
	IEcoLexicalRules1REPtr_t pIRules = 0;
    IEcoLexicalData1* pIData = 0;
	int16_t result;

	pILog->pVTbl->Info(pILog, "\n=== Start test lexical analyzer save to file ===");

	result = pILA->pVTbl->CreateRulesRE(pILA, &pIRules);

    if (result == 0 && pIRules != 0) {
        pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\[", TOKEN_LBRACKET);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\]", TOKEN_RBRACKET);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\{", TOKEN_LBRACE);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\}", TOKEN_RBRACE);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\(", TOKEN_LPAREN);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\)", TOKEN_RPAREN);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, ";", TOKEN_SEMI);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, ",", TOKEN_COMMA);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, ":", TOKEN_COLON);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\.", TOKEN_POINT);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\\*", TOKEN_STAR);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "interface", TOKEN_KW_INTERFACE);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "uuid", TOKEN_KW_UUID);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "import", TOKEN_KW_IMPORT);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "in", TOKEN_KW_IN);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "out", TOKEN_KW_OUT);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "void", TOKEN_KW_VOID);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "\"([A-Z]|[a-z]|[0-9]|_|\\[|\\]| |\\{|\\}|\\(|\\)|;|:|,|\\.|\\*)*\"", TOKEN_STRING);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "[0-9]+", TOKEN_INTEGER);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "([A-Z]|[a-z]|_)([A-Z]|[a-z]|[0-9]|_)*", TOKEN_IDENTIFIER);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "([0-9]|[a-f]|[A-F]){8}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){12}", TOKEN_UUID_LITERAL);
		pIRules->pVTbl->AddRuleRE(pIRules, 0, "( |\t|\r|\n)+", TOKEN_WS);

		pIRules->pVTbl->SetPriority(pIRules, TOKEN_STRING, 5);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_UUID_LITERAL, 6);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_INTERFACE, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_UUID, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_IMPORT, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_IN, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_OUT, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_KW_VOID, 10);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_LBRACKET, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_RBRACKET, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_LBRACE, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_RBRACE, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_LPAREN, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_RPAREN, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_SEMI, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_COMMA, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_COLON, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_STAR, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_POINT, 15);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_INTEGER, 25);
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_IDENTIFIER, 25); 
		pIRules->pVTbl->SetPriority(pIRules, TOKEN_WS, 100); 
		pIRules->pVTbl->SetChannel(pIRules, TOKEN_WS, 1);
		pILog->pVTbl->Info(pILog, "Rules added");

        result = pIRules->pVTbl->Compile(pIRules, &pIData);
		if (result != 0) {
			pILog->pVTbl->InfoFormat(pILog, "Compile failed with code %d", result);
			return;
		} else {
			pILog->pVTbl->Info(pILog, "Compile successed");
		}
		
		if (result == 0 && pIData != 0) {
			result = pILA->pVTbl->SaveRulesToFile(pILA, (IEcoUnknownPtr_t)pIData, "idl_core.bin");
			if (result != 0) {
				pILog->pVTbl->InfoFormat(pILog, "ERROR: failed when saving rules to a file with code %d", result);
				return;
			} else {
				pILog->pVTbl->Info(pILog, "SUCCESS saved rules to a file");
			}
		}
	}
	if (pIData) pIData->pVTbl->Release(pIData);
    if (pIRules) pIRules->pVTbl->Release(pIRules);
	pILog->pVTbl->Info(pILog, "=== Finish test lexical analyzer save to file ===");
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

    pILog->pVTbl->Info(pILog, "\n=== Start tests ===");
    TestLexicalAnalyzerFromStringScan(pILog, pILA);
	TestLexicalAnalyserFromFileScan(pILog, pILA, "IEcoBRE1.idl");
	TestLexicalAnalyserFromFileScan(pILog, pILA, "IEcoBinaryTree1.idl");
	TestLexicalAnalyserSaveToFile(pILog, pILA);
	pILog->pVTbl->Info(pILog, "\n=== Finish tests ===");
        


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