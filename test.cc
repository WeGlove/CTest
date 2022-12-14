/*
Check the C-API Reference for Info. It is a good source. https://docs.python.org/3/c-api/index.html
Should also make some Linter for the python functions.
*/


#include <Python.h>
#include <ndarrayobject.h>

// Function 1: A simple 'hello world' function
static PyObject* c_hello_world(PyObject* self, PyObject* args)
{
    printf("Hello World\n");
    return Py_None;
}

// Function 1: A simple 'hello world' function
static PyObject* c_print(PyObject* self, PyObject* args)
{
    PyObject* str_obj = PyTuple_GET_ITEM(args, 0);
    Py_ssize_t size = PyUnicode_GET_LENGTH(str_obj);
    wchar_t* arg_string = PyUnicode_AsWideCharString(str_obj, &size);
    size_t length = sizeof(arg_string)/sizeof(arg_string[0]);
    unsigned int kind = PyUnicode_KIND(str_obj);
    printf("Kind: %d\n", kind);
    printf("Charsize: %d\n", sizeof(arg_string[0]));
    printf("Length: %zu\n", length);



    switch (kind){
        case 1:
            Py_UCS1* str_1 = PyUnicode_1BYTE_DATA(str_obj);
            wprintf(str_1);
            break;
        case 2:
            Py_UCS2* str_2 = PyUnicode_2BYTE_DATA(str_obj);
            wprintf(str_2);
            break;
        case 3:
            Py_UCS4* str_4 = PyUnicode_4BYTE_DATA(str_obj);
            wprintf(str_4);
            break;
        default:
            return Py_None;
    }



    return Py_None;
}

static PyObject* arg_unpack(PyObject* self, PyObject* args)
{
    PyObject* obj_0 = PyTuple_GET_ITEM(args, 0);
    PyObject* obj_1 = PyTuple_GET_ITEM(args, 1);
    printf(PyUnicode_AS_DATA(obj_0));
    printf(PyUnicode_AS_DATA(obj_1));
    return Py_None;
}

static PyObject* print_int(PyObject* self, PyObject* args) // even if one argument is given it is interpreted as a tuple
{
    PyObject* pynum = PyTuple_GET_ITEM(args, 0);
    if (PyLong_Check(pynum)){
        long num = PyLong_AsLong(pynum);
        printf("%ld", num);
    } else {
        printf("Given Argument was not, or could not be converted to, a PyLong.");
    }

    return Py_None;
}

static PyObject* print_dec(PyObject* self, PyObject* args) // even if one argument is given it is interpreted as a tuple
{
    PyObject* pynum = PyTuple_GET_ITEM(args, 0);
    if (PyFloat_Check(pynum)){
        double num = PyFloat_AS_DOUBLE(pynum);
        printf("%f", num);
    } else {
        printf("Given Argument was not, or could not be converted to, a PyFloat.");
    }

    return Py_None;
}

static PyObject* access_ext_files(PyObject* self, PyObject* args)
{
    printf("%d", add(1,2));
    return Py_None;
}



// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// https://docs.python.org/3/c-api/structures.html#c.PyMethodDef
// Signatures is [{function_name}, actual function, , description]
static PyMethodDef myMethods[] = {
    { "c_print", c_print, METH_VARARGS, "Prints a string" },
    { "c_hello_world", c_hello_world, METH_NOARGS, "Prints Hello World" },
    { "arg_unpack", arg_unpack, METH_VARARGS, "Unpacks a tuple, prints both as strings." },
    { "print_int", print_int, METH_VARARGS, "Print a given number as a long." },
    { "print_dec", print_dec, METH_VARARGS, "Print a given number as a double." },
    { "access_ext_files", access_ext_files, METH_NOARGS, "Attempt tp access an external file" },
    { NULL, NULL, 0, NULL }
};

// Our Module Definition struct
static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "myModule",
    "Test Module",
    -1,
    myMethods
};

// Initializes our module using our above struct
PyMODINIT_FUNC PyInit_myModule(void)
{
    return PyModule_Create(&myModule);
}