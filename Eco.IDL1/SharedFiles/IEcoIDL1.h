/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IEcoIDL1
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoIDL1
 * </description>
 *
 * <reference>
 *
 * </reference>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_IDL_1_H__
#define __I_ECO_IDL_1_H__

#include "IEcoBase1.h"
#include "IEcoAST1.h"
#include "IEcoIDL1Emitter.h"
#include "IEcoIDL1ProjectLayout.h"

/* IEcoIDL1 IID = {948C13ED-820E-4538-9E1E-BBDD9308A42C} */
#ifndef __IID_IEcoIDL1
static const UGUID IID_IEcoIDL1 = {0x01, 0x10, {0x94, 0x8C, 0x13, 0xED, 0x82, 0x0E, 0x45, 0x38, 0x9E, 0x1E, 0xBB, 0xDD, 0x93, 0x08, 0xA4, 0x2C}};
#endif /* __IID_IEcoIDL1 */

typedef struct IEcoIDL1* IEcoIDL1Ptr_t;

typedef struct IEcoIDL1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoIDL1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoIDL1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoIDL1Ptr_t me);

    /* IEcoIDL1 */

    /* 1. Парсинг и построение дерева (Frontend) */
    /* Инициализация внутреннего состояния перед парсингом */
    int16_t (ECOCALLMETHOD *Initialize)(/* in */ IEcoIDL1Ptr_t me);
    int16_t (ECOCALLMETHOD *Terminate)(/* in */ IEcoIDL1Ptr_t me);

    /* Управление грамматикой (Лексика и Синтаксис) */
    int16_t (ECOCALLMETHOD *GetLexicalRules)(/* in */ IEcoIDL1Ptr_t me, /* out */ voidptr_t* ppRules);
    int16_t (ECOCALLMETHOD *GetSyntaxRules)(/* in */ IEcoIDL1Ptr_t me, /* out */ voidptr_t* ppRules);

    /* Разбор файла и создание AST-дерева */
    int16_t (ECOCALLMETHOD *ParseFile)(/* in */ IEcoIDL1Ptr_t me, /* in */ char_t* filePath, /* out */ IEcoAST1Ptr_t* ppAST);

    /* 2. Управление эмиттерами (Backend) */
    /* Регистрация компонента-эмиттера по его CLSID и строковому имени языка (напр. "C", "Java") */
    int16_t (ECOCALLMETHOD *RegisterEmitter)(/* in */ IEcoIDL1Ptr_t me, /* in */ const UGUID* rcid, /* in */ char_t* langId);

    /*  Получение экземпляра эмиттера по его текстовому идентификатору */
    int16_t (ECOCALLMETHOD *GetEmitter)(/* in */ IEcoIDL1Ptr_t me, /* in */ char_t* langId, /* out */ IEcoIDL1Emitter** ppIEmitter);

    /* 3. Полная генерация всех файлов для указанного языка */
    /* pAST - дерево, langId - "C"/"Java", commonArgs - пути и настройки */
    int16_t (ECOCALLMETHOD *Generate)(/* in */ IEcoIDL1Ptr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ IEcoIDL1ProjectLayoutPtr_t pLayout, /* in */ char_t* langId, /* in */ void* commonArgs);

} IEcoIDL1VTbl, *IEcoIDL1VTblPtr_t;

interface IEcoIDL1 {
    struct IEcoIDL1VTbl *pVTbl;
} IEcoIDL1;


#endif /* __I_ECO_IDL_1_H__ */

