/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IEcoRegEx1EnumMatches
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoRegEx1EnumMatches
 * </description>
 *
 * <reference>
 *
 * </reference>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_REG_EX_1_ENUM_MATCHES_H__
#define __I_ECO_REG_EX_1_ENUM_MATCHES_H__

#include "IEcoBase1.h"

/* IEcoRegEx1EnumMatches IID = {784F264D-DE14-44F4-B1FF-94430059B13B} */
#ifndef __IID_IEcoRegEx1EnumMatches
static const UGUID IID_IEcoRegEx1EnumMatches = {0x01, 0x10, {0x78, 0x4F, 0x26, 0x4D, 0xDE, 0x14, 0x44, 0xF4, 0xB1, 0xFF, 0x94, 0x43, 0x00, 0x59, 0xB1, 0x3B}};
#endif /* __IID_IEcoRegEx1EnumMatches */

typedef struct EcoRegEx1Match {
    uint32_t index;    /* Позиция в символах или байтах */
    uint32_t length;   /* Длина */
    voidptr_t pValue;  /* Указатель на подстроку (может быть char* или wchar_t*) */
    uint32_t cCookie;  /* Cookie или идентификатор группы (Capture Group), если нужно */
} EcoRegEx1Match;

typedef struct IEcoRegEx1EnumMatches* IEcoRegEx1EnumMatchesPtr_t;

typedef struct IEcoRegEx1EnumMatchesVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoRegEx1EnumMatchesPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoRegEx1EnumMatchesPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoRegEx1EnumMatchesPtr_t me);

    /* IEcoRegEx1EnumMatches */
    int16_t (ECOCALLMETHOD *Next)(/* in */ IEcoRegEx1EnumMatchesPtr_t me, /* in */ uint32_t cMatchs, /* out */ struct EcoRegEx1Match *rgcd, /* out */ uint32_t *pcFetched);
    int16_t (ECOCALLMETHOD *Skip)(/* in */ IEcoRegEx1EnumMatchesPtr_t me, /* in */ uint32_t cMatchs);
    int16_t (ECOCALLMETHOD *Reset)(/* in */ IEcoRegEx1EnumMatchesPtr_t me);
    int16_t (ECOCALLMETHOD *Clone)(/* in */ IEcoRegEx1EnumMatchesPtr_t me, /* out */ IEcoRegEx1EnumMatchesPtr_t* ppEnum);

} IEcoRegEx1EnumMatchesVTbl, *IEcoRegEx1EnumMatchesVTblPtr_t;

interface IEcoRegEx1EnumMatches {
    struct IEcoRegEx1EnumMatchesVTbl *pVTbl;
} IEcoRegEx1EnumMatches;


#endif /* __I_ECO_REG_EX_1_ENUM_MATCHES_H__ */

