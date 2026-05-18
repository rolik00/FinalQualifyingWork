/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoTreePrintVisitor
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoTreePrintVisitor
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoTreePrintVisitor.h"
#include "IEcoTree1.h"
#include "IEcoAST1GlobalScope.h"
#include "IEcoAST1FunctionDefinition.h"

 /*
  *
  * <сводка>
  *   Функция QueryInterface
  * </сводка>
  *
  * <описание>
  *   Функция Add_AdditionalInfoForScopes 
  * </описание>
  *
  */
int16_t CEcoTreePrintVisitor_Add_AdditionalInfoForScopes(/* in */ struct CEcoTreePrintVisitor* pCMe, IEcoTree1Node* pINode, char_t* offset) {
	IEcoAST1Scope* pIScope = 0;
    IEcoAST1GlobalScope* pIGlobalScope = 0;
	IEcoAST1Declaration* pIDeclaration = 0;
	IEcoAST1StructOrUnionDeclaration* pIStructDeclaration = 0;
    IEcoAST1EnumDeclaration* pIEnumDeclaration = 0;
	IEcoAST1StructOrUnionType* pIUndeclaredType = 0;
    IEcoAST1EnumType* pIUndeclaredEnumType = 0;
    IEcoAST1FunctionDefinition* pIDefinition = 0;
	IEcoList1* pIDeclarations = 0;
	char_t* description = 0;
	uint32_t i = 0;
	int32_t result = 0;

	/* Try to get scope */
	result = pINode->pVTbl->QueryInterface(pINode, &IID_IEcoAST1Scope, (void**)&pIScope);
	if (result == 0 && pIScope != 0) {
		/* Add declarations */
		pIDeclarations = pIScope->pVTbl->get_Declarations(pIScope);
		for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
			pIDeclaration = (IEcoAST1Declaration*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
			description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, pIDeclaration->pVTbl->get_IdentifierName(pIDeclaration));
			description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, " ");
		}
		pCMe->m_pILog->pVTbl->InfoFormat(pCMe->m_pILog, "%s|     Declarations: %s", offset, description);
		pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, description);
		description = 0;
		pIDeclarations->pVTbl->Clear(pIDeclarations);
		pIDeclarations->pVTbl->Release(pIDeclarations);

		/* Add struct or union declarations */
		pIDeclarations = pIScope->pVTbl->get_StructOrUnionDeclarations(pIScope);
		for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
			pIStructDeclaration = (IEcoAST1StructOrUnionDeclaration*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
			description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, pIStructDeclaration->pVTbl->get_IdentifierName(pIStructDeclaration));
			description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, " ");
		}
		pCMe->m_pILog->pVTbl->InfoFormat(pCMe->m_pILog, "%s|     Struct or union declarations: %s", offset, description);
		pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, description);
		description = 0;
		pIDeclarations->pVTbl->Clear(pIDeclarations);
		pIDeclarations->pVTbl->Release(pIDeclarations);

        /* Add enum declarations */
        pIDeclarations = pIScope->pVTbl->get_EnumDeclarations(pIScope);
        for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
            pIEnumDeclaration = (IEcoAST1EnumDeclaration*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
            description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, pIEnumDeclaration->pVTbl->get_IdentifierName(pIEnumDeclaration));
            description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, " ");
        }
        pCMe->m_pILog->pVTbl->InfoFormat(pCMe->m_pILog, "%s|     Enum declarations: %s", offset, description);
        pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, description);
        description = 0;
        pIDeclarations->pVTbl->Clear(pIDeclarations);
        pIDeclarations->pVTbl->Release(pIDeclarations);

		/* Add undeclared types */
		pIDeclarations = pIScope->pVTbl->get_UndeclaredEnumTypes(pIScope);
		for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
			pIUndeclaredType = (IEcoAST1StructOrUnionType*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
			description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, pIUndeclaredType->pVTbl->get_TypeName(pIUndeclaredType));
			description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, " ");
		}
		pCMe->m_pILog->pVTbl->InfoFormat(pCMe->m_pILog, "%s|     Undeclared types: %s", offset, description);
		pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, description);
		description = 0;
		pIDeclarations->pVTbl->Clear(pIDeclarations);
		pIDeclarations->pVTbl->Release(pIDeclarations);

        /* Add undeclared enum types */
        pIDeclarations = pIScope->pVTbl->get_UndeclaredTypes(pIScope);
        for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
            pIUndeclaredEnumType = (IEcoAST1EnumType*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
            description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, pIUndeclaredEnumType->pVTbl->get_TypeName(pIUndeclaredEnumType));
            description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, " ");
        }
        pCMe->m_pILog->pVTbl->InfoFormat(pCMe->m_pILog, "%s|     Undeclared enum types: %s", offset, description);
        pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, description);
        description = 0;
        pIDeclarations->pVTbl->Clear(pIDeclarations);
        pIDeclarations->pVTbl->Release(pIDeclarations);
        /* Free */
        pIScope->pVTbl->Release(pIScope);
	}

    /* Try to get Global scope */
    result = pINode->pVTbl->QueryInterface(pINode, &IID_IEcoAST1GlobalScope, (void**)&pIGlobalScope);
    if (result == 0 && pIGlobalScope != 0) {
        /* Add function defenitions */
        pIDeclarations = pIGlobalScope->pVTbl->get_FunctionDefinitions(pIGlobalScope);
        for (i = 0; i < pIDeclarations->pVTbl->Count(pIDeclarations); ++i) {
            pIDefinition = (IEcoAST1FunctionDefinition*)pIDeclarations->pVTbl->Item(pIDeclarations, i);
            pIDeclaration = (IEcoAST1Declaration*)pIDefinition->pVTbl->get_Declaration(pIDefinition);
            description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, pIDeclaration->pVTbl->get_IdentifierName(pIDeclaration));
            description = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, description, " ");
        }
        pCMe->m_pILog->pVTbl->InfoFormat(pCMe->m_pILog, "%s|     Definitions: %s", offset, description);
        pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, description);
        description = 0;
        pIDeclarations->pVTbl->Clear(pIDeclarations);
        pIDeclarations->pVTbl->Release(pIDeclarations);

        /* Free */
        pIGlobalScope->pVTbl->Release(pIGlobalScope);
    }

	return 0;
}



/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoTreePrintVisitor
 * </описание>
 *
 */
int16_t CEcoTreePrintVisitor_QueryInterface(/* in */ struct IEcoTreePrintVisitor* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoTreePrintVisitor) ) {
        *ppv = &pCMe->m_pVTblIPrint;
        pCMe->m_pVTblIPrint->AddRef((IEcoTreePrintVisitor*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIPrint;
        pCMe->m_pVTblIPrint->AddRef((IEcoTreePrintVisitor*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoVisitor1) ) {
        *ppv = &pCMe->m_pVTblIVisitor;
        pCMe->m_pVTblIPrint->AddRef((IEcoTreePrintVisitor*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoTreePrintVisitor
 * </описание>
 *
 */
uint32_t CEcoTreePrintVisitor_AddRef(/* in */ struct IEcoTreePrintVisitor* me) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoTreePrintVisitor
 * </описание>
 *
 */
uint32_t CEcoTreePrintVisitor_Release(/* in */ struct IEcoTreePrintVisitor* me) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoTreePrintVisitor((IEcoTreePrintVisitor*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoVisitor1
 * </описание>
 *
 */
int16_t CEcoTreePrintVisitor_IEcoVisitor1_QueryInterface(/* in */ struct IEcoVisitor1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)((uint64_t)me - sizeof(struct IEcoTreePrintVisitor*));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoVisitor1) ) {
        *ppv = &pCMe->m_pVTblIVisitor;
        pCMe->m_pVTblIPrint->AddRef((IEcoTreePrintVisitor*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIPrint;
        pCMe->m_pVTblIPrint->AddRef((IEcoTreePrintVisitor*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoTreePrintVisitor) ) {
        *ppv = &pCMe->m_pVTblIPrint;
        pCMe->m_pVTblIPrint->AddRef((IEcoTreePrintVisitor*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoVisitor1
 * </описание>
 *
 */
uint32_t CEcoTreePrintVisitor_IEcoVisitor1_AddRef(/* in */ struct IEcoVisitor1* me) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)((uint64_t)me - sizeof(struct IEcoTreePrintVisitor*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoVisitor1
 * </описание>
 *
 */
uint32_t CEcoTreePrintVisitor_IEcoVisitor1_Release(/* in */ struct IEcoVisitor1* me) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)((uint64_t)me - sizeof(struct IEcoTreePrintVisitor*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoTreePrintVisitor((IEcoTreePrintVisitor*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция set_Logger
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoTreePrintVisitor_set_Logger(/* in */ struct IEcoTreePrintVisitor* me, /* in */ IEcoLog1* pILog) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    /* Присвоение */
    pCMe->m_pILog = pILog;

    return;
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
int16_t CEcoTreePrintVisitor_IEcoVisitor1_Accept(/* in */ struct IEcoVisitor1* me, /* in */ IEcoUnknown* pIUnk) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)((uint64_t)me - sizeof(struct IEcoTreePrintVisitor*));
    IEcoTree1Node* pIRootNode = 0;
    IEcoTree1Node* pINode = 0;
    IEcoTree1Node* pIChild = 0;
    IEcoTree1Node* pIParent = 0;
    IEcoStack1* pIStack = 0;
    IEcoList1* pIChildren = 0;
    int32_t result = 0;
    char_t* offset = 0;
	char_t* new_offset = 0;
	uint32_t i = 0;
	uint32_t depth = 0;

    /* Проверка указателей */
    if (me == 0 || pIUnk == 0) {
        return -1;
    }

    result = pIUnk->pVTbl->QueryInterface(pIUnk, &IID_IEcoTree1Node, (void**)&pIRootNode);
    if (result == 0 && pIRootNode != 0) {
        pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoStack1, 0, &IID_IEcoStack1, (void**)&pIStack);
        pIStack->pVTbl->Push(pIStack, pIRootNode);
        offset = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, offset, "");
        while (pIStack->pVTbl->Count(pIStack) != 0) {
            pINode = (IEcoTree1Node*)pIStack->pVTbl->Pop(pIStack);
            pCMe->m_pILog->pVTbl->InfoFormat(pCMe->m_pILog, "%s|_ %s", offset, pINode->pVTbl->get_Name(pINode));
            pIChildren = pINode->pVTbl->get_Childrens(pINode);
            for (i = pIChildren->pVTbl->Count(pIChildren) - 1; i < pIChildren->pVTbl->Count(pIChildren); --i) {
                pIChild = (IEcoTree1Node*)pIChildren->pVTbl->Item(pIChildren, i);
                pIStack->pVTbl->Push(pIStack, pIChild);
            }
            if (pINode->pVTbl->get_NextSibling(pINode) != 0 && pIChildren->pVTbl->Count(pIChildren) != 0)
                offset = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, offset, "|  ");
            else if (pINode->pVTbl->get_NextSibling(pINode) == 0 && pIChildren->pVTbl->Count(pIChildren) != 0) 
                offset = pCMe->m_pIString->pVTbl->Append(pCMe->m_pIString, offset, "   ");
            else if (pINode->pVTbl->get_NextSibling(pINode) == 0) {
                pIParent = pINode;
                while (pIParent != 0 && pIParent->pVTbl->get_NextSibling(pIParent) == 0)
                    pIParent = pIParent->pVTbl->get_Parent(pIParent);
                if (pIParent != 0) {
                    depth = pIParent->pVTbl->get_Depth(pIParent);
                    new_offset = pCMe->m_pIString->pVTbl->Substring(pCMe->m_pIString, offset, 0, 3 * depth);
                    pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, offset);
                    offset = new_offset;
                }
            }
			pCMe->Add_AdditionalInfoForScopes(pCMe, pINode, offset);
        }
        pIStack->pVTbl->Release(pIStack);
        pIRootNode->pVTbl->Release(pIRootNode);
        pCMe->m_pIString->pVTbl->Free(pCMe->m_pIString, offset);
    } else
        pCMe->m_pILog->pVTbl->InfoFormat(pCMe->m_pILog, "Can't get root node\r\n");

    return result;
}

/* Create Virtual Table */
IEcoTreePrintVisitorVTbl g_x9C23CF5D08D249AA9680D48FCE750562VTbl = {
    CEcoTreePrintVisitor_QueryInterface,
    CEcoTreePrintVisitor_AddRef,
    CEcoTreePrintVisitor_Release,
    CEcoTreePrintVisitor_set_Logger
};

IEcoVisitor1VTbl g_x9C23CF5D08D249AA9680D48FCE750562VTblVisitor = {
    CEcoTreePrintVisitor_IEcoVisitor1_QueryInterface,
    CEcoTreePrintVisitor_IEcoVisitor1_AddRef,
    CEcoTreePrintVisitor_IEcoVisitor1_Release,
    CEcoTreePrintVisitor_IEcoVisitor1_Accept
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t createCEcoTreePrintVisitor(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoTreePrintVisitor** ppIVisitor) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoTreePrintVisitor* pCMe = 0;

    /* Проверка указателей */
    if (ppIVisitor == 0 || pIUnkSystem == 0) {
        return result;
    }

   /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение интерфейса распределителя памяти */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoTreePrintVisitor*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoTreePrintVisitor));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;
    pCMe->m_pIBus = pIBus;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoTreePrintVisitor1 */
    pCMe->m_pVTblIPrint = &g_x9C23CF5D08D249AA9680D48FCE750562VTbl;

    /* Создание таблицы функций интерфейса IEcoVisitor1 */
    pCMe->m_pVTblIVisitor = &g_x9C23CF5D08D249AA9680D48FCE750562VTblVisitor;

    /* Получение интерфейса для работы со строкой */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**) &pCMe->m_pIString);
    if (result != 0 || pCMe->m_pIString == 0) {
        /* Освобождение в случае ошибки */
        deleteCEcoTreePrintVisitor((IEcoTreePrintVisitor*)pCMe);
    }

    /* Инициализация данных */
    pCMe->m_pILog = 0;
    pCMe->m_pIBus = pIBus;

	pCMe->Add_AdditionalInfoForScopes = CEcoTreePrintVisitor_Add_AdditionalInfoForScopes;

    /* Возврат указателя на интерфейс */
    *ppIVisitor = (IEcoTreePrintVisitor*)pCMe;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void deleteCEcoTreePrintVisitor(/* in */ IEcoTreePrintVisitor* pIVisitor) {
    CEcoTreePrintVisitor* pCMe = (CEcoTreePrintVisitor*)pIVisitor;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIVisitor != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_pIString != 0 ) {
            pCMe->m_pIString->pVTbl->Release(pCMe->m_pIString);
        }
		if (pCMe->m_pISys != 0) {
			pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
		}
        if (pCMe->m_pIBus != 0) {
            pCMe->m_pIBus->pVTbl->Release(pCMe->m_pIBus);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
