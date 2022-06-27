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

#include "DNLDB.h"

#include "SNLInstance.h"
#include "SNLDesign.h"

namespace naja { namespace DNL {

DNLDB* DNLDB::create() {
  auto db = new DNLDB();
  return db;
}

size_t DNLDB::pushInstance(const SNL::SNLInstance* instance, size_t parentIndex) {
  // SNLInstance ID, ParentIndex
  instances_.insert(instances_.end(), {instance->getID(), parentIndex});
  return instances_.size()-2;
}

void DNLDB::pushLeaf(const SNL::SNLInstance* instance, size_t parentIndex) {
  // SNLInstance ID, ParentIndex, nextInstance, Term, Term, Term, Term, .... 
  leaves_.insert(leaves_.end(), {instance->getID(), parentIndex, 0});
  //size_t instanceIndex = leaves_.size()-3;
  size_t nextInstanceIndex = leaves_.size()-2;
  auto model = instance->getModel();
  size_t nbBitTerms = model->getBitTerms().size();
  instances_.resize(leaves_.size() + nbBitTerms);
  instances_[nextInstanceIndex] = leaves_.size();
}

}} //namespace DNL // namespace naja