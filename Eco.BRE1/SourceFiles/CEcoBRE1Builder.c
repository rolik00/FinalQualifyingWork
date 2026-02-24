/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBRE1Builder_0E0B7D40
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBRE1Builder_0E0B7D40
 * </description>
 *
 * <author>
 *   Copyright (c) 2018 Vladimir. All rights reserved.
 * </author>
 *
 */

#define _CRT_SECURE_NO_WARNINGS 
#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoBRE1Builder.h" 
#include "IdEcoBinaryTree1.h"
#include "CEcoBRE1RegEx.h"
#include "IEcoRegEx1Builder.h"
#include "IEcoFSM1.h"
#include "IdEcoFSM1.h"

extern CEcoBRE1RegEx_0E0B7D40 g_xCEcoBRE1RegEx_0E0B7D40;

/*
 * Структура для хранения контекста построения NFA
 */
typedef struct NFABuildContext {
    CEcoBRE1Builder_0E0B7D40* pBuilder;
    IEcoFSM1* pFSM;
    IEcoFSM1StateMachine* pStateMachine;
    uint32_t nextStateId;
} NFABuildContext;

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoRegEx1Builder interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_QueryInterface(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoRegEx1Builder) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1Builder;
        pCMe->m_pVTblIEcoRegEx1Builder->AddRef((IEcoRegEx1Builder*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoRegEx1Builder;
        pCMe->m_pVTblIEcoRegEx1Builder->AddRef((IEcoRegEx1Builder*)pCMe);
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
 *   AddRef function for the IEcoRegEx1Builder interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_AddRef(/* in */ IEcoRegEx1BuilderPtr_t me) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;

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
 *   Release function for the IEcoRegEx1Builder interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_Release(/* in */ IEcoRegEx1BuilderPtr_t me) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;

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

/* Вспомогательная функция для выделения и инициализации данных узла */
EcoRegEx1NodeData* AllocNodeData(CEcoBRE1Builder_0E0B7D40* pCMe, EcoRegEx1NodeType type) {
	uint32_t i;
	char* ptr;
    EcoRegEx1NodeData* pData = (EcoRegEx1NodeData*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoRegEx1NodeData));
    if (pData) {
        ptr = (char*)pData;
        for(i = 0; i < sizeof(EcoRegEx1NodeData); i++) ptr[i] = 0;
        pData->type = (uint32_t)type;
    }
    return pData;
}

/* Создание узла дерева с привязкой данных */
IEcoBinaryTree1Node* CreateNodeWithData(CEcoBRE1Builder_0E0B7D40* pCMe, EcoRegEx1NodeData* pData) {
    IEcoBinaryTree1Node* pNode = 0;

    if (pCMe->m_pBinaryTree == 0) return 0;

    pNode = pCMe->m_pBinaryTree->pVTbl->CreateNode(pCMe->m_pBinaryTree, 0, 0);

    if (pNode != 0 && pData != 0) {
        pNode->pVTbl->set_Data(pNode, pData);
    }
    return pNode;
}

/*
 *
 * <summary>
 *   CreateLiteral Function
 * </summary>
 *
 * <description>
 *   CreateLiteral Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateLiteral(/* in */ IEcoRegEx1BuilderPtr_t me, /* in */ uint32_t c) {
    CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;

	if (me == 0) return 0;
	
	pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_LITERAL);

    if (pData) pData->data.literal.codePoint = c;

    return CreateNodeWithData(pCMe, pData);
}

/*
 *
 * <summary>
 *   CreateAnyChar Function
 * </summary>
 *
 * <description>
 *   CreateAnyChar (.) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateAnyChar(IEcoRegEx1BuilderPtr_t me) {
	CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;

	if (me == 0) return 0;
	
	pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_ANYCHAR);

    return CreateNodeWithData(pCMe, pData);
}

/*
 *
 * <summary>
 *   CreateRange Function
 * </summary>
 *
 * <description>
 *   CreateRange (a-z) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateRange(IEcoRegEx1BuilderPtr_t me, uint32_t start, uint32_t end) {
    CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;

	if (me == 0) return 0;
    
    pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_RANGE);
    
    if (pData) {
        pData->data.range.start = start;
        pData->data.range.end = end;
    }
    return CreateNodeWithData(pCMe, pData);
}

/*
 *
 * <summary>
 *   CreateConcat Function
 * </summary>
 *
 * <description>
 *   CreateConcat (AB) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateConcat(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t left, IEcoBinaryTree1NodePtr_t right) {
    CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;
	IEcoBinaryTree1Node* pNode = 0;

	if (me == 0) return 0;

	pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_CONCAT);
    pNode = CreateNodeWithData(pCMe, pData);
    
    if (pNode) {
        if (left) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, left);
        }
        if (right) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, right);
        } 
    } else {
        if (left) left->pVTbl->Release(left);
        if (right) right->pVTbl->Release(right);
    }

    return pNode;
}

/*
 *
 * <summary>
 *   CreateAlternation Function
 * </summary>
 *
 * <description>
 *   CreateAlternation (A|B) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateAlternation(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t left, IEcoBinaryTree1NodePtr_t right) {
    CEcoBRE1Builder_0E0B7D40* pCMe = 0;
	EcoRegEx1NodeData* pData = 0;
	IEcoBinaryTree1Node* pNode = 0;

	if (me == 0) return 0;

	pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    pData = AllocNodeData(pCMe, ECO_REGEX_NODE_ALTERNATION);
    pNode = CreateNodeWithData(pCMe, pData);
    
    if (pNode) {
        if (left) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, left);
        }
        if (right) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, right);
        }
    } else {
        if (left) left->pVTbl->Release(left);
        if (right) right->pVTbl->Release(right);
    }

    return pNode;
}

IEcoBinaryTree1Node* CreateQuantifierNode(CEcoBRE1Builder_0E0B7D40* pCMe, IEcoBinaryTree1Node* child, uint32_t min, uint32_t max) {
    EcoRegEx1NodeData* pData = AllocNodeData(pCMe, ECO_REGEX_NODE_QUANTIFIER);
    IEcoBinaryTree1Node* pNode = 0;
    if (pData) {
        pData->data.quantifier.min = min;
        pData->data.quantifier.max = max; /* 0xFFFFFFFF = infinity */
        pData->data.quantifier.isGreedy = 1;
        pNode = CreateNodeWithData(pCMe, pData);
        if (pNode == 0) {
			pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pData);
			if (child) child->pVTbl->Release(child);
			return 0;
		}
		
		if (child) {
			pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, child);
		}
    }
    return pNode;
}

/*
 *
 * <summary>
 *   CreateStar Function
 * </summary>
 *
 * <description>
 *   CreateStar (A*) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateStar(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child) {
    return CreateQuantifierNode((CEcoBRE1Builder_0E0B7D40*)me, child, 0, 0xFFFFFFFF);
}

/*
 *
 * <summary>
 *   CreatePlus Function
 * </summary>
 *
 * <description>
 *   CreatePlus (A+) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreatePlus(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child) {
    return CreateQuantifierNode((CEcoBRE1Builder_0E0B7D40*)me, child, 1, 0xFFFFFFFF);
}

/*
 *
 * <summary>
 *   CreateOptional Function
 * </summary>
 *
 * <description>
 *   CreateOptional (A?) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateOptional(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child) {
    return CreateQuantifierNode((CEcoBRE1Builder_0E0B7D40*)me, child, 0, 1);
}

/*
 *
 * <summary>
 *   CreateRepeat Function
 * </summary>
 *
 * <description>
 *   CreateRepeat (A{n,m}) Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateRepeat(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child, uint32_t min, uint32_t max) {
    return CreateQuantifierNode((CEcoBRE1Builder_0E0B7D40*)me, child, min, max);
}

/*
 *
 * <summary>
 *   CreateGroup Function
 * </summary>
 *
 * <description>
 *   CreateGroup () Function
 * </description>
 *
 */
static IEcoBinaryTree1NodePtr_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_CreateGroup(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t child, uint32_t index) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    EcoRegEx1NodeData* pData = AllocNodeData(pCMe, ECO_REGEX_NODE_GROUP);
    IEcoBinaryTree1Node* pNode = 0;
    if (pData) {
        pData->data.group.index = index;
        pNode = CreateNodeWithData(pCMe, pData);
        if (pNode && child) {
            pCMe->m_pBinaryTree->pVTbl->InsertNode(pCMe->m_pBinaryTree, pNode, child);
			child->pVTbl->Release(child);
		}
    }
    return pNode;
}

/*
 * Создает новое состояние в автомате
 */
static IEcoFSM1State* CreateNFAState(NFABuildContext* pCtx, char_t* name) {
    char_t stateName[32];
    sprintf(stateName, "S%d_%s", pCtx->nextStateId++, name ? name : "");
    
    return pCtx->pStateMachine->pVTbl->AddState(pCtx->pStateMachine, stateName);
}

/*
 * Создает ε-переход между состояниями
 * Используем IsNull = true для ε-события
 */
static int16_t CreateEpsilonTransition(NFABuildContext* pCtx,
                                       IEcoFSM1State* from,
                                       IEcoFSM1State* to) {
    IEcoFSM1Event* pEpsilonEvent = pCtx->pStateMachine->pVTbl->AddEvent(
        pCtx->pStateMachine,
        "ε",
        -1,    
        1 
    );
    
    if (pEpsilonEvent == 0) return -1;
    
    pCtx->pStateMachine->pVTbl->AddTransition(
        pCtx->pStateMachine,
        pEpsilonEvent,
        from,
        to
    );
    
    return 0;
}

/*
 * Создает переход по символу (литералу)
 */
static int16_t CreateSymbolTransition(NFABuildContext* pCtx,
                                      IEcoFSM1State* from,
                                      IEcoFSM1State* to,
                                      uint32_t symbol) {
	IEcoFL1SymbolSet* pSymbolSet = 0;
    IEcoFSM1Event* pEvent = pCtx->pStateMachine->pVTbl->AddEvent(
        pCtx->pStateMachine,
        "literal",
        symbol,   
        0    
    );
    
    if (pEvent == 0) return -1;
    
    pSymbolSet = pEvent->pVTbl->AddSymbolSet(pEvent, "lit");
    if (pSymbolSet) {
        pSymbolSet->pVTbl->AddSymbol(pSymbolSet, (byte_t*)&symbol, 8, 0, 0);
    }
    
    pCtx->pStateMachine->pVTbl->AddTransition(
        pCtx->pStateMachine,
        pEvent,
        from,
        to
    );
    
    return 0;
}

/*
 * Создает переход по любому символу (.)
 */
static int16_t CreateAnyCharTransition(NFABuildContext* pCtx,
                                       IEcoFSM1State* from,
                                       IEcoFSM1State* to) {
	IEcoFL1SymbolSet* pSymbolSet = 0;
	uint32_t dummy = 0;
    IEcoFSM1Event* pEvent = pCtx->pStateMachine->pVTbl->AddEvent(
        pCtx->pStateMachine,
        "anychar",
        256, 
        0
    );
    
    if (pEvent == 0) return -1;
    
    pSymbolSet = pEvent->pVTbl->AddSymbolSet(pEvent, "any");
    if (pSymbolSet) {
        pSymbolSet->pVTbl->set_Complement(pSymbolSet, 1);
		pSymbolSet->pVTbl->AddSymbol(pSymbolSet, (byte_t*)&dummy, 8, 0, 0);
    }
    
    pCtx->pStateMachine->pVTbl->AddTransition(
        pCtx->pStateMachine,
        pEvent,
        from,
        to
    );
    
    return 0;
}

/*
 * Построение NFA для узла AST по алгоритму Томпсона
 * Возвращает входное и выходное состояния построенного фрагмента
 */
static int16_t BuildNFANode(NFABuildContext* pCtx,
                            IEcoBinaryTree1Node* node,
                            IEcoFSM1State** ppEntry,
                            IEcoFSM1State** ppExit) {
    EcoRegEx1NodeData* pData = 0;
    IEcoFSM1State *entry = 0, *exit = 0;
    IEcoFSM1State *leftEntry = 0, *leftExit = 0;
    IEcoFSM1State *rightEntry = 0, *rightExit = 0;
    IEcoFSM1State *start = 0, *end = 0;
    IEcoFSM1State *newEntry = 0, *newExit = 0;
    IEcoFSM1State *prevExit = 0;
    IEcoFSM1State *lastEntry = 0, *lastExit = 0;
    IEcoFSM1State *currentStart = 0, *currentPrev = 0;
    IEcoBinaryTree1Node* child = 0;
    IEcoFSM1Event* pEvent = 0;
    IEcoFL1SymbolSet* pSymbolSet = 0;
    uint32_t min = 0, max = 0, i = 0;
    int16_t result = 0;

    if (node == 0) return -1;
    
    pData = (EcoRegEx1NodeData*)node->pVTbl->get_Data(node);
    if (pData == 0) return -1;
    
    switch (pData->type) {
        case ECO_REGEX_NODE_LITERAL: {
            entry = CreateNFAState(pCtx, "lit_in");
            exit = CreateNFAState(pCtx, "lit_out");
            CreateSymbolTransition(pCtx, entry, exit, pData->data.literal.codePoint);
            break;
        }
        
        case ECO_REGEX_NODE_ANYCHAR: {
            entry = CreateNFAState(pCtx, "any_in");
            exit = CreateNFAState(pCtx, "any_out");
            CreateAnyCharTransition(pCtx, entry, exit);
            break;
        }
        
        case ECO_REGEX_NODE_RANGE: {
            entry = CreateNFAState(pCtx, "range_in");
            exit = CreateNFAState(pCtx, "range_out");
            
            pEvent = pCtx->pStateMachine->pVTbl->AddEvent(
                pCtx->pStateMachine,
                "range",
                pData->data.range.start * 1000 + pData->data.range.end,
                0
            );

			 if (pEvent == 0) {
				 if (entry) entry->pVTbl->Release(entry);
				 if (exit) exit->pVTbl->Release(exit);
				 result = -1;
				 break;
			 }
            
            pSymbolSet = pEvent->pVTbl->AddSymbolSet(pEvent, "range");
			if (pSymbolSet == 0) {
				pEvent->pVTbl->Release(pEvent);
				if (entry) entry->pVTbl->Release(entry);
				if (exit) exit->pVTbl->Release(exit);
				result = -1;
				break;
			}
            pSymbolSet->pVTbl->AddSymbolRange(pSymbolSet, 
                                              pData->data.range.start,
                                              pData->data.range.end, 0);
            
            pCtx->pStateMachine->pVTbl->AddTransition(pCtx->pStateMachine, pEvent, entry, exit);
            break;
        }
        
        case ECO_REGEX_NODE_CONCAT: {
            result = BuildNFANode(pCtx, node->pVTbl->get_Left(node), &leftEntry, &leftExit);
            if (result != 0) break;
            
            result = BuildNFANode(pCtx, node->pVTbl->get_Right(node), &rightEntry, &rightExit);
            if (result != 0) break;
            
            CreateEpsilonTransition(pCtx, leftExit, rightEntry);
            
            entry = leftEntry;
            exit = rightExit;
            break;
        }
        
        case ECO_REGEX_NODE_ALTERNATION: {
            start = CreateNFAState(pCtx, "alt_start");
            end = CreateNFAState(pCtx, "alt_end");
            
            result = BuildNFANode(pCtx, node->pVTbl->get_Left(node), &leftEntry, &leftExit);
            if (result != 0) break;
            
            result = BuildNFANode(pCtx, node->pVTbl->get_Right(node), &rightEntry, &rightExit);
            if (result != 0) break;
            
            CreateEpsilonTransition(pCtx, start, leftEntry);
            CreateEpsilonTransition(pCtx, start, rightEntry);
            CreateEpsilonTransition(pCtx, leftExit, end);
            CreateEpsilonTransition(pCtx, rightExit, end);
            
            entry = start;
            exit = end;
            break;
        }
        
        case ECO_REGEX_NODE_QUANTIFIER: {
            child = node->pVTbl->get_Left(node);
            min = pData->data.quantifier.min;
            max = pData->data.quantifier.max;
            
            result = BuildNFANode(pCtx, child, &leftEntry, &leftExit);
            if (result != 0) break;
            
            if (min == 0 && max == 0xFFFFFFFF) {
                start = CreateNFAState(pCtx, "star_start");
                end = CreateNFAState(pCtx, "star_end");
                
                CreateEpsilonTransition(pCtx, start, leftEntry);
                CreateEpsilonTransition(pCtx, start, end);
                CreateEpsilonTransition(pCtx, leftExit, leftEntry);     
                CreateEpsilonTransition(pCtx, leftExit, end);
                
                entry = start;
                exit = end;
                
            } else if (min == 1 && max == 0xFFFFFFFF) {
                start = CreateNFAState(pCtx, "plus_start");
                end = CreateNFAState(pCtx, "plus_end");
                
                CreateEpsilonTransition(pCtx, start, leftEntry);
                CreateEpsilonTransition(pCtx, leftExit, leftEntry);
                CreateEpsilonTransition(pCtx, leftExit, end);
                
                entry = start;
                exit = end;
                
            } else if (min == 0 && max == 1) {
                start = CreateNFAState(pCtx, "opt_start");
                end = CreateNFAState(pCtx, "opt_end");
                
                CreateEpsilonTransition(pCtx, start, leftEntry);
                CreateEpsilonTransition(pCtx, start, end);
                CreateEpsilonTransition(pCtx, leftExit, end);
                
                entry = start;
                exit = end;
            } else if (min == max && max != 0xFFFFFFFF) {
				prevExit = leftEntry;
				start = leftEntry;
				
				for (i = 1; i < min; i++) {
					result = BuildNFANode(pCtx, child, &newEntry, &newExit);
					if (result != 0) break;
					CreateEpsilonTransition(pCtx, prevExit == leftEntry ? leftExit : prevExit, newEntry);
					prevExit = newExit;
				}
				entry = start;
				exit = (min == 0) ? leftEntry : (min == 1) ? leftExit : prevExit;
			} else if (max == 0xFFFFFFFF && min > 1) {
				lastEntry = leftEntry;
				lastExit = leftExit;
				start = leftEntry;
				for (i = 1; i < min; i++) {
					result = BuildNFANode(pCtx, child, &newEntry, &newExit);
					if (result != 0) break;
					CreateEpsilonTransition(pCtx, lastExit, newEntry);
					lastEntry = newEntry;
					lastExit = newExit;
				}
				end = CreateNFAState(pCtx, "repeat_end");
				CreateEpsilonTransition(pCtx, lastExit, lastEntry); 
				CreateEpsilonTransition(pCtx, lastExit, end);       
				entry = start;
				exit = end;
			} else if (max != 0xFFFFFFFF && max > min) {
				prevExit = leftEntry;
				start = leftEntry;
				end = CreateNFAState(pCtx, "range_end");
				for (i = 1; i < min; i++) {
					result = BuildNFANode(pCtx, child, &newEntry, &newExit);
					if (result != 0) break;
					CreateEpsilonTransition(pCtx, prevExit == leftEntry ? leftExit : prevExit, newEntry);
					prevExit = newExit;
				}
				currentStart = (min == 0) ? leftEntry : (min == 1) ? leftEntry : prevExit;
				currentPrev = currentStart;
				for (i = 0; i < max - min; i++) {
					result = BuildNFANode(pCtx, child, &newEntry, &newExit);
					if (result != 0) break;
					CreateEpsilonTransition(pCtx, currentPrev, newEntry);
					CreateEpsilonTransition(pCtx, newExit, end);
					currentPrev = newExit;
				}
				if (min > 0) {
					CreateEpsilonTransition(pCtx, prevExit, end);
				} else {
					CreateEpsilonTransition(pCtx, leftEntry, end);
				}
				entry = start;
				exit = end;
			} else if (min == 0 && max == 0) {
				start = CreateNFAState(pCtx, "empty_start");
				end = CreateNFAState(pCtx, "empty_end");
				CreateEpsilonTransition(pCtx, start, end);
				entry = start;
			} else {
				entry = leftEntry;
				exit = leftExit;
			}
            break;
        }
        
        case ECO_REGEX_NODE_GROUP: {
            result = BuildNFANode(pCtx, node->pVTbl->get_Left(node), &entry, &exit);
            break;
        }
        
        default:
            result = -1;
            break;
    }
    
    if (ppEntry) *ppEntry = entry;
    if (ppExit) *ppExit = exit;
    
    return result;
}

/* Строит из синтасического дерева конечный автомат */
static int16_t ECOCALLMETHOD CEcoBRE1Builder_0E0B7D40_Build(IEcoRegEx1BuilderPtr_t me, IEcoBinaryTree1NodePtr_t root, IEcoRegEx1Ptr_t* ppIRegex) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
    CEcoBRE1RegEx_0E0B7D40Ptr_t pCObj = 0;
    int16_t result = ERR_ECO_POINTER;
    CEcoBRE1RegEx_0E0B7D40* pRegExImpl = 0;
    NFABuildContext ctx;
    IEcoFSM1* pFSM = 0;
    IEcoFSM1StateMachine* pStateMachine = 0;
    IEcoFSM1State* entry = 0;
    IEcoFSM1State* exit = 0;
    IEcoInterfaceBus1* pIBus = 0;
	
    if (me == 0 || root == 0 || ppIRegex == 0) {
		return result;
    }

	result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
		return result;
    }
	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFSM1, 0, &IID_IEcoFSM1, (void**)&pFSM);
	pIBus->pVTbl->Release(pIBus);
	if (result != 0 || pFSM == 0) {
		return result;
    }
	
	pStateMachine = pFSM->pVTbl->CreateStateMachine(pFSM, "RegexNFA");
    if (pStateMachine == 0) {
		pFSM->pVTbl->Release(pFSM);
        return -1;
    }
	
	memset(&ctx, 0, sizeof(ctx));
    ctx.pBuilder = pCMe;
    ctx.pFSM = pFSM;
    ctx.pStateMachine = pStateMachine;
    ctx.nextStateId = 0;

	result = BuildNFANode(&ctx, root, &entry, &exit);
	
	if (result == 0 && entry && exit) {
        entry->pVTbl->set_Initial(entry, 1);
        exit->pVTbl->set_Final(exit, 1);
        
		pCObj = (CEcoBRE1RegEx_0E0B7D40Ptr_t)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBRE1RegEx_0E0B7D40));
        if (pCObj) {
			pCObj = (CEcoBRE1RegEx_0E0B7D40Ptr_t)pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, pCObj, &g_xCEcoBRE1RegEx_0E0B7D40, sizeof(CEcoBRE1RegEx_0E0B7D40));
			pCObj->m_cRef = 1;
            pCObj->m_pIMem = pCMe->m_pIMem;
            pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);
            pCObj->m_pISys = pCMe->m_pISys;
            pCMe->m_pISys->pVTbl->AddRef(pCMe->m_pISys);
            pCObj->m_Name = 0;
            pCObj->m_pRoot = root;
            root->pVTbl->AddRef(root);
            pCObj->m_pFSM = pFSM;
            pCObj->m_pStateMachine = pStateMachine;
            pCObj->m_pStartState = entry;
            pFSM->pVTbl->AddRef(pFSM);
            pStateMachine->pVTbl->AddRef(pStateMachine);
            *ppIRegex = (IEcoRegEx1Ptr_t)pCObj;
            result = 0;
        }
    }

	if (result != 0) {
        if (pStateMachine) pStateMachine->pVTbl->Release(pStateMachine);
        if (pFSM) pFSM->pVTbl->Release(pFSM);
        if (entry) entry->pVTbl->Release(entry);
        if (exit) exit->pVTbl->Release(exit);
    }

	root->pVTbl->Release(root);
	return result;
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
int16_t ECOCALLMETHOD initCEcoBRE1Builder_0E0B7D40(/*in*/ CEcoBRE1Builder_0E0B7D40Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBRE1Builder_0E0B7D40* pCMe = (CEcoBRE1Builder_0E0B7D40*)me;
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
	
	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoBinaryTree1, 0, &IID_IEcoBinaryTree1, (void**)&pCMe->m_pBinaryTree);
	if (result != 0 || pCMe->m_pBinaryTree == 0) {
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
int16_t ECOCALLMETHOD createCEcoBRE1Builder_0E0B7D40(/* in */ CEcoBRE1Builder_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
    int16_t result = ERR_ECO_POINTER;
    CEcoBRE1Builder_0E0B7D40* pNewObj = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    if (pCMe == 0 || pIUnkSystem == 0) {
        return ERR_ECO_POINTER;
    }

    /* Получаем системный интерфейс */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);
    if (result != 0 || pISys == 0) {
        return ERR_ECO_NOSYSTEM;
    }

    /* Получаем интерфейсную шину */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_NOBUS;
    }

    /* Получаем менеджер памяти */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получаем аллокатор памяти */
    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Выделяем память под новый объект */
    pNewObj = (CEcoBRE1Builder_0E0B7D40*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoBRE1Builder_0E0B7D40));
    if (pNewObj == 0) {
        pIMem->pVTbl->Release(pIMem);
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }

    /* Копируем данные из шаблона */
    pNewObj = (CEcoBRE1Builder_0E0B7D40*)pIMem->pVTbl->Copy(pIMem, pNewObj, pCMe, sizeof(CEcoBRE1Builder_0E0B7D40));
    
    /* Инициализируем поля */
    pNewObj->m_cRef = 1;
    pNewObj->m_pIMem = pIMem;
    pIMem->pVTbl->AddRef(pIMem);
    
    pNewObj->m_pISys = pISys;
    pISys->pVTbl->AddRef(pISys);
    
    pNewObj->m_Name = 0;
    pNewObj->m_pBinaryTree = 0;

    pIBus->pVTbl->Release(pIBus);

    return 0; /* ERR_ECO_SUCCESES */
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
static void ECOCALLMETHOD deleteCEcoBRE1Builder_0E0B7D40(/* in */ CEcoBRE1Builder_0E0B7D40Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
		if (pCMe->m_pBinaryTree != 0) {
            pCMe->m_pBinaryTree->pVTbl->Release(pCMe->m_pBinaryTree);
        }
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoRegEx1Builder Virtual Table */
IEcoRegEx1BuilderVTbl g_x38E665D3C7B94BD098540E96A232BF40VTbl_0E0B7D40 = {
    CEcoBRE1Builder_0E0B7D40_QueryInterface,
    CEcoBRE1Builder_0E0B7D40_AddRef,
    CEcoBRE1Builder_0E0B7D40_Release,
    CEcoBRE1Builder_0E0B7D40_CreateLiteral,
	CEcoBRE1Builder_0E0B7D40_CreateAnyChar,
    CEcoBRE1Builder_0E0B7D40_CreateRange,
	CEcoBRE1Builder_0E0B7D40_CreateConcat,
    CEcoBRE1Builder_0E0B7D40_CreateAlternation,
    CEcoBRE1Builder_0E0B7D40_CreateStar,
    CEcoBRE1Builder_0E0B7D40_CreatePlus,
    CEcoBRE1Builder_0E0B7D40_CreateOptional,
    CEcoBRE1Builder_0E0B7D40_CreateRepeat,
	CEcoBRE1Builder_0E0B7D40_CreateGroup,
    CEcoBRE1Builder_0E0B7D40_Build
};



/* Object Instance */
CEcoBRE1Builder_0E0B7D40 g_xCEcoBRE1Builder_0E0B7D40 = {
    &g_x38E665D3C7B94BD098540E96A232BF40VTbl_0E0B7D40,
    initCEcoBRE1Builder_0E0B7D40,
    createCEcoBRE1Builder_0E0B7D40,
    deleteCEcoBRE1Builder_0E0B7D40,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pIMem */
    0, /* m_Name */
	0  /* m_pBinaryTree */
};
