/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1_40BB8A88
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoIDL1_40BB8A88 component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_IDL_1_H__
#define __C_ECO_IDL_1_H__

#include "IEcoIDL1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"
#include "IdEcoBLA1.h"
#include "IdEcoBNF1.h"
#include "IdEcoBSA1.h"
#include "IdEcoAST1.h"

typedef struct CEcoIDL1_40BB8A88* CEcoIDL1_40BB8A88Ptr_t;

typedef struct CEcoIDL1EmitterConfig {
    UGUID cid;
    char_t langId[32];
} CEcoIDL1EmitterConfig_t;

typedef struct CEcoIDL1_40BB8A88 {

    /* IEcoIDL1 interface function table */
    IEcoIDL1VTbl* m_pVTblIIDL;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoIDL1_40BB8A88Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoIDL1_40BB8A88Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoIDL1_40BB8A88Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;
    IEcoInterfaceBus1* m_pIBus;
    IEcoString1* m_pIStr;

    /* Instance data */
    IEcoLexicalAnalyzer1* m_pILA;
    IEcoLexicalRules1REPtr_t m_pILexicalRules;
	IEcoLexicalData1* m_pIData;
    IEcoSyntaxAnalyzer1* m_pISA;
    IEcoBNF1* m_pISyntaxRules;
    IEcoAST1* m_pIAST;
    char_t* m_Name;

	/* ��������� ������������������ ��������� (Key-Value) */
    CEcoIDL1EmitterConfig_t m_Emitters[16];
    uint32_t m_cEmitters;

} CEcoIDL1_40BB8A88;

#endif /* __C_ECO_IDL_1_H__ */
