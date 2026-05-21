/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1CVisitor_28028A01
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoIDL1CVisitor_28028A01
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
#include "CEcoIDL1CVisitor.h"

static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitImportDeclaration(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1VariableDeclaration* pIVariableDeclaration);

/*
 *
 * <сводка>
 *   Функция EmitTranslationUnit
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitTranslationUnit(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1TranslationUnit* pITranslationUnit) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    IEcoAST1BlockTranslationUnitObjects* pIBlockTranslationUnitObjects = 0;
    IEcoAST1GlobalScope* pIGlobalScope = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || pITranslationUnit == 0) {
        return -1;
    }

    pIGlobalScope = pITranslationUnit->pVTbl->get_Scope(pITranslationUnit);
    result = pIGlobalScope->pVTbl->QueryInterface(pIGlobalScope, &IID_IEcoVisitor1Element, (void **)&pIElement);
    if (result == 0 && pIElement != 0) {
        pIElement->pVTbl->Visit(pIElement, me);
        pIElement->pVTbl->Release(pIElement);
    }
    pIBlockTranslationUnitObjects = pITranslationUnit->pVTbl->getObjects(pITranslationUnit);
    result = pIBlockTranslationUnitObjects->pVTbl->QueryInterface(pIBlockTranslationUnitObjects, &IID_IEcoVisitor1Element, (void **)&pIElement);
    if (result == 0 && pIElement != 0) {
        pIElement->pVTbl->Visit(pIElement, me);
        pIElement->pVTbl->Release(pIElement);
    }
    return result;
}

/*
 *
 * <сводка>
 *   Функция EmitBlockTranslationUnitObject
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitBlockTranslationUnitObject(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1BlockTranslationUnitObjects* pIBlockTranslationUnitObjects) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    IEcoAST1TranslationUnitObject* pITranslationUnitObject = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;
    int32_t index = 0;
    uint32_t count = 0;

    /* Проверка указателей */
    if (me == 0 || pIBlockTranslationUnitObjects == 0) {
        return -1;
    }

    count = pIBlockTranslationUnitObjects->pVTbl->get_Count(pIBlockTranslationUnitObjects);
    for (index = 0; index < count; ++index) {
        IEcoAST1VariableDeclaration* pIVarDecl = 0;

        pITranslationUnitObject = pIBlockTranslationUnitObjects->pVTbl->get_Object(pIBlockTranslationUnitObjects, index);
        if (pITranslationUnitObject == 0) continue;
        
        result = pITranslationUnitObject->pVTbl->QueryInterface(pITranslationUnitObject, &IID_IEcoAST1VariableDeclaration, (void**)&pIVarDecl);
        if (result == 0 && pIVarDecl != 0) {
            CEcoIDL1CVisitor_28028A01_EmitImportDeclaration(me, pIVarDecl);
            pIVarDecl->pVTbl->Release(pIVarDecl);
        } else {
            result = pITranslationUnitObject->pVTbl->QueryInterface(pITranslationUnitObject, &IID_IEcoVisitor1Element, (void **)&pIElement);
            if (result == 0 && pIElement != 0) {
                pIElement->pVTbl->Visit(pIElement, me);
                pIElement->pVTbl->Release(pIElement);
            }
        }
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция EmitGlobalScope
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitGlobalScope(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1GlobalScope* pIGlobalScope) {
    /* Проверка указателей */
    if (me == 0 || pIGlobalScope == 0) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция EmitStructOrUnionDeclaration
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitStructOrUnionDeclaration(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1StructOrUnionDeclaration* pIStructOrUnionDeclaration) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    IEcoAST1BlockDeclarations* pMethodsBlock = 0;
    IEcoAST1Declaration* pMethod = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;
    int32_t index = 0;
    char_t* pszName = 0;
    uint32_t iSize = 0;
    char_t* pszStructHeader = "typedef struct ";
    char_t* pszUnknownHeader1 = "    /* IEcoUnknown */\r\n    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ ";
    char_t* pszUnknownHeader2 = "Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);\r\n    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ ";
    char_t* pszUnknownHeader3 = "Ptr_t me);\r\n    uint32_t (ECOCALLMETHOD *Release )(/* in */ ";
    char_t* pszUnknownHeader4 = "Ptr_t me);\r\n    /* ";
    char_t* pszOutput = 0;
    IEcoAST1BlockExpressions* pSizes = 0;
    IEcoAST1StringLiteral* pStringLiteral = 0;
    char_t* pszUUID = 0;
    uint32_t uuidIndex = 0;
    uint8_t uuidBytes[16] = {0};

    /* Проверка указателей */
    if (me == 0 || pIStructOrUnionDeclaration == 0) {
        return -1;
    }

    pSizes = pIStructOrUnionDeclaration->pVTbl->get_Sizes(pIStructOrUnionDeclaration);
    if (pSizes != 0) {
        IEcoAST1Expression* pExpr = pSizes->pVTbl->get_Expression(pSizes, 0);
        while (pExpr != 0) {
            result = pExpr->pVTbl->QueryInterface(pExpr, &IID_IEcoAST1StringLiteral, (void**)&pStringLiteral);
            if (result == 0 && pStringLiteral != 0) {
                pszUUID = pStringLiteral->pVTbl->get_Value(pStringLiteral);
                if (pszUUID) {
                    const char_t* p = pszUUID;
                    int bytePos = 0;
                    uint8_t val = 0;
                    int nibble = 0;
                    while (*p && bytePos < 16) {
                        if (*p >= '0' && *p <= '9') {
                            val = (val << 4) | (*p - '0');
                            nibble++;
                        } else if (*p >= 'A' && *p <= 'F') {
                            val = (val << 4) | (*p - 'A' + 10);
                            nibble++;
                        } else if (*p >= 'a' && *p <= 'f') {
                            val = (val << 4) | (*p - 'a' + 10);
                            nibble++;
                        } 
                        if (nibble == 2) {
                            uuidBytes[bytePos++] = val;
                            val = 0;
                            nibble = 0;
                        }
                        p++;
                    }
                }
                pStringLiteral->pVTbl->Release(pStringLiteral);
                break;
            }
            uuidIndex++;
            pExpr = pSizes->pVTbl->get_Expression(pSizes, uuidIndex);
        }
    }

    pszName = pIStructOrUnionDeclaration->pVTbl->get_IdentifierName(pIStructOrUnionDeclaration);
    
    if (pCMe->m_Name != 0) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCMe->m_Name);
        pCMe->m_Name = 0;
    }
    pCMe->m_Name = pCMe->m_pIStr->pVTbl->Clone(pCMe->m_pIStr, pszName);
    
    if (pszUUID != 0) {
        int i;
        char_t* pszUUIDOutput = 0;
        char_t* pszComment = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, 0, "\n/* ");
        pszComment = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszComment, pszName);
        pszComment = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszComment, " IID = {");
        pszComment = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszComment, pszUUID);
        pszComment = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszComment, "} */\r\n");
        iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszComment);
        pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszComment, &iSize);
        pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszComment);

        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, 0, "#ifndef __IID_");
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, pszName);
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, "\r\n");
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, "static const UGUID IID_");
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, pszName);
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, " = {0x01, 0x10, {");
        
        for (i = 0; i < 16; i++) {
            char hex[16];
            sprintf(hex, "0x%02X", uuidBytes[i]);
            pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, hex);
            if (i < 15) pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, ", ");
        }
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, "}};\r\n");
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, "#endif /* __IID_");
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, pszName);
        pszUUIDOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszUUIDOutput, " */\r\n\r\n");

        iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszUUIDOutput);
        pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszUUIDOutput, &iSize);
        pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszUUIDOutput);
    }
	
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszStructHeader);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "* ");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "Ptr_t;\r\n\r\n");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszStructHeader);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "VTbl {\r\n");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszUnknownHeader1);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszUnknownHeader2);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszUnknownHeader3);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszUnknownHeader4);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, " */\r\n");
    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszOutput);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszOutput, &iSize);
    pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszOutput);
    pszOutput = 0;

    pMethodsBlock = pIStructOrUnionDeclaration->pVTbl->get_Params(pIStructOrUnionDeclaration);
    if (pMethodsBlock != 0) {
        pMethod = pMethodsBlock->pVTbl->get_Declaration(pMethodsBlock, index);
        while (pMethod != 0 ) {
            result = pMethod->pVTbl->QueryInterface(pMethod, &IID_IEcoVisitor1Element, (void **)&pIElement);
            if (result == 0 && pIElement != 0) {
                pIElement->pVTbl->Visit(pIElement, me);
                pIElement->pVTbl->Release(pIElement);
            }

            index++;
            pMethod = pMethodsBlock->pVTbl->get_Declaration(pMethodsBlock, index);
        }
    }

    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "\r\n} ");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "VTbl;\r\n\r\ninterface ");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, " {\r\n    struct ");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "VTbl *pVTbl;\r\n} ");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, ";\r\n");
    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszOutput);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszOutput, &iSize);
    pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszOutput);
    pszOutput = 0;

    return result;
}

/*
 *
 * <сводка>
 *   Функция EmitFunctionDeclaration
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitFunctionDeclaration(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1FunctionDeclaration* pIFunctionDeclaration) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    IEcoAST1Type* pReturnType = 0;
    IEcoAST1BlockDeclarations* pParams = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;
    char_t* pszName = 0;
    uint32_t iSize = 0;
    char_t* pszOutput = 0;

    /* Проверка указателей */
    if (me == 0 || pIFunctionDeclaration == 0) {
        return -1;
    }

    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "    ");
    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszOutput);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszOutput, &iSize);
    pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszOutput);
    pszOutput = 0;

    pReturnType = pIFunctionDeclaration->pVTbl->get_ReturnType(pIFunctionDeclaration);
    if (pReturnType != 0) {
        result = pReturnType->pVTbl->QueryInterface(pReturnType, &IID_IEcoVisitor1Element, (void **)&pIElement);
        if (result == 0 && pIElement != 0) {
            pIElement->pVTbl->Visit(pIElement, me);
            pIElement->pVTbl->Release(pIElement);
        }
    }

    pszName = pIFunctionDeclaration->pVTbl->get_IdentifierName(pIFunctionDeclaration);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, " (ECOCALLMETHOD *");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, ")(/* in */ ");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pCMe->m_Name);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "Ptr_t me");
    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszOutput);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszOutput, &iSize);
    pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszOutput);
    pszOutput = 0;

    pParams = pIFunctionDeclaration->pVTbl->get_Params(pIFunctionDeclaration);
    if (pParams != 0) {
        result = pParams->pVTbl->QueryInterface(pParams, &IID_IEcoVisitor1Element, (void **)&pIElement);
        if (result == 0 && pIElement != 0) {
            pIElement->pVTbl->Visit(pIElement, me);
            pIElement->pVTbl->Release(pIElement);
        }
    }

    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, ");\r\n");
    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszOutput);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszOutput, &iSize);
    pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszOutput);
    pszOutput = 0;

    return result;
}

/*
 *
 * <сводка>
 *   Функция EmitNumberType
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitNumberType(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1NumberType* pINumberType) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    int16_t result = 0;
    int16_t iType = 0;
    uint32_t iTypeSize = 0;
    uint32_t iSize = 0;
    char_t* pszOutput = 0;

    /* Проверка указателей */
    if (me == 0 || pINumberType == 0) {
        return -1;
    }
    iType = pINumberType->pVTbl->get_IntegralType(pINumberType);
    if (!pINumberType->pVTbl->IsConst(pINumberType)) {
        pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "const ");
    }
    if (!pINumberType->pVTbl->IsSigned(pINumberType) && iType != ECO__AST1_TYPE_VOID) {
        pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "u");
    }
    switch (iType) {
        case ECO__AST1_TYPE_VOID:   /* void */
            pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "void");
        break;
        case ECO__AST1_TYPE_CHAR:       /* char */
            pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "char_t");
        break;
        case ECO__AST1_TYPE_SHORT:      /* short */
            pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "short_t");
        break;
        case ECO__AST1_TYPE_INT:        /* int */
            iTypeSize = pINumberType->pVTbl->get_Size(pINumberType);
            if (iTypeSize == 8) {
                pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "int8_t");
            }
            else if (iTypeSize == 16) {
                pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "int16_t");
            }
            else if (iTypeSize == 32) {
                pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "int32_t");
            }
            else if (iTypeSize == 64) {
                pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "int32_t");
            }
        break;
        case ECO__AST1_TYPE_LONG:       /* long */
            pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "long_t");
        break;
        case ECO__AST1_TYPE_LONG_LONG:  /* long long */
            pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "long long");
        break;
        case ECO__AST1_TYPE_FLOAT:      /* float */
            pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "float_t");
        break;
        case ECO__AST1_TYPE_DOUBLE:     /* double */
            pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "double_t");
        break;
        case ECO__AST1_TYPE_LONG_DOUBLE: /* long double */
            pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "long double");
        break;
     }

    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszOutput);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszOutput, &iSize);
    pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszOutput);
    pszOutput = 0;

    return result;
}

/*
 *
 * <сводка>
 *   Функция EmitPointerType
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitPointerType(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1PointerType* pIPointerType) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    IEcoAST1Type* pIType = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;
    uint32_t iSize = 1;

    /* Проверка указателей */
    if (me == 0 || pIPointerType == 0) {
        return -1;
    }

    pIType = pIPointerType->pVTbl->get_IntegralType(pIPointerType);
    if (pIType != 0) {
        result = pIType->pVTbl->QueryInterface(pIType, &IID_IEcoVisitor1Element, (void **)&pIElement);
        if (result == 0 && pIElement != 0) {
            pIElement->pVTbl->Visit(pIElement, me);
            pIElement->pVTbl->Release(pIElement);
        }
    }

    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, "*", &iSize);

    return result;
}

/*
 *
 * <сводка>
 *   Функция EmitBlockDeclarations
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitBlockDeclarations(/* in */ struct IEcoVisitor1* me, /* in */ IEcoAST1BlockDeclarations* pIBlockDeclarations) {
    IEcoVisitor1Element* pIElement = 0;
    IEcoAST1Declaration* pIDeclaration = 0;
    int16_t result = 0;
    uint32_t index = 0;

    /* Проверка указателей */
    if (me == 0 || pIBlockDeclarations == 0) {
        return -1;
    }

    pIDeclaration = pIBlockDeclarations->pVTbl->get_Declaration(pIBlockDeclarations, index);
    while (pIDeclaration != 0 ) {
        result = pIDeclaration->pVTbl->QueryInterface(pIDeclaration, &IID_IEcoVisitor1Element, (void **)&pIElement);
        if (result == 0 && pIElement != 0) {
            pIElement->pVTbl->Visit(pIElement, me);
            pIElement->pVTbl->Release(pIElement);
        }

       index++;
       pIDeclaration = pIBlockDeclarations->pVTbl->get_Declaration(pIBlockDeclarations, index);
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция EmitVariableDeclaration
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitVariableDeclaration(/* in */ struct IEcoVisitor1* me, /* in */ IEcoAST1VariableDeclaration* pIVariableDeclaration) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    IEcoAST1Type* pIType = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;
    uint32_t iSize = 0;
    char_t* pszOutput = 0;
    char_t* pszName = 0;

    /* Проверка указателей */
    if (me == 0 || pIVariableDeclaration == 0) {
        return -1;
    }

    iSize = 2;
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, ", ", &iSize);

    pIType = pIVariableDeclaration->pVTbl->get_Type(pIVariableDeclaration);
    if (pIType != 0) {
        result = pIType->pVTbl->QueryInterface(pIType, &IID_IEcoVisitor1Element, (void **)&pIElement);
        if (result == 0 && pIElement != 0) {
            pIElement->pVTbl->Visit(pIElement, me);
            pIElement->pVTbl->Release(pIElement);
        }
    }

    pszName = pIVariableDeclaration->pVTbl->get_IdentifierName(pIVariableDeclaration);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, " ");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszOutput);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszOutput, &iSize);
    pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszOutput);
    pszOutput = 0;

    return result;
}

/*
 *
 * <summary>
 *   EmitImportDeclaration
 * </summary>
 *
 * <description>
 *   Генерация #include для импортированного IDL-файла
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_EmitImportDeclaration(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1VariableDeclaration* pIVariableDeclaration) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    char_t* pszName = 0;
    uint32_t len = 0;
    uint32_t iSize = 0;
    char_t* pszInclude = 0;
    char_t* pszHeader = 0;
    char_t* pszBase = 0;

    if (me == 0 || pIVariableDeclaration == 0) return -1;

    pszName = pIVariableDeclaration->pVTbl->get_IdentifierName(pIVariableDeclaration);
    if (pszName == 0) return -1;

    len = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszName);
    if (len > 0) {
        uint32_t start = 0;
        uint32_t end = len;
		uint32_t base_len = 0;

        if (pszName[0] == '"') {
            start = 1;
        }
        if (len > 1 && pszName[len - 1] == '"') {
            end = len - 1;
        }

        base_len = end - start;
        if (base_len > 4 && pszName[end - 4] == '.' && pszName[end - 3] == 'i' && pszName[end - 2] == 'd' && pszName[end - 1] == 'l') {

            pszBase = pCMe->m_pIStr->pVTbl->Substring(pCMe->m_pIStr, pszName, start, base_len - 4);
            if (pszBase) {
                pszHeader = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszBase, ".h");
            }
            if (pszHeader) {
                pszInclude = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszInclude, "#include \"");
                pszInclude = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszInclude, pszHeader);
                pszInclude = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszInclude, "\"\r\n");

                iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszInclude);
                pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszInclude, &iSize);

                pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszInclude);
                pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszHeader);
            }
        }
    }
    return 0;
}

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoIDL1CVisitor interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_QueryInterface(/* in */ IEcoVisitor1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoVisitor1) ) {
        *ppv = &pCMe->m_pVTblIVisitor;
        pCMe->m_pVTblIVisitor->AddRef((IEcoVisitor1Ptr_t)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIVisitor;
        pCMe->m_pVTblIVisitor->AddRef((IEcoVisitor1Ptr_t)pCMe);
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
 *   AddRef function for the IEcoIDL1CVisitor interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_AddRef(/* in */ IEcoVisitor1Ptr_t me) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;

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
 *   Release function for the IEcoIDL1CVisitor interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_Release(/* in */ IEcoVisitor1Ptr_t me) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;

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

/*
 *
 * <сводка>
 *   Функция Accept
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1CVisitor_28028A01_Accept(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoUnknown* pIUnk) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    IEcoAST1SyntaxObject* pISyntaxObject = 0;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || pIUnk == 0) {
        return -1;
    }

    result = pIUnk->pVTbl->QueryInterface(pIUnk, &IID_IEcoAST1SyntaxObject, (void**)&pISyntaxObject);

    if (result == 0 && pISyntaxObject != 0) {
        if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ArrayType) ) {
            //CEcoIDL1CVisitor_28028A01_EmitArrayType((IEcoVisitor1*)pCMe, (IEcoAST1ArrayType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BinaryExpression) ) {
            //CEcoIDL1CVisitor_28028A01_EmitBinaryExpression((IEcoVisitor1*)pCMe, (IEcoAST1BinaryExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockDeclarations) ) {
            CEcoIDL1CVisitor_28028A01_EmitBlockDeclarations((IEcoVisitor1*)pCMe, (IEcoAST1BlockDeclarations*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockExpressions) ) {
            //CEcoIDL1CVisitor_28028A01_EmitBlockExpressions((IEcoVisitor1*)pCMe, (IEcoAST1BlockExpressions*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockStatements) ) {
            //CEcoIDL1CVisitor_28028A01_EmitBlockStatements((IEcoVisitor1*)pCMe, (IEcoAST1BlockStatements*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockTranslationUnitObjects) ) {
            CEcoIDL1CVisitor_28028A01_EmitBlockTranslationUnitObject((IEcoVisitor1*)pCMe, (IEcoAST1BlockTranslationUnitObjects*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockTypes) ) {
            //CEcoIDL1CVisitor_28028A01_EmitBlockTypes((IEcoVisitor1*)pCMe, (IEcoAST1BlockTypes*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BreakStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitBreakStatement((IEcoVisitor1*)pCMe, (IEcoAST1BreakStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1CaseStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitCaseStatement((IEcoVisitor1*)pCMe, (IEcoAST1CaseStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1CastExpression) ) {
            //CEcoIDL1CVisitor_28028A01_EmitCastExpression((IEcoVisitor1*)pCMe, (IEcoAST1CastExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1CharacterLiteral) ) {
            //CEcoIDL1CVisitor_28028A01_EmitCharacterLiteral((IEcoVisitor1*)pCMe, (IEcoAST1CharacterLiteral*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1CompoundStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitCompoundStatement((IEcoVisitor1*)pCMe, (IEcoAST1CompoundStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ConditionalExpression) ) {
            //CEcoIDL1CVisitor_28028A01_EmitConditionalExpression((IEcoVisitor1*)pCMe, (IEcoAST1ConditionalExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ContinueStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitContinueStatement((IEcoVisitor1*)pCMe, (IEcoAST1ContinueStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Declaration) ) {
            //CEcoIDL1CVisitor_28028A01_EmitDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1Declaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1DefaultStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitDefaultStatement((IEcoVisitor1*)pCMe, (IEcoAST1DefaultStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1DoWhileStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitDoWhileStatement((IEcoVisitor1*)pCMe, (IEcoAST1DoWhileStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1EnumDeclaration) ) {
            //CEcoIDL1CVisitor_28028A01_EmitEnumDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1EnumDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1EnumType) ) {
            //CEcoIDL1CVisitor_28028A01_EmitEnumType((IEcoVisitor1*)pCMe, (IEcoAST1EnumType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Expression) ) {
            //CEcoIDL1CVisitor_28028A01_EmitExpression((IEcoVisitor1*)pCMe, (IEcoAST1Expression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ExpressionableDeclaration) ) {
            //CEcoIDL1CVisitor_28028A01_EmitExpressionableDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1ExpressionableDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FloatLiteral) ) {
            //CEcoIDL1CVisitor_28028A01_EmitFloatLiteral((IEcoVisitor1*)pCMe, (IEcoAST1FloatLiteral*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ForStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitForStatement((IEcoVisitor1*)pCMe, (IEcoAST1ForStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FunctionCall) ) {
            //CEcoIDL1CVisitor_28028A01_EmitFunctionCall((IEcoVisitor1*)pCMe, (IEcoAST1FunctionCall*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FunctionDeclaration) ) {
            CEcoIDL1CVisitor_28028A01_EmitFunctionDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1FunctionDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FunctionDefinition) ) {
            //CEcoIDL1CVisitor_28028A01_EmitFunctionDefinition((IEcoVisitor1*)pCMe, (IEcoAST1FunctionDefinition*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FunctionType) ) {
            //CEcoIDL1CVisitor_28028A01_EmitFunctionType((IEcoVisitor1*)pCMe, (IEcoAST1FunctionType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1GlobalScope) ) {
            CEcoIDL1CVisitor_28028A01_EmitGlobalScope((IEcoVisitor1*)pCMe, (IEcoAST1GlobalScope*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1GoToStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitGoToStatement((IEcoVisitor1*)pCMe, (IEcoAST1GoToStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1IfStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitIfStatement((IEcoVisitor1*)pCMe, (IEcoAST1IfStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1IntegerLiteral) ) {
            //CEcoIDL1CVisitor_28028A01_EmitIntegerLiteral((IEcoVisitor1*)pCMe, (IEcoAST1IntegerLiteral*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1LabelStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitLabelStatement((IEcoVisitor1*)pCMe, (IEcoAST1LabelStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Literal) ) {
            //CEcoIDL1CVisitor_28028A01_EmitLiteral((IEcoVisitor1*)pCMe, (IEcoAST1Literal*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1MemberSelection) ) {
            //CEcoIDL1CVisitor_28028A01_EmitMemberSelection((IEcoVisitor1*)pCMe, (IEcoAST1MemberSelection*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1NullExpression) ) {
            //CEcoIDL1CVisitor_28028A01_EmitNullExpression((IEcoVisitor1*)pCMe, (IEcoAST1NullExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1NumberType) ) {
            CEcoIDL1CVisitor_28028A01_EmitNumberType((IEcoVisitor1*)pCMe, (IEcoAST1NumberType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1PointerType) ) {
            CEcoIDL1CVisitor_28028A01_EmitPointerType((IEcoVisitor1*)pCMe, (IEcoAST1PointerType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ReturnStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitReturnStatement((IEcoVisitor1*)pCMe, (IEcoAST1ReturnStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Scope) ) {
            //CEcoIDL1CVisitor_28028A01_EmitScope((IEcoVisitor1*)pCMe, (IEcoAST1Scope*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SingleStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitSingleStatement((IEcoVisitor1*)pCMe, (IEcoAST1SingleStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SizeofExpression) ) {
            //CEcoIDL1CVisitor_28028A01_EmitSizeofExpression((IEcoVisitor1*)pCMe, (IEcoAST1SizeofExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SizeofType) ) {
            //CEcoIDL1CVisitor_28028A01_EmitSizeofType((IEcoVisitor1*)pCMe, (IEcoAST1SizeofType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Statement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitStatement((IEcoVisitor1*)pCMe, (IEcoAST1Statement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1StringLiteral) ) {
            //CEcoIDL1CVisitor_28028A01_EmitStringLiteral((IEcoVisitor1*)pCMe, (IEcoAST1StringLiteral*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1StructOrUnionDeclaration) ) {
            CEcoIDL1CVisitor_28028A01_EmitStructOrUnionDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1StructOrUnionDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1StructOrUnionType) ) {
            //CEcoIDL1CVisitor_28028A01_EmitStructOrUnionType((IEcoVisitor1*)pCMe, (IEcoAST1StructOrUnionType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SwitchStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitSwitchStatement((IEcoVisitor1*)pCMe, (IEcoAST1SwitchStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SyntaxObject) ) {
            //CEcoIDL1CVisitor_28028A01_EmitSyntaxObject((IEcoVisitor1*)pCMe, (IEcoAST1SyntaxObject*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1TranslationUnit) ) {
            CEcoIDL1CVisitor_28028A01_EmitTranslationUnit((IEcoVisitor1*)pCMe, (IEcoAST1TranslationUnit*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1TranslationUnitObject) ) {
            //CEcoIDL1CVisitor_28028A01_EmitTranslationUnitObject((IEcoVisitor1*)pCMe, (IEcoAST1TranslationUnitObject*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1TypedefDeclaration) ) {
            //CEcoIDL1CVisitor_28028A01_EmitTypedefDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1TypedefDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1TypedefType) ) {
            //CEcoIDL1CVisitor_28028A01_EmitTypedefType((IEcoVisitor1*)pCMe, (IEcoAST1TypedefType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1UnaryExpression) ) {
            //CEcoIDL1CVisitor_28028A01_EmitUnaryExpression((IEcoVisitor1*)pCMe, (IEcoAST1UnaryExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1VariableDeclaration) ) {
            CEcoIDL1CVisitor_28028A01_EmitVariableDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1VariableDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1VariableDefinition) ) {
            //CEcoIDL1CVisitor_28028A01_EmitVariableDefinition((IEcoVisitor1*)pCMe, (IEcoAST1VariableDefinition*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1WhileStatement) ) {
            //CEcoIDL1CVisitor_28028A01_EmitWhileStatement((IEcoVisitor1*)pCMe, (IEcoAST1WhileStatement*)pISyntaxObject);
        } else {
            result = -1;
        }

        pISyntaxObject->pVTbl->Release(pISyntaxObject);
    } else {
        result = -1;
    }

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
static int16_t ECOCALLMETHOD initCEcoIDL1CVisitor_28028A01(/*in*/ CEcoIDL1CVisitor_28028A01Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoFile1* pIFile) {
    CEcoIDL1CVisitor_28028A01* pCMe = (CEcoIDL1CVisitor_28028A01*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = ERR_ECO_POINTER;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    /* Pointer Validation */
    if (me == 0 || pIFile == 0) {
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

    result = pIBus->pVTbl->QueryComponent(pIBus,  &CID_EcoString1, 0, &IID_IEcoString1, (void**) &pCMe->m_pIStr);
    /* Check */
    if (result != 0 || pCMe->m_pIStr == 0) {
        result = ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    pCMe->m_pIFile = pIFile;

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
static int16_t ECOCALLMETHOD createCEcoIDL1CVisitor_28028A01(/* in */ CEcoIDL1CVisitor_28028A01Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoIDL1CVisitor_28028A01(/* in */ CEcoIDL1CVisitor_28028A01Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
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

/* IEcoIDL1CVisitor Virtual Table */
IEcoVisitor1VTbl g_xA6105EF4C95F47F0BA187C6EB7D204D2VTbl_28028A01 = {
    CEcoIDL1CVisitor_28028A01_QueryInterface,
    CEcoIDL1CVisitor_28028A01_AddRef,
    CEcoIDL1CVisitor_28028A01_Release,
    CEcoIDL1CVisitor_28028A01_Accept
};


/* Object Instance */
CEcoIDL1CVisitor_28028A01 g_xCEcoIDL1CVisitor_28028A01 = {
    &g_xA6105EF4C95F47F0BA187C6EB7D204D2VTbl_28028A01,
    initCEcoIDL1CVisitor_28028A01,
    createCEcoIDL1CVisitor_28028A01,
    deleteCEcoIDL1CVisitor_28028A01,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_pIStr */
    0, /* m_pIFile */
    0  /* m_Name */
};