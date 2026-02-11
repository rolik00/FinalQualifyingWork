/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoBRE1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoBRE1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_BRE_1_H__
#define __I_ECO_BRE_1_H__

#include "IEcoBase1.h"
#include "IEcoRegEx1.h"
#include "IEcoRegEx1Builder.h"

/* IEcoBRE1 IID = {25F98342-4A72-4CBB-B270-A4BF6468C8A8} */
#ifndef __IID_IEcoBRE1
static const UGUID IID_IEcoBRE1 = {0x01, 0x10, {0x25, 0xF9, 0x83, 0x42, 0x4A, 0x72, 0x4C, 0xBB, 0xB2, 0x70, 0xA4, 0xBF, 0x64, 0x68, 0xC8, 0xA8}};
#endif /* __IID_IEcoBRE1 */

typedef struct IEcoBRE1* IEcoBRE1Ptr_t;

typedef struct IEcoBRE1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoBRE1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoBRE1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoBRE1Ptr_t me);

    /* IEcoBRE1 */
 
    /* Создание скомпилированного объекта RegEx из строки шаблона */
    int16_t (ECOCALLMETHOD *CreateRegEx)(
        /* in */ IEcoBRE1Ptr_t me, 
        /* in */ voidptr_t pattern,        /* Поддержка ASCII/UTF-8/UTF-16 */
        /* in */ uint32_t patSizeInBytes, 
        /* in */ uint32_t flags,           /* Кодировка шаблона и опции компиляции */
        /* out */ IEcoRegEx1Ptr_t* ppIRegex
    );

    /* Получение билдера для ручного построения дерева разбора (AST) */
    int16_t (ECOCALLMETHOD *CreateBuilder)(
        /* in */ IEcoBRE1Ptr_t me, 
        /* out */ struct IEcoRegEx1Builder** ppIBuilder
    );
} IEcoBRE1VTbl, *IEcoBRE1VTblPtr_t;

interface IEcoBRE1 {
    struct IEcoBRE1VTbl *pVTbl;
} IEcoBRE1;

#endif /* __I_ECO_BRE_1_H__ */
