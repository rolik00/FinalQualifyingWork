/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLexicalAnalyzer1Scanner
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLexicalAnalyzer1Scanner
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

#ifndef __I_ECO_LEXICAL_ANALYZER_1_SCANNER_H__
#define __I_ECO_LEXICAL_ANALYZER_1_SCANNER_H__

#include "IEcoBase1.h"
#include "IEcoLexicalAnalyzer1Token.h"
#include "IEcoLexicalData1.h"

/* IEcoLexicalAnalyzer1Scanner IID = {D0A7FF25-3BEE-4A5B-936D-195420F8D08C} */
#ifndef __IID_IEcoLexicalAnalyzer1Scanner
static const UGUID IID_IEcoLexicalAnalyzer1Scanner = {0x01, 0x10, {0xD0, 0xA7, 0xFF, 0x25, 0x3B, 0xEE, 0x4A, 0x5B, 0x93, 0x6D, 0x19, 0x54, 0x20, 0xF8, 0xD0, 0x8C}};
#endif /* __IID_IEcoLexicalAnalyzer1Scanner */

typedef struct IEcoLexicalAnalyzer1Scanner* IEcoLexicalAnalyzer1ScannerPtr_t;

typedef struct IEcoLexicalAnalyzer1ScannerVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLexicalAnalyzer1ScannerPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLexicalAnalyzer1ScannerPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLexicalAnalyzer1ScannerPtr_t me);

    /* IEcoLexicalAnalyzer1Scanner */

    /* --- Основные операции сканирования --- */
    
    /* Извлечь следующий токен из активного канала. Сдвигает указатель чтения. */
    IEcoLexicalAnalyzer1TokenPtr_t (ECOCALLMETHOD *Scan)(IEcoLexicalAnalyzer1ScannerPtr_t me);
    /* Попытка восстановления после лексической ошибки (пропуск мусора до синхронизации) */
    int16_t (ECOCALLMETHOD *Recover)(IEcoLexicalAnalyzer1ScannerPtr_t me, IEcoLexicalAnalyzer1TokenPtr_t pIToken);

    /* Просмотр следующего токена без сдвига указателя (Lookahead 1) */
    IEcoLexicalAnalyzer1TokenPtr_t (ECOCALLMETHOD *Peek)(IEcoLexicalAnalyzer1ScannerPtr_t me);
    /* Заглядывание на N токенов вперед (Lookahead N) */
    IEcoLexicalAnalyzer1TokenPtr_t (ECOCALLMETHOD *LookAhead)(IEcoLexicalAnalyzer1ScannerPtr_t me, uint32_t n);


    /* --- Навигация (Positioning) --- */

    /* Получить текущее абсолютное смещение в байтах */
    uint64_t (ECOCALLMETHOD *get_Position)(IEcoLexicalAnalyzer1ScannerPtr_t me);
    /* Установить позицию чтения (для реализации Backtracking в парсерах) */
    int16_t (ECOCALLMETHOD *set_Position)(IEcoLexicalAnalyzer1ScannerPtr_t me, uint64_t position);

    /* --- Управление контекстными состояниями (Lexer Modes) --- */

    /* Вход в новое состояние (аналог BEGIN во flex). Сохраняет текущее в стек. */
    int16_t (ECOCALLMETHOD *PushState)(IEcoLexicalAnalyzer1ScannerPtr_t me, char_t* stateName);
    /* Возврат к предыдущему состоянию из стека */
    int16_t (ECOCALLMETHOD *PopState)(IEcoLexicalAnalyzer1ScannerPtr_t me);
    /* Получить имя текущего активного состояния */
    char_t* (ECOCALLMETHOD *get_CurrentState)(IEcoLexicalAnalyzer1ScannerPtr_t me);

    /* --- Каналы и Фильтрация (ANTLR-style) --- */

    /* Установка маски активных каналов (например, исключить Hidden канал с комментариями) */
    int16_t (ECOCALLMETHOD *SetChannelMask)(IEcoLexicalAnalyzer1ScannerPtr_t me, uint32_t mask);
    uint32_t (ECOCALLMETHOD *get_ChannelMask)(IEcoLexicalAnalyzer1ScannerPtr_t me);

    /* --- Инкрементальность (Tree-sitter style) --- */

    /* Уведомление о правке текста для частичного пересчета токенов в буфере */
    int16_t (ECOCALLMETHOD *NotifyEdit)(IEcoLexicalAnalyzer1ScannerPtr_t me, uint64_t startOffset, uint32_t oldLen, uint32_t newLen);

    /* --- Доступ к данным и диагностика --- */

    /* Получить объект данных (таблицы), на которых работает сканер */
    IEcoLexicalData1Ptr_t (ECOCALLMETHOD *get_LexicalData)(IEcoLexicalAnalyzer1ScannerPtr_t me);
    
    /* Текущие человекочитаемые координаты */
    uint32_t (ECOCALLMETHOD *get_CurrentLine)(IEcoLexicalAnalyzer1ScannerPtr_t me);
    uint32_t (ECOCALLMETHOD *get_CurrentColumn)(IEcoLexicalAnalyzer1ScannerPtr_t me);


} IEcoLexicalAnalyzer1ScannerVTbl, *IEcoLexicalAnalyzer1ScannerVTblPtr_t;

interface IEcoLexicalAnalyzer1Scanner {
    struct IEcoLexicalAnalyzer1ScannerVTbl *pVTbl;
} IEcoLexicalAnalyzer1Scanner;


#endif /* __I_ECO_LEXICAL_ANALYZER_1_SCANNER_H__ */

