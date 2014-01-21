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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

/*
 * Missing STM32F0 Timer definitions
 */

#define TIM_CCMR1_OC1M_PWM1     ((  TIM_CCMR1_OC1M_2 )|(  TIM_CCMR1_OC1M_1 )|( !TIM_CCMR1_OC1M_0 ))
#define TIM_CCMR1_OC1M_PWM2     ((  TIM_CCMR1_OC1M_2 )|(  TIM_CCMR1_OC1M_1 )|(  TIM_CCMR1_OC1M_0 ))

#define TIM_CCMR1_OC2M_PWM1     ((  TIM_CCMR1_OC2M_2 )|(  TIM_CCMR1_OC2M_1 )|( !TIM_CCMR1_OC2M_0 ))
#define TIM_CCMR1_OC2M_PWM2     ((  TIM_CCMR1_OC2M_2 )|(  TIM_CCMR1_OC2M_1 )|(  TIM_CCMR1_OC2M_0 ))

#define TIM_CCMR2_OC3M_Timing   (( !TIM_CCMR2_OC3M_2 )|( !TIM_CCMR2_OC3M_1 )|( !TIM_CCMR2_OC3M_0 ))
#define TIM_CCMR2_OC3M_Active   (( !TIM_CCMR2_OC3M_2 )|( !TIM_CCMR2_OC3M_1 )|(  TIM_CCMR2_OC3M_0 ))
#define TIM_CCMR2_OC3M_Inactive (( !TIM_CCMR2_OC3M_2 )|(  TIM_CCMR2_OC3M_1 )|( !TIM_CCMR2_OC3M_0 ))
#define TIM_CCMR2_OC3M_Toggle   (( !TIM_CCMR2_OC3M_2 )|(  TIM_CCMR2_OC3M_1 )|(  TIM_CCMR2_OC3M_0 ))

#define TIM_CCMR2_OC3M_PWM1     ((  TIM_CCMR2_OC3M_2 )|(  TIM_CCMR2_OC3M_1 )|( !TIM_CCMR2_OC3M_0 ))
#define TIM_CCMR2_OC3M_PWM2     ((  TIM_CCMR2_OC3M_2 )|(  TIM_CCMR2_OC3M_1 )|(  TIM_CCMR2_OC3M_0 ))

#define TIM_CCMR2_OC4M_Timing   (( !TIM_CCMR2_OC4M_2 )|( !TIM_CCMR2_OC4M_1 )|( !TIM_CCMR2_OC4M_0 ))
#define TIM_CCMR2_OC4M_Active   (( !TIM_CCMR2_OC4M_2 )|( !TIM_CCMR2_OC4M_1 )|(  TIM_CCMR2_OC4M_0 ))
#define TIM_CCMR2_OC4M_Inactive (( !TIM_CCMR2_OC4M_2 )|(  TIM_CCMR2_OC4M_1 )|( !TIM_CCMR2_OC4M_0 ))
#define TIM_CCMR2_OC4M_Toggle   (( !TIM_CCMR2_OC4M_2 )|(  TIM_CCMR2_OC4M_1 )|(  TIM_CCMR2_OC4M_0 ))

#define TIM_CCMR2_OC4M_PWM1     ((  TIM_CCMR2_OC4M_2 )|(  TIM_CCMR2_OC4M_1 )|( !TIM_CCMR2_OC4M_0 ))
#define TIM_CCMR2_OC4M_PWM2     ((  TIM_CCMR2_OC4M_2 )|(  TIM_CCMR2_OC4M_1 )|(  TIM_CCMR2_OC4M_0 ))

#define TIM_CCER_CC1P_Rising    (( !TIM_CCER_CC1NP )|( !TIM_CCER_CC1P ))
#define TIM_CCER_CC1P_Falling   (( !TIM_CCER_CC1NP )|(  TIM_CCER_CC1P ))
#define TIM_CCER_CC1P_Both      ((  TIM_CCER_CC1NP )|(  TIM_CCER_CC1P ))
#define TIM_CCER_CC2P_Rising    (( !TIM_CCER_CC2NP )|( !TIM_CCER_CC2P ))
#define TIM_CCER_CC2P_Falling   (( !TIM_CCER_CC2NP )|(  TIM_CCER_CC2P ))
#define TIM_CCER_CC2P_Both      ((  TIM_CCER_CC2NP )|(  TIM_CCER_CC2P ))
#define TIM_CCER_CC3P_Rising    (( !TIM_CCER_CC3NP )|( !TIM_CCER_CC3P ))
#define TIM_CCER_CC3P_Falling   (( !TIM_CCER_CC3NP )|(  TIM_CCER_CC3P ))
#define TIM_CCER_CC3P_Both      ((  TIM_CCER_CC3NP )|(  TIM_CCER_CC3P ))
#define TIM_CCER_CC4P_Rising    (( !TIM_CCER_CC4NP )|( !TIM_CCER_CC4P ))
#define TIM_CCER_CC4P_Falling   (( !TIM_CCER_CC4NP )|(  TIM_CCER_CC4P ))
#define TIM_CCER_CC4P_Both      ((  TIM_CCER_CC4NP )|(  TIM_CCER_CC4P ))

#define GPIO_AFRx_AFRx0_AF0            ((uint32_t)0x00000000)
#define GPIO_AFRx_AFRx0_AF1            ((uint32_t)0x00000001)
#define GPIO_AFRx_AFRx0_AF2            ((uint32_t)0x00000002)
#define GPIO_AFRx_AFRx0_AF3            ((uint32_t)0x00000003)
#define GPIO_AFRx_AFRx0_AF4            ((uint32_t)0x00000004)
#define GPIO_AFRx_AFRx0_AF5            ((uint32_t)0x00000005)
#define GPIO_AFRx_AFRx0_AF6            ((uint32_t)0x00000006)
#define GPIO_AFRx_AFRx0_AF7            ((uint32_t)0x00000007)
#define GPIO_AFRx_AFRx1_AF0            ((uint32_t)0x00000000)
#define GPIO_AFRx_AFRx1_AF1            ((uint32_t)0x00000010)
#define GPIO_AFRx_AFRx1_AF2            ((uint32_t)0x00000020)
#define GPIO_AFRx_AFRx1_AF3            ((uint32_t)0x00000030)
#define GPIO_AFRx_AFRx1_AF4            ((uint32_t)0x00000040)
#define GPIO_AFRx_AFRx1_AF5            ((uint32_t)0x00000050)
#define GPIO_AFRx_AFRx1_AF6            ((uint32_t)0x00000060)
#define GPIO_AFRx_AFRx1_AF7            ((uint32_t)0x00000070)
#define GPIO_AFRx_AFRx2_AF0            ((uint32_t)0x00000000)
#define GPIO_AFRx_AFRx2_AF1            ((uint32_t)0x00000100)
#define GPIO_AFRx_AFRx2_AF2            ((uint32_t)0x00000200)
#define GPIO_AFRx_AFRx2_AF3            ((uint32_t)0x00000300)
#define GPIO_AFRx_AFRx2_AF4            ((uint32_t)0x00000400)
#define GPIO_AFRx_AFRx2_AF5            ((uint32_t)0x00000500)
#define GPIO_AFRx_AFRx2_AF6            ((uint32_t)0x00000600)
#define GPIO_AFRx_AFRx2_AF7            ((uint32_t)0x00000700)
#define GPIO_AFRx_AFRx3_AF0            ((uint32_t)0x00000000)
#define GPIO_AFRx_AFRx3_AF1            ((uint32_t)0x00001000)
#define GPIO_AFRx_AFRx3_AF2            ((uint32_t)0x00002000)
#define GPIO_AFRx_AFRx3_AF3            ((uint32_t)0x00003000)
#define GPIO_AFRx_AFRx3_AF4            ((uint32_t)0x00004000)
#define GPIO_AFRx_AFRx3_AF5            ((uint32_t)0x00005000)
#define GPIO_AFRx_AFRx3_AF6            ((uint32_t)0x00006000)
#define GPIO_AFRx_AFRx3_AF7            ((uint32_t)0x00007000)
#define GPIO_AFRx_AFRx4_AF0            ((uint32_t)0x00000000)
#define GPIO_AFRx_AFRx4_AF1            ((uint32_t)0x00010000)
#define GPIO_AFRx_AFRx4_AF2            ((uint32_t)0x00020000)
#define GPIO_AFRx_AFRx4_AF3            ((uint32_t)0x00030000)
#define GPIO_AFRx_AFRx4_AF4            ((uint32_t)0x00040000)
#define GPIO_AFRx_AFRx4_AF5            ((uint32_t)0x00050000)
#define GPIO_AFRx_AFRx4_AF6            ((uint32_t)0x00060000)
#define GPIO_AFRx_AFRx4_AF7            ((uint32_t)0x00070000)
#define GPIO_AFRx_AFRx5_AF0            ((uint32_t)0x00000000)
#define GPIO_AFRx_AFRx5_AF1            ((uint32_t)0x00100000)
#define GPIO_AFRx_AFRx5_AF2            ((uint32_t)0x00200000)
#define GPIO_AFRx_AFRx5_AF3            ((uint32_t)0x00300000)
#define GPIO_AFRx_AFRx5_AF4            ((uint32_t)0x00400000)
#define GPIO_AFRx_AFRx5_AF5            ((uint32_t)0x00500000)
#define GPIO_AFRx_AFRx5_AF6            ((uint32_t)0x00600000)
#define GPIO_AFRx_AFRx5_AF7            ((uint32_t)0x00700000)
#define GPIO_AFRx_AFRx6_AF0            ((uint32_t)0x00000000)
#define GPIO_AFRx_AFRx6_AF1            ((uint32_t)0x01000000)
#define GPIO_AFRx_AFRx6_AF2            ((uint32_t)0x02000000)
#define GPIO_AFRx_AFRx6_AF3            ((uint32_t)0x03000000)
#define GPIO_AFRx_AFRx6_AF4            ((uint32_t)0x04000000)
#define GPIO_AFRx_AFRx6_AF5            ((uint32_t)0x05000000)
#define GPIO_AFRx_AFRx6_AF6            ((uint32_t)0x06000000)
#define GPIO_AFRx_AFRx6_AF7            ((uint32_t)0x07000000)
#define GPIO_AFRx_AFRx7_AF0            ((uint32_t)0x00000000)
#define GPIO_AFRx_AFRx7_AF1            ((uint32_t)0x10000000)
#define GPIO_AFRx_AFRx7_AF2            ((uint32_t)0x20000000)
#define GPIO_AFRx_AFRx7_AF3            ((uint32_t)0x30000000)
#define GPIO_AFRx_AFRx7_AF4            ((uint32_t)0x40000000)
#define GPIO_AFRx_AFRx7_AF5            ((uint32_t)0x50000000)
#define GPIO_AFRx_AFRx7_AF6            ((uint32_t)0x60000000)
#define GPIO_AFRx_AFRx7_AF7            ((uint32_t)0x70000000)
