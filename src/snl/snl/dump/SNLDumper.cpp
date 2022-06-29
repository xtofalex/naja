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

#include "SNLUniverse.h"
#include "SNLScalarTerm.h"
#include "SNLBusTerm.h"
#include "SNLScalarNet.h"
#include "SNLBusNet.h"
#include "SNLDump.h"
#include "SNLDumpManifest.h"
#include "SNLDumpException.h"

namespace {
using namespace naja::SNL;

void dumpScalarNet(const SNLScalarNet* net, std::ostream& stream) {
  stream << SNLDump::Tag::BusNet
    << " " << net->getID();
  if (not net->isAnonymous()) {
    stream << " " << net->getName().getString();
  }
  stream << std::endl;
}

void dumpBusNet(const SNLBusNet* net, std::ostream& stream) {
  stream << SNLDump::Tag::BusNet
    << " " << net->getID()
    << " " << net->getLSB()
    << " " << net->getMSB();
  if (not net->isAnonymous()) {
    stream << " " << net->getName().getString();
  }
  stream << std::endl;
}

void dumpNet(const SNLNet* net, std::ostream& stream) {
  if (auto bus = dynamic_cast<const SNLBusNet*>(net)) {
    dumpBusNet(bus, stream);
  } else {
    auto scalar = static_cast<const SNLScalarNet*>(net);
    dumpScalarNet(scalar, stream);
  }
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

void dumpParameter(const SNLParameter* parameter, std::ostream& stream) {
  stream << SNLDump::Tag::Parameter
    << " " << parameter->getName().getString()
    << " " << parameter->getValue()
    << std::endl;
}

void dumpDesignInterface(const SNLDesign* design, std::ostream& stream) {
  stream << SNLDump::Tag::Design
    << " " << design->getLibrary()->getID()
    << " " << design->getID()
    << " " << design->getName().getString() << std::endl;
  for (auto term: design->getTerms()) {
    dumpTerm(term, stream);
  }
  for (auto parameter: design->getParameters()) {
    dumpParameter(parameter, stream);
  }
}

void dumpInstance(const SNLInstance* instance, std::ostream& stream) {
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

void dumpDesignContent(const SNLDesign* design, std::ostream& stream) {
  stream << SNLDump::Tag::Design
    << " " << design->getLibrary()->getID()
    << " " << design->getID()
    << " " << design->getName().getString() << std::endl;
  for (auto instance: design->getInstances()) {
    dumpInstance(instance, stream);
  }
  for (auto net: design->getNets()) {
    dumpNet(net, stream);
  }
}

void dumpLibraryInterface(const SNLLibrary* library, const std::filesystem::path& path) {
  //create stream
  std::string libName = "ilib" + std::to_string(library->getID());
  std::filesystem::path dumpPath(path/libName);
  std::ofstream stream(dumpPath);
  stream << SNLDump::Tag::Library << " " << library->getID();
  if (not library->isAnonymous()) {
    stream << " " << library->getName().getString();
  }
  stream << std::endl;
  for (auto design: library->getDesigns()) {
    dumpDesignInterface(design, stream);
  }
}

void dumpLibraryContent(const SNLLibrary* library, const std::filesystem::path& path) {
  //create stream
  std::string libName = "lib" + std::to_string(library->getID());
  std::filesystem::path dumpPath(path/libName);
  std::ofstream stream(dumpPath);
  stream << SNLDump::Tag::Library << " " << library->getID();
  if (not library->isAnonymous()) {
    stream << " " << library->getName().getString();
  }
  stream << std::endl;
  for (auto design: library->getDesigns()) {
    dumpDesignContent(design, stream);
  }
}

void dumpLibrary(const SNLLibrary* library, const std::filesystem::path& path) {
  std::string dirName = "lib" + std::to_string(library->getID());
  std::filesystem::path dirPath(path/dirName);
  //create dir for library
  std::filesystem::create_directory(dirPath);
  dumpLibraryInterface(library, dirPath);
  dumpLibraryContent(library, dirPath);
  for (auto library: library->getLibraries()) {
    dumpLibrary(library, dirPath);
  }
}

void dumpDB(const SNLDB* db, const std::filesystem::path& path) {
  std::string dbName = "db" + std::to_string(db->getID());
  std::filesystem::path dbPath(path/dbName);
  //create dir for DB
  std::filesystem::create_directory(dbPath);
  for (auto library: db->getLibraries()) {
    dumpLibrary(library, dbPath);
  }
}

}

namespace naja { namespace SNL {

void SNLDump::dumpUniverse(const std::filesystem::path& path) {
  //First round dump DB, Library and Design Interfaces
  auto universe = SNLUniverse::get();
  if (not universe) {
    return;
  }

  //create directory
  if (std::filesystem::exists(path)) {
    std::ostringstream reason;
    reason << "cannot dump " << universe->getString() << " as " << path.string() << " exists already";
    throw SNLDumpException(reason.str());
  }
  std::filesystem::create_directory(path);

  //start manifest
  //auto manifestStream = SNLDumpManifest::start(path);

  auto dbs = universe->getUserDBs();
  for (auto db: dbs) {
    dumpDB(db, path);
  }

#if 0
  
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
#endif
}

}} // namespace SNL // namespace naja
