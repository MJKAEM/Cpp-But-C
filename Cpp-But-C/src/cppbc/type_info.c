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

#include "../../include/cppbc/typeinfo.h"

#include <string.h>

#include "../../include/cppbc/new.h"
#include "../../include/cppbc/stdbool.h"

/**
 * Static declarations
 */

static void cppbc__type_info__impl__delete(
    struct cppbc__type_info *this_
);

static void cppbc__type_info__impl__delete_c_array(
    struct cppbc__type_info *c_array
);

/**
 * Implementation of statics
 */

static void cppbc__type_info__impl__delete(
    struct cppbc__type_info *this_
) {
  cppbc__type_info__destruct(this_);
  cppbc__delete((void*) this_);
}

static void cppbc__type_info__impl__delete_c_array(
    struct cppbc__type_info *c_array
) {
  size_t i;
  size_t element_count;

  /* Call the destructor on all elements in the array. */
  element_count = cppbc__get_c_array_element_count((void*) c_array);

  for (i = 0; i < element_count; i += 1) {
    struct cppbc__type_info* element_ptr =
        &((struct cppbc__type_info*) c_array)[i];
    cppbc__type_info__destruct(element_ptr);
  }

  cppbc__delete_c_array((void*) c_array);
}

/**
 * Public API
 */

const struct cppbc__type_info*
cppbc__type_info__get_type_info_vtable_type_info(void) {
  static struct cppbc__type_info type_info;
  static cppbc__bool is_init = CPPBC_FALSE;

  if (!is_init) {
    type_info.vtable = cppbc__type_info__get_type_info_vtable();
    type_info.name = "cppbc__type_info";

    is_init = CPPBC_TRUE;
  }

  return &type_info;
}

const struct cppbc__type_info_vtable*
cppbc__type_info__get_type_info_vtable(void) {
  static struct cppbc__type_info_vtable vtable;
  static cppbc__bool is_init = CPPBC_FALSE;

  if (!is_init) {
    /*
     * Special vtable case to prevent infinite loop when getting the type_info
     * of type_info.
     */
    is_init = CPPBC_TRUE;

    vtable.type_info = cppbc__type_info__get_type_info_vtable_type_info();
    vtable.delete_ = &cppbc__type_info__impl__delete;
    vtable.delete_c_array = &cppbc__type_info__impl__delete_c_array;
  }

  return &vtable;
}

void cppbc__type_info__destruct(
    struct cppbc__type_info *this_
) {
}

void cppbc__type_info__delete(
    struct cppbc__type_info *this_
) {
  this_->vtable->delete_(this_);
}

void cppbc__type_info__delete_c_array(
    struct cppbc__type_info *c_array
) {
  c_array->vtable->delete_c_array(c_array);
}

cppbc__bool cppbc__type_info__before(
    const struct cppbc__type_info *this_
);

cppbc__bool cppbc__type_info__equals(
    const struct cppbc__type_info *lhs,
    const struct cppbc__type_info *rhs
) {
  int difference;

  difference = memcmp(
      (const void*) lhs,
      (const void*) rhs,
      sizeof(*lhs)
  );

  return (difference == 0);
}

size_t cppbc__type_info__hash_code(
    const struct cppbc__type_info *this_
);

const char* cppbc__type_info__name(
    const struct cppbc__type_info *this_
) {
  return this_->name;
}
