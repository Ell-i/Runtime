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
 * Debugging macros for the IP stack
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _NET_DEBUG_H
# define _NET_DEBUG_H

# ifdef EMULATOR
#  include <stdio.h>
#  define net_error(...) fprintf(stderr, __VA_ARGS__)
#  define net_debug(...) fprintf(stderr, __VA_ARGS__)
# else
#  define net_error(...)
#  define net_debug(...)
# endif

#endif //_NET_DEBUG_H
