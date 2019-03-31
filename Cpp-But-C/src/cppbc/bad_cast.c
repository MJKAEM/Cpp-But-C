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

#include <stddef.h>

#include "../../include/cppbc/new.h"
#include "../../include/cppbc/stdexcept.h"

/**
 * Declaration of statics
 */

static void cppbc__bad_cast__impl__delete(
    struct cppbc__bad_cast *this_
);

static void cppbc__bad_cast__impl__delete_c_array(
    struct cppbc__bad_cast *c_array
);

static const char* cppbc__bad_cast__impl__what(
    const struct cppbc__bad_cast *this_
);

/**
 * Definition of statics
 */

static void cppbc__bad_cast__impl__delete(
    struct cppbc__bad_cast *this_
) {
  cppbc__bad_cast__destruct(this_);
  cppbc__delete((void*) this_);
}

static void cppbc__bad_cast__impl__delete_c_array(
    struct cppbc__bad_cast *c_array
) {
  size_t i;
  size_t element_count;

  /* Call the destructor on all elements in the array. */
  element_count = cppbc__get_c_array_element_count((void*) c_array);

  for (i = 0; i < element_count; i += 1) {
    struct cppbc__bad_cast* element_ptr = &c_array[i];
    cppbc__bad_cast__destruct(element_ptr);
  }

  cppbc__delete_c_array((void*) c_array);
}

static const char* cppbc__bad_cast__impl__what(
    const struct cppbc__bad_cast *this_
) {
  return "cppbc__bad_cast";
}

/**
 * Public API
 */

const struct cppbc__bad_cast_vtable*
cppbc__bad_cast__get_bad_cast_vtable(void) {
  static struct cppbc__bad_cast_vtable bad_cast_vtable;
  static cppbc__bool is_init = CPPBC_FALSE;

  if (!is_init) {
    bad_cast_vtable.type_info =
        cppbc__bad_cast__get_bad_cast_vtable_type_info();

    bad_cast_vtable.delete_ = &cppbc__bad_cast__impl__delete;
    bad_cast_vtable.delete_c_array = &cppbc__bad_cast__impl__delete_c_array;
    bad_cast_vtable.what = &cppbc__bad_cast__impl__what;

    is_init = CPPBC_TRUE;
  }

  return &bad_cast_vtable;
}

const struct cppbc__type_info*
cppbc__bad_cast__get_bad_cast_vtable_type_info(void) {
  static struct cppbc__type_info type_info;
  static cppbc__bool is_init = CPPBC_FALSE;

  if (!is_init) {
    type_info.vtable = cppbc__type_info__get_type_info_vtable();
    type_info.name = "cppbc__bad_cast";

    is_init = CPPBC_TRUE;
  }

  return &type_info;
}

struct cppbc__bad_cast*
cppbc__bad_cast__construct_default(
    struct cppbc__bad_cast *this_
) {
  this_->vtable = cppbc__bad_cast__get_bad_cast_vtable();

  return this_;
}

void cppbc__bad_cast__destruct(
    struct cppbc__bad_cast *this_
) {
  cppbc__exception__destruct((struct cppbc__exception*) this_);
}

void cppbc__bad_cast__delete(
    struct cppbc__bad_cast *this_
) {
  this_->vtable->delete_(this_);
}

void cppbc__bad_cast__delete_c_array(
    struct cppbc__bad_cast *c_array
) {
  c_array->vtable->delete_c_array(c_array);
}

const char* cppbc__bad_cast__what(
    const struct cppbc__bad_cast *this_
) {
  return this_->vtable->what(this_);
}
