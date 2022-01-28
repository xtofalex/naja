#include "SNLDB.h"

#include <list>

#include "SNLUniverse.h"

namespace SNL {

SNLDB::SNLDB(SNLUniverse* universe):
  universe_(universe)
{}

SNLDB* SNLDB::create(SNLUniverse* universe) {
  preCreate();
  SNLDB* db = new SNLDB(universe);
  db->postCreate();
  return db;
}

void SNLDB::preCreate() {
  super::preCreate();
}

void SNLDB::postCreate() {
  super::postCreate();
  universe_->addDB(this);
}

void SNLDB::commonPreDrestroy() {
  struct destroyLibraryFromDB {
    void operator()(SNL::SNLLibrary* library) {
      library->destroyFromParent();
    }
  };
  //First delete standard primitives
  //collect standard libraries
  using StandardLibraries = std::list<SNLLibrary*>;
  StandardLibraries standardLibraries;
  for (auto it = libraries_.begin(); it!=libraries_.end(); ++it) {
    SNLLibrary* library = &*it;
    if (library->isStandard()) {
      standardLibraries.push_back(library);
    }
  }
  for (auto library: standardLibraries) {
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

void SNLDB::addLibrary(SNLLibrary* library) {
  library->id_ = nextLibraryID_++;
  libraries_.insert(*library);
  libraryNameIDMap_[library->getName()] = library->id_;
}

void SNLDB::removeLibrary(SNLLibrary* library) {
  libraries_.erase(*library);
  libraryNameIDMap_.erase(library->getName());
}

SNLLibrary* SNLDB::getLibrary(SNLID::LibraryID id) {
  auto it = libraries_.find(SNLID(getID(), id), SNLIDComp<SNLLibrary>());
  if (it != libraries_.end()) {
    return &*it;
  }
  return nullptr;
}

SNLLibrary* SNLDB::getLibrary(const SNLName& name) {
  auto it = libraryNameIDMap_.find(name);
  if (it != libraryNameIDMap_.end()) {
    SNLID::LibraryID id = it->second;
    return getLibrary(id);
  }
  return nullptr;
}

SNLCollection<SNLLibrary*> SNLDB::getLibraries() const {
  return SNLCollection<SNLLibrary*>(new SNLIntrusiveConstSetCollection<SNLLibrary, SNLDBLibrariesHook>(&libraries_));
}

SNLID SNLDB::getSNLID() const {
  return SNLID(id_);
}

constexpr const char* SNLDB::getTypeName() const {
  return "SNLDB";
}

std::string SNLDB::getString() const {
  return std::string();
}

std::string SNLDB::getDescription() const {
  return "<" + std::string(getTypeName()) + ">";  
}

}
