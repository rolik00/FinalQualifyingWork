/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLexicalRules1RE
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLexicalRules1RE
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

#ifndef __I_ECO_LEXICAL_RULES_1_RE_H__
#define __I_ECO_LEXICAL_RULES_1_RE_H__

#include "IEcoBase1.h"
#include "IEcoRegEx1.h"
#include "IEcoLexicalData1.h"

/* --- Структуры данных для обработки совпадений --- */

typedef struct EcoLexicalMatchInfo {
    voidptr_t buffer;      /* Указатель на начало найденного фрагмента текста */
    uint32_t length;       /* Длина фрагмента в байтах */
    uint32_t line;         /* Номер строки (1-based) */
    uint32_t column;       /* Номер колонки (1-based) */
    uint64_t position;     /* Абсолютное смещение в байтах от начала потока */
} EcoLexicalMatchInfo;

/* Тип функции-обработчика (Action). Возвращает итоговый Token ID. */
typedef uint32_t (ECOCALLMETHOD *EcoLexicalAction_t)(
    /* in */ voidptr_t pUnkContext, 
    /* in */ EcoLexicalMatchInfo* pMatch
);

/* Информация о правиле для инспекции (Геттеров) */
typedef struct EcoLexicalRuleREInfo {
    uint32_t tokenId;      /* Идентификатор токена */
    char_t* stateName;     /* Имя лексерного состояния (NULL для INITIAL) */
    uint32_t priority;     /* Приоритет разрешения конфликтов (выше - важнее) */
    uint32_t channelId;    /* Канал токена (0 - Default, 1 - Hidden) */
    bool_t hasAction;      /* Наличие привязанного callback-обработчика */
} EcoLexicalRuleREInfo;


/* IEcoLexicalRules1RE IID = {D3974ACC-EAAB-4273-A1F0-E97557E7B138} */
#ifndef __IID_IEcoLexicalRules1RE
static const UGUID IID_IEcoLexicalRules1RE = {0x01, 0x10, {0xD3, 0x97, 0x4A, 0xCC, 0xEA, 0xAB, 0x42, 0x73, 0xA1, 0xF0, 0xE9, 0x75, 0x57, 0xE7, 0xB1, 0x38}};
#endif /* __IID_IEcoLexicalRules1RE */

typedef struct IEcoLexicalRules1RE* IEcoLexicalRules1REPtr_t;

typedef struct IEcoLexicalRules1REVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLexicalRules1REPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLexicalRules1REPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLexicalRules1REPtr_t me);

    /* IEcoLexicalRules1RE */

    /* --- Управление Лексерными Состояниями (Контексты) --- */
    
    /* Добавить именованное состояние (напр. "STRING_MODE"). isExclusive=TRUE (аналог %x), FALSE (аналог %s) */
    int16_t (ECOCALLMETHOD *AddState)(IEcoLexicalRules1REPtr_t me, char_t* name, bool_t isExclusive);
    uint32_t (ECOCALLMETHOD *get_StatesCount)(IEcoLexicalRules1REPtr_t me);
    char_t* (ECOCALLMETHOD *get_StateName)(IEcoLexicalRules1REPtr_t me, uint32_t index);

    /* --- Добавление и Настройка Правил (RE) --- */

    /* Добавить правило через строку регулярного выражения */
    int16_t (ECOCALLMETHOD *AddRuleRE)(IEcoLexicalRules1REPtr_t me, char_t* stateName, char_t* pattern, uint32_t tokenId);
    
    /* Добавить правило через готовый объект регулярного выражения */
    int16_t (ECOCALLMETHOD *AddRuleObject)(IEcoLexicalRules1REPtr_t me, char_t* stateName, IEcoRegEx1Ptr_t pIRegEx, uint32_t tokenId);

    /* Настройка параметров токена */
    int16_t (ECOCALLMETHOD *SetPriority)(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, uint32_t priority);
    int16_t (ECOCALLMETHOD *SetChannel)(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, uint32_t channelId);
    
    /* Привязка Action (обработчика) к токену. Вызывается сканером при успешном Match. */
    int16_t (ECOCALLMETHOD *SetAction)(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, EcoLexicalAction_t pfnAction, voidptr_t pContext);

    /* --- Инспекция (Геттеры) --- */

    uint32_t (ECOCALLMETHOD *get_Count)(IEcoLexicalRules1REPtr_t me);
    int16_t (ECOCALLMETHOD *GetRuleInfo)(IEcoLexicalRules1REPtr_t me, uint32_t index, EcoLexicalRuleREInfo* pInfo);
    int16_t (ECOCALLMETHOD *GetRuleObject)(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, IEcoRegEx1Ptr_t* ppIRegEx);
    int16_t (ECOCALLMETHOD *GetAction)(IEcoLexicalRules1REPtr_t me, uint32_t tokenId, EcoLexicalAction_t* ppfnAction, voidptr_t* ppContext);

    /* --- Обработка Ошибок (Default Behavior) --- */

    /* Установка ID и Action для ситуации, когда ни одно правило в состоянии не подошло */
    int16_t (ECOCALLMETHOD *SetDefaultTokenId)(IEcoLexicalRules1REPtr_t me, char_t* stateName, uint32_t tokenId);
    int16_t (ECOCALLMETHOD *SetDefaultAction)(IEcoLexicalRules1REPtr_t me, char_t* stateName, EcoLexicalAction_t pfnAction, voidptr_t pContext);

    /* --- Операции --- */

    /* Удаление правила по его ID */
    int16_t (ECOCALLMETHOD *RemoveRule)(IEcoLexicalRules1REPtr_t me, uint32_t tokenId);
    /* Очистка всех правил и состояний */
    int16_t (ECOCALLMETHOD *Clear)(IEcoLexicalRules1REPtr_t me);

    /* ГЛАВНЫЙ МЕТОД: Компиляция правил в оптимизированную структуру таблиц (DFA) */
    int16_t (ECOCALLMETHOD *Compile)(IEcoLexicalRules1REPtr_t me, /* IEcoLexicalData1Ptr_t* */ void* ppIData);


} IEcoLexicalRules1REVTbl, *IEcoLexicalRules1REVTblPtr_t;

interface IEcoLexicalRules1RE {
    struct IEcoLexicalRules1REVTbl *pVTbl;
} IEcoLexicalRules1RE;


#endif /* __I_ECO_LEXICAL_RULES_1_RE_H__ */

