/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1Java_286DCE90
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoIDL1Java_286DCE90 component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_IDL_1_JAVA_H__
#define __C_ECO_IDL_1_JAVA_H__

#include "IEcoIDL1Emitter.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoVisitor1.h"

typedef struct CEcoIDL1Java_286DCE90* CEcoIDL1Java_286DCE90Ptr_t;

typedef struct CEcoIDL1Java_286DCE90 {

    /* IEcoIDL1Java interface function table */
    IEcoIDL1EmitterVTbl* m_pVTblIEmitter;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoIDL1Java_286DCE90Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoIDL1Java_286DCE90Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoIDL1Java_286DCE90Ptr_t pCMe);


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

} CEcoIDL1Java_286DCE90;

#endif /* __C_ECO_IDL_1_JAVA_H__ */
