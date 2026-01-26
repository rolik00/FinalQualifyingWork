/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoBinaryTree1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoBinaryTree1
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

#ifndef __ID_ECO_BINARY_TREE_1_H__
#define __ID_ECO_BINARY_TREE_1_H__

#include "IEcoBase1.h"
#include "IEcoBinaryTree1.h"

/* EcoBinaryTree1 CID = {7CAD4D02-15EF-4EDF-B1FF-6A7CAF1C3D6C} */
#ifndef __CID_EcoBinaryTree1
static const UGUID CID_EcoBinaryTree1 = {0x01, 0x10, {0x7C, 0xAD, 0x4D, 0x02, 0x15, 0xEF, 0x4E, 0xDF, 0xB1, 0xFF, 0x6A, 0x7C, 0xAF, 0x1C, 0x3D, 0x6C}};
#endif /* __CID_EcoBinaryTree1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_7CAD4D0215EF4EDFB1FF6A7CAF1C3D6C;
#endif

#endif /* __ID_ECO_BINARY_TREE_1_H__ */
