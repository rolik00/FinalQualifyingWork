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

#ifndef __I_ECOBINARYTREE1_HPP__
#define __I_ECOBINARYTREE1_HPP__

#include "IEcoBase1.hpp"

/* IEcoBinaryTree1 IID = {CEFEBA6D-8A95-46EB-BE4C-1EE7F6195168} */
#ifndef __IID_IEcoBinaryTree1
static const UGUID IID_IEcoBinaryTree1 = {0x01, 0x10, {0xCE, 0xFE, 0xBA, 0x6D, 0x8A, 0x95, 0x46, 0xEB, 0xBE, 0x4C, 0x1E, 0xE7, 0xF6, 0x19, 0x51, 0x68}};
#endif /* __IID_IEcoBinaryTree1 */

interface IEcoBinaryTree1 : public IEcoUnknown {
public:
    /* IEcoBinaryTree1 */
    virtual IEcoBinaryTree1Node* ECOCALLMETHOD CreateNode(/* in */ voidptr_t data, /* in */ char_t* name) = 0;
    virtual IEcoBinaryTree1Node* ECOCALLMETHOD InsertNode(/* in */ IEcoBinaryTree1NodePtr_t parent, /* in */ IEcoBinaryTree1NodePtr_t child) = 0;
    virtual IEcoBinaryTree1Node* ECOCALLMETHOD InsertNodeByData(/* in */ IEcoBinaryTree1NodePtr_t parent, /* in */ voidptr_t data, /* in */ char_t* name) = 0;
    virtual int16_t ECOCALLMETHOD DeleteNode(/* in */ IEcoBinaryTree1NodePtr_t node) = 0;
    virtual int16_t ECOCALLMETHOD Clear() = 0;
};

#endif /* __I_ECOBINARYTREE1_HPP__ */
