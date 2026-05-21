/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1PythonVisitor
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoIDL1PythonVisitor component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __C_ECO_IDL_1_PYTHON_VISITOR_H__
#define __C_ECO_IDL_1_PYTHON_VISITOR_H__

#include "IEcoVisitor1.h"
#include "IEcoAST1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoFile1.h"
#include "IdEcoString1.h"

typedef struct CEcoIDL1PythonVisitor_2C7799FC* CEcoIDL1PythonVisitor_2C7799FCPtr_t;

typedef struct CEcoIDL1PythonVisitor_2C7799FC {

    /* IEcoIDL1PythonVisitor interface function table */
    IEcoVisitor1VTbl* m_pVTblIVisitor;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoIDL1PythonVisitor_2C7799FCPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoFile1* pIFile);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoIDL1PythonVisitor_2C7799FCPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoIDL1PythonVisitor_2C7799FCPtr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* String interface */
    IEcoString1* m_pIStr;

    /* File interface */
    IEcoFile1* m_pIFile;

    /* Instance data */
    char_t* m_Name;

} CEcoIDL1PythonVisitor_2C7799FC;

#endif /* __C_ECO_IDL_1_PYTHON_VISITOR_H__ */
