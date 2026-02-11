/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IEcoRegEx1
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoRegEx1
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

#ifndef __I_ECO_REG_EX_1_H__
#define __I_ECO_REG_EX_1_H__

#include "IEcoBase1.h"
#include "IEcoRegEx1EnumMatches.h"

/* IEcoRegEx1 IID = {A5E921E4-E4B6-4CA3-BDD5-AFF5EB75F915} */
#ifndef __IID_IEcoRegEx1
static const UGUID IID_IEcoRegEx1 = {0x01, 0x10, {0xA5, 0xE9, 0x21, 0xE4, 0xE4, 0xB6, 0x4C, 0xA3, 0xBD, 0xD5, 0xAF, 0xF5, 0xEB, 0x75, 0xF9, 0x15}};
#endif /* __IID_IEcoRegEx1 */

typedef enum EcoRegEx1Encoding {
    ECO_REGEX_ENC_ASCII  = 0,
    ECO_REGEX_ENC_UTF8   = 1,
    ECO_REGEX_ENC_UTF16  = 2,
    ECO_REGEX_ENC_UTF32  = 3,
    
    /* Дополнительные флаги поиска (битовая маска) */
    ECO_REGEX_OPT_IGNORE_CASE = 0x00000100,
    ECO_REGEX_OPT_MULTILINE   = 0x00000200
} EcoRegEx1Encoding;

typedef struct IEcoRegEx1* IEcoRegEx1Ptr_t;

typedef struct IEcoRegEx1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoRegEx1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoRegEx1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoRegEx1Ptr_t me);

    /* IEcoRegEx1 */

    /* IsMatch: Проверка наличия совпадения */
    //int16_t (ECOCALLMETHOD *IsMatch)(
    //    /* in */ IEcoRegEx1Ptr_t me, 
    //    /* in */ voidptr_t str,            /* Строка для поиска */
    //    /* in */ uint32_t sizeInBytes,     /* Размер в байтах */
    //    /* in */ uint32_t flags            /* Флаги кодировки и опции (например, CaseInsensitive) */
    //);

    /* Match: Поиск первого совпадения */
    int16_t (ECOCALLMETHOD *Match)(
        /* in */ IEcoRegEx1Ptr_t me, 
        /* in */ voidptr_t str, 
        /* in */ uint32_t sizeInBytes, 
        /* in */ uint32_t flags, 
		/* out */ EcoRegEx1Match** pMatch
    );

    /* Matches: Возвращает итератор для всех совпадений */
    //int16_t (ECOCALLMETHOD *Matches)(
    //    /* in */ IEcoRegEx1Ptr_t me, 
    //    /* in */ voidptr_t str, 
    //    /* in */ uint32_t sizeInBytes, 
    //    /* in */ uint32_t flags, 
    //    /* out */ IEcoRegEx1EnumMatchesPtr_t* ppEnum
    //);

    /* Split: Разделение строки по шаблону */
    //int16_t (ECOCALLMETHOD *Split)(
    //    /* in */ IEcoRegEx1Ptr_t me, 
    //    /* in */ voidptr_t str, 
    //    /* in */ uint32_t sizeInBytes, 
    //    /* in */ uint32_t flags, 
    //    /* out */ voidptr_t* ppEnumStrings /* Интерфейс перечислителя строк */
    //);

    /* Replace: Замена совпадений на новую подстроку */
    //int16_t (ECOCALLMETHOD *Replace)(
    //    /* in */ IEcoRegEx1Ptr_t me, 
    //    /* in */ voidptr_t str, 
    //    /* in */ uint32_t sizeInBytes, 
    //   /* in */ voidptr_t replacement,    /* Строка замены */
    //    /* in */ uint32_t repSizeInBytes,  /* Размер замены */
    //    /* in */ uint32_t flags, 
    //    /* out */ voidptr_t* ppResultStr,  /* Выходной буфер (выделяется компонентом) */
    //    /* out */ uint32_t* pResSizeInBytes/* Размер полученного буфера */
    //);

} IEcoRegEx1VTbl, *IEcoRegEx1VTblPtr_t;

interface IEcoRegEx1 {
    struct IEcoRegEx1VTbl *pVTbl;
} IEcoRegEx1;


#endif /* __I_ECO_REG_EX_1_H__ */

