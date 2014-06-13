/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
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
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2013-2014
 */

#ifndef _SYSTEM_MEMORY_H_
# define _SYSTEM_MEMORY_H_

#  ifndef memcpy
extern void *memcpy(void *dst, const void *src, size_t size);
#  endif
#  ifndef memset
extern void *memset(void *dst, int c, size_t size);
#  endif

#endif//_SYSTEM_MEMORY_H_
