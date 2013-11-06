/**
  ******************************************************************************
  * @file    system_stm32f0xx.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Source File.
  *
  *
  * 1.  This file provides one function to be called from a user application:
  *      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier
  *                      and Divider factors, AHB/APBx prescalers and Flash settings),
  *                      depending on the configuration selected (see above).
  *                      This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32f0xx.s" file.
  *
  * 2. After each device reset the HSI (8 MHz Range) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_stm32f0xx.c" file, and
  *    thereafter SetSysClock() is called to configure the system clock before to 
  *    branch to main program.
  *
  * 3. If the system clock source selected by user fails to startup, the SystemInit()
  *    function will do nothing and HSI still used as system clock source.
  *
  * 4. The default value of HSE crystal is set to 8MHz, refer to "HSE_VALUE" define
  *    in "stm32f0xx.h" file. When HSE is used as system clock source, directly or
  *    through PLL, and you are using different crystal you have to adapt the HSE
  *    value to your own configuration.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


#include "stm32f0xx.h"

/**
  * @brief  Setup the microcontroller system.
  *         Initialize the Embedded Flash Interface, the PLL and update the
  *         SystemCoreClock variable.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FFB80C;

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  RCC->CFGR &= (uint32_t)0xFFC0FFFF;

  /* Reset PREDIV1[3:0] bits */
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0;

  /* Reset USARTSW[1:0], I2CSW, CECSW and ADCSW bits */
  RCC->CFGR3 &= (uint32_t)0xFFFFFEAC;

  /* Reset HSI14 bit */
  RCC->CR2 &= (uint32_t)0xFFFFFFFE;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;

}

