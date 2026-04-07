/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLexicalData1
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLexicalData1
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

#ifndef __I_ECO_LEXICAL_DATA_1_H__
#define __I_ECO_LEXICAL_DATA_1_H__

#include "IEcoBase1.h"
#include "IEcoLexicalRules1RE.h" /* Для EcoLexicalAction_t и MatchInfo */

/* Флаги оптимизации данных */
#define ECO_LEX_DATA_FL_MULTI_ALPHABET   0x00000001  /* Каждое состояние лексера имеет свой ClassMap */
#define ECO_LEX_DATA_FL_STATE_CLASSES    0x00000002  /* Использование StateClassMap для сжатия строк матрицы */
#define ECO_LEX_DATA_FL_LITTLE_ENDIAN    0x00000004  /* Порядок байт в таблицах */

/* Структура описания поведения (финального состояния) */
typedef struct EcoLexicalStateClassInfo {
    uint32_t tokenId;      /* ID токена (0 если состояние не принимающее) */
    uint32_t channelId;    /* Канал токена (Default/Hidden) */
    bool_t isFinal;        /* Признак терминального состояния */
    //EcoLexicalAction_t pfnAction; /* Обработчик Си-кода */
    voidptr_t pContext;    /* Контекст для обработчика */
	uint32_t priority;
} EcoLexicalStateClassInfo;

/* IEcoLexicalData1 IID = {DB2E1637-58AA-4447-A843-545A8805D3FE} */
#ifndef __IID_IEcoLexicalData1
static const UGUID IID_IEcoLexicalData1 = {0x01, 0x10, {0xDB, 0x2E, 0x16, 0x37, 0x58, 0xAA, 0x44, 0x47, 0xA8, 0x43, 0x54, 0x5A, 0x88, 0x05, 0xD3, 0xFE}};
#endif /* __IID_IEcoLexicalData1 */

typedef struct IEcoLexicalData1* IEcoLexicalData1Ptr_t;

typedef struct IEcoLexicalData1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLexicalData1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLexicalData1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLexicalData1Ptr_t me);

    /* IEcoLexicalData1 */
    /* --- Свойства и метаданные --- */
    uint32_t (ECOCALLMETHOD *get_Flags)(IEcoLexicalData1Ptr_t me);
    uint32_t (ECOCALLMETHOD *get_InitialState)(IEcoLexicalData1Ptr_t me);
    uint32_t (ECOCALLMETHOD *get_Version)(IEcoLexicalData1Ptr_t me);

    /* --- ТАБЛИЦА 1: ALPHABET MAP (Символ -> Класс Символа) --- */
    
    /* Возвращает глобальный маппинг. Индекс - код символа. */
    uint16_t* (ECOCALLMETHOD *get_GlobalAlphabetMap)(IEcoLexicalData1Ptr_t me);
    
    /* Локальный маппинг для конкретного состояния лексера (если ECO_LEX_DATA_FL_MULTI_ALPHABET) */
    uint16_t* (ECOCALLMETHOD *get_AlphabetMapByLexerState)(IEcoLexicalData1Ptr_t me, char_t* lexerStateName);
    
    uint16_t (ECOCALLMETHOD *get_AlphabetClassesCount)(IEcoLexicalData1Ptr_t me, char_t* lexerStateName);

    /* --- ТАБЛИЦА 2: STATE CLASS MAP (Состояние -> Класс Состояния) --- */
    
    /* Маппинг индекса состояния в индекс его поведения (StateClassId) */
    uint16_t* (ECOCALLMETHOD *get_StateClassMap)(IEcoLexicalData1Ptr_t me);
    uint32_t (ECOCALLMETHOD *get_TotalStatesCount)(IEcoLexicalData1Ptr_t me);

    /* --- ТАБЛИЦА 3: TRANSITION MATRIX --- */
    
    /* Сжатая матрица переходов для конкретного режима работы лексера.
       Доступ: [StateClassId * AlphabetClassesCount + AlphabetClassId] */
    int32_t* (ECOCALLMETHOD *get_TransitionMatrix)(IEcoLexicalData1Ptr_t me, char_t* lexerStateName);
    uint16_t (ECOCALLMETHOD *get_StateClassesCount)(IEcoLexicalData1Ptr_t me);

    /* --- ТАБЛИЦА 4: BEHAVIOR (Класс Состояния -> Метаданные) --- */
    
    /* Получить tokenId и Action по ID класса состояния */
    int16_t (ECOCALLMETHOD *get_StateClassInfo)(IEcoLexicalData1Ptr_t me, uint16_t stateClassId, /* EcoLexicalStateClassInfo* */ void* pInfo);

    /* --- СЕРИАЛИЗАЦИЯ --- */
    
    /* Сохраняет все таблицы и метаданные в поток/файл */
    int16_t (ECOCALLMETHOD *Save)(IEcoLexicalData1Ptr_t me, char_t* fileName);
    /* Вычисляет CRC для проверки целостности данных */
    uint32_t (ECOCALLMETHOD *get_Checksum)(IEcoLexicalData1Ptr_t me);

} IEcoLexicalData1VTbl, *IEcoLexicalData1VTblPtr_t;

interface IEcoLexicalData1 {
    struct IEcoLexicalData1VTbl *pVTbl;
} IEcoLexicalData1;


#endif /* __I_ECO_LEXICAL_DATA_1_H__ */

