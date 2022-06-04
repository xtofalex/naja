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

#include "SNLFlattenerInstanceTree.h"

#include "SNLFlattenerInstanceTreeNode.h"

namespace naja { namespace SNL {

SNLFlattenerInstanceTree::SNLFlattenerInstanceTree(const SNLDesign* top) {
  root_ = new SNLFlattenerInstanceTreeNode(this, top);
}

SNLFlattenerInstanceTree::~SNLFlattenerInstanceTree() {
  delete root_;
}

void SNLFlattenerInstanceTree::print(std::ostream& stream) const {
  getRoot()->print(stream);
}

SNLCollection<SNLFlattenerInstanceTreeNode*> SNLFlattenerInstanceTree::getLeaves() const {
  return SNLCollection<SNLFlattenerInstanceTreeNode*>();
}

}} // namespace SNL // namespace naja