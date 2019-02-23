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

#include "../../include/cppbc/new.h"

#include <stddef.h>

#include "../../include/cppbc/stdbool.h"
#include "../../include/cppbc/stdexcept.h"

/**
 * Static declarations
 */

static void cppbc__bad_alloc__impl__delete(
    struct cppbc__bad_alloc *this_
);

static void cppbc__bad_alloc__impl__delete_c_array(
    struct cppbc__bad_alloc *c_array
);

static const char* cppbc__bad_alloc__impl__what(
    struct cppbc__bad_alloc *this_
);

/**
 * Implementation of statics
 */

static void cppbc__bad_alloc__impl__delete(
    struct cppbc__bad_alloc *this_
) {
  cppbc__bad_alloc__destruct(this_);
  cppbc__deallocate(this_);
}

static void cppbc__bad_alloc__impl__delete_c_array(
    struct cppbc__bad_alloc *c_array
) {
  size_t i;
  size_t element_count;

  element_count = cppbc__get_c_array_element_count((void*) c_array);

  for (i = 0; i < element_count; i += 1) {
    cppbc__bad_alloc__destruct(&c_array[i]);
  }

  cppbc__deallocate_c_array((void*) c_array);
}

static const char* cppbc__bad_alloc__impl__what(
    struct cppbc__bad_alloc *this_
) {
  return "cppbc__bad_alloc";
}

/**
 * Public API
 */

const struct cppbc__exception_vtable*
cppbc__bad_alloc__get_exception_vtable(void) {
  static struct cppbc__exception_vtable exception_vtable;
  static cppbc__bool is_init = CPPBC_FALSE;

  if (!is_init) {
    exception_vtable.delete_ = (void(*)(struct cppbc__exception*))
        &cppbc__bad_alloc__impl__delete;
    exception_vtable.delete_c_array = (void(*)(struct cppbc__exception*))
        &cppbc__bad_alloc__impl__delete_c_array;
    exception_vtable.what = (const char*(*)(const struct cppbc__exception*))
        &cppbc__bad_alloc__impl__what;

    is_init = CPPBC_TRUE;
  }

  return &exception_vtable;
}

struct cppbc__bad_alloc*
cppbc__bad_alloc__construct_default(
    struct cppbc__bad_alloc *this_
) {
  struct cppbc__exception *exception;

  exception = (struct cppbc__exception*) &this_->__exception_vtable;
  cppbc__exception__construct_default(exception);

  exception->__vtable =
      cppbc__bad_alloc__get_exception_vtable();

  return this_;
}

struct cppbc__bad_alloc*
cppbc__bad_alloc__new_default(void) {
  struct cppbc__bad_alloc *this_ = cppbc__allocate(sizeof(*this_));
  cppbc__bad_alloc__construct_default(this_);

  return this_;
}

struct cppbc__bad_alloc*
cppbc__bad_alloc__new_c_array(
    size_t element_count
) {
  size_t i;
  struct cppbc__bad_alloc *c_array;

  c_array = cppbc__allocate_c_array(element_count, sizeof(*c_array));

  for (i = 0; i < element_count; i += 1) {
    cppbc__bad_alloc__construct_default(&c_array[i]);
  }

  return c_array;
}

struct cppbc__bad_alloc*
cppbc__bad_alloc__construct_copy(
    struct cppbc__bad_alloc *this_,
    const struct cppbc__bad_alloc *src
) {
  struct cppbc__exception *this_as_exception;
  struct cppbc__exception *src_as_exception;
  this_as_exception = (struct cppbc__exception*) &this_->__exception_vtable;
  src_as_exception = (struct cppbc__exception*) &src->__exception_vtable;
  cppbc__exception__construct_copy(this_as_exception, src_as_exception);

  this_as_exception->__vtable =
      cppbc__bad_alloc__get_exception_vtable();

  return this_;
}

struct cppbc__bad_alloc*
cppbc__bad_alloc__new_copy(
    const struct cppbc__bad_alloc *src
) {
  struct cppbc__bad_alloc *this_ = cppbc__allocate(sizeof(*this_));
  cppbc__bad_alloc__construct_copy(this_, src);

  return this_;
}

void cppbc__bad_alloc__destruct(
    struct cppbc__bad_alloc *this_
) {
  /* Nothing to destruct! */

  struct cppbc__exception *exception;
  exception = (struct cppbc__exception*) &this_->__exception_vtable;
  cppbc__exception__destruct(exception);
}

void cppbc__bad_alloc__delete(
    struct cppbc__bad_alloc *this_
) {
  if (this_ != NULL) {
    this_->__bad_alloc_vtable->delete_(this_);
  }
}

void cppbc__bad_alloc__delete_c_array(
    struct cppbc__bad_alloc *c_array
) {
  if (c_array != NULL) {
    c_array->__bad_alloc_vtable->delete_c_array(c_array);
  }
}

struct cppbc__bad_alloc*
cppbc__exception__downcast_to__cppbc__bad_alloc(
    struct cppbc__exception *this_
) {
  return (struct cppbc__bad_alloc*) this_;
}

struct cppbc__exception*
cppbc__bad_alloc__upcast_to__cppbc__exception(
    struct cppbc__bad_alloc *this_
) {
  return (struct cppbc__exception*) &this_->__exception_vtable;
}

const char* cppbc__bad_alloc__what(
    const struct cppbc__bad_alloc* this_
) {
  return this_->__bad_alloc_vtable->what(this_);
}
