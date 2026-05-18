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
 *   Данный заголовок описывает реализацию компонента CEcoTreePrintVisitor
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_TREE_PRINT_VISITOR_H__
#define __C_ECO_TREE_PRINT_VISITOR_H__

#include "IEcoTreePrintVisitor.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"
#include "IdEcoVisitor1.h"
#include "IdEcoStack1.h"
#include "IdEcoInterfaceBus1.h"
#include "IEcoTree1.h"

typedef struct CEcoTreePrintVisitor {

    /* Таблица функций интерфейса IEcoTreePrintVisitor */
    IEcoTreePrintVisitorVTbl* m_pVTblIPrint;

    /* Таблица функций интерфейса IEcoVisitor1 */
    IEcoVisitor1VTbl* m_pVTblIVisitor;

	int16_t(*Add_AdditionalInfoForScopes)(struct CEcoTreePrintVisitor* pCMe, IEcoTree1Node* pINode, char_t* offset);

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Интерфейс для работы со строкой */
    IEcoString1* m_pIString;

    /* Интерфейс для работы с журналом */
    IEcoLog1* m_pILog;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Интерфейсная шина */
    IEcoInterfaceBus1* m_pIBus;

} CEcoTreePrintVisitor, *CEcoTreePrintVisitorPtr;

/* Создание экземпляра */
int16_t createCEcoTreePrintVisitor(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoTreePrintVisitor** ppIVisitor);
/* Удаление */
void deleteCEcoTreePrintVisitor(/* in */ IEcoTreePrintVisitor* ppIVisitor);

#endif /* __C_ECO_TREE_PRINT_VISITOR_H__ */
