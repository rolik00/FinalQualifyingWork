/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBRE1RegEx_0E0B7D40
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBRE1RegEx_0E0B7D40
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir. All rights reserved.
 * </author>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoBRE1RegEx.h"
#include "IEcoFSM1.h"
#include "IdEcoFSM1.h"
#include "IEcoFL1.h"
#include "CEcoBRE1EnumMatches.h"
#include <string.h>

extern CEcoBRE1EnumMatches_0E0B7D40 g_xCEcoBRE1EnumMatches_0E0B7D40;

/* Вспомогательная функция для инициализации множества состояний */
static void InitStateSet(StateSet* set, CEcoBRE1RegEx_0E0B7D40* pRegEx) {
    set->states = 0;
    set->count = 0;
    set->capacity = 0;
}

/* Вспомогательная функция для добавления состояния в множество */
static void AddStateToSet(StateSet* set, int16_t stateId, CEcoBRE1RegEx_0E0B7D40* pRegEx) {
    uint32_t i = 0;
    
    for (i = 0; i < set->count; i++) {
        if (set->states[i] == stateId) {
            return;
        }
    }
    
    if (set->count >= set->capacity) {
        uint32_t newCapacity = set->capacity == 0 ? 16 : set->capacity * 2;
        int16_t* newStates = (int16_t*)pRegEx->m_pIMem->pVTbl->Alloc(pRegEx->m_pIMem, newCapacity * sizeof(int16_t));
        
        if (newStates == 0) return;
        
        if (set->states) {
            memcpy(newStates, set->states, set->count * sizeof(int16_t));
            pRegEx->m_pIMem->pVTbl->Free(pRegEx->m_pIMem, set->states);
        }
        
        set->states = newStates;
        set->capacity = newCapacity;
    }
    
    set->states[set->count++] = stateId;
}

/* Вспомогательная функция для освобождения множества состояний */
static void FreeStateSet(StateSet* set, CEcoBRE1RegEx_0E0B7D40* pRegEx) {
    if (set->states) {
        pRegEx->m_pIMem->pVTbl->Free(pRegEx->m_pIMem, set->states);
    }
    set->states = 0;
    set->count = 0;
    set->capacity = 0;
}

/* Вспомогательная функция для копирования множества состояний */
static void CopyStateSet(StateSet* dest, StateSet* src, CEcoBRE1RegEx_0E0B7D40* pRegEx) {
    uint32_t i = 0;
    
    FreeStateSet(dest, pRegEx);
    
    for (i = 0; i < src->count; i++) {
        AddStateToSet(dest, src->states[i], pRegEx);
    }
}

/* Вспомогательная функция для проверки символа по событию */
static int MatchSymbol(IEcoFSM1Event* pEvent, char c) {
    IEcoList1* pSymbolSets = 0;
    uint32_t count = 0;
    IEcoFL1SymbolSet* pSymbolSet = 0;
    uint32_t i = 0;
    int result = 0;

    if (pEvent == 0) return 0;

    pSymbolSets = pEvent->pVTbl->get_SymbolSets(pEvent);
    if (pSymbolSets == 0) return 0;

    count = pSymbolSets->pVTbl->Count(pSymbolSets);

    for (i = 0; i < count; i++) {
        pSymbolSet = (IEcoFL1SymbolSet*)pSymbolSets->pVTbl->Item(pSymbolSets, i);
        if (pSymbolSet) {
            if (pSymbolSet->pVTbl->IsExist(pSymbolSet, (byte_t*)&c, 8, 0)) {
                result = 1;
                break;
            }
        }
    }

    return result;
}

/*
 * Вычисляет ε-замыкание множества состояний
 */
static void GetEpsilonClosure(IEcoFSM1StateMachine* pStateMachine, StateSet* input, StateSet* closure, CEcoBRE1RegEx_0E0B7D40* pRegEx) {
    IEcoList1* pTransitions = 0;
    uint32_t transCount = 0;
    IEcoFSM1Transition* pTransition = 0;
    IEcoFSM1Event* pEvent = 0;
    IEcoFSM1State* pSource = 0;
    IEcoFSM1State* pTarget = 0;
    uint32_t i = 0, j = 0;
    int16_t sourceId = 0, targetId = 0;
    int changed = 1;
	uint32_t k = 0;
	int found = 0;
    
    CopyStateSet(closure, input, pRegEx);
    
    pTransitions = pStateMachine->pVTbl->get_Transitions(pStateMachine);
    if (pTransitions == 0) return;
    
    transCount = pTransitions->pVTbl->Count(pTransitions);
    
    while (changed) {
        changed = 0;
        
        for (i = 0; i < closure->count; i++) {
            sourceId = closure->states[i];
            
            for (j = 0; j < transCount; j++) {
                pTransition = (IEcoFSM1Transition*)pTransitions->pVTbl->Item(pTransitions, j);
                if (pTransition == 0) continue;
                
                pSource = pTransition->pVTbl->get_Source(pTransition);
                if (pSource == 0 || pSource->pVTbl->get_Id(pSource) != sourceId) continue;
                
                pEvent = pTransition->pVTbl->get_Event(pTransition);
                if (pEvent == 0) continue;
                
                if (pEvent->pVTbl->IsNull(pEvent)) {
                    pTarget = pTransition->pVTbl->get_Target(pTransition);
                    if (pTarget == 0) continue;
                    
                    targetId = pTarget->pVTbl->get_Id(pTarget);
                    
                    k = 0;
                    found = 0;
                    for (k = 0; k < closure->count; k++) {
                        if (closure->states[k] == targetId) {
                            found = 1;
                            break;
                        }
                    }
                    
                    if (!found) {
                        AddStateToSet(closure, targetId, pRegEx);
                        changed = 1;
                    }
                }
            }
        }
    }
}

/*
 * Вычисляет множество состояний, достижимых по символу
 */
static void Move(IEcoFSM1StateMachine* pStateMachine, StateSet* from, char c, StateSet* to, CEcoBRE1RegEx_0E0B7D40* pRegEx) {
    IEcoList1* pTransitions = 0;
    uint32_t transCount = 0;
    IEcoFSM1Transition* pTransition = 0;
    IEcoFSM1Event* pEvent = 0;
    IEcoFSM1State* pSource = 0;
    IEcoFSM1State* pTarget = 0;
    uint32_t i = 0, j = 0;
    int16_t sourceId = 0, targetId = 0;
    
    FreeStateSet(to, pRegEx);
    
    pTransitions = pStateMachine->pVTbl->get_Transitions(pStateMachine);
    if (pTransitions == 0) return;
    
    transCount = pTransitions->pVTbl->Count(pTransitions);
    
    for (i = 0; i < from->count; i++) {
        sourceId = from->states[i];
        
        for (j = 0; j < transCount; j++) {
            pTransition = (IEcoFSM1Transition*)pTransitions->pVTbl->Item(pTransitions, j);
            if (pTransition == 0) continue;
            
            pSource = pTransition->pVTbl->get_Source(pTransition);
            if (pSource == 0 || pSource->pVTbl->get_Id(pSource) != sourceId) continue;
            
            pEvent = pTransition->pVTbl->get_Event(pTransition);
            if (pEvent == 0 || pEvent->pVTbl->IsNull(pEvent)) continue;
            
            if (MatchSymbol(pEvent, c)) {
                pTarget = pTransition->pVTbl->get_Target(pTransition);
                if (pTarget == 0) continue;
                
                targetId = pTarget->pVTbl->get_Id(pTarget);
                AddStateToSet(to, targetId, pRegEx);
            }
        }
    }
}

/*
 * Проверяет, содержит ли множество состояний финальное состояние
 */
static int ContainsFinalState(IEcoFSM1StateMachine* pStateMachine, StateSet* set) {
    IEcoList1* pStates = 0;
    uint32_t stateCount = 0;
    IEcoFSM1State* pState = 0;
    uint32_t i = 0, j = 0;
    int16_t stateId = 0;
    
    pStates = pStateMachine->pVTbl->get_States(pStateMachine);
    if (pStates == 0) return 0;
    
    stateCount = pStates->pVTbl->Count(pStates);
    
    for (i = 0; i < set->count; i++) {
        stateId = set->states[i];
        
        for (j = 0; j < stateCount; j++) {
            pState = (IEcoFSM1State*)pStates->pVTbl->Item(pStates, j);
            if (pState && pState->pVTbl->get_Id(pState) == stateId) {
                if (pState->pVTbl->IsFinal(pState)) {
                    return 1;
                }
                break;
            }
        }
    }
    
    return 0;
}

/*
 *
 * <summary>
 *   Функция IsMatch
 * </summary>
 *
 * <description>
 *   Проверяет полное совпадение строки шаблону
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_IsMatch(/* in */ IEcoRegEx1Ptr_t me, /* in */ voidptr_t string, /* in */ uint32_t sizeInBytes, /* in */ uint32_t flags) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;
    IEcoFSM1StateMachine* pStateMachine = 0;
    char* pStr = (char*)string;
    int32_t i = 0;
    int32_t len = sizeInBytes == 0 ? (int32_t)strlen(pStr) : sizeInBytes;
    int16_t result = 0;
    
    StateSet current, next, closure;
    IEcoFSM1State* pStartState = 0;
    int16_t startStateId = 0;

    if (me == 0 || string == 0) {
        return 0;
    }

    pStateMachine = pCMe->m_pStateMachine;
    if (pStateMachine == 0 || pCMe->m_pStartState == 0) {
        return 0;
    }

    InitStateSet(&current, pCMe);
    InitStateSet(&next, pCMe);
    InitStateSet(&closure, pCMe);

    startStateId = pCMe->m_pStartState->pVTbl->get_Id(pCMe->m_pStartState);
    AddStateToSet(&current, startStateId, pCMe);
    
    GetEpsilonClosure(pStateMachine, &current, &closure, pCMe);
    CopyStateSet(&current, &closure, pCMe);

    for (i = 0; i < len; i++) {
        Move(pStateMachine, &current, pStr[i], &next, pCMe);
        
        if (next.count == 0) {
            FreeStateSet(&current, pCMe);
            FreeStateSet(&next, pCMe);
            FreeStateSet(&closure, pCMe);
            return 0;
        }
        
        GetEpsilonClosure(pStateMachine, &next, &closure, pCMe);
        CopyStateSet(&current, &closure, pCMe);
    }

    result = ContainsFinalState(pStateMachine, &current);

    FreeStateSet(&current, pCMe);
    FreeStateSet(&next, pCMe);
    FreeStateSet(&closure, pCMe);

    return result;
}

/*
 *
 * <summary>
 *   Функция Match
 * </summary>
 *
 * <description>
 *   Ищет первое вхождение шаблона в строку
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_Match(/* in */ IEcoRegEx1Ptr_t me, /* in */ voidptr_t string,  /* in */ uint32_t sizeInBytes, /* in */ uint32_t flags, /* out */ struct EcoRegEx1Match** match) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;
    IEcoFSM1StateMachine* pStateMachine = 0;
	EcoRegEx1Match* pMatch = 0;
    StateSet current, next, closure;
    char* pStr = (char*)string;
    int32_t len = sizeInBytes == 0 ? (int32_t)strlen(pStr) : sizeInBytes;
    int32_t start = 0, i = 0;
    int32_t bestLength = 0;
    int16_t found = 0, startStateId = 0;

    if (me == 0 || string == 0 || match == 0) {
        return -1;
    }

    *match = 0;

    pStateMachine = pCMe->m_pStateMachine;
    if (pStateMachine == 0 || pCMe->m_pStartState == 0) {
        return -1;
    }

    InitStateSet(&current, pCMe);
    InitStateSet(&next, pCMe);
    InitStateSet(&closure, pCMe);

    startStateId = pCMe->m_pStartState->pVTbl->get_Id(pCMe->m_pStartState);

    for (start = 0; start < len && !found; start++) {
        FreeStateSet(&current, pCMe);
        AddStateToSet(&current, startStateId, pCMe);
        
        GetEpsilonClosure(pStateMachine, &current, &closure, pCMe);
        CopyStateSet(&current, &closure, pCMe);

        if (ContainsFinalState(pStateMachine, &current)) {
            bestLength = 0;
            found = 1;
            break;
        }

        for (i = start; i < len; i++) {
            Move(pStateMachine, &current, pStr[i], &next, pCMe);
            
            if (next.count == 0) {
                break;
            }
            
            GetEpsilonClosure(pStateMachine, &next, &closure, pCMe);
            CopyStateSet(&current, &closure, pCMe);

            if (ContainsFinalState(pStateMachine, &current)) {
                bestLength = i - start + 1;
                found = 1;
            }
        }

		if (found) {
            break;
        }
    }

	if (found && bestLength >= 0) {
        pMatch = (EcoRegEx1Match*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoRegEx1Match));
        if (pMatch == 0) {
            FreeStateSet(&current, pCMe);
            FreeStateSet(&next, pCMe);
            FreeStateSet(&closure, pCMe);
            return -1;
        }

        pMatch->index = start;
        pMatch->length = bestLength;
        *match = pMatch;
        
        FreeStateSet(&current, pCMe);
        FreeStateSet(&next, pCMe);
        FreeStateSet(&closure, pCMe);
        return 0;
    }

    FreeStateSet(&current, pCMe);
    FreeStateSet(&next, pCMe);
    FreeStateSet(&closure, pCMe);

    return -1;
}

/*
 *
 * <summary>
 *   Функция Matches
 * </summary>
 *
 * <description>
 *   Возвращает итератор для всех совпадений шаблона в строке
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_Matches(/* in */ IEcoRegEx1Ptr_t me, /* in */ voidptr_t str, /* in */ uint32_t sizeInBytes, /* in */ uint32_t flags, /* out */ IEcoRegEx1EnumMatchesPtr_t* ppEnum) {
	CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;
    IEcoFSM1StateMachine* fsm = pCMe->m_pStateMachine;
    CEcoBRE1EnumMatches_0E0B7D40* en = 0;
    EcoRegEx1Match* matches = 0;
    EcoRegEx1Match* newm = 0;
    StateSet curr, nexts, eps;
    char* text = (char*)str;
    int32_t len = sizeInBytes ? (int32_t)sizeInBytes : (int32_t)strlen(text);
    int32_t pos = 0, match_start = 0, match_end = -1, i = 0;
    int16_t startId = 0, hr = 0;
    uint32_t capacity = 0, count = 0, length = 0, newcap = 0;

    if (!pCMe || !str || !ppEnum) return ERR_ECO_POINTER;
    if (!fsm || !pCMe->m_pStartState) return ERR_ECO_NOINTERFACE;

    *ppEnum = 0;

    InitStateSet(&curr,  pCMe);
    InitStateSet(&nexts, pCMe);
    InitStateSet(&eps,   pCMe);

    startId = pCMe->m_pStartState->pVTbl->get_Id(pCMe->m_pStartState);

    while (pos <= len) {
        match_start = pos;
        match_end = -1;

        FreeStateSet(&curr, pCMe);
        AddStateToSet(&curr, startId, pCMe);
        GetEpsilonClosure(fsm, &curr, &eps, pCMe);
        CopyStateSet(&curr, &eps, pCMe);

        if (ContainsFinalState(fsm, &curr)) {
            match_end = pos;
        }

        for (i = pos; i < len; i++) {
            Move(fsm, &curr, text[i], &nexts, pCMe);
            if (nexts.count == 0) break;

            GetEpsilonClosure(fsm, &nexts, &eps, pCMe);
            CopyStateSet(&curr, &eps, pCMe);

            if (ContainsFinalState(fsm, &curr)) {
                match_end = i + 1;
            }
        }

        if (match_end >= match_start) {
            length = (uint32_t)(match_end - match_start);

            if (count >= capacity) {
                newcap = capacity ? capacity * 2 : 8;
                newm = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, newcap * sizeof(EcoRegEx1Match));
                if (newm == 0) goto nomem;

                if (matches) {
                    memcpy(newm, matches, count * sizeof(EcoRegEx1Match));
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, matches);
                }
                matches = newm;
                capacity = newcap;
            }

            matches[count].index   = (uint32_t)match_start;
            matches[count].length  = length;
            matches[count].pValue  = text + match_start;
            matches[count].cCookie = 0;
            count++;

            if (length > 0) {
                pos = match_end;           
			} else {
                pos++;                   
            }
        }
        else {
            pos++;  
        }
    }

    en = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBRE1EnumMatches_0E0B7D40));
    if (!en) goto nomem;

    memcpy(en, &g_xCEcoBRE1EnumMatches_0E0B7D40, sizeof(*en));
    en->m_cRef = 1;

    hr = en->Init(en, (IEcoUnknownPtr_t)pCMe->m_pISys);
    if (hr != ERR_ECO_SUCCESES) {
        if (matches) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, matches);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, en);
        goto nomem;
    }

    en->m_matches = matches;
    en->m_count = count;
    en->m_current = 0;

    *ppEnum = (IEcoRegEx1EnumMatchesPtr_t)en;

    FreeStateSet(&curr,  pCMe);
    FreeStateSet(&nexts, pCMe);
    FreeStateSet(&eps,   pCMe);
	return ERR_ECO_SUCCESES;

nomem:
    if (matches) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, matches);
    FreeStateSet(&curr,  pCMe);
    FreeStateSet(&nexts, pCMe);
    FreeStateSet(&eps,   pCMe);
    return -1;  
}

/*
 *
 * <summary>
 *   Функция Split
 * </summary>
 *
 * <description>
 *   Разделяет строку по шаблону и возвращает массив подстрок
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_Split(/* in */ IEcoRegEx1Ptr_t me, /* in */ voidptr_t str, /* in */ uint32_t sizeInBytes, /* in */ uint32_t flags, /* out */ voidptr_t* ppEnumStrings) {
	CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;
    IEcoFSM1StateMachine* pStateMachine = 0;
    SplitResult* pResult = 0;
    StateSet current, next, closure;
    char* pStr = (char*)str;
	char** newStrings;
    int32_t len = sizeInBytes == 0 ? (int32_t)strlen(pStr) : sizeInBytes;
    int32_t start = 0, i = 0, lastPos = 0;
	uint32_t substrLen = 0, newCapacity = 0;
    int16_t startStateId = 0;
	int found = 0, matchLength = 0;

    if (me == 0 || str == 0 || ppEnumStrings == 0) {
        return ERR_ECO_POINTER;
    }

    *ppEnumStrings = 0;

	pStateMachine = pCMe->m_pStateMachine;
    if (pStateMachine == 0 || pCMe->m_pStartState == 0) {
        return ERR_ECO_NOINTERFACE;
    }

	pResult = (SplitResult*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(SplitResult));
    if (pResult == 0) {
        return -1;
    }
    pResult->strings = 0;
    pResult->count = 0;
    pResult->capacity = 0;

	InitStateSet(&current, pCMe);
    InitStateSet(&next, pCMe);
    InitStateSet(&closure, pCMe);

    startStateId = pCMe->m_pStartState->pVTbl->get_Id(pCMe->m_pStartState);

	for (start = 0; start < len; start++) {
        found = 0;
        matchLength = 0;
        
        FreeStateSet(&current, pCMe);
        AddStateToSet(&current, startStateId, pCMe);
        
        GetEpsilonClosure(pStateMachine, &current, &closure, pCMe);
        CopyStateSet(&current, &closure, pCMe);

        for (i = start; i < len; i++) {
            Move(pStateMachine, &current, pStr[i], &next, pCMe);
            
            if (next.count == 0) {
                break;
            }
            
            GetEpsilonClosure(pStateMachine, &next, &closure, pCMe);
            CopyStateSet(&current, &closure, pCMe);

            if (ContainsFinalState(pStateMachine, &current)) {
                matchLength = i - start + 1;
                found = 1;
            }
        }

        if (found) {
            if (lastPos < start) {
                substrLen = start - lastPos;
                
                if (pResult->count >= pResult->capacity) {
                    newCapacity = pResult->capacity == 0 ? 8 : pResult->capacity * 2;
                    newStrings = (char**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, newCapacity * sizeof(char*));
                    if (newStrings == 0) {
                        break;
                    }
                    if (pResult->strings) {
                        memcpy(newStrings, pResult->strings, pResult->count * sizeof(char*));
                        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pResult->strings);
                    }
                    pResult->strings = newStrings;
                    pResult->capacity = newCapacity;
                }
                
                pResult->strings[pResult->count] = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, substrLen + 1);
                if (pResult->strings[pResult->count]) {
                    memcpy(pResult->strings[pResult->count], pStr + lastPos, substrLen);
                    pResult->strings[pResult->count][substrLen] = '\0';
                    pResult->count++;
                }
            }
            
            start += matchLength - 1;
            lastPos = start + 1;
        }
    }

	if (lastPos < len) {
        substrLen = len - lastPos;
        
        if (pResult->count >= pResult->capacity) {
            newCapacity = pResult->capacity == 0 ? 8 : pResult->capacity * 2;
            newStrings = (char**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, newCapacity * sizeof(char*));
            if (newStrings) {
                if (pResult->strings) {
                    memcpy(newStrings, pResult->strings, pResult->count * sizeof(char*));
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pResult->strings);
                }
                pResult->strings = newStrings;
                pResult->capacity = newCapacity;
            }
        }
        
        if (pResult->count < pResult->capacity) {
            pResult->strings[pResult->count] = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, substrLen + 1);
            if (pResult->strings[pResult->count]) {
                memcpy(pResult->strings[pResult->count], pStr + lastPos, substrLen);
                pResult->strings[pResult->count][substrLen] = '\0';
                pResult->count++;
            }
        }
    } else if (lastPos == len && pResult->count == 0) {
        pResult->strings = (char**)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(char*));
        if (pResult->strings) {
            pResult->strings[0] = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 1);
            if (pResult->strings[0]) {
                pResult->strings[0][0] = '\0';
                pResult->count = 1;
                pResult->capacity = 1;
            }
        }
    }

    FreeStateSet(&current, pCMe);
    FreeStateSet(&next, pCMe);
    FreeStateSet(&closure, pCMe);

    *ppEnumStrings = pResult;

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Функция Replace
 * </summary>
 *
 * <description>
 *   Заменяет все вхождения шаблона на указанную строку
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_Replace(/* in */ IEcoRegEx1Ptr_t me, /* in */ voidptr_t str, /* in */ uint32_t sizeInBytes, /* in */ voidptr_t replacement, /* in */ uint32_t repSizeInBytes, /* in */ uint32_t flags, /* out */ voidptr_t* ppResultStr, /* out */ uint32_t* pResSizeInBytes) {
	CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;
    IEcoFSM1StateMachine* pStateMachine = 0;
	StateSet current, next, closure;
    char* pStr = (char*)str;
    char* pRep = (char*)replacement;
	char *result = 0, *temp = 0;
    int32_t len = sizeInBytes == 0 ? (int32_t)strlen(pStr) : sizeInBytes;
    int32_t repLen = repSizeInBytes == 0 ? (int32_t)strlen(pRep) : repSizeInBytes;
    int32_t start = 0, i = 0, lastPos = 0;
    int16_t startStateId = 0;
    uint32_t resultSize = 0, resultCapacity = len + 1; 
    uint32_t tempPos = 0, copyLen = 0;
	int found = 0, matchLength = 0;

    if (me == 0 || str == 0 || ppResultStr == 0 || pResSizeInBytes == 0) {
        return ERR_ECO_POINTER;
    }

	*ppResultStr = 0;
    *pResSizeInBytes = 0;

    pStateMachine = pCMe->m_pStateMachine;
    if (pStateMachine == 0 || pCMe->m_pStartState == 0) {
        return ERR_ECO_NOINTERFACE;
    }

    result = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, resultCapacity);
    if (result == 0) {
        return -1;
    }

	InitStateSet(&current, pCMe);
    InitStateSet(&next, pCMe);
    InitStateSet(&closure, pCMe);

    startStateId = pCMe->m_pStartState->pVTbl->get_Id(pCMe->m_pStartState);

	for (start = 0; start < len; start++) {
        found = 0;
        matchLength = 0;
        
        FreeStateSet(&current, pCMe);
        AddStateToSet(&current, startStateId, pCMe);
        
        GetEpsilonClosure(pStateMachine, &current, &closure, pCMe);
        CopyStateSet(&current, &closure, pCMe);

        for (i = start; i < len; i++) {
            Move(pStateMachine, &current, pStr[i], &next, pCMe);
            
            if (next.count == 0) {
                break;
            }
            
            GetEpsilonClosure(pStateMachine, &next, &closure, pCMe);
            CopyStateSet(&current, &closure, pCMe);

            if (ContainsFinalState(pStateMachine, &current)) {
                matchLength = i - start + 1;
                found = 1;
            }
        }

        if (found) {
            copyLen = start - lastPos;
            if (copyLen > 0) {
                if (tempPos + copyLen >= resultCapacity) {
                    resultCapacity = (tempPos + copyLen) * 2;
                    temp = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, resultCapacity);
                    if (temp == 0) {
                        break;
                    }
                    memcpy(temp, result, tempPos);
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, result);
                    result = temp;
                }
                memcpy(result + tempPos, pStr + lastPos, copyLen);
                tempPos += copyLen;
            }
            
            if (repLen > 0) {
                if (tempPos + repLen >= resultCapacity) {
                    resultCapacity = (tempPos + repLen) * 2;
                    temp = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, resultCapacity);
                    if (temp == 0) {
                        break;
                    }
                    memcpy(temp, result, tempPos);
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, result);
                    result = temp;
                }
                memcpy(result + tempPos, pRep, repLen);
                tempPos += repLen;
            }
            
            start += matchLength - 1;
            lastPos = start + 1;
        }
    }

	if (lastPos < len) {
        copyLen = len - lastPos;
        if (tempPos + copyLen >= resultCapacity) {
            resultCapacity = tempPos + copyLen + 1;
            temp = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, resultCapacity);
            if (temp) {
                memcpy(temp, result, tempPos);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, result);
                result = temp;
            }
        }
        memcpy(result + tempPos, pStr + lastPos, copyLen);
        tempPos += copyLen;
    }

	FreeStateSet(&current, pCMe);
    FreeStateSet(&next, pCMe);
    FreeStateSet(&closure, pCMe);

    if (tempPos >= resultCapacity) {
        resultCapacity = tempPos + 1;
        temp = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, resultCapacity);
        if (temp) {
            memcpy(temp, result, tempPos);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, result);
            result = temp;
        }
    }
    result[tempPos] = '\0';

	*ppResultStr = result;
    *pResSizeInBytes = tempPos;

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoRegEx1 interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_QueryInterface(/* in */ IEcoRegEx1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if (IsEqualUGUID(riid, &IID_IEcoRegEx1) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1;
        pCMe->m_pVTblIEcoRegEx1->AddRef((IEcoRegEx1*)pCMe);
    }
	else if (IsEqualUGUID(riid, &IID_IEcoFSM1StateMachine)) {
        *ppv = pCMe->m_pStateMachine;
        pCMe->m_pVTblIEcoRegEx1->AddRef((IEcoRegEx1*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1;
        pCMe->m_pVTblIEcoRegEx1->AddRef((IEcoRegEx1*)pCMe);
    }
    else {
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
 *   AddRef function for the IEcoRegEx1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_AddRef(/* in */ IEcoRegEx1Ptr_t me) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1;
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
 *   Release function for the IEcoRegEx1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1RegEx_0E0B7D40_Release(/* in */ IEcoRegEx1Ptr_t me) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1;
    }

    /* Decrementing the component's reference count */
    --pCMe->m_cRef;
    /* If the count is zero, free the instance data */
    if (pCMe->m_cRef == 0) {
        pCMe->Delete(pCMe);
        return 0;
    }
    return pCMe->m_cRef;
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
static int16_t ECOCALLMETHOD initCEcoBRE1RegEx_0E0B7D40(/*in*/ CEcoBRE1RegEx_0E0B7D40Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBRE1RegEx_0E0B7D40* pCMe = (CEcoBRE1RegEx_0E0B7D40*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = ERR_ECO_POINTER;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    /* Pointer Validation */
    if (me == 0) {
        return result;
    }

    /* Storing the pointer to the system interface */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Getting the interface for working with the interface bus */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0) {
        return result;
    }

    /* Getting the component ID for working with memory */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Getting the memory allocator interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);
    /* Check */
    if (result != 0 || pCMe->m_pIMem == 0) {
        result = ERR_ECO_GET_MEMORY_ALLOCATOR;
        pIBus->pVTbl->Release(pIBus);
        return result;
    }

    /* Freeing */
    pIBus->pVTbl->Release(pIBus);

    return result;
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
static int16_t ECOCALLMETHOD createCEcoBRE1RegEx_0E0B7D40(/* in */ CEcoBRE1RegEx_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
    int16_t result = ERR_ECO_POINTER;

    /* Pointer Validation */
    if (pCMe == 0) {
        return result;
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
static void ECOCALLMETHOD deleteCEcoBRE1RegEx_0E0B7D40(/* in */ CEcoBRE1RegEx_0E0B7D40Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0) {
        pIMem = pCMe->m_pIMem;

        /* Freeing resources */
        if (pCMe->m_pRoot != 0) {
            pCMe->m_pRoot->pVTbl->Release(pCMe->m_pRoot);
        }
        if (pCMe->m_pStateMachine != 0) {
            pCMe->m_pStateMachine->pVTbl->Release(pCMe->m_pStateMachine);
        }
        if (pCMe->m_pFSM != 0) {
            pCMe->m_pFSM->pVTbl->Release(pCMe->m_pFSM);
        }
        if (pCMe->m_pStartState != 0) {
            pCMe->m_pStartState->pVTbl->Release(pCMe->m_pStartState);
        }
        if (pCMe->m_Name != 0) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if (pCMe->m_pISys != 0) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoRegEx1 Virtual Table */
IEcoRegEx1VTbl g_xCEcoBRE1RegEx_0E0B7D40VTbl = {
    CEcoBRE1RegEx_0E0B7D40_QueryInterface,
    CEcoBRE1RegEx_0E0B7D40_AddRef,
    CEcoBRE1RegEx_0E0B7D40_Release,
    CEcoBRE1RegEx_0E0B7D40_IsMatch,
    CEcoBRE1RegEx_0E0B7D40_Match,
    CEcoBRE1RegEx_0E0B7D40_Matches,
    CEcoBRE1RegEx_0E0B7D40_Split,
    CEcoBRE1RegEx_0E0B7D40_Replace
};

/* Object Instance */
CEcoBRE1RegEx_0E0B7D40 g_xCEcoBRE1RegEx_0E0B7D40 = {
    &g_xCEcoBRE1RegEx_0E0B7D40VTbl,
    initCEcoBRE1RegEx_0E0B7D40,
    createCEcoBRE1RegEx_0E0B7D40,
    deleteCEcoBRE1RegEx_0E0B7D40,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pIMem */
    0, /* m_Name */
    0, /* m_pRoot */
    0, /* m_pFSM */
    0, /* m_pStateMachine */
    0  /* m_pStartState */
};