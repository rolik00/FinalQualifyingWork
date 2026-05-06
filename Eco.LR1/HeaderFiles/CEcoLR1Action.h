/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLR1Action
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoLR1Action component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_LR_1_ACTION_H__
#define __C_ECO_LR_1_ACTION_H__

#include "IEcoParser1Action.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLR1Action_A441A18E* CEcoLR1Action_A441A18EPtr_t;

typedef struct CEcoLR1Action_A441A18E {

    /* IEcoLR1Action interface function table */
    IEcoParser1ActionVTbl* m_pVTblIAction;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLR1Action_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLR1Action_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLR1Action_A441A18EPtr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    int16_t m_Type;          /* SHIFT, REDUCE, ACCEPT */
    IEcoBNF1Rule* m_pRule;   /* Для REDUCE */
    uint16_t m_RuleSetId;    /* Для REDUCE */
    IEcoFSM1State* m_pState; /* Для SHIFT */

} CEcoLR1Action_A441A18E;

#endif /* __C_ECO_LR_1_ACTION_H__ */
