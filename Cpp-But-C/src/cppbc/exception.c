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

#include "../../include/cppbc/stdexcept.h"

#include <stdlib.h>
#include "../../include/cppbc/stdbool.h"

/**
 * Static declarations
 */

static void cppbc__exception__impl__delete(
    struct cppbc__exception *this_
);

static const char* cppbc__exception__impl__what(
    struct cppbc__exception *this_
);

/**
 * Implementation of statics
 */

static void cppbc__exception__impl__delete(
    struct cppbc__exception *this_
) {
  cppbc__exception__destruct(this_);
  free(this_);
}

static const char* cppbc__exception__impl__what(
    struct cppbc__exception *this_
) {
  return "cppbc__exception";
}

/**
 * Public API
 */

const struct cppbc__exception_vtable*
cppbc__exception__get_exception_vtable(void) {
  static struct cppbc__exception_vtable exception_vtable;
  static cppbc__bool is_init = cppbc__false;

  if (!is_init) {
    exception_vtable.delete_ = &cppbc__exception__impl__delete;
    exception_vtable.what = &cppbc__exception__impl__what;

    is_init = cppbc__true;
  }

  return &exception_vtable;
}

struct cppbc__exception*
cppbc__exception__construct_default(
    struct cppbc__exception *this_
) {
  this_->__vtable = &cppbc__exception__get_exception_vtable;
}

struct cppbc__exception*
cppbc__exception__construct_copy(
    struct cppbc__exception *this_,
    const struct cppbc__exception *src
) {
  this_->__vtable = &cppbc__exception__get_exception_vtable;
}

void cppbc__exception__destruct(
    struct cppbc__exception *this_
) {
  /* Nothing to destruct! */
}

void cppbc__exception__delete(
    struct cppbc__exception *this_
) {
  if (this_ != NULL) {
    this_->__vtable->delete_(this_);
  }
}

const char* cppbc__exception__what(
    const struct cppbc__exception *this_
) {
  return this_->__vtable->what(this_);
}
