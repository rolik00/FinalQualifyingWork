/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLexicalRules1BNF
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLexicalRules1BNF
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

#ifndef __I_ECO_LEXICAL_RULES_1_BNF_H__
#define __I_ECO_LEXICAL_RULES_1_BNF_H__

#include "IEcoBase1.h"
#include "IEcoBNF1.h"
#include "IEcoLexicalData1.h"
#include "IEcoLexicalRules1RE.h" /* Для общих типов MatchInfo и Action */

/* Информация о правиле BNF для инспекции */
typedef struct EcoLexicalRuleBNFInfo {
    uint32_t tokenId;      /* Идентификатор токена */
    char_t* stateName;     /* Имя лексерного состояния (NULL для INITIAL) */
    uint32_t priority;     /* Приоритет разрешения конфликтов */
    uint32_t channelId;    /* Канал токена (0 - Default, 1 - Hidden) */
    bool_t isGreedy;       /* Жадный или ленивый поиск */
    bool_t hasAction;      /* Наличие привязанного callback-обработчика */
} EcoLexicalRuleBNFInfo;

/* IEcoLexicalRules1BNF IID = {4A71B410-41E7-4058-A8A5-1C154ACA5CAE} */
#ifndef __IID_IEcoLexicalRules1BNF
static const UGUID IID_IEcoLexicalRules1BNF = {0x01, 0x10, {0x4A, 0x71, 0xB4, 0x10, 0x41, 0xE7, 0x40, 0x58, 0xA8, 0xA5, 0x1C, 0x15, 0x4A, 0xCA, 0x5C, 0xAE}};
#endif /* __IID_IEcoLexicalRules1BNF */

typedef struct IEcoLexicalRules1BNF* IEcoLexicalRules1BNFPtr_t;

typedef struct IEcoLexicalRules1BNFVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLexicalRules1BNFPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLexicalRules1BNFPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLexicalRules1BNFPtr_t me);

    /* IEcoLexicalRules1BNF */

    /* --- Управление Лексерными Состояниями --- */
    
    int16_t (ECOCALLMETHOD *AddState)(IEcoLexicalRules1BNFPtr_t me, char_t* name, bool_t isExclusive);
    uint32_t (ECOCALLMETHOD *get_StatesCount)(IEcoLexicalRules1BNFPtr_t me);
    char_t* (ECOCALLMETHOD *get_StateName)(IEcoLexicalRules1BNFPtr_t me, uint32_t index);

    /* --- Добавление и Конфигурация BNF-правил --- */

    /* Привязка BNF-правила к TokenID. Правило должно быть праволинейным (регулярным). */
    int16_t (ECOCALLMETHOD *AddRuleBNF)(IEcoLexicalRules1BNFPtr_t me, char_t* stateName, IEcoBNF1RulePtr_t pIBNFRule, uint32_t tokenId);

    /* Исключение (Exclusion): Правило (tokenId) НЕ срабатывает, если текст подходит под pExceptRule */
    int16_t (ECOCALLMETHOD *AddException)(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, IEcoBNF1RulePtr_t pExceptRule);

    /* Предпросмотр (Lookahead): Правило сработает, только если впереди следует/не следует pFollowRule */
    int16_t (ECOCALLMETHOD *SetLookahead)(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, IEcoBNF1RulePtr_t pFollowRule, bool_t isNegative);

    /* Настройка атрибутов */
    int16_t (ECOCALLMETHOD *SetPriority)(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, uint32_t priority);
    int16_t (ECOCALLMETHOD *SetChannel)(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, uint32_t channelId);
    int16_t (ECOCALLMETHOD *SetGreedy)(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, bool_t isGreedy);
    
    /* Привязка Action-обработчика */
    int16_t (ECOCALLMETHOD *SetAction)(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, EcoLexicalAction_t pfnAction, voidptr_t pContext);

    /* --- Инспекция (Геттеры) --- */

    uint32_t (ECOCALLMETHOD *get_Count)(IEcoLexicalRules1BNFPtr_t me);
    int16_t (ECOCALLMETHOD *GetRuleInfo)(IEcoLexicalRules1BNFPtr_t me, uint32_t index, EcoLexicalRuleBNFInfo* pInfo);
    int16_t (ECOCALLMETHOD *GetRuleObject)(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId, IEcoBNF1RulePtr_t* ppIBNFRule);

    /* --- Обработка Ошибок (Default Behavior) --- */

    int16_t (ECOCALLMETHOD *SetDefaultTokenId)(IEcoLexicalRules1BNFPtr_t me, char_t* stateName, uint32_t tokenId);
    int16_t (ECOCALLMETHOD *SetDefaultAction)(IEcoLexicalRules1BNFPtr_t me, char_t* stateName, EcoLexicalAction_t pfnAction, voidptr_t pContext);

    /* --- Операции и Валидация --- */

    /* Проверка BNF-правил на соответствие регулярному типу (для построения DFA) */
    int16_t (ECOCALLMETHOD *Validate)(IEcoLexicalRules1BNFPtr_t me);

    /* Удаление правила */
    int16_t (ECOCALLMETHOD *RemoveRule)(IEcoLexicalRules1BNFPtr_t me, uint32_t tokenId);

    /* ГЛАВНЫЙ МЕТОД: Компиляция BNF в оптимизированную структуру таблиц (DFA) */
    int16_t (ECOCALLMETHOD *Compile)(IEcoLexicalRules1BNFPtr_t me, IEcoLexicalData1Ptr_t* ppIData);


} IEcoLexicalRules1BNFVTbl, *IEcoLexicalRules1BNFVTblPtr_t;

interface IEcoLexicalRules1BNF {
    struct IEcoLexicalRules1BNFVTbl *pVTbl;
} IEcoLexicalRules1BNF;


#endif /* __I_ECO_LEXICAL_RULES_1_BNF_H__ */

