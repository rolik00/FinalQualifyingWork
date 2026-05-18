/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoTSA1RM
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoTSA1RM
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

#ifndef __I_ECO_SYNTAX_ANALYZER_1_RULE_MAPPER_H__
#define __I_ECO_SYNTAX_ANALYZER_1_RULE_MAPPER_H__

#include "IEcoBase1.h"
#include "IEcoAST1.h"
#include "IEcoTree1.h"

/* IEcoSyntaxAnalyzer1RuleMapper IID = {3CED9830-5D73-41B4-B705-6E0B9C6E1111} */
#ifndef __IID_IEcoSyntaxAnalyzer1RuleMapper
static const UGUID IID_IEcoSyntaxAnalyzer1RuleMapper = {0x01, 0x10, {0x3C, 0xED, 0x98, 0x30, 0x5D, 0x73, 0x41, 0xB4, 0xB7, 0x05, 0x6E, 0x0B, 0x9C, 0x6E, 0x11, 0x11} };
#endif /* __IID_IEcoSyntaxAnalyzer1RuleMapper */

typedef struct IEcoSyntaxAnalyzer1RuleMapper* IEcoSyntaxAnalyzer1RuleMapperPtr_t;

typedef struct IEcoSyntaxAnalyzer1RuleMapperVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoSyntaxAnalyzer1RuleMapperPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoSyntaxAnalyzer1RuleMapperPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoSyntaxAnalyzer1RuleMapperPtr_t me);

    /* IEcoTSA1RM */
    int16_t (ECOCALLMETHOD *Init)(/* in */ IEcoSyntaxAnalyzer1RuleMapperPtr_t me, /* in */ IEcoAST1* pIAST);
    int16_t (ECOCALLMETHOD *Map)(/* in */ IEcoSyntaxAnalyzer1RuleMapperPtr_t me, /* in */ IEcoTree1Node* pINode, /* in */ IEcoTree1Node* pIPreviousNode, /* in */ IEcoAST1Scope** ppICurScope, /* out */ IEcoList1** pIObjectList);

} IEcoSyntaxAnalyzer1RuleMapperVTbl, *IEcoSyntaxAnalyzer1RuleMapperVTblPtr;

interface IEcoSyntaxAnalyzer1RuleMapper {
    struct IEcoSyntaxAnalyzer1RuleMapperVTbl *pVTbl;
} IEcoSyntaxAnalyzer1RuleMapper;

#endif /* __I_ECO_SYNTAX_ANALYZER_1_RULE_MAPPER_H__ */
