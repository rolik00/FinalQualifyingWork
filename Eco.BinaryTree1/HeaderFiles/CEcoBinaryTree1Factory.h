/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBinaryTree1Factory
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию фабрики для компонента
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_BINARY_TREE_1_FACTORY_H__
#define __C_ECO_BINARY_TREE_1_FACTORY_H__

#include "IEcoSystem1.h"

typedef struct CEcoBinaryTree1_AF1C3D6CFactory {

    /* Таблица функций интерфейса IEcoComponentFactory */
    IEcoComponentFactoryVTbl* m_pVTblICF;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Данные компонентов для фабрики */
    char_t m_Name[64];
    char_t m_Version[16];
    char_t m_Manufacturer[64];

} CEcoBinaryTree1_AF1C3D6CFactory;

#endif /* __C_ECO_BINARY_TREE_1_FACTORY_H__ */
