/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoSyntaxAnalyzer1Parser
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoSyntaxAnalyzer1Parser
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

#ifndef __I_ECO_SYNTAX_ANALYZER_1_PARSER_H__
#define __I_ECO_SYNTAX_ANALYZER_1_PARSER_H__

#include "IEcoBase1.h"
#include "IdEcoAST1.h"
#include "IEcoParser1Action.h"
#include "IEcoSyntaxAnalyzer1RuleMapper.h"
#include "IEcoLexicalAnalyzer1Token.h"
#include "IEcoSyntaxAnalyzer1ConflictResolver.h"

/* IEcoSyntaxAnalyzer1Parser IID = {3CED9830-5D73-41B4-B705-6E0B9C6E108C} */
#ifndef __IID_IEcoSyntaxAnalyzer1Parser
static const UGUID IID_IEcoSyntaxAnalyzer1Parser = {0x01, 0x10, {0x3C, 0xED, 0x98, 0x30, 0x5D, 0x73, 0x41, 0xB4, 0xB7, 0x05, 0x6E, 0x0B, 0x9C, 0x6E, 0x10, 0x8C} };
#endif /* __IID_IEcoSyntaxAnalyzer1Parser */

typedef struct IEcoSyntaxAnalyzer1Parser* IEcoSyntaxAnalyzer1ParserPtr_t;

typedef struct IEcoSyntaxAnalyzer1ParserVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoSyntaxAnalyzer1ParserPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoSyntaxAnalyzer1ParserPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoSyntaxAnalyzer1ParserPtr_t me);

    /* IEcoSyntaxAnalyzer1Parser */
    IEcoParser1Action* (ECOCALLMETHOD *Parse)(/* in */ IEcoSyntaxAnalyzer1ParserPtr_t me, /* in */ IEcoLexicalAnalyzer1Token* token);
    int16_t (ECOCALLMETHOD *RuleMapping)(/* in */ IEcoSyntaxAnalyzer1ParserPtr_t me, /* in */ char_t* ruleName, /* in */ IEcoSyntaxAnalyzer1RuleMapperPtr_t pIMapper);
    int16_t(ECOCALLMETHOD *SetConflictResolver)(/* in */ IEcoSyntaxAnalyzer1ParserPtr_t me, /* in */ IEcoSyntaxAnalyzer1ConflictResolver* pIResolver);
    IEcoUnknown* (ECOCALLMETHOD *get_Algorithm)(/* in */ IEcoSyntaxAnalyzer1ParserPtr_t me);
    IEcoAST1* (ECOCALLMETHOD *get_AST)(/* in */ IEcoSyntaxAnalyzer1ParserPtr_t me);

} IEcoSyntaxAnalyzer1ParserVTbl, *IEcoSyntaxAnalyzer1ParserVTblPtr;

interface IEcoSyntaxAnalyzer1Parser {
    struct IEcoSyntaxAnalyzer1ParserVTbl *pVTbl;
} IEcoSyntaxAnalyzer1Parser;

#endif /* __I_ECO_SYNTAX_ANALYZER_1_PARSER_H__ */
