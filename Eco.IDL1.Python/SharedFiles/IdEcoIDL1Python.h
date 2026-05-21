/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoIDL1Python
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoIDL1Python
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

#ifndef __ID_ECO_IDL_1_PYTHON_H__
#define __ID_ECO_IDL_1_PYTHON_H__

#include "IEcoBase1.h"
#include "IEcoIDL1Emitter.h"

/* EcoIDL1Python CID = {4F8058F3-13B3-46A8-87D5-9E582C7799FC} */
#ifndef __CID_EcoIDL1Python
static const UGUID CID_EcoIDL1Python = {0x01, 0x10, {0x4F, 0x80, 0x58, 0xF3, 0x13, 0xB3, 0x46, 0xA8, 0x87, 0xD5, 0x9E, 0x58, 0x2C, 0x77, 0x99, 0xFC}};
#endif /* __CID_EcoIDL1Python */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_4F8058F313B346A887D59E582C7799FC;
#endif

#endif /* __ID_ECO_IDL_1_PYTHON_H__ */

