/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1C_28028A01
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoIDL1C_28028A01 component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_IDL_1_C_H__
#define __C_ECO_IDL_1_C_H__

#include "IEcoIDL1Emitter.h"
#include "IEcoIDL1LangEmitter.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoVisitor1.h"

typedef struct CEcoIDL1C_28028A01* CEcoIDL1C_28028A01Ptr_t;

typedef struct CEcoIDL1C_28028A01 {

    /* IEcoIDL1C interface function table */
    IEcoIDL1EmitterVTbl* m_pVTblIEmitter;

    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoIDL1C_28028A01Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoIDL1C_28028A01Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoIDL1C_28028A01Ptr_t pCMe);

    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Визитор */
    IEcoVisitor1* m_pIVisitor;

    /* Интерфейс для работы с файлами */
    IEcoFileManager1* m_pIFileManager;
    IEcoFile1* m_pIFile;

    /* Instance data */
    char_t* m_Name;

} CEcoIDL1C_28028A01;

#endif /* __C_ECO_IDL_1_C_H__ */
