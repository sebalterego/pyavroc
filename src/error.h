/*
 * Copyright 2015 Byhiras (Europe) Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef INC_ERROR_H
#define INC_ERROR_H

#define NULL_ON_ERROR(V)                                    \
    if (V) {                                                \
        PyErr_Format(PyExc_IOError, "%s", avro_strerror()); \
        return NULL;                                        \
    }

void set_error_prefix(const char *format, ...);

int set_avro_error(int rval);

int set_type_error(int rval, const PyObject *pyobj);

#endif
