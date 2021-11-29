#include "SNLLibrary.h"

#include "SNLDB.h"
#include "SNLException.h"

namespace SNL {

SNLLibrary::Type::Type(const TypeEnum& typeEnum):
  typeEnum_(typeEnum) 
{}

std::string SNLLibrary::Type::getString() const {
  switch (typeEnum_) {
    case Type::Standard: return "Standard";
    case Type::InDB0: return "InDB0";
    case Type::Primitives: return "Primitives";
  }
  return "Unknown";
}

SNLLibrary::SNLLibrary(SNLDB* parent, const Type& type, const SNLName& name):
  super(),
  name_(name),
  type_(type),
  parent_(parent),
  isRootLibrary_(true)
{}

SNLLibrary::SNLLibrary(SNLLibrary* parent, const Type& type, const SNLName& name):
  super(),
  name_(name),
  type_(type),
  parent_(parent),
  isRootLibrary_(false)
{}

SNLLibrary* SNLLibrary::create(SNLDB* db, const SNLName& name) {
  preCreate(db, Type::Standard, name);
  SNLLibrary* library = new SNLLibrary(db, Type::Standard, name);
  library->postCreate();
  return library;
}

SNLLibrary* SNLLibrary::create(SNLDB* db, const Type& type, const SNLName& name) {
  preCreate(db, type, name);
  SNLLibrary* library = new SNLLibrary(db, type, name);
  library->postCreate();
  return library;
}

SNLLibrary* SNLLibrary::create(SNLLibrary* parent, const SNLName& name) {
  preCreate(parent, Type::Standard, name);
  SNLLibrary* library = new SNLLibrary(parent, Type::Standard, name);
  library->postCreate();
  return library;
}

SNLLibrary* SNLLibrary::create(SNLLibrary* parent, const Type& type, const SNLName& name) {
  preCreate(parent, type, name);
  SNLLibrary* library = new SNLLibrary(parent, type, name);
  library->postCreate();
  return library;
}

void SNLLibrary::preCreate(SNLDB* db, const Type& type, const SNLName& name) {
  super::preCreate();
  if (not db) {
    throw SNLException("malformed SNLLibrary creator with NULL db argument");
  }
  if (not name.empty() and db->getLibrary(name)) {
    std::string reason = "SNLDB " + db->getString() + " contains already a SNLLibrary named: " + name;
    throw SNLException(reason);
  }
}

void SNLLibrary::preCreate(SNLLibrary* parentLibrary, const Type& type, const SNLName& name) {
  super::preCreate();
  if (not parentLibrary) {
    throw SNLException("malformed SNLLibrary creator with NULL parent library argument");
  }
  if (type not_eq parentLibrary->getType()) {
    throw SNLException("non compatible types in library constructor");
  }
  if (not name.empty() and parentLibrary->getLibrary(name)) {
    std::string reason = "SNLLibrary " + parentLibrary->getString() + " contains already a SNLLibrary named: " + name;
    throw SNLException(reason);
  }
}

void SNLLibrary::postCreate() {
  super::postCreate();
  if (isRootLibrary()) {
    static_cast<SNLDB*>(parent_)->addLibrary(this);
  } else {
    static_cast<SNLLibrary*>(parent_)->addLibrary(this);
  }
}

void SNLLibrary::commonPreDestroy() {
  struct destroyDesignFromLibrary {
    void operator()(SNLDesign* design) {
      design->destroyFromLibrary();
    }
  };
  designs_.clear_and_dispose(destroyDesignFromLibrary());
  struct destroyLibraryFromLibrary {
    void operator()(SNLLibrary* library) {
      library->destroyFromParent();
    }
  };
  libraries_.clear_and_dispose(destroyLibraryFromLibrary());
  super::preDestroy();
}

void SNLLibrary::destroyFromParent() {
  commonPreDestroy();
  delete this;
}

void SNLLibrary::preDestroy() {
  if (isRootLibrary()) {
    static_cast<SNLDB*>(parent_)->removeLibrary(this);
  } else {
    static_cast<SNLLibrary*>(parent_)->removeLibrary(this);
  }
  commonPreDestroy();
}

SNLDB* SNLLibrary::getDB() const {
  if (isRootLibrary()) {
    return static_cast<SNLDB*>(parent_);
  } else {
    return getParentLibrary()->getDB();
  }
}

SNLLibrary* SNLLibrary::getParentLibrary() const {
  if (not isRootLibrary()) {
    return static_cast<SNLLibrary*>(parent_);
  }
  return nullptr;
}

SNLLibrary* SNLLibrary::getLibrary(SNLID::LibraryID id) {
  auto it = libraries_.find(SNLID(getDB()->getID(), id), SNLIDComp<SNLLibrary>());
  if (it != libraries_.end()) {
    return &*it;
  }
  return nullptr;
}

SNLLibrary* SNLLibrary::getLibrary(const SNLName& name) {
  auto lit = libraryNameIDMap_.find(name);
  if (lit != libraryNameIDMap_.end()) {
    SNLID::LibraryID id = lit->second;
    return getLibrary(id);
  }
  return nullptr;
}

SNLCollection<SNLLibrary*> SNLLibrary::getLibraries() const {
  return SNLCollection<SNLLibrary*>(new SNLIntrusiveConstSetCollection<SNLLibrary, SNLLibraryLibrariesHook>(&libraries_));
}

SNLDesign* SNLLibrary::getDesign(SNLID::DesignID id) {
  auto it = designs_.find(SNLID(getDB()->getID(), getID(), id), SNLIDComp<SNLDesign>());
  if (it != designs_.end()) {
    return &*it;
  }
  return nullptr;
}

SNLDesign* SNLLibrary::getDesign(const SNLName& name) {
  auto dit = designNameIDMap_.find(name);
  if (dit != designNameIDMap_.end()) {
    SNLID::DesignID id = dit->second;
    return getDesign(id);
  }
  return nullptr;
}

SNLCollection<SNLDesign*> SNLLibrary::getDesigns() const {
  return SNLCollection<SNLDesign*>(new SNLIntrusiveConstSetCollection<SNLDesign, SNLLibraryDesignsHook>(&designs_));
}

void SNLLibrary::addLibrary(SNLLibrary* library) {
  library->id_ = getDB()->nextLibraryID_++;
  libraries_.insert(*library);
  if (not library->isAnonymous()) {
    libraryNameIDMap_[library->getName()] = library->id_;
  }
}

void SNLLibrary::removeLibrary(SNLLibrary* library) {
  if (not library->isAnonymous()) {
    libraryNameIDMap_.erase(library->getName());
  }
  libraries_.erase(*library);
}

void SNLLibrary::addDesign(SNLDesign* design) {
  if (designs_.empty()) {
    design->id_ = 0;
  } else {
    auto it = designs_.rbegin();
    SNLDesign* lastDesign = &(*it);
    SNLID::DesignID designID = lastDesign->id_+1;
    design->id_ = designID;
  }
  designs_.insert(*design);
  if (not design->isAnonymous()) {
    designNameIDMap_[design->getName()] = design->id_;
  }
}

void SNLLibrary::removeDesign(SNLDesign* design) {
  if (not design->isAnonymous()) {
    designNameIDMap_.erase(design->getName());
  }
  designs_.erase(*design);
}

constexpr const char* SNLLibrary::getTypeName() const {
  return "SNLLibrary";
}

std::string SNLLibrary::getString() const {
  return getName();
}

std::string SNLLibrary::getDescription() const {
  return "<" + std::string(getTypeName()) + " " + name_ + ">";  
}

SNLID SNLLibrary::getSNLID() const {
  return SNLID(getDB()->getID(), getID());
}

}
