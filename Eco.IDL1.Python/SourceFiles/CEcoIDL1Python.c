/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1Python_2C7799FC
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoIDL1Python_2C7799FC
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
#include "CEcoIDL1Python.h"
#include "CEcoIDL1PythonVisitor.h"

extern CEcoIDL1PythonVisitor_2C7799FC g_xCEcoIDL1PythonVisitor_2C7799FC;

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoIDL1Python interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1Python_2C7799FC_QueryInterface(/* in */ IEcoIDL1EmitterPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoIDL1Emitter) ) {
        *ppv = &pCMe->m_pVTblIEmitter;
        pCMe->m_pVTblIEmitter->AddRef((IEcoIDL1Emitter*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEmitter;
        pCMe->m_pVTblIEmitter->AddRef((IEcoIDL1Emitter*)pCMe);
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
 *   AddRef function for the IEcoIDL1Python interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1Python_2C7799FC_AddRef(/* in */ IEcoIDL1EmitterPtr_t me) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return atomicincrement_int32_t(&pCMe->m_cRef);
}

/*
 *
 * <summary>
 *   Release Function
 * </summary>
 *
 * <description>
 *   Release function for the IEcoIDL1Python interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1Python_2C7799FC_Release(/* in */ IEcoIDL1EmitterPtr_t me) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Decrementing the component's reference count */
    atomicdecrement_int32_t(&pCMe->m_cRef);
    /* If the count is zero, free the instance data */
    if ( pCMe->m_cRef == 0 ) {
        pCMe->Delete(pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <summary>
 *   GetLanguageIdentifier Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1Python_2C7799FC_GetIdentifier(/* in */ IEcoIDL1EmitterPtr_t me, /* out */ char_t** langId) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   EmitInterfaces Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1Python_2C7799FC_Emit(/* in */ IEcoIDL1EmitterPtr_t me, /* in */ IEcoAST1Ptr_t pIAST, /* in */ char_t* outputPath) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;
    CEcoIDL1PythonVisitor_2C7799FCPtr_t pCObj = 0;
    IEcoAST1SyntaxObject* pISyntaxObject = 0;
    IEcoVisitor1Element* pIElement = 0;
	IEcoInterfaceBus1* pIBus = 0;
	IEcoString1* pIStr = 0;
	char_t* pszFullPath = 0;
    int16_t result = 0;

    /* Pointer Validation */
    if (me == 0 || pIAST == 0 || outputPath == 0) {
        return ERR_ECO_POINTER;
    }

	result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || pIBus == 0) {
		return result;
	}

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**)&pIStr);
    pIBus->pVTbl->Release(pIBus);
    if (result != 0 || pIStr == 0) {
		goto Release;
	}

	pszFullPath = pIStr->pVTbl->Append(pIStr, pszFullPath, outputPath);
	pszFullPath = pIStr->pVTbl->Append(pIStr, pszFullPath, ".py");

    if (pCMe->m_pIFileManager != 0) {
        pCMe->m_pIFile = pCMe->m_pIFileManager->pVTbl->Create(pCMe->m_pIFileManager, pszFullPath);
    }

    /* Проверка визитора */
    if (pCMe->m_pIVisitor == 0) {
        /* Выделение памяти для данных экземпляра */
        pCObj = (CEcoIDL1PythonVisitor_2C7799FCPtr_t)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoIDL1PythonVisitor_2C7799FC));
        /* Формирование данных экземпляра */
        pCObj = (CEcoIDL1PythonVisitor_2C7799FCPtr_t)pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, pCObj, &g_xCEcoIDL1PythonVisitor_2C7799FC, sizeof(CEcoIDL1PythonVisitor_2C7799FC));
        /* Создание компонента */
        result = pCObj->Create(pCObj, (IEcoUnknown*)pCMe->m_pISys, 0);
        if (result != 0) {
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pCObj);
            goto Release;
        }
        /* Инициализация компонента */
        result = pCObj->Init(pCObj, (IEcoUnknown*)pCMe->m_pISys, pCMe->m_pIFile);
        if (result != 0) {
            pCObj->Delete(pCObj);
            goto Release;
        }
        pCMe->m_pIVisitor = (IEcoVisitor1*)pCObj;
    }

    pISyntaxObject = (IEcoAST1SyntaxObject*)pIAST->pVTbl->get_TranslationUnit(pIAST);
    /* Проверка работы элемента визитора */
    result = pISyntaxObject->pVTbl->QueryInterface(pISyntaxObject, &IID_IEcoVisitor1Element, (void **)&pIElement);
    if (result == 0 && pIElement != 0) {
        /* Посещение визитором объекта (элемента) */
        pIElement->pVTbl->Visit(pIElement, pCMe->m_pIVisitor);
        pIElement->pVTbl->Release(pIElement);
    } else {
        return -1;
    }
    
	result = ERR_ECO_SUCCESES;

Release:
    if (pszFullPath != 0 && pIStr != 0) {
        pIStr->pVTbl->Free(pIStr, pszFullPath);
    }
    if (pIStr) pIStr->pVTbl->Release(pIStr);
    if (pIBus) pIBus->pVTbl->Release(pIBus);

    return result;
}

/*
 *
 * <summary>
 *   EmitIdFile Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1Python_2C7799FC_EmitIdFile(/* in */ IEcoIDL1EmitterPtr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ char_t* outputPath) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   EmitMarshalingCode Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1Python_2C7799FC_EmitMarshalingCode(/* in */ IEcoIDL1EmitterPtr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ char_t* outputPath) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   EmitTemplate Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1Python_2C7799FC_EmitTemplate(/* in */ IEcoIDL1EmitterPtr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ char_t* outputPath) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
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
static int16_t ECOCALLMETHOD initCEcoIDL1Python_2C7799FC(/*in*/ CEcoIDL1Python_2C7799FCPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoIDL1Python_2C7799FC* pCMe = (CEcoIDL1Python_2C7799FC*)me;
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
    /* Получение интерфейса управление файлами */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFileSystemManagement1, 0, &IID_IEcoFileManager1, (void**) &pCMe->m_pIFileManager);

    if (result != 0 || pCMe->m_pIFileManager == 0) {
        /* Освобождение в случае ошибки */
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
static int16_t ECOCALLMETHOD createCEcoIDL1Python_2C7799FC(/* in */ CEcoIDL1Python_2C7799FCPtr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoIDL1Python_2C7799FC(/* in */ CEcoIDL1Python_2C7799FCPtr_t pCMe) {
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

/* IEcoIDL1Python Virtual Table */
IEcoIDL1EmitterVTbl g_x882AD8D1D9A44A00A9C9E144ACFA1E79VTbl_2C7799FC = {
    CEcoIDL1Python_2C7799FC_QueryInterface,
    CEcoIDL1Python_2C7799FC_AddRef,
    CEcoIDL1Python_2C7799FC_Release,
    CEcoIDL1Python_2C7799FC_GetIdentifier,
    CEcoIDL1Python_2C7799FC_Emit
};

/* IEcoIDL1LangEmitter Virtual Table */
//IEcoIDL1LangEmitterVTbl g_x16F3F96482B4491A92D417FDC783D977VTbl_2C7799FC = {
//    CEcoIDL1Python_2C7799FC_QueryInterface,
//    CEcoIDL1Python_2C7799FC_AddRef,
//    CEcoIDL1Python_2C7799FC_Release,
//    CEcoIDL1Python_2C7799FC_GetIdentifier,
//    CEcoIDL1Python_2C7799FC_Emit,
//    CEcoIDL1Python_2C7799FC_EmitIdFile,
//    CEcoIDL1Python_2C7799FC_EmitMarshalingCode,
//    CEcoIDL1Python_2C7799FC_EmitTemplate
//};

/* Object Instance */
CEcoIDL1Python_2C7799FC g_xCEcoIDL1Python_2C7799FC = {
    &g_x882AD8D1D9A44A00A9C9E144ACFA1E79VTbl_2C7799FC,
    //&g_x16F3F96482B4491A92D417FDC783D977VTbl_2C7799FC,
    initCEcoIDL1Python_2C7799FC,
    createCEcoIDL1Python_2C7799FC,
    deleteCEcoIDL1Python_2C7799FC,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_pIVisitor */
    0, /* m_pIFileManager */
    0, /* m_pIFile */
    0  /* m_Name */
};
