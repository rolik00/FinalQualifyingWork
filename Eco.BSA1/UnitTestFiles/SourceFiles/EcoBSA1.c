/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   EcoBSA1
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
#include "IdEcoBSA1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoBLA1.h"
#include "IdEcoBRE1.h"
#include "IdEcoBinaryTree1.h"
#include "IdEcoTree1.h"
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
#include "IdEcoLR1.h"
#include "IdEcoPDA1.h"
#include "IdEcoData1.h"
#include "IdEcoStack1.h"
#include "IdEcoDictionary1.h"
#include "IdEcoBNF1.h"
#include "IdEcoMap2.h"
#include "IdEcoSet2.h"
#include "IdEcoComparator1.h"
#include "IEcoContainer1.h"
#include "IdEcoQueue1.h"
#include "IdEcoVisitor1.h"
#include "CEcoASTPrintVisitor.h"

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

static void TestAnalyserFromFile(/* in */ IEcoSystem1* pISys, IEcoLog1* pILog, /* in */ IEcoString1* pIStr, IEcoLexicalAnalyzer1* pILA, IEcoSyntaxAnalyzer1* pISA, IEcoBNF1* pIBNF, IEcoParser1LRk* pILRk, char_t* fileName);

IEcoLexicalData1* GetTestLEX(IEcoLog1* pILog, IEcoString1* pIStr, IEcoBNF1* pIBNF, IEcoLexicalAnalyzer1* pILA);
IEcoBNF1* GetTestBNF(IEcoLog1* pILog, IEcoBNF1* pIBNF);
bool_t OutputDiagnosticInfoOfBNF(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoBNF1* pGrammar);
bool_t OutputDiagnosticInfoOfAST(/* in */ IEcoSystem1* pISys, /* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoAST1* pIAST);
bool_t OutputDiagnosticInfoOfParser(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoParser1LRk* pILRk);
bool_t OutputDiagnosticInfoOfFSM(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoParser1LRk* pILRk);

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
    /* Pointer to the tested interface */
    IEcoSyntaxAnalyzer1* pISA = 0;
    IEcoBNF1* pIBNF = 0;
    IEcoParser1LRk* pILRk = 0;
    IEcoString1* pIStr = 0;

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
    /* Registration of a static component for working with the BSA */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBSA1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_FF73C4B2F8B0484897DB3298F6E9D8E1);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    /* Registration of a static component for working with the BLA */
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
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoTree1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_82F73722057E47F3A2931ED27087694D);
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
    /* Регистрация статического компонента для работы с LRk */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLR1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_F4561FD215A34CC5BA1D8791A441A18E);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Map */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMap2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_715AF131CD174E90AAF3B753221B9B73);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Set */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoSet2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_58CDC2713209420CAC919BE1E16F4CA4);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Comparator */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoComparator1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_44CE56A815DF433EB567D8943DA32D8E);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Queue */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoQueue1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_25D72F83A2564F4E9F59E489BE85E2A4);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Stack */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoStack1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_18129B1DCF9248D9A7787F9206E2D6DC);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с BNF */
    result =pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBNF1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_323DD55E33D040FA98068E2FCB1CBD49);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с PDA */
    result =pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoPDA1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_A03120BB3AF5425EBDE0A5535B423579);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Dictionary */
    result =pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoDictionary1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_2912A7C7E0B84B4D9BFE9500EF4667D3);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с AST */
    result =pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoAST1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_2FE0BD508F5743BDA9F52414233542A8);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Visitor */
    result =pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoVisitor1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4E7C20FEFAF341069B5C42497B462BBE);
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

    /* Получение интерфейса работы с String */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**)&pIStr);
    if (result != 0 || pIStr == 0) {
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

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBLA1, 0, &IID_IEcoLexicalAnalyzer1, (void**) &pILA);
    if (result != 0 || pILA == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBNF1, 0, &IID_IEcoBNF1, (void**) &pIBNF);
    if (result != 0 || pIBNF == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLR1, 0, &IID_IEcoParser1LRk, (void**) &pILRk);
    if (result != 0 || pILRk == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }

    /* Getting the tested interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBSA1, 0, &IID_IEcoSyntaxAnalyzer1, (void**) &pISA);
    if (result != 0 || pISA == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBNF1, 0, &IID_IEcoBNF1, (void**) &pIBNF);
    if (result != 0 || pIBNF == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }

    pILog->pVTbl->Info(pILog, "\n=== Start tests ===");
    TestAnalyserFromFile(pISys, pILog, pIStr, pILA, pISA, pIBNF, pILRk, "IEcoBRE1.idl");
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
    if (pISA != 0) {
        pISA->pVTbl->Release(pISA);
    }


    /* Free the system interface */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

static void TestAnalyserFromFile(/* in */ IEcoSystem1* pISys, IEcoLog1* pILog, /* in */ IEcoString1* pIStr, IEcoLexicalAnalyzer1* pILA, IEcoSyntaxAnalyzer1* pISA, IEcoBNF1* pIBNF, IEcoParser1LRk* pILRk, char_t* fileName) {
    IEcoLexicalRules1REPtr_t pIRules = 0;
    IEcoLexicalData1* pIData = 0;
    IEcoLexicalAnalyzer1Scanner* pScanner = 0;
    IEcoSyntaxAnalyzer1Parser* pParser = 0;
    IEcoParser1Action* pAction = 0;
    IEcoAST1* pIAST = 0;
    IEcoLexicalAnalyzer1Token* pToken = 0;
    int16_t result;

    pILog->pVTbl->Info(pILog, "\n=== Start test from file ===");

    pIBNF = GetTestBNF(pILog, pIBNF);
    OutputDiagnosticInfoOfBNF( pILog, pIStr, pIBNF);
    pIData = GetTestLEX(pILog, pIStr, pIBNF, pILA);

    result = pILA->pVTbl->CreateRulesRE(pILA, &pIRules);

    if (result == 0 && pIData != 0) {
        result = pILA->pVTbl->new_FileScanner(pILA, (IEcoUnknownPtr_t)pIData, fileName, &pScanner);
        if (result != 0) {
            pILog->pVTbl->InfoFormat(pILog, "ERROR: failed when scanning a file with code %d", result);
            return;
        } else {
            pILog->pVTbl->Info(pILog, "SUCCESS scanned a file");
    }

    pISA->pVTbl->RegisterAlgorithm(pISA, &CID_EcoLR1, "LRk");
    pParser = pISA->pVTbl->get_Parser(pISA, pIBNF, 0);
    OutputDiagnosticInfoOfParser( pILog, pIStr, (IEcoParser1LRk*)pParser->pVTbl->get_Algorithm(pParser));
    OutputDiagnosticInfoOfFSM( pILog, pIStr, (IEcoParser1LRk*)pParser->pVTbl->get_Algorithm(pParser));
    pToken = pScanner->pVTbl->Scan(pScanner);
    while (pToken) {
        uint32_t type = pToken->pVTbl->get_Type(pToken);
        char_t* lexeme = pToken->pVTbl->get_Lexeme(pToken);
        uint32_t line = pToken->pVTbl->get_Line(pToken);
        uint32_t col = pToken->pVTbl->get_Column(pToken);
        uint32_t channel = pToken->pVTbl->get_Channel(pToken);
		bool_t isEOF = pToken->pVTbl->IsEOF(pToken);

        pILog->pVTbl->InfoFormat(pILog, "Token: type=%u, lexeme='%s', line=%u, col=%u, channel=%u", type, lexeme ? lexeme : "", line, col, channel);
        
        if (channel == 0) {
            pAction = pParser->pVTbl->Parse(pParser, pToken);
		}

		if (isEOF) {
			break;
		}

        pToken->pVTbl->Release(pToken);
        pToken = 0;
        pToken = pScanner->pVTbl->Scan(pScanner);
    }
    if (pToken) {
        pToken->pVTbl->Release(pToken);
        pToken = 0;
    }
    pIAST = pParser->pVTbl->get_AST(pParser);
    OutputDiagnosticInfoOfAST(pISys, pILog, pIStr, pIAST);
    if (pScanner) pScanner->pVTbl->Release(pScanner);
    if (pIData) pIData->pVTbl->Release(pIData);
    if (pIRules) pIRules->pVTbl->Release(pIRules);
    pILog->pVTbl->Info(pILog, "=== Finish test  from file ===");
}
}

IEcoLexicalData1* GetTestLEX(IEcoLog1* pILog, IEcoString1* pIStr, IEcoBNF1* pIBNF, IEcoLexicalAnalyzer1* pILA) {
    IEcoLexicalRules1REPtr_t pIRules = 0;
    IEcoLexicalData1* pIData = 0;
    IEcoList1* pIRuleSet = 0;
    IEcoList1* pIElementList = 0;
    IEcoList1* pIRuleList = 0;
    IEcoList1* pITerminals = 0;

    IEcoBNF1Element* pIElement = 0;
    int16_t result;
    bool_t bFound = 0;
    IEcoBNF1Rule* pIRule = 0;
    char_t* Word = 0;
    uint32_t index = 0;
    uint32_t indexRule = 0;
    uint32_t indexSet = 0;
    uint32_t indexElement = 0;
    uint32_t lastId = 0;
    bool_t isAdded[1024]; 
    uint32_t currentId = 0;
    memset(isAdded, 0, sizeof(isAdded));

    pILog->pVTbl->Info(pILog, "\n=== Create lexical analyzer  ===");
    result = pILA->pVTbl->CreateRulesRE(pILA, &pIRules);
    if (result == 0 && pIRules != 0) {
        /* Получение списков */
        pIRuleList = pIBNF->pVTbl->get_RuleList(pIBNF);
        pITerminals = pIBNF->pVTbl->get_TerminalAlphabet(pIBNF);
        for (index = 0; index < pITerminals->pVTbl->Count(pITerminals); index++) {
            Word = (char_t*)pITerminals->pVTbl->Item(pITerminals, index);

            for (indexRule = 0; indexRule < pIRuleList->pVTbl->Count(pIRuleList); indexRule++) {
                pIRule = (IEcoBNF1Rule*)pIRuleList->pVTbl->Item(pIRuleList, indexRule);
                pIRuleSet = pIRule->pVTbl->get_RuleSet(pIRule);
                for (indexSet = 0; indexSet < pIRuleSet->pVTbl->Count(pIRuleSet); indexSet++) {
                    pIElementList = (IEcoList1*)pIRuleSet->pVTbl->Item(pIRuleSet, indexSet);
                    for (indexElement = 0; indexElement < pIElementList->pVTbl->Count(pIElementList); indexElement++) {
                        pIElement = (IEcoBNF1Element*)pIElementList->pVTbl->Item(pIElementList, indexElement);
                        currentId = pIElement->pVTbl->get_Id(pIElement);
                        
                        if (pIStr->pVTbl->Compare(pIStr, pIElement->pVTbl->get_Name(pIElement), Word) == 0 && currentId < 1024 && !isAdded[currentId]) {
                            if (pIStr->pVTbl->Compare(pIStr, Word, "epsilon") == 0) {
                                continue; 
                            }
                            pILog->pVTbl->InfoFormat(pILog, "Terminal: ID = %d, Name = %s", pIElement->pVTbl->get_Id(pIElement), pIElement->pVTbl->get_Name(pIElement));
                            if (pIStr->pVTbl->Compare(pIStr, Word, "id") == 0) {
                                pIRules->pVTbl->AddRuleRE(pIRules, 0, "([A-Z]|[a-z]|_)([A-Z]|[a-z]|[0-9]|_)*", currentId);
                                pIRules->pVTbl->SetPriority(pIRules, currentId, 50); 
                            } else if (pIStr->pVTbl->Compare(pIStr, Word, "string_literal") == 0) {
                                pIRules->pVTbl->AddRuleRE(pIRules, 0, "\"([A-Z]|[a-z]|[0-9]|_|\\[|\\]| |\\{|\\}|\\(|\\)|;|:|,|\\.|\\*)*\"", currentId);
                                pIRules->pVTbl->SetPriority(pIRules, currentId, 5);
                            } else if (pIStr->pVTbl->Compare(pIStr, Word, "{") == 0 || 
                                     pIStr->pVTbl->Compare(pIStr, Word, "}") == 0 ||
                                     pIStr->pVTbl->Compare(pIStr, Word, "(") == 0 ||
                                     pIStr->pVTbl->Compare(pIStr, Word, ")") == 0 ||
                                     pIStr->pVTbl->Compare(pIStr, Word, "[") == 0 ||
                                     pIStr->pVTbl->Compare(pIStr, Word, "]") == 0 ||
                                     pIStr->pVTbl->Compare(pIStr, Word, ":") == 0 ||
                                     pIStr->pVTbl->Compare(pIStr, Word, "*") == 0 ||
                                     pIStr->pVTbl->Compare(pIStr, Word, ".") == 0) {
                                char_t escaped[3] = {'\\', 0, 0};
                                escaped[1] = Word[0];
                                pIRules->pVTbl->AddRuleRE(pIRules, 0, escaped, currentId);
                                pIRules->pVTbl->SetPriority(pIRules, currentId, 10);
                            } else {
                                pIRules->pVTbl->AddRuleRE(pIRules, 0, Word, currentId);
                                pIRules->pVTbl->SetPriority(pIRules, currentId, 10);
                            }
                            isAdded[currentId] = 1; 
                            if (currentId > lastId) lastId = currentId;
                        }
                    }
                }
            }
        }

        lastId++;

        pIRules->pVTbl->AddRuleRE(pIRules, 0, "( |\t|\r|\n)+", lastId);
        pIRules->pVTbl->SetPriority(pIRules, lastId, 100);
        pIRules->pVTbl->SetChannel(pIRules, lastId, 1);
        pILog->pVTbl->Info(pILog, "Rules added");

        result = pIRules->pVTbl->Compile(pIRules, &pIData);
        if (result != 0) {
            pILog->pVTbl->InfoFormat(pILog, "Compile failed with code %d", result);
            return 0;
        } else {
            pILog->pVTbl->Info(pILog, "Compile successed");
        }
    }
    return pIData;
}

IEcoBNF1* GetTestBNF(IEcoLog1* pILog, IEcoBNF1* pIBNF) {
    IEcoBNF1Rule* pIRule = 0;
    uint32_t iSet = 0;

	pIRule = pIBNF->pVTbl->AddRule(pIBNF, "start");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "intf");

    /* 1. intf */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "intf"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "interface");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ":");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "}");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "interface");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "{");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "}");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");

    /* 2. methods */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "methods"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "methods");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "method");
	iSet = 0;
	pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "method");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_EPSILON, "epsilon");

    /* 3. method */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "method"); 
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "(");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "params");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ")");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ";");

    /* 4. params */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "params");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "params_list");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_EPSILON, "epsilon");

    /* 5. params_list */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "params_list");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "params_list");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, ",");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "param");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "param");

    /* 6. param */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "param");
	iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "attr");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "]");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "attr");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "]");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "*");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "[");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "attr");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "]");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");
    iSet = 0;
    pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_NONE, "base_type");
    pIRule->pVTbl->AddConcatenation(pIRule, iSet, ECO_BNF_1_EF_TERMINAL, "id");

    /* 7. attr */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "attr");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "in");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "out");

    /* 8. base_type */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "base_type");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "int16_t");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "char_t");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "voidptr_t");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "void");
    iSet = 0; pIRule->pVTbl->AddAlternative(pIRule, &iSet, ECO_BNF_1_EF_TERMINAL, "uint32_t");

    return pIBNF;
}

bool_t OutputDiagnosticInfoOfBNF(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoBNF1* pGrammar) {
    bool_t bResult = 0;
    IEcoBNF1Rule* pIRule = 0;
    IEcoBNF1Element* pIElement = 0;
    IEcoList1* pIAlphabet = 0;
    IEcoList1* pIRules = 0;
    IEcoList1* pIRuleSet = 0;
    IEcoList1* pIElements = 0;
    char_t* word = 0;
    char_t* Rule = 0;
    uint32_t index = 0;
    uint32_t indexSet = 0;
    uint32_t indexElement = 0;
    
    if (pGrammar != 0) {
        pILog->pVTbl->InfoFormat(pILog, "*** GRAMMAR ***");
        pILog->pVTbl->InfoFormat(pILog, "Alphabet :");
        pIAlphabet = pGrammar->pVTbl->get_Alphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t *)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }
        pILog->pVTbl->InfoFormat(pILog, "NonTerminal :");
        pIAlphabet = pGrammar->pVTbl->get_NonTerminalAlphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t *)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }
        pILog->pVTbl->InfoFormat(pILog, "Terminal :");
        pIAlphabet = pGrammar->pVTbl->get_TerminalAlphabet(pGrammar);
        for (index = 0; index < pIAlphabet->pVTbl->Count(pIAlphabet); index++) {
            word = (char_t *)pIAlphabet->pVTbl->Item(pIAlphabet, index);
            pILog->pVTbl->InfoFormat(pILog, "%i %s,", index, word);
        }
        
        pIRules = pGrammar->pVTbl->get_RuleList(pGrammar);
        for (index = 0; index < pIRules->pVTbl->Count(pIRules); index++) {
            pIRule = (IEcoBNF1Rule*)pIRules->pVTbl->Item(pIRules, index);
            Rule = pIStr->pVTbl->Append(pIStr, Rule, (char_t *)pIRule->pVTbl->get_Name(pIRule));
            pIRuleSet = pIRule->pVTbl->get_RuleSet(pIRule);
            for (indexSet = 0; indexSet < pIRuleSet->pVTbl->Count(pIRuleSet); indexSet++) {
                pIElements = (IEcoList1*)pIRuleSet->pVTbl->Item(pIRuleSet, indexSet);
                if (indexSet == 0) {
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, ":\r\n\t");
                }
                else {
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, "\r\n\t");
                }
                for (indexElement = 0; indexElement < pIElements->pVTbl->Count(pIElements); indexElement++) {
                    pIElement = (IEcoBNF1Element*)pIElements->pVTbl->Item(pIElements, indexElement);
                    if (pIElement == 0) {
                        Rule = pIStr->pVTbl->Append(pIStr, Rule, "epsilon ");
                        continue;
                    }
                    if (pIElement->pVTbl->CheckFlag(pIElement, ECO_BNF_1_EF_OPTIONAL)) {
                        Rule = pIStr->pVTbl->Append(pIStr, Rule, "[");
                    }
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, (char_t *)pIElement->pVTbl->get_Name(pIElement));
                    if (pIElement->pVTbl->CheckFlag(pIElement, ECO_BNF_1_EF_OPTIONAL)) {
                        Rule = pIStr->pVTbl->Append(pIStr, Rule, "]");
                    }
                    Rule = pIStr->pVTbl->Append(pIStr, Rule, " ");
                }
            }
            pILog->pVTbl->InfoFormat(pILog, "Rule [%d]\r\n%s", pIRule->pVTbl->get_Id(pIRule), Rule);
        }
            pIStr->pVTbl->Free(pIStr, Rule);
            Rule = 0;
        bResult = 1;
    }
    return bResult;
}

bool_t OutputDiagnosticInfoOfAST(/* in */ IEcoSystem1* pISys, /* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoAST1* pIAST) {
    IEcoVisitor1* pIVisitor = 0;
    IEcoASTPrintVisitor* pIPrintVisitor = 0;
    IEcoVisitor1Element* pIElement = 0;

	pILog->pVTbl->Info(pILog, "Final AST");

    createCEcoASTPrintVisitor((IEcoUnknown*)pISys, 0, &pIPrintVisitor);
    pIPrintVisitor->pVTbl->set_Logger(pIPrintVisitor, pILog);

    if (pIPrintVisitor->pVTbl->QueryInterface(pIPrintVisitor, &IID_IEcoVisitor1, (void **)&pIVisitor) == 0) {
        if (pIAST->pVTbl->QueryInterface(pIAST, &IID_IEcoVisitor1Element, (void **)&pIElement) == 0) {
            pIElement->pVTbl->Visit(pIElement, pIVisitor);
            pIElement->pVTbl->Release(pIElement);
        }
        pIVisitor->pVTbl->Release(pIVisitor);
    }
    pIPrintVisitor->pVTbl->Release(pIPrintVisitor);

    return 1;
}

bool_t OutputDiagnosticInfoOfParser(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoParser1LRk* pILRk) {
    IEcoMap2* pIFirstMap = 0;
    IEcoMap2* pIFollowMap = 0;
    IEcoBNF1* pIGrammar = 0;
    IEcoList1* pINonTerminals = 0;
    IEcoList1* pIItemSets = 0;
    IEcoSet2* pISet = 0;
    IEcoContainer1* pIContainer = 0;
    IEcoContainer1Iterator* pIIter = 0;
    char_t* ntName = 0;
    char_t* symName = 0;
    char_t* line = 0;
    uint32_t i = 0;

    if (pILRk == 0 || pILog == 0) return 0;

    pILog->pVTbl->Info(pILog, "*** PARSER LR(k) ***");
    pIGrammar = pILRk->pVTbl->get_Grammar(pILRk);
    pINonTerminals = pIGrammar->pVTbl->get_NonTerminalAlphabet(pIGrammar);

    pILog->pVTbl->Info(pILog, "FIRST Sets:");
    pIFirstMap = pILRk->pVTbl->get_First(pILRk);
    for (i = 0; i < pINonTerminals->pVTbl->Count(pINonTerminals); i++) {
        ntName = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, i);
        pISet = (IEcoSet2*)pIFirstMap->pVTbl->Get(pIFirstMap, ntName);
        if (pISet) {
            pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
            line = pIStr->pVTbl->Append(pIStr, 0, "  FIRST(");
            line = pIStr->pVTbl->Append(pIStr, line, ntName);
            line = pIStr->pVTbl->Append(pIStr, line, ") = { ");
            pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
            if (pIIter) {
                while (pIIter->pVTbl->Value(pIIter)) {
                    symName = (char_t*)pIIter->pVTbl->Value(pIIter);
                    line = pIStr->pVTbl->Append(pIStr, line, symName);
                    pIIter->pVTbl->Next(pIIter);
                    if (pIIter->pVTbl->Value(pIIter)) line = pIStr->pVTbl->Append(pIStr, line, ", ");
                }
                pIIter->pVTbl->Release(pIIter);
            }
            line = pIStr->pVTbl->Append(pIStr, line, " }");
            pILog->pVTbl->Info(pILog, line);
            pIStr->pVTbl->Free(pIStr, line);
        }
    }

    pILog->pVTbl->Info(pILog, "FOLLOW Sets:");
    pIFollowMap = pILRk->pVTbl->get_Follow(pILRk);
    for (i = 0; i < pINonTerminals->pVTbl->Count(pINonTerminals); i++) {
        ntName = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, i);
        pISet = (IEcoSet2*)pIFollowMap->pVTbl->Get(pIFollowMap, ntName);
        if (pISet) {
            pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
            line = pIStr->pVTbl->Append(pIStr, 0, "  FOLLOW(");
            line = pIStr->pVTbl->Append(pIStr, line, ntName);
            line = pIStr->pVTbl->Append(pIStr, line, ") = { ");
            pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
            if (pIIter) {
                while (pIIter->pVTbl->Value(pIIter)) {
                    symName = (char_t*)pIIter->pVTbl->Value(pIIter);
                    line = pIStr->pVTbl->Append(pIStr, line, symName);
                    pIIter->pVTbl->Next(pIIter);
                    if (pIIter->pVTbl->Value(pIIter)) line = pIStr->pVTbl->Append(pIStr, line, ", ");
                }
                pIIter->pVTbl->Release(pIIter);
            }
            line = pIStr->pVTbl->Append(pIStr, line, " }");
            pILog->pVTbl->Info(pILog, line);
            pIStr->pVTbl->Free(pIStr, line);
        }
    }

    pILog->pVTbl->Info(pILog, "Item Sets (States):");
    pIItemSets = pILRk->pVTbl->get_ItemSets(pILRk);
    if (pIItemSets) {
        for (i = 0; i < pIItemSets->pVTbl->Count(pIItemSets); i++) {
            pISet = (IEcoSet2*)pIItemSets->pVTbl->Item(pIItemSets, i);
            pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
            pILog->pVTbl->InfoFormat(pILog, "  State %d:", i);
            pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
            if (pIIter) {
                while (pIIter->pVTbl->Value(pIIter)) {
                    IEcoParser1LRkItem* pItem = (IEcoParser1LRkItem*)pIIter->pVTbl->Value(pIIter);
                    char_t* desc = pItem->pVTbl->get_Description(pItem);
                    pILog->pVTbl->InfoFormat(pILog, "    %s", desc);
                    pIIter->pVTbl->Next(pIIter);
                }
                pIIter->pVTbl->Release(pIIter);
            }
        }
    }

    pILog->pVTbl->Info(pILog, "********************");
    return 1;
}

bool_t OutputDiagnosticInfoOfFSM(/* in */ IEcoLog1* pILog, /* in */ IEcoString1* pIStr, /* in */ IEcoParser1LRk* pILRk) {
    IEcoBNF1* pIGrammar = 0;
    IEcoList1* pITerminals = 0;
    IEcoList1* pINonTerminals = 0;
    IEcoList1* pIItemSets = 0;
    uint32_t numStates = 0;
    uint32_t i = 0, j = 0;
    char_t* symName = 0;
    int32_t actionValue = 0;

    if (pILRk == 0 || pILog == 0) return 0;

    /* 1. Извлекаем необходимые данные через интерфейсы */
    pIGrammar = pILRk->pVTbl->get_Grammar(pILRk);
    pITerminals = pIGrammar->pVTbl->get_TerminalAlphabet(pIGrammar);
    pINonTerminals = pIGrammar->pVTbl->get_NonTerminalAlphabet(pIGrammar);
    pIItemSets = pILRk->pVTbl->get_ItemSets(pILRk);
    numStates = pIItemSets->pVTbl->Count(pIItemSets);

    pILog->pVTbl->Info(pILog, "*** GOTO/ACTION TABLE (FSM) ***");
    pILog->pVTbl->Info(pILog, "  Source   |   Symbol       |   Target   |  Action ");
    pILog->pVTbl->Info(pILog, "-----------+----------------+------------+----------");

    /* 2. Проход по всем состояниям (строкам таблицы) */
    for (i = 0; i < numStates; i++) {
        
        /* 2.1. Проверяем действия по Терминалам (ACTION) */
        for (j = 0; j < pITerminals->pVTbl->Count(pITerminals); j++) {
            symName = (char_t*)pITerminals->pVTbl->Item(pITerminals, j);
            actionValue = pILRk->pVTbl->get_Action(pILRk, i, symName);

            if (actionValue != 0) { /* 0 - это Error, пропускаем для чистоты лога */
                if (actionValue == 0x7FFFFFFF) {
                    /* ACCEPT */
                    pILog->pVTbl->InfoFormat(pILog, "  State %-3u | %-14s |            | [ ACCEPT ]", i, symName);
                } else if (actionValue > 0) {
                    /* SHIFT */
                    pILog->pVTbl->InfoFormat(pILog, "  State %-3u | %-14s | State %-3d | SHIFT", i, symName, actionValue);
                } else {
                    /* REDUCE (отрицательное значение) */
                    pILog->pVTbl->InfoFormat(pILog, "  State %-3u | %-14s | Rule %-5d | REDUCE", i, symName, -actionValue);
                }
            }
        }

        /* 2.2. Проверяем переходы по Нетерминалам (GOTO) */
        for (j = 0; j < pINonTerminals->pVTbl->Count(pINonTerminals); j++) {
            symName = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, j);
            actionValue = pILRk->pVTbl->get_Goto(pILRk, i, symName);

            if (actionValue != -1) { /* -1 - перехода нет */
                pILog->pVTbl->InfoFormat(pILog, "  State %-3u | %-14s | State %-3d | GOTO", i, symName, actionValue);
            }
        }
    }

    pILog->pVTbl->Info(pILog, "-----------+----------------+------------+----------");
    return 1;
}