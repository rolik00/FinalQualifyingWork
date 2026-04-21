/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoIDL1Emitter
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoIDL1Emitter
 * </description>
 *
 * <reference>
 *
 * </reference>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_IDL_1_EMITTER_H__
#define __I_ECO_IDL_1_EMITTER_H__

#include "IEcoBase1.h"
#include "IEcoAST1.h"

/* IEcoIDL1Emitter IID = {882AD8D1-D9A4-4A00-A9C9-E144ACFA1E79} */
#ifndef __IID_IEcoIDL1Emitter
static const UGUID IID_IEcoIDL1Emitter = {0x01, 0x10, {0x88, 0x2A, 0xD8, 0xD1, 0xD9, 0xA4, 0x4A, 0x00, 0xA9, 0xC9, 0xE1, 0x44, 0xAC, 0xFA, 0x1E, 0x79}};
#endif /* __IID_IEcoIDL1Emitter */

typedef struct IEcoIDL1Emitter* IEcoIDL1EmitterPtr_t;

typedef struct IEcoIDL1EmitterVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoIDL1EmitterPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoIDL1EmitterPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoIDL1EmitterPtr_t me);

    /* IEcoIDL1Emitter */
 
    /* Получить идентификатор языка (например, "C", "CPP", "JAVA") */
    int16_t (ECOCALLMETHOD *GetIdentifier)(/* in */ IEcoIDL1EmitterPtr_t me, /* out */ char_t** langId);

    /* Герерация заголовочных файлов интерфейсов / описаний типов */
    int16_t (ECOCALLMETHOD *Emit)(/* in */ IEcoIDL1EmitterPtr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ char_t* outputPath);

} IEcoIDL1EmitterVTbl, *IEcoIDL1EmitterVTblPtr_t;

interface IEcoIDL1Emitter {
    struct IEcoIDL1EmitterVTbl *pVTbl;
} IEcoIDL1Emitter;


#endif /* __I_ECO_IDL_1_EMITTER_H__ */

