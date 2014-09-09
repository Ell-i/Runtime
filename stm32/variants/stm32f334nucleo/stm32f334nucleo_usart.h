/*
 * Copyright (c) 2014 ELL-i co-operative.
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
 * along with ELL-i software.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/*
 * @author Otso Jousimaa <otso@ojousima.net> 2014
 */

#ifndef _STM32F334NUCLEO_USART_H_
# define _STM32F334NUCLEO_USART_H_

# include <arduelli_usart.h>

/**
 * Declarations for externally visible USART init records.
 *
 * STM32F334 has USART ports 1, 2, 3.
 */

USART_INIT_DEFAULT(1);
USART_INIT_DEFAULT(2);
USART_INIT_DEFAULT(3);


#endif //_STM32F334NUCLEO_USART_H_
