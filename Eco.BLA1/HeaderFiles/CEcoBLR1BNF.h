/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLR1BNF
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBLR1BNF component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_BASIC_LEXICAL_RULES_1_BNF_H__
#define __I_ECO_BASIC_LEXICAL_RULES_1_BNF_H__

#include "IEcoLexicalRules1BNF.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoBLR1BNF_F82A88F6* CEcoBLR1BNF_F82A88F6Ptr_t;

typedef struct CEcoBLR1BNF_F82A88F6 {

    /* IEcoLexicalRules1BNF interface function table */
    IEcoLexicalRules1BNFVTbl* m_pVTblIRules;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBLR1BNF_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBLR1BNF_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBLR1BNF_F82A88F6Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

} CEcoBLR1BNF_F82A88F6;

#endif /* __I_ECO_BASIC_LEXICAL_RULES_1_BNF_H__ */
