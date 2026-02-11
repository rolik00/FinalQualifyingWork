/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoBRE1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoBRE1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_BRE_1_H__
#define __C_ECO_BRE_1_H__

#include "IEcoBRE1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoRegEx1Builder.h"

typedef struct ParseContext {
    char* current;             
    IEcoRegEx1Builder* builder;
} ParseContext;

typedef struct CEcoBRE1_0E0B7D40* CEcoBRE1_0E0B7D40Ptr_t;

typedef struct CEcoBRE1_0E0B7D40 {

    /* Таблица функций интерфейса IEcoBRE1 */
    IEcoBRE1VTbl* m_pVTblIEcoBRE1;


    /* Инициализация экземпляра */
    int16_t (ECOCALLMETHOD *Init)(/*in*/ CEcoBRE1_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem);
    /* Создание экземпляра */
    int16_t (ECOCALLMETHOD *Create)(/*in*/ CEcoBRE1_0E0B7D40Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter);
    /* Удаление */
    void (ECOCALLMETHOD *Delete)(/*in*/ CEcoBRE1_0E0B7D40Ptr_t pCMe);


    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoBRE1_0E0B7D40;

#endif /* __C_ECO_BRE_1_H__ */
