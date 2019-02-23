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

/*
 * The bool type is required by the public API and the internal implementation
 * in order to function correctly.  In order to get around potential naming
 * conflicts, cppbc__ is prefixed to the names, but may be aliased without the
 * prefix if desired.  Define CPPBC_ENABLE_BOOL_ALIAS to enable these aliases.
 */

/*
 * Enum was not chosen because its size is uncontrollable, and it is not
 * treated as being a separate type.  Empty enums are not permitted.
 *
 * Struct was not chosen because it cannot be directly evaluated in
 * conditional statements.
 *
 * Contributor note: Treat bool as a special type that cannot have template
 * specializations.  Many problems could be solved without needing to treat
 * bool as a special type (e.g. set instead of map with bool value).
 */

typedef unsigned char cppbc__bool;

#define CPPBC_FALSE 0
#define CPPBC_TRUE 1

#if defined(CPPBC_ENABLE_BOOL_ALIAS)

#if /* Using C and not C++. */ \
    !defined(__cplusplus)

typedef cppbc__bool bool;

#define false CPPBC_FALSE
#define true CPPBC_TRUE

#endif

#endif /* defined(CPPBC_ENABLE_BOOL_ALIAS) */

#endif /* CPPBC_STDBOOL_H_ */
