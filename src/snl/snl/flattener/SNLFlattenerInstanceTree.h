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

#ifndef __SNL_FLATTENER_INSTANCE_TREE_H_
#define __SNL_FLATTENER_INSTANCE_TREE_H_

#include <ostream>

namespace naja { namespace SNL {

class SNLDesign;
class SNLFlattenerInstanceTreeNode;

class SNLFlattenerInstanceTree {
  public:
    SNLFlattenerInstanceTree(const SNLFlattenerInstanceTree&) = delete;
    SNLFlattenerInstanceTree(const SNLFlattenerInstanceTree&&) = delete;
    static SNLFlattenerInstanceTree* create(const SNLDesign* top);
    void destroy();

    SNLFlattenerInstanceTreeNode* getRoot() const { return root_; }

    void print(std::ostream& stream) const;
  private:
    SNLFlattenerInstanceTree() = default;
    ~SNLFlattenerInstanceTree();

    SNLFlattenerInstanceTreeNode* root_;
};

}} // namespace SNL // namespace naja

#endif /* __SNL_FLATTENER_INSTANCE_TREE_H_ */