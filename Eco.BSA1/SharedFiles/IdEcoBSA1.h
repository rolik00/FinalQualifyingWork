/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoBSA1
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoBSA1
 * </description>
 *
 * <reference>
 *
 * </reference>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __ID_ECO_BSA_1_H__
#define __ID_ECO_BSA_1_H__

#include "IEcoBase1.h"
#include "IEcoSyntaxAnalyzer1.h"

/* EcoBSA1 CID = {FF73C4B2-F8B0-4848-97DB-3298F6E9D8E1} */
#ifndef __CID_EcoBSA1
static const UGUID CID_EcoBSA1 = {0x01, 0x10, {0xFF, 0x73, 0xC4, 0xB2, 0xF8, 0xB0, 0x48, 0x48, 0x97, 0xDB, 0x32, 0x98, 0xF6, 0xE9, 0xD8, 0xE1}};
#endif /* __CID_EcoBSA1 */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_FF73C4B2F8B0484897DB3298F6E9D8E1;
#endif

#endif /* __ID_ECO_BSA_1_H__ */

