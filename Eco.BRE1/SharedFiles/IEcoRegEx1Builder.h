/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IEcoRegEx1Builder
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoRegEx1Builder
 * </description>
 *
 * <reference>
 *
 * </reference>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_REG_EX_1_BUILDER_H__
#define __I_ECO_REG_EX_1_BUILDER_H__

#include "IEcoBase1.h"
#include "IEcoRegEx1.h"
#include "IEcoBinaryTree1.h"

/* IEcoRegEx1Builder IID = {38E665D3-C7B9-4BD0-9854-0E96A232BF40} */
#ifndef __IID_IEcoRegEx1Builder
static const UGUID IID_IEcoRegEx1Builder = {0x01, 0x10, {0x38, 0xE6, 0x65, 0xD3, 0xC7, 0xB9, 0x4B, 0xD0, 0x98, 0x54, 0x0E, 0x96, 0xA2, 0x32, 0xBF, 0x40}};
#endif /* __IID_IEcoRegEx1Builder */

/* Типы узлов */
typedef enum EcoRegEx1NodeType {
    ECO_REGEX_NODE_UNDEFINED = 0,
    ECO_REGEX_NODE_LITERAL,
    ECO_REGEX_NODE_ANYCHAR,     // .
    ECO_REGEX_NODE_RANGE,       // a-z
    ECO_REGEX_NODE_CONCAT,
    ECO_REGEX_NODE_ALTERNATION, // |
    ECO_REGEX_NODE_QUANTIFIER,  // *, +, ?, {n,m}
    ECO_REGEX_NODE_GROUP        // ()
} EcoRegEx1NodeType;

/* Данные конкретных типов узлов */
typedef struct EcoRegEx1NodeData {
    uint32_t type;  /* Тип узла (всегда первый) */
    uint32_t flags; /* Флаги узла */
    union {
        /* Для ECO_REGEX_NODE_LITERAL */
        struct {
            uint32_t codePoint;  /* Символ в формате Unicode (совместим с ASCII) */
        } literal;

        /* Для ECO_REGEX_NODE_RANGE (например, [a-z]) */
        struct {
            uint32_t start;
            uint32_t end;
        } range;

        /* Для ECO_REGEX_NODE_QUANTIFIER (*, +, ?, {n,m}) */
        struct {
            uint32_t min;
            uint32_t max;        /* Например, 0xFFFFFFFF для бесконечности */
            bool_t isGreedy;     /* Жадный или ленивый квантификатор */
        } quantifier;

        /* Для ECO_REGEX_NODE_GROUP */
        struct {
            uint32_t index;      /* Индекс группы захвата */
            char_t* name;        /* Имя группы (для именованных групп) */
        } group;

    } data;
} EcoRegEx1NodeData;

typedef struct IEcoRegEx1Builder* IEcoRegEx1BuilderPtr_t;

typedef struct IEcoRegEx1BuilderVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoRegEx1BuilderPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoRegEx1BuilderPtr_t me);

    /* IEcoRegEx1Builder */

    /* IEcoRegEx1Builder: Листья (Терминалы) */
    
    /* Поддержка Unicode через uint32_t (Code Point) */
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateLiteral)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ uint32_t c);
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateAnyChar)(/* in */ IEcoRegEx1BuilderPtr_t me); /* '.' */
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateRange)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ uint32_t start, /* in */ uint32_t end);

    /* IEcoRegEx1Builder: Бинарные операции */
    
    /* Сцепление (A followed by B) */
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateConcat)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ IEcoBinaryTree1NodePtr_t left, /* in */ IEcoBinaryTree1NodePtr_t right);
    /* Альтернатива (A | B) */
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateAlternation)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ IEcoBinaryTree1NodePtr_t left, /* in */ IEcoBinaryTree1NodePtr_t right);

    /* IEcoRegEx1Builder: Унарные операции (Квантификаторы) */
    
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateStar)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ IEcoBinaryTree1NodePtr_t child);     /* '*' */
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreatePlus)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ IEcoBinaryTree1NodePtr_t child);     /* '+' */
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateOptional)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ IEcoBinaryTree1NodePtr_t child); /* '?' */
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateRepeat)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ IEcoBinaryTree1NodePtr_t child, /* in */ uint32_t min, /* in */ uint32_t max);

    /* IEcoRegEx1Builder: Группировка */
    
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *CreateGroup)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ IEcoBinaryTree1NodePtr_t child, /* in */ uint32_t index);

    /* Превращает корень дерева в готовый объект RegEx */
    int16_t (ECOCALLMETHOD *Build)(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ IEcoBinaryTree1NodePtr_t root, /* out */ IEcoRegEx1Ptr_t* ppIRegex);


} IEcoRegEx1BuilderVTbl, *IEcoRegEx1BuilderVTblPtr_t;

interface IEcoRegEx1Builder {
    struct IEcoRegEx1BuilderVTbl *pVTbl;
} IEcoRegEx1Builder;


#endif /* __I_ECO_REG_EX_1_BUILDER_H__ */

