#include "SNLInstance.h"

#include <iostream>
#include <sstream>

#include "Card.h"

#include "SNLException.h"
#include "SNLDesign.h"
#include "SNLInstance.h"
#include "SNLBusTerm.h"
#include "SNLBusTermBit.h"
#include "SNLScalarTerm.h"
#include "SNLInstTerm.h"

namespace SNL {

SNLInstance::SNLInstance(SNLDesign* design, SNLDesign* model, const SNLName& name):
  super(),
  design_(design),
  model_(model),
  name_(name)
{}

SNLInstance* SNLInstance::create(SNLDesign* design, SNLDesign* model, const SNLName& name) {
  preCreate(design, name);
  SNLInstance* instance = new SNLInstance(design, model, name);
  instance->postCreate();
  return instance;
}

SNLSharedPath* SNLInstance::getSharedPath(const SNLSharedPath* tailSharedPath) const {
  auto it = sharedPaths_.find(tailSharedPath);
  if (it != sharedPaths_.end()) {
    return it->second;
  }
  return nullptr;
}

void SNLInstance::addSharedPath(const SNLSharedPath* tailSharedPath) {
}

void SNLInstance::preCreate(SNLDesign* design, const SNLName& name) {
  super::preCreate();
  if (not design) {
    throw SNLException("malformed SNLInstance creator with NULL design argument");
  }
  if (not name.empty() and design->getInstance(name)) {
    std::string reason = "SNLDesign " + design->getString() + " contains already a SNLInstance named: " + name.getString();
    throw SNLException(reason);
  }
}

void SNLInstance::postCreate() {
  super::postCreate();
  getDesign()->addInstance(this);
  if (not getModel()->isPrimitive()) {
    //Always execute addSlaveInstance after addInstance.
    //addInstance determines the instance ID.
    getModel()->addSlaveInstance(this);
  }
  //create instance terminals
  for (SNLTerm* term: getModel()->getTerms()) {
    if (SNLBusTerm* bus = dynamic_cast<SNLBusTerm*>(term)) {
      for (auto bit: bus->getBits()) {
        createInstTerm(bit);
      }
    } else {
      SNLScalarTerm* scalar = static_cast<SNLScalarTerm*>(term);
      createInstTerm(scalar);
    }
  }
}

void SNLInstance::createInstTerm(SNLBitTerm* term) {
  instTerms_.push_back(SNLInstTerm::create(this, term));
}

void SNLInstance::removeInstTerm(SNLBitTerm* term) {
  if (term->getPosition() > instTerms_.size()) {
    throw SNLException("");
  }
  instTerms_[term->getPosition()] = nullptr;
}

void SNLInstance::commonPreDestroy() {
#if DEBUG
  std::cerr << "commonPreDestroy: " << getString() << std::endl;
#endif
  for (auto instTerm: instTerms_) {
    instTerm->destroyFromInstance();
  }
  super::preDestroy();
}

void SNLInstance::destroyFromModel() {
  getDesign()->removeInstance(this);
  commonPreDestroy();
  delete this;
}

void SNLInstance::destroyFromDesign() {
  if (not getModel()->isPrimitive()) {
    getModel()->removeSlaveInstance(this);
  }
  commonPreDestroy();
  delete this;
}

void SNLInstance::preDestroy() {
  if (not getModel()->isPrimitive()) {
    getModel()->removeSlaveInstance(this);
  }
  getDesign()->removeInstance(this);
  commonPreDestroy();
}

SNLID SNLInstance::getSNLID() const {
  return SNLDesignObject::getSNLID(SNLID::Type::Instance, 0, id_, 0);
}

SNLInstTerm* SNLInstance::getInstTerm(const SNLBitTerm* term) {
  if (term->getDesign() != getModel()) {
    std::string reason = "SNLInstance::getInsTerm incoherency: "
      + getName().getString() + " model: " + getModel()->getName().getString()
      + " and " + term->getString() + " model: " + term->getDesign()->getName().getString()
      + " should be the same";
    throw SNLException(reason);
  }
  if (term->getPosition() > instTerms_.size()) {
    std::string reason = "SNLInstance::getInsTerm error: size issue";
    throw SNLException(reason);
  }
  return instTerms_[term->getPosition()];
}

SNLCollection<SNLInstTerm*> SNLInstance::getInstTerms() const {
  //FIXME: filter non null inst terms
  return SNLCollection<SNLInstTerm*>(new SNLVectorCollection<SNLInstTerm*>(&instTerms_));
}

constexpr const char* SNLInstance::getTypeName() const {
  return "SNLInstance";
}

std::string SNLInstance::getString() const {
  std::ostringstream str; 
  if (not isAnonymous()) {
    str << getName().getString();
  }
  str << "(" << getID() << ")";
  return str.str();
}

std::string SNLInstance::getDescription() const {
  return "<" + std::string(getTypeName())
    + " " + name_.getString()
    + " " + design_->getName().getString()
    + " " + model_->getName().getString()
    + ">";  
}

Card* SNLInstance::getCard() const {
  Card* card = super::getCard();
  card->addItem(new CardDataItem<const SNLName>("Name", name_));
  card->addItem(new CardDataItem<const SNLDesign*>("Design", design_));
  card->addItem(new CardDataItem<const SNLDesign*>("Model", model_));
  return card;
}

}
