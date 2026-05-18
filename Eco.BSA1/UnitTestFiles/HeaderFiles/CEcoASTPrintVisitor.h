/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoASTPrintVisitor
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoASTPrintVisitor
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_AST_PRINT_VISITOR_H__
#define __C_ECO_AST_PRINT_VISITOR_H__

#include "IEcoASTPrintVisitor.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"
#include "IdEcoVisitor1.h"
#include "IEcoStack1.h"
#include "IdEcoInterfaceBus1.h"

typedef struct CEcoASTPrintVisitor {

    /* Таблица функций интерфейса IEcoASTPrintVisitor */
    IEcoASTPrintVisitorVTbl* m_pVTblIPrint;

    /* Таблица функций интерфейса IEcoVisitor1 */
    IEcoVisitor1VTbl* m_pVTblIVisitor;

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

} CEcoASTPrintVisitor, *CEcoASTPrintVisitorPtr;

/* Создание экземпляра */
int16_t createCEcoASTPrintVisitor(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoASTPrintVisitor** ppIVisitor);
/* Удаление */
void deleteCEcoASTPrintVisitor(/* in */ IEcoASTPrintVisitor* ppIVisitor);

#endif /* __C_ECO_AST_PRINT_VISITOR_H__ */
