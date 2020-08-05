#ifndef __LIBMYPY_H__
#define __LIBMYPY_H__

#include <Python.h>

/**
 * @brief UserObject Tipo definido
 *
 */
typedef struct {
    PyObject_HEAD int id;
    // PyObject_HEAD TW_IDENTITY appID; // storage for App states
    // SourceManagerObject* pSM;        // all comms are through SM
    // int bEnabled;                    // Flag to indicate source is enabled
    // TW_USERINTERFACE twUI;           // User info status (set during BeginAcquire)
    // char szUnused[4096];
    int val1;
    int val2;
    char buffer[255];
} UserObject, *pUserObject;

// /**
//  * @brief Metodos de acesso ao UserObject Tipo versao Antiga
//  *
//  * @param self
//  * @param name
//  * @return PyObject*
//  */
// PyObject* User_getattr(UserObject* self, char* name);

/**
 * @brief Metodos de acesso ao UserObject Tipo
 *
 * @param self
 * @param attr
 * @return PyObject*
 */
PyObject* User_getattro(UserObject* self, PyObject* attr);

/**
 * @brief memory clean
 *
 * @param User
 */
void dealloc_User(UserObject* User);

/**
 * @brief Definiciao dos metodos padrao e chamadas do UserObject tipo
 *
 */
static PyTypeObject UserType = {
    PyVarObject_HEAD_INIT(NULL, 0) "User", /* tp_name */
    sizeof(UserObject),                    /* tp_basicsize */
    0,                                     /* tp_itemsize */
    (destructor)dealloc_User,              /* tp_dealloc */
    0,                                     /* tp_print */
    0,                                     /* tp_getattr (getattrfunc)User_getattr,*/
    0,                                     /* tp_setattr */
    0,                                     /* tp_reserved */
    0,                                     /* tp_repr */
    0,                                     /* tp_as_number */
    0,                                     /* tp_as_sequence */
    0,                                     /* tp_as_mapping */
    0,                                     /* tp_hash  */
    0,                                     /* tp_call */
    0,                                     /* tp_str */
    (getattrofunc)User_getattro,           /* tp_getattro */
    0,                                     /* tp_setattro */
    0,                                     /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                    /* tp_flags */
    "User objects",                        /* tp_doc */
};

static char User_inicialize_doc[] = "Inicializacao usuario";
static char User_finalize_doc[] = "Finalizacao usuario";

/**
 * @brief Inicializa dados
 *
 * @param self
 * @param args
 * @return PyObject*
 */
PyObject* User_inicialize(UserObject* self, PyObject* args);

/**
 * @brief Finaliza dados
 *
 * @param self
 * @param args
 * @return PyObject*
 */
PyObject* User_finalize(UserObject* self, PyObject* args);

static PyMethodDef User_methods[] = {{"inicialize", (PyCFunction)User_inicialize, METH_VARARGS, User_inicialize_doc},
                                     {"finalize", (PyCFunction)User_finalize, METH_VARARGS, User_finalize_doc},
                                     {NULL}};

// Metodos chamados diretamente na api
static char hellofunc_docs[] = "Hello world description.";
static char heymanfunc_docs[] = "Echo your name and passed number.";
static char addfunc_docs[] = "Add two numbers function.";
static char createUser_docs[] = "Create new user c Object";

/**
 * @brief Mansagem de Hello
 *
 * @return PyObject*
 */
PyObject* hello(PyObject*);

/**
 * @brief reponde preenchando dados
 *
 * @return PyObject*
 */
PyObject* heyman(PyObject*, PyObject*);

/**
 * @brief soma e retorna
 *
 * @return PyObject*
 */
PyObject* add(PyObject*, PyObject*);

/**
 * @brief Create a User object Tipo
 *
 * @param self
 * @param args
 * @return PyObject*
 */
PyObject* createUser(PyObject* self, PyObject* args);

static PyMethodDef helloworld_funcs[] = {{"hello", (PyCFunction)hello, METH_NOARGS, hellofunc_docs},
                                         {"heyman", (PyCFunction)heyman, METH_VARARGS, heymanfunc_docs},
                                         {"add", (PyCFunction)add, METH_VARARGS, addfunc_docs},
                                         {"createUser", (PyCFunction)createUser, METH_VARARGS, createUser_docs},
                                         {NULL}};

static char helloworldmod_docs[] = "This is hello world module.";

// Exceptions
static PyObject* execCreateUserFailed;

#endif