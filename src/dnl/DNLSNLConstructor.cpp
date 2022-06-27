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

#include "DNLSNLConstructor.h"

#include <iostream>

#include "SNLDesign.h"

#include "DNLDB.h"

namespace naja { namespace DNL {

DNLDB* DNLSNLConstructor::construct(SNL::SNLDesign* top) {
  DNLDB* db = DNLDB::create();
  //go down in tree and create an entry for each instance
  //construct stack of nodes to visit
  using Instance = std::pair<size_t, SNL::SNLInstance*>;
  using Instances = std::deque<Instance>;
  Instances instances;

  for (auto snlInstance: top->getInstances()) {
    instances.push_back(Instance(0, snlInstance));
  }

  while (not instances.empty()) {
    auto instance = instances.front();
    //add instance in SNLDB
    auto parentIndex = instance.first;
    auto snlInstance = instance.second; 
    instances.pop_front();

    if (snlInstance->isLeaf()) {
      db->pushLeaf(snlInstance, parentIndex);
    } else {
      auto instanceIndex = db->pushInstance(snlInstance, parentIndex);
      auto model = snlInstance->getModel();
      for (auto subSNLInstance: model->getInstances()) {
        instances.push_back(Instance(instanceIndex, subSNLInstance));
      }
    }
  }
  return db;
}

}} //namespace DNL // namespace naja