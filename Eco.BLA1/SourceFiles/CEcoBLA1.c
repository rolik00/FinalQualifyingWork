/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLA1_F82A88F6
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBLA1_F82A88F6
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
#include "IEcoFileSystemManagement1.h"
#include "IEcoFileManager1.h"
#include "IEcoFile1.h"
#include "CEcoBLA1.h"
#include "CEcoBLR1RE.h" 
#include "CEcoBLA1Scanner.h"
#include "IdEcoFileSystemManagement1.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoBLA1 interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_QueryInterface(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoLexicalAnalyzer1) ) {
        *ppv = &pCMe->m_pVTblILA;
        pCMe->m_pVTblILA->AddRef((IEcoLexicalAnalyzer1Ptr_t)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblILA;
        pCMe->m_pVTblILA->AddRef((IEcoLexicalAnalyzer1Ptr_t)pCMe);
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
 *   AddRef function for the IEcoLexicalAnalyzer1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLA1_F82A88F6_AddRef(/* in */ IEcoLexicalAnalyzer1Ptr_t me) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

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
 *   Release function for the IEcoLexicalAnalyzer1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLA1_F82A88F6_Release(/* in */ IEcoLexicalAnalyzer1Ptr_t me) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

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

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_new_FileScanner(/* in */  IEcoLexicalAnalyzer1Ptr_t me, /* in */  IEcoUnknownPtr_t pIRules, /* in */  char_t* fileName, /* out */ IEcoLexicalAnalyzer1ScannerPtr_t* ppIScanner) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoLexicalData1* pIData = (IEcoLexicalData1*)pIRules;
    IEcoFileSystemManagement1* pIFSM = 0;
    IEcoFileManager1* pIFMgr = 0;
    IEcoFile1* pIFile = 0;
    CEcoBLA1Scanner_F82A88F6* pScanner = 0;
    char *tempBuffer = 0, *newBuf = 0;
    int16_t result = 0;
    uint32_t toRead = 0, bytesRead = 0, chunkSize = 4096U;

    if (me == 0 || pIRules == 0 || fileName == 0 || ppIScanner == 0) {
        return ERR_ECO_POINTER;
    }

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || pIBus == 0) {
		return result;
	}

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFileSystemManagement1, 0, &IID_IEcoFileSystemManagement1, (void**)&pIFSM);
    pIBus->pVTbl->Release(pIBus);
    if (result != 0 || pIFSM == 0) {
		return result;
	}

    pIFMgr = pIFSM->pVTbl->get_FileManager(pIFSM);
    pIFile = pIFMgr->pVTbl->Open(pIFMgr, fileName);
    if (pIFile == 0) {
        pIFSM->pVTbl->Release(pIFSM);
        return -1;
    }

    pScanner = (CEcoBLA1Scanner_F82A88F6*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBLA1Scanner_F82A88F6));
    if (pScanner == 0) {
		goto cleanup_error;
	}

    memcpy(pScanner, &g_xCEcoBLA1Scanner_F82A88F6, sizeof(CEcoBLA1Scanner_F82A88F6));

    pScanner->m_pIMem = pCMe->m_pIMem;
    pScanner->m_pIMem->pVTbl->AddRef(pScanner->m_pIMem);
    pScanner->m_pISys = pCMe->m_pISys;
    if (pScanner->m_pISys) pScanner->m_pISys->pVTbl->AddRef(pScanner->m_pISys);
    pScanner->m_Name = 0;

    result = pScanner->Init((CEcoBLA1Scanner_F82A88F6Ptr_t)pScanner, (IEcoUnknown*)pScanner->m_pISys);
    if (result != 0) {
		goto cleanup_error;
	}

    pScanner->m_pIData = pIData;
    pScanner->m_pIData->pVTbl->AddRef(pScanner->m_pIData);
    pScanner->m_pIFile = 0;
    pScanner->m_filePos = 0;
    pScanner->m_line = 1;
    pScanner->m_column = 1;
    pScanner->m_currentState = pIData->pVTbl->get_InitialState(pIData);
    pScanner->m_channelMask = 0xFFFFFFFFU;
    pScanner->m_stateStack = 0;
    pScanner->m_stateStackSize = 0;
    pScanner->m_stateStackTop = -1;
    pScanner->m_buffer = 0;
    pScanner->m_bufferSize = 0;
    pScanner->m_bufferPos = 0;
    pScanner->m_bufferEnd = 0;

    tempBuffer = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, chunkSize);
    if (tempBuffer == 0) {
        result = ERR_ECO_OUTOFMEMORY;
        goto cleanup_error;
    }

    while (1) {
        toRead = chunkSize;
        result = pIFile->pVTbl->Read(pIFile, tempBuffer, &toRead);
        bytesRead = toRead;

        if (bytesRead == 0) {
            result = 0;
            break;
        }
        if (result != 0) {
            break;
        }

        newBuf = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, pScanner->m_bufferSize + bytesRead);
        if (newBuf == 0) {
            result = ERR_ECO_OUTOFMEMORY;
            break;
        }

        if (pScanner->m_buffer != 0) {
            memcpy(newBuf, pScanner->m_buffer, pScanner->m_bufferSize);
            pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pScanner->m_buffer);
        }
        memcpy(newBuf + pScanner->m_bufferSize, tempBuffer, bytesRead);

        pScanner->m_buffer = newBuf;
        pScanner->m_bufferSize += bytesRead;
        pScanner->m_bufferEnd = pScanner->m_bufferSize;
        newBuf = 0;
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, tempBuffer);
    tempBuffer = 0;

    if (result != 0) goto cleanup_error;

    pIFile->pVTbl->Close(pIFile);
    pIFile = 0;
    pIFSM->pVTbl->Release(pIFSM);
    pIFSM = 0;

    *ppIScanner = (IEcoLexicalAnalyzer1ScannerPtr_t)pScanner;
    return ERR_ECO_SUCCESES;

cleanup_error:
    if (tempBuffer) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, tempBuffer);
    if (newBuf) pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, newBuf);
    if (pScanner) pScanner->Delete((CEcoBLA1Scanner_F82A88F6Ptr_t)pScanner);
    if (pIFile) pIFile->pVTbl->Close(pIFile);
    if (pIFSM) pIFSM->pVTbl->Release(pIFSM);
    return (result != 0) ? result : ERR_ECO_OUTOFMEMORY;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_LoadRulesFromFile(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ char_t* fileName, /* out */ IEcoLexicalData1Ptr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_SaveRulesToFile(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ char_t* fileName) {
    IEcoLexicalData1* pIData;
	
	if (!me || !pIRules || !fileName) {
		return ERR_ECO_POINTER;
	}

    pIData = (IEcoLexicalData1*)pIRules;
    return pIData->pVTbl->Save(pIData, fileName);
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_new_MemoryScanner(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ voidptr_t buffer, /* in */ uint32_t size, /* out */ IEcoLexicalAnalyzer1ScannerPtr_t* ppIScanner) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;
    CEcoBLA1Scanner_F82A88F6* pScanner = 0;
    int16_t result;

    if (!me || !pIRules || !buffer || !ppIScanner) {
        return ERR_ECO_POINTER;
	}

    pScanner = (CEcoBLA1Scanner_F82A88F6*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBLA1Scanner_F82A88F6));
    if (!pScanner) {
		return ERR_ECO_OUTOFMEMORY;
	}

    memcpy(pScanner, &g_xCEcoBLA1Scanner_F82A88F6, sizeof(CEcoBLA1Scanner_F82A88F6));
    pScanner->m_pIMem = pCMe->m_pIMem;
    pScanner->m_pIMem->pVTbl->AddRef(pScanner->m_pIMem);
    pScanner->m_pISys = pCMe->m_pISys;
    if (pScanner->m_pISys) pScanner->m_pISys->pVTbl->AddRef(pScanner->m_pISys);

    result = pScanner->Init((CEcoBLA1Scanner_F82A88F6Ptr_t)pScanner, (IEcoUnknown*)pScanner->m_pISys);
    if (result != 0) {
        pScanner->Delete((CEcoBLA1Scanner_F82A88F6Ptr_t)pScanner);
        return result;
    }

    pScanner->m_pIData = (IEcoLexicalData1*)pIRules;
    pScanner->m_pIData->pVTbl->AddRef(pScanner->m_pIData);
    pScanner->m_bufferSize = size;
    pScanner->m_buffer = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, size);
    if (!pScanner->m_buffer) {
        pScanner->Delete((CEcoBLA1Scanner_F82A88F6Ptr_t)pScanner);
        return ERR_ECO_OUTOFMEMORY;
    }
    memcpy(pScanner->m_buffer, buffer, size);
    pScanner->m_bufferPos = 0;
    pScanner->m_bufferEnd = size;
    pScanner->m_filePos = 0;
    pScanner->m_line = 1;
    pScanner->m_column = 1;
    pScanner->m_currentState = pScanner->m_pIData->pVTbl->get_InitialState(pScanner->m_pIData);
    pScanner->m_channelMask = 0xFFFFFFFF;
    pScanner->m_pIFile = 0;

    *ppIScanner = (IEcoLexicalAnalyzer1ScannerPtr_t)pScanner;
    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_LoadRulesFromMemory(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ voidptr_t pBuffer, /* in */ uint32_t size, /* out */ IEcoLexicalData1Ptr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_SaveRulesToMemory(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* in */ IEcoUnknownPtr_t pIRules, /* in */ voidptr_t* ppBuffer, /* in */ uint32_t* pSize) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_CreateRulesRE(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1REPtr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;
    CEcoBLR1RE_F82A88F6* pRules = 0;
    int16_t result = ERR_ECO_SUCCESES;

    if (me == 0 || ppIRules == 0) {
        return ERR_ECO_POINTER;
    }

    *ppIRules = 0;

    if (pCMe->m_pIMem == 0) {
        return -1;
    }

    pRules = (CEcoBLR1RE_F82A88F6*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBLR1RE_F82A88F6));
    if (pRules == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    memcpy(pRules, &g_xCEcoBLR1RE_F82A88F6, sizeof(CEcoBLR1RE_F82A88F6));

    pRules->m_pIMem = pCMe->m_pIMem;
    pRules->m_pIMem->pVTbl->AddRef(pRules->m_pIMem);

    pRules->m_pISys = pCMe->m_pISys;
    if (pRules->m_pISys) {
        pRules->m_pISys->pVTbl->AddRef(pRules->m_pISys);
    }
	pRules->m_pBRE = 0;
    pRules->m_pRulesList = 0;
    pRules->m_pSuperNFA = 0;
    pRules->m_pFinalStateAttrs = 0;
    pRules->m_Name = 0;

    result = pRules->Init((CEcoBLR1RE_F82A88F6Ptr_t)pRules, (IEcoUnknown*)pRules->m_pISys);
    if (result != 0) {
        pRules->Delete((CEcoBLR1RE_F82A88F6Ptr_t)pRules);
        return result;
    }

    *ppIRules = (IEcoLexicalRules1REPtr_t)pRules;

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_CreateRulesBNF(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1BNFPtr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_CreateRulesFSM(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1FSMPtr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1_F82A88F6_CreateRulesDirect(/* in */ IEcoLexicalAnalyzer1Ptr_t me, /* out */ IEcoLexicalRules1DirectPtr_t* ppIRules) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;

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
static int16_t ECOCALLMETHOD initCEcoBLA1_F82A88F6(/*in*/ CEcoBLA1_F82A88F6Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBLA1_F82A88F6* pCMe = (CEcoBLA1_F82A88F6*)me;
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
static int16_t ECOCALLMETHOD createCEcoBLA1_F82A88F6(/* in */ CEcoBLA1_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBLA1_F82A88F6(/* in */ CEcoBLA1_F82A88F6Ptr_t pCMe) {
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

/* IEcoBLA1 Virtual Table */
IEcoLexicalAnalyzer1VTbl g_x78E16240C3354A458D40D896B3F9D73BVTbl_F82A88F6 = {
    CEcoBLA1_F82A88F6_QueryInterface,
    CEcoBLA1_F82A88F6_AddRef,
    CEcoBLA1_F82A88F6_Release,
    CEcoBLA1_F82A88F6_new_FileScanner,
    CEcoBLA1_F82A88F6_LoadRulesFromFile,
    CEcoBLA1_F82A88F6_SaveRulesToFile,
    CEcoBLA1_F82A88F6_new_MemoryScanner,
    CEcoBLA1_F82A88F6_LoadRulesFromMemory,
    CEcoBLA1_F82A88F6_SaveRulesToMemory,
    CEcoBLA1_F82A88F6_CreateRulesRE,
    CEcoBLA1_F82A88F6_CreateRulesBNF,
    CEcoBLA1_F82A88F6_CreateRulesFSM,
    CEcoBLA1_F82A88F6_CreateRulesDirect
};

/* Object Instance */
CEcoBLA1_F82A88F6 g_xCEcoBLA1_F82A88F6 = {
    &g_x78E16240C3354A458D40D896B3F9D73BVTbl_F82A88F6,
   
    initCEcoBLA1_F82A88F6,
    createCEcoBLA1_F82A88F6,
    deleteCEcoBLA1_F82A88F6,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0  /* m_Name */
};