/*
 * Copyright (c) 2013 ELL-i co-operative
 */

#include <Register.h>

class Flash {
public:
    DEFINE_REGISTER(FLASH, ACR,     0x0000000);
    DEFINE_REGISTER(FLASH, KEYR,    0x0000000);
    DEFINE_REGISTER(FLASH, OPTKEYR, 0x0000000);
    DEFINE_REGISTER(FLASH, SR,      0x0000000);
    DEFINE_REGISTER(FLASH, CR,      0x0000080);
protected:
    Flash()
        : ACR()
        , CR()
        {}
public:
    static Flash FLASH;
};

Flash *const FLASH = &Flash::FLASH;
