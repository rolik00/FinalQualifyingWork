/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLA1Token
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBLA1Token component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_BASIC_LEXICAL_ANALYZER_1_TOKEN_H__
#define __I_ECO_BASIC_LEXICAL_ANALYZER_1_TOKEN_H__

#include "IEcoLexicalAnalyzer1Token.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoBLA1Token_F82A88F6* CEcoBLA1Token_F82A88F6Ptr_t;

typedef struct CEcoBLA1Token_F82A88F6 {

    /* IEcoBLA1Token interface function table */
    IEcoLexicalAnalyzer1TokenVTbl* m_pVTblIToken;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBLA1Token_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBLA1Token_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBLA1Token_F82A88F6Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

	uint32_t m_type;                   
    char_t* m_lexeme;                  
    uint16_t m_length;                 
    uint32_t m_line;                   
    uint32_t m_column;                 
    uint64_t m_position;               
    uint32_t m_channel;                
    bool_t m_isEOF;                    
    bool_t m_isError; 

} CEcoBLA1Token_F82A88F6;

extern CEcoBLA1Token_F82A88F6 g_xCEcoBLA1Token_F82A88F6;

#endif /* __I_ECO_BASIC_LEXICAL_ANALYZER_1_TOKEN_H__ */
