/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoBRE1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoBRE1
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

#ifndef __ID_ECO_BRE_1_H__
#define __ID_ECO_BRE_1_H__

#include "IEcoBase1.h"
#include "IEcoBRE1.h"

/* EcoBRE1 CID = {755D526A-EBF9-43E9-B4AA-4F860E0B7D40} */
#ifndef __CID_EcoBRE1
static const UGUID CID_EcoBRE1 = {0x01, 0x10, {0x75, 0x5D, 0x52, 0x6A, 0xEB, 0xF9, 0x43, 0xE9, 0xB4, 0xAA, 0x4F, 0x86, 0x0E, 0x0B, 0x7D, 0x40}};
#endif /* __CID_EcoBRE1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_755D526AEBF943E9B4AA4F860E0B7D40;
#endif

#endif /* __ID_ECO_BRE_1_H__ */
