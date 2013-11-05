
#include <stdint.h>

uint32_t _sidata, _sdata, _edata, _sbss, _ebss;

extern "C" {
    void Reset_Handler(void);
}

#undef main

int main(int ac, char **av) {
    Reset_Handler();
}

