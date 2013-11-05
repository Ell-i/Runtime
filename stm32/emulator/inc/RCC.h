/*
 * Copyright (c) 2013 ELL-i co-operative
 */

#include <Register.h>

class ResetClockControl {
public:
    DEFINE_REGISTER(RCC, CR,       0x0200FF83); // PLL set for SetSysClock
    DEFINE_REGISTER(RCC, CFGR,     0x00000008); // PLL set for SetSysClock
    DEFINE_REGISTER(RCC, CIR,      0x00000000);
    DEFINE_REGISTER(RCC, APB1RSTR, 0x00000000);
    DEFINE_REGISTER(RCC, AHBENR,   0x00000014);
    DEFINE_REGISTER(RCC, APB2RSTR, 0x00000000);
    DEFINE_REGISTER(RCC, BDCR,     0x00000018);
    DEFINE_REGISTER(RCC, CSR,      0x0C000000);
    DEFINE_REGISTER(RCC, AHBRSTR,  0x00000000);
    DEFINE_REGISTER(RCC, CFGR2,    0x00000000);
    DEFINE_REGISTER(RCC, CFGR3,    0x00000000);
    DEFINE_REGISTER(RCC, CR2,      0x0000FF80);
protected:
    ResetClockControl() {}
public:
    static ResetClockControl RCC;
};

ResetClockControl *const RCC = &ResetClockControl::RCC;
