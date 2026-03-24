/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoBLA1Token_F82A88F6
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoBLA1Token_F82A88F6
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
#include "CEcoBLA1Token.h"

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoLexicalAnalyzer1Token interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_QueryInterface(/* in */ IEcoLexicalAnalyzer1TokenPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoLexicalAnalyzer1Token) ) {
        *ppv = &pCMe->m_pVTblIToken;
        pCMe->m_pVTblIToken->AddRef((IEcoLexicalAnalyzer1Token*)pCMe);
    }
	
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIToken;
        pCMe->m_pVTblIToken->AddRef((IEcoLexicalAnalyzer1Token*)pCMe);
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
 *   AddRef function for the IEcoLexicalAnalyzer1Token interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_AddRef(/* in */ IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

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
 *   Release function for the IEcoLexicalAnalyzer1Token interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_Release(/* in */ IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

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
 * <summary>
 *   MyFunction Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_MyFunction(/* in */ IEcoLexicalAnalyzer1TokenPtr_t me, /* in */ char_t* Name, /* out */ char_t** copyName) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

static uint32_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Type(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}


static char_t* ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Lexeme(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}


static uint16_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Length(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}


static uint32_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_TokenIndex(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}


static uint32_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Line(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}


static uint32_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Column(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}


static uint64_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Position(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}


static char_t* ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Source(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}


static uint32_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Channel(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}


static char_t* ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_LexerState(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}


static void ECOCALLMETHOD CEcoBLA1Token_F82A88F6_set_Tag(IEcoLexicalAnalyzer1TokenPtr_t me, char_t* tag) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return;
    }

    return;
}


static char_t* ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Tag(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}


static void ECOCALLMETHOD CEcoBLA1Token_F82A88F6_set_Value(IEcoLexicalAnalyzer1TokenPtr_t me, voidptr_t value) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return;
    }

    return ;
}


static voidptr_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Value(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}


static char_t* ECOCALLMETHOD CEcoBLA1Token_F82A88F6_get_Description(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}


static bool_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_IsEOF(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
    }

    return ERR_ECO_SUCCESES;
}


static bool_t ECOCALLMETHOD CEcoBLA1Token_F82A88F6_IsError(IEcoLexicalAnalyzer1TokenPtr_t me) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return 0;
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
static int16_t ECOCALLMETHOD initCEcoBLA1Token_F82A88F6(/*in*/ CEcoBLA1Token_F82A88F6Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoBLA1Token_F82A88F6* pCMe = (CEcoBLA1Token_F82A88F6*)me;
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
static int16_t ECOCALLMETHOD createCEcoBLA1Token_F82A88F6(/* in */ CEcoBLA1Token_F82A88F6Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
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
static void ECOCALLMETHOD deleteCEcoBLA1Token_F82A88F6(/* in */ CEcoBLA1Token_F82A88F6Ptr_t pCMe) {
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

/* IEcoLexicalAnalyzer1Token Virtual Table */
IEcoLexicalAnalyzer1TokenVTbl g_xE119E477D7664E4B894592C16187740EVTbl_F82A88F6 = {
    CEcoBLA1Token_F82A88F6_QueryInterface,
    CEcoBLA1Token_F82A88F6_AddRef,
    CEcoBLA1Token_F82A88F6_Release,
    CEcoBLA1Token_F82A88F6_get_Type,
    CEcoBLA1Token_F82A88F6_get_Lexeme,
    CEcoBLA1Token_F82A88F6_get_Length,
    CEcoBLA1Token_F82A88F6_get_TokenIndex,
    CEcoBLA1Token_F82A88F6_get_Line,
    CEcoBLA1Token_F82A88F6_get_Column,
    CEcoBLA1Token_F82A88F6_get_Position,
    CEcoBLA1Token_F82A88F6_get_Source,
    CEcoBLA1Token_F82A88F6_get_Channel,
    CEcoBLA1Token_F82A88F6_get_LexerState,
    CEcoBLA1Token_F82A88F6_set_Tag,
    CEcoBLA1Token_F82A88F6_get_Tag,
    CEcoBLA1Token_F82A88F6_set_Value,
    CEcoBLA1Token_F82A88F6_get_Value,
    CEcoBLA1Token_F82A88F6_get_Description,
    CEcoBLA1Token_F82A88F6_IsEOF,
    CEcoBLA1Token_F82A88F6_IsError
};



/* Object Instance */
CEcoBLA1Token_F82A88F6 g_xCEcoBLA1Token_F82A88F6 = {
    &g_xE119E477D7664E4B894592C16187740EVTbl_F82A88F6,
    initCEcoBLA1Token_F82A88F6,
    createCEcoBLA1Token_F82A88F6,
    deleteCEcoBLA1Token_F82A88F6,
    1, /* m_cRef */
    0, /* m_pISys */
    0, /* m_pISys */
    0  /* m_Name */
};
