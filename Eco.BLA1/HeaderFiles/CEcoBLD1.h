/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLD1
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBLD1 component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_BASIC_LEXICAL_DATA_1_H__
#define __I_ECO_BASIC_LEXICAL_DATA_1_H__

#include "IEcoLexicalData1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoBLD1_F82A88F6* CEcoBLD1_F82A88F6Ptr_t;

typedef struct CEcoBLD1_F82A88F6 {

    /* IEcoLexicalData1 interface function table */
    IEcoLexicalData1VTbl* m_pVTblIData;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBLD1_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBLD1_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBLD1_F82A88F6Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

	/* поля для сжатой таблицы лексического анализатора */
    uint32_t m_flags;
    uint32_t m_initialState;
    uint32_t m_version;
    uint16_t m_alphabetClassesCount;
    uint16_t* m_pGlobalAlphabetMap;
    uint16_t m_stateClassesCount;
    uint16_t* m_pStateClassMap; 
    uint32_t m_totalStatesCount;
    int32_t* m_pTransitionMatrix;
    EcoLexicalStateClassInfo* m_pStateClassInfoArray;

} CEcoBLD1_F82A88F6;

extern CEcoBLD1_F82A88F6 g_xCEcoBLD1_F82A88F6;

#endif /* __I_ECO_BASIC_LEXICAL_DATA_1_H__ */
