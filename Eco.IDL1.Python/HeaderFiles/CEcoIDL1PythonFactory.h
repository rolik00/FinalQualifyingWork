/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1Python_2C7799FCFactory
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

#ifndef __C_ECOIDL1PYTHON_FACTORY_H__
#define __C_ECOIDL1PYTHON_FACTORY_H__

#include "IEcoSystem1.h"

typedef struct CEcoIDL1Python_2C7799FCFactory {

    /* IEcoComponentFactory interface function table */
    IEcoComponentFactoryVTbl* m_pVTblICF;

    /* Reference counter */
    uint32_t m_cRef;

    /* Component data for the factory */
    char_t m_Name[64];
    char_t m_Version[16];
    char_t m_Manufacturer[64];

} CEcoIDL1Python_2C7799FCFactory;

#endif /* __C_ECOIDL1PYTHON_FACTORY_H__ */
