/**
 * C++ But C
 * Copyright (C) 2019  Martino Kuan
 *
 * This file is part of C++ But C.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CPPBC_STDBOOL_H_
#define CPPBC_STDBOOL_H_


#if /* Using C99 or above. */ \
    defined(__STDC_VERSION__) \
    && (__STDC_VERSION__ >= 199901L)

#include <stdbool.h>

#elif /* Using C89. */ \
    !defined(__cplusplus)

/*
 * Enum was not chosen because its size is uncontrollable, and it is not
 * treated as being a separate type.  Empty enums are not permitted.
 *
 * Struct was not chosen because it cannot be directly evaluated in
 * conditional statements.
 *
 * Contributor note: Treat bool as a special type that cannot have template
 * specializations.  Many problems could be solved without needing to treat
 * bool as a special type (e.g. set instead of map with bool value)
 */

typedef unsigned char bool;

#define false 0
#define true 1

#endif

/*
 * If none of the cases matched, then the language is C++, which makes bool a
 * keyword.  stdbool.h is deprecated in C++.  cstdbool is removed in C++20.
 */

#endif /* CPPBC_STDBOOL_H_ */
