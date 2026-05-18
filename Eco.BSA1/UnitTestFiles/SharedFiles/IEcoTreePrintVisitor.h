/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoTreePrintVisitor
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейсов IEcoTreePrintVisitor
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_TREE_PRINT_VISITOR_H__
#define __I_ECO_TREE_PRINT_VISITOR_H__

#include "IEcoBase1.h"
#include "IEcoLog1.h"

/* IEcoTreePrintVisitor IID = {9C23CF5D-08D2-49AA-9680-D48FCE750562} */
#ifndef __IID_IEcoTreePrintVisitor
static const UGUID IID_IEcoTreePrintVisitor= {0x01, 0x10, 0x9C, 0x23, 0xCF, 0x5D, 0x08, 0xD2, 0x49, 0xAA, 0x96, 0x80, 0xD4, 0x8F, 0xCE, 0x75, 0x05, 0x62 };
#endif /* __IID_IEcoTreePrintVisitor */

typedef struct IEcoTreePrintVisitorVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface )(/* in */ struct IEcoTreePrintVisitor* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef )(/* in */ struct IEcoTreePrintVisitor* me);
    uint32_t (*Release )(/* in */ struct IEcoTreePrintVisitor* me);

    /* IEcoTreePrintVisitor1 */
    void (*set_Logger)(/* in */ struct IEcoTreePrintVisitor* me, /* in */ IEcoLog1* pILog);

} IEcoTreePrintVisitorVTbl, *IEcoTreePrintVisitorVTblPtr;

interface IEcoTreePrintVisitor {
    struct IEcoTreePrintVisitorVTbl *pVTbl;
} IEcoTreePrintVisitor;

#endif /* __I_ECO_TREE_PRINT_VISITOR_H__ */
