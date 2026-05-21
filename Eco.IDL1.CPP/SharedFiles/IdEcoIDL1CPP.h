/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoIDL1CPP
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoIDL1CPP
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

#ifndef __ID_ECO_IDL_1_CPP_H__
#define __ID_ECO_IDL_1_CPP_H__

#include "IEcoBase1.h"
#include "IEcoIDL1Emitter.h"

/* EcoIDL1CPP CID = {8F45C7FF-B814-4066-BEAF-F11296176293} */
#ifndef __CID_EcoIDL1CPP
static const UGUID CID_EcoIDL1CPP = {0x01, 0x10, {0x8F, 0x45, 0xC7, 0xFF, 0xB8, 0x14, 0x40, 0x66, 0xBE, 0xAF, 0xF1, 0x12, 0x96, 0x17, 0x62, 0x93}};
#endif /* __CID_EcoIDL1CPP */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_8F45C7FFB8144066BEAFF11296176293;
#endif

#endif /* __ID_ECO_IDL_1_CPP_H__ */

