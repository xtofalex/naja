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

#include "SNLOccurrence.h"

#include "SNLPath.h"
#include "SNLDesignObject.h"

namespace naja { namespace SNL {

SNLOccurrence::SNLOccurrence(SNLDesignObject* object):
  object_(object)
{}

SNLOccurrence::SNLOccurrence(const SNLPath& path, SNLDesignObject* object):
  path_(path.getSharedPath()),
  object_(object)
{}

bool SNLOccurrence::operator==(const SNLOccurrence& rhs) const {
  if (getObject() == nullptr) {
    return rhs.getObject() == nullptr;
  }
  if (rhs.getObject() == nullptr) {
    return false;
  }
  return (*getObject() == *rhs.getObject()) and (getPath() == rhs.getPath());
}

bool SNLOccurrence::operator<(const SNLOccurrence& rhs) const {
  //First start by comparing objects (through their SNLIDs)
  //If equal compare their path. Paths can be nullptr
  if (getObject() == nullptr) {
    return rhs.getObject() not_eq nullptr;
  }
  if (rhs.getObject() == nullptr) {
    return false;
  }
  return (*getObject() < *rhs.getObject()) or
    ((*getObject() == *rhs.getObject()) and (getPath() < rhs.getPath()));
}

SNLPath SNLOccurrence::getPath() const {
  if (path_) {
    return SNLPath(path_);
  }
  return SNLPath();
}

}} // namespace SNL // namespace naja
