/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoIDL1C
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoIDL1C
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

#ifndef __ID_ECO_IDL_1_C_H__
#define __ID_ECO_IDL_1_C_H__

#include "IEcoBase1.h"
#include "IEcoIDL1Emitter.h"

/* EcoIDL1C CID = {E89F37B5-194F-4F4A-8ADE-1FFB28028A01} */
#ifndef __CID_EcoIDL1C
static const UGUID CID_EcoIDL1C = {0x01, 0x10, {0xE8, 0x9F, 0x37, 0xB5, 0x19, 0x4F, 0x4F, 0x4A, 0x8A, 0xDE, 0x1F, 0xFB, 0x28, 0x02, 0x8A, 0x01}};
#endif /* __CID_EcoIDL1C */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_E89F37B5194F4F4A8ADE1FFB28028A01;
#endif

#endif /* __ID_ECO_IDL_1_C_H__ */

