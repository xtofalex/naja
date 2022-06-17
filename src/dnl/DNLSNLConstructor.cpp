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
#include "SNLFlattener.h"
#include "SNLFlattenerInstanceTree.h"
#include "SNLFlattenerInstanceTreeNode.h"

#include "DNLDB.h"

namespace naja { namespace DNL {

DNLDB* DNLSNLConstructor::construct(SNL::SNLDesign* top) {
  SNL::SNLFlattener flattener;
  flattener.process(top);
  auto instanceTree = flattener.getInstanceTree();
  DNLDB* db = DNLDB::create();
  //go down in tree and create an entry for each instance
  //construct stack of nodes to visit
  using NodeStack = std::stack<SNL::SNLFlattenerInstanceTreeNode*>;
  NodeStack nodes;
  if (instanceTree->getRoot()) {
    nodes.push(instanceTree->getRoot());
  }
  while (not nodes.empty()) {
    auto node = nodes.top();
    nodes.pop();
    for (auto child: node->getChildren()) {
      nodes.push(child);
    }
    if (node->isRoot()) {
      
    } else {
      auto instance = node->getInstance();
      std::cerr << instance->getString() << std::endl;
    }
  }
  return db;
}

}} //namespace DNL // namespace naja