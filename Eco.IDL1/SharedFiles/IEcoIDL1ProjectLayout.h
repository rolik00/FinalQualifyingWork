/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IdEcoIDL1ProjectLayout
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoIDL1ProjectLayout
 * </description>
 *
 * <reference>
 *
 * </reference>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_IDL_1_PROJECT_LAYOUT_H__
#define __I_ECO_IDL_1_PROJECT_LAYOUT_H__

#include "IEcoBase1.h"

/* Типы артефактов для маппинга путей */
#define ECO_IDL_ARTIFACT_INTERFACE          1
#define ECO_IDL_ARTIFACT_ID_FILE            2
#define ECO_IDL_ARTIFACT_PROXY_STUB         3
#define ECO_IDL_ARTIFACT_TYPELIB            4
#define ECO_IDL_ARTIFACT_TEMPLATE           5
#define ECO_IDL_ARTIFACT_TEMPLATE_HEADERS   6
#define ECO_IDL_ARTIFACT_TEMPLATE_SHAREDS   7
#define ECO_IDL_ARTIFACT_TEMPLATE_SOURCES   8

/* IEcoIDL1ProjectLayout IID = {151492C5-8D57-490C-8E5D-FA6168D1C45F} */
#ifndef __IID_IEcoIDL1ProjectLayout
static const UGUID IID_IEcoIDL1ProjectLayout = {0x01, 0x10, {0x15, 0x14, 0x92, 0xC5, 0x8D, 0x57, 0x49, 0x0C, 0x8E, 0x5D, 0xFA, 0x61, 0x68, 0xD1, 0xC4, 0x5F}};
#endif /* __IID_IEcoIDL1ProjectLayout */

typedef struct IEcoIDL1ProjectLayout* IEcoIDL1ProjectLayoutPtr_t;

typedef struct IEcoIDL1ProjectLayoutVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoIDL1ProjectLayoutPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoIDL1ProjectLayoutPtr_t me);

    /* IEcoIDL1ProjectLayout */
    int16_t (ECOCALLMETHOD *Clear)(/* in */ IEcoIDL1ProjectLayoutPtr_t me);

    /* Установка базового пути проекта (Root) */
    int16_t (ECOCALLMETHOD *SetRootPath)(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ char_t* path);
    
    /* Установка относительного пути для конкретного типа файлов */
    /* Например: SetPath(me, ECO_IDL_ARTIFACT_INTERFACE, "include/idl") */
    int16_t (ECOCALLMETHOD *SetArtifactPath)(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ uint32_t artifactType, /* in */ char_t* relPath);

    /* Получение полного пути для генерации */
    int16_t (ECOCALLMETHOD *GetFullPath)(/* in */ IEcoIDL1ProjectLayoutPtr_t me, /* in */ uint32_t artifactType, /* out */ char_t** pFullPath);

} IEcoIDL1ProjectLayoutVTbl, *IEcoIDL1ProjectLayoutVTblPtr_t;

interface IEcoIDL1ProjectLayout {
    struct IEcoIDL1ProjectLayoutVTbl *pVTbl;
} IEcoIDL1ProjectLayout;


#endif /* __I_ECO_IDL_1_PROJECT_LAYOUT_H__ */

