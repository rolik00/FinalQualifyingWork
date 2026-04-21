/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoIDL1
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoIDL1
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

#ifndef __ID_ECOIDL1_H__
#define __ID_ECOIDL1_H__

#include "IEcoBase1.h"
#include "IEcoIDL1.h"

/* EcoIDL1 CID = {54F2EF99-5743-46E4-9122-AA7840BB8A88} */
#ifndef __CID_EcoIDL1
static const UGUID CID_EcoIDL1 = {0x01, 0x10, {0x54, 0xF2, 0xEF, 0x99, 0x57, 0x43, 0x46, 0xE4, 0x91, 0x22, 0xAA, 0x78, 0x40, 0xBB, 0x8A, 0x88}};
#endif /* __CID_EcoIDL1 */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_54F2EF99574346E49122AA7840BB8A88;
#endif

#endif /* __ID_ECOIDL1_H__ */

