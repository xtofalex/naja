#include "SNLScalarTerm.h"

#include <sstream>

#include "SNLException.h"
#include "SNLDesign.h"

namespace SNL {

SNLScalarTerm::SNLScalarTerm(SNLDesign* design, const Direction& direction, const SNLName& name):
  super(),
  design_(design),
  name_(name),
  direction_(direction)
{}

SNLScalarTerm* SNLScalarTerm::create(SNLDesign* design, const Direction& direction, const SNLName& name) {
  preCreate(design, name);
  SNLScalarTerm* net = new SNLScalarTerm(design, direction, name);
  net->postCreate();
  return net;
}

void SNLScalarTerm::preCreate(SNLDesign* design, const SNLName& name) {
  super::preCreate();
  if (not design) {
    throw SNLException("malformed SNLScalarTerm creator with NULL design argument");
  }
  if (not name.empty() and design->getTerm(name)) {
    std::string reason = "SNLDesign " + design->getString() + " contains already a SNLScalarTerm named: " + name;
    throw SNLException(reason);
  }
}

void SNLScalarTerm::postCreate() {
  super::postCreate();
  getDesign()->addTerm(this);
}

void SNLScalarTerm::commonPreDestroy() {
  super::preDestroy();
}

void SNLScalarTerm::destroyFromDesign() {
  commonPreDestroy();
  delete this;
}

void SNLScalarTerm::preDestroy() {
  commonPreDestroy();
  getDesign()->removeTerm(this);
}

SNLID SNLScalarTerm::getSNLID() const {
  return SNLDesignObject::getSNLID(SNLID::Type::Term, id_, 0, 0);
}

constexpr const char* SNLScalarTerm::getTypeName() const {
  return "SNLScalarTerm";
}
 
std::string SNLScalarTerm::getString() const {
  std::ostringstream str;
  if (not isAnonymous()) {
    str << getName();
  }
  str << "(" << getID() << ")";
  return str.str();

}

std::string SNLScalarTerm::getDescription() const {
  return "<" + std::string(getTypeName()) + " " + name_ + " " + design_->getName() + ">";  
}

}
