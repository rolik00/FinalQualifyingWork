/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLA1_F82A88F6Factory
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the factory for the component
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_BASIC_LEXICAL_ANALYZER_1_FACTORY_H__
#define __I_ECO_BASIC_LEXICAL_ANALYZER_1_FACTORY_H__

#include "IEcoSystem1.h"

typedef struct CEcoBLA1_F82A88F6Factory {

    /* IEcoComponentFactory interface function table */
    IEcoComponentFactoryVTbl* m_pVTblICF;

    /* Reference counter */
    uint32_t m_cRef;

    /* Component data for the factory */
    char_t m_Name[64];
    char_t m_Version[16];
    char_t m_Manufacturer[64];

} CEcoBLA1_F82A88F6Factory;

#endif /* __I_ECO_BASIC_LEXICAL_ANALYZER_1_FACTORY_H__ */
