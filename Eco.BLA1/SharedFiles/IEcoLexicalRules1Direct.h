/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLexicalRules1Direct
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLexicalRules1Direct
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

#ifndef __I_ECO_LEXICAL_RULES_1_DIRECT_H__
#define __I_ECO_LEXICAL_RULES_1_DIRECT_H__

#include "IEcoBase1.h"
#include "IEcoLexicalRules1RE.h" /* Для общих типов MatchInfo и Action */

/**
 * Функция должна проанализировать буфер и вернуть ID найденного токена.
 * Если токен не опознан, функция ОБЯЗАНА вернуть 0.
 */
typedef uint32_t (ECOCALLMETHOD *EcoLexicalDirectMatch_t)(
    /* in */ voidptr_t pUnkContext,      /* Пользовательские данные (контекст правила) */
    /* in */ voidptr_t buffer,           /* Текущее смещение в данных сканера */
    /* in */ uint32_t size,              /* Доступное количество байт в буфере */
    /* out */ uint32_t* consumedBytes    /* Сколько байт поглощено этим токеном */
);

/* Информация о правиле Direct для инспекции */
typedef struct EcoLexicalRuleDirectInfo {
    uint32_t tokenId;      /* Идентификатор токена */
    char_t* stateName;     /* Имя лексерного состояния (NULL для INITIAL) */
    uint32_t priority;     /* Приоритет (порядок вызова функции в списке) */
    uint32_t channelId;    /* Канал токена */
    voidptr_t pContext;    /* Указатель на контекст функции */
} EcoLexicalRuleDirectInfo;



/* IEcoLexicalRules1Direct IID = {558CA8B2-7C1A-4681-97DD-183120865764} */
#ifndef __IID_IEcoLexicalRules1Direct
static const UGUID IID_IEcoLexicalRules1Direct = {0x01, 0x10, {0x55, 0x8C, 0xA8, 0xB2, 0x7C, 0x1A, 0x46, 0x81, 0x97, 0xDD, 0x18, 0x31, 0x20, 0x86, 0x57, 0x64}};
#endif /* __IID_IEcoLexicalRules1Direct */

typedef struct IEcoLexicalRules1Direct* IEcoLexicalRules1DirectPtr_t;

typedef struct IEcoLexicalRules1DirectVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLexicalRules1DirectPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLexicalRules1DirectPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLexicalRules1DirectPtr_t me);

    /* IEcoLexicalRules1Direct */
    /* --- Управление Лексерными Состояниями --- */
    
    int16_t (ECOCALLMETHOD *AddState)(IEcoLexicalRules1DirectPtr_t me, char_t* name, bool_t isExclusive);
    uint32_t (ECOCALLMETHOD *get_StatesCount)(IEcoLexicalRules1DirectPtr_t me);
    char_t* (ECOCALLMETHOD *get_StateName)(IEcoLexicalRules1DirectPtr_t me, uint32_t index);

    /* --- Регистрация пользовательских функций (Direct Rules) --- */

    /* Добавление правила в виде Си-функции. 
       tokenId здесь выступает как ID по умолчанию, если функция не вернет другой. */
    int16_t (ECOCALLMETHOD *AddRuleFunc)(
        IEcoLexicalRules1DirectPtr_t me, 
        char_t* stateName, 
        EcoLexicalDirectMatch_t pfnMatch, 
        voidptr_t pContext, 
        uint32_t tokenId
    );

    /* Настройка атрибутов */
    int16_t (ECOCALLMETHOD *SetPriority)(IEcoLexicalRules1DirectPtr_t me, uint32_t tokenId, uint32_t priority);
    int16_t (ECOCALLMETHOD *SetChannel)(IEcoLexicalRules1DirectPtr_t me, uint32_t tokenId, uint32_t channelId);
    
    /* Дополнительный Action (выполняется ПОСЛЕ того, как pfnMatch вернула успех) */
    int16_t (ECOCALLMETHOD *SetAction)(IEcoLexicalRules1DirectPtr_t me, uint32_t tokenId, EcoLexicalAction_t pfnAction, voidptr_t pActionContext);

    /* --- Инспекция (Геттеры) --- */

    uint32_t (ECOCALLMETHOD *get_Count)(IEcoLexicalRules1DirectPtr_t me);
    int16_t (ECOCALLMETHOD *GetRuleInfo)(IEcoLexicalRules1DirectPtr_t me, uint32_t index, EcoLexicalRuleDirectInfo* pInfo);

    /* --- Обработка Ошибок (Default Behavior) --- */

    int16_t (ECOCALLMETHOD *SetDefaultTokenId)(IEcoLexicalRules1DirectPtr_t me, char_t* stateName, uint32_t tokenId);
    int16_t (ECOCALLMETHOD *SetDefaultAction)(IEcoLexicalRules1DirectPtr_t me, char_t* stateName, EcoLexicalAction_t pfnAction, voidptr_t pContext);

    /* --- Операции --- */

    /* Упорядочивает функции по приоритетам для эффективного последовательного вызова */
    int16_t (ECOCALLMETHOD *Compile)(IEcoLexicalRules1DirectPtr_t me);

    int16_t (ECOCALLMETHOD *RemoveRule)(IEcoLexicalRules1DirectPtr_t me, uint32_t tokenId);
    int16_t (ECOCALLMETHOD *Clear)(IEcoLexicalRules1DirectPtr_t me);


} IEcoLexicalRules1DirectVTbl, *IEcoLexicalRules1DirectVTblPtr_t;

interface IEcoLexicalRules1Direct {
    struct IEcoLexicalRules1DirectVTbl *pVTbl;
} IEcoLexicalRules1Direct;


#endif /* __I_ECO_LEXICAL_RULES_1_DIRECT_H__ */

