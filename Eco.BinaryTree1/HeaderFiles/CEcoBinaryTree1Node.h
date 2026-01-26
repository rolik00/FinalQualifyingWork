/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBinaryTree1Node
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoBinaryTree1Node
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_BINARY_TREE_1_NODE_H__
#define __C_ECO_BINARY_TREE_1_NODE_H__

#include "IEcoBinaryTree1Node.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoBinaryTree1Node_AF1C3D6C* CEcoBinaryTree1Node_AF1C3D6CPtr_t;

typedef struct CEcoBinaryTree1Node_AF1C3D6C {

    /* Таблица функций интерфейса IEcoBinaryTree1Node */
    IEcoBinaryTree1NodeVTbl* m_pVTblIEcoBinaryTree1Node;

    /* Инициализация экземпляра */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBinaryTree1Node_AF1C3D6CPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Создание экземпляра */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBinaryTree1Node_AF1C3D6CPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Удаление */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBinaryTree1Node_AF1C3D6CPtr_t pCMe);

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    IEcoBinaryTree1Node* m_pILeft;      // Левый узел
    IEcoBinaryTree1Node* m_pIRight;     // Правый узел
    IEcoBinaryTree1Node* m_pIParent;    // Узел-родитель
    voidptr_t m_pData;                  // Указатель на данные
    char_t* m_pName;                    // Имя узла

} CEcoBinaryTree1Node_AF1C3D6C;

#endif /* __C_ECO_BINARY_TREE_1_NODE_H__ */
