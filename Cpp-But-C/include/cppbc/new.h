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
  struct cppbc__bad_alloc_vtable *__vtable;
};

struct cppbc__bad_alloc_vtable {
  struct cppbc__exception_vtable exception_vtable;
};

#endif /* CPPBC_NEW_H_ */
