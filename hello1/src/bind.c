
#include "libHello1.h"

char hellofunc_docs[] = "Hello world description.";
char heymanfunc_docs[] = "Echo your name and passed number.";
char addfunc_docs[] = "Add two numbers function.";
char createUser_docs[] = "Create new user c Object";

PyMethodDef helloworld_funcs[] = {{"hello", (PyCFunction)hello, METH_NOARGS, hellofunc_docs},
                                  {"heyman", (PyCFunction)heyman, METH_VARARGS, heymanfunc_docs},
                                  {"add", (PyCFunction)add, METH_VARARGS, addfunc_docs},
                                  {"createUser", (PyCFunction)createUser, METH_VARARGS, createUser_docs},
                                  {NULL}};

char helloworldmod_docs[] = "This is hello world module.";

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