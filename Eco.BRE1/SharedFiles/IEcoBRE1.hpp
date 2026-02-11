/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoBRE1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoBRE1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOBRE1_HPP__
#define __I_ECOBRE1_HPP__

#include "IEcoBase1.hpp"

/* IEcoBRE1 IID = {25F98342-4A72-4CBB-B270-A4BF6468C8A8} */
#ifndef __IID_IEcoBRE1
static const UGUID IID_IEcoBRE1 = {0x01, 0x10, {0x25, 0xF9, 0x83, 0x42, 0x4A, 0x72, 0x4C, 0xBB, 0xB2, 0x70, 0xA4, 0xBF, 0x64, 0x68, 0xC8, 0xA8}};
#endif /* __IID_IEcoBRE1 */

interface IEcoBRE1 : public IEcoUnknown {
public:
    /* IEcoBRE1 */
    virtual int16_t ECOCALLMETHOD MyFunction(/* in */ char_t* Name, /* out */ char_t** CopyName) = 0;

};



#endif /* __I_ECOBRE1_HPP__ */
