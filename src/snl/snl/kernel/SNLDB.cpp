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

#include "SNLDB.h"

#include <list>
#include <iostream>
#include <sstream>

#include "SNLUniverse.h"
#include "SNLDB0.h"
#include "SNLException.h"

namespace naja { namespace SNL {

SNLDB::SNLDB(SNLID::DBID id):
  id_(id)
{}

SNLDB* SNLDB::create(SNLUniverse* universe) {
  preCreate(universe);
  SNLDB* db = new SNLDB();
  db->postCreateAndSetID(universe);
  return db;
}

SNLDB* SNLDB::create(SNLUniverse* universe, SNLID::DBID id) {
  preCreate(universe, id);
  SNLDB* db = new SNLDB(id);
  db->postCreate(universe);
  return db;
}

void SNLDB::preCreate(SNLUniverse* universe) {
  super::preCreate();
  if (not universe) {
    throw SNLException("DB creation: NULL Universe");
  }
}

void SNLDB::preCreate(SNLUniverse* universe, SNLID::DBID id) {
  preCreate(universe);
  if (SNLUniverse::get()->getDB(id)) {
    throw SNLException("DB collision");
  }
}

void SNLDB::postCreateAndSetID(SNLUniverse* universe) {
  super::postCreate();
  universe->addDBAndSetID(this);
}

void SNLDB::postCreate(SNLUniverse* universe) {
  super::postCreate();
  universe->addDB(this);
}

void SNLDB::commonPreDrestroy() {
#ifdef SNL_DESTROY_DEBUG
  std::cerr << "Destroying " << getDescription() << std::endl; 
#endif
  struct destroyLibraryFromDB {
    void operator()(SNL::SNLLibrary* library) {
      library->destroyFromDB();
    }
  };
  //First delete standard primitives
  //collect standard libraries
  using Libraries = std::list<SNLLibrary*>;
  Libraries nonRootLibraries;
  Libraries standardRootLibraries;
  for (auto it = libraries_.begin(); it!=libraries_.end(); ++it) {
    SNLLibrary* library = &*it;
    //destroy first root and standard library 
    if (not library->isRoot()) {
      nonRootLibraries.push_back(library);
    } else if (library->isStandard()) {
      standardRootLibraries.push_back(library);
    } 
  }
  for (auto library: nonRootLibraries) {
    libraries_.erase(*library);
  }
  for (auto library: standardRootLibraries) {
    libraries_.erase_and_dispose(*library, destroyLibraryFromDB());
  }

  //remove all the rest
  libraries_.clear_and_dispose(destroyLibraryFromDB());
  libraryNameIDMap_.clear();
  super::preDestroy();
}

void SNLDB::preDestroy() {
  commonPreDrestroy();
  SNLUniverse::get()->removeDB(this);
}

void SNLDB::destroyFromUniverse() {
  commonPreDrestroy();
  delete this;
}

void SNLDB::addLibraryAndSetID(SNLLibrary* library) {
  if (libraries_.empty()) {
    library->id_ = 0;
  } else {
    auto it = libraries_.rbegin();
    SNLLibrary* lastLibrary = &(*it);
    library->id_ = lastLibrary->id_;
    ++library->id_;
  }
  addLibrary(library);
}

void SNLDB::addLibrary(SNLLibrary* library) {
  libraries_.insert(*library);
  libraryNameIDMap_[library->getName()] = library->id_;
}

void SNLDB::removeLibrary(SNLLibrary* library) {
  libraries_.erase(*library);
  libraryNameIDMap_.erase(library->getName());
}

SNLLibrary* SNLDB::getLibrary(SNLID::LibraryID id) const {
  auto it = libraries_.find(SNLID(getID(), id), SNLIDComp<SNLLibrary>());
  if (it != libraries_.end()) {
    return const_cast<SNLLibrary*>(&*it);
  }
  return nullptr;
}

SNLLibrary* SNLDB::getLibrary(const SNLName& name) const {
  auto it = libraryNameIDMap_.find(name);
  if (it != libraryNameIDMap_.end()) {
    SNLID::LibraryID id = it->second;
    return getLibrary(id);
  }
  return nullptr;
}

SNLDesign* SNLDB::getDesign(const SNLID::DBDesignReference& designReference) const {
  auto library = getLibrary(designReference.libraryID_);
  if (library) {
    return library->getDesign(designReference.designID_);
  }
  return nullptr;
}

SNLDesign* SNLDB::getDesign(const SNLName& name) const {
  for (auto library: getLibraries()) {
    auto design = library->getDesign(name);
    if (design) {
      return design;
    }
  }
  return nullptr;
}

NajaCollection<SNLLibrary*> SNLDB::getGlobalLibraries() const {
  return NajaCollection(new NajaIntrusiveSetCollection(&libraries_));
}

NajaCollection<SNLLibrary*> SNLDB::getLibraries() const {
  auto filter = [](const SNLLibrary* l) { return l->isRoot(); };
  return getGlobalLibraries().getSubCollection(filter);
}

SNLID SNLDB::getSNLID() const {
  return SNLID(id_);
}

bool SNLDB::isTopDB() const {
  return SNLUniverse::get()->getTopDB() == this;
}

SNLDesign* SNLDB::getTopDesign() const {
  return topDesign_;
}

void SNLDB::setTopDesign(SNLDesign* design) {
  if (design and design->getDB() not_eq this) {
    std::ostringstream reason;
    reason << "Impossible setTopDesign call with ";
    reason << design->getString() << " and ";
    reason << getString();
    throw SNLException(reason.str());
  }
  topDesign_ = design;
}

//LCOV_EXCL_START
const char* SNLDB::getTypeName() const {
  return "SNLDB";
}
//LCOV_EXCL_STOP

//LCOV_EXCL_START
std::string SNLDB::getString() const {
  return "<" + std::string(getTypeName()) + " " + std::to_string(getID()) + ">";  
}
//LCOV_EXCL_STOP

//LCOV_EXCL_START
std::string SNLDB::getDescription() const {
  return "<" + std::string(getTypeName()) + " " + std::to_string(getID()) + ">";  
}
//LCOV_EXCL_STOP

}} // namespace SNL // namespace naja
