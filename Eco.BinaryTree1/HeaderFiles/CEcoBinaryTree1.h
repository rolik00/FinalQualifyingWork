/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBinaryTree1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoBinaryTree1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_BINARY_TREE_1_H__
#define __C_ECO_BINARY_TREE_1_H__

#include "IEcoBinaryTree1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"

typedef struct CEcoBinaryTree1_AF1C3D6C* CEcoBinaryTree1_AF1C3D6CPtr_t;

typedef struct CEcoBinaryTree1_AF1C3D6C {

    /* Таблица функций интерфейса IEcoBinaryTree1 */
    IEcoBinaryTree1VTbl* m_pVTblIEcoBinaryTree1;

    /* Инициализация экземпляра */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBinaryTree1_AF1C3D6CPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Создание экземпляра */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBinaryTree1_AF1C3D6CPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Удаление */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBinaryTree1_AF1C3D6CPtr_t pCMe);

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Интерфейс для работы со строкой */
    IEcoString1* m_pIString;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;
    IEcoBinaryTree1Node* m_pRoot;

} CEcoBinaryTree1_AF1C3D6C;

#endif /* __C_ECO_BINARY_TREE_1_H__ */
