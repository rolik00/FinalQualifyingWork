/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLA1Scanner
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBLA1Scanner component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_BASIC_LEXICAL_ANALYZER_1_SCANNER_H__
#define __I_ECO_BASIC_LEXICAL_ANALYZER_1_SCANNER_H__

#include "IEcoLexicalAnalyzer1Scanner.h"
#include "IEcoSystem1.h"
#include "IEcoFile1.h"
#include "IEcoLexicalData1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoBLA1Scanner_F82A88F6* CEcoBLA1Scanner_F82A88F6Ptr_t;

typedef struct CEcoBLA1Scanner_F82A88F6 {

    /* IEcoBLA1Scanner interface function table */
    IEcoLexicalAnalyzer1ScannerVTbl* m_pVTblIScanner;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBLA1Scanner_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBLA1Scanner_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBLA1Scanner_F82A88F6Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

	IEcoFile1* m_pIFile;             
    IEcoLexicalData1* m_pIData;       
    uint64_t m_filePos;                
    uint32_t m_line;                   
    uint32_t m_column;                 
    char* m_buffer;                   
    uint32_t m_bufferSize;             
    uint32_t m_bufferPos;              
    uint32_t m_bufferEnd;             
    uint32_t m_currentState;           
    uint32_t* m_stateStack;            
    int32_t m_stateStackSize;          
    int32_t m_stateStackTop;           
    uint32_t m_channelMask;

} CEcoBLA1Scanner_F82A88F6;

extern CEcoBLA1Scanner_F82A88F6 g_xCEcoBLA1Scanner_F82A88F6;

#endif /* __I_ECO_BASIC_LEXICAL_ANALYZER_1_SCANNER_H__ */
