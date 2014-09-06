/*
 * Copyright (c) 2014 ELL-i co-operative.
 *
 * This file is part of ELL-i software.
 *
 * ELL-i software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ELL-i software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ELL-i software.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Otso Jousimaa <otso@ojousima.net> 2014
 */

#include <stm32f334nucleo_usart.h>

/*
 * Boot-time definitions for the STM32F3 series MCU USART registers.
 */

#ifdef __cplusplus
# define D32(p, r, v) { v }
#else
# ifndef offsetof
#  define offsetof(st, m) ((uint32_t)(&((st *)0)->m))
# endif
# define D32(p, r, v) [offsetof(p, r)/sizeof(uint32_t)] = { v }
#endif

#if 0 // TODO \/
const SystemInitRecordData32Only USART_INIT_DefaultRecords[] = {
    D32(USART_TypeDef, CR1,
        0
        | ! USART_CR1_EOBIE    /* 0: No smartcard end of block interrupts */
        | ! USART_CR1_RTOIE    /* 0: No receiver timeout interrupts */
        | ! USART_CR1_DEAT     /* 0: RS-485 driver enable not used, no assertion time */
        | ! USART_CR1_DEDT     /* 0: RS-485 driver enable not used, no deassertion time */
        | ! USART_CR1_OVER8    /* 0: Oversampling by 16 */
        | ! USART_CR1_CMIE     /* 0: No character matching interrupts */
        | ! USART_CR1_MME      /* 0: Receiver in active mode permanently */
        /* The Arduino default is 8 data bits, no parity, one stop bit. */
        | ! USART_CR1_M        /* 0: 1 Start bit, 8 data bits */
        | ! USART_CR1_WAKE     /* 0: Not used, active mode permanently */
        | ! USART_CR1_PCE      /* 0: No parity */
        | ! USART_CR1_PS       /* 0: Not used, parity not used */
        | ! USART_CR1_PEIE     /* 0: Not used, parity not used */
        |   USART_CR1_TXEIE    /* 1: Enable transmit interrupts */
        | ! USART_CR1_TCIE     /* 0: Disable transmission complete interrupts */
        |   USART_CR1_RXNEIE   /* 1: Enable receive interrupts */
        | ! USART_CR1_IDLEIE   /* 0: Disable idel interrupt */
        | ! USART_CR1_TE       /* 0: Disable transmitter, XXX TBD */
        |   USART_CR1_RE       /* 1: Enable receiver, effective only once UE will be asserted */
        | ! USART_CR1_UESM     /* 0: Wakeup from stop disabled */
        | ! USART_CR1_UE       /* 0: Do not enable the USART, only configure it at this time */
        ),
    D32(USART_TypeDef, CR2,
        0
        | ! USART_CR2_ADD      /* 0x00: Default value, addressing not used */
        | ! USART_CR2_RTOEN    /* 0:    Default value, Receiver timeout disabled */
        | ! USART_CR2_ABRMODE  /* 00:   Default value, autobaud not used */
        | ! USART_CR2_ABREN    /* 0:    Autobaud rate detection disabled */
        | ! USART_CR2_MSBFIRST /* 0:    Default value, LSB first */
        | ! USART_CR2_DATAINV  /* 0:    Default value, normal logic */
        | ! USART_CR2_TXINV    /* 0:    Default value, TX standard logic levels */
        | ! USART_CR2_RXINV    /* 0:    Default value, RX standard logic levels */
        | ! USART_CR2_SWAP     /* 0:    Default value, RX and TX normally connected */
        | ! USART_CR2_LINEN    /* 0:    Default value, LIN mode disabled */
        | ! USART_CR2_STOP     /* 00:   1 stop bit */
        | ! USART_CR2_CLKEN    /* 0:    Default value, SCLK pin disabled */
        | ! USART_CR2_CPOL     /* 0:    Default value, SCLK not used */
        | ! USART_CR2_CPHA     /* 0:    Default value, SCLK not used */
        | ! USART_CR2_LBCL     /* 0:    Default value, SCLK not used */
        | ! USART_CR2_LBDIE    /* 0:    Default value, LIN mode not used */
        | ! USART_CR2_LBDL     /* 0:    Default value, LIN mode not used */
        | ! USART_CR2_ADDM7    /* 0:    Default value, addressing not used */
        ),
    D32(USART_TypeDef, CR3,
        0
        | ! USART_CR3_WUFIE    /* 0:    Defalut value, wakeup from stop not used */
        | ! USART_CR3_WUS      /* 00:   Default value, wakeup from stop not used */
        | ! USART_CR3_SCARCNT  /* 000:  Default value, smartcart mode not used */
        | ! USART_CR3_DEP      /* 0:    Default value, driver enable not used */
        | ! USART_CR3_DEM      /* 0:    Default value, driver enable not used */
        | ! USART_CR3_DDRE     /* 0:    Default value, DMA not used */
        |   USART_CR3_OVRDIS   /* 1:    Overrun functionality disabled XXX TBD */
        | ! USART_CR3_ONEBIT   /* 0:    Default value, three sample bit method */
        | ! USART_CR3_CTSIE    /* 0:    Default value, CTS not used */
        | ! USART_CR3_CTSE     /* 0:    Default value, CTS not used */
        | ! USART_CR3_RTSE     /* 0:    Default value, RTS not used */
        | ! USART_CR3_DMAT     /* 0:    Default value, DMA not used */
        | ! USART_CR3_DMAR     /* 0:    Default value, DMA not used */
        | ! USART_CR3_SCEN     /* 0:    Default value, Smartcard mode not used */
        | ! USART_CR3_NACK     /* 0:    Default value, Smartcard mode not used */
        | ! USART_CR3_HDSEL    /* 0:    Default value, halfduplex not used */
        | ! USART_CR3_IRLP     /* 0:    Default value, IrDA not used */
        | ! USART_CR3_IREN     /* 0:    Default value, IrDA not used */
        | ! USART_CR3_EIE      /* 0:    Disable error interrupts, XXX TBD */
        ),
    /* Default to 115200 bauds at 48 MHz clock, see Table 48 on page 589 of RM0091 */
    D32(USART_TypeDef, BRR, 0x1A1),
    /* Guard time and prescaler not needed as IrDA nor smartcard are used */
    D32(USART_TypeDef, GTPR, 0),
    /* Receiver timeout not used */
    D32(USART_TypeDef, RTOR, 0),
};
// TODO ^


/*
 * Boot-time definitions for the STM32F4 series MCU USARTs.
 *
 * These macros here generate SystemInitRecord structures to the
 * SYSTEM_INIT_SECTION linker section.  The boot time initialisation
 * code iterates the records from that section, initialising the MCU
 * peripheral ports accordingly.
 */

DEFINE_USART_DEVICE(/*USART*/1, /*APB*/2, USART_INIT_DefaultRecords);
DEFINE_USART_DEVICE(/*USART*/2, /*APB*/1, USART_INIT_DefaultRecords);
DEFINE_USART_DEVICE(/*USART*/3, /*APB*/1, USART_INIT_DefaultRecords);
// DEFINE_USART_DEVICE(/*USART*/4, /*APB*/1, USART_INIT_DefaultRecords); // UART
// DEFINE_USART_DEVICE(/*USART*/5, /*APB*/1, USART_INIT_DefaultRecords); // UART
DEFINE_USART_DEVICE(/*USART*/6, /*APB*/2, USART_INIT_DefaultRecords);

#endif //TODO
