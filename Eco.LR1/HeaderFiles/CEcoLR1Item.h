/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLR1Item
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoLR1Item component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_LR_1_ITEM_H__
#define __C_ECO_LR_1_ITEM_H__

#include "IEcoParser1LRkItem.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"
#include "IdEcoSet2.h"

typedef struct CEcoLR1Item_A441A18E* CEcoLR1Item_A441A18EPtr_t;

typedef struct CEcoLR1Item_A441A18E {

    /* IEcoLR1Item interface function table */
    IEcoParser1LRkItemVTbl* m_pVTblIItem;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoLR1Item_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoLR1Item_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoLR1Item_A441A18EPtr_t pCMe);

    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    IEcoString1* m_pIStr;

    /* Данные экземпляра */
    int32_t m_MarkerPosition;           /* Позиция маркера в пункте                           */
    int32_t m_RuleSetId;                /* Идентефикатор правила в наборе m_pIRule            */
    IEcoBNF1Rule* m_pIRule;             /* Правило (конкретнее: набор правил, см. грамматику) */
    char_t* m_Description;              /* Описание пункта                                    */
    IEcoSet2* m_pINextTerms;            /* Последующие терминалы                              */
    bool_t m_NeedUpdate;                /* Нужен ли обновить описание (в случае новых термов) */

} CEcoLR1Item_A441A18E;

#endif /* __C_ECO_LR_1_ITEM_H__ */
