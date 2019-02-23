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

#include <stdlib.h>

void* cppbc__allocate(size_t size) {
  return malloc(size);
}

void* cppbc__allocate_c_array(size_t element_count, size_t element_size) {
  size_t total_size;
  struct cppbc__c_array_metadata *metadata;

  /*
   * Determine the size of the array and allocate space for the array and
   * metadata.
   */
  total_size = (element_count * element_size)
      + sizeof(*metadata);

  metadata = (struct cppbc__c_array_metadata*) malloc(total_size);
  metadata->element_count = element_count;

  return &metadata[1];
}

void cppbc__deallocate(void *ptr) {
  free(ptr);
}

void cppbc__deallocate_c_array(void* c_array) {
  struct cppbc__c_array_metadata *metadata;

  /* The allocated memory chunk begins at metadata. */
  metadata = &((struct cppbc__c_array_metadata*) c_array)[-1];
  free(metadata);
}

size_t cppbc__get_c_array_element_count(void *c_array) {
  struct cppbc__c_array_metadata *metadata;
  size_t element_count;

  /* Retrieve the element count. */
  metadata = &((struct cppbc__c_array_metadata*) c_array)[-1];
  element_count = metadata->element_count;

  return element_count;
}
