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

#ifndef CPPBC_NEW_H_
#define CPPBC_NEW_H_

#include <stddef.h>
#include "stdexcept.h"

/**
 * Forward declarations
 */

struct cppbc__bad_alloc;
struct cppbc__bad_alloc_vtable;

struct cppbc__c_array_metadata;

/**
 * cppbc__c_array_metadata
 */

struct cppbc__c_array_metadata {
  size_t element_count;
};

/**
 * Functions
 */

void* cppbc__allocate(size_t size);

void* cppbc__allocate_c_array(size_t element_count, size_t element_size);

void cppbc__deallocate(void *ptr);

void cppbc__deallocate_c_array(void *c_array);

size_t cppbc__get_c_array_element_count(void *c_array);

/**
 * cppbc__bad_alloc
 */

struct cppbc__bad_alloc {
  union {
    struct cppbc__bad_alloc_vtable *__bad_alloc_vtable;
    struct cppbc__exception_vtable *__exception_vtable;
  };
};

struct cppbc__bad_alloc_vtable {
  void* type_info; /* TODO (Martino Kuan): Reserved for future implementation. */

  void (*delete_)(
      struct cppbc__bad_alloc*
  );

  void (*delete_c_array)(
      struct cppbc__bad_alloc*
  );

  const char* (*what)(
      const struct cppbc__bad_alloc*
  );
};

const struct cppbc__exception_vtable*
cppbc__bad_alloc__get_exception_vtable(void);

struct cppbc__bad_alloc*
cppbc__bad_alloc__construct_default(
    struct cppbc__bad_alloc *this_
);

struct cppbc__bad_alloc*
cppbc__bad_alloc__new_default(void);

struct cppbc__bad_alloc*
cppbc__bad_alloc__new_c_array(
    size_t element_count
);

struct cppbc__bad_alloc*
cppbc__bad_alloc__construct_copy(
    struct cppbc__bad_alloc *this_,
    const struct cppbc__bad_alloc *src
);

struct cppbc__bad_alloc*
cppbc__bad_alloc__new_copy(
    const struct cppbc__bad_alloc *src
);

void cppbc__bad_alloc__destruct(
    struct cppbc__bad_alloc *this_
);

void cppbc__bad_alloc__delete(
    struct cppbc__bad_alloc *this_
);

void cppbc__bad_alloc__delete_c_array(
    struct cppbc__bad_alloc *c_array
);

struct cppbc__bad_alloc*
cppbc__exception__downcast_to__cppbc__bad_alloc(
    struct cppbc__exception *this_
);

struct cppbc__exception*
cppbc__bad_alloc__upcast_to__cppbc__exception(
    struct cppbc__bad_alloc *this_
);

const char* cppbc__bad_alloc__what(
    const struct cppbc__bad_alloc *this_
);

#endif /* CPPBC_NEW_H_ */
