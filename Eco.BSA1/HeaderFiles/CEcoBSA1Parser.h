/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBSA1Parser
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBSA1Parser component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_BASIC_SYNTAX_ANALYZER_1_PARSER_H__
#define __C_ECO_BASIC_SYNTAX_ANALYZER_1_PARSER_H__

#include "IEcoSyntaxAnalyzer1Parser.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"
#include "IdEcoStack1.h"
#include "IdEcoList1.h"
#include "IEcoParser1LRk.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoSyntaxAnalyzer1Parser.h"
#include "IEcoTree1.h"
#include "IdEcoMap2.h"
#include "IdEcoInterfaceBus1.h"

typedef struct CEcoBSA1Parser_F6E9D8E1* CEcoBSA1Parser_F6E9D8E1Ptr_t;

typedef struct CEcoBSA1Parser_F6E9D8E1 {

    /* IEcoSyntaxAnalyzer1Parser interface function table */
    IEcoSyntaxAnalyzer1ParserVTbl* m_pVTblIParser;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBSA1Parser_F6E9D8E1Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /*in*/ IEcoParser1LRk* pIAlgorithm);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBSA1Parser_F6E9D8E1Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBSA1Parser_F6E9D8E1Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Интерфейс для работы с шиной */
    IEcoInterfaceBus1* m_pIBus;

    /* Интерфейс для работы со строкой */
    IEcoString1* m_pIStr;

    /* Интерфейс для работы с файлами */
    IEcoParser1LRk* m_pIAlgorithm;
    IEcoParser1ActionProcessing* m_pIProcessing;
    IEcoAST1* m_pIAST;
    IEcoLexicalAnalyzer1Token* m_pILatestToken;

    /* Массив ассоциативных правил для построения узлов дерева */
    IEcoMap2* m_pIRuleMappers;

    /* Разрешатель конфликтов */
    IEcoSyntaxAnalyzer1ConflictResolver* m_pIResolver;

    /* Другие вспомогательные интерфейсы */
    IEcoAST1GlobalScope* m_pIGlobalScope;
    IEcoAST1Scope* m_pIScope;
    IEcoTree1* m_pINotCheckedTokens;
    IEcoStack1* m_pIStack;
	IEcoAST1TranslationUnit* m_pTranslationUnit;
} CEcoBSA1Parser_F6E9D8E1;

#endif /* __C_ECO_BASIC_SYNTAX_ANALYZER_1_PARSER_H__ */
