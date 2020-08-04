
#include "libHello1.h"
#include <Python.h>
#include <stdio.h>

PyObject* User_getattr(UserObject* self, char* name) {
    // return Py_FindMethod(User_methods, (PyObject*)self, name); // TODO: implementado aqui!!!!
    return PyObject_GenericGetAttr((PyObject*)self, PyUnicode_FromString(name));
}

void dealloc_User(UserObject* User) {
#if TRACE
    printf("dealloc User, thread %d\n", GetCurrentThreadId());
#endif
    // kill_User(User, TRUE);
    PyObject_Del(User);
}

PyObject* User_inicialize(PyObject* self, PyObject* args) { return NULL; }

PyObject* User_finalize(PyObject* self, PyObject* args) { return NULL; }

PyObject* hello(PyObject* self) { return PyUnicode_FromFormat("Hello C extension!"); }

PyObject* createUser(PyObject* self, PyObject* args) {

    UserObject* User;

    int pyErr = 0;
    char szMessage[255];

    User = PyObject_New(UserObject, &UserType);

    if (pyErr != 0) {
        // Problem Opening the Source - Raise an Exception
        sprintf(szMessage, "return code %d", 9);
        PyErr_SetString(execCreateUserFailed, szMessage);
        return NULL;
    }

    return (PyObject*)User;
}

PyObject* heyman(PyObject* self, PyObject* args) {
    int num;
    char* name;

    if (!PyArg_ParseTuple(args, "is", &num, &name))
        return NULL;

    return PyUnicode_FromFormat("Hay %s!  You gave me %d.", name, num);
}

PyObject* add(PyObject* self, PyObject* args) {
    int num1, num2;
    char eq[20];

    if (!PyArg_ParseTuple(args, "ii", &num1, &num2))
        return NULL;

    sprintf(eq, "%d + %d", num1, num2);

    return Py_BuildValue("is", num1 + num2, eq);
}