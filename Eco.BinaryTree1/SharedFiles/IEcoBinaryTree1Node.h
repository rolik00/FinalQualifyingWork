/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoBinaryTree1Node
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoBinaryTree1Node
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

#ifndef __I_ECO_BINARY_TREE_1_NODE_H__
#define __I_ECO_BINARY_TREE_1_NODE_H__

#include "IEcoBase1.h"

/* IEcoBinaryTree1Node IID = {C77EFA7F-F12B-4852-969E-0A1508B62022} */
#ifndef __IID_IEcoBinaryTree1Node
static const UGUID IID_IEcoBinaryTree1Node = {0x01, 0x10, {0xC7, 0x7E, 0xFA, 0x7F, 0xF1, 0x2B, 0x48, 0x52, 0x96, 0x9E, 0x0A, 0x15, 0x08, 0xB6, 0x20, 0x22}};
#endif /* __IID_IEcoBinaryTree1Node */

typedef struct IEcoBinaryTree1Node* IEcoBinaryTree1NodePtr_t;

typedef struct IEcoBinaryTree1NodeVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoBinaryTree1NodePtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoBinaryTree1NodePtr_t me);

    /* IEcoBinaryTree1Node */
    voidptr_t (ECOCALLMETHOD *get_Data)(/* in */ IEcoBinaryTree1NodePtr_t me);
    void (ECOCALLMETHOD *set_Data)(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ voidptr_t value);
    char_t* (ECOCALLMETHOD *get_Name)(/* in */ IEcoBinaryTree1NodePtr_t me);
    void (ECOCALLMETHOD *set_Name)(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ char_t* value);
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *get_Parent)(/* in */ IEcoBinaryTree1NodePtr_t me);
    void (ECOCALLMETHOD *set_Parent)(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ IEcoBinaryTree1NodePtr_t parent);
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *get_Left)(/* in */ IEcoBinaryTree1NodePtr_t me);
    void (ECOCALLMETHOD *set_Left)(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ IEcoBinaryTree1NodePtr_t node);
    IEcoBinaryTree1NodePtr_t (ECOCALLMETHOD *get_Right)(/* in */ IEcoBinaryTree1NodePtr_t me);
    void (ECOCALLMETHOD *set_Right)(/* in */ IEcoBinaryTree1NodePtr_t me, /* in */ IEcoBinaryTree1NodePtr_t node);
    bool_t (ECOCALLMETHOD *IsRoot)(/* in */ IEcoBinaryTree1NodePtr_t me);
    bool_t (ECOCALLMETHOD *IsLeaf)(/* in */ IEcoBinaryTree1NodePtr_t me);

} IEcoBinaryTree1NodeVTbl;

interface IEcoBinaryTree1Node {
    struct IEcoBinaryTree1NodeVTbl *pVTbl;
} IEcoBinaryTree1Node;

#endif /* __I_ECO_BINARY_TREE_1_NODE_H__ */
