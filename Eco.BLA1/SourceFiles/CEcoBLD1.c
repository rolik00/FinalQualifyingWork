/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLD1_F82A88F6
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBLD1_F82A88F6
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
#include "IEcoFileSystemManagement1.h"
#include "IEcoFileManager1.h"
#include "IEcoFile1.h"
#include "CEcoBLD1.h"
#include "IdEcoFileSystemManagement1.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoLexicalRules1Direct interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBLD1_F82A88F6_QueryInterface(/* in */ IEcoLexicalData1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoLexicalData1) ) {
        *ppv = &pCMe->m_pVTblIData;
        pCMe->m_pVTblIData->AddRef((IEcoLexicalData1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIData;
        pCMe->m_pVTblIData->AddRef((IEcoLexicalData1*)pCMe);
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
 *   AddRef function for the IEcoLexicalRules1Direct interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLD1_F82A88F6_AddRef(/* in */ IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

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
 *   Release function for the IEcoLexicalRules1Direct interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLD1_F82A88F6_Release(/* in */ IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

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

static uint32_t ECOCALLMETHOD CEcoBLD1_F82A88F6_get_Flags(IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_flags;
}

static uint32_t ECOCALLMETHOD CEcoBLD1_F82A88F6_get_InitialState(IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_initialState;
}

static uint32_t ECOCALLMETHOD CEcoBLD1_F82A88F6_get_Version(IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_version;
}

static uint16_t* ECOCALLMETHOD CEcoBLD1_F82A88F6_get_GlobalAlphabetMap(IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_pGlobalAlphabetMap;
}

static uint16_t* ECOCALLMETHOD CEcoBLD1_F82A88F6_get_AlphabetMapByLexerState(IEcoLexicalData1Ptr_t me, char_t* lexerStateName) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_pGlobalAlphabetMap;
}

static uint16_t ECOCALLMETHOD CEcoBLD1_F82A88F6_get_AlphabetClassesCount(IEcoLexicalData1Ptr_t me, char_t* lexerStateName) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_alphabetClassesCount;
}

static uint16_t* ECOCALLMETHOD CEcoBLD1_F82A88F6_get_StateClassMap(IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_pStateClassMap;
}

static uint32_t ECOCALLMETHOD CEcoBLD1_F82A88F6_get_TotalStatesCount(IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_totalStatesCount;
}

static int32_t* ECOCALLMETHOD CEcoBLD1_F82A88F6_get_TransitionMatrix(IEcoLexicalData1Ptr_t me, char_t* lexerStateName) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_pTransitionMatrix;
}

static uint16_t ECOCALLMETHOD CEcoBLD1_F82A88F6_get_StateClassesCount(IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_stateClassesCount;
}

static int16_t ECOCALLMETHOD CEcoBLD1_F82A88F6_get_StateClassInfo(IEcoLexicalData1Ptr_t me, uint16_t stateClassId, EcoLexicalStateClassInfo* pInfo) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 || pInfo == 0 || stateClassId >= pCMe->m_stateClassesCount) {
        return ERR_ECO_POINTER;
    }

    *pInfo = pCMe->m_pStateClassInfoArray[stateClassId];
    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLD1_F82A88F6_Save(IEcoLexicalData1Ptr_t me, char_t* fileName) {
	CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoFileSystemManagement1* pIFSM = 0;
    IEcoFileManager1* pIFMgr = 0;
    IEcoFile1* pIFile = 0;
    int16_t result = 0;
	uint32_t magic, version, flags, initialState;
    uint16_t alphabetClassesCount, stateClassesCount;
    uint32_t totalStatesCount, matrixSize;

    if (!me || !fileName) {
		return ERR_ECO_POINTER;
	}

    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || !pIBus) {
		return result;
	}

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFileSystemManagement1, 0, &IID_IEcoFileSystemManagement1, (void**)&pIFSM);
    pIBus->pVTbl->Release(pIBus);
    if (result != 0 || !pIFSM) {
		return result;
	}

    pIFMgr = pIFSM->pVTbl->get_FileManager(pIFSM);
    pIFile = pIFMgr->pVTbl->Create(pIFMgr, fileName);
    if (!pIFile) {
        pIFSM->pVTbl->Release(pIFSM);
        return -1;
    }

    magic = 0x4C58444C; 
	version = pCMe->m_version;
    flags = pCMe->m_flags;
    initialState = pCMe->m_initialState;
    alphabetClassesCount = pCMe->m_alphabetClassesCount;
    stateClassesCount = pCMe->m_stateClassesCount;
    totalStatesCount = pCMe->m_totalStatesCount;
    matrixSize = totalStatesCount * alphabetClassesCount;

#define WRITE(ptr, size) do { \
    uint32_t w = size; \
    if (pIFile->pVTbl->Write(pIFile, ptr, &w) != 0 || w != size) goto error; \
} while (0)

    WRITE(&magic, sizeof(magic));
    WRITE(&version, sizeof(version));
    WRITE(&flags, sizeof(flags));
    WRITE(&initialState, sizeof(initialState));
    WRITE(&alphabetClassesCount, sizeof(alphabetClassesCount));
    WRITE(pCMe->m_pGlobalAlphabetMap, 256 * sizeof(uint16_t));
    WRITE(&stateClassesCount, sizeof(stateClassesCount));
    WRITE(pCMe->m_pStateClassMap, totalStatesCount * sizeof(uint16_t));
    WRITE(&totalStatesCount, sizeof(totalStatesCount));
    WRITE(pCMe->m_pTransitionMatrix, matrixSize * sizeof(int32_t));
    WRITE(pCMe->m_pStateClassInfoArray, stateClassesCount * sizeof(EcoLexicalStateClassInfo));

#undef WRITE

    pIFile->pVTbl->Close(pIFile);
    pIFSM->pVTbl->Release(pIFSM);
    return ERR_ECO_SUCCESES;

error:
    pIFile->pVTbl->Close(pIFile);
    pIFSM->pVTbl->Release(pIFSM);
    return -1;
}

static uint32_t ECOCALLMETHOD CEcoBLD1_F82A88F6_get_Checksum(IEcoLexicalData1Ptr_t me) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
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
static int16_t ECOCALLMETHOD initCEcoBLD1_F82A88F6(/*in*/ CEcoBLD1_F82A88F6Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBLD1_F82A88F6* pCMe = (CEcoBLD1_F82A88F6*)me;
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
static int16_t ECOCALLMETHOD createCEcoBLD1_F82A88F6(/* in */ CEcoBLD1_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBLD1_F82A88F6(/* in */ CEcoBLD1_F82A88F6Ptr_t pCMe) {
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
		if (pCMe->m_pGlobalAlphabetMap) pIMem->pVTbl->Free(pIMem, pCMe->m_pGlobalAlphabetMap);
        if (pCMe->m_pStateClassMap) pIMem->pVTbl->Free(pIMem, pCMe->m_pStateClassMap);
        if (pCMe->m_pTransitionMatrix) pIMem->pVTbl->Free(pIMem, pCMe->m_pTransitionMatrix);
        if (pCMe->m_pStateClassInfoArray) pIMem->pVTbl->Free(pIMem, pCMe->m_pStateClassInfoArray);
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoLexicalRules1Direct Virtual Table */
IEcoLexicalData1VTbl g_xDB2E163758AA4447A843545A8805D3FEVTbl_F82A88F6 = {
    CEcoBLD1_F82A88F6_QueryInterface,
    CEcoBLD1_F82A88F6_AddRef,
    CEcoBLD1_F82A88F6_Release,
    CEcoBLD1_F82A88F6_get_Flags,
    CEcoBLD1_F82A88F6_get_InitialState,
    CEcoBLD1_F82A88F6_get_Version,
    CEcoBLD1_F82A88F6_get_GlobalAlphabetMap,
    CEcoBLD1_F82A88F6_get_AlphabetMapByLexerState,
    CEcoBLD1_F82A88F6_get_AlphabetClassesCount,
    CEcoBLD1_F82A88F6_get_StateClassMap,
    CEcoBLD1_F82A88F6_get_TotalStatesCount,
    CEcoBLD1_F82A88F6_get_TransitionMatrix,
    CEcoBLD1_F82A88F6_get_StateClassesCount,
    CEcoBLD1_F82A88F6_get_StateClassInfo,
    CEcoBLD1_F82A88F6_Save,
    CEcoBLD1_F82A88F6_get_Checksum
};


/* Object Instance */
CEcoBLD1_F82A88F6 g_xCEcoBLD1_F82A88F6 = {
    &g_xDB2E163758AA4447A843545A8805D3FEVTbl_F82A88F6,
    initCEcoBLD1_F82A88F6,
    createCEcoBLD1_F82A88F6,
    deleteCEcoBLD1_F82A88F6,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0, /* m_Name */
	0, /* m_flags */ 
    0, /* m_initialState */
    0, /* m_version */
    0, /* m_alphabetClassesCount */
    0, /* m_pGlobalAlphabetMap */
    0, /* m_stateClassesCount */
    0, /* m_pStateClassMap */ 
    0, /* m_totalStatesCount */
    0, /* m_pTransitionMatrix */
    0  /* m_pStateClassInfoArray */
};
