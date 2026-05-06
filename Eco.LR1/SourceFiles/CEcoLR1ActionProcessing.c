/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoLR1ActionProcessing_A441A18E
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoLR1ActionProcessing_A441A18E
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */


#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLR1ActionProcessing.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoParser1ActionProcessing interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_QueryInterface(/* in */ IEcoParser1ActionProcessingPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoParser1ActionProcessing) ) {
        *ppv = &pCMe->m_pVTblIAP;
        pCMe->m_pVTblIAP->AddRef((IEcoParser1ActionProcessing*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIAP;
        pCMe->m_pVTblIAP->AddRef((IEcoParser1ActionProcessing*)pCMe);
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
 *   AddRef function for the IEcoParser1ActionProcessing interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_AddRef(/* in */ IEcoParser1ActionProcessingPtr_t me) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;

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
 *   Release function for the IEcoParser1ActionProcessing interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_Release(/* in */ IEcoParser1ActionProcessingPtr_t me) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;

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

/* Вспомогательная функция поиска перехода (Си89, вставьте в начало файла) */
static IEcoFSM1Transition* CEcoLR1ActionProcessing_A441A18E_FindTransition(IEcoFSM1StateMachine* pIFSM, IEcoFSM1State* pSrc, IEcoFSM1Event* pEv) {
    IEcoList1* pTransitions = 0;
    IEcoFSM1Transition* pTr = 0;
    uint32_t i = 0, count = 0;
    if (!pIFSM || !pSrc || !pEv) return 0;
    pTransitions = pIFSM->pVTbl->get_Transitions(pIFSM);
    if (!pTransitions) return 0;
    count = pTransitions->pVTbl->Count(pTransitions);
    for (i = 0; i < count; i++) {
        pTr = (IEcoFSM1Transition*)pTransitions->pVTbl->Item(pTransitions, i);
        if (pTr != 0 && pTr->pVTbl->get_Source(pTr) == pSrc && pTr->pVTbl->get_Event(pTr) == pEv) {
            return pTr;
        }
    }
    return 0;
}

static IEcoFSM1State* ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_get_CurrentState(/* in */ IEcoParser1ActionProcessingPtr_t me, /* out */ int16_t* StateType) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;
    return 0;
}
static IEcoParser1Action* ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_InvokeById(IEcoParser1ActionProcessingPtr_t me, int16_t Id) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;
    IEcoFSM1State *pCurrentState = 0, *pNextState = 0;
    IEcoFSM1StateMachine* pFSM = 0;
    IEcoFSM1Event* pEv = 0;
    IEcoFSM1Transition* pTr = 0;
    IEcoParser1Action* pAction = 0;
    IEcoList1* pEvents = 0;
    int16_t aType = 0;

    if (pCMe == 0 || pCMe->m_pPDAProcessing == 0) return 0;

    /* 1. Получаем текущее состояние ДО выполнения шага */
    pCurrentState = pCMe->m_pPDAProcessing->pVTbl->get_CurrentState(pCMe->m_pPDAProcessing);
    if (pCurrentState == 0) return 0;

    /* 2. Получаем список событий и находим текущее событие по Id */
    pFSM = pCMe->m_pPDAProcessing->pVTbl->get_FSMProcessing(pCMe->m_pPDAProcessing)->pVTbl->get_StateMachine(pCMe->m_pPDAProcessing->pVTbl->get_FSMProcessing(pCMe->m_pPDAProcessing));
    pEvents = pFSM->pVTbl->get_Events(pFSM);
    
    if (Id < 0 || (uint32_t)Id >= pEvents->pVTbl->Count(pEvents)) return 0;
    pEv = (IEcoFSM1Event*)pEvents->pVTbl->Item(pEvents, Id);

    /* 3. Ищем переход в таблице для извлечения Action */
    pTr = CEcoLR1ActionProcessing_A441A18E_FindTransition(pFSM, pCurrentState, pEv);
    if (pTr == 0) {
        printf("[LR1_PROC] SYNTAX ERROR: No transition from s%d on '%s'\n", 
               pCurrentState->pVTbl->get_Id(pCurrentState), pEv->pVTbl->get_Name(pEv));
        return 0;
    }

    pAction = (IEcoParser1Action*)pTr->pVTbl->get_Parameter(pTr);
    if (pAction == 0) return 0;
    aType = pAction->pVTbl->get_Type(pAction);

    /* 4. ВЫПОЛНЯЕМ ШАГ В PDA */
    /* Для SHIFT: положит состояние в стек и сдвинет вход.
       Для REDUCE: сделает Pop и НЕ сдвинет вход (так как событие помечено isNull=1). */
    pNextState = pCMe->m_pPDAProcessing->pVTbl->InvokeById(pCMe->m_pPDAProcessing, Id);
    
    if (pNextState == 0) {
        printf("[LR1_PROC] PDA Rejected transition\n");
        return 0;
    }

    /* 5. СПЕЦИФИКА LR: Обработка GOTO после REDUCE */
    if (aType == ECO_ACTION_PROCESSING_TYPE_REDUCE) {
        /* После свертки на вершине стека лежит символ НЕТЕРМИНАЛА.
           Нам нужно заставить PDA совершить эпсилон-переход (GOTO) из текущего состояния 
           в новое, основываясь на этом нетерминале. */
        
        /* В вашем PDA InvokeBySymbol(0,0,0) прогоняет эпсилон-цепочки. 
           Это инициирует GOTO-переход в следующее состояние. */
        pNextState = pCMe->m_pPDAProcessing->pVTbl->InvokeBySymbol(pCMe->m_pPDAProcessing, 0, 0, 0);
        
        if (pNextState == 0) {
            printf("[LR1_PROC] GOTO failed after REDUCE\n");
            return 0;
        }
    }

    /* 6. Обновляем текущее состояние в обертке и выводим лог */
    pCMe->m_pCurrentState = pNextState;
    printf("[LR1_PROC] s%d --(%s)--> s%d | %s\n", 
           pCurrentState->pVTbl->get_Id(pCurrentState), 
           pEv->pVTbl->get_Name(pEv), 
           pNextState->pVTbl->get_Id(pNextState),
           (aType == ECO_ACTION_PROCESSING_TYPE_SHIFT ? "SHIFT" : 
           (aType == ECO_ACTION_PROCESSING_TYPE_REDUCE ? "REDUCE" : "ACCEPT")));

    return pAction;
}


static IEcoParser1Action* ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_InvokeByName(IEcoParser1ActionProcessingPtr_t me, char_t* Name) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;
    IEcoFSM1EventProcessing* pFSMProc = 0;
    IEcoFSM1StateMachine* pFSM = 0;
    IEcoList1* pEvents = 0;
    IEcoFSM1Event* pEv = 0;
    char_t* eventName = 0;
    uint32_t i = 0, count = 0;

    /* 1. Валидация входных параметров */
    if (pCMe == 0 || pCMe->m_pPDAProcessing == 0 || Name == 0) {
        return 0;
    }

    /* 2. Получение интерфейсов доступа к событиям через PDA и FSM */
    pFSMProc = pCMe->m_pPDAProcessing->pVTbl->get_FSMProcessing(pCMe->m_pPDAProcessing);
    if (pFSMProc == 0) return 0;
    
    pFSM = pFSMProc->pVTbl->get_StateMachine(pFSMProc);
    if (pFSM == 0) return 0;
    
    pEvents = pFSM->pVTbl->get_Events(pFSM);
    if (pEvents == 0) return 0;
    
    count = pEvents->pVTbl->Count(pEvents);

    /* 3. Линейный поиск ID события по текстовому имени */
    for (i = 0; i < count; i++) {
        pEv = (IEcoFSM1Event*)pEvents->pVTbl->Item(pEvents, i);
        
        /* Проверяем валидность объекта события и его таблицы методов */
        if (pEv != 0 && pEv->pVTbl != 0) {
            eventName = pEv->pVTbl->get_Name(pEv);
            
            /* Сравниваем имя только если оно существует */
            if (eventName != 0 && strcmp(eventName, Name) == 0) {
                /* Перенаправляем выполнение в InvokeById, где реализована вся логика PDA+GOTO */
                return CEcoLR1ActionProcessing_A441A18E_InvokeById(me, (int16_t)i);
            }
        }
    }

    /* Логируем ошибку, если символ не найден в текущем алфавите парсера */
    printf("[LR1_PROC] ERROR: Terminal or NonTerminal '%s' not found in FSM events\n", Name);
    return 0;
}


static IEcoParser1Action* ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_ResolveConflict(/* in */ IEcoParser1ActionProcessingPtr_t me, /* in */ int16_t resolveType, uint16_t index) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;
    return 0;
}

/* IEcoParser1ActionProcessing: Reset */
static IEcoFSM1State* ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_Reset(IEcoParser1ActionProcessingPtr_t me) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;
    IEcoFSM1State* pInitial = 0;

    if (pCMe == 0 || pCMe->m_pPDAProcessing == 0) return 0;

    /* 1. Сбрасываем PDA в начальное состояние (кладем $ в стек) */
    pCMe->m_pPDAProcessing->pVTbl->Reset(pCMe->m_pPDAProcessing);
    
    /* 2. Получаем начальное состояние из PDA */
    pInitial = pCMe->m_pPDAProcessing->pVTbl->get_CurrentState(pCMe->m_pPDAProcessing);
    pCMe->m_pCurrentState = pInitial;
    pCMe->m_LastStateType = ECO_PROCESSING_TYPE_WAITING;

    printf("[PARSER_ACTION] Reset performed. Initial state: %p\n", (void*)pInitial);
    return pInitial;
}


/* Геттер стека — пробрасываем стек PDA */
static IEcoStack1* ECOCALLMETHOD CEcoLR1ActionProcessing_A441A18E_get_Stack(IEcoParser1ActionProcessingPtr_t me) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;
    if (pCMe == 0 || pCMe->m_pPDAProcessing == 0) return 0;
    return pCMe->m_pPDAProcessing->pVTbl->get_Stack(pCMe->m_pPDAProcessing, 0); /* Используем Стек 0 */
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
static int16_t ECOCALLMETHOD initCEcoLR1ActionProcessing_A441A18E(/*in*/ CEcoLR1ActionProcessing_A441A18EPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoPDA1EventProcessingPtr_t pPDAProcessing) {
    CEcoLR1ActionProcessing_A441A18E* pCMe = (CEcoLR1ActionProcessing_A441A18E*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = ERR_ECO_POINTER;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    /* Pointer Validation */
    if (me == 0 ) {
        return result;
    }

    /* Storing the pointer to the system interface */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Getting the interface for working with the interface bus */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

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
    }

    pCMe->m_pPDAProcessing = pPDAProcessing;


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
static int16_t ECOCALLMETHOD createCEcoLR1ActionProcessing_A441A18E(/* in */ CEcoLR1ActionProcessing_A441A18EPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoLR1ActionProcessing_A441A18E(/* in */ CEcoLR1ActionProcessing_A441A18EPtr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoParser1ActionProcessing Virtual Table */
IEcoParser1ActionProcessingVTbl g_x8B6D924C3257433B90AF59569E131F37VTbl_A441A18E = {
    CEcoLR1ActionProcessing_A441A18E_QueryInterface,
    CEcoLR1ActionProcessing_A441A18E_AddRef,
    CEcoLR1ActionProcessing_A441A18E_Release,
    CEcoLR1ActionProcessing_A441A18E_get_Stack,
    CEcoLR1ActionProcessing_A441A18E_Reset,
    CEcoLR1ActionProcessing_A441A18E_get_CurrentState,
    CEcoLR1ActionProcessing_A441A18E_InvokeById,
    CEcoLR1ActionProcessing_A441A18E_InvokeByName,
    CEcoLR1ActionProcessing_A441A18E_ResolveConflict
};



/* Object Instance */
CEcoLR1ActionProcessing_A441A18E g_xCEcoLR1ActionProcessing_A441A18E = {
    &g_x8B6D924C3257433B90AF59569E131F37VTbl_A441A18E,
    initCEcoLR1ActionProcessing_A441A18E,
    createCEcoLR1ActionProcessing_A441A18E,
    deleteCEcoLR1ActionProcessing_A441A18E,
    1,    /* m_cRef */
    0,    /* m_pIMem */
    0,    /* m_pISys */
    0,    /* m_pIBus */
    0,    /* m_pPDAProcessing */
    0,    /* m_pCurrentState */
    0     /* m_LastStateType */
};
