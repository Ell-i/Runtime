
#include <stdint.h>

extern "C" {

uint32_t _sidata, _sdata, _edata, _sbss, _ebss;


extern void Reset_Handler(void);

void start(void) __attribute__((naked));

void __cxa_atexit(void) {
}

#undef main

int main(int ac, char **av) {
    Reset_Handler();
}

}
