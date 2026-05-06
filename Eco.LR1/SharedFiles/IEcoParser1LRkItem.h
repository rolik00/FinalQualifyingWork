/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoParser1LRkItem
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoParser1LRkItem
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

#ifndef __I_ECO_PARSER_1_LR_K_ITEM_H__
#define __I_ECO_PARSER_1_LR_K_ITEM_H__

#include "IEcoBase1.h"
#include "IEcoBNF1.h"
#include "IEcoSet2.h"

/* IEcoParser1LRkItem IID = {70527837-F4DD-4BFB-90B5-37A41393443C} */
#ifndef __IID_IEcoParser1LRkItem
static const UGUID IID_IEcoParser1LRkItem = { 0x01, 0x10, {0x70, 0x52, 0x78, 0x37, 0xF4, 0xDD, 0x4B, 0xFB, 0x90, 0xB5, 0x37, 0xA4, 0x13, 0x93, 0x44, 0x3C} };
#endif /* __IID_IEcoParser1LRkItem */

typedef struct IEcoParser1LRkItem* IEcoParser1LRkItemPtr_t;

/* одно правило в некотором состоянии в парсере */
typedef struct IEcoParser1LRkItemVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoParser1LRkItemPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoParser1LRkItemPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoParser1LRkItemPtr_t me);

    /* IEcoParser1LRkItem */
    char_t* (ECOCALLMETHOD *get_Description)(/* in */ IEcoParser1LRkItemPtr_t me);
    int16_t (ECOCALLMETHOD *get_MarkerPosition)(/* in */ IEcoParser1LRkItemPtr_t me);
    int32_t (ECOCALLMETHOD *get_RuleSetId)(/* in */ IEcoParser1LRkItemPtr_t me);
    IEcoBNF1Rule* (ECOCALLMETHOD *get_Rule)(/* in */ IEcoParser1LRkItemPtr_t me);
    IEcoSet2* (ECOCALLMETHOD *get_NextTerms)(/* in */ IEcoParser1LRkItemPtr_t me);
    int16_t (ECOCALLMETHOD *AddNextTermSet)(/* in */ IEcoParser1LRkItemPtr_t me, IEcoSet2* pINewNextTerms);
    int16_t(ECOCALLMETHOD *AddNextTerm)(/* in */ IEcoParser1LRkItemPtr_t me, char_t* nextTerm);

} IEcoParser1LRkItemVTbl, *IEcoParser1LRkItemVTblPtr;

interface IEcoParser1LRkItem {
    struct IEcoParser1LRkItemVTbl *pVTbl;
} IEcoParser1LRkItem;

#endif /* __I_ECO_PARSER_1_LR_K_ITEM_H__ */
