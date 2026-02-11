/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBRE1Builder
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBRE1Builder component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_BRE_1_BUILDER_H__
#define __C_ECO_BRE_1_BUILDER_H__

#include "IEcoRegEx1Builder.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoBRE1Builder_0E0B7D40* CEcoBRE1Builder_0E0B7D40Ptr_t;

typedef struct CEcoBRE1Builder_0E0B7D40 {

    /* IEcoRegEx1Builder interface function table */
    IEcoRegEx1BuilderVTbl* m_pVTblIEcoRegEx1Builder;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBRE1Builder_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBRE1Builder_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBRE1Builder_0E0B7D40Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

	/* —сылка на компонент BinaryTree */
    IEcoBinaryTree1* m_pBinaryTree; 

} CEcoBRE1Builder_0E0B7D40;

#endif /* __C_ECO_BRE_1_BUILDER_H__ */
