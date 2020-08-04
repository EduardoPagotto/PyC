#ifndef __LIBMYPY_H__
#define __LIBMYPY_H__

#include <Python.h>

// Exceptions
static PyObject* execCreateUserFailed;

typedef struct {
    // PyObject_HEAD TW_IDENTITY appID; // storage for App states
    // SourceManagerObject* pSM;        // all comms are through SM
    // int bEnabled;                    // Flag to indicate source is enabled
    // TW_USERINTERFACE twUI;           // User info status (set during BeginAcquire)
    // char szUnused[4096];
    int val1;
    int val2;
    char buffer[10];
} UserObject, *pUserObject;

PyObject* User_getattr(UserObject* self, char* name);
void dealloc_User(UserObject* User);

static PyTypeObject UserType = {
    PyVarObject_HEAD_INIT(NULL, 0) "User", /* tp_name */
    sizeof(UserObject),                    /* tp_basicsize */
    0,                                     /* tp_itemsize */
    (destructor)dealloc_User,              /* tp_dealloc */
    0,                                     /* tp_print */
    (getattrfunc)User_getattr,             /* tp_getattr */
    0,                                     /* tp_setattr */
    0,                                     /* tp_reserved */
    0,                                     /* tp_repr */
    0,                                     /* tp_as_number */
    0,                                     /* tp_as_sequence */
    0,                                     /* tp_as_mapping */
    0,                                     /* tp_hash  */
    0,                                     /* tp_call */
    0,                                     /* tp_str */
    0,                                     /* tp_getattro */
    0,                                     /* tp_setattro */
    0,                                     /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                    /* tp_flags */
    "User objects",                        /* tp_doc */
};

PyObject* User_inicialize(PyObject* self, PyObject* args);
PyObject* User_finalize(PyObject* self, PyObject* args);

PyObject* hello(PyObject*);
PyObject* heyman(PyObject*, PyObject*);
PyObject* add(PyObject*, PyObject*);

PyObject* createUser(PyObject* self, PyObject* args);

#endif