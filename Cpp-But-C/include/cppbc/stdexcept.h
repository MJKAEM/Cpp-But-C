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

#ifndef CPPBC_STDEXCEPT_H_
#define CPPBC_STDEXCEPT_H_

/**
 * Forward declarations
 */

struct cppbc__exception;
struct cppbc__exception_vtable;

/**
 * cppbc__exception
 */

struct cppbc__exception {
  const struct cppbc__exception_vtable *__vtable;
};

struct cppbc__exception_vtable {
  void* type_info; /* TODO (Martino Kuan): Reserved for future implementation. */

  void (*delete_)(
      struct cppbc__exception*
  );

  void (*delete_c_array)(
      struct cppbc__exception*
  );

  const char* (*what)(
      const struct cppbc__exception*
  );
};

/**
 * cppbc__exception functions
 */

const struct cppbc__exception_vtable*
cppbc__exception__get_exception_vtable(void);

struct cppbc__exception*
cppbc__exception__construct_default(
    struct cppbc__exception *this_
);

struct cppbc__exception*
cppbc__exception__new_default(
    void
);

struct cppbc__exception*
cppbc__exception__construct_copy(
    struct cppbc__exception *this_,
    const struct cppbc__exception *src
);

struct cppbc__exception*
cppbc__exception__new_copy(
    const struct cppbc__exception *src
);

void cppbc__exception__destruct(
    struct cppbc__exception *this_
);

void cppbc__exception__delete(
    struct cppbc__exception *this_
);

void cppbc__exception__delete_c_array(
    struct cppbc__exception *c_array
);

const char* cppbc__exception__what(
    const struct cppbc__exception* this_
);

#endif // CPPBC_STDEXCEPT_H_
