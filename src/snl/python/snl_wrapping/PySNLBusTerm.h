// Copyright 2022 The Naja Authors.
// SPDX-FileCopyrightText: 2023 The Naja authors <https://github.com/xtofalex/naja/blob/main/AUTHORS>
//
// SPDX-License-Identifier: Apache-2.0

#ifndef __PY_SNL_BUS_TERM_H_
#define __PY_SNL_BUS_TERM_H_

#include "PySNLTerm.h"

namespace naja::SNL {
  class SNLBusTerm;
}

namespace PYSNL {

typedef struct {
  PySNLTerm parent_;
} PySNLBusTerm;

extern PyTypeObject PyTypeSNLBusTerm;

extern PyObject*    PySNLBusTerm_Link(naja::SNL::SNLBusTerm* t);
extern void         PySNLBusTerm_LinkPyType();

#define IsPySNLBusTerm(v) (PyObject_TypeCheck(v, &PyTypeSNLBusTerm))
#define PYSNLBusTerm(v)   ((PySNLBusTerm*)(v))
#define PYSNLBusTerm_O(v) (PYSNLBusTerm(v)->object_)

} // PYSNL namespace
 
#endif // __PY_SNL_BUS_TERM_H_