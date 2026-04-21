/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1ProjectLayout
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoIDL1ProjectLayout component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECOIDL1PROJECTLAYOUT_H__
#define __C_ECOIDL1PROJECTLAYOUT_H__

#include "IEcoIDL1ProjectLayout.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoIDL1ProjectLayout_40BB8A88* CEcoIDL1ProjectLayout_40BB8A88Ptr_t;

typedef struct CEcoIDL1ProjectLayout_40BB8A88 {

    /* IEcoIDL1ProjectLayout interface function table */
    IEcoIDL1ProjectLayoutVTbl* m_pVTblIEcoIDL1ProjectLayout;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoIDL1ProjectLayout_40BB8A88Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoIDL1ProjectLayout_40BB8A88Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoIDL1ProjectLayout_40BB8A88Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

} CEcoIDL1ProjectLayout_40BB8A88;

#endif /* __C_ECOIDL1PROJECTLAYOUT_H__ */
