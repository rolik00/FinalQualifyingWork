/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLR1RE
 * </summary>
 *
 * <description>
 *   This header describes the implementation of the CEcoBLR1RE component
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */

#ifndef __I_ECO_BASIC_LEXICAL_RULES_1_RE_H__
#define __I_ECO_BASIC_LEXICAL_RULES_1_RE_H__

#include "IEcoLexicalRules1RE.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoList1.h"
#include "IEcoFSM1.h"
#include "IEcoBRE1.h"

typedef struct RuleRE {
    char_t* stateName;   
    char_t* pattern;     
    uint32_t tokenId;
    uint32_t priority;    
    uint32_t channel;   
    EcoLexicalAction_t action;
    voidptr_t actionContext;
    IEcoFSM1StateMachine* pNFA;                 
    IEcoFSM1State* pStartState;         
    IEcoList1* pAcceptingStates;
	IEcoRegEx1* pRegex;
} RuleRE;

// ¬спомогательна€ структура дл€ супер-NFA
typedef struct FinalStateInfo {
    IEcoFSM1State* pState;     
    uint32_t tokenId;           
    uint32_t priority;           
    uint32_t channel;            
    EcoLexicalAction_t pfnAction; 
    voidptr_t pActionContext;   
} FinalStateInfo;

typedef struct DFAState {
    IEcoList1* nfaStates;          
    bool_t isAccepting;
    uint32_t bestTokenId;        
    uint32_t bestPriority;       
    EcoLexicalAction_t bestAction;
    voidptr_t bestActionContext;
    uint32_t bestChannel;
	IEcoList1* transitions;
} DFAState;

typedef struct DFATransition {
	IEcoFSM1Event* pEvent;
	uint32_t targetStateIdx; 
} DFATransition;

typedef struct CEcoBLR1RE_F82A88F6* CEcoBLR1RE_F82A88F6Ptr_t;

typedef struct CEcoBLR1RE_F82A88F6 {

    /* IEcoLexicalRules1RE interface function table */
    IEcoLexicalRules1REVTbl* m_pVTblIRules;


    /* Instance initialization */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBLR1RE_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Instance creation */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBLR1RE_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Deletion */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBLR1RE_F82A88F6Ptr_t pCMe);


    /* Reference counter */
    uint32_t m_cRef;

    /* Interface for memory operations */
    IEcoMemoryAllocator1* m_pIMem;

    /* System interface */
    IEcoSystem1* m_pISys;

    /* Instance data */
    char_t* m_Name;

	// пол€ дл€ NFA
	IEcoBRE1* m_pBRE;
	IEcoList1* m_pRulesList;        
	IEcoFSM1StateMachine* m_pSuperNFA;
	IEcoList1* m_pFinalStateAttrs;

	// пол€ дл€ DFA
	IEcoList1* m_pDFAStates; 

    uint32_t m_startStateIdx;

} CEcoBLR1RE_F82A88F6;

extern CEcoBLR1RE_F82A88F6 g_xCEcoBLR1RE_F82A88F6;

#endif /* __I_ECO_BASIC_LEXICAL_RULES_1_RE_H__ */
