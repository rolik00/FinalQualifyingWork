/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLA1Scanner_F82A88F6
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBLA1Scanner_F82A88F6
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
#include "IEcoLexicalData1.h"
#include "CEcoBLA1Scanner.h"
#include "CEcoBLA1Token.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoLexicalAnalyzer1Scanner interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_QueryInterface(/* in */ IEcoLexicalAnalyzer1ScannerPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoLexicalAnalyzer1Scanner) ) {
        *ppv = &pCMe->m_pVTblIScanner;
        pCMe->m_pVTblIScanner->AddRef((IEcoLexicalAnalyzer1Scanner*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIScanner;
        pCMe->m_pVTblIScanner->AddRef((IEcoLexicalAnalyzer1Scanner*)pCMe);
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
 *   AddRef function for the IEcoLexicalAnalyzer1Scanner interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_AddRef(/* in */ IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

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
 *   Release function for the IEcoLexicalAnalyzer1Scanner interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_Release(/* in */ IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

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

static IEcoLexicalAnalyzer1TokenPtr_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_Scan(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;
    CEcoBLA1Token_F82A88F6* pToken = 0;
    IEcoLexicalData1* pIData = pCMe->m_pIData;

    uint16_t *globalMap = 0, *stateMap = 0;
    uint16_t classCount = 0;
    uint32_t totalStates = 0;
    int32_t* transMatrix = 0;

    uint32_t currentState = 0, startPos = 0, startLine = 0, startCol = 0;
    uint32_t bestAcceptPos = 0;
    uint32_t bestTokenId = 0, bestChannel = 0;
    uint32_t bestPriority = 0xFFFFFFFFU;
    bool_t accepted = 0;

    if (!pIData || pCMe->m_bufferPos >= pCMe->m_bufferEnd) {
        goto return_eof;
    }

    globalMap = pIData->pVTbl->get_GlobalAlphabetMap(pIData);
    classCount = pIData->pVTbl->get_AlphabetClassesCount(pIData, 0);
    stateMap = pIData->pVTbl->get_StateClassMap(pIData);
    totalStates = pIData->pVTbl->get_TotalStatesCount(pIData);
    transMatrix = pIData->pVTbl->get_TransitionMatrix(pIData, 0);

    currentState = pCMe->m_currentState;
    startPos = pCMe->m_bufferPos;
    startLine = pCMe->m_line;
    startCol = pCMe->m_column;
    bestAcceptPos = startPos;

    while (pCMe->m_bufferPos < pCMe->m_bufferEnd) {
        unsigned char ch = (unsigned char)pCMe->m_buffer[pCMe->m_bufferPos];
        uint16_t cls = 0, stateClass = 0;
        int32_t nextState = 0;

        if (ch == '\n') {
            pCMe->m_line++;
            pCMe->m_column = 1;
        } else {
            pCMe->m_column++;
        }

        cls = globalMap[ch];
        stateClass = stateMap[currentState];
        nextState = transMatrix[stateClass * classCount + cls];

        if (nextState >= 0 && (uint32_t)nextState < totalStates) {
            EcoLexicalStateClassInfo info = {0};

            currentState = (uint32_t)nextState;
            pCMe->m_bufferPos++;

            if (pIData->pVTbl->get_StateClassInfo(pIData, stateMap[currentState], &info) == 0 && info.isFinal) {
                if (info.priority < bestPriority ||
                    (info.priority == bestPriority && pCMe->m_bufferPos > bestAcceptPos)) {
                    bestPriority = info.priority;
                    bestTokenId = info.tokenId;
                    bestChannel = info.channelId;
                    bestAcceptPos = pCMe->m_bufferPos;
                    accepted = 1;
                }
            }
        } else {
            break;
        }
	}

    if (accepted && bestAcceptPos > startPos) {
        pToken = (CEcoBLA1Token_F82A88F6*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBLA1Token_F82A88F6));
        if (!pToken) goto return_eof;

        memcpy(pToken, &g_xCEcoBLA1Token_F82A88F6, sizeof(CEcoBLA1Token_F82A88F6));
        pToken->m_pIMem = pCMe->m_pIMem;
        pToken->m_pIMem->pVTbl->AddRef(pToken->m_pIMem);
        pToken->m_pISys = pCMe->m_pISys;
        if (pToken->m_pISys) pToken->m_pISys->pVTbl->AddRef(pToken->m_pISys);

        pToken->m_type = bestTokenId;
        pToken->m_channel = bestChannel;
        pToken->m_line = startLine;
        pToken->m_column = startCol;
        pToken->m_length = bestAcceptPos - startPos;

        pToken->m_lexeme = (char_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, pToken->m_length + 1);
        if (pToken->m_lexeme) {
            memcpy(pToken->m_lexeme, pCMe->m_buffer + startPos, pToken->m_length);
            pToken->m_lexeme[pToken->m_length] = '\0';
        }

        pToken->m_isEOF = 0;
        pToken->m_isError = 0;

        pCMe->m_bufferPos = bestAcceptPos;
        pCMe->m_currentState = pIData->pVTbl->get_InitialState(pIData);

        return (IEcoLexicalAnalyzer1TokenPtr_t)pToken;
    }

return_eof:
    pToken = (CEcoBLA1Token_F82A88F6*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(CEcoBLA1Token_F82A88F6));
    if (pToken) {
        memcpy(pToken, &g_xCEcoBLA1Token_F82A88F6, sizeof(CEcoBLA1Token_F82A88F6));
        pToken->m_pIMem = pCMe->m_pIMem;
        pToken->m_pIMem->pVTbl->AddRef(pToken->m_pIMem);
        if (pCMe->m_pISys) {
            pToken->m_pISys = pCMe->m_pISys;
            pToken->m_pISys->pVTbl->AddRef(pToken->m_pISys);
        }
        pToken->m_type = 0xFFFFFFFE;
        pToken->m_isEOF = 1;
        pToken->m_isError = 0;
        pToken->m_lexeme = 0;
        pToken->m_length = 0;
        pToken->m_line = pCMe->m_line;
        pToken->m_column = pCMe->m_column;
    }
    return (IEcoLexicalAnalyzer1TokenPtr_t)pToken;
}

static int16_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_Recover(IEcoLexicalAnalyzer1ScannerPtr_t me, IEcoLexicalAnalyzer1TokenPtr_t pIToken) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static IEcoLexicalAnalyzer1TokenPtr_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_Peek(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}

static IEcoLexicalAnalyzer1TokenPtr_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_LookAhead(IEcoLexicalAnalyzer1ScannerPtr_t me, uint32_t n) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}

static uint64_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_get_Position(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_set_Position(IEcoLexicalAnalyzer1ScannerPtr_t me, uint64_t position) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_PushState(IEcoLexicalAnalyzer1ScannerPtr_t me, char_t* stateName) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_PopState(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static char_t* ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_get_CurrentState(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_SetChannelMask(IEcoLexicalAnalyzer1ScannerPtr_t me, uint32_t mask) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static uint32_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_get_ChannelMask(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static int16_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_NotifyEdit(IEcoLexicalAnalyzer1ScannerPtr_t me, uint64_t startOffset, uint32_t oldLen, uint32_t newLen) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static IEcoLexicalData1Ptr_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_get_LexicalData(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}

static uint32_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_get_CurrentLine(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static uint32_t ECOCALLMETHOD CEcoBLA1Scanner_F82A88F6_get_CurrentColumn(IEcoLexicalAnalyzer1ScannerPtr_t me) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;

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
static int16_t ECOCALLMETHOD initCEcoBLA1Scanner_F82A88F6(/*in*/ CEcoBLA1Scanner_F82A88F6Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBLA1Scanner_F82A88F6* pCMe = (CEcoBLA1Scanner_F82A88F6*)me;
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

    /* Initialize new fields to safe defaults */
    pCMe->m_pIFile = 0;
    pCMe->m_pIData = 0;
    pCMe->m_filePos = 0;
    pCMe->m_line = 1;
    pCMe->m_column = 1;
    pCMe->m_buffer = 0;
    pCMe->m_bufferSize = 0;
    pCMe->m_bufferPos = 0;
    pCMe->m_bufferEnd = 0;
    pCMe->m_currentState = 0;
    pCMe->m_stateStack = 0;
    pCMe->m_stateStackSize = 0;
    pCMe->m_stateStackTop = -1;
    pCMe->m_channelMask = 0xFFFFFFFF; /* include all channels by default */

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
static int16_t ECOCALLMETHOD createCEcoBLA1Scanner_F82A88F6(/* in */ CEcoBLA1Scanner_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBLA1Scanner_F82A88F6(/* in */ CEcoBLA1Scanner_F82A88F6Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;

        if (pCMe->m_pIFile != 0) {
            pCMe->m_pIFile->pVTbl->Close(pCMe->m_pIFile);
            pCMe->m_pIFile = 0;
        }

        if (pCMe->m_pIData != 0) {
            pCMe->m_pIData->pVTbl->Release(pCMe->m_pIData);
        }

        if (pCMe->m_buffer != 0) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_buffer);
        }

        if (pCMe->m_stateStack != 0) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_stateStack);
        }

        if (pCMe->m_Name != 0) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }

        if (pCMe->m_pISys != 0) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }

        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoBLA1Scanner Virtual Table */
IEcoLexicalAnalyzer1ScannerVTbl g_xD0A7FF253BEE4A5B936D195420F8D08CVTbl_F82A88F6 = {
    CEcoBLA1Scanner_F82A88F6_QueryInterface,
    CEcoBLA1Scanner_F82A88F6_AddRef,
    CEcoBLA1Scanner_F82A88F6_Release,
    CEcoBLA1Scanner_F82A88F6_Scan,
    CEcoBLA1Scanner_F82A88F6_Recover,
    CEcoBLA1Scanner_F82A88F6_Peek,
    CEcoBLA1Scanner_F82A88F6_LookAhead,
    CEcoBLA1Scanner_F82A88F6_get_Position,
    CEcoBLA1Scanner_F82A88F6_set_Position,
    CEcoBLA1Scanner_F82A88F6_PushState,
    CEcoBLA1Scanner_F82A88F6_PopState,
    CEcoBLA1Scanner_F82A88F6_get_CurrentState,
    CEcoBLA1Scanner_F82A88F6_SetChannelMask,
    CEcoBLA1Scanner_F82A88F6_get_ChannelMask,
    CEcoBLA1Scanner_F82A88F6_NotifyEdit,
    CEcoBLA1Scanner_F82A88F6_get_LexicalData,
    CEcoBLA1Scanner_F82A88F6_get_CurrentLine,
    CEcoBLA1Scanner_F82A88F6_get_CurrentColumn
};


/* Object Instance */
CEcoBLA1Scanner_F82A88F6 g_xCEcoBLA1Scanner_F82A88F6 = {
    &g_xD0A7FF253BEE4A5B936D195420F8D08CVTbl_F82A88F6,
    initCEcoBLA1Scanner_F82A88F6,
    createCEcoBLA1Scanner_F82A88F6,
    deleteCEcoBLA1Scanner_F82A88F6,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_Name */
	0, /* m_pIFile */            
    0, /* m_pIData */       
    0, /* m_filePos */                
    0, /* m_line */                  
    0, /* m_column */                
    0, /* m_buffer */                   
    0, /* m_bufferSize */             
    0, /* m_bufferPos */             
    0, /* m_bufferEnd */            
    0, /* m_currentState */          
    0, /* m_stateStack */          
    0, /* m_stateStackSize */         
    0, /* m_stateStackTop */         
    0  /* m_channelMask */
};