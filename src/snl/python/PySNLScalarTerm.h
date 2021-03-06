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

#ifndef __PY_SNL_SCALAR_TERM_H_
#define __PY_SNL_SCALAR_TERM_H_

#include "PySNLBitTerm.h"
#include "SNLScalarTerm.h"

namespace PYSNL {

typedef struct {
  PySNLBitTerm parent_;
} PySNLScalarTerm;

extern PyTypeObject PyTypeSNLScalarTerm;
extern PyMethodDef  PySNLScalarTerm_Methods[];

extern PyObject*    PySNLScalarTerm_Link(naja::SNL::SNLScalarTerm* t);
extern void         PySNLScalarTerm_LinkPyType();

#define IsPySNLScalarTerm(v) (PyObject_TypeCheck(v, &PyTypeSNLScalarTerm))
#define PYSNLScalarTerm(v)   (static_cast<PySNLScalarTerm*>(v))
#define PYSNLScalarTerm_O(v) (PYSNLScalarTerm(v)->object_)

} // PYSNL namespace
 
#endif // __PY_SNL_SCALAR_TERM_H_
