/*
 * Copyright 2022 The Naja Authors.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __PY_INTERFACE_H
#define __PY_INTERFACE_H

#include <iostream>
#include <sstream>

#define PY_SSIZE_T_CLEAN /* Make "s#" use Py_ssize_t rather than int. */
#include <Python.h>

#include "SNLException.h"

namespace PYSNL {

static void setError(const std::string& reason) {
  //Mabybe create a custom error type in the future ?
  PyErr_SetString(PyExc_RuntimeError, reason.c_str());
}

}

// This macro must be redefined in derived classes.
// Example : baseOject_.object_
#define ACCESS_OBJECT object_

#define SNLTRY try {

#define SNLCATCH                                        \
  } catch (const naja::SNL::SNLException& e) {                \
    setError("SNL exception: " + e.getReason());        \
    return nullptr;                                     \
  } catch (const std::exception& e) {                   \
    setError("Exception " + std::string(e.what()));     \
    return nullptr;                                     \
  } catch (...) {                                       \
    setError("Unknown exception");                      \
    return nullptr;                                     \
  }

#define DirectReprMethod(PY_FUNC_NAME,PY_SELF_TYPE,SELF_TYPE)                                   \
  static PyObject* PY_FUNC_NAME(PY_SELF_TYPE *self ) {                                          \
    if (not self->ACCESS_OBJECT) {                                                              \
      std::ostringstream repr;                                                                  \
      repr << "<" #PY_SELF_TYPE " [" << (void*)self << " <-> nullptr] unbound>";                \
      return PyUnicode_FromString(repr.str().c_str());                                          \
    }                                                                                           \
    SELF_TYPE* object = dynamic_cast<SELF_TYPE*>(self->ACCESS_OBJECT);                          \
    if (not object) {                                                                           \
      return PyUnicode_FromString("<PyObject invalid dynamic_cast>");                           \
    }                                                                                           \
    std::ostringstream repr;                                                                    \
    repr << "[" << (void*)self << "<->" << (void*)object << " " << object->getString() << "]";  \
    return PyUnicode_FromString(repr.str().c_str() );                                           \
  }

#define DirectStrMethod(PY_FUNC_NAME,PY_SELF_TYPE,SELF_TYPE)                      \
  static PyObject* PY_FUNC_NAME(PY_SELF_TYPE *self) {                             \
    if (not self->ACCESS_OBJECT) {                                                \
      std::ostringstream repr;                                                    \
      repr << "<" #PY_SELF_TYPE " [" << (void*)self << " <-> nullptr] unbound>";  \
      return PyUnicode_FromString(repr.str().c_str());                            \
    }                                                                             \
    SELF_TYPE* object = dynamic_cast<SELF_TYPE*>(self->ACCESS_OBJECT);            \
    if (not object)                                                               \
      return PyUnicode_FromString("<PyObject invalid dynamic_cast>" );            \
                                                                                  \
    return PyUnicode_FromString(object->getString().c_str() );                    \
  }

#define DirectCmpMethod(PY_FUNC_NAME,IS_PY_OBJECT,PY_SELF_TYPE)               \
  static int PY_FUNC_NAME(PY_SELF_TYPE *self, PyObject* other) {              \
    if (!IS_PY_OBJECT(other)) { return -1; }                                  \
                                                                              \
    PY_SELF_TYPE* otherPyObject = (PY_SELF_TYPE*)other;                       \
    if (self->ACCESS_OBJECT == otherPyObject->ACCESS_OBJECT) return 0;        \
    if (self->ACCESS_OBJECT < otherPyObject->ACCESS_OBJECT) return -1;        \
                                                                              \
    return 1;                                                                 \
  }

#define DirectHashMethod(PY_FUNC_NAME,PY_SELF_TYPE)                           \
  static int PY_FUNC_NAME (PY_SELF_TYPE *self) {                              \
    return (long)self->ACCESS_OBJECT;                                         \
  }


#define DirectGetIntMethod(PY_FUNC_NAME,FUNC_NAME,PY_SELF_TYPE,SELF_TYPE) \
  static PyObject* PY_FUNC_NAME(PY_SELF_TYPE* self, PyObject *args ) {    \
    GENERIC_METHOD_HEAD(SELF_TYPE,cobject,#FUNC_NAME"()")                 \
    return Py_BuildValue("i", cobject->FUNC_NAME());                      \
  }

#define DBoDestroyAttribute(PY_FUNC_NAME, PY_SELF_TYPE)                                    \
  static PyObject* PY_FUNC_NAME(PY_SELF_TYPE *self) {                                      \
    if (not self->ACCESS_OBJECT) {                                                         \
      setError("applying a destroy() to a Python object with no object attached");         \
      return nullptr;                                                                      \
    }                                                                                      \
    self->ACCESS_OBJECT->destroy();                                                        \
    self->ACCESS_OBJECT = nullptr;                                                         \
    Py_RETURN_NONE;                                                                        \
  }

#define DBoDeallocMethod(SELF_TYPE)                                      \
  static void Py##SELF_TYPE##_DeAlloc(Py##SELF_TYPE *self) {             \
    PyObject_DEL(self);                                                  \
  }

#define PyTypeObjectLinkPyTypeWithClass(PY_SELF_TYPE,SELF_TYPE)                   \
  DirectReprMethod(Py##PY_SELF_TYPE##_Repr, Py##PY_SELF_TYPE,   SELF_TYPE)        \
  DirectStrMethod (Py##PY_SELF_TYPE##_Str,  Py##PY_SELF_TYPE,   SELF_TYPE)        \
  DirectCmpMethod (Py##PY_SELF_TYPE##_Cmp,  IsPy##PY_SELF_TYPE, Py##PY_SELF_TYPE) \
  DirectHashMethod(Py##PY_SELF_TYPE##_Hash, Py##SELF_TYPE)                        \
  extern void  Py##PY_SELF_TYPE##_LinkPyType() {                                  \
    PyType##PY_SELF_TYPE.tp_dealloc = (destructor) Py##PY_SELF_TYPE##_DeAlloc;    \
    /*PyType##PY_SELF_TYPE.tp_compare = (cmpfunc)    Py##PY_SELF_TYPE##_Cmp;*/    \
    PyType##PY_SELF_TYPE.tp_repr    = (reprfunc)   Py##PY_SELF_TYPE##_Repr;       \
    PyType##PY_SELF_TYPE.tp_str     = (reprfunc)   Py##PY_SELF_TYPE##_Str;        \
    PyType##PY_SELF_TYPE.tp_hash    = (hashfunc)   Py##PY_SELF_TYPE##_Hash;       \
    PyType##PY_SELF_TYPE.tp_methods = Py##PY_SELF_TYPE##_Methods;                 \
  }

#define DBoLinkCreateMethod(SELF_TYPE)                                         \
  PyObject* Py##SELF_TYPE##_Link(SELF_TYPE* object) {                          \
    if (not object) {                                                          \
      Py_RETURN_NONE;                                                          \
    }                                                                          \
    Py##SELF_TYPE* pyObject = PyObject_NEW(Py##SELF_TYPE, &PyType##SELF_TYPE); \
    pyObject->ACCESS_OBJECT = object;                                          \
    return (PyObject*)pyObject;                                                \
  }

#define PyTypeObjectLinkPyType(SELF_TYPE) \
  PyTypeObjectLinkPyTypeWithClass(SELF_TYPE,SELF_TYPE)

#define PYTYPE_READY(TYPE)                                        \
  if (PyType_Ready(&PyType##TYPE) < 0) {                          \
    std::cerr << "[ERROR] Failed to initialize <Py" #TYPE ">."    \
      << std::endl;                                               \
    return nullptr;                                               \
  }

#define  PYTYPE_READY_SUB(TYPE, TYPE_BASE)                        \
  PyType##TYPE.tp_base = &PyType##TYPE_BASE;                      \
  if (PyType_Ready(&PyType##TYPE) < 0) {                          \
    std::cerr << "[ERROR]\n"                                      \
         << "  Failed to initialize <Py" #TYPE ">." << std::endl; \
    return nullptr;                                               \
  }

#define PyTypeObjectDefinitions(SELF_TYPE)                          \
  PyTypeObject PyType##SELF_TYPE = {                                \
    PyVarObject_HEAD_INIT(NULL, 0)                                  \
    #SELF_TYPE, /* tp_name */                                       \
    sizeof(Py##SELF_TYPE), /* tp_basicsize */                       \
    0, /* tp_itemsize */                                            \
    0, /* tp_dealloc */                                             \
    0, /* tp_print */                                               \
    0, /* tp_getattr */                                             \
    0, /* tp_setattr */                                             \
    0, /* tp_reserved */                                            \
    0, /* tp_repr */                                                \
    0, /* tp_as_number */                                           \
    0, /* tp_as_sequence */                                         \
    0, /* tp_as_mapping */                                          \
    0, /* tp_hash */                                                \
    0, /* tp_call */                                                \
    0, /* tp_str */                                                 \
    0, /* tp_getattro */                                            \
    0, /* tp_setattro */                                            \
    0, /* tp_as_buffer */                                           \
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */        \
    "#SELF_TYPE objects", /* tp_doc */                              \
    0, /* tp_traverse */                                            \
    0, /* tp_clear */                                               \
    0, /* tp_richcompare */                                         \
    0, /* tp_weaklistoffset */                                      \
    0, /* tp_iter */                                                \
    0, /* tp_iternext */                                            \
    0, /* tp_methods */                                             \
    0, /* tp_members */                                             \
    0, /* tp_getset */                                              \
    0, /* tp_base */                                                \
    0, /* tp_dict */                                                \
    0, /* tp_descr_get */                                           \
    0, /* tp_descr_set */                                           \
    0, /* tp_dictoffset */                                          \
    0, /* tp_init */                                                \
    0, /* tp_alloc */                                               \
    PyType_GenericNew /* tp_new */                                  \
};

#define PyTypeInheritedObjectDefinitions(SELF_TYPE, SUPER_TYPE)     \
  PyTypeObject PyType##SELF_TYPE = {                                \
    PyVarObject_HEAD_INIT(NULL, 0)                                  \
    #SELF_TYPE, /* tp_name */                                       \
    sizeof(Py##SELF_TYPE), /* tp_basicsize */                       \
    0, /* tp_itemsize */                                            \
    0, /* tp_dealloc */                                             \
    0, /* tp_print */                                               \
    0, /* tp_getattr */                                             \
    0, /* tp_setattr */                                             \
    0, /* tp_reserved */                                            \
    0, /* tp_repr */                                                \
    0, /* tp_as_number */                                           \
    0, /* tp_as_sequence */                                         \
    0, /* tp_as_mapping */                                          \
    0, /* tp_hash */                                                \
    0, /* tp_call */                                                \
    0, /* tp_str */                                                 \
    0, /* tp_getattro */                                            \
    0, /* tp_setattro */                                            \
    0, /* tp_as_buffer */                                           \
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */        \
    "#SELF_TYPE objects", /* tp_doc */                              \
    0, /* tp_traverse */                                            \
    0, /* tp_clear */                                               \
    0, /* tp_richcompare */                                         \
    0, /* tp_weaklistoffset */                                      \
    0, /* tp_iter */                                                \
    0, /* tp_iternext */                                            \
    0, /* tp_methods */                                             \
    0, /* tp_members */                                             \
    0, /* tp_getset */                                              \
    &PyType##SUPER_TYPE, /* tp_base */                              \
    0, /* tp_dict */                                                \
    0, /* tp_descr_get */                                           \
    0, /* tp_descr_set */                                           \
    0, /* tp_dictoffset */                                          \
    0, /* tp_init */                                                \
    0, /* tp_alloc */                                               \
    PyType_GenericNew /* tp_new */                                  \
};

#define GENERIC_METHOD_HEAD(SELF_TYPE,SELF_OBJECT,function)                                 \
  if (not self->ACCESS_OBJECT) {                                                            \
    setError("Attempt to call " function " on an unbound object");                          \
    return nullptr;                                                                         \
  }                                                                                         \
  SELF_TYPE* SELF_OBJECT = dynamic_cast<SELF_TYPE*>(self->ACCESS_OBJECT);                   \
  if (not SELF_OBJECT) {                                                                    \
    setError("Invalid dynamic_cast<> while calling " function "");                          \
    return nullptr;                                                                         \
  }

#endif /* __PY_INTERFACE_H */
