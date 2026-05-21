/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoIDL1Java
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoIDL1Java
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

#ifndef __ID_ECO_IDL_1_JAVA_H__
#define __ID_ECO_IDL_1_JAVA_H__

#include "IEcoBase1.h"
#include "IEcoIDL1Emitter.h"

/* EcoIDL1Java CID = {C26F52E0-372D-4051-A290-C1BD286DCE90} */
#ifndef __CID_EcoIDL1Java
static const UGUID CID_EcoIDL1Java = {0x01, 0x10, {0xC2, 0x6F, 0x52, 0xE0, 0x37, 0x2D, 0x40, 0x51, 0xA2, 0x90, 0xC1, 0xBD, 0x28, 0x6D, 0xCE, 0x90}};
#endif /* __CID_EcoIDL1Java */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_C26F52E0372D4051A290C1BD286DCE90;
#endif

#endif /* __ID_ECO_IDL_1_JAVA_H__ */

