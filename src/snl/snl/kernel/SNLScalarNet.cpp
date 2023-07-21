// Copyright 2022 The Naja Authors.
// SPDX-FileCopyrightText: 2023 The Naja authors <https://github.com/xtofalex/naja/blob/main/AUTHORS>
//
// SPDX-License-Identifier: Apache-2.0

#include "SNLScalarNet.h"

#include <sstream>

#include "SNLDB.h"
#include "SNLException.h"
#include "SNLLibrary.h"
#include "SNLDesign.h"
#include "SNLMacros.h"

namespace naja { namespace SNL {

SNLScalarNet::SNLScalarNet(SNLDesign* design, const SNLName& name):
  super(),
  design_(design),
  name_(name)
{}

SNLScalarNet::SNLScalarNet(SNLDesign* design, SNLID::DesignObjectID id, const SNLName& name):
  super(),
  design_(design),
  id_(id),
  name_(name)
{}

SNLScalarNet* SNLScalarNet::create(SNLDesign* design, const SNLName& name) {
  preCreate(design, name);
  SNLScalarNet* net = new SNLScalarNet(design, name);
  net->postCreateAndSetID();
  return net;
}

SNLScalarNet* SNLScalarNet::create(SNLDesign* design, SNLID::DesignObjectID id, const SNLName& name) {
  preCreate(design, id, name);
  SNLScalarNet* net = new SNLScalarNet(design, id, name);
  net->postCreate();
  return net;
}

void SNLScalarNet::preCreate(const SNLDesign* design, const SNLName& name) {
  super::preCreate();
  if (not design) {
    throw SNLException("malformed SNLScalarNet creator with NULL design argument");
  }
  if (not name.empty() and design->getNet(name)) {
    std::string reason = "SNLDesign " + design->getString() + " contains already a SNLScalarNet named: " + name.getString();
    throw SNLException(reason);
  }
}

void SNLScalarNet::preCreate(const SNLDesign* design, SNLID::DesignObjectID id, const SNLName& name) {
  preCreate(design, name);
  if (design->getNet(id)) {
    std::string reason = "SNLDesign " + design->getString() + " contains already a SNLScalarNet with id: " + std::to_string(id);
    throw SNLException(reason);
  }
}

void SNLScalarNet::postCreateAndSetID() {
  super::postCreate();
  getDesign()->addNetAndSetID(this);
}

void SNLScalarNet::postCreate() {
  super::postCreate();
  getDesign()->addNet(this);
}

DESIGN_OBJECT_SET_NAME(SNLScalarNet, Net, net)

void SNLScalarNet::commonPreDestroy() {
  super::preDestroy();
}

void SNLScalarNet::destroyFromDesign() {
  commonPreDestroy();
  delete this;
}

void SNLScalarNet::preDestroy() {
  commonPreDestroy();
  getDesign()->removeNet(this);
}

SNLID SNLScalarNet::getSNLID() const {
  return SNLDesignObject::getSNLID(SNLID::Type::Net, id_, 0, 0);
}

NajaCollection<SNLBitNet*> SNLScalarNet::getBits() const {
  return NajaCollection(new NajaSingletonCollection(const_cast<SNLScalarNet*>(this))).getParentTypeCollection<SNLBitNet*>();
}

//LCOV_EXCL_START
const char* SNLScalarNet::getTypeName() const {
  return "SNLScalarNet";
}
//LCOV_EXCL_STOP


//LCOV_EXCL_START
std::string SNLScalarNet::getString() const {
  return getName().getString();
}
//LCOV_EXCL_STOP

//LCOV_EXCL_START
std::string SNLScalarNet::getDescription() const {
  std::ostringstream stream;
  stream << "<" << std::string(getTypeName());
  if (not isAnonymous()) {
    stream << " " + getName().getString();
  }
  stream << " " << getID();
  if (not getDesign()->isAnonymous()) {
    stream << " " + getDesign()->getName().getString();
  }
  stream << " " << getDesign()->getID();
  stream << ">";
  return stream.str(); 
}
//LCOV_EXCL_STOP

//LCOV_EXCL_START
void SNLScalarNet::debugDump(size_t indent, std::ostream& stream) const {
  stream << std::string(indent, ' ') << getDescription() << std::endl;
}
//LCOV_EXCL_STOP

}} // namespace SNL // namespace naja
