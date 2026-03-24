/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoBLA1
 * </summary>
 *
 * <description>
 *   This header describes the interface IdEcoBLA1
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

#ifndef __ID_ECO_BASIC_LEXICAL_ANALYZER_1_H__
#define __ID_ECO_BASIC_LEXICAL_ANALYZER_1_H__

#include "IEcoBase1.h"
#include "IEcoLexicalAnalyzer1.h"

/* EcoBLA1 CID = {88DD9459-2E7C-48BA-B381-EAA0F82A88F6} */
#ifndef __CID_EcoBLA1
static const UGUID CID_EcoBLA1 = {0x01, 0x10, {0x88, 0xDD, 0x94, 0x59, 0x2E, 0x7C, 0x48, 0xBA, 0xB3, 0x81, 0xEA, 0xA0, 0xF8, 0x2A, 0x88, 0xF6}};
#endif /* __CID_EcoBLA1 */

/* Component factory for dynamic and static layout */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_88DD94592E7C48BAB381EAA0F82A88F6;
#endif

#endif /* __ID_ECO_BASIC_LEXICAL_ANALYZER_1_H__ */

