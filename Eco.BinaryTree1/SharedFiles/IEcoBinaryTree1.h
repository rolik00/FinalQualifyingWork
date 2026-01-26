/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoBinaryTree1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoBinaryTree1
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

#ifndef __I_ECO_BINARY_TREE_1_H__
#define __I_ECO_BINARY_TREE_1_H__

#include "IEcoBase1.h"
#include "IEcoList1.h"
#include "IEcoBinaryTree1Node.h"

/* IEcoBinaryTree1 IID = {CEFEBA6D-8A95-46EB-BE4C-1EE7F6195168} */
#ifndef __IID_IEcoBinaryTree1
static const UGUID IID_IEcoBinaryTree1 = {0x01, 0x10, {0xCE, 0xFE, 0xBA, 0x6D, 0x8A, 0x95, 0x46, 0xEB, 0xBE, 0x4C, 0x1E, 0xE7, 0xF6, 0x19, 0x51, 0x68}};
#endif /* __IID_IEcoBinaryTree1 */

typedef struct IEcoBinaryTree1* IEcoBinaryTree1Ptr_t;

typedef struct IEcoBinaryTree1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoBinaryTree1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoBinaryTree1Ptr_t me);

    /* IEcoBinaryTree1 */
    IEcoBinaryTree1Node* (ECOCALLMETHOD *CreateNode)(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ voidptr_t data, /* in */ char_t* name);
    IEcoBinaryTree1Node* (ECOCALLMETHOD *InsertNode)(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ IEcoBinaryTree1NodePtr_t parent, /* in */ IEcoBinaryTree1NodePtr_t child);
    IEcoBinaryTree1Node* (ECOCALLMETHOD *InsertNodeByData)(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ IEcoBinaryTree1NodePtr_t parent, /* in */ voidptr_t data, /* in */ char_t* name);
    int16_t (ECOCALLMETHOD *DeleteNode)(/* in */ IEcoBinaryTree1Ptr_t me, /* in */ IEcoBinaryTree1NodePtr_t node);
    int16_t (ECOCALLMETHOD *Clear)(/* in */ IEcoBinaryTree1Ptr_t me);

} IEcoBinaryTree1VTbl, *IEcoBinaryTree1VTblPtr_t;

interface IEcoBinaryTree1 {
    struct IEcoBinaryTree1VTbl *pVTbl;
} IEcoBinaryTree1;


#endif /* __I_ECO_BINARY_TREE_1_H__ */
