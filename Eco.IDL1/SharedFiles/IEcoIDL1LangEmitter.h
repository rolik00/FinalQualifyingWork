/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IEcoIDL1LangEmitter
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoIDL1LangEmitter
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

#ifndef __I_ECO_IDL_1_LANG_EMITTER_H__
#define __I_ECO_IDL_1_LANG_EMITTER_H__

#include "IEcoBase1.h"
#include "IEcoAST1.h"
#include "IEcoIDL1Emitter.h"

/* IEcoIDL1LangEmitter IID = {16F3F964-82B4-491A-92D4-17FDC783D977} */
#ifndef __IID_IEcoIDL1LangEmitter
static const UGUID IID_IEcoIDL1LangEmitter = {0x01, 0x10, {0x16, 0xF3, 0xF9, 0x64, 0x82, 0xB4, 0x49, 0x1A, 0x92, 0xD4, 0x17, 0xFD, 0xC7, 0x83, 0xD9, 0x77}};
#endif /* __IID_IEcoIDL1LangEmitter */

typedef struct IEcoIDL1LangEmitter* IEcoIDL1LangEmitterPtr_t;

typedef struct IEcoIDL1LangEmitterVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoIDL1LangEmitterPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoIDL1LangEmitterPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoIDL1LangEmitterPtr_t me);

    /* IEcoIDL1Emitter */

    /* Получить идентификатор языка (например, "C", "CPP", "JAVA") */
    int16_t (ECOCALLMETHOD *GetIdentifier)(/* in */ IEcoIDL1LangEmitterPtr_t me, /* out */ char_t** langId);
    int16_t (ECOCALLMETHOD *Emit)(/* in */ IEcoIDL1LangEmitterPtr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ char_t* outputPath);

    /* IEcoIDL1LangEmitter */

    /* Герерация файла с GUID компонента и интерфейсов */
    int16_t (ECOCALLMETHOD *EmitIdFile)(/* in */ IEcoIDL1LangEmitterPtr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ char_t* outputPath);

    /* Герерация кода для маршалинга (Proxy и Stub) */
    int16_t (ECOCALLMETHOD *EmitMarshalingCode)(/* in */ IEcoIDL1LangEmitterPtr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ char_t* outputPath);

    /* Герерация шаблона реализации (заготовки для разработчика) */
    int16_t (ECOCALLMETHOD *EmitTemplate)(/* in */ IEcoIDL1LangEmitterPtr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ char_t* outputPath);


} IEcoIDL1LangEmitterVTbl, *IEcoIDL1LangEmitterVTblPtr_t;

interface IEcoIDL1LangEmitter {
    struct IEcoIDL1LangEmitterVTbl *pVTbl;
} IEcoIDL1LangEmitter;


#endif /* __I_ECO_IDL_1_LANG_EMITTER_H__ */

