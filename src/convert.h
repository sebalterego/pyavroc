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

#ifndef INC_CONVERT_H
#define INC_CONVERT_H

#include "Python.h"
#include "avro.h"

typedef struct {
    PyObject *types;
} ConvertInfo;

/*
 * Check if the Python datum `pyobj` matches the given schema.  If it
 * doesn't, return -1; if it matches one of the n branches in a union
 * (or one of the n elements in an enum), return the corresponding index
 * (0 ... n-1); if it matches, but it's not a union or enum, return 0.
 */
int validate(PyObject *pyobj, avro_schema_t schema);

PyObject *avro_to_python(ConvertInfo *info, avro_value_t *);

int python_to_avro(ConvertInfo *info, PyObject *pyobj, avro_value_t *);

PyTypeObject *get_avro_types_type(void);

PyObject *declare_types(ConvertInfo *info, avro_schema_t schema);

#endif
