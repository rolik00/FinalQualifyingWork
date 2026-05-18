/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoASTPrintVisitor
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейсов IEcoASTPrintVisitor
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_AST_PRINT_VISITOR_H__
#define __I_ECO_AST_PRINT_VISITOR_H__

#include "IEcoBase1.h"
#include "IEcoLog1.h"

/* IEcoASTPrintVisitor IID = {9DC461F5-30AA-4CE6-A373-4BB7CECF06AA} */
#ifndef __IID_IEcoASTPrintVisitor
static const UGUID IID_IEcoASTPrintVisitor= {0x01, 0x10, 0x9D, 0xC4, 0x61, 0xF5, 0x30, 0xAA, 0x4C, 0xE6, 0xA3, 0x73, 0x4B, 0xB7, 0xCE, 0xCF, 0x06, 0xAA};
#endif /* __IID_IEcoASTPrintVisitor */


typedef struct IEcoASTPrintVisitorVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface )(/* in */ struct IEcoASTPrintVisitor* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef )(/* in */ struct IEcoASTPrintVisitor* me);
    uint32_t (*Release )(/* in */ struct IEcoASTPrintVisitor* me);

    /* IEcoASTPrintVisitor1 */
    void (*set_Logger)(/* in */ struct IEcoASTPrintVisitor* me, /* in */ IEcoLog1* pILog);

} IEcoASTPrintVisitorVTbl, *IEcoASTPrintVisitorVTblPtr;

interface IEcoASTPrintVisitor {
    struct IEcoASTPrintVisitorVTbl *pVTbl;
} IEcoASTPrintVisitor;

#endif /* __I_ECO_AST_PRINT_VISITOR_H__ */
