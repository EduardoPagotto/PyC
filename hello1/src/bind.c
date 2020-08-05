#include "libHello1.h"

void dealloc_User(UserObject* User) {
#if TRACE
    printf("dealloc User, thread %d\n", GetCurrentThreadId());
#endif
    // kill_User(User, TRUE);
    PyObject_Del(User);
}

int handlername2int(PyObject* name) {
    int i;
    for (i = 0; User_methods[i].ml_name != NULL; i++) {
        if (PyUnicode_CompareWithASCIIString(name, User_methods[i].ml_name) == 0) {
            return i;
        }
    }
    return -1;
}

PyObject* User_getattro(UserObject* self, PyObject* nameObj) {

    if (!PyUnicode_Check(nameObj))
        return PyObject_GenericGetAttr((PyObject*)self, nameObj);

    int handlernum = handlername2int(nameObj);
    if (handlernum != -1) {
        return PyCFunction_New(&User_methods[handlernum], (PyObject*)self); // FIXME: Verificar se memory-leak
    }

    // if (!PyArg_ParseTuple(nameObj, "s", &teste))
    //     return NULL;

    // Py_ssize_t size;
    // const char* ptr = PyUnicode_AsUTF8AndSize(nameObj, &size);
    // if (size > 0) {
    //     if (PyUnicode_CompareWithASCIIString(nameObj, (const char*)"val1") == 0) {
    //         return Py_BuildValue("i", self->val1);
    //     }
    // }

    return NULL;
}

// PyObject* User_getattr(UserObject* self, char* name) { // char* name

//     int handlernum = -1;
//     PyObject* nameObj = PyUnicode_FromString(name);

//     // if (!PyUnicode_Check(nameObj))
//     //     return PyObject_GenericGetAttr((PyObject*)self, nameObj);

//     handlernum = handlername2int(nameObj);
//     if (handlernum != -1) {
//         return PyCFunction_New(&User_methods[handlernum], (PyObject*)self); // FIXME: Verificar se memory-leak
//     }

//     Py_ssize_t size;
//     // const char* ptr = PyUnicode_AsUTF8AndSize(nameObj, &size);
//     // if (size > 0) {
//     if (strcmp(name, (const char*)"val1") == 0) {
//         return Py_BuildValue("i", self->val1);
//     }
//     // }
//     return NULL;
// }

PyModuleDef helloworld_mod = {PyModuleDef_HEAD_INIT, "helloworld", helloworldmod_docs, -1, helloworld_funcs, NULL, NULL, NULL, NULL};

PyMODINIT_FUNC PyInit_helloworld(void) {

    PyObject* m = PyModule_Create(&helloworld_mod);

    if (m == NULL)
        return NULL;

    PyObject* d = PyModule_GetDict(m);

    execCreateUserFailed = PyErr_NewException("helloworld.execCreateUserFailed", NULL, NULL);
    PyDict_SetItemString(d, "execCreateUserFailed", execCreateUserFailed);

    return m;
}