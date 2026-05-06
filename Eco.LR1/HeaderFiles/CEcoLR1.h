/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLR1_A441A18E
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoLR1_A441A18E component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_LR_1_H__
#define __C_ECO_LR_1_H__

#include "IEcoParser1LRk.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoBNF1.h"
#include "IdEcoPDA1.h"
#include "IdEcoString1.h"
#include "IdEcoMap2.h"
#include "IdEcoSet2.h"
#include "IdEcoList1.h"
#include "IdEcoQueue1.h"
#include "IdEcoComparator1.h"

typedef struct CEcoLR1_A441A18E* CEcoLR1_A441A18EPtr_t;

typedef struct CEcoLR1_A441A18E {

    /* IEcoParser1LRk interface function table */
    IEcoParser1LRkVTbl* m_pVTblILRk;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLR1_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLR1_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLR1_A441A18EPtr_t pCMe);

    int16_t (ECOCALLMETHOD *BuildFL1Alphabet)(/*in*/ CEcoLR1_A441A18EPtr_t pCMe);
    int16_t (ECOCALLMETHOD *BuildFirst)(/*in*/ CEcoLR1_A441A18EPtr_t pCMe);
    int16_t (ECOCALLMETHOD *BuildFollow)(/*in*/ CEcoLR1_A441A18EPtr_t pCMe);
    int16_t (ECOCALLMETHOD *BuildItemSets)(/*in*/ CEcoLR1_A441A18EPtr_t pCMe);
    int16_t (ECOCALLMETHOD *ConfigurePDAOperations)(/*in*/ CEcoLR1_A441A18EPtr_t  pCMe);

    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;
    /* Системный интерфейс */
    IEcoInterfaceBus1* m_pIBus;

    /* Интерфейс для работы со строкой */
    IEcoString1* m_pIStr;

    /* Instance data */
    IEcoBNF1* m_pIExtGrammar;
    int8_t m_nLookahead;
    IEcoPDA1* m_pIPDA;
    IEcoMap2* m_pIFirst;
    IEcoMap2* m_pIFollow;
    IEcoMap2* m_pSymbolMap;
    IEcoList1* m_pIItemSets;
    IEcoList1* m_pIClosureList;
    IEcoMap2* m_pIItemSetIdxMap;
    IEcoList1* m_pIGoTo;
    IEcoComparator1* m_pIItemComparator;

} CEcoLR1_A441A18E;

#endif /* __C_ECO_LR_1_H__ */
