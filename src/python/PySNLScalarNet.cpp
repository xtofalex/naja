#include "PySNLScalarNet.h"

#include "PySNLDesign.h"

#include "SNLScalarNet.h"

namespace PYSNL {

using namespace SNL;

#undef   ACCESS_OBJECT
#undef   ACCESS_CLASS
#define  ACCESS_OBJECT           parent_.parent_.parent_.object_
#define  ACCESS_CLASS(_pyObject)  &(_pyObject->parent_)
#define  METHOD_HEAD(function)   GENERIC_METHOD_HEAD(ScalarNet, net, function)

static PyObject* PySNLScalarNet_create(PyObject*, PyObject* args) {
  PyObject* arg0 = nullptr;
  const char* arg1 = nullptr;
  if (not PyArg_ParseTuple(args, "O|s:SNLDB.create", &arg0, &arg1)) {
    setError("malformed SNLScalarNet create method");
    return nullptr;
  }
  SNLName name;
  if (arg1) {
    name = SNLName(arg1);
  }

  SNLScalarNet* net = nullptr;
  SNLTRY
  if (IsPySNLDesign(arg0)) {
    net = SNLScalarNet::create(PYSNLDesign_O(arg0), name);
  } else {
    setError("SNLScalarNet create accepts SNLDesign as first argument");
    return nullptr;
  }
  SNLCATCH
  return PySNLScalarNet_Link(net);
}

PyMethodDef PySNLScalarNet_Methods[] = {
  { "create", (PyCFunction)PySNLScalarNet_create, METH_VARARGS|METH_STATIC,
    "SNLScalarNet creator"},
  {NULL, NULL, 0, NULL}           /* sentinel */
};

DBoDestroyAttribute(PySNLScalarNet_destroy, PySNLScalarNet)
DBoDeallocMethod(SNLScalarNet)

DBoLinkCreateMethod(SNLScalarNet)
PyTypeObjectLinkPyType(SNLScalarNet)
PyTypeObjectDefinitions(SNLScalarNet)

}
