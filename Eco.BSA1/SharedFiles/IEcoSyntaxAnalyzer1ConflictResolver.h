/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoSyntaxAnalyzer1ConflictResolver
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoSyntaxAnalyzer1ConflictResolver
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

#ifndef __I_ECO_SYNTAX_ANALYZER_1_CONFLICT_RESOLVER_H__
#define __I_ECO_SYNTAX_ANALYZER_1_CONFLICT_RESOLVER_H__

#include "IEcoBase1.h"
#include "IEcoAST1.h"
#include "IEcoLexicalAnalyzer1Token.h"
#include "IEcoParser1Action.h"

/* IEcoSyntaxAnalyzer1ConflictResolver IID = {3CED9830-5D73-41B4-B705-6E0B9C6E0567} */
#ifndef __IID_IEcoSyntaxAnalyzer1ConflictResolver
static const UGUID IID_IEcoSyntaxAnalyzer1ConflictResolver = {0x01, 0x10, {0x3C, 0xED, 0x98, 0x30, 0x5D, 0x73, 0x41, 0xB4, 0xB7, 0x05, 0x6E, 0x0B, 0x9C, 0x6E, 0x05, 0x67} };
#endif /* __IID_IEcoSyntaxAnalyzer1ConflictResolver */

typedef struct IEcoSyntaxAnalyzer1ConflictResolver* IEcoSyntaxAnalyzer1ConflictResolverPtr_t;

typedef struct IEcoSyntaxAnalyzer1ConflictResolverVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoSyntaxAnalyzer1ConflictResolverPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoSyntaxAnalyzer1ConflictResolverPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoSyntaxAnalyzer1ConflictResolverPtr_t me);

    /* IEcoSyntaxAnalyzer1ConflictResolver */
    int16_t (ECOCALLMETHOD *Init)(/* in */ IEcoSyntaxAnalyzer1ConflictResolverPtr_t me, /* in */ IEcoAST1* pIAST);
    int16_t(ECOCALLMETHOD *Resolve)(/* in */ IEcoSyntaxAnalyzer1ConflictResolverPtr_t me,
                                      /* in */ IEcoLexicalAnalyzer1Token* pIPrevToken, /* in */ IEcoLexicalAnalyzer1Token* pICurToken, /* in */ IEcoParser1Action* pIAction, /* in */ IEcoAST1Scope* pIScope,
                                      /* out */ int16_t* operation, /* out */ int16_t* reduceCount);

} IEcoSyntaxAnalyzer1ConflictResolverVTbl, *IEcoSyntaxAnalyzer1ConflictResolverVTblPtr;

interface IEcoSyntaxAnalyzer1ConflictResolver {
    struct IEcoSyntaxAnalyzer1ConflictResolverVTbl *pVTbl;
} IEcoSyntaxAnalyzer1ConflictResolver;

#endif /* __I_ECO_SYNTAX_ANALYZER_1_CONFLICT_RESOLVER_H__ */
