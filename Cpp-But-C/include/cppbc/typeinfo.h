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

#ifndef CPPBC_TYPEINFO_H_
#define CPPBC_TYPEINFO_H_

#include <stddef.h>

#include "stdbool.h"

/**
 * Forward declarations
 */

struct cppbc__type_info;
struct cppbc__type_info_vtable;

/**
 * cppbc__type_info
 */

struct cppbc__type_info {
  struct cppbc__type_info_vtable *vtable;
  const char* name;
};

struct cppbc__type_info_vtable {
  const struct cppbc__type_info *type_info;

  void (*delete_)(struct cppbc__type_info*);
  void (*delete_c_array)(struct cppbc__type_info*);
};

const struct cppbc__type_info*
cppbc__type_info__get_type_info_vtable_type_info(void);

const struct cppbc__type_info_vtable*
cppbc__type_info__get_type_info_vtable(void);

void cppbc__type_info__destruct(
    struct cppbc__type_info *this_
);

void cppbc__type_info__delete(
    struct cppbc__type_info *this_
);

void cppbc__type_info__delete_c_array(
    struct cppbc__type_info *c_array
);

cppbc__bool cppbc__type_info__before(
    const struct cppbc__type_info *this_
);

cppbc__bool cppbc__type_info__equals(
    const struct cppbc__type_info *lhs,
    const struct cppbc__type_info *rhs
);

size_t cppbc__type_info__hash_code(
    const struct cppbc__type_info *this_
);

const char* cppbc__type_info__name(
    const struct cppbc__type_info *this_
);

#endif /* CPPBC_TYPEINFO_H_ */
