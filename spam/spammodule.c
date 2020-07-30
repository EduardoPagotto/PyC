#define PY_SSIZE_T_CLEAN
#define SPAM_MODULE

#include <Python.h>

#include "spammodule.h"

// ref: https://docs.python.org/3/extending/extending.html,
// https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code

// funçao a ser chamada do python
static PyObject* spam_system(PyObject* self, PyObject* args) {

    char* command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return Py_BuildValue("i", sts);
}

// Lista de metodos a serem disponibilizados no python
static PyMethodDef SpamMethods[] = {
    //...
    {"system", spam_system, METH_VARARGS, "Execute a shell command."},
    //...
    {NULL, NULL, 0, NULL} /* Sentinel */
};

// definicoes do modulo
static struct PyModuleDef spammodule = {PyModuleDef_HEAD_INIT, "spam", /* name of module */
                                        NULL,                          /* module documentation, may be NULL era spam_doc,  */
                                        -1,                            /* size of per-interpreter state of the module,
                                                                          or -1 if the module keeps state in global variables. */
                                        SpamMethods};

// inicializador do metodo
PyMODINIT_FUNC PyInit_spam(void) {
    PyObject* m;
    static void* PySpam_API[PySpam_API_pointers];
    PyObject* c_api_object;

    m = PyModule_Create(&spammodule);
    if (m == NULL)
        return NULL;

    /* Initialize the C API pointer array */
    PySpam_API[PySpam_System_NUM] = (void*)PySpam_System;

    /* Create a Capsule containing the API pointer array's address */
    c_api_object = PyCapsule_New((void*)PySpam_API, "spam._C_API", NULL);

    if (PyModule_AddObject(m, "_C_API", c_api_object) < 0) {
        Py_XDECREF(c_api_object);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

// carregamento do PyInit_spam pelo PyImport_AppendInittab
int main(int argc, char* argv[]) {
    wchar_t* program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    if (PyImport_AppendInittab("spam", PyInit_spam) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required.
       If this step fails, it will be a fatal error. */
    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    PyObject* pmodule = PyImport_ImportModule("spam");
    if (!pmodule) {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module 'spam'\n");
    }

    PyMem_RawFree(program);
    return 0;
}