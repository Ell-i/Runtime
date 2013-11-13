/*
 * Copyright (c) 2013 ELL-i co-operative.
 */

#include <system_init.h>

void SystemInitMaskOnly(const SystemInitRecord *records) {
}

void SystemInitMaskAndValue(const SystemInitRecord *records) {
}

/*
 * Function pointer table, indexed by the enum.
 */
typedef void (*SystemInitFunctionType)(const SystemInitRecord *records);

const SystemInitFunctionType SystemInitFunctions[SYSTEM_INIT_TYPES] = {
    SystemInitMaskOnly,
    SystemInitMaskAndValue,
};

/*
 * Start and end addresses of the peripheral initialisation records.
 */
extern int __peripheral_start, __peripheral_end;
const SystemInitRecord *const peri_start = (const SystemInitRecord *)&__peripheral_start;
const SystemInitRecord *const peri_end   = (const SystemInitRecord *)&__peripheral_end;

void SystemInitPeripherals(void) {
    for (register const SystemInitRecord *ir = peri_start; ir < peri_end; ir++) {
        SystemInitFunctions[ir->init_record_type](ir);
    }
}


