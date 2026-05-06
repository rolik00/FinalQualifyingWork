/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLR1_A441A18E
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoLR1_A441A18E
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLR1.h"
#include "CEcoLR1Item.h"
#include "CEcoLR1ActionProcessing.h"
#include "CEcoLR1Action.h"
#include "IEcoContainer1.h"

static IEcoSet2* ECOCALLMETHOD CEcoLR1_A441A18E_get_FirstFromString(CEcoLR1_A441A18E* pCMe, IEcoList1* pIElements, uint32_t from);
static IEcoParser1LRkItem* ECOCALLMETHOD CEcoLR1_A441A18E_CreateItem(CEcoLR1_A441A18E* pCMe, IEcoBNF1Rule* pIRule, uint32_t ruleSetId, uint32_t markerPos);

extern IEcoParser1LRkItemVTbl g_xCEcoLR1Item_A441A18E;
extern IEcoParser1ActionProcessingVTbl g_xCEcoLR1ActionProcessing_A441A18E;
extern CEcoLR1Action_A441A18E g_xCEcoLR1Action_A441A18E;


/* Очистка параметров FSM от наших Action до вызова PDA->Clear() */
static void CEcoLR1_A441A18E_ClearActions(CEcoLR1_A441A18E* pCMe) {
    IEcoFSM1StateMachine* pFSM = 0;
    IEcoList1* pTransitions = 0;
    IEcoFSM1Transition* pTr = 0;
    IEcoParser1Action* pAction = 0;
    uint32_t i = 0, count = 0;

    if (pCMe == 0 || pCMe->m_pIPDA == 0) return;

    pFSM = pCMe->m_pIPDA->pVTbl->get_FSM(pCMe->m_pIPDA);
    if (pFSM == 0) return;

    pTransitions = pFSM->pVTbl->get_Transitions(pFSM);
    if (pTransitions == 0) return;

    count = pTransitions->pVTbl->Count(pTransitions);
    for (i = 0; i < count; i++) {
        pTr = (IEcoFSM1Transition*)pTransitions->pVTbl->Item(pTransitions, i);
        if (pTr != 0) {
            pAction = (IEcoParser1Action*)pTr->pVTbl->get_Parameter(pTr);
            if (pAction != 0) {
                /* Освобождаем наш Action, устраняя утечку памяти */
                pAction->pVTbl->Release(pAction);
                /* Зануляем параметр, чтобы PDA_Clear не пытался удалить его как StackOp */
                pTr->pVTbl->set_Parameter(pTr, 0); 
            }
        }
    }
}

static IEcoParser1Action* CEcoLR1_A441A18E_CreateAction(
    /* in */ CEcoLR1_A441A18E* pCMe, 
    /* in */ int16_t type, 
    /* in */ IEcoBNF1Rule* pRule, 
    /* in */ uint16_t ruleSetId, 
    /* in */ IEcoFSM1State* pState) {
    CEcoLR1Action_A441A18E* pCObj = 0;
    int16_t result = 0;

    if (pCMe == 0) return 0;

    /* 1. Выделение памяти под объект действия */
    pCObj = (CEcoLR1Action_A441A18EPtr_t)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoLR1Action_A441A18E));
    if (pCObj == 0) return 0;

    /* 2. Копирование vtbl и начальных данных из статического шаблона (напрямую структурой для устранения BAD_ACT) */
    *pCObj = g_xCEcoLR1Action_A441A18E;

    /* 3. Стандартный цикл создания (Create) */
    result = pCObj->Create(pCObj, (IEcoUnknown*)pCMe->m_pISys, 0);
    if (result != 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCObj);
        return 0;
    }

    /* 4. Инициализация (Init) */
    result = pCObj->Init(pCObj, (IEcoUnknown*)pCMe->m_pISys);
    if (result != 0) {
        pCObj->Delete(pCObj);
        return 0;
    }

    /* 5. Заполнение специфических данных LR-действия */
    pCObj->m_Type = type;
    pCObj->m_pRule = pRule;
    pCObj->m_RuleSetId = ruleSetId;
    pCObj->m_pState = pState;

    return (IEcoParser1Action*)pCObj;
}

static IEcoParser1LRkItem* ECOCALLMETHOD CEcoLR1_A441A18E_CreateItem(
    /* in */ CEcoLR1_A441A18E* pCMe, 
    /* in */ IEcoBNF1Rule* pIRule, 
    /* in */ uint32_t ruleSetId, 
    /* in */ uint32_t markerPos) {
    CEcoLR1Item_A441A18E* pCObj = 0;
    int16_t result = 0;

    /* 1. Выделение памяти */
    pCObj = (CEcoLR1Item_A441A18EPtr_t)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoLR1Item_A441A18E));
    
    /* 2. Копирование vtbl и данных */
    pCObj = (CEcoLR1Item_A441A18EPtr_t)pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, pCObj, &g_xCEcoLR1Item_A441A18E, sizeof(CEcoLR1Item_A441A18E));
    
    /* 3. Создание (Create) */
    result = pCObj->Create(pCObj, (IEcoUnknown*)pCMe->m_pISys, 0);
    if (result != 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCObj);
        return 0;
    }

    pCObj->m_pIRule = pIRule;
    pCObj->m_RuleSetId = ruleSetId;
    pCObj->m_MarkerPosition = markerPos;

    /* 4. Инициализация */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pCObj->m_pINextTerms);
    if (pCObj->m_pINextTerms) {
        pCObj->m_pINextTerms->pVTbl->InitByTypeAndComparator(pCObj->m_pINextTerms, ECO_COMPARATOR_1_POINTER_T, 0);
    }
    result = pCObj->Init(pCObj, (IEcoUnknown*)pCMe->m_pISys);
    if (result != 0) {
        pCObj->Delete(pCObj);
        return 0;
    }

    return (IEcoParser1LRkItem*)pCObj;
}

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoParser1LRk interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLR1_A441A18E_QueryInterface(/* in */ IEcoParser1LRkPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoParser1LRk) ) {
        *ppv = &pCMe->m_pVTblILRk;
        pCMe->m_pVTblILRk->AddRef((IEcoParser1LRk*)pCMe);
    } else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblILRk;
        pCMe->m_pVTblILRk->AddRef((IEcoParser1LRk*)pCMe);
    } else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   AddRef Function
 * </summary>
 *
 * <description>
 *   AddRef function for the IEcoParser1LRk interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLR1_A441A18E_AddRef(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <summary>
 *   Release Function
 * </summary>
 *
 * <description>
 *   Release function for the IEcoParser1LRk interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLR1_A441A18E_Release(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    
    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Decrementing the component's reference count */
    --pCMe->m_cRef;

    /* If the count is zero, free the instance data */
    if ( pCMe->m_cRef == 0 ) {
        pCMe->Delete(pCMe);
        return 0;
    }

    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD CEcoLR1_A441A18E_ItemComparator_Compare(IEcoComparator1* me, void* p1, void* p2) {
    IEcoParser1LRkItem *item1 = (IEcoParser1LRkItem*)p1;
    IEcoParser1LRkItem *item2 = (IEcoParser1LRkItem*)p2;
    IEcoSet2 *s1 = 0, *s2 = 0;
    IEcoContainer1 *pICont1 = 0, *pICont2 = 0;
    IEcoContainer1Iterator* pIter1 = 0;
    int16_t res = 0;
    bool_t isMatch = 0;

    if (p1 == p2) return 0;

    if (p1 == 0 || p2 == 0) return 1;

    /* 1. Сравнение Ядра (Core) */
    if (item1->pVTbl->get_Rule(item1) != item2->pVTbl->get_Rule(item2)) return 1;
    if (item1->pVTbl->get_RuleSetId(item1) != item2->pVTbl->get_RuleSetId(item2)) return 1;
    if (item1->pVTbl->get_MarkerPosition(item1) != item2->pVTbl->get_MarkerPosition(item2)) return 1;
   
    /* 2. Глубокое сравнение Lookahead множеств */
    s1 = item1->pVTbl->get_NextTerms(item1);
    s2 = item2->pVTbl->get_NextTerms(item2);

    if (s1 == s2) return 0;
    if (s1 == 0 || s2 == 0) return 1;
    if (s1->pVTbl->Count(s1) != s2->pVTbl->Count(s2)) return 1;

    /* 3. Проверка содержимого (каждый символ s1 должен быть в s2) */
    res = s1->pVTbl->QueryInterface(s1, &IID_IEcoContainer1, (voidptr_t*)&pICont1);
    if (res != 0 || pICont1 == 0) return 1;
    
    res = s2->pVTbl->QueryInterface(s2, &IID_IEcoContainer1, (voidptr_t*)&pICont2);
    if (res != 0 || pICont2 == 0) {
        pICont1->pVTbl->Release(pICont1);
        return 1;
    }

    isMatch = 1;
    pIter1 = pICont1->pVTbl->GetIterator(pICont1, ECO_CONTAINER_1_ITER_BEGIN, 0);
    
    while (pIter1 && pIter1->pVTbl->Value(pIter1)) {
        if (!pICont2->pVTbl->Contains(pICont2, pIter1->pVTbl->Value(pIter1))) {
            isMatch = 0;
            break;
        }
        pIter1->pVTbl->Next(pIter1);
    }

    if (pIter1) pIter1->pVTbl->Release(pIter1);
    
    pICont1->pVTbl->Release(pICont1);
    pICont2->pVTbl->Release(pICont2);
    
    return (isMatch ? 0 : 1);
}

/* Вспомогательная функция для получения FIRST от хвоста строки + Lookahead пункта */
static IEcoSet2* ECOCALLMETHOD CEcoLR1_A441A18E_GetLookaheadForChild(CEcoLR1_A441A18E* pCMe, IEcoParser1LRkItem* pParentItem, IEcoList1* pElements, uint32_t nextPos) {
    IEcoSet2* pResult = 0;
    IEcoSet2* pFirstBeta = 0;
    IEcoSet2* pParentLA = 0;
    IEcoContainer1* pICont = 0;
    IEcoContainer1Iterator* pIter = 0;
    void* pValue = 0;
    int16_t hasEmpty = 0;
    int16_t res = 0;

    if (!pCMe || !pParentItem || !pElements) return 0;

    /* 1. Создаем результирующее множество */
    res = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pResult);
    if (res != 0) return 0;
    pResult->pVTbl->InitByType(pResult, ECO_COMPARATOR_1_STR_T);

    /* 2. Вычисляем FIRST(beta) — символы после нетерминала */
    pFirstBeta = CEcoLR1_A441A18E_get_FirstFromString(pCMe, pElements, nextPos);
    if (pFirstBeta != 0) {
        res = pFirstBeta->pVTbl->QueryInterface(pFirstBeta, &IID_IEcoContainer1, (voidptr_t*)&pICont);
        if (res == 0 && pICont != 0) {
            pIter = pICont->pVTbl->GetIterator(pICont, ECO_CONTAINER_1_ITER_BEGIN, 0);
            while (pIter && pIter->pVTbl->Value(pIter)) {
                pValue = pIter->pVTbl->Value(pIter);

                if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, (char_t*)pValue, ECO_PARSER_SPECIAL_SYMBOL_EMPTY) != 0) {
                    pResult->pVTbl->Add(pResult, pValue);
                } else {
                    hasEmpty = 1;
                }
                pIter->pVTbl->Next(pIter);
            }
            if (pIter) pIter->pVTbl->Release(pIter);
            pICont->pVTbl->Release(pICont);
        }
       
        if (pFirstBeta->pVTbl->Count(pFirstBeta) == 0 || 
           (pFirstBeta->pVTbl->Count(pFirstBeta) == 1 && hasEmpty)) {
            hasEmpty = 1;
        }

        pFirstBeta->pVTbl->Release(pFirstBeta);
    } else {
        hasEmpty = 1;
    }

    /* 3. Если beta может быть пустой — наследуем Lookahead родителя */
    if (hasEmpty || nextPos >= pElements->pVTbl->Count(pElements)) {
        pParentLA = pParentItem->pVTbl->get_NextTerms(pParentItem);
        if (pParentLA != 0) {
            res = pParentLA->pVTbl->QueryInterface(pParentLA, &IID_IEcoContainer1, (voidptr_t*)&pICont);
            if (res == 0 && pICont != 0) {
                pIter = pICont->pVTbl->GetIterator(pICont, ECO_CONTAINER_1_ITER_BEGIN, 0);
                while (pIter && pIter->pVTbl->Value(pIter)) {
                    pResult->pVTbl->Add(pResult, pIter->pVTbl->Value(pIter));
                    pIter->pVTbl->Next(pIter);
                }
                if (pIter) pIter->pVTbl->Release(pIter);
                pICont->pVTbl->Release(pICont);
            }
        }
    }
    return pResult;
}

IEcoSet2* ECOCALLMETHOD CEcoLR1_A441A18E_Closure(CEcoLR1_A441A18E* pCMe, IEcoSet2* pIItemSet) {
    IEcoParser1LRkItem *pIItem = 0, *pINewItem = 0, *pExisting = 0;
    IEcoBNF1Rule *pIRule = 0, *pICheckRule = 0;
    IEcoBNF1Element* pIElement = 0;
    IEcoList1 *pIRuleSet = 0, *pIElements = 0, *pIAllRules = 0;
    IEcoQueue1* pIQueue = 0;
    IEcoSet2 *pIResult = 0, *pIFirstBeta = 0;
    IEcoContainer1 *pIContInput = 0, *pIContResult = 0;
    IEcoContainer1Iterator *pISetIter = 0;
    char_t *name = 0;
    uint32_t i = 0, k = 0;
    int16_t res = 0;

    if (!pCMe || !pIItemSet) return 0;

    /* 1. Подготовка результирующего множества и очереди */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pIResult);
    pIResult->pVTbl->InitByType(pIResult, ECO_COMPARATOR_1_OBJECT_T);
    pIResult->pVTbl->QueryInterface(pIResult, &IID_IEcoContainer1, (voidptr_t*)&pIContResult);
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoQueue1, 0, &IID_IEcoQueue1, (void**)&pIQueue);
    
    /* 2. Копируем начальное ядро в результат и очередь */
    res = pIItemSet->pVTbl->QueryInterface(pIItemSet, &IID_IEcoContainer1, (voidptr_t*)&pIContInput);
    if (res == 0 && pIContInput != 0) {
        pISetIter = pIContInput->pVTbl->GetIterator(pIContInput, ECO_CONTAINER_1_ITER_BEGIN, 0);
        while (pISetIter && pISetIter->pVTbl->Value(pISetIter)) {
            pIItem = (IEcoParser1LRkItem*)pISetIter->pVTbl->Value(pISetIter);
            pIResult->pVTbl->Add(pIResult, pIItem);
            pIQueue->pVTbl->Enqueue(pIQueue, pIItem);
            pISetIter->pVTbl->Next(pISetIter);
        }
        if (pISetIter) pISetIter->pVTbl->Release(pISetIter);
        pIContInput->pVTbl->Release(pIContInput);
    }
    pIAllRules = pCMe->m_pIExtGrammar->pVTbl->get_RuleList(pCMe->m_pIExtGrammar);
    
    /* 3. Основной цикл вычисления замыкания */
    while (pIQueue->pVTbl->Count(pIQueue) > 0) {
        pIItem = (IEcoParser1LRkItem*)pIQueue->pVTbl->Dequeue(pIQueue);
        pIRule = pIItem->pVTbl->get_Rule(pIItem);
        pIElements = (IEcoList1*)pIRule->pVTbl->get_RuleSet(pIRule)->pVTbl->Item(pIRule->pVTbl->get_RuleSet(pIRule), pIItem->pVTbl->get_RuleSetId(pIItem));
        
        if ((uint32_t)pIItem->pVTbl->get_MarkerPosition(pIItem) >= pIElements->pVTbl->Count(pIElements)) continue;
        pIElement = (IEcoBNF1Element*)pIElements->pVTbl->Item(pIElements, pIItem->pVTbl->get_MarkerPosition(pIItem));
        
        if (pIElement && !pIElement->pVTbl->CheckFlag(pIElement, ECO_BNF_1_EF_TERMINAL)) {
            name = pIElement->pVTbl->get_Name(pIElement);
 
            if (pCMe->m_nLookahead > 0) {
                pIFirstBeta = CEcoLR1_A441A18E_GetLookaheadForChild(pCMe, pIItem, pIElements, pIItem->pVTbl->get_MarkerPosition(pIItem) + 1);
            } else {
                pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pIFirstBeta);
                if (pIFirstBeta) pIFirstBeta->pVTbl->InitByType(pIFirstBeta, ECO_COMPARATOR_1_STR_T);
            }
            for (k = 0; k < pIAllRules->pVTbl->Count(pIAllRules); k++) {
                pICheckRule = (IEcoBNF1Rule*)pIAllRules->pVTbl->Item(pIAllRules, k);
                if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, pICheckRule->pVTbl->get_Name(pICheckRule), name) == 0) {
                    pIRuleSet = pICheckRule->pVTbl->get_RuleSet(pICheckRule);
                    for (i = 0; i < pIRuleSet->pVTbl->Count(pIRuleSet); i++) {
                        pExisting = 0;
                        
                        pISetIter = pIContResult->pVTbl->GetIterator(pIContResult, ECO_CONTAINER_1_ITER_BEGIN, 0);
                        while (pISetIter && pISetIter->pVTbl->Value(pISetIter)) {
                            IEcoParser1LRkItem* pCurr = (IEcoParser1LRkItem*)pISetIter->pVTbl->Value(pISetIter);
                            if (pCurr->pVTbl->get_Rule(pCurr) == pICheckRule && 
                                pCurr->pVTbl->get_RuleSetId(pCurr) == i && 
                                pCurr->pVTbl->get_MarkerPosition(pCurr) == 0) {
                                pExisting = pCurr;
                                break;
                            }
                            pISetIter->pVTbl->Next(pISetIter);
                        }
                        if (pISetIter) pISetIter->pVTbl->Release(pISetIter);
                        if (pExisting) {
                            if (pExisting->pVTbl->AddNextTermSet(pExisting, pIFirstBeta) == 0) {
                                pIQueue->pVTbl->Enqueue(pIQueue, pExisting);
                            }
                        } else {
                            pINewItem = CEcoLR1_A441A18E_CreateItem(pCMe, pICheckRule, i, 0);
                            pINewItem->pVTbl->AddNextTermSet(pINewItem, pIFirstBeta);
                            pIResult->pVTbl->Add(pIResult, pINewItem);
                            pIQueue->pVTbl->Enqueue(pIQueue, pINewItem);
                        }
                    }
                }
            }
            if (pIFirstBeta) pIFirstBeta->pVTbl->Release(pIFirstBeta);
        }
    }
    if (pIContResult) pIContResult->pVTbl->Release(pIContResult);
    if (pIQueue) pIQueue->pVTbl->Release(pIQueue);
    return pIResult;
}

IEcoSet2* ECOCALLMETHOD CEcoLR1_A441A18E_GoTo(CEcoLR1_A441A18E* pCMe, IEcoSet2* pIItemSet, char_t* X) {
    IEcoSet2* pIInitialSet = 0;
    IEcoContainer1* pIInputCont = 0;
    IEcoContainer1Iterator* pIIter = 0;
    IEcoParser1LRkItem *pIItem = 0, *pINewItem = 0;
    IEcoBNF1Rule* pIRule = 0;
    IEcoList1 *pIRuleSet = 0, *pIElements = 0;
    IEcoBNF1Element* pISymbol = 0;
    char_t* symbolName = 0;
    uint32_t markerPos = 0;
    int16_t res = 0;

    if (!pCMe || !pIItemSet || !X) return 0;

    /* 1. Создаем новое множество (ядро будущего состояния) */
    res = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pIInitialSet);
    if (res != 0) return 0;
    
    /* Настраиваем компаратор для пунктов (сравнение по правилу, позиции и LA) */
    pIInitialSet->pVTbl->InitByType(pIInitialSet, ECO_COMPARATOR_1_OBJECT_T);
    
    /* 2. Получаем контейнер входного множества для итерации */
    res = pIItemSet->pVTbl->QueryInterface(pIItemSet, &IID_IEcoContainer1, (voidptr_t*)&pIInputCont);
    if (res != 0 || pIInputCont == 0) return 0;
    
    pIIter = pIInputCont->pVTbl->GetIterator(pIInputCont, ECO_CONTAINER_1_ITER_BEGIN, 0);
    while (pIIter && pIIter->pVTbl->Value(pIIter)) {
        pIItem = (IEcoParser1LRkItem*)pIIter->pVTbl->Value(pIIter);
        pIRule = pIItem->pVTbl->get_Rule(pIItem);
        pIRuleSet = pIRule->pVTbl->get_RuleSet(pIRule);
        pIElements = (IEcoList1*)pIRuleSet->pVTbl->Item(pIRuleSet, pIItem->pVTbl->get_RuleSetId(pIItem));
        markerPos = pIItem->pVTbl->get_MarkerPosition(pIItem);

        if (markerPos < pIElements->pVTbl->Count(pIElements)) {
            pISymbol = (IEcoBNF1Element*)pIElements->pVTbl->Item(pIElements, markerPos);
			if (pISymbol != 0 ) {
				symbolName = pISymbol->pVTbl->get_Name(pISymbol);
				if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, symbolName, X) == 0) {
					pINewItem = CEcoLR1_A441A18E_CreateItem(pCMe, pIRule, pIItem->pVTbl->get_RuleSetId(pIItem), markerPos + 1);
					pINewItem->pVTbl->AddNextTermSet(pINewItem, pIItem->pVTbl->get_NextTerms(pIItem));
					pIInitialSet->pVTbl->Add(pIInitialSet, pINewItem);
				}
			}
        }
        pIIter->pVTbl->Next(pIIter);
    }
    if (pIIter) pIIter->pVTbl->Release(pIIter);
    pIInputCont->pVTbl->Release(pIInputCont);

    if (pIInitialSet->pVTbl->Count(pIInitialSet) > 0) {
        IEcoSet2* pIClosure = CEcoLR1_A441A18E_Closure(pCMe, pIInitialSet);
        pIInitialSet->pVTbl->Release(pIInitialSet);
        return pIClosure;
    }
    
    pIInitialSet->pVTbl->Release(pIInitialSet);
    return 0;
}

static int32_t ECOCALLMETHOD CEcoLR1_A441A18E_FindSetIndex(CEcoLR1_A441A18E* pCMe, IEcoSet2* pISet) {
    uint32_t i = 0;
    IEcoSet2* pIExistingSet = 0;
    IEcoContainer1 *pIInputCont = 0, *pIExistCont = 0;
    IEcoContainer1Iterator *pIterNew = 0, *pIterOld = 0;
    int16_t res = 0;
    bool_t isItemFound = 0;
    bool_t isAllMatched = 0;
    
    if (!pCMe || !pISet) return -1;
    
    res = pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIInputCont);
    if (res != 0 || pIInputCont == 0) return -1;
    
    for (i = 0; i < pCMe->m_pIItemSets->pVTbl->Count(pCMe->m_pIItemSets); i++) {
        pIExistingSet = (IEcoSet2*)pCMe->m_pIItemSets->pVTbl->Item(pCMe->m_pIItemSets, i);
        if (pIExistingSet->pVTbl->Count(pIExistingSet) != pISet->pVTbl->Count(pISet)) continue;
        res = pIExistingSet->pVTbl->QueryInterface(pIExistingSet, &IID_IEcoContainer1, (voidptr_t*)&pIExistCont);
        if (res != 0 || pIExistCont == 0) continue;
        
        isAllMatched = 1;
        pIterNew = pIInputCont->pVTbl->GetIterator(pIInputCont, ECO_CONTAINER_1_ITER_BEGIN, 0);
        while (pIterNew && pIterNew->pVTbl->Value(pIterNew)) {
            void* pNewItem = pIterNew->pVTbl->Value(pIterNew);
            isItemFound = 0;
            pIterOld = pIExistCont->pVTbl->GetIterator(pIExistCont, ECO_CONTAINER_1_ITER_BEGIN, 0);
            while (pIterOld && pIterOld->pVTbl->Value(pIterOld)) {
                if (CEcoLR1_A441A18E_ItemComparator_Compare(0, pNewItem, pIterOld->pVTbl->Value(pIterOld)) == 0) {
                    isItemFound = 1;
                    break;
                }
                pIterOld->pVTbl->Next(pIterOld);
            }
            if (pIterOld) pIterOld->pVTbl->Release(pIterOld);
            if (!isItemFound) {
                isAllMatched = 0;
                break;
            }
            pIterNew->pVTbl->Next(pIterNew);
        }
        if (pIterNew) pIterNew->pVTbl->Release(pIterNew);
        pIExistCont->pVTbl->Release(pIExistCont);
        if (isAllMatched) {
            pIInputCont->pVTbl->Release(pIInputCont);
            return (int32_t)i;
        }
    }
    pIInputCont->pVTbl->Release(pIInputCont);
    return -1;
}

int16_t ECOCALLMETHOD CEcoLR1_A441A18E_BuildItemSets(CEcoLR1_A441A18E* pCMe) {
    IEcoBNF1Rule* pIStartRule = 0;
    IEcoList1 *pIRules = 0, *pIAlphabet = 0;
    IEcoSet2 *pIInitialSet = 0, *pIClosure = 0;
    IEcoParser1LRkItem* pIStartItem = 0;
    uint32_t i = 0, j = 0;
    int16_t res = 0;

    if (!pCMe) return -1;

    pIAlphabet = pCMe->m_pIExtGrammar->pVTbl->get_Alphabet(pCMe->m_pIExtGrammar);
    
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pIInitialSet);
    pIInitialSet->pVTbl->InitByType(pIInitialSet, ECO_COMPARATOR_1_OBJECT_T);
    pIRules = pCMe->m_pIExtGrammar->pVTbl->get_RuleList(pCMe->m_pIExtGrammar);
    pIStartRule = (IEcoBNF1Rule*)pIRules->pVTbl->Item(pIRules, 0);
    pIStartItem = CEcoLR1_A441A18E_CreateItem(pCMe, pIStartRule, 0, 0);
    pIStartItem->pVTbl->AddNextTerm(pIStartItem, ECO_PARSER_SPECIAL_SYMBOL_END);
    pIInitialSet->pVTbl->Add(pIInitialSet, pIStartItem);
    
    pIClosure = CEcoLR1_A441A18E_Closure(pCMe, pIInitialSet);
    if (pIClosure && pIClosure->pVTbl->Count(pIClosure) > 0) {
        pCMe->m_pIItemSets->pVTbl->Add(pCMe->m_pIItemSets, pIClosure);
        printf("SUCCESS: State 0 initialized. Total states to process: 1\n");
        
        for (i = 0; i < pCMe->m_pIItemSets->pVTbl->Count(pCMe->m_pIItemSets); i++) {
            IEcoSet2* pICurrentState = (IEcoSet2*)pCMe->m_pIItemSets->pVTbl->Item(pCMe->m_pIItemSets, i);
            for (j = 0; j < pIAlphabet->pVTbl->Count(pIAlphabet); j++) {
                char_t* X = (char_t*)pIAlphabet->pVTbl->Item(pIAlphabet, j);
                IEcoSet2* pINextState = CEcoLR1_A441A18E_GoTo(pCMe, pICurrentState, X);
                if (pINextState && pINextState->pVTbl->Count(pINextState) > 0) {
                    int32_t idx = CEcoLR1_A441A18E_FindSetIndex(pCMe, pINextState);
                    if (idx == -1) {
                        pCMe->m_pIItemSets->pVTbl->Add(pCMe->m_pIItemSets, pINextState);
                        idx = pCMe->m_pIItemSets->pVTbl->Count(pCMe->m_pIItemSets) - 1;
                        printf("DEBUG: State %d --(%s)--> State %d (NEW)\n", i, X, idx);
                    } else {
                        printf("DEBUG: State %d --(%s)--> State %d (Old)\n", i, X, idx);
                        pINextState->pVTbl->Release(pINextState);
                    }
                } else if (pINextState) {
                    pINextState->pVTbl->Release(pINextState);
                }
            }
        }
    } else {
        printf("FATAL: Closure returned empty set!\n");
    }
    if (pIInitialSet) pIInitialSet->pVTbl->Release(pIInitialSet);
    printf("DONE: Built %d states.\n", pCMe->m_pIItemSets->pVTbl->Count(pCMe->m_pIItemSets));
    return 0;
}

static IEcoSet2* ECOCALLMETHOD CEcoLR1_A441A18E_get_FirstFromString(CEcoLR1_A441A18E* pCMe, IEcoList1* pIElements, uint32_t from) {
    IEcoBNF1Element* pIElement = 0;
    IEcoSet2* pIResult = 0;
    IEcoSet2* pIFirstOfSymbol = 0;
    IEcoContainer1* pISymbolCont = 0;
    IEcoContainer1Iterator* pIIter = 0;
    char_t* elemName = 0;
    char_t* terminalName = 0;
    void* pValue = 0;
    uint32_t i = 0;
    uint32_t elementCount = 0;
    int16_t res = 0;
    bool_t hasEmptyInSymbol = 0;

    if (pCMe == 0 || pIElements == 0) {
        return 0;
    }

    elementCount = pIElements->pVTbl->Count(pIElements);
    
    /* 1. Создаем временное множество для результата */
    res = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pIResult);
    if (res != 0 || pIResult == 0) {
        printf("ERROR: get_FirstFromString failed to create pIResult set!\n");
        return 0;
    }

    /* 2. Инициализируем множество строковым компаратором для имен терминалов */
    pIResult->pVTbl->InitByType(pIResult, ECO_COMPARATOR_1_STR_T);
    
    /* 3. Проход по цепочке элементов от позиции from */
    for (i = from; i < elementCount; ++i) {
        pIElement = (IEcoBNF1Element*)pIElements->pVTbl->Item(pIElements, i);
        
		if (pIElement == 0 || *(void**)pIElement == 0) {
            hasEmptyInSymbol = 1;
            if (i == elementCount - 1) {
                pIResult->pVTbl->Add(pIResult, ECO_PARSER_SPECIAL_SYMBOL_EMPTY);
            }
            continue;
        }

        elemName = pIElement->pVTbl->get_Name(pIElement);
        if (elemName == 0) {
            hasEmptyInSymbol = 1;
            continue;
        }

        elemName = pIElement->pVTbl->get_Name(pIElement);
        hasEmptyInSymbol = 0;
        
        /* 4. Получаем множество FIRST для конкретного символа из карты */
        pIFirstOfSymbol = (IEcoSet2*)pCMe->m_pIFirst->pVTbl->Get(pCMe->m_pIFirst, elemName);
        if (pIFirstOfSymbol == 0) {
            printf("ERROR: Symbol '%s' not found in m_pIFirst map!\n", elemName);
            break;
        }
        
        /* 5. Итерируемся по терминалам внутри множества FIRST этого символа */
        res = pIFirstOfSymbol->pVTbl->QueryInterface(pIFirstOfSymbol, &IID_IEcoContainer1, (voidptr_t*)&pISymbolCont);
        if (res == 0 && pISymbolCont != 0) {
            pIIter = pISymbolCont->pVTbl->GetIterator(pISymbolCont, ECO_CONTAINER_1_ITER_BEGIN, 0);
            while (pIIter != 0 && pIIter->pVTbl->Value(pIIter) != 0) {
                pValue = pIIter->pVTbl->Value(pIIter);
                terminalName = (char_t*)pValue;
               
                if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, terminalName, ECO_PARSER_SPECIAL_SYMBOL_EMPTY) != 0) {
                    pIResult->pVTbl->Add(pIResult, terminalName);
                } else {
                    hasEmptyInSymbol = 1;
                }
                pIIter->pVTbl->Next(pIIter);
            }
            if (pIIter) {
                pIIter->pVTbl->Release(pIIter);
            }
            
            /* 6. Если символ не может быть пустым, FIRST цепочки закончен */
            if (hasEmptyInSymbol == 0) {
                pISymbolCont->pVTbl->Release(pISymbolCont);
                break;
            }
            pISymbolCont->pVTbl->Release(pISymbolCont);
        }
        
        if (i == elementCount - 1 && hasEmptyInSymbol == 1) {
            pIResult->pVTbl->Add(pIResult, ECO_PARSER_SPECIAL_SYMBOL_EMPTY);
        }
    }
   
    if (from >= elementCount) {
        pIResult->pVTbl->Add(pIResult, ECO_PARSER_SPECIAL_SYMBOL_EMPTY);
    }
    return pIResult;
}

int16_t ECOCALLMETHOD CEcoLR1_A441A18E_BuildFirst(CEcoLR1_A441A18E* pCMe) {
    IEcoBNF1Rule* pIRule = 0;
    IEcoList1* pITerminals = 0;
    IEcoList1* pINonTerminals = 0;
    IEcoList1* pIRules = 0;
    IEcoList1* pIRuleSet = 0;
    IEcoList1* pIElements = 0;
    IEcoSet2* pIFirstFromString = 0;
    IEcoSet2* pIFirstOfNonTerm = 0;
    IEcoContainer1* pIContFromString = 0;
    IEcoContainer1Iterator* pIIter = 0;
    char_t* name = 0;
    void* pValue = 0;
    uint32_t i = 0, j = 0;
    int32_t updateCount = 1;
    int32_t iteration = 0;
    int16_t res = 0;

    if (pCMe == 0) return -1;

    printf("\n--- START BuildFirst Diagnostic ---\n");

    /* 1. FIRST для ТЕРМИНАЛОВ: FIRST(t) = {t} */
    pITerminals = pCMe->m_pIExtGrammar->pVTbl->get_TerminalAlphabet(pCMe->m_pIExtGrammar);
    printf("1. Initializing Terminals (Count: %d)\n", pITerminals->pVTbl->Count(pITerminals));
    
    for (i = 0; i < pITerminals->pVTbl->Count(pITerminals); ++i) {
        name = (char_t*)pITerminals->pVTbl->Item(pITerminals, i);
        res = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pIFirstOfNonTerm);
        
        pIFirstOfNonTerm->pVTbl->InitByType(pIFirstOfNonTerm, ECO_COMPARATOR_1_STR_T);
        pIFirstOfNonTerm->pVTbl->Add(pIFirstOfNonTerm, name); 
        pCMe->m_pIFirst->pVTbl->Set(pCMe->m_pIFirst, name, pIFirstOfNonTerm);
        printf("  Terminal [%s]: Added to FIRST map\n", name);
        pIFirstOfNonTerm->pVTbl->Release(pIFirstOfNonTerm);
    }

    /* 2. Инициализация FIRST для НЕТЕРМИНАЛОВ (пустые множества) */
    pINonTerminals = pCMe->m_pIExtGrammar->pVTbl->get_NonTerminalAlphabet(pCMe->m_pIExtGrammar);
    printf("2. Initializing NonTerminals (Count: %d)\n", pINonTerminals->pVTbl->Count(pINonTerminals));
    for (i = 0; i < pINonTerminals->pVTbl->Count(pINonTerminals); ++i) {
        name = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, i);
        res = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pIFirstOfNonTerm);
        pIFirstOfNonTerm->pVTbl->InitByType(pIFirstOfNonTerm, ECO_COMPARATOR_1_STR_T);
        pCMe->m_pIFirst->pVTbl->Set(pCMe->m_pIFirst, name, pIFirstOfNonTerm);
        pIFirstOfNonTerm->pVTbl->Release(pIFirstOfNonTerm);
    }

    /* 3. Итеративное заполнение (Fixed Point Iteration) */
    pIRules = pCMe->m_pIExtGrammar->pVTbl->get_RuleList(pCMe->m_pIExtGrammar);
    printf("3. Starting Iterations...\n");
    while (updateCount != 0) {
        updateCount = 0;
        iteration++;
        for (i = 0; i < pIRules->pVTbl->Count(pIRules); ++i) {
            pIRule = (IEcoBNF1Rule*)pIRules->pVTbl->Item(pIRules, i);
            name = pIRule->pVTbl->get_Name(pIRule);
            pIFirstOfNonTerm = (IEcoSet2*)pCMe->m_pIFirst->pVTbl->Get(pCMe->m_pIFirst, name);
            pIRuleSet = pIRule->pVTbl->get_RuleSet(pIRule);
            for (j = 0; j < pIRuleSet->pVTbl->Count(pIRuleSet); ++j) {
                pIElements = (IEcoList1*)pIRuleSet->pVTbl->Item(pIRuleSet, j);
                
                pIFirstFromString = CEcoLR1_A441A18E_get_FirstFromString(pCMe, pIElements, 0);
                if (pIFirstFromString != 0) {
                    
                    res = pIFirstFromString->pVTbl->QueryInterface(pIFirstFromString, &IID_IEcoContainer1, (voidptr_t*)&pIContFromString);
                    if (res == 0 && pIContFromString != 0) {
                        pIIter = pIContFromString->pVTbl->GetIterator(pIContFromString, ECO_CONTAINER_1_ITER_BEGIN, 0);
                        while (pIIter != 0 && pIIter->pVTbl->Value(pIIter) != 0) {
                            pValue = pIIter->pVTbl->Value(pIIter);
                            
                            if (pIFirstOfNonTerm->pVTbl->Add(pIFirstOfNonTerm, pValue) == 0) {
                                updateCount++;
                            }
                            pIIter->pVTbl->Next(pIIter);
                        }
                        if (pIIter) pIIter->pVTbl->Release(pIIter);
                        pIContFromString->pVTbl->Release(pIContFromString);
                    }
                    pIFirstFromString->pVTbl->Release(pIFirstFromString);
                }
            }
        }
        printf("  Iteration %d: New symbols added: %d\n", iteration, updateCount);
        if (iteration > 100) {
            printf("  ERROR: Potential infinite loop in BuildFirst!\n");
            break;
        }
    }
    printf("--- END BuildFirst Diagnostic ---\n\n");
    return 0;
}

int16_t ECOCALLMETHOD CEcoLR1_A441A18E_BuildFollow(CEcoLR1_A441A18E* pCMe) {
    IEcoBNF1Rule* pIRule = 0;
    IEcoBNF1Element* pIElement = 0;
    IEcoList1* pINonTerminals = 0;
    IEcoList1* pIRules = 0;
    IEcoList1* pIRuleSet = 0;
    IEcoList1* pIElements = 0;
    IEcoSet2* pIFollowOfElem = 0;
    IEcoSet2* pIFirstOfTail = 0;
    IEcoSet2* pIFollowOfParent = 0;
    IEcoContainer1* pIContFirst = 0;
    IEcoContainer1* pIContParentFollow = 0;
    IEcoContainer1Iterator* pIIter = 0;
    char_t* ruleName = 0;
    char_t* elemName = 0;
    void* pValue = 0;
    uint32_t i = 0, j = 0, k = 0;
    int32_t updateCount = 1;
    int32_t iteration = 0;
    int16_t res = 0;
    bool_t hasEmptyInTail = 0;

    if (pCMe == 0) return -1;

    printf("\n--- START BuildFollow Diagnostic ---\n");

    /* 1. Инициализация пустых множеств FOLLOW для всех нетерминалов */
    pINonTerminals = pCMe->m_pIExtGrammar->pVTbl->get_NonTerminalAlphabet(pCMe->m_pIExtGrammar);
    printf("1. Initializing FOLLOW sets (Count: %d)\n", pINonTerminals->pVTbl->Count(pINonTerminals));
    for (i = 0; i < pINonTerminals->pVTbl->Count(pINonTerminals); ++i) {
        elemName = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, i);
        res = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pIFollowOfElem);
        
        pIFollowOfElem->pVTbl->InitByType(pIFollowOfElem, ECO_COMPARATOR_1_STR_T);
        pCMe->m_pIFollow->pVTbl->Set(pCMe->m_pIFollow, elemName, pIFollowOfElem);
        pIFollowOfElem->pVTbl->Release(pIFollowOfElem);
    }

    /* 2. FOLLOW(StartSymbol) = { $END } */
    if (pINonTerminals->pVTbl->Count(pINonTerminals) > 0) {
        elemName = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, 0);
        pIFollowOfElem = (IEcoSet2*)pCMe->m_pIFollow->pVTbl->Get(pCMe->m_pIFollow, elemName);
        if (pIFollowOfElem) {
            pIFollowOfElem->pVTbl->Add(pIFollowOfElem, ECO_PARSER_SPECIAL_SYMBOL_END);
            printf("2. Added $END to FOLLOW of start symbol [%s]\n", elemName);
        }
    }

    /* 3. Итеративное построение (Fixed Point) */
    pIRules = pCMe->m_pIExtGrammar->pVTbl->get_RuleList(pCMe->m_pIExtGrammar);
    printf("3. Starting Iterations...\n");
    while (updateCount != 0) {
        updateCount = 0;
        iteration++;
        for (i = 0; i < pIRules->pVTbl->Count(pIRules); ++i) {
            pIRule = (IEcoBNF1Rule*)pIRules->pVTbl->Item(pIRules, i);
            ruleName = pIRule->pVTbl->get_Name(pIRule);
            
            pIFollowOfParent = (IEcoSet2*)pCMe->m_pIFollow->pVTbl->Get(pCMe->m_pIFollow, ruleName);
            if (pIFollowOfParent == 0) continue;
            pIRuleSet = pIRule->pVTbl->get_RuleSet(pIRule);
            for (j = 0; j < pIRuleSet->pVTbl->Count(pIRuleSet); ++j) {
                pIElements = (IEcoList1*)pIRuleSet->pVTbl->Item(pIRuleSet, j);
                for (k = 0; k < pIElements->pVTbl->Count(pIElements); ++k) {
                    pIElement = (IEcoBNF1Element*)pIElements->pVTbl->Item(pIElements, k);

					if (pIElement == 0 || *(void**)pIElement == 0) {
						continue;
					}
                    
                    if (pIElement->pVTbl->CheckFlag(pIElement, ECO_BNF_1_EF_TERMINAL)) continue;
                    elemName = pIElement->pVTbl->get_Name(pIElement);
                    pIFollowOfElem = (IEcoSet2*)pCMe->m_pIFollow->pVTbl->Get(pCMe->m_pIFollow, elemName);
                    if (pIFollowOfElem == 0) continue;
                
                    pIFirstOfTail = CEcoLR1_A441A18E_get_FirstFromString(pCMe, pIElements, k + 1);
                    if (pIFirstOfTail == 0) continue;
                    res = pIFirstOfTail->pVTbl->QueryInterface(pIFirstOfTail, &IID_IEcoContainer1, (voidptr_t*)&pIContFirst);
                    hasEmptyInTail = 0;
                    if (res == 0 && pIContFirst != 0) {
                        pIIter = pIContFirst->pVTbl->GetIterator(pIContFirst, ECO_CONTAINER_1_ITER_BEGIN, 0);
                        while (pIIter != 0 && pIIter->pVTbl->Value(pIIter) != 0) {
                            pValue = pIIter->pVTbl->Value(pIIter);
                            if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, (char_t*)pValue, ECO_PARSER_SPECIAL_SYMBOL_EMPTY) != 0) {
                                if (pIFollowOfElem->pVTbl->Add(pIFollowOfElem, pValue) == 0) updateCount++;
                            } else {
                                hasEmptyInTail = 1;
                            }
                            pIIter->pVTbl->Next(pIIter);
                        }
                        pIIter->pVTbl->Release(pIIter);
                        pIContFirst->pVTbl->Release(pIContFirst);
                    }
                    pIFirstOfTail->pVTbl->Release(pIFirstOfTail);
                 
                    if (hasEmptyInTail || (k + 1 == pIElements->pVTbl->Count(pIElements))) {
                        res = pIFollowOfParent->pVTbl->QueryInterface(pIFollowOfParent, &IID_IEcoContainer1, (voidptr_t*)&pIContParentFollow);
                        if (res == 0 && pIContParentFollow != 0) {
                            pIIter = pIContParentFollow->pVTbl->GetIterator(pIContParentFollow, ECO_CONTAINER_1_ITER_BEGIN, 0);
                            while (pIIter != 0 && pIIter->pVTbl->Value(pIIter) != 0) {
                                if (pIFollowOfElem->pVTbl->Add(pIFollowOfElem, pIIter->pVTbl->Value(pIIter)) == 0) updateCount++;
                                pIIter->pVTbl->Next(pIIter);
                            }
                            pIIter->pVTbl->Release(pIIter);
                            pIContParentFollow->pVTbl->Release(pIContParentFollow);
                        }
                    }
                }
            }
        }
        printf("  Iteration %d: New symbols added to FOLLOW: %d\n", iteration, updateCount);
        if (iteration > 100) break;
    }
    printf("--- END BuildFollow Diagnostic ---\n\n");
    return 0;
}

int16_t ECOCALLMETHOD CEcoLR1_A441A18E_BuildFL1Alphabet(CEcoLR1_A441A18E* pCMe) {
    IEcoBNF1* pIBNF = pCMe->m_pIExtGrammar;
    IEcoList1* pITerminals = 0;
    IEcoList1* pINonTerminals = 0;
    IEcoFL1Alphabet* pIAlphabet = 0;
    IEcoFL1SymbolSet* pISet = 0;
    char_t* name = 0;
    uint32_t i = 0;
    uint32_t nameLen = 0;

    /* 1. Получаем доступ к алфавиту FL1 из PDA */
    pIAlphabet = (IEcoFL1Alphabet*)pCMe->m_pIPDA->pVTbl->get_InputAlphabet(pCMe->m_pIPDA);
    
    /* 2. Регистрируем Терминалы */
    pITerminals = pIBNF->pVTbl->get_TerminalAlphabet(pIBNF);
    for (i = 0; i < pITerminals->pVTbl->Count(pITerminals); i++) {
        name = (char_t*)pITerminals->pVTbl->Item(pITerminals, i);
        nameLen = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, name);
        pISet = pIAlphabet->pVTbl->AddSymbolSet(pIAlphabet, name);
        pISet->pVTbl->set_Terminal(pISet, 1);
        if (nameLen == 1) {
            pISet->pVTbl->AddSymbol(pISet, (byte_t*)name, 8, 0, 0); 
        } else {
            pISet->pVTbl->set_Word(pISet, (byte_t*)name, (uint8_t)nameLen);
        }
        pCMe->m_pSymbolMap->pVTbl->Set(pCMe->m_pSymbolMap, name, pISet);
    }

    /* 3. Регистрируем Нетерминалы */
    pINonTerminals = pIBNF->pVTbl->get_NonTerminalAlphabet(pIBNF);
    for (i = 0; i < pINonTerminals->pVTbl->Count(pINonTerminals); i++) {
        name = (char_t*)pINonTerminals->pVTbl->Item(pINonTerminals, i);
        pISet = pIAlphabet->pVTbl->AddSymbolSet(pIAlphabet, name);
        pISet->pVTbl->set_Terminal(pISet, 0);
        pCMe->m_pSymbolMap->pVTbl->Set(pCMe->m_pSymbolMap, name, pISet);
    }
    
    /* 4. Маркер конца $END */
    pISet = pIAlphabet->pVTbl->AddSymbolSet(pIAlphabet, ECO_PARSER_SPECIAL_SYMBOL_END);
    pISet->pVTbl->set_Terminal(pISet, 1);
    pCMe->m_pSymbolMap->pVTbl->Set(pCMe->m_pSymbolMap, ECO_PARSER_SPECIAL_SYMBOL_END, pISet);
    
    return 0;
}

/* Вспомогательная функция поиска перехода в FSM (C89) */
static IEcoFSM1Transition* CEcoLR1_A441A18E_FindTransition(IEcoFSM1StateMachine* pIFSM, IEcoFSM1State* pSrc, IEcoFSM1Event* pEv) {
    IEcoList1* pTransitions = 0;
    IEcoFSM1Transition* pTr = 0;
    uint32_t i = 0, count = 0;
    
    if (!pIFSM || !pSrc || !pEv) return 0;

    /* Получаем список всех существующих переходов в автомате */
    pTransitions = pIFSM->pVTbl->get_Transitions(pIFSM);
    if (!pTransitions) return 0;
    count = pTransitions->pVTbl->Count(pTransitions);
    for (i = 0; i < count; i++) {
        pTr = (IEcoFSM1Transition*)pTransitions->pVTbl->Item(pTransitions, i);
        if (pTr != 0) {
            if (pTr->pVTbl->get_Source(pTr) == pSrc && pTr->pVTbl->get_Event(pTr) == pEv) {
                return pTr;
            }
        }
    }
    return 0;
}

/* Функция конфигурации FSM для алгоритма LR (генерация Action и Goto) без привязки к PDA */
int16_t ECOCALLMETHOD CEcoLR1_A441A18E_ConfigurePDAOperations(CEcoLR1_A441A18E* pCMe) {
    IEcoFSM1StateMachine* pIFSM = 0;
    IEcoList1 *pIItemSets = 0, *pIAlphabet = 0, *pStatesList = 0, *pLookaheadsToProcess = 0;
    IEcoSet2 *pISet = 0, *pNextSet = 0, *pINextTerms = 0;
    IEcoContainer1Iterator *pIItemIter = 0, *pILookIter = 0;
    IEcoParser1LRkItem* pIItem = 0;
    IEcoParser1Action* pIAction = 0;
    IEcoBNF1Rule *pIRule = 0, *pIStartRule = 0;
    IEcoList1* pIElements = 0, *pTerminals = 0;
    IEcoFSM1Transition* pTrans = 0;
    IEcoFSM1Event* pEv = 0;
    IEcoFSM1State *pSrcState = 0, *pDstState = 0;
    IEcoContainer1 *pIContainer = 0, *pIContainerTerms = 0;
    char_t* X = 0;
    char_t* lookahead = 0;
    char_t szState[32];
    uint32_t i = 0, j = 0, t = 0, laIdx = 0;
    int32_t nextIdx = 0;
    int16_t res = 0;

    if (!pCMe || !pCMe->m_pIPDA) return -1;

    pIFSM = pCMe->m_pIPDA->pVTbl->get_FSM(pCMe->m_pIPDA);
    pIItemSets = pCMe->m_pIItemSets;
    pIAlphabet = pCMe->m_pIExtGrammar->pVTbl->get_Alphabet(pCMe->m_pIExtGrammar);
    pTerminals = pCMe->m_pIExtGrammar->pVTbl->get_TerminalAlphabet(pCMe->m_pIExtGrammar);
    pIStartRule = (IEcoBNF1Rule*)pCMe->m_pIExtGrammar->pVTbl->get_RuleList(pCMe->m_pIExtGrammar)->pVTbl->Item(pCMe->m_pIExtGrammar->pVTbl->get_RuleList(pCMe->m_pIExtGrammar), 0);

    printf("\n[FSM_CONFIG] === Starting FSM (Action/Goto) Configuration ===\n");

    /* 1. Создание всех состояний парсера в FSM */
    for (i = 0; i < pIItemSets->pVTbl->Count(pIItemSets); i++) {
        sprintf(szState, "s%u", i);
        pDstState = pIFSM->pVTbl->AddState(pIFSM, szState);
        if (i == 0) pDstState->pVTbl->set_Initial(pDstState, 1);
    }
    pStatesList = pIFSM->pVTbl->get_States(pIFSM);

    /* 2. Настройка переходов SHIFT, GOTO и REDUCE */
    for (i = 0; i < pIItemSets->pVTbl->Count(pIItemSets); i++) {
        pISet = (IEcoSet2*)pIItemSets->pVTbl->Item(pIItemSets, i);
        res = pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer);
        pSrcState = (IEcoFSM1State*)pStatesList->pVTbl->Item(pStatesList, i);

        /* --- ЧАСТЬ А: SHIFT (терминалы) и GOTO (нетерминалы) --- */
        for (j = 0; j < pIAlphabet->pVTbl->Count(pIAlphabet); j++) {
            X = (char_t*)pIAlphabet->pVTbl->Item(pIAlphabet, j);
            pNextSet = CEcoLR1_A441A18E_GoTo(pCMe, pISet, X);
            
            if (pNextSet && pNextSet->pVTbl->Count(pNextSet) > 0) {
                nextIdx = CEcoLR1_A441A18E_FindSetIndex(pCMe, pNextSet);
                if (nextIdx != -1) {
                    pDstState = (IEcoFSM1State*)pStatesList->pVTbl->Item(pStatesList, (uint32_t)nextIdx);
                    
                    /* Создаем событие перехода */
                    pEv = pIFSM->pVTbl->AddEvent(pIFSM, X, (int16_t)j, 0);
                    
                    if (!CEcoLR1_A441A18E_FindTransition(pIFSM, pSrcState, pEv)) {
                        pTrans = pIFSM->pVTbl->AddTransition(pIFSM, pEv, pSrcState, pDstState);
                        
                        /* Создаем SHIFT/GOTO экшен. Мы НЕ перезаписываем Parameter сторонними StackOp! */
                        pIAction = CEcoLR1_A441A18E_CreateAction(pCMe, ECO_ACTION_PROCESSING_TYPE_SHIFT, 0, 0, pDstState);
                        pTrans->pVTbl->set_Parameter(pTrans, pIAction);
                    } else if (pCMe->m_nLookahead == 0) {
                        /* Конфликт при добавлении SHIFT (обычно невозможно для детерминированных, но безопасно проверить) */
                        printf("[LR(0) CONFLICT] Shift/Goto Conflict on '%s' in State %u\n", X, i);
                        pNextSet->pVTbl->Release(pNextSet);
                        pIContainer->pVTbl->Release(pIContainer);
                        return -1;
                    }
                }
            }
            if (pNextSet) pNextSet->pVTbl->Release(pNextSet);
        }

        /* --- ЧАСТЬ Б: REDUCE и ACCEPT --- */
        pIItemIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
        while (pIItemIter && pIItemIter->pVTbl->Value(pIItemIter)) {
            pIItem = (IEcoParser1LRkItem*)pIItemIter->pVTbl->Value(pIItemIter);
            pIRule = pIItem->pVTbl->get_Rule(pIItem);
            pIElements = (IEcoList1*)pIRule->pVTbl->get_RuleSet(pIRule)->pVTbl->Item(pIRule->pVTbl->get_RuleSet(pIRule), pIItem->pVTbl->get_RuleSetId(pIItem));
            
            /* Если точка в конце — это кандидат на свертку */
            if ((uint32_t)pIItem->pVTbl->get_MarkerPosition(pIItem) == pIElements->pVTbl->Count(pIElements)) {
                
                pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pLookaheadsToProcess);
                
                /* Формирование набора Lookahead для REDUCE */
                if (pCMe->m_nLookahead == 0) {
                    /* Для LR(0) мы применяем REDUCE на все терминалы + $END */
                    for (t = 0; t < pTerminals->pVTbl->Count(pTerminals); t++) {
                        pLookaheadsToProcess->pVTbl->Add(pLookaheadsToProcess, pTerminals->pVTbl->Item(pTerminals, t));
                    }
                    pLookaheadsToProcess->pVTbl->Add(pLookaheadsToProcess, ECO_PARSER_SPECIAL_SYMBOL_END);
                } else {
                    /* Для LR(k>0) используем только символы из NextTerms пункта */
                    pINextTerms = pIItem->pVTbl->get_NextTerms(pIItem);
                    res = pINextTerms->pVTbl->QueryInterface(pINextTerms, &IID_IEcoContainer1, (voidptr_t*)&pIContainerTerms);
                    pILookIter = pIContainerTerms->pVTbl->GetIterator(pIContainerTerms, ECO_CONTAINER_1_ITER_BEGIN, 0);
                    while (pILookIter && pILookIter->pVTbl->Value(pILookIter)) {
                        pLookaheadsToProcess->pVTbl->Add(pLookaheadsToProcess, pILookIter->pVTbl->Value(pILookIter));
                        pILookIter->pVTbl->Next(pILookIter);
                    }
                    if (pILookIter) pILookIter->pVTbl->Release(pILookIter);
                    if (pIContainerTerms) pIContainerTerms->pVTbl->Release(pIContainerTerms);
                }

                for (laIdx = 0; laIdx < pLookaheadsToProcess->pVTbl->Count(pLookaheadsToProcess); laIdx++) {
                    lookahead = (char_t*)pLookaheadsToProcess->pVTbl->Item(pLookaheadsToProcess, laIdx);
                    
                    /* isNull = 1, REDUCE не должен потреблять входной символ! */
                    pEv = pIFSM->pVTbl->AddEvent(pIFSM, lookahead, 0, 1);

                    if (!CEcoLR1_A441A18E_FindTransition(pIFSM, pSrcState, pEv)) {
                        /* Переходим в самих себя, так как вычислять новое состояние будет ActionProcessing */
                        pTrans = pIFSM->pVTbl->AddTransition(pIFSM, pEv, pSrcState, pSrcState);
                        
                        if (pIRule == pIStartRule && strcmp(lookahead, ECO_PARSER_SPECIAL_SYMBOL_END) == 0) {
                            pIAction = CEcoLR1_A441A18E_CreateAction(pCMe, ECO_ACTION_PROCESSING_TYPE_ACCEPT, 0, 0, 0);
                            pSrcState->pVTbl->set_Final(pSrcState, 1);
                        } else {
                            pIAction = CEcoLR1_A441A18E_CreateAction(pCMe, ECO_ACTION_PROCESSING_TYPE_REDUCE, pIRule, pIItem->pVTbl->get_RuleSetId(pIItem), 0);
                        }
                        pTrans->pVTbl->set_Parameter(pTrans, pIAction);
                    } else {
                        /* Конфликт обнаружен! Shift-Reduce или Reduce-Reduce */
                        printf("[CONFLICT] Shift/Reduce or Reduce/Reduce Conflict on '%s' in State %u\n", lookahead, i);
                        pLookaheadsToProcess->pVTbl->Release(pLookaheadsToProcess);
                        pIItemIter->pVTbl->Release(pIItemIter);
                        pIContainer->pVTbl->Release(pIContainer);
                        return -1;
                    }
                }
                pLookaheadsToProcess->pVTbl->Release(pLookaheadsToProcess);
            }
            pIItemIter->pVTbl->Next(pIItemIter);
        }
        if (pIItemIter) pIItemIter->pVTbl->Release(pIItemIter);
        if (pIContainer) pIContainer->pVTbl->Release(pIContainer);
    }
    printf("[FSM_CONFIG] === Configuration Finished. States: %u ===\n", pIItemSets->pVTbl->Count(pIItemSets));
    return 0;
}

/* Чистая проверка конфликтов без использования PDA/FSM */
static int16_t CheckConflicts(CEcoLR1_A441A18E* pCMe) {
    uint32_t i = 0, t = 0;
    IEcoSet2* pISet = 0;
    IEcoContainer1* pIContainer = 0;
    IEcoContainer1Iterator* pIItemIter = 0;
    IEcoParser1LRkItem* pIItem = 0;
    IEcoBNF1Rule* pIRule = 0;
    IEcoList1* pIElements = 0;
    IEcoList1* pTerminals = pCMe->m_pIExtGrammar->pVTbl->get_TerminalAlphabet(pCMe->m_pIExtGrammar);
    
    IEcoSet2 *pShiftSymbols = 0, *pReduceSymbols = 0;
    IEcoContainer1 *pILookaheadCont = 0;
    IEcoContainer1Iterator *pILookIter = 0;
    int16_t conflictFound = 0;

    if (!pCMe || !pCMe->m_pIItemSets) return -1;

    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pShiftSymbols);
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoSet2, 0, &IID_IEcoSet2, (void**)&pReduceSymbols);
    pShiftSymbols->pVTbl->InitByType(pShiftSymbols, ECO_COMPARATOR_1_STR_T);
    pReduceSymbols->pVTbl->InitByType(pReduceSymbols, ECO_COMPARATOR_1_STR_T);

    for (i = 0; i < pCMe->m_pIItemSets->pVTbl->Count(pCMe->m_pIItemSets); i++) {
        pISet = (IEcoSet2*)pCMe->m_pIItemSets->pVTbl->Item(pCMe->m_pIItemSets, i);
        pShiftSymbols->pVTbl->Clear(pShiftSymbols);
        pReduceSymbols->pVTbl->Clear(pReduceSymbols);

        if (pISet->pVTbl->QueryInterface(pISet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer) != 0) continue;

        pIItemIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
        while (pIItemIter && pIItemIter->pVTbl->Value(pIItemIter)) {
            pIItem = (IEcoParser1LRkItem*)pIItemIter->pVTbl->Value(pIItemIter);
            pIRule = pIItem->pVTbl->get_Rule(pIItem);
            pIElements = (IEcoList1*)pIRule->pVTbl->get_RuleSet(pIRule)->pVTbl->Item(pIRule->pVTbl->get_RuleSet(pIRule), pIItem->pVTbl->get_RuleSetId(pIItem));

            if ((uint32_t)pIItem->pVTbl->get_MarkerPosition(pIItem) < pIElements->pVTbl->Count(pIElements)) {
                IEcoBNF1Element* pElem = (IEcoBNF1Element*)pIElements->pVTbl->Item(pIElements, pIItem->pVTbl->get_MarkerPosition(pIItem));
                if (pElem != 0 && pElem->pVTbl->CheckFlag(pElem, ECO_BNF_1_EF_TERMINAL)) {
                    pShiftSymbols->pVTbl->Add(pShiftSymbols, pElem->pVTbl->get_Name(pElem));
                }
            } 
            else {
                if (pCMe->m_nLookahead == 0) {
                    for (t = 0; t < pTerminals->pVTbl->Count(pTerminals); t++) {
                        char_t* term = (char_t*)pTerminals->pVTbl->Item(pTerminals, t);
                        if (pReduceSymbols->pVTbl->Add(pReduceSymbols, term) != 0) {
                            conflictFound = 1; 
                            printf("  [CONFLICT] Reduce/Reduce in State %u on '%s'\n", i, term);
                        }
                    }
                    if (pReduceSymbols->pVTbl->Add(pReduceSymbols, ECO_PARSER_SPECIAL_SYMBOL_END) != 0) conflictFound = 1;
                } else {
                    IEcoSet2* pINextTerms = pIItem->pVTbl->get_NextTerms(pIItem);
                    if (pINextTerms && pINextTerms->pVTbl->QueryInterface(pINextTerms, &IID_IEcoContainer1, (voidptr_t*)&pILookaheadCont) == 0) {
                        pILookIter = pILookaheadCont->pVTbl->GetIterator(pILookaheadCont, ECO_CONTAINER_1_ITER_BEGIN, 0);
                        while (pILookIter && pILookIter->pVTbl->Value(pILookIter)) {
                            char_t* la = (char_t*)pILookIter->pVTbl->Value(pILookIter);
                            if (pReduceSymbols->pVTbl->Add(pReduceSymbols, la) != 0) {
								conflictFound = 1;
                                printf("  [CONFLICT] Reduce/Reduce in State %u on '%s'\n", i, la);
                            }
                            pILookIter->pVTbl->Next(pILookIter);
                        }
                        if (pILookIter) pILookIter->pVTbl->Release(pILookIter);
                        pILookaheadCont->pVTbl->Release(pILookaheadCont);
                    }
                }
            }
            pIItemIter->pVTbl->Next(pIItemIter);
        }
        if (pIItemIter) pIItemIter->pVTbl->Release(pIItemIter);
        pIContainer->pVTbl->Release(pIContainer);

        if (pReduceSymbols->pVTbl->QueryInterface(pReduceSymbols, &IID_IEcoContainer1, (voidptr_t*)&pIContainer) == 0) {
            pIItemIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
            while (pIItemIter && pIItemIter->pVTbl->Value(pIItemIter)) {
                if (pShiftSymbols->pVTbl->Contains(pShiftSymbols, pIItemIter->pVTbl->Value(pIItemIter))) {
                    conflictFound = 1;
                    printf("  [CONFLICT] Shift/Reduce in State %u on '%s'\n", i, (char_t*)pIItemIter->pVTbl->Value(pIItemIter));
                }
                pIItemIter->pVTbl->Next(pIItemIter);
            }
            if (pIItemIter) pIItemIter->pVTbl->Release(pIItemIter);
            pIContainer->pVTbl->Release(pIContainer);
        }

        if (conflictFound) break;
    }

    pShiftSymbols->pVTbl->Release(pShiftSymbols);
    pReduceSymbols->pVTbl->Release(pReduceSymbols);

    return conflictFound ? -1 : 0;
}

static int16_t ECOCALLMETHOD CEcoLR1_A441A18E_InitByGrammar(/* in */ IEcoParser1LRkPtr_t me, /* in */ IEcoBNF1* pIGrammar, /* in */ int8_t lookahead) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    IEcoFSM1StateMachine* pIFSM = 0;
    int16_t result = 0;
    
    /* Pointer Validation */
    if (me == 0 || !pIGrammar) {
        return ERR_ECO_POINTER;
    }

    /* 1. Инициализация инфраструктуры */
    pCMe->m_pIExtGrammar = pIGrammar;
    pIGrammar->pVTbl->AddRef(pIGrammar);
    pCMe->m_nLookahead = lookahead;
    if (pCMe->m_pIItemSets) {
        pCMe->m_pIItemSets->pVTbl->Clear(pCMe->m_pIItemSets);
    }

    /* 2. Подготовка PDA и FSM */
    /* Важно очистить наши экшены ДО того как PDA вызовет очистку FSM */
    CEcoLR1_A441A18E_ClearActions(pCMe);
    pCMe->m_pIPDA->pVTbl->Clear(pCMe->m_pIPDA);
    pIFSM = pCMe->m_pIPDA->pVTbl->get_FSM(pCMe->m_pIPDA);

    /* 3. Регистрация терминалов в FL1 Alphabet */
    result = pCMe->BuildFL1Alphabet(pCMe);

    /* 4. Математический этап (FIRST/FOLLOW) */
    pCMe->BuildFirst(pCMe);
    if (lookahead > 0) {
        pCMe->BuildFollow(pCMe);
    }
        
    /* 5. Генерация состояний (ItemSets) */
    result = pCMe->BuildItemSets(pCMe);
    if (result != 0) {
        return result; 
    }
    
	/* 6. Проверка алгоритма на конфликты */
    result = CheckConflicts(pCMe);
    if (result != 0) {
        return result; 
    }

    return ERR_ECO_SUCCESES;
}

static int8_t ECOCALLMETHOD CEcoLR1_A441A18E_get_Lookahead(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}

static IEcoBNF1* ECOCALLMETHOD CEcoLR1_A441A18E_get_Grammar(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;

    if (pCMe == 0) return 0;

    return pCMe->m_pIExtGrammar; 
}

static IEcoBNF1* ECOCALLMETHOD CEcoLR1_A441A18E_get_InternalGrammar(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;

    if (pCMe == 0) return 0;

    return pCMe->m_pIExtGrammar;
}

static IEcoMap2* ECOCALLMETHOD CEcoLR1_A441A18E_get_First(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;

    if (pCMe == 0) return 0;

    return pCMe->m_pIFirst; 
}

static IEcoMap2* ECOCALLMETHOD CEcoLR1_A441A18E_get_Follow(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    
    if (pCMe == 0) return 0;
    
    return pCMe->m_pIFollow; 
}

static IEcoList1* ECOCALLMETHOD CEcoLR1_A441A18E_get_ItemSets(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;

    if (pCMe == 0) return 0;

    return pCMe->m_pIItemSets; 
}

static int32_t ECOCALLMETHOD CEcoLR1_A441A18E_get_Action(IEcoParser1LRkPtr_t me, uint32_t stateId, char_t* terminal) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    IEcoSet2* pICurrentSet = 0;
    IEcoContainer1* pIContainer = 0;
    IEcoContainer1Iterator* pIIter = 0;
    IEcoParser1LRkItem* pIItem = 0;
    IEcoBNF1Rule* pIRule = 0;
    IEcoList1* pIElements = 0;
    int32_t resultAction = 0; /* По умолчанию ERROR (0) */

    /* 1. Валидация входных данных */
    if (pCMe == 0 || pCMe->m_pIItemSets == 0 || terminal == 0) {
        return 0;
    }

    if (stateId >= pCMe->m_pIItemSets->pVTbl->Count(pCMe->m_pIItemSets)) {
        return 0;
    }

    /* 2. Извлекаем набор ситуаций для текущего состояния */
    pICurrentSet = (IEcoSet2*)pCMe->m_pIItemSets->pVTbl->Item(pCMe->m_pIItemSets, stateId);

    /* 3. Проверка на SHIFT (Переход по терминалу) */
    /* Используем функцию GOTO: если переход по терминалу ведет в новое состояние, это SHIFT */
    {
        IEcoSet2* pNextSet = CEcoLR1_A441A18E_GoTo(pCMe, pICurrentSet, terminal);
        if (pNextSet && pNextSet->pVTbl->Count(pNextSet) > 0) {
            int32_t nextStateIdx = CEcoLR1_A441A18E_FindSetIndex(pCMe, pNextSet);
            if (nextStateIdx != -1) {
                pNextSet->pVTbl->Release(pNextSet);
                return nextStateIdx; /* Положительное число = SHIFT в состояние N */
            }
        }
        if (pNextSet) pNextSet->pVTbl->Release(pNextSet);
    }

    /* 4. Проверка на REDUCE или ACCEPT */
    /* Итерируемся по всем пунктам (Items) внутри состояния */
    if (pICurrentSet->pVTbl->QueryInterface(pICurrentSet, &IID_IEcoContainer1, (voidptr_t*)&pIContainer) == 0) {
        pIIter = pIContainer->pVTbl->GetIterator(pIContainer, ECO_CONTAINER_1_ITER_BEGIN, 0);
        while (pIIter && pIIter->pVTbl->Value(pIIter)) {
            pIItem = (IEcoParser1LRkItem*)pIIter->pVTbl->Value(pIIter);
            pIRule = pIItem->pVTbl->get_Rule(pIItem);
            
            /* Получаем правую часть правила для проверки позиции маркера */
            pIElements = (IEcoList1*)pIRule->pVTbl->get_RuleSet(pIRule)->pVTbl->Item(pIRule->pVTbl->get_RuleSet(pIRule), pIItem->pVTbl->get_RuleSetId(pIItem));

            /* Если маркер стоит в самом конце: A -> alpha . */
            if ((uint32_t)pIItem->pVTbl->get_MarkerPosition(pIItem) == pIElements->pVTbl->Count(pIElements)) {
                
                /* Проверяем Lookahead (NextTerms) */
                IEcoSet2* pNextTerms = pIItem->pVTbl->get_NextTerms(pIItem);
                
                /* Если текущий входной терминал входит в множество предпросмотра данного правила */
                if (pNextTerms && pNextTerms->pVTbl->Contains(pNextTerms, terminal)) {
                    
                    /* Проверка на ACCEPT: Специальное правило S' -> S . и символ конца $ */
                    if (pIItem->pVTbl->get_RuleSetId(pIItem) == 0 && 
                        strcmp(terminal, ECO_PARSER_SPECIAL_SYMBOL_END) == 0) {
                        resultAction = 0x7FFFFFFF; /* Константа ACCEPT */
                    } else {
                        /* Отрицательное число = REDUCE по правилу M */
                        /* Индекс берется из RuleSetId или глобального списка правил */
                        resultAction = -(int32_t)(pIItem->pVTbl->get_RuleSetId(pIItem));
                    }
                    break;
                }
            }
            pIIter->pVTbl->Next(pIIter);
        }
        if (pIIter) pIIter->pVTbl->Release(pIIter);
        pIContainer->pVTbl->Release(pIContainer);
    }

    return resultAction;
}

static int32_t ECOCALLMETHOD CEcoLR1_A441A18E_get_Goto(IEcoParser1LRkPtr_t me, uint32_t stateId, char_t* nonTerminal) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    IEcoSet2* pICurrentSet = 0;
    IEcoSet2* pNextSet = 0;
    int32_t nextStateIdx = -1; /* -1 означает отсутствие перехода */

    /* 1. Валидация входных параметров */
    if (pCMe == 0 || pCMe->m_pIItemSets == 0 || nonTerminal == 0) {
        return -1;
    }

    /* Проверка индекса состояния */
    if (stateId >= pCMe->m_pIItemSets->pVTbl->Count(pCMe->m_pIItemSets)) {
        return -1;
    }

    /* 2. Извлекаем набор ситуаций (ItemSet) текущего состояния */
    pICurrentSet = (IEcoSet2*)pCMe->m_pIItemSets->pVTbl->Item(pCMe->m_pIItemSets, stateId);
    if (pICurrentSet == 0) {
        return -1;
    }

    /* 3. Вычисляем целевое состояние с помощью функции GoTo */
    /* В LR-анализе GOTO(I, X) = Closure({ [A -> alpha X . beta, a] | [A -> alpha . X beta, a] in I }) */
    pNextSet = CEcoLR1_A441A18E_GoTo(pCMe, pICurrentSet, nonTerminal);

    if (pNextSet != 0) {
        /* Если переход существует и результирующее множество не пустое */
        if (pNextSet->pVTbl->Count(pNextSet) > 0) {
            /* Ищем индекс полученного множества в общем списке состояний */
            nextStateIdx = CEcoLR1_A441A18E_FindSetIndex(pCMe, pNextSet);
        }
        
        /* Освобождаем временное множество, созданное функцией GoTo */
        pNextSet->pVTbl->Release(pNextSet);
    }

    /* Возвращаем индекс состояния или -1, если переход невозможен */
    return nextStateIdx;
}


static IEcoFSM1StateMachine* ECOCALLMETHOD CEcoLR1_A441A18E_get_StateMachine(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    
    if (pCMe == 0) return 0;
    
    /* В вашем PDA есть FSM, возвращаем его через интерфейс PDA */
    if (pCMe->m_pIPDA) {
        return pCMe->m_pIPDA->pVTbl->get_FSM(pCMe->m_pIPDA);
    }

    return 0;
}

static IEcoList1* ECOCALLMETHOD CEcoLR1_A441A18E_get_Reduce(/* in */ IEcoParser1LRkPtr_t me, uint32_t stateId, char_t* nextTerm) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}

static IEcoData1Table* ECOCALLMETHOD CEcoLR1_A441A18E_get_ActionTable(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    
    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}

static IEcoParser1ActionProcessing* ECOCALLMETHOD CEcoLR1_A441A18E_get_ActionProcessing(/* in */ IEcoParser1LRkPtr_t me) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    CEcoLR1ActionProcessing_A441A18E* pCObj = 0;
    int16_t result = 0;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    /* Выделение памяти */
    pCObj = (CEcoLR1ActionProcessing_A441A18EPtr_t)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoLR1ActionProcessing_A441A18E));
    
    /* Копирование vtbl и данных */
    pCObj = (CEcoLR1ActionProcessing_A441A18EPtr_t)pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, pCObj, &g_xCEcoLR1ActionProcessing_A441A18E, sizeof(CEcoLR1ActionProcessing_A441A18E));
   
    /* Создание (Create) */
    result = pCObj->Create(pCObj, (IEcoUnknown*)pCMe->m_pISys, 0);
    if (result != 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCObj);
        return 0;
    }
    
    /* Инициализация */
    result = pCObj->Init(pCObj, (IEcoUnknown*)pCMe->m_pISys, pCMe->m_pIPDA->pVTbl->CreateProcessing(pCMe->m_pIPDA));
    if (result != 0) {
        pCObj->Delete(pCObj);
        return 0;
    }

    return (IEcoParser1ActionProcessing*)pCObj;
}

/*
 *
 * <summary>
 *   Init Function
 * </summary>
 *
 * <description>
 *   Instance initialization function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD initCEcoLR1_A441A18E(/*in*/ CEcoLR1_A441A18EPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoLR1_A441A18E* pCMe = (CEcoLR1_A441A18E*)me;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = -1;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	
    
    /* Pointer Validation */
    if (me == 0 ) {
        return result;
    }

    /* Storing the pointer to the system interface */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;
    
    /* Getting the interface for working with the interface bus */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pCMe->m_pIBus);
   
    /* Getting the component ID for working with memory */
    result = pCMe->m_pIBus->pVTbl->QueryInterface(pCMe->m_pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Getting the memory allocator interface */
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);
    if (result != 0 || pCMe->m_pIMem == 0) {
        return -1;
    }
        
    /* Getting the string interface */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**) &pCMe->m_pIStr);
    
    /* Создаем PDA */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoPDA1, 0, &IID_IEcoPDA1, (void**) &pCMe->m_pIPDA);
   
    /* 1. Множество FIRST: Ключ - Строка, Значение - Объект (IEcoSet2) */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoMap2, 0, &IID_IEcoMap2, (void**)&pCMe->m_pIFirst);
    pCMe->m_pIFirst->pVTbl->InitByType(pCMe->m_pIFirst, ECO_COMPARATOR_1_POINTER_T, ECO_COMPARATOR_1_OBJECT_T);
    
    /* 2. Множество FOLLOW: Ключ - Строка, Значение - Объект (IEcoSet2) */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoMap2, 0, &IID_IEcoMap2, (void**)&pCMe->m_pIFollow);
    pCMe->m_pIFollow->pVTbl->InitByType(pCMe->m_pIFollow, ECO_COMPARATOR_1_POINTER_T, ECO_COMPARATOR_1_OBJECT_T);
    
    /* 3. Карта символов: Ключ - Строка, Значение - Объект (IEcoFL1SymbolSet) */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoMap2, 0, &IID_IEcoMap2, (void**)&pCMe->m_pSymbolMap);
    pCMe->m_pSymbolMap->pVTbl->InitByType(pCMe->m_pSymbolMap, ECO_COMPARATOR_1_POINTER_T, ECO_COMPARATOR_1_OBJECT_T);
    
    /* 4. Карта индексов состояний: Ключ - Объект (IEcoSet2), Значение - Число (int32) */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoMap2, 0, &IID_IEcoMap2, (void**)&pCMe->m_pIItemSetIdxMap);
    pCMe->m_pIItemSetIdxMap->pVTbl->InitByType(pCMe->m_pIItemSetIdxMap, ECO_COMPARATOR_1_OBJECT_T, ECO_COMPARATOR_1_INT32_T);
    
    /* Инициализируем списки */
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pCMe->m_pIItemSets);
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pCMe->m_pIClosureList);
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pCMe->m_pIGoTo);
    
    return 0;
}

/*
 *
 * <summary>
 *   Create Function
 * </summary>
 *
 * <description>
 *   Instance creation function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD createCEcoLR1_A441A18E(/* in */ CEcoLR1_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
    int16_t result = ERR_ECO_POINTER;
    
    /* Pointer Validation */
    if (pCMe == 0) {
        return result; /* ERR_ECO_POINTER */
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Delete Function
 * </summary>
 *
 * <description>
 *   Instance freeing function
 * </description>
 *
 */
static void ECOCALLMETHOD deleteCEcoLR1_A441A18E(/* in */ CEcoLR1_A441A18EPtr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;
    if (pCMe != 0 ) {
        CEcoLR1_A441A18E_ClearActions(pCMe);
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoParser1LRk Virtual Table */
IEcoParser1LRkVTbl g_x1DB8846466B14AC699B1BBD4F2AE2F9BVTbl_A441A18E = {
    CEcoLR1_A441A18E_QueryInterface,
    CEcoLR1_A441A18E_AddRef,
    CEcoLR1_A441A18E_Release,
    CEcoLR1_A441A18E_InitByGrammar,
    CEcoLR1_A441A18E_get_Lookahead,
    CEcoLR1_A441A18E_get_Grammar,
    CEcoLR1_A441A18E_get_InternalGrammar,
    CEcoLR1_A441A18E_get_First,
    CEcoLR1_A441A18E_get_Follow,
    CEcoLR1_A441A18E_get_ItemSets,
    CEcoLR1_A441A18E_get_Action,
    CEcoLR1_A441A18E_get_Goto,
    CEcoLR1_A441A18E_get_StateMachine,
    CEcoLR1_A441A18E_get_Reduce,
    CEcoLR1_A441A18E_get_ActionTable,
    CEcoLR1_A441A18E_get_ActionProcessing
};

/* Object Instance */
CEcoLR1_A441A18E g_xCEcoLR1_A441A18E = {
    &g_x1DB8846466B14AC699B1BBD4F2AE2F9BVTbl_A441A18E,
    initCEcoLR1_A441A18E,
    createCEcoLR1_A441A18E,
    deleteCEcoLR1_A441A18E,
    CEcoLR1_A441A18E_BuildFL1Alphabet,
    CEcoLR1_A441A18E_BuildFirst,
    CEcoLR1_A441A18E_BuildFollow,
    CEcoLR1_A441A18E_BuildItemSets,
    CEcoLR1_A441A18E_ConfigurePDAOperations,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_pIBus */
    0, /* m_pIStr */
    0, /* m_pIExtGrammar */
    0, /* m_nLookahead */
    0, /* m_pIPDA */
    0, /* m_pIFirst */
    0, /* m_pIFollow */
    0, /* m_pSymbolMap */
    0, /* m_pIItemSets */
    0, /* m_pIClosureList */
    0, /* m_pIItemSetIdxMap */
    0 /* m_pIGoTo */
};