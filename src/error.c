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

#include "Python.h"
#include "util.h"
#include "avro.h"

void
set_error_prefix(const char *format, ...)
{
    PyObject *type;  /* error type */
    PyObject *value;  /* error message */
    PyObject *traceback;  /* error traceback */
    PyObject *newmessage;

    va_list argp;
    va_start(argp, format);
#if PY_MAJOR_VERSION >= 3
    newmessage = PyUnicode_FromFormatV(format, argp);
#else
    newmessage = PyString_FromFormatV(format, argp);
#endif
    va_end(argp);

    if (!newmessage) {
        PyErr_Warn(PyExc_RuntimeWarning, "Failed to format exception message");
        newmessage = chars_to_pystring(format);
    }

    if (!PyErr_Occurred()) {
        PyErr_SetObject(PyExc_IOError, newmessage);
        Py_DECREF(newmessage);
        return;
    }

    PyErr_Fetch(&type, &value, &traceback);

    pystring_concat_str(&newmessage, value);

    PyErr_Restore(type, newmessage, traceback);  /* steals refs */
}

int
set_avro_error(int rval)
{
    if (rval != 0) {
        PyErr_Format(PyExc_IOError, "%s", avro_strerror());
    }
    return rval;
}

int
set_type_error(int rval, const PyObject *pyobj)
{
    PyObject* pyrepr;

    if (rval == 0) {
        return 0;
    }

    pyrepr = PyObject_Repr((PyObject*)pyobj);

    if (pyrepr != NULL) {
        PyObject *pybytes = pystring_to_pybytes(pyrepr);
        set_error_prefix("invalid python object %.100s, ", pybytes_to_chars(pybytes));
        Py_DECREF(pybytes);
        Py_DECREF(pyrepr);
    }  /* otherwise the error is already set, so leave it alone. */

    return rval;
}
