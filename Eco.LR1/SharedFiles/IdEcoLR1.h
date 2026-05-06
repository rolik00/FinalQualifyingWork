/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoLR1
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoLR1
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

#ifndef __ID_ECO_LR_1_H__
#define __ID_ECO_LR_1_H__

#include "IEcoBase1.h"
#include "IEcoParser1LRk.h"

/* EcoLR1 CID = {F4561FD2-15A3-4CC5-BA1D-8791A441A18E} */
#ifndef __CID_EcoLR1
static const UGUID CID_EcoLR1 = {0x01, 0x10, {0xF4, 0x56, 0x1F, 0xD2, 0x15, 0xA3, 0x4C, 0xC5, 0xBA, 0x1D, 0x87, 0x91, 0xA4, 0x41, 0xA1, 0x8E}};
#endif /* __CID_EcoLR1 */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_F4561FD215A34CC5BA1D8791A441A18E;
#endif

#endif /* __ID_ECO_LR_1_H__ */

