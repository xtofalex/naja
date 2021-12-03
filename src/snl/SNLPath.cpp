#include "SNLPath.h"

#include "SNLSharedPath.h"
#include "SNLInstance.h"
#include "SNLException.h"

namespace SNL {

SNLPath::SNLPath(SNLSharedPath* sharedPath):
  sharedPath_(sharedPath)
{}

SNLPath::SNLPath(SNLInstance* instance): SNLPath() {
  if (instance) {
    sharedPath_ = instance->getSharedPath(nullptr);
    if (not sharedPath_) {
      sharedPath_ = new SNLSharedPath(instance);
    }
  }
}

SNLPath::SNLPath(SNLInstance* headInstance, const SNLPath& tailPath): SNLPath() {
  if (not headInstance) {
    throw SNLException("cannot create SNLPath with null head instance");
  }

  if (not tailPath.sharedPath_) {
    sharedPath_ = headInstance->getSharedPath(nullptr);
    if (not sharedPath_) {
      sharedPath_ = new SNLSharedPath(headInstance);
    } else {
      SNLSharedPath* tailSharedPath = tailPath.sharedPath_;
      if (tailSharedPath->getDesign() not_eq headInstance->getModel()) {
        throw SNLException("cannot create SNLPath: incompatible tail path");
      }
      sharedPath_ = headInstance->getSharedPath(tailSharedPath);
      if (not sharedPath_) {
        sharedPath_ = new SNLSharedPath(headInstance, tailSharedPath);
      }
    }
  }
}

SNLPath::SNLPath(const SNLPath& headPath, SNLInstance* tailInstance): SNLPath() {
  if (not tailInstance) {
    throw SNLException("Cant't create SNLPath: null tail instance");
  }

  if (not headPath.sharedPath_) {
    sharedPath_ = tailInstance->getSharedPath(nullptr);
    if (not sharedPath_) {
      sharedPath_ = new SNLSharedPath(tailInstance);
    } else {
      SNLInstance* headInstance = headPath.getHeadInstance();
      SNLSharedPath* tailSharedPath = SNLPath(headPath.getTailPath(), tailInstance).sharedPath_;
      sharedPath_ = headInstance->getSharedPath(tailSharedPath);
      if (not sharedPath_) {
        sharedPath_ = new SNLSharedPath(headInstance, tailSharedPath);
      }
    }
  }
}


SNLInstance* SNLPath::getHeadInstance() const {
  return sharedPath_?sharedPath_->getHeadInstance():nullptr;
}

SNLPath SNLPath::getTailPath() const {
  return SNLPath(sharedPath_?sharedPath_->getTailSharedPath():nullptr);
}

SNLPath SNLPath::getHeadPath() const {
  return SNLPath(sharedPath_?sharedPath_->getHeadSharedPath():nullptr);
}

SNLInstance* SNLPath::getTailInstance() const {
  return sharedPath_?sharedPath_->getTailInstance():nullptr;
}

bool SNLPath::empty() const {
  return not sharedPath_;
}

SNLDesign* SNLPath::getDesign() const {
  return sharedPath_?sharedPath_->getDesign():nullptr; 
}

SNLDesign* SNLPath::getModel() const {
  return sharedPath_?sharedPath_->getModel():nullptr; 
}

bool SNLPath::operator==(const SNLPath& path) const {
  return sharedPath_ == path.sharedPath_;
}

bool SNLPath::operator!=(const SNLPath& path) const {
  return sharedPath_ != path.sharedPath_;
}

}
