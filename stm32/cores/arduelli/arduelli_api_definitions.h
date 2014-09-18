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
 *
 * @brief  Macros for defining Arduino API types
 */

#ifndef  _ARDUELLI_API_DEFINITIONS_H_
# define _ARDUELLI_API_DEFINITIONS_H_

# include <system_init.h>

/*
 * Arduino API denominators
 */

# define ARDUINO_INLINE_API              static inline
# define ARDUINO_INLINE_MEMBER_FUNCTION         inline
# define ARDUINO_GLOBAL_IMMUTABLE        static const

#endif //_ARDUELLI_API_FUNCTION_H_
