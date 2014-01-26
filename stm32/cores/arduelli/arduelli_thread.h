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

#ifndef _ARDUELLI_THREAD_H_
# define _ARDUELLI_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif
// XXX TBD Most probably move to the system side?  Or have an inline call here?
inline void yield(void) {}; // XXX TBD Replace with a real implementation
#ifdef __cplusplus
}
#endif

#endif//_ARDUELLI_THHREAD_H_
