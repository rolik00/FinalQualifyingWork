/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLR1ActionProcessing
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoLR1ActionProcessing component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_LR_1_ACTION_PROCESSING_H__
#define __C_ECO_LR_1_ACTION_PROCESSING_H__

#include "IEcoParser1ActionProcessing.h"
#include "IEcoSystem1.h"
#include "IEcoPDA1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLR1ActionProcessing_A441A18E* CEcoLR1ActionProcessing_A441A18EPtr_t;

typedef struct CEcoLR1ActionProcessing_A441A18E {

    /* IEcoParser1ActionProcessing interface function table */
    IEcoParser1ActionProcessingVTbl* m_pVTblIAP;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLR1ActionProcessing_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoPDA1EventProcessingPtr_t pPDAProcessing);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLR1ActionProcessing_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLR1ActionProcessing_A441A18EPtr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;
    IEcoInterfaceBus1* m_pIBus;

    /* Instance data */
    IEcoPDA1EventProcessing* m_pPDAProcessing;
    
    /* Состояние парсера */
    IEcoFSM1State* m_pCurrentState;
    int16_t m_LastStateType;

} CEcoLR1ActionProcessing_A441A18E;

#endif /* __C_ECO_LR_1_ACTION_PROCESSING_H__ */
