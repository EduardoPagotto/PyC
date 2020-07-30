
#include "libHello1.h"
#include <Python.h>

PyObject* hello(PyObject* self) { return PyUnicode_FromFormat("Hello C extension!"); }