/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoSyntaxAnalyzer1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoSyntaxAnalyzer1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_SYNTAX_ANALYZER_1_H__
#define __I_ECO_SYNTAX_ANALYZER_1_H__

#include "IEcoBase1.h"
#include "IEcoSyntaxAnalyzer1Parser.h"

/* IEcoSyntaxAnalyzer1 IID = {223B5731-DC7A-4109-A426-AA10962400AB} */
#ifndef __IID_IEcoSyntaxAnalyzer1
static const UGUID IID_IEcoSyntaxAnalyzer1 = {0x01, 0x10, {0x22, 0x3B, 0x57, 0x31, 0xDC, 0x7A, 0x41, 0x09, 0xA4, 0x26, 0xAA, 0x10, 0x96, 0x24, 0x00, 0xAB} };
#endif /* __IID_IEcoSyntaxAnalyzer1 */

typedef struct IEcoSyntaxAnalyzer1* IEcoSyntaxAnalyzer1Ptr_t;

typedef struct IEcoSyntaxAnalyzer1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoSyntaxAnalyzer1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoSyntaxAnalyzer1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoSyntaxAnalyzer1Ptr_t me);

    /* IEcoSyntaxAnalyzer1 */
    int16_t (ECOCALLMETHOD *RegisterAlgorithm)(/* in */ IEcoSyntaxAnalyzer1Ptr_t me, /*in*/ const UGUID* rcid, /*in*/ char_t* algmName);
    void (ECOCALLMETHOD *set_DefaultAlgorithm)(/* in */ IEcoSyntaxAnalyzer1Ptr_t me, /*in*/ char_t* algmName);
    char_t* (ECOCALLMETHOD *get_DefaultAlgorithm)(/* in */ IEcoSyntaxAnalyzer1Ptr_t me);
    IEcoSyntaxAnalyzer1Parser* (ECOCALLMETHOD *get_Parser)(/* in */ IEcoSyntaxAnalyzer1Ptr_t me, /* in */ IEcoBNF1* pIGrammar, /* in */ char_t* algmName /* 0 - алгоритм по умолчанию */);

} IEcoSyntaxAnalyzer1VTbl, *IEcoSyntaxAnalyzer1VTblPtr;

interface IEcoSyntaxAnalyzer1 {
    struct IEcoSyntaxAnalyzer1VTbl *pVTbl;
} IEcoSyntaxAnalyzer1;

#endif /* __I_ECO_SYNTAX_ANALYZER_1_H__ */
