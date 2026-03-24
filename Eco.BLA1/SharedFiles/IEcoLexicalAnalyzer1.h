/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   IEcoLexicalAnalyzer1
 * </summary>
 *
 * <description>
 *   This header describes the interface IEcoLexicalAnalyzer1
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

#ifndef __I_ECO_LEXICAL_ANALYZER_1_H__
#define __I_ECO_LEXICAL_ANALYZER_1_H__

#include "IEcoBase1.h"
#include "IEcoLexicalRules1RE.h"
#include "IEcoLexicalRules1BNF.h"
#include "IEcoLexicalRules1FSM.h"
#include "IEcoLexicalRules1Direct.h"
#include "IEcoLexicalAnalyzer1Scanner.h"
#include "IEcoLexicalData1.h"

/* IEcoLexicalAnalyzer1 IID = {78E16240-C335-4A45-8D40-D896B3F9D73B} */
#ifndef __IID_IEcoLexicalAnalyzer1
static const UGUID IID_IEcoLexicalAnalyzer1 = {0x01, 0x10, {0x78, 0xE1, 0x62, 0x40, 0xC3, 0x35, 0x4A, 0x45, 0x8D, 0x40, 0xD8, 0x96, 0xB3, 0xF9, 0xD7, 0x3B}};
#endif /* __IID_IEcoLexicalAnalyzer1 */

typedef struct IEcoLexicalAnalyzer1* IEcoLexicalAnalyzer1Ptr_t;

typedef struct IEcoLexicalAnalyzer1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLexicalAnalyzer1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLexicalAnalyzer1Ptr_t me);

    /* IEcoLexicalAnalyzer1 */
    int16_t (ECOCALLMETHOD *new_FileScanner)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ char_t* fileName, /* out */ IEcoLexicalAnalyzer1ScannerPtr_t* ppIScanner);
    int16_t (ECOCALLMETHOD *LoadRulesFromFile)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ char_t* fileName, /* out */ IEcoLexicalData1Ptr_t* ppIRules);
    int16_t (ECOCALLMETHOD *SaveRulesToFile)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ char_t* fileName);

    int16_t (ECOCALLMETHOD *new_MemoryScanner)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ voidptr_t buffer, /* in */ uint32_t size, /* out */ IEcoLexicalAnalyzer1ScannerPtr_t* ppIScanner);
    int16_t (ECOCALLMETHOD *LoadRulesFromMemory)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ voidptr_t pBuffer, /* in */ uint32_t size, /* out */ IEcoLexicalData1Ptr_t* ppIRules);
    int16_t (ECOCALLMETHOD *SaveRulesToMemory)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ voidptr_t* ppBuffer, /* in */ uint32_t* pSize);

    int16_t (ECOCALLMETHOD *CreateRulesRE)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1REPtr_t* ppIRules);
    int16_t (ECOCALLMETHOD *CreateRulesBNF)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1BNFPtr_t* ppIRules);
    int16_t (ECOCALLMETHOD *CreateRulesFSM)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1FSMPtr_t* ppIRules);
    int16_t (ECOCALLMETHOD *CreateRulesDirect)(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1DirectPtr_t* ppIRules);

} IEcoLexicalAnalyzer1VTbl, *IEcoLexicalAnalyzer1VTblPtr_t;

interface IEcoLexicalAnalyzer1 {
    struct IEcoLexicalAnalyzer1VTbl *pVTbl;
} IEcoLexicalAnalyzer1;


#endif /* __I_ECO_LEXICAL_ANALYZER_1_H__ */

