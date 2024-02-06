// SPDX-FileCopyrightText: 2024 The Naja authors <https://github.com/xtofalex/naja/blob/main/AUTHORS>
//
// SPDX-License-Identifier: Apache-2.0

#ifndef BNE_H_
#define BNE_H_

#include "SNLID.h"

namespace naja { namespace BNE {

class BNENode {
  public:
    bool isRoot() const { return isRoot_; }
    BNENode* getParent() const;
  private:
    bool                        isRoot_;
    void*                       parent_;
    SNL::SNLID::DesignObjectID  instanceID_;
};

}} // namespace BNE // namespace naja

#endif // BNE_H_