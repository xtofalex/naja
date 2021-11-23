#include "SNLBusTermBit.h"

#include <iostream>

#include "SNLBusTerm.h"

namespace SNL {

SNLBusTermBit::SNLBusTermBit(
    SNLBusTerm* bus,
    SNLID::Bit bit):
  super(),
  bus_(bus),
  bit_(bit)
{}

SNLBusTermBit* SNLBusTermBit::create(SNLBusTerm* bus, SNLID::Bit bit) {
  preCreate(bus, bit);
  SNLBusTermBit* busTermBit = new SNLBusTermBit(bus, bit);
  busTermBit->postCreate();
  return busTermBit;
}

void SNLBusTermBit::preCreate(const SNLBusTerm* bus, SNLID::Bit bit) {
  super::preCreate();
}

void SNLBusTermBit::postCreate() {
  super::postCreate();
}

void SNLBusTermBit::destroyFromBus() {
  preDestroy();
  delete this;
}

void SNLBusTermBit::destroy() {
  //FIXME:manage with exception in the future ??
  std::cerr << "Unauthorized destroy of BusTermBit" << std::endl; 
  exit(-35);
}

void SNLBusTermBit::preDestroy() {
  super::preDestroy();
}

SNLID SNLBusTermBit::getSNLID() const {
  return SNLDesignObject::getSNLID(SNLID::Type::Net, getBus()->getID(), 0, getBit());
}

SNLDesign* SNLBusTermBit::getDesign() const {
  return getBus()->getDesign();
}

constexpr const char* SNLBusTermBit::getTypeName() const {
  return "SNLBusTermBit";
}

SNLName SNLBusTermBit::getName() const {
  return getBus()->getName();
}

SNLTerm::Direction SNLBusTermBit::getDirection() const {
  return getBus()->getDirection();
}

std::string SNLBusTermBit::getString() const {
  return std::string();
}

std::string SNLBusTermBit::getDescription() const {
  return "";
}

bool SNLBusTermBit::isAnonymous() const {
  return getBus()->isAnonymous();
}

}