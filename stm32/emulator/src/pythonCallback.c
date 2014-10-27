#include </opt/pym32/include/python2.7/Python.h>

static PyObject *my_callback = NULL;

static PyObject *set_python_callback_reference(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    PyObject *temp;

    if (PyArg_ParseTuple(args, "O:REGISTER_VALUES_CALLBACK", &temp)) {
        if (!PyCallable_Check(temp)) {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
        Py_XINCREF(temp);
        Py_XDECREF(my_callback);
        my_callback = temp;
        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}

static PyObject *callback_python(PyObject *dummy, PyObject *arglist) {
    PyObject *result = PyObject_CallObject(my_callback, arglist);
    Py_DECREF(arglist);
    if (result == NULL) {
        return NULL;
    }
    Py_DECREF(result);
    Py_INCREF(Py_None);
    result = Py_None;
    return result;
}

static char set_python_callback_reference_docs[] = "Set python callback function reference from python to C call.";
static char callback_python_docs[] = "Call python callback function from C to python through python callback reference.";

static PyMethodDef pythonCallback_methods[] = {
  {"set_python_callback_reference", (PyCFunction)set_python_callback_reference, METH_VARARGS, \
    set_python_callback_reference_docs},
  {"callback_python", (PyCFunction)callback_python, METH_VARARGS, callback_python_docs},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initpythonCallback(void)
{
    (void) Py_InitModule3("pythonCallback", pythonCallback_methods, "Extension module for C-to-from-python callbacks");
}
