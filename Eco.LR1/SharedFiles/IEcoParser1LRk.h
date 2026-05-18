/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoParser1LRk
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoParser1LRk
 * </описание>
 *
 * <ссылка>
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_PARSER_1_LR_K_H__
#define __I_ECO_PARSER_1_LR_K_H__

#include "IEcoBase1.h"
#include "IEcoBNF1.h"
#include "IEcoMap2.h"

#include "IEcoParser1LRkItem.h"
#include "IEcoParser1ActionProcessing.h"
#include "IEcoDictionary1.h"
#include "IEcoData1.h"
#include "IEcoBNF1.h"
#include "IEcoFSM1.h"

/* IEcoParser1LRk IID = {1DB88464-66B1-4AC6-99B1-BBD4F2AE2F9B} */
#ifndef __IID_IEcoParser1LRk
static const UGUID IID_IEcoParser1LRk = {0x01, 0x10, {0x1D, 0xB8, 0x84, 0x64, 0x66, 0xB1, 0x4A, 0xC6, 0x99, 0xB1, 0xBB, 0xD4, 0xF2, 0xAE, 0x2F, 0x9B} };
#endif /* __IID_IEcoParser1LRk */

typedef struct IEcoParser1LRk* IEcoParser1LRkPtr_t;

typedef struct IEcoParser1LRkVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoParser1LRkPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoParser1LRkPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoParser1LRkPtr_t me);

    /* IEcoParser1LRk */
    int16_t (ECOCALLMETHOD *InitByGrammar)(/* in */ IEcoParser1LRkPtr_t me, /* in */ IEcoBNF1* pIGrammar, /* in */ int8_t lookahead);
    int8_t (ECOCALLMETHOD *get_Lookahead)(/* in */ IEcoParser1LRkPtr_t me);
    IEcoBNF1* (ECOCALLMETHOD *get_Grammar)(/* in */ IEcoParser1LRkPtr_t me);
    IEcoBNF1* (ECOCALLMETHOD *get_InternalGrammar)(/* in */ IEcoParser1LRkPtr_t me);
    IEcoMap2* (ECOCALLMETHOD *get_First)(/* in */ IEcoParser1LRkPtr_t me);
    IEcoMap2* (ECOCALLMETHOD *get_Follow)(/* in */ IEcoParser1LRkPtr_t me);
    IEcoList1* (ECOCALLMETHOD *get_ItemSets)(/* in */ IEcoParser1LRkPtr_t me);

    /* ACTION: Что делать в состоянии stateId при встрече терминала terminal?
       Возвращает упакованное значение: 
       > 0 : Shift в состояние N
       < 0 : Reduce по правилу M
       0   : Error
       0x7FFFFFFF : Accept
    */
    int32_t (ECOCALLMETHOD *get_Action)(/* in */ IEcoParser1LRkPtr_t me, /* in */ uint32_t stateId, /* in */ char_t* terminal);

    /* GOTO: Куда перейти из состояния stateId по нетерминалу nonTerminal? */
    int32_t (ECOCALLMETHOD *get_Goto)(IEcoParser1LRkPtr_t me, uint32_t stateId, char_t* nonTerminal);

    /* ACTION BY ID: Максимальная скорость. 
       terminalId — это индекс терминала в TerminalAlphabet грамматики. 
       Именно этот ID должен возвращать лексер. */
    int32_t (ECOCALLMETHOD *get_ActionById)(IEcoParser1LRkPtr_t me, uint32_t stateId, uint32_t terminalId);

    /* GOTO BY ID: Прямой переход после свертки.
       nonTerminalId — это индекс нетерминала в NonTerminalAlphabet. */
    int32_t (ECOCALLMETHOD *get_GotoById)(IEcoParser1LRkPtr_t me, uint32_t stateId, uint32_t nonTerminalId);


    IEcoFSM1StateMachine* (ECOCALLMETHOD *get_StateMachine)(/* in */ IEcoParser1LRkPtr_t me);
    IEcoList1* (ECOCALLMETHOD *get_Reduce)(/* in */ IEcoParser1LRkPtr_t me, uint32_t stateId, char_t* nextTerm);
    IEcoData1Table* (ECOCALLMETHOD *get_ActionTable)(/* in */ IEcoParser1LRkPtr_t me);
    IEcoParser1ActionProcessing* (ECOCALLMETHOD *get_ActionProcessing)(/* in */ IEcoParser1LRkPtr_t me);

} IEcoParser1LRkVTbl, *IEcoParser1LRkVTblPtr;

interface IEcoParser1LRk {
    struct IEcoParser1LRkVTbl *pVTbl;
} IEcoParser1LRk;

#endif /* __I_ECO_PARSER_1_LR_K_H__ */
