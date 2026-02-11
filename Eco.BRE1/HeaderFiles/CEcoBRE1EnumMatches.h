/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBRE1EnumMatches
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBRE1EnumMatches component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_BRE_1_ENUM_MATCHES_H__
#define __C_ECO_BRE_1_ENUM_MATCHES_H__

#include "IEcoRegEx1EnumMatches.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoBRE1EnumMatches_0E0B7D40* CEcoBRE1EnumMatches_0E0B7D40Ptr_t;

typedef struct CEcoBRE1EnumMatches_0E0B7D40 {

    /* IEcoRegEx1EnumMatches interface function table */
    IEcoRegEx1EnumMatchesVTbl* m_pVTblIEcoRegEx1EnumMatches;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBRE1EnumMatches_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBRE1EnumMatches_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBRE1EnumMatches_0E0B7D40Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

} CEcoBRE1EnumMatches_0E0B7D40;

#endif /* __C_ECO_BRE_1_ENUM_MATCHES_H__ */
