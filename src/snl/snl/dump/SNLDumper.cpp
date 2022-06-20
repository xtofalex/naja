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

#include "SNLDump.h"

#include <fstream>
#include <sstream>

#include "SNLDB.h"
#include "SNLLibrary.h"
#include "SNLDesign.h"
#include "SNLScalarTerm.h"
#include "SNLBusTerm.h"
#include "SNLUtils.h"
#include "SNLDump.h"
#include "SNLDumpManifest.h"
#include "SNLDumpException.h"

namespace {
using namespace naja::SNL;

void dumpParameter(const SNLParameter* parameter, std::ostream& stream) {
  stream << SNLDump::Tag::Parameter
    << " " << parameter->getName().getString()
    << " " << parameter->getValue()
    << std::endl;
}

void dumpBusTerm(const SNLBusTerm* term, std::ostream& stream) {
  stream << SNLDump::Tag::BusTerm
    << " " << term->getID()
    << " " << term->getDirection()
    << " " << term->getLSB()
    << " " << term->getMSB();
  if (not term->isAnonymous()) {
    stream << " " << term->getName().getString();
  }
  stream << std::endl;
}

void dumpScalarTerm(const SNLScalarTerm* term, std::ostream& stream) {
  stream << SNLDump::Tag::ScalarTerm
    << " " << term->getID()
    << " " << term->getDirection();
  if (not term->isAnonymous()) {
    stream << " " << term->getName().getString();
  }
  stream << std::endl;
}

void dumpTerm(const SNLTerm* term, std::ostream& stream) {
  if (auto bus = dynamic_cast<const SNLBusTerm*>(term)) {
    dumpBusTerm(bus, stream);
  } else {
    auto scalar = static_cast<const SNLScalarTerm*>(term);
    dumpScalarTerm(scalar, stream);
  }
 
}

void dumpNet(const SNLNet* net, std::ostream& stream) {
  stream << SNLDump::Tag::Net
    << " " << net->getID();
  if (not net->isAnonymous()) {
    stream << " " << net->getName().getString();
  }
  stream << std::endl;
}

void dumpInstance(const SNLInstance* instance, std::ostream& stream) {
  //DBID is unsigned char
  //+ promotes it to numerical value
  stream << SNLDump::Tag::Instance
    << " " << +instance->getModel()->getDB()->getID()
    << " " << instance->getModel()->getLibrary()->getID()
    << " " << instance->getModel()->getID()
    << " " << instance->getID();
  if (not instance->isAnonymous()) {
    stream << " " << instance->getName().getString();
  }
  stream << std::endl;
}

void dumpDesign(const SNLDesign* design, std::ostream& stream) {
  stream << SNLDump::Tag::Design
    << " " << design->getLibrary()->getID()
    << " " << design->getID()
    << " " << design->getName().getString() << std::endl;
  for (auto parameter: design->getParameters()) {
    dumpParameter(parameter, stream);
  }
  for (auto net: design->getNets()) {
    dumpNet(net, stream);
  }
  for (auto term: design->getTerms()) {
    dumpTerm(term, stream);
  }
  for (auto instance: design->getInstances()) {
    dumpInstance(instance, stream);
  }
}

}

namespace naja { namespace SNL {


void SNLDump::dump(const std::filesystem::path& path) {
  //First round dump DB, Library and Design Interfaces
  auto universe = SNLUniverse::getUserDBs();

  //create directory
  if (std::filesystem::exists(path)) {
    std::ostringstream reason;
    reason << "cannot dump " << top->getString() << " as " << path.string() << " exists already";
    throw SNLDumpException(reason.str());
  }
  std::filesystem::create_directory(path);
  //publish manifest
  SNLDumpManifest::dump(path);
  
  std::filesystem::path dumpPath(path/DesignDBName);
  std::ofstream dumpStream(dumpPath);
  SNLUtils::SortedDesigns designs;
  SNLUtils::getDesignsSortedByHierarchicalLevel(top, designs);
  //get all designs libraries in a set
  using Libraries = std::set<SNLLibrary*>;
  Libraries libraries;
  for (const SNLUtils::DesignLevel& dl: designs) {
    auto design = dl.first;
    libraries.insert(libraries);
  }
  

  for (const SNLUtils::DesignLevel& dl: designs) {
    dumpDesign(dl.first, dumpStream);
  }
}

}} // namespace SNL // namespace naja
