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

#ifndef __PY_SNL_NET_H_
#define __PY_SNL_NET_H_

#include "PySNLDesignObject.h"
#include "SNLNet.h"

namespace PYSNL {

typedef struct {
  PySNLDesignObject parent_;
} PySNLNet;

extern PyTypeObject PyTypeSNLNet;

extern PyObject*    PySNLNet_Link(naja::SNL::SNLNet*);
extern void         PySNLNet_LinkPyType();

#define IsPySNLNet(v) (PyObject_TypeCheck(v, &PyTypeSNLNet))
#define PYSNLNet(v)   (static_cast<PySNLNet*>(v))
#define PYSNLNet_O(v) (static_cast<naja::SNL::SNLNet*>(PYSNLNet(v)->parent_->object_))

} /* PYSNL namespace */
 
#endif /* __PY_SNL_NET_H_ */
