/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLexicalRules1FSM
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLexicalRules1FSM
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

#ifndef __I_ECO_LEXICAL_RULES_1_FSM_H__
#define __I_ECO_LEXICAL_RULES_1_FSM_H__

#include "IEcoBase1.h"
#include "IEcoLexicalData1.h"
#include "IEcoLexicalRules1RE.h" /* Для общих типов MatchInfo и Action */
#include "IEcoFSM1.h" 

/* Информация о правиле FSM для инспекции */
typedef struct EcoLexicalRuleFSMInfo {
    uint32_t tokenId;      /* Идентификатор токена */
    char_t* stateName;     /* Имя лексерного состояния (NULL для INITIAL) */
    uint32_t priority;     /* Приоритет разрешения конфликтов */
    uint32_t channelId;    /* Канал токена (0 - Default, 1 - Hidden) */
    bool_t isDeterministic; /* Является ли исходный автомат детерминированным */
    bool_t hasAction;      /* Наличие привязанного callback-обработчика */
} EcoLexicalRuleFSMInfo;

/* IEcoLexicalRules1FSM IID = {F7275F99-2572-469B-A386-127B80FF82E2} */
#ifndef __IID_IEcoLexicalRules1FSM
static const UGUID IID_IEcoLexicalRules1FSM = {0x01, 0x10, {0xF7, 0x27, 0x5F, 0x99, 0x25, 0x72, 0x46, 0x9B, 0xA3, 0x86, 0x12, 0x7B, 0x80, 0xFF, 0x82, 0xE2}};
#endif /* __IID_IEcoLexicalRules1FSM */

typedef struct IEcoLexicalRules1FSM* IEcoLexicalRules1FSMPtr_t;

typedef struct IEcoLexicalRules1FSMVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLexicalRules1FSMPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLexicalRules1FSMPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLexicalRules1FSMPtr_t me);

    /* IEcoLexicalRules1FSM */

    /* --- Управление Лексерными Состояниями (Контексты) --- */
    
    int16_t (ECOCALLMETHOD *AddState)(IEcoLexicalRules1FSMPtr_t me, char_t* name, bool_t isExclusive);
    uint32_t (ECOCALLMETHOD *get_StatesCount)(IEcoLexicalRules1FSMPtr_t me);
    char_t* (ECOCALLMETHOD *get_StateName)(IEcoLexicalRules1FSMPtr_t me, uint32_t index);

    /* --- Добавление и Конфигурация FSM-правил --- */

    /* Добавление правила в виде готового конечного автомата.
       Компонент интегрирует структуру pIFSM в общий лексерный граф. */
    int16_t (ECOCALLMETHOD *AddRuleFSM)(IEcoLexicalRules1FSMPtr_t me, char_t* stateName, IEcoFSM1StateMachinePtr_t pIFSM, uint32_t tokenId);

    /* Настройка атрибутов токена */
    int16_t (ECOCALLMETHOD *SetPriority)(IEcoLexicalRules1FSMPtr_t me, uint32_t tokenId, uint32_t priority);
    int16_t (ECOCALLMETHOD *SetChannel)(IEcoLexicalRules1FSMPtr_t me, uint32_t tokenId, uint32_t channelId);
    
    /* Привязка Action-обработчика (выполняется при достижении финального состояния pIFSM) */
    int16_t (ECOCALLMETHOD *SetAction)(IEcoLexicalRules1FSMPtr_t me, uint32_t tokenId, EcoLexicalAction_t pfnAction, voidptr_t pContext);

    /* --- Инспекция (Геттеры) --- */

    uint32_t (ECOCALLMETHOD *get_Count)(IEcoLexicalRules1FSMPtr_t me);
    int16_t (ECOCALLMETHOD *GetRuleInfo)(IEcoLexicalRules1FSMPtr_t me, uint32_t index, EcoLexicalRuleFSMInfo* pInfo);
    int16_t (ECOCALLMETHOD *GetRuleObject)(IEcoLexicalRules1FSMPtr_t me, uint32_t tokenId, IEcoFSM1StateMachinePtr_t* ppIFSM);

    /* --- Обработка Ошибок (Default Behavior) --- */

    int16_t (ECOCALLMETHOD *SetDefaultTokenId)(IEcoLexicalRules1FSMPtr_t me, char_t* stateName, uint32_t tokenId);
    int16_t (ECOCALLMETHOD *SetDefaultAction)(IEcoLexicalRules1FSMPtr_t me, char_t* stateName, EcoLexicalAction_t pfnAction, voidptr_t pContext);

    /* --- Операции --- */

    /* Проверка автомата на детерминированность. Если IsDeterministic=FALSE, Compile выполнит NFA->DFA. */
    bool_t (ECOCALLMETHOD *IsDeterministic)(IEcoLexicalRules1FSMPtr_t me, uint32_t tokenId);

    /* Удаление правила */
    int16_t (ECOCALLMETHOD *RemoveRule)(IEcoLexicalRules1FSMPtr_t me, uint32_t tokenId);
    int16_t (ECOCALLMETHOD *Clear)(IEcoLexicalRules1FSMPtr_t me);

    /* ГЛАВНЫЙ МЕТОД: Компиляция всех FSM в оптимизированную структуру данных (DFA) */
    int16_t (ECOCALLMETHOD *Compile)(IEcoLexicalRules1FSMPtr_t me, IEcoLexicalData1Ptr_t* ppIData);


} IEcoLexicalRules1FSMVTbl, *IEcoLexicalRules1FSMVTblPtr_t;

interface IEcoLexicalRules1FSM {
    struct IEcoLexicalRules1FSMVTbl *pVTbl;
} IEcoLexicalRules1FSM;


#endif /* __I_ECO_LEXICAL_RULES_1_FSM_H__ */

