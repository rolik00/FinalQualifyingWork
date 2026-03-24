/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLexicalAnalyzer1Token
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLexicalAnalyzer1Token
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

#ifndef __I_ECO_LEXICAL_ANALYZER_1_TOKEN_H__
#define __I_ECO_LEXICAL_ANALYZER_1_TOKEN_H__

#include "IEcoBase1.h"

/* IEcoLexicalAnalyzer1Token IID = {E119E477-D766-4E4B-8945-92C16187740E} */
#ifndef __IID_IEcoLexicalAnalyzer1Token
static const UGUID IID_IEcoLexicalAnalyzer1Token = {0x01, 0x10, {0xE1, 0x19, 0xE4, 0x77, 0xD7, 0x66, 0x4E, 0x4B, 0x89, 0x45, 0x92, 0xC1, 0x61, 0x87, 0x74, 0x0E}};
#endif /* __IID_IEcoLexicalAnalyzer1Token */

typedef struct IEcoLexicalAnalyzer1Token* IEcoLexicalAnalyzer1TokenPtr_t;

typedef struct IEcoLexicalAnalyzer1TokenVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLexicalAnalyzer1TokenPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLexicalAnalyzer1TokenPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLexicalAnalyzer1TokenPtr_t me);

    /* IEcoLexicalAnalyzer1Token */

    /* Тип (ID) токена, определенный в правилах (RE/BNF/FSM/Direct) */
    uint32_t (ECOCALLMETHOD *get_Type)(IEcoLexicalAnalyzer1TokenPtr_t me);

    /* Текстовое представление (лексема) */
    char_t* (ECOCALLMETHOD *get_Lexeme)(IEcoLexicalAnalyzer1TokenPtr_t me);
    uint16_t (ECOCALLMETHOD *get_Length)(IEcoLexicalAnalyzer1TokenPtr_t me);

    /* --- Координаты и Навигация --- */

    /* Порядковый номер токена в общем потоке (0-based) */
    uint32_t (ECOCALLMETHOD *get_TokenIndex)(IEcoLexicalAnalyzer1TokenPtr_t me);

    /* Позиция в источнике (строка, колонка, смещение) */
    uint32_t (ECOCALLMETHOD *get_Line)(IEcoLexicalAnalyzer1TokenPtr_t me);
    uint32_t (ECOCALLMETHOD *get_Column)(IEcoLexicalAnalyzer1TokenPtr_t me);
    uint64_t (ECOCALLMETHOD *get_Position)(IEcoLexicalAnalyzer1TokenPtr_t me);
    char_t* (ECOCALLMETHOD *get_Source)(IEcoLexicalAnalyzer1TokenPtr_t me); /* Имя файла/ресурса */

    /* --- Каналы и Состояния --- */

    /* Канал токена (0 - Default, 1 - Hidden/Comments и т.д.) */
    uint32_t (ECOCALLMETHOD *get_Channel)(IEcoLexicalAnalyzer1TokenPtr_t me);

    /* Имя лексерного состояния, в котором был порожден токен */
    char_t* (ECOCALLMETHOD *get_LexerState)(IEcoLexicalAnalyzer1TokenPtr_t me);

    /* --- Пользовательские данные и типизация --- */

    /* Пользовательский тег (например, для раскраски синтаксиса) */
    void (ECOCALLMETHOD *set_Tag)(IEcoLexicalAnalyzer1TokenPtr_t me, char_t* tag);
    char_t* (ECOCALLMETHOD *get_Tag)(IEcoLexicalAnalyzer1TokenPtr_t me);

    /* Типизированное значение (например, вычисленный int или double из Action) */
    void (ECOCALLMETHOD *set_Value)(IEcoLexicalAnalyzer1TokenPtr_t me, voidptr_t value);
    voidptr_t (ECOCALLMETHOD *get_Value)(IEcoLexicalAnalyzer1TokenPtr_t me);

    /* Описание токена из правил (для вывода ошибок пользователю) */
    char_t* (ECOCALLMETHOD *get_Description)(IEcoLexicalAnalyzer1TokenPtr_t me);

    /* --- Специальные флаги --- */
    bool_t (ECOCALLMETHOD *IsEOF)(IEcoLexicalAnalyzer1TokenPtr_t me);
    bool_t (ECOCALLMETHOD *IsError)(IEcoLexicalAnalyzer1TokenPtr_t me);


} IEcoLexicalAnalyzer1TokenVTbl, *IEcoLexicalAnalyzer1TokenVTblPtr_t;

interface IEcoLexicalAnalyzer1Token {
    struct IEcoLexicalAnalyzer1TokenVTbl *pVTbl;
} IEcoLexicalAnalyzer1Token;


#endif /* __I_ECO_LEXICAL_ANALYZER_1_TOKEN_H__ */

