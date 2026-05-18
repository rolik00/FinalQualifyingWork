/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBSA1Parser_F6E9D8E1
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBSA1Parser_F6E9D8E1
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
#include "CEcoBSA1Parser.h"

/* Прототип функции-строителя узла AST */
typedef int16_t (ECOCALLMETHOD *ASTBuildHandler)(
    struct CEcoBSA1Parser_F6E9D8E1* pCMe,
    IEcoAST1* pIAST, 
    IEcoLexicalAnalyzer1Token* pToken, 
    IEcoList1* pChildren, 
    voidptr_t* ppResultNode
);

/* Запись в таблице маппинга */
typedef struct EcoASTMapperEntry {
    char_t* bnfRuleName;
    ASTBuildHandler handler;
} EcoASTMapperEntry;

typedef struct EcoParserStackItem {
    uint32_t stateId;     
    voidptr_t pASTNode; 
} EcoParserStackItem;

int16_t ECOCALLMETHOD BuildBaseTypeHandler(struct CEcoBSA1Parser_F6E9D8E1* pCMe, IEcoAST1* pIAST, IEcoLexicalAnalyzer1Token* pT, IEcoList1* pC, voidptr_t* ppR) {
    IEcoLexicalAnalyzer1Token* pRealToken = 0;
    char_t* name = 0;
    
    if (pC == 0 || pC->pVTbl->Count(pC) == 0) {
		return -1;
	}
    
    pRealToken = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 0);
    if (pRealToken == 0 || *(void**)pRealToken == 0) {
		return -1;
	}
    
    name = pRealToken->pVTbl->get_Lexeme(pRealToken);
    if (name == 0) {
		return -1;
	}

    if (strcmp(name, "int16_t") == 0) {
        return pIAST->pVTbl->new_NumberType(pIAST, pRealToken, ECO__AST1_TYPE_INT, 16, 0, 1, 0, (IEcoAST1NumberType**)ppR);
    }
    if (strcmp(name, "uint32_t") == 0) {
        return pIAST->pVTbl->new_NumberType(pIAST, pRealToken, ECO__AST1_TYPE_INT, 32, 0, 0, 0, (IEcoAST1NumberType**)ppR);
    }
    if (strcmp(name, "char_t") == 0) {
        return pIAST->pVTbl->new_NumberType(pIAST, pRealToken, ECO__AST1_TYPE_CHAR, 8, 0, 1, 0, (IEcoAST1NumberType**)ppR);
    }
    if (strcmp(name, "void") == 0) {
        return pIAST->pVTbl->new_NumberType(pIAST, pRealToken, ECO__AST1_TYPE_VOID, 0, 0, 0, 0, (IEcoAST1NumberType**)ppR);
    }
    if (strcmp(name, "voidptr_t") == 0) {
        IEcoAST1NumberType* pVoidType = 0;
        pIAST->pVTbl->new_NumberType(pIAST, pRealToken, ECO__AST1_TYPE_VOID, 0, 0, 0, 0, &pVoidType);
        if (pVoidType) {
            return pIAST->pVTbl->new_PointerType(pIAST, pRealToken, (IEcoAST1Type*)pVoidType, 0, (IEcoAST1PointerType**)ppR);
        }
        return -1;
    }
    
    *ppR = pC->pVTbl->Item(pC, 0);
    return 0;
}

int16_t ECOCALLMETHOD BuildAttrHandler(struct CEcoBSA1Parser_F6E9D8E1* pCMe, IEcoAST1* pIAST, IEcoLexicalAnalyzer1Token* pT, IEcoList1* pC, voidptr_t* ppR) {
    IEcoLexicalAnalyzer1Token* pAttrToken = 0;
    char_t* attrName = 0;
    
    if (pC == 0 || pC->pVTbl->Count(pC) == 0) {
		return -1;
	}
    
    pAttrToken = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 0);
    if (pAttrToken == 0 || *(void**)pAttrToken == 0) {
		return -1;
	}
    
    attrName = pAttrToken->pVTbl->get_Lexeme(pAttrToken);
    if (attrName == 0) {
		return -1;
	}

    if (strcmp(attrName, "in") == 0) {
        *ppR = (voidptr_t)1;
    } else if (strcmp(attrName, "out") == 0) {
        *ppR = (voidptr_t)2;
    }
    return 0;
}

int16_t ECOCALLMETHOD BuildParamHandler(struct CEcoBSA1Parser_F6E9D8E1* pCMe, IEcoAST1* pIAST, IEcoLexicalAnalyzer1Token* pT, IEcoList1* pC, voidptr_t* ppR) {
    uint32_t count = 0;

    if (pC == 0) {
		return -1;
	}

    count = pC->pVTbl->Count(pC);
    
    if (count == 7) { 
        IEcoAST1Type* pBaseType = (IEcoAST1Type*)pC->pVTbl->Item(pC, 3);
        IEcoLexicalAnalyzer1Token* pStar1 = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 4);
        IEcoLexicalAnalyzer1Token* pStar2 = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 5);
        IEcoLexicalAnalyzer1Token* pId = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 6);
        IEcoAST1PointerType* pPtrType1 = 0;
        IEcoAST1PointerType* pPtrType2 = 0;
        
        if (pId == 0 || *(void**)pId == 0 || pBaseType == 0 || pStar1 == 0 || pStar2 == 0) {
			return -1;
		}

        pIAST->pVTbl->new_PointerType(pIAST, pStar1, pBaseType, 0, &pPtrType1);

        pIAST->pVTbl->new_PointerType(pIAST, pStar2, (IEcoAST1Type*)pPtrType1, 0, &pPtrType2);

        return pIAST->pVTbl->new_VariableDeclaration(pIAST, pId, (IEcoAST1Type*)pPtrType2, pId->pVTbl->get_Lexeme(pId), 0, (IEcoAST1VariableDeclaration**)ppR);
        
    } else if (count == 6) { 
        IEcoAST1Type* pBaseType = (IEcoAST1Type*)pC->pVTbl->Item(pC, 3);
        IEcoLexicalAnalyzer1Token* pStar = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 4);
        IEcoLexicalAnalyzer1Token* pId = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 5);
        IEcoAST1PointerType* pPtrType = 0;
        
        if (pId == 0 || *(void**)pId == 0 || pBaseType == 0 || pStar == 0) {
			return -1;
		}

        pIAST->pVTbl->new_PointerType(pIAST, pStar, pBaseType, 0, &pPtrType);
        return pIAST->pVTbl->new_VariableDeclaration(pIAST, pId, (IEcoAST1Type*)pPtrType, pId->pVTbl->get_Lexeme(pId), 0, (IEcoAST1VariableDeclaration**)ppR);
    } else if (count == 5) {
        IEcoAST1Type* pType = (IEcoAST1Type*)pC->pVTbl->Item(pC, 3);
        IEcoLexicalAnalyzer1Token* pId = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 4);

        if (pId == 0 || *(void**)pId == 0 || pType == 0) {
			return -1;
		}

        return pIAST->pVTbl->new_VariableDeclaration(pIAST, pId, pType, pId->pVTbl->get_Lexeme(pId), 0, (IEcoAST1VariableDeclaration**)ppR);
    } else if (count == 2) {
        IEcoAST1Type* pType = (IEcoAST1Type*)pC->pVTbl->Item(pC, 0);
        IEcoLexicalAnalyzer1Token* pId = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 1);

        if (pId == 0 || *(void**)pId == 0 || pType == 0) {
			return -1;
		}

        return pIAST->pVTbl->new_VariableDeclaration(pIAST, pId, pType, pId->pVTbl->get_Lexeme(pId), 0, (IEcoAST1VariableDeclaration**)ppR);
    }
    return -1;
}

int16_t ECOCALLMETHOD BuildParamsListHandler(struct CEcoBSA1Parser_F6E9D8E1* pCMe, IEcoAST1* pIAST, IEcoLexicalAnalyzer1Token* pT, IEcoList1* pC, voidptr_t* ppR) {
    uint32_t count = 0;
    IEcoList1* pParamList = 0;
	IEcoAST1VariableDeclaration* pParam = 0;

    if (pC == 0) {
		return -1;
	}

    count = pC->pVTbl->Count(pC);

    if (count == 3) { 
        pParamList = (IEcoList1*)pC->pVTbl->Item(pC, 0);
        pParam = (IEcoAST1VariableDeclaration*)pC->pVTbl->Item(pC, 2);
        if (pParamList && pParam) {
            pParamList->pVTbl->Add(pParamList, pParam);
        }
    } else if (count == 1) { 
        pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pParamList);
        pParam = (IEcoAST1VariableDeclaration*)pC->pVTbl->Item(pC, 0);
        if (pParamList && pParam) {
            pParamList->pVTbl->Add(pParamList, pParam);
        }
    }

    *ppR = pParamList;
    return 0;
}

int16_t ECOCALLMETHOD BuildMethodHandler(struct CEcoBSA1Parser_F6E9D8E1* pCMe, IEcoAST1* pIAST, IEcoLexicalAnalyzer1Token* pT, IEcoList1* pC, voidptr_t* ppR) {
    IEcoAST1Type* pRetType;
    IEcoLexicalAnalyzer1Token* pIdToken;
    IEcoList1* pParamList;
    IEcoAST1BlockDeclarations* pParamsBlock = 0;
    IEcoAST1FunctionType* pFuncType = 0;
    IEcoAST1Scope* pMethodScope = 0;
    IEcoAST1FunctionDeclaration* pFuncDecl = 0;
    int16_t result = 0; 
    
    if (pC == 0 || pC->pVTbl->Count(pC) < 4) {
		return -1;
	}
    
    pRetType = (IEcoAST1Type*)pC->pVTbl->Item(pC, 0);
    pIdToken = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 1);
    pParamList = (IEcoList1*)pC->pVTbl->Item(pC, 3);
    
    if (pRetType == 0 || pIdToken == 0 || *(void**)pIdToken == 0) {
		return -1;
	}

    if (pParamList == 0) {
        pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pParamList);
    }
    
    pIAST->pVTbl->new_BlockDeclarations(pIAST, pIdToken, pParamList, &pParamsBlock);

    if (pCMe->m_pIGlobalScope == 0) {
        pCMe->m_pIAST->pVTbl->new_GlobalScope(pCMe->m_pIAST, 0, &pCMe->m_pIGlobalScope);
    }

    pIAST->pVTbl->new_Scope(pIAST, pIdToken, (IEcoAST1Scope*)pCMe->m_pIGlobalScope, &pMethodScope);
    pIAST->pVTbl->new_FunctionType(pIAST, pIdToken, pRetType, pParamsBlock, pMethodScope, 0, &pFuncType);
    result = pIAST->pVTbl->new_FunctionDeclaration(pIAST, pIdToken, pFuncType, pIdToken->pVTbl->get_Lexeme(pIdToken), &pFuncDecl);
    
    if (result == 0 && pFuncDecl && pMethodScope) {
        IEcoList1* pDeclarations = pMethodScope->pVTbl->get_Declarations(pMethodScope);
        if (pDeclarations) {
            pDeclarations->pVTbl->Add(pDeclarations, pFuncDecl);
            pDeclarations->pVTbl->Release(pDeclarations);
        }
    }
    
    *ppR = pFuncDecl;
    return result;
}

int16_t ECOCALLMETHOD BuildMethodsListHandler(struct CEcoBSA1Parser_F6E9D8E1* pCMe, IEcoAST1* pIAST, IEcoLexicalAnalyzer1Token* pT, IEcoList1* pC, voidptr_t* ppR) {
    IEcoList1* pMethodList = 0;
	IEcoAST1FunctionDeclaration* pMethod = 0;
    uint32_t count = 0;

    if (pC == 0) {
		return -1;
	}

    count = pC->pVTbl->Count(pC);

    if (count == 2) { 
        pMethodList = (IEcoList1*)pC->pVTbl->Item(pC, 0);
        pMethod = (IEcoAST1FunctionDeclaration*)pC->pVTbl->Item(pC, 1);
        if (pMethodList && pMethod) {
            pMethodList->pVTbl->Add(pMethodList, pMethod);
        }
    } else if (count == 1) { 
        pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pMethodList);
        pMethod = (IEcoAST1FunctionDeclaration*)pC->pVTbl->Item(pC, 0);
        if (pMethodList && pMethod) {
            pMethodList->pVTbl->Add(pMethodList, pMethod);
        }
    }

    *ppR = pMethodList;
    return 0;
}

int16_t ECOCALLMETHOD BuildInterfaceHandler(struct CEcoBSA1Parser_F6E9D8E1* pCMe, IEcoAST1* pIAST, IEcoLexicalAnalyzer1Token* pT, IEcoList1* pC, voidptr_t* ppR) {
    IEcoAST1BlockExpressions* pIExpressions = 0;
    IEcoList1* pListExpr = 0;
    uint32_t count = 0;
    IEcoLexicalAnalyzer1Token* pIdToken = 0;
    IEcoList1* pMethodList = 0;
    IEcoAST1BlockDeclarations* pMethodsBlock = 0;
    char_t* lexeme = 0;
    IEcoAST1StructOrUnionDeclaration* pInterfaceDecl = 0;
    int16_t result = 0;

    if (pC == 0 || pIAST == 0 || pCMe == 0) {
		return -1;
	}

    count = pC->pVTbl->Count(pC);
    
    if (count < 6) {
		return -1;
	}

    pIdToken = (IEcoLexicalAnalyzer1Token*)pC->pVTbl->Item(pC, 1);
    if (pIdToken == 0) {
		return -1;
	}
    
    lexeme = pIdToken->pVTbl->get_Lexeme(pIdToken);
    if (lexeme == 0) {
		return -1;
	}

    pMethodList = (IEcoList1*)pC->pVTbl->Item(pC, count - 3);
    if (pMethodList == 0) {
        pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pMethodList);
    }
    
    pIAST->pVTbl->new_BlockDeclarations(pIAST, pIdToken, pMethodList, &pMethodsBlock);

    if (pCMe->m_pIGlobalScope == 0) {
        pIAST->pVTbl->new_GlobalScope(pIAST, 0, (IEcoAST1GlobalScope**)&pCMe->m_pIGlobalScope);
    }

    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pListExpr);
    pIAST->pVTbl->new_BlockExpressions(pIAST, pIdToken, pListExpr, &pIExpressions);
    if (pListExpr) {
		pListExpr->pVTbl->Release(pListExpr);
	}

    result = pIAST->pVTbl->new_StructOrUnionDeclaration(pIAST, pIdToken, lexeme, pMethodsBlock, pIExpressions, 1, (IEcoAST1Scope*)pCMe->m_pIGlobalScope, &pInterfaceDecl);

    if (result == 0 && pInterfaceDecl && pCMe->m_pIGlobalScope) {
        IEcoAST1GlobalScope* pGlobal = (IEcoAST1GlobalScope*)pCMe->m_pIGlobalScope;
        IEcoList1* pDeclarations = pGlobal->pVTbl->get_StructOrUnionDeclarations(pGlobal);
        IEcoList1* pObjects = 0;
        IEcoAST1BlockTranslationUnitObjects* pBlockObjects = 0;
        IEcoAST1TranslationUnit* pTU = 0;
        
        if (pDeclarations) {
            pDeclarations->pVTbl->Add(pDeclarations, pInterfaceDecl);
            pDeclarations->pVTbl->Release(pDeclarations);
        }

        if (pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pObjects) == 0 && pObjects) {
            pObjects->pVTbl->Add(pObjects, pInterfaceDecl);
            
            if (pIAST->pVTbl->new_BlockTranslationUnitObjects(pIAST, pIdToken, pObjects, &pBlockObjects) == 0 && pBlockObjects) {
                if (pIAST->pVTbl->new_TranslationUnit(pIAST, pIdToken, (IEcoAST1GlobalScope*)pCMe->m_pIGlobalScope, pBlockObjects, &pTU) == 0 && pTU) {
                    IEcoTree1* pITree = 0;

                    pCMe->m_pTranslationUnit = pTU;
                    
                    if (pIAST->pVTbl->QueryInterface(pIAST, &IID_IEcoTree1, (void**)&pITree) == 0 && pITree) {
                        IEcoTree1Node* pTUNode = 0;
                        if (pTU->pVTbl->QueryInterface(pTU, &IID_IEcoTree1Node, (void**)&pTUNode) == 0 && pTUNode) {
                            pITree->pVTbl->InsertNode(pITree, 0, pTUNode);
                            pTUNode->pVTbl->Release(pTUNode);
                        }
                        pITree->pVTbl->Release(pITree);
                    }
                }
                if (pBlockObjects) pBlockObjects->pVTbl->Release(pBlockObjects);
            }
            pObjects->pVTbl->Release(pObjects);
        }
    }

    *ppR = pInterfaceDecl;
    return result;
}

static EcoASTMapperEntry g_IDL_AST_Mapper[] = {
    {"base_type", BuildBaseTypeHandler}, 
    {"attr", BuildAttrHandler}, 
    {"param", BuildParamHandler},
    {"params_list", BuildParamsListHandler}, 
    {"method", BuildMethodHandler},
    {"methods", BuildMethodsListHandler}, 
    {"intf", BuildInterfaceHandler}, 
    {0, 0}
};

static ASTBuildHandler FindHandler(char_t* name) {
    uint32_t i = 0;

    if (name == 0) {
		return 0;
	}

    while (g_IDL_AST_Mapper[i].bnfRuleName != 0) {
        if (strcmp(g_IDL_AST_Mapper[i].bnfRuleName, name) == 0) {
            return g_IDL_AST_Mapper[i].handler;
        }
        i++;
    }
    return 0;
}

static int16_t ECOCALLMETHOD CEcoBSA1Parser_F6E9D8E1_QueryInterface(IEcoSyntaxAnalyzer1ParserPtr_t me, const UGUID* riid, void** ppv) {
    CEcoBSA1Parser_F6E9D8E1* pCMe = (CEcoBSA1Parser_F6E9D8E1*)me;

    if (me == 0 || ppv == 0) {
		return ERR_ECO_POINTER;
	}

    if ( IsEqualUGUID(riid, &IID_IEcoSyntaxAnalyzer1Parser) || IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIParser;
        pCMe->m_pVTblIParser->AddRef((IEcoSyntaxAnalyzer1Parser*)pCMe);
    } else {
        *ppv = 0; 
		return ERR_ECO_NOINTERFACE;
    }

    return ERR_ECO_SUCCESES;
}

static uint32_t ECOCALLMETHOD CEcoBSA1Parser_F6E9D8E1_AddRef(IEcoSyntaxAnalyzer1ParserPtr_t me) {
    CEcoBSA1Parser_F6E9D8E1* pCMe = (CEcoBSA1Parser_F6E9D8E1*)me;
    return (me == 0) ? -1 : ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoBSA1Parser_F6E9D8E1_Release(IEcoSyntaxAnalyzer1ParserPtr_t me) {
    CEcoBSA1Parser_F6E9D8E1* pCMe = (CEcoBSA1Parser_F6E9D8E1*)me;
    if (me == 0) {
		return -1;
	}

    if (--pCMe->m_cRef == 0) { 
        pCMe->Delete(pCMe); 
		return 0;
    }
    return pCMe->m_cRef;
}

IEcoParser1Action* ECOCALLMETHOD CEcoBSA1Parser_F6E9D8E1_Parse(struct IEcoSyntaxAnalyzer1Parser* me, IEcoLexicalAnalyzer1Token* pIToken) {
    CEcoBSA1Parser_F6E9D8E1* pCMe = (CEcoBSA1Parser_F6E9D8E1*)me;
    IEcoParser1LRk* pAlgo = pCMe->m_pIAlgorithm;
    EcoParserStackItem* pNewItem = 0;
    char_t* bnfSymbolName = 0;
    int32_t actionValue = 0;
    voidptr_t pNewASTNode = 0;

    if (!pCMe || !pIToken || !pAlgo) {
		return 0;
	}

    if (pIToken->pVTbl->get_Channel(pIToken) != 0) {
        return (IEcoParser1Action*)3;
    }

    if (pCMe->m_pIStack->pVTbl->Count(pCMe->m_pIStack) == 0) {
        pNewItem = (EcoParserStackItem*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoParserStackItem));
        if (pNewItem) {
            pNewItem->stateId = 0;
            pNewItem->pASTNode = NULL;
            pCMe->m_pIStack->pVTbl->Push(pCMe->m_pIStack, pNewItem);
        }
    }

    if (pIToken->pVTbl->IsEOF(pIToken)) {
        bnfSymbolName = "$END";
    } else if (pIToken->pVTbl->get_Type(pIToken) == 3) {
        bnfSymbolName = "id";
    } else {
        bnfSymbolName = pIToken->pVTbl->get_Lexeme(pIToken);
    }

    while (1) {
        EcoParserStackItem* pTop = (EcoParserStackItem*)pCMe->m_pIStack->pVTbl->Peek(pCMe->m_pIStack);
        if (!pTop) {
			return 0;
		}

        actionValue = pAlgo->pVTbl->get_Action(pAlgo, pTop->stateId, bnfSymbolName);
        if (actionValue == 0) {
            actionValue = pAlgo->pVTbl->get_Action(pAlgo, pTop->stateId, "epsilon");
        }
        if (actionValue == 0) {
            return 0;
        }

        if (actionValue > 0 && actionValue != 0x7FFF && actionValue != 0x7FFFFFFF) {
            pNewItem = (EcoParserStackItem*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoParserStackItem));
            
			if (!pNewItem) {
				return 0;
			}

            pNewItem->stateId = (uint32_t)actionValue;
            
			if (pAlgo->pVTbl->get_Action(pAlgo, pTop->stateId, bnfSymbolName) == actionValue) {
                pIToken->pVTbl->AddRef(pIToken);
                pNewItem->pASTNode = (voidptr_t)pIToken;
            } else {
                pNewItem->pASTNode = NULL;
            }

            pCMe->m_pIStack->pVTbl->Push(pCMe->m_pIStack, pNewItem);
            return (IEcoParser1Action*)1;
        } else if (actionValue < 0) {
            uint32_t packed = (uint32_t)(-actionValue);
            uint32_t ruleIdx = (packed >> 8) - 1;
            uint32_t altIdx = packed & 0xFF;
            uint32_t i = 0;
            IEcoBNF1* pGrammar = pAlgo->pVTbl->get_Grammar(pAlgo);
            IEcoList1* pRules = pGrammar->pVTbl->get_RuleList(pGrammar);
            IEcoBNF1Rule* pRule = (IEcoBNF1Rule*)pRules->pVTbl->Item(pRules, ruleIdx);
            char_t* ruleName = pRule->pVTbl->get_Name(pRule);
            IEcoList1* pChildren = 0;
            IEcoList1* pRuleSet = pRule->pVTbl->get_RuleSet(pRule);
            IEcoList1* pRHS = (IEcoList1*)pRuleSet->pVTbl->Item(pRuleSet, altIdx);
            uint32_t rhsSize = (pRHS != 0) ? pRHS->pVTbl->Count(pRHS) : 0;
            ASTBuildHandler pfn;
            int32_t nextState = 0;

            if (rhsSize == 1) {
                IEcoBNF1Element* pElem = (IEcoBNF1Element*)pRHS->pVTbl->Item(pRHS, 0);
                if (pElem && strcmp(pElem->pVTbl->get_Name(pElem), "epsilon") == 0) {
                    rhsSize = 0;
                }
            }

            pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**)&pChildren);
            if (pChildren) {
                voidptr_t* tempArr = (voidptr_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(voidptr_t) * (rhsSize > 0 ? rhsSize : 1));
                if (tempArr) {
                    for (i = 0; i < rhsSize; i++) {
                        EcoParserStackItem* pPopped = (EcoParserStackItem*)pCMe->m_pIStack->pVTbl->Pop(pCMe->m_pIStack);
                        if (pPopped) {
                            tempArr[rhsSize - 1 - i] = pPopped->pASTNode;
                            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pPopped);
                        } else {
                            tempArr[rhsSize - 1 - i] = 0;
                        }
                    }
                    for (i = 0; i < rhsSize; i++) {
                        pChildren->pVTbl->Add(pChildren, tempArr[i]);
                    }
                    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, tempArr);
                }
            }

            pNewASTNode = 0;
            pfn = FindHandler(ruleName);
            if (pfn) {
                pfn(pCMe, pCMe->m_pIAST, pIToken, pChildren, &pNewASTNode);
            } else if (rhsSize > 0) {
                pNewASTNode = pChildren->pVTbl->Item(pChildren, 0);
            }

            pTop = (EcoParserStackItem*)pCMe->m_pIStack->pVTbl->Peek(pCMe->m_pIStack);
            nextState = pAlgo->pVTbl->get_Goto(pAlgo, pTop->stateId, ruleName);

            pNewItem = (EcoParserStackItem*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(EcoParserStackItem));
            if (pNewItem) {
                pNewItem->stateId = (uint32_t)nextState;
                pNewItem->pASTNode = pNewASTNode;
                pCMe->m_pIStack->pVTbl->Push(pCMe->m_pIStack, pNewItem);
            }

            if (pChildren) pChildren->pVTbl->Release(pChildren);
            continue;
        } else {
            return (IEcoParser1Action*)2;
        }
    }
}

int16_t ECOCALLMETHOD CEcoBSA1Parser_F6E9D8E1_RuleMapping(struct IEcoSyntaxAnalyzer1Parser* me, char_t* ruleName, IEcoSyntaxAnalyzer1RuleMapperPtr_t pIMapper) {
    CEcoBSA1Parser_F6E9D8E1* pCMe = (CEcoBSA1Parser_F6E9D8E1*)me;
    pCMe->m_pIRuleMappers->pVTbl->Set(pCMe->m_pIRuleMappers, ruleName, pIMapper);
    pIMapper->pVTbl->Init(pIMapper, pCMe->m_pIAST);
    return 0;
}

int16_t ECOCALLMETHOD CEcoBSA1Parser_F6E9D8E1_SetConflictResolver(struct IEcoSyntaxAnalyzer1Parser* me, IEcoSyntaxAnalyzer1ConflictResolver* pIResolver) {
    CEcoBSA1Parser_F6E9D8E1* pCMe = (CEcoBSA1Parser_F6E9D8E1*)me;

    if (pCMe->m_pIResolver) {
		pCMe->m_pIResolver->pVTbl->Release(pCMe->m_pIResolver);
	}

    pCMe->m_pIResolver = pIResolver;
    if (pIResolver) {
		pIResolver->pVTbl->AddRef(pIResolver);
	}

    return 0;
}

IEcoUnknown* ECOCALLMETHOD CEcoBSA1Parser_F6E9D8E1_get_Algorithm(struct IEcoSyntaxAnalyzer1Parser* me) {
    return (IEcoUnknown*)((CEcoBSA1Parser_F6E9D8E1*)me)->m_pIAlgorithm;
}

IEcoAST1* ECOCALLMETHOD CEcoBSA1Parser_F6E9D8E1_get_AST(struct IEcoSyntaxAnalyzer1Parser* me) {
    CEcoBSA1Parser_F6E9D8E1* pCMe = (CEcoBSA1Parser_F6E9D8E1*)me;
    return pCMe->m_pIAST;
}

static int16_t ECOCALLMETHOD initCEcoBSA1Parser_F6E9D8E1(CEcoBSA1Parser_F6E9D8E1Ptr_t me, IEcoUnknownPtr_t pIUnkSystem, IEcoParser1LRk* pIAlgorithm) {
    CEcoBSA1Parser_F6E9D8E1* pCMe = (CEcoBSA1Parser_F6E9D8E1*)me;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;
    pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pCMe->m_pIBus);
    pCMe->m_pIBus->pVTbl->QueryInterface(pCMe->m_pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    
    if (pIMemExt) { 
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt); 
        pIMemExt->pVTbl->Release(pIMemExt); 
    }

    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void **)&pCMe->m_pIStr);
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoAST1, 0, &IID_IEcoAST1, (void **)&pCMe->m_pIAST);
    if (pCMe->m_pIAST) {
        pCMe->m_pIAST->pVTbl->new_GlobalScope(pCMe->m_pIAST, 0, (IEcoAST1GlobalScope**)&pCMe->m_pIGlobalScope);
    }
    pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoStack1, 0, &IID_IEcoStack1, (void **)&pCMe->m_pIStack);
    pCMe->m_pIAlgorithm = pIAlgorithm; 
    pIAlgorithm->pVTbl->AddRef(pIAlgorithm);
    return 0;
}

static int16_t ECOCALLMETHOD createCEcoBSA1Parser_F6E9D8E1(CEcoBSA1Parser_F6E9D8E1Ptr_t pCMe, IEcoUnknownPtr_t pIUnkSystem, IEcoUnknownPtr_t pIUnkOuter) {
    return ERR_ECO_SUCCESES;
}

static void ECOCALLMETHOD deleteCEcoBSA1Parser_F6E9D8E1(CEcoBSA1Parser_F6E9D8E1Ptr_t pCMe) {
    if (pCMe) {
        IEcoMemoryAllocator1* pIMem = pCMe->m_pIMem;
        if (pCMe->m_pIAlgorithm) {
			pCMe->m_pIAlgorithm->pVTbl->Release(pCMe->m_pIAlgorithm);
		}
        if (pCMe->m_pIStack) {
			pCMe->m_pIStack->pVTbl->Release(pCMe->m_pIStack);
		}
        if (pCMe->m_pISys) {
			pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
		}
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoSyntaxAnalyzer1Parser Virtual Table */
IEcoSyntaxAnalyzer1ParserVTbl g_x3CED98305D7341B4B7056E0B9C6E108CVTbl_F6E9D8E1 = {
    CEcoBSA1Parser_F6E9D8E1_QueryInterface,
    CEcoBSA1Parser_F6E9D8E1_AddRef,
    CEcoBSA1Parser_F6E9D8E1_Release,
    CEcoBSA1Parser_F6E9D8E1_Parse,
    CEcoBSA1Parser_F6E9D8E1_RuleMapping,
    CEcoBSA1Parser_F6E9D8E1_SetConflictResolver,
    CEcoBSA1Parser_F6E9D8E1_get_Algorithm,
    CEcoBSA1Parser_F6E9D8E1_get_AST
};

CEcoBSA1Parser_F6E9D8E1 g_xCEcoBSA1Parser_F6E9D8E1 = {
    &g_x3CED98305D7341B4B7056E0B9C6E108CVTbl_F6E9D8E1,
    initCEcoBSA1Parser_F6E9D8E1,
    createCEcoBSA1Parser_F6E9D8E1,
    deleteCEcoBSA1Parser_F6E9D8E1,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_pIBus */
    0, /* m_pIStr */
    0, /* m_pIAlgorithm */
    0, /* m_pIProcessing */
    0, /* m_pIAST */
    0, /* m_pILatestToken */
    0, /* m_pIRuleMappers */
    0, /* m_pIResolver */
    0, /* m_pIGlobalScope */
    0, /* m_pIScope */
    0, /* m_pINotCheckedTokens */
    0, /* m_pIStack */
    0  /* m_pTranslationUnit */
};