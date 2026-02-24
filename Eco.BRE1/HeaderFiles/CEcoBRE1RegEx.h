/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBRE1RegEx
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBRE1RegEx component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_BRE_1_REG_EX_H__
#define __C_ECO_BRE_1_REG_EX_H__

#include "IEcoRegEx1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoBinaryTree1.h" 
#include "IEcoFSM1.h"

typedef struct CEcoBRE1RegEx_0E0B7D40* CEcoBRE1RegEx_0E0B7D40Ptr_t;

typedef struct CEcoBRE1RegEx_0E0B7D40 {

    /* IEcoRegEx1 interface function table */
    IEcoRegEx1VTbl* m_pVTblIEcoRegEx1;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBRE1RegEx_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBRE1RegEx_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoRegEx1Ptr_t* ppIRegex);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBRE1RegEx_0E0B7D40Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

    IEcoBinaryTree1Node* m_pRoot;

	IEcoFSM1* m_pFSM;  
	IEcoFSM1StateMachine* m_pStateMachine;
	IEcoFSM1State* m_pStartState;

} CEcoBRE1RegEx_0E0B7D40;

#endif /* __C_ECO_BRE_1_REG_EX_H__ */
