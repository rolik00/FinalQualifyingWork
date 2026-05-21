/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1JavaVisitor_286DCE90
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoIDL1JavaVisitor_286DCE90
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
#include "CEcoIDL1JavaVisitor.h"

/* Вспомогательная функция для анализа цепочки типов. */
static IEcoAST1Type* GetBaseTypeInfo(IEcoAST1Type* pIType, int16_t* pDepth, int16_t* pIntegralType, uint32_t* pSize, bool_t* pIsSigned) {
    IEcoAST1PointerType* pIPointer = 0;
    IEcoAST1NumberType* pINumber = 0;
    IEcoAST1Type* pNext = 0;

    if (pIType == 0) {
		return 0;
	}

    if (pIType->pVTbl->QueryInterface(pIType, &IID_IEcoAST1PointerType, (void**)&pIPointer) == 0) {
        (*pDepth)++;
        pNext = pIPointer->pVTbl->get_IntegralType(pIPointer);
        pIPointer->pVTbl->Release(pIPointer);
        return GetBaseTypeInfo(pNext, pDepth, pIntegralType, pSize, pIsSigned);
    } 
    
    if (pIType->pVTbl->QueryInterface(pIType, &IID_IEcoAST1NumberType, (void**)&pINumber) == 0) {
        *pIntegralType = pINumber->pVTbl->get_IntegralType(pINumber);
        *pSize = pINumber->pVTbl->get_Size(pINumber);
        *pIsSigned = pINumber->pVTbl->IsSigned(pINumber);
        pINumber->pVTbl->Release(pINumber);
    }

    return pIType;
}

/* Маппинг базовых типов */
static const char_t* GetJavaPrimitiveName(int16_t iType, uint32_t iTypeSize, bool_t isSigned) {
    switch (iType) {
        case ECO__AST1_TYPE_VOID: return "void";
        case ECO__AST1_TYPE_CHAR: return "char";
        case ECO__AST1_TYPE_SHORT: return "short";
        case ECO__AST1_TYPE_INT:
            if (iTypeSize == 8) return "byte";
            if (iTypeSize == 16) return "short";
            if (iTypeSize == 32) return isSigned ? "int" : "long";
            if (iTypeSize == 64) return "long";
            return "int";
        case ECO__AST1_TYPE_LONG: return "long";
        case ECO__AST1_TYPE_FLOAT: return "float";
        case ECO__AST1_TYPE_DOUBLE: return "double";
        default: return "Object";
    }
}

/*
 *
 * <summary>
 *   EmitImportDeclaration
 * </summary>
 *
 * <description>
 *   Генерация import для импортированного IDL-файла в Java
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitImportDeclaration(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1VariableDeclaration* pIVariableDeclaration) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    char_t* pszName = 0;
    uint32_t len = 0;
    uint32_t iSize = 0;
    char_t* pszImport = 0;
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
                pszImport = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszImport, "import ");
                pszImport = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszImport, pszBase);
                pszImport = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszImport, ";\r\n");

                iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszImport);
                pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszImport, &iSize);

                pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszImport);
                pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszBase);
            }
        }
    }
    return 0;
}

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
static int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitTranslationUnit(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1TranslationUnit* pITranslationUnit) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    IEcoAST1BlockTranslationUnitObjects* pIBlockTranslationUnitObjects = 0;
    IEcoAST1GlobalScope* pIGlobalScope = 0;
    IEcoAST1SyntaxObject* pISyntaxObject = 0;
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
static int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitBlockTranslationUnitObject(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1BlockTranslationUnitObjects* pIBlockTranslationUnitObjects) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
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
            CEcoIDL1JavaVisitor_286DCE90_EmitImportDeclaration(me, pIVarDecl);
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
static int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitGlobalScope(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1GlobalScope* pIGlobalScope) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || pIGlobalScope == 0) {
        return -1;
    }

    return result;
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
static int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitStructOrUnionDeclaration(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1StructOrUnionDeclaration* pIStructOrUnionDeclaration) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    IEcoAST1BlockDeclarations* pMethodsBlock = 0;
    IEcoAST1Declaration* pMethod = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;
    int32_t index = 0;
    char_t* pszName = 0;
    uint32_t iSize = 0;
    char_t* pszOutput = 0;
    IEcoAST1BlockExpressions* pSizes = 0;
    IEcoAST1StringLiteral* pStringLiteral = 0;
    char_t* pszUUID = 0;
    uint32_t uuidIndex = 0;

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
        pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "\n@EcoNative(uuid = \"");
        pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszUUID);
        pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "\")\r\npublic interface ");
    } else {
        pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "@EcoNative\r\npublic interface ");
    }
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, " extends IEcoUnknown {\r\n");

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

    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "\r\n}\r\n");
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
static int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitFunctionDeclaration(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1FunctionDeclaration* pIFunctionDeclaration) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
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
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, " ");
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, pszName);
    pszOutput = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszOutput, "(");
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
int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitNumberType(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1NumberType* pINumberType) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    uint32_t iSize = 0;
    const char_t* pszJavaType = GetJavaPrimitiveName(pINumberType->pVTbl->get_IntegralType(pINumberType), pINumberType->pVTbl->get_Size(pINumberType), pINumberType->pVTbl->IsSigned(pINumberType));

    /* Проверка указателей */
    if (me == 0 || pINumberType == 0) {
        return -1;
    }
    
    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, (char_t*)pszJavaType);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, (char_t*)pszJavaType, &iSize);

    return 0;
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
int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitPointerType(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoAST1PointerType* pIPointerType) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    IEcoAST1Type* pBaseTypeObj = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t depth = 0;
    int16_t iIntegralType = -1;
    uint32_t iTypeSize = 0;
    bool_t isSigned = 0;
    uint32_t iSize = 0;
    int16_t i = 0;

    /* Проверка указателей */
    if (me == 0 || pIPointerType == 0) {
        return -1;
    }

    pBaseTypeObj = GetBaseTypeInfo((IEcoAST1Type*)pIPointerType, &depth, &iIntegralType, &iTypeSize, &isSigned);

    if (iIntegralType == ECO__AST1_TYPE_CHAR) {
        if (depth == 1) {
            iSize = 6;
            pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, "String", &iSize);
            return 0;
        } else if (depth == 2) {
            iSize = 8;
            pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, "String[]", &iSize);
            return 0;
        }
    }

    if (iIntegralType == ECO__AST1_TYPE_VOID) {
        iSize = 6;
        pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, "Object", &iSize);
        for (i = 0; i < depth - 1; i++) {
            iSize = 2;
            pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, "[]", &iSize);
        }
        return 0;
    }

	if (pBaseTypeObj) {
        if (pBaseTypeObj->pVTbl->QueryInterface(pBaseTypeObj, &IID_IEcoVisitor1Element, (void **)&pIElement) == 0) {
            pIElement->pVTbl->Visit(pIElement, me);
            pIElement->pVTbl->Release(pIElement);
        }

        if (iIntegralType != -1) {
            for (i = 0; i < depth; i++) {
                iSize = 2;
                pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, "[]", &iSize);
            }
        } else {
            for (i = 0; i < depth - 1; i++) {
                iSize = 2;
                pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, "[]", &iSize);
            }
        }
    }

    return 0;
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
int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitBlockDeclarations(/* in */ struct IEcoVisitor1* me, /* in */ IEcoAST1BlockDeclarations* pIBlockDeclarations) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    IEcoAST1SyntaxObject* pISyntaxObject = 0;
    IEcoVisitor1Element* pIElement = 0;
    IEcoAST1Declaration* pIDeclaration = 0;
    int16_t result = 0;
    uint32_t index = 0;
    uint32_t iSize = 0;

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
       if (pIDeclaration != 0) {
           iSize = 2;
           pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, ", ", &iSize);
       }
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
int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_EmitVariableDeclaration(/* in */ struct IEcoVisitor1* me, /* in */ IEcoAST1VariableDeclaration* pIVariableDeclaration) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    IEcoAST1Type* pIType = 0;
    IEcoVisitor1Element* pIElement = 0;
    char_t* pszName = 0;
    uint32_t iSize = 0;

    /* Проверка указателей */
    if (me == 0 || pIVariableDeclaration == 0) {
        return -1;
    }

    pIType = pIVariableDeclaration->pVTbl->get_Type(pIVariableDeclaration);
    if (pIType != 0) {
        if (pIType->pVTbl->QueryInterface(pIType, &IID_IEcoVisitor1Element, (void **)&pIElement) == 0) {
            pIElement->pVTbl->Visit(pIElement, me);
            pIElement->pVTbl->Release(pIElement);
        }
    }

    pszName = pIVariableDeclaration->pVTbl->get_IdentifierName(pIVariableDeclaration);
    iSize = 1;
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, " ", &iSize);
    iSize = pCMe->m_pIStr->pVTbl->RetrieveSize(pCMe->m_pIStr, pszName);
    pCMe->m_pIFile->pVTbl->Write(pCMe->m_pIFile, pszName, &iSize);

    return 0;
}

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoIDL1JavaVisitor interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_QueryInterface(/* in */ IEcoVisitor1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;

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
 *   AddRef function for the IEcoIDL1JavaVisitor interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_AddRef(/* in */ IEcoVisitor1Ptr_t me) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;

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
 *   Release function for the IEcoIDL1JavaVisitor interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_Release(/* in */ IEcoVisitor1Ptr_t me) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;

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
static int16_t ECOCALLMETHOD CEcoIDL1JavaVisitor_286DCE90_Accept(/* in */ IEcoVisitor1Ptr_t me, /* in */ IEcoUnknown* pIUnk) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
    IEcoAST1SyntaxObject* pISyntaxObject = 0;
    IEcoVisitor1Element* pIElement = 0;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 || pIUnk == 0) {
        return -1;
    }

    result = pIUnk->pVTbl->QueryInterface(pIUnk, &IID_IEcoAST1SyntaxObject, (void**)&pISyntaxObject);

    if (result == 0 && pISyntaxObject != 0) {
        if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ArrayType) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitArrayType((IEcoVisitor1*)pCMe, (IEcoAST1ArrayType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BinaryExpression) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitBinaryExpression((IEcoVisitor1*)pCMe, (IEcoAST1BinaryExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockDeclarations) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitBlockDeclarations((IEcoVisitor1*)pCMe, (IEcoAST1BlockDeclarations*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockExpressions) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitBlockExpressions((IEcoVisitor1*)pCMe, (IEcoAST1BlockExpressions*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockStatements) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitBlockStatements((IEcoVisitor1*)pCMe, (IEcoAST1BlockStatements*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockTranslationUnitObjects) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitBlockTranslationUnitObject((IEcoVisitor1*)pCMe, (IEcoAST1BlockTranslationUnitObjects*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BlockTypes) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitBlockTypes((IEcoVisitor1*)pCMe, (IEcoAST1BlockTypes*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1BreakStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitBreakStatement((IEcoVisitor1*)pCMe, (IEcoAST1BreakStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1CaseStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitCaseStatement((IEcoVisitor1*)pCMe, (IEcoAST1CaseStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1CastExpression) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitCastExpression((IEcoVisitor1*)pCMe, (IEcoAST1CastExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1CharacterLiteral) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitCharacterLiteral((IEcoVisitor1*)pCMe, (IEcoAST1CharacterLiteral*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1CompoundStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitCompoundStatement((IEcoVisitor1*)pCMe, (IEcoAST1CompoundStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ConditionalExpression) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitConditionalExpression((IEcoVisitor1*)pCMe, (IEcoAST1ConditionalExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ContinueStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitContinueStatement((IEcoVisitor1*)pCMe, (IEcoAST1ContinueStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Declaration) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1Declaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1DefaultStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitDefaultStatement((IEcoVisitor1*)pCMe, (IEcoAST1DefaultStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1DoWhileStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitDoWhileStatement((IEcoVisitor1*)pCMe, (IEcoAST1DoWhileStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1EnumDeclaration) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitEnumDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1EnumDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1EnumType) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitEnumType((IEcoVisitor1*)pCMe, (IEcoAST1EnumType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Expression) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitExpression((IEcoVisitor1*)pCMe, (IEcoAST1Expression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ExpressionableDeclaration) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitExpressionableDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1ExpressionableDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FloatLiteral) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitFloatLiteral((IEcoVisitor1*)pCMe, (IEcoAST1FloatLiteral*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ForStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitForStatement((IEcoVisitor1*)pCMe, (IEcoAST1ForStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FunctionCall) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitFunctionCall((IEcoVisitor1*)pCMe, (IEcoAST1FunctionCall*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FunctionDeclaration) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitFunctionDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1FunctionDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FunctionDefinition) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitFunctionDefinition((IEcoVisitor1*)pCMe, (IEcoAST1FunctionDefinition*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1FunctionType) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitFunctionType((IEcoVisitor1*)pCMe, (IEcoAST1FunctionType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1GlobalScope) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitGlobalScope((IEcoVisitor1*)pCMe, (IEcoAST1GlobalScope*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1GoToStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitGoToStatement((IEcoVisitor1*)pCMe, (IEcoAST1GoToStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1IfStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitIfStatement((IEcoVisitor1*)pCMe, (IEcoAST1IfStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1IntegerLiteral) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitIntegerLiteral((IEcoVisitor1*)pCMe, (IEcoAST1IntegerLiteral*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1LabelStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitLabelStatement((IEcoVisitor1*)pCMe, (IEcoAST1LabelStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Literal) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitLiteral((IEcoVisitor1*)pCMe, (IEcoAST1Literal*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1MemberSelection) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitMemberSelection((IEcoVisitor1*)pCMe, (IEcoAST1MemberSelection*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1NullExpression) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitNullExpression((IEcoVisitor1*)pCMe, (IEcoAST1NullExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1NumberType) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitNumberType((IEcoVisitor1*)pCMe, (IEcoAST1NumberType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1PointerType) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitPointerType((IEcoVisitor1*)pCMe, (IEcoAST1PointerType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1ReturnStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitReturnStatement((IEcoVisitor1*)pCMe, (IEcoAST1ReturnStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Scope) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitScope((IEcoVisitor1*)pCMe, (IEcoAST1Scope*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SingleStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitSingleStatement((IEcoVisitor1*)pCMe, (IEcoAST1SingleStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SizeofExpression) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitSizeofExpression((IEcoVisitor1*)pCMe, (IEcoAST1SizeofExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SizeofType) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitSizeofType((IEcoVisitor1*)pCMe, (IEcoAST1SizeofType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1Statement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitStatement((IEcoVisitor1*)pCMe, (IEcoAST1Statement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1StringLiteral) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitStringLiteral((IEcoVisitor1*)pCMe, (IEcoAST1StringLiteral*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1StructOrUnionDeclaration) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitStructOrUnionDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1StructOrUnionDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1StructOrUnionType) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitStructOrUnionType((IEcoVisitor1*)pCMe, (IEcoAST1StructOrUnionType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SwitchStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitSwitchStatement((IEcoVisitor1*)pCMe, (IEcoAST1SwitchStatement*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1SyntaxObject) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitSyntaxObject((IEcoVisitor1*)pCMe, (IEcoAST1SyntaxObject*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1TranslationUnit) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitTranslationUnit((IEcoVisitor1*)pCMe, (IEcoAST1TranslationUnit*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1TranslationUnitObject) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitTranslationUnitObject((IEcoVisitor1*)pCMe, (IEcoAST1TranslationUnitObject*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1TypedefDeclaration) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitTypedefDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1TypedefDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1TypedefType) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitTypedefType((IEcoVisitor1*)pCMe, (IEcoAST1TypedefType*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1UnaryExpression) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitUnaryExpression((IEcoVisitor1*)pCMe, (IEcoAST1UnaryExpression*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1VariableDeclaration) ) {
            CEcoIDL1JavaVisitor_286DCE90_EmitVariableDeclaration((IEcoVisitor1*)pCMe, (IEcoAST1VariableDeclaration*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1VariableDefinition) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitVariableDefinition((IEcoVisitor1*)pCMe, (IEcoAST1VariableDefinition*)pISyntaxObject);
        } else if ( IsEqualUGUID(pISyntaxObject->pVTbl->get_Id(pISyntaxObject), &IID_IEcoAST1WhileStatement) ) {
            //CEcoIDL1JavaVisitor_286DCE90_EmitWhileStatement((IEcoVisitor1*)pCMe, (IEcoAST1WhileStatement*)pISyntaxObject);
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
static int16_t ECOCALLMETHOD initCEcoIDL1JavaVisitor_286DCE90(/*in*/ CEcoIDL1JavaVisitor_286DCE90Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoFile1* pIFile) {
    CEcoIDL1JavaVisitor_286DCE90* pCMe = (CEcoIDL1JavaVisitor_286DCE90*)me;
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
static int16_t ECOCALLMETHOD createCEcoIDL1JavaVisitor_286DCE90(/* in */ CEcoIDL1JavaVisitor_286DCE90Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoIDL1JavaVisitor_286DCE90(/* in */ CEcoIDL1JavaVisitor_286DCE90Ptr_t pCMe) {
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

/* IEcoIDL1JavaVisitor Virtual Table */
IEcoVisitor1VTbl g_xA6105EF4C95F47F0BA187C6EB7D204D2VTbl_286DCE90 = {
    CEcoIDL1JavaVisitor_286DCE90_QueryInterface,
    CEcoIDL1JavaVisitor_286DCE90_AddRef,
    CEcoIDL1JavaVisitor_286DCE90_Release,
    CEcoIDL1JavaVisitor_286DCE90_Accept
};



/* Object Instance */
CEcoIDL1JavaVisitor_286DCE90 g_xCEcoIDL1JavaVisitor_286DCE90 = {
    &g_xA6105EF4C95F47F0BA187C6EB7D204D2VTbl_286DCE90,
    initCEcoIDL1JavaVisitor_286DCE90,
    createCEcoIDL1JavaVisitor_286DCE90,
    deleteCEcoIDL1JavaVisitor_286DCE90,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_pIStr */
    0, /* m_pIFile */
    0  /* m_Name */
};
