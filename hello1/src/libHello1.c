
#include "libHello1.h"
#include <Python.h>
#include <stdio.h>

int handlername2int(PyObject* name) {
    int i;
    for (i = 0; User_methods[i].ml_name != NULL; i++) {
        if (PyUnicode_CompareWithASCIIString(name, User_methods[i].ml_name) == 0) {
            return i;
        }
    }
    return -1;
}

PyObject* User_getattr(UserObject* self, PyObject* nameObj) {
    // return Py_FindMethod(User_methods, (PyObject*)self, name); // TODO: implementado aqui!!!!

    // Py_UNICODE* name;
    int handlernum = -1;

    // if (!PyUnicode_Check(nameObj))
    //     return PyObject_GenericGetAttr((PyObject*)self, nameObj);

    handlernum = handlername2int(nameObj);

    if (handlernum != -1) {
        PyCFunction funcExec = User_methods[handlernum].ml_meth;

        PyObject* result = (PyObject*)funcExec;
        Py_INCREF(result);
        return result;
    }

    Py_ssize_t size;
    const char* ptr = PyUnicode_AsUTF8AndSize(nameObj, &size);
    if (size > 0) {
        if (strcmp(ptr, (const char*)"val1") == 0) {
            return Py_BuildValue("i", self->val1);
        }
    }
    return NULL;
}

void dealloc_User(UserObject* User) {
#if TRACE
    printf("dealloc User, thread %d\n", GetCurrentThreadId());
#endif
    // kill_User(User, TRUE);
    PyObject_Del(User);
}

PyObject* User_inicialize(UserObject* self, PyObject* args) {

    int val1_in;
    int val2_in;

    if (self == NULL)
        return Py_BuildValue("i", -11);

    if (!PyArg_ParseTuple(args, "ii", &val1_in, &val1_in))
        return NULL;

    self->val1 = val1_in;
    self->val2 = val2_in;

    return Py_BuildValue("i", 56);
}

PyObject* User_finalize(UserObject* self, PyObject* args) { return NULL; }

PyObject* hello(PyObject* self) { return PyUnicode_FromFormat("Hello C extension!"); }

PyObject* createUser(PyObject* self, PyObject* args) {

    UserObject* User;

    int pyErr = 0;
    char szMessage[255];

    User = PyObject_New(UserObject, &UserType);

    // memset(User, 0, sizeof(UserObject));
    User->val1 = 202;
    User->val2 = 303;
    // sprintf(User->buffer, "Inicializado objeto: %d", 0);

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