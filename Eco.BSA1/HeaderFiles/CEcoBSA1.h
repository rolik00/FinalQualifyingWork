/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBSA1_F6E9D8E1
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBSA1_F6E9D8E1 component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_BASIC_SYNTAX_ANALYZER_1_H__
#define __C_ECO_BASIC_SYNTAX_ANALYZER_1_H__

#include "IEcoSyntaxAnalyzer1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"
#include "IdEcoDictionary1.h"
#include "IEcoParser1LRk.h"

typedef struct CEcoBSA1_F6E9D8E1* CEcoBSA1_F6E9D8E1Ptr_t;

typedef struct CEcoBSA1_F6E9D8E1 {

    /* IEcoSyntaxAnalyzer1 interface function table */
    IEcoSyntaxAnalyzer1VTbl* m_pVTblISyntax;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBSA1_F6E9D8E1Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBSA1_F6E9D8E1Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBSA1_F6E9D8E1Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Интерфейс для работы со строкой */
    IEcoString1* m_pIStr;

    /* Данные экземпляра */
    IEcoDictionary1* m_Algorithms;
    char_t* m_AlgorithmName;

} CEcoBSA1_F6E9D8E1;

#endif /* __C_ECO_BASIC_SYNTAX_ANALYZER_1_H__ */
