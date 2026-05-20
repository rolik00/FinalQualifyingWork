/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   EcoIDL1
 * </summary>
 *
 * <description>
 *   This source file is the entry point
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoIDL1.h"
#include "IEcoCommandArguments1.h"
#include "IdEcoString1.h"
#include "IdEcoList1.h"
#include "IdEcoQueue1.h"
#include "IdEcoStdIOC89.h"
#include "IdEcoAST1.h"
#include "IdEcoFSM1.h"
#include "IdEcoTree1.h"
#include "IdEcoStack1.h"
#include "IdEcoVisitor1.h"
#include "IdEcoDictionary1.h"
#include "IdEcoDateTime1.h"
#include "IdEcoData1.h"
#include "IdEcoMap2.h"
#include "IdEcoSet2.h"
#include "IdEcoFLD1.h"
#include "IdEcoPDA1.h"
#include "IdEcoComparator1.h"
#include "IdEcoBLA1.h"
#include "IdEcoBSA1.h"
#include "IdEcoBNF1.h"
#include "IdEcoBRE1.h"
#include "IdEcoLR1.h"
#include "IdEcoBinaryTree1.h"
#include "IdEcoIDL1C.h"
#include "IdEcoIDL1CPP.h"
#include "IdEcoIDL1Java.h"
#include "IdEcoIDL1Python.h"

void PrintUsage(/* in */ IEcoStdIOC89* pIStdIO);
void PrintComponentError(/* in */ IEcoStdIOC89* pIStdIO, /* in */ const UGUID* riid, /* in */ char_t* Name, /* in */ int16_t errorCode);

/* Конвертация символа HEX в число */
static int8_t HexCharToInt(char_t c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

/* Парсинг GUID из строки */
static int16_t ParseUGUID(const char_t* str, UGUID* guid) {
    uint32_t i = 0;
    int16_t byteIdx = 0;
    int8_t n1, n2;
    uint8_t* pBytes = (uint8_t*)guid;

    for (i = 0; i < sizeof(UGUID); i++) {
		pBytes[i] = 0;
	}

    if (!str || !guid) {
		return -1;
	}

    i = 0;
    while (str[i] != '\0' && byteIdx < (int16_t)sizeof(UGUID)) {
        if (str[i] == '-' || str[i] == '{' || str[i] == '}' || str[i] == ' ' || str[i] == ':') {
            i++;
            continue;
        }

        n1 = HexCharToInt(str[i++]);
        if (n1 == -1) {
			return -1;
		}

        while (str[i] == '-') {
			i++;
		}

        if (str[i] == '\0') {
			return -1;
		}
        n2 = HexCharToInt(str[i++]);
        if (n2 == -1) {
			return -1;
		}

        pBytes[byteIdx++] = (uint8_t)((n1 << 4) | n2);
    }

    return (byteIdx >= 16) ? 0 : -1;
}

/* Ручной парсинг строки Key=Value */
static void ParseConfigLine(char_t* line, char_t* key, char_t* value) {
    int16_t i = 0, k = 0, v = 0;
    int8_t isValue = 0;
    
    key[0] = 0;
    value[0] = 0;

    for (i = 0; line[i] != '\0' && line[i] != '\r' && line[i] != '\n'; i++) {
        if (line[i] == '=' && !isValue) {
            isValue = 1;
            key[k] = '\0';
            continue;
        }
        if (!isValue) {
            if (k < 63) key[k++] = line[i];
        } else {
            if (v < 127) value[v++] = line[i];
        }
    }
    key[k] = '\0';
    value[v] = '\0';
}

/* Чтение файла конфигурации */
static void LoadEmittersConfig(IEcoStdIOC89* pIStdIO, IEcoIDL1* pIIDL, IEcoFileSystemManagement1* pIFSM, IEcoMemoryAllocator1* pIMem, const char_t* configFile) {
    IEcoFileManager1* pIFM = 0;
    IEcoFile1* pFile = 0;
    uint32_t fileSize = 0;
    char_t* buffer = 0;
    char_t* current = 0;
    char_t line[256];
    char_t langId[64];
    char_t guidStr[128];
    UGUID cid;
    int16_t i;

    if (pIFSM) {
        pIFM = pIFSM->pVTbl->get_FileManager(pIFSM);
    }

    if (pIFM) {
        pFile = pIFM->pVTbl->Open(pIFM, (char_t*)configFile);
    }

    if (!pFile) {
        pIStdIO->pVTbl->printf(pIStdIO, "Warning: Configuration file '%s' not found. Using default internal emitters.\n", configFile);
        pIIDL->pVTbl->RegisterEmitter(pIIDL, &CID_EcoIDL1C, "C");
        pIIDL->pVTbl->RegisterEmitter(pIIDL, &CID_EcoIDL1CPP, "CPP");
        pIIDL->pVTbl->RegisterEmitter(pIIDL, &CID_EcoIDL1Java, "Java");
        pIIDL->pVTbl->RegisterEmitter(pIIDL, &CID_EcoIDL1Python, "Python");
        return;
    }

    pIStdIO->pVTbl->printf(pIStdIO, "Loading language emitters from '%s'...\n", configFile);

    fileSize = pFile->pVTbl->get_Size(pFile);
    buffer = (char_t*)pIMem->pVTbl->Alloc(pIMem, fileSize + 1);

    if (buffer) {
        pFile->pVTbl->Read(pFile, buffer, &fileSize);
        buffer[fileSize] = '\0';
        current = buffer;

        while (*current != '\0') {
            i = 0;
            
            while (*current != '\0' && *current != '\n' && *current != '\r' && i < 255) {
                line[i++] = *current++;
            }
            line[i] = '\0';

            while (*current == '\n' || *current == '\r') {
                current++;
            }

            if (line[0] == '\0' || line[0] == ';' || line[0] == '#' || line[0] == '[') {
                continue;
            }

            ParseConfigLine(line, langId, guidStr);

            if (langId[0] != '\0' && guidStr[0] != '\0') {
                if (ParseUGUID(guidStr, &cid) == 0) {
                    pIIDL->pVTbl->RegisterEmitter(pIIDL, &cid, langId);
                    pIStdIO->pVTbl->printf(pIStdIO, "  [+] Registered: %s -> %s\n", langId, guidStr);
                } else {
                    pIStdIO->pVTbl->printf(pIStdIO, "  [!] Error parsing GUID for %s: %s\n", langId, guidStr);
                }
            }
        }
        
        pIMem->pVTbl->Free(pIMem, buffer);
    }

    pFile->pVTbl->Close(pFile);
    pIStdIO->pVTbl->printf(pIStdIO, "----------------------------------------\n");
}

/*
 *
 * <summary>
 *   EcoMain Function
 * </summary>
 *
 * <description>
 *   EcoMain function - entry point
 * </description>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Pointer to the system interface */
    IEcoSystem1* pISys = 0;
    IEcoCommandArguments1* pICmdArg = 0;
    /* Pointer to the interface for working with the system interface bus */
    IEcoInterfaceBus1* pIBus = 0;
    /* Pointer to the memory management interface */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на интерфейс работы сo строкой */
    IEcoString1* pIStr = 0;
    /* Указатель на интерфейс работы со стандартным вводом/выводом LibC стандарта 89  */
    IEcoStdIOC89* pIStdIO = 0;
	/* Pointer to the tested interface */
    IEcoIDL1* pIIDL = 0;
    IEcoIDL1ProjectLayout* pILayout = 0;
	IEcoFileSystemManagement1* pIFSM = 0;

    /* Переменные */
    char_t* pszArg = 0;
    char_t* pszIDLFileName = 0;
    char_t* pszOutputPath= 0;
    char_t* pszFileExt = 0;
    char_t* pszLangId = "ALL";
	bool_t bGenerateTlb = 0;
    int16_t iArgIndex = 0;
    IEcoAST1* pIAST = 0;
    
    /* System interface check and creation */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Free the system interface in case of an error */
            goto Release;
        }
    }

    /* Getting the interface for working with the interface bus */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Free in case of an error */
        goto Release;
    }
#ifdef ECO_LIB
    /* Registration of a static component for working with the list */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoIDL1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_54F2EF99574346E49122AA7840BB8A88);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoStdIOC89, (IEcoUnknown*)GetIEcoComponentFactoryPtr_00000000000000000000000053494F31);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
	/* Регистрация статического компонента файловой системы */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoFileSystemManagement1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_00000000000000000000000046534D31);
    if (result != 0 ) {
		goto Release;
	}
    /* Регистрация статического компонента для работы с AST */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoAST1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_2FE0BD508F5743BDA9F52414233542A8);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с конечным автоматом */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoFSM1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5E7C610CB846447DB59A3C5A2C4F446F);
    if (result != 0 ) {
        goto Release;
    }
    /* Регистрация статического компонента для работы с BLA */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBLA1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_88DD94592E7C48BAB381EAA0F82A88F6);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    /* Регистрация статического компонента для работы с BNF */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBNF1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_323DD55E33D040FA98068E2FCB1CBD49);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    /* Регистрация статического компонента для работы с BSA */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBSA1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_FF73C4B2F8B0484897DB3298F6E9D8E1);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    /* Регистрация статического компонента для работы с LR */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLR1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_F4561FD215A34CC5BA1D8791A441A18E);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с BRE */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBRE1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_755D526AEBF943E9B4AA4F860E0B7D40);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с бинарным деревом */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoBinaryTree1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_7CAD4D0215EF4EDFB1FF6A7CAF1C3D6C);
    if (result != 0 ) {
        goto Release;
    }

    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы со словарем */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoDictionary1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_2912A7C7E0B84B4D9BFE9500EF4667D3);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с деревом */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoTree1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_82F73722057E47F3A2931ED27087694D);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы со строкой */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoString1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_84CC0A7DBABD44EEBE749C9A8312D37E);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с визитером */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoVisitor1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4E7C20FEFAF341069B5C42497B462BBE);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы со стеком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoStack1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_18129B1DCF9248D9A7787F9206E2D6DC);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы со стеком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoSet2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_58CDC2713209420CAC919BE1E16F4CA4);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с датой и вреенем */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoDateTime1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5B2BA17BEA704527BC708F88568FE115);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Queue */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoQueue1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_25D72F83A2564F4E9F59E489BE85E2A4);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с Dictionary */
    result =pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoDictionary1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_2912A7C7E0B84B4D9BFE9500EF4667D3);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с данными */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoData1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5A0F0DD57E6448EC9EE0E5D67572B47E);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с интерфейсом сравнениия */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoComparator1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_44CE56A815DF433EB567D8943DA32D8E);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с ассоциированным масивом */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMap2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_715AF131CD174E90AAF3B753221B9B73);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с форматом формальных языков */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoFLD1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_F9E1B4FA37A7446C94A4D1E8BAA65DB1);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с PDA */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoPDA1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_A03120BB3AF5425EBDE0A5535B423579);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoIDL1C, (IEcoUnknown*)GetIEcoComponentFactoryPtr_E89F37B5194F4F4A8ADE1FFB28028A01);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoIDL1CPP, (IEcoUnknown*)GetIEcoComponentFactoryPtr_8F45C7FFB8144066BEAFF11296176293);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoIDL1Java, (IEcoUnknown*)GetIEcoComponentFactoryPtr_C26F52E0372D4051A290C1BD286DCE90);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoIDL1Python, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4F8058F313B346A887D59E582C7799FC);
    if (result != 0 ) {
        /* Free in case of an error */
        goto Release;
    }
#endif
    /* Getting the memory management interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Check */
    if (result != 0 || pIMem == 0) {
        /* Free the system interface in case of an error */
        goto Release;
    }

    /* Получение интерфейса для работы с аргументами командной строки */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoCommandArguments1, (void **)&pICmdArg);
    if (result != 0 || pICmdArg == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса для работы со стандартным вводом/выводом LibC стандарта 89 */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoStdIOC89, 0, &IID_IEcoStdIOC89, (void**) &pIStdIO);
    /* Проверка */
    if (result != 0 || pIStdIO == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoFileSystemManagement1, 0, &IID_IEcoFileSystemManagement1, (void**) &pIFSM);

    /* Вывод информации */
    pIStdIO->pVTbl->printf(pIStdIO, "Eco IDL v.1.0.0\n");
    pIStdIO->pVTbl->printf(pIStdIO, "Copyright (C) 2026 LLC PeerF\n");


    /* Getting the tested interface */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoIDL1, 0, &IID_IEcoIDL1, (void**) &pIIDL);
    if (result != 0 || pIIDL == 0) {
        /* Free interfaces in case of an error */
        goto Release;
    }


    /* Получение интерфейса для работы со строкой */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void **)&pIStr);
    if (result != 0 || pIStr == 0) {
        PrintComponentError(pIStdIO, &CID_EcoString1, "EcoString1", result);
        /* Освобождение в случае ошибки */
        goto Release;
    }

	LoadEmittersConfig(pIStdIO, pIIDL, pIFSM, pIMem, "config.ini");

    /* Вывод информации в случае отсутствия параметров */
    if ( pICmdArg->pVTbl->get_Count(pICmdArg) <= 1) {
        PrintUsage(pIStdIO);
		goto Release;
    }

    /* Парсинг аргументов командной строки */
    for(iArgIndex = 1; iArgIndex < pICmdArg->pVTbl->get_Count(pICmdArg); iArgIndex++) {
        pszArg = pICmdArg->pVTbl->get_Arg(pICmdArg, iArgIndex);
        
        if (pIStr->pVTbl->Compare(pIStr, pszArg, "/HELP") == 0 || pIStr->pVTbl->Compare(pIStr, pszArg, "-help") == 0)  {
            PrintUsage(pIStdIO);
            goto Release;
        }
        else if (pIStr->pVTbl->Compare(pIStr, pszArg, "/lang") == 0 || pIStr->pVTbl->Compare(pIStr, pszArg, "-lang") == 0)  {
            if (iArgIndex + 1 < pICmdArg->pVTbl->get_Count(pICmdArg)) {
                iArgIndex++;
                pszLangId = pICmdArg->pVTbl->get_Arg(pICmdArg, iArgIndex);
            }
            continue;
        }
        else if (pIStr->pVTbl->Compare(pIStr, pszArg, "/out") == 0 || pIStr->pVTbl->Compare(pIStr, pszArg, "-out") == 0)  {
            if (iArgIndex + 1 < pICmdArg->pVTbl->get_Count(pICmdArg)) {
                iArgIndex++;
                pszOutputPath = pICmdArg->pVTbl->get_Arg(pICmdArg, iArgIndex);
            }
            continue;
        }
        else if (pIStr->pVTbl->Compare(pIStr, pszArg, "/tlb") == 0 || pIStr->pVTbl->Compare(pIStr, pszArg, "-tlb") == 0)  {
            bGenerateTlb = 1;
            continue;
        }
        else {
            pszFileExt = pIStr->pVTbl->SearchLastCharacter(pIStr, pszArg, '.');
            if (pszFileExt != 0 && pIStr->pVTbl->Compare(pIStr, pszFileExt, ".idl") == 0) {
                pszIDLFileName = pszArg;
            }
        }
    }

    if (pszIDLFileName == 0) {
        pIStdIO->pVTbl->printf(pIStdIO, "Error: No input .idl file specified.\n");
        goto Release;
    }

    pIStdIO->pVTbl->printf(pIStdIO, "Processing file: %s (Target Lang: %s)\n", pszIDLFileName, pszLangId);

    /* 1. Инициализация внутреннего состояния (лексера/парсера) */
    result = pIIDL->pVTbl->Initialize(pIIDL);
    if (result != 0) {
        pIStdIO->pVTbl->printf(pIStdIO, "Error: Failed to initialize IDL engine.\n");
        goto Release;
    }

    /* 2. Парсинг входного IDL файла. Внутри будет выведен отладочный список токенов */
    result = pIIDL->pVTbl->ParseFile(pIIDL, pszIDLFileName, &pIAST);
    if (result != 0 /*|| pIAST == 0*/) { 
        pIStdIO->pVTbl->printf(pIStdIO, "Error: Parsing failed for file: %s\n", pszIDLFileName);
        goto Release;
    }

    /* 3. Подготовка структуры проекта */
    result = pIIDL->pVTbl->QueryInterface(pIIDL, &IID_IEcoIDL1ProjectLayout, (void**) &pILayout);
    if (result == 0 && pILayout != 0) {
        pILayout->pVTbl->SetRootPath(pILayout, pszOutputPath ? pszOutputPath : ".");
        pILayout->pVTbl->SetArtifactPath(pILayout, ECO_IDL_ARTIFACT_INTERFACE, "inc");
        pILayout->pVTbl->SetArtifactPath(pILayout, ECO_IDL_ARTIFACT_ID_FILE, "src");
    }

    /* 4. Запуск генерации */
    result = pIIDL->pVTbl->Generate(pIIDL, pIAST, pILayout, pszLangId, (void*)pszOutputPath);
    if (result == -2) {
        pIStdIO->pVTbl->printf(pIStdIO, "Error: Target language '%s' is not registered. Check config.ini!\n", pszLangId);
    } 
    else if (result == -3) {
        pIStdIO->pVTbl->printf(pIStdIO, "Error: Emitter for '%s' is registered, but the component failed to load. (Check GUID or missing DLL/LIB)\n", pszLangId);
    } 
    else if (result == -4) {
        pIStdIO->pVTbl->printf(pIStdIO, "Warning: Generation completed partially. Some language components failed to load.\n");
    } 
    else if (result != 0) {
        pIStdIO->pVTbl->printf(pIStdIO, "Error: Generation failed with code %d.\n", result);
    } 
    else {
        pIStdIO->pVTbl->printf(pIStdIO, "Success: Generation completed.\n");
    }

Release:
	if (pIFSM != 0) pIFSM->pVTbl->Release(pIFSM);
    if (pILayout != 0) pILayout->pVTbl->Release(pILayout);
    if (pIStr != 0) pIStr->pVTbl->Release(pIStr);
    if (pIIDL != 0) pIIDL->pVTbl->Release(pIIDL);
    if (pIStdIO != 0) pIStdIO->pVTbl->Release(pIStdIO);
    if (pIMem != 0) pIMem->pVTbl->Release(pIMem);
    if (pIBus != 0) pIBus->pVTbl->Release(pIBus);
    if (pISys != 0) pISys->pVTbl->Release(pISys);

    return result;
}

/*
 *
 * <сводка>
 *   Функция PrintUsage
 * </сводка>
 *
 * <описание>
 *   Функция вывода информации о программе в консоль
 * </описание>
 *
 */
void PrintUsage(/* in */ IEcoStdIOC89* pIStdIO) {
    if (pIStdIO != 0) {
        pIStdIO->pVTbl->printf(pIStdIO, "Usage: eco-idl [OPTIONS]... <input.idl>\n");
        pIStdIO->pVTbl->printf(pIStdIO, "Options:\n");
        pIStdIO->pVTbl->printf(pIStdIO, "    /HELP, -help           Display this help message.\n");
        pIStdIO->pVTbl->printf(pIStdIO, "    /lang, -lang <id>      Specify target language emitter ('C', 'CPP', 'Java', 'Python', 'ALL').\n");
        pIStdIO->pVTbl->printf(pIStdIO, "                           If omitted or set to 'ALL', generates for all registered languages.\n");
        pIStdIO->pVTbl->printf(pIStdIO, "    /out,  -out <dir>      Set the root output directory.\n");
        pIStdIO->pVTbl->printf(pIStdIO, "    /tlb,  -tlb            Generate binary type library.\n");
        pIStdIO->pVTbl->printf(pIStdIO, "\nExamples:\n");
        pIStdIO->pVTbl->printf(pIStdIO, "    eco-idl -lang C -out ./build MyInterface.idl\n");
        pIStdIO->pVTbl->printf(pIStdIO, "    eco-idl -lang ALL MyInterface.idl\n");
    }
}


/*
 *
 * <сводка>
 *   Функция PrintComponentError
 * </сводка>
 *
 * <описание>
 *   Функция вывода ошибки в консоль
 * </описание>
 *
 */
void PrintComponentError(/* in */ IEcoStdIOC89* pIStdIO, /* in */ const UGUID* riid, /* in */ char_t* Name, /* in */ int16_t errorCode) {
    char_t* pszDescr = 0;
    if (pIStdIO != 0) {
        switch ((int16_t)errorCode) {
            case (int16_t)ERR_ECO_COMPONENT_NOTFOUND:
                pszDescr = "component not found";
            break;
            default:
                pszDescr = "Unknown";
        };
        pIStdIO->pVTbl->printf(pIStdIO, "Error: Code: %04hX - Component ID: %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X - <%s> - %s.\n",
            errorCode, riid->Data[0], riid->Data[1], riid->Data[2], riid->Data[3], riid->Data[4], riid->Data[5], riid->Data[6], riid->Data[7], riid->Data[8],
            riid->Data[9], riid->Data[10], riid->Data[11], riid->Data[12], riid->Data[13], riid->Data[14], riid->Data[15], Name, pszDescr);
    }
}
