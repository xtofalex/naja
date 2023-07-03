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

#ifndef __SNL_MACROS_H_
#define __SNL_MACROS_H_

#include <sstream>

//
//Contains various methods used in different while similar... contexts
//Might seem dirty to use good old macros but I prefer this than plain copy/paste...
//Did not find a proper way to implement this with templates.
//

#define NET_COMPONENT_SET_NET(TYPE) \
void TYPE::setNet(SNLNet* net) { \
  if (net and net->getDesign() not_eq getDesign()) { \
    std::string reason = "Impossible setNet call with incompatible designs: "; \
    reason += getString() + " is in " + getDesign()->getString() + " while "; \
    reason += net->getString() + " is in " + net->getDesign()->getString(); \
    throw SNLException(reason); \
  } \
  SNLBitNet* bitNet = nullptr; \
  if (net) { \
    bitNet = dynamic_cast<SNLBitNet*>(net); \
    if (not bitNet) { \
      std::string reason = "Impossible setNet call with incompatible nets size: "; \
      throw SNLException(reason); \
    } \
  } \
  if (net_ not_eq bitNet) { \
    if (net_) { \
      net_->removeComponent(this); \
    } \
    net_ = bitNet; \
    if (net_) { \
      net_->addComponent(this); \
    } \
  } \
}

#define DESIGN_OBJECT_SET_NAME(TYPE, METHOD_TYPE, STRING) \
void TYPE::setName(const SNLName& name) { \
  if (name_ == name) { \
    return; \
  } \
  if (not name.empty()) { \
    /* check collision */ \
    if (auto collision = design_->get##METHOD_TYPE(name)) { \
      std::ostringstream reason; \
      reason << "In design " << design_->getString() \
        << ", cannot rename " << getString() << " to " \
        << name.getString() << ", another #STRING: " << collision->getString() \
        << " has already this name."; \
      throw SNLException(reason.str()); \
    } \
  } \
  auto previousName = getName(); \
  name_ = name; \
  getDesign()->rename(this, previousName); \
}

#define DESIGN_RENAME(TYPE, METHOD_TYPE, MAP) \
void SNLDesign::rename(TYPE* object, const SNLName& previousName) { \
  /*if object was anonymous, and new one is not... just insert with new name */ \
  if (previousName.empty()) { \
    if (not object->isAnonymous()) { \
      /* collision is already verified by object before trying insertion */ \
      MAP[object->getName()] = object->getID(); \
    } /* else nothing to do, anonymous to anonymous */ \
  } else { \
    auto node = MAP.extract(previousName); \
    assert(node); \
    if (not object->isAnonymous()) { \
      node.key() = object->getName(); \
      MAP.insert(std::move(node)); \
    } \
  } \
}

#endif // __SNL_MACROS_H_
