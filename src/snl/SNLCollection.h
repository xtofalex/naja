#ifndef __SNL_COLLECTION_H_
#define __SNL_COLLECTION_H_

#include <boost/intrusive/set.hpp>
#include <vector>

namespace SNL {

template<class Type>
class SNLBaseIterator {
  public:
    SNLBaseIterator(const SNLBaseIterator&) = default;
    SNLBaseIterator(SNLBaseIterator&&) = delete;
    virtual ~SNLBaseIterator() {}
    virtual Type getElement() const = 0;
    virtual void progress() = 0;
    virtual bool isEqual(const SNLBaseIterator<Type>* r) = 0;
    virtual bool isDifferent(const SNLBaseIterator<Type>* r) = 0;
    virtual SNLBaseIterator<Type>* clone() = 0;
  protected:
    SNLBaseIterator() = default;
};

template<class Type>
class SNLBaseCollection {
  public:
    virtual SNLBaseIterator<Type>* begin() const = 0;
    virtual SNLBaseIterator<Type>* end() const = 0;

    virtual size_t size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;

    SNLBaseCollection(const SNLBaseCollection&) = delete;
    SNLBaseCollection(SNLBaseCollection&&) = delete;
    virtual ~SNLBaseCollection() = default;
  protected:
    SNLBaseCollection() = default;
};

template<class Type, class HookType>
class SNLIntrusiveConstSetCollection: public SNLBaseCollection<Type*> {
  public:
    using super = SNLBaseCollection<Type*>;
    using Set = boost::intrusive::set<Type, HookType>;

    class SNLIntrusiveConstSetCollectionIterator: public SNLBaseIterator<Type*> {
      public:
        using SetIterator = typename Set::const_iterator;
        SNLIntrusiveConstSetCollectionIterator(const SNLIntrusiveConstSetCollectionIterator&) = default;
        SNLIntrusiveConstSetCollectionIterator(const Set* set, bool beginOrEnd=true): set_(set) {
          if (set_) {
            if (beginOrEnd) {
              it_ = set->begin();
            } else {
              it_ = set->end();
            }
          }
        }
        Type* getElement() const override { return const_cast<Type*>(&*it_); }
        void progress() override { ++it_; }
        bool isEqual(const SNLBaseIterator<Type*>* r) override {
          if (const SNLIntrusiveConstSetCollectionIterator* rit = dynamic_cast<const SNLIntrusiveConstSetCollectionIterator*>(r)) {
            return it_ == rit->it_;
          }
          return false;
        }
        bool isDifferent(const SNLBaseIterator<Type*>* r) override {
          if (const SNLIntrusiveConstSetCollectionIterator* rit = dynamic_cast<const SNLIntrusiveConstSetCollectionIterator*>(r)) {
            return it_ != rit->it_;
          }
          return true;
        }
        SNLBaseIterator<Type*>* clone() override {
          return new SNLIntrusiveConstSetCollectionIterator(*this);
        }
      private:
        const Set*  set_  {nullptr};
        SetIterator it_   {};
    };

    SNLBaseIterator<Type*>* begin() const override {
      return new SNLIntrusiveConstSetCollectionIterator(set_, true);
    }

    SNLBaseIterator<Type*>* end() const override {
      return new SNLIntrusiveConstSetCollectionIterator(set_, false);
    }

    SNLIntrusiveConstSetCollection() = delete;
    SNLIntrusiveConstSetCollection(const SNLIntrusiveConstSetCollection&) = delete;
    SNLIntrusiveConstSetCollection(SNLIntrusiveConstSetCollection&&) = delete;
    SNLIntrusiveConstSetCollection(const Set* set): super(), set_(set) {}

    size_t size() const noexcept override {
      if (set_) {
        return set_->size();
      }
      return 0;
    }

    bool empty() const noexcept override {
      if (set_) {
        return set_->empty();
      }
      return true;
    }

  private:
    const Set*  set_  {nullptr};
};

template<class Type, class HookType>
class SNLIntrusiveSetCollection: public SNLBaseCollection<Type*> {
  public:
    using super = SNLBaseCollection<Type*>;
    using Set = boost::intrusive::set<Type, HookType>;

    class SNLIntrusiveSetCollectionIterator: public SNLBaseIterator<Type*> {
      public:
        using SetIterator = typename Set::iterator;
        SNLIntrusiveSetCollectionIterator(Set* set, bool beginOrEnd=true): set_(set) {
          if (set_) {
            if (beginOrEnd) {
              it_ = set->begin();
            } else {
              it_ = set->end();
            }
          }
        }
        Type* getElement() const override { return &*it_; } 
        void progress() override { ++it_; }
        bool isEqual(const SNLBaseIterator<Type*>* r) override {
          if (const SNLIntrusiveSetCollectionIterator* rit = dynamic_cast<const SNLIntrusiveSetCollectionIterator*>(r)) {
            return it_ == rit->it_;
          }
          return false;
        }
        bool isDifferent(const SNLBaseIterator<Type*>* r) override {
          if (const SNLIntrusiveSetCollectionIterator* rit = dynamic_cast<const SNLIntrusiveSetCollectionIterator*>(r)) {
            return it_ != rit->it_;
          }
          return true;
        }
      private:
        Set*        set_  {nullptr};
        SetIterator it_   {};
    };

    SNLIntrusiveSetCollection() = delete;
    SNLIntrusiveSetCollection(const SNLIntrusiveSetCollection&) = delete;
    SNLIntrusiveSetCollection(SNLIntrusiveSetCollection&&) = delete;
    SNLIntrusiveSetCollection(Set* set): super(), set_(set) {}

    SNLBaseIterator<Type*>* begin() const override {
      return new SNLIntrusiveSetCollectionIterator(set_, true);
    }
    SNLBaseIterator<Type*>* end() const override {
      return new SNLIntrusiveSetCollectionIterator(set_, false);
    }

    size_t size() const noexcept override {
      if (set_) {
        return set_->size();
      }
      return 0;
    }

    bool empty() const noexcept override {
      if (set_) {
        return set_->empty();
      }
      return true;
    }
  private:
    Set*  set_  {nullptr};
};

template<class Type>
class SNLVectorCollection: public SNLBaseCollection<Type> {
  public:
    using super = SNLBaseCollection<Type>;
    using Vector = std::vector<Type>;

    class SNLVectorCollectionIterator: public SNLBaseIterator<Type> {
      public:
        using VectorIterator = typename Vector::const_iterator;
        SNLVectorCollectionIterator(const Vector* bits, bool beginOrEnd=true): bits_(bits) {
          if (bits_) {
            if (beginOrEnd) {
              it_ = bits->begin();
            } else {
              it_ = bits->end();
            }
          }
        }
        SNLVectorCollectionIterator(SNLVectorCollectionIterator&) = default;
        SNLBaseIterator<Type>* clone() override {
          return new SNLVectorCollectionIterator(*this);
        }
        Type getElement() const override { return *it_; } 
        void progress() override { ++it_; }
        bool isEqual(const SNLBaseIterator<Type>* r) override {
          if (const SNLVectorCollectionIterator* rit = dynamic_cast<const SNLVectorCollectionIterator*>(r)) {
            return it_ == rit->it_;
          }
          return false;
        }
        bool isDifferent(const SNLBaseIterator<Type>* r) override {
          if (const SNLVectorCollectionIterator* rit = dynamic_cast<const SNLVectorCollectionIterator*>(r)) {
            return it_ != rit->it_;
          }
          return true;
        }
      private:
        const Vector*   bits_ {nullptr};
        VectorIterator  it_   {};
    };

    SNLVectorCollection() = delete;
    SNLVectorCollection(const SNLVectorCollection&) = delete;
    SNLVectorCollection(SNLVectorCollection&&) = delete;
    SNLVectorCollection(const Vector* bits): super(), bits_(bits) {}

    SNLBaseIterator<Type>* begin() const override {
      return new SNLVectorCollectionIterator(bits_, true);
    }
    SNLBaseIterator<Type>* end() const override {
      return new SNLVectorCollectionIterator(bits_, false);
    }

    size_t size() const noexcept override {
      if (bits_) {
        return bits_->size();
      }
      return 0;
    }

    bool empty() const noexcept override {
      if (bits_) {
        return bits_->empty();
      }
      return true;
    }
  private:
    const Vector* bits_ {nullptr};
};

#if 0

template<class Type, SubType> class SNLSubTypeCollection: public SNLCollection<SubType> {
  public:
    using super = SNLCollection<SubType>;

    SNLSubTypeCollection(): super(), collection_ {}
    SNLSubTypeCollection(const SNLSubTypeCollection&) = delete;
    SNLSubTypeCollection& operator=(const SNLSubTypeCollection&) = delete;

    public: virtual Hurricane::Locator<SubType>* getLocator() const
    // ************************************************************
    {
        return new Locator(_collection);
    }


};

#endif

template<class Type>
class SNLCollection {
  public:
    class Iterator: public std::iterator<std::input_iterator_tag, Type> {
      public:
        Iterator() = delete;
        Iterator(const Iterator& it) {
          if (it.baseIt_) {
            baseIt_ = it.baseIt_->clone();
          }
        }
        Iterator(SNLBaseIterator<Type>* iterator): baseIt_(iterator) {}
        ~Iterator() { if (baseIt_) { delete baseIt_; } }

        Iterator& operator++() { baseIt_->progress(); return *this; }

        Type operator*() const { return baseIt_->getElement(); }

        bool operator==(const Iterator& r) const { return baseIt_->isEqual(r.baseIt_); }
        bool operator!=(const Iterator& r) const { return baseIt_->isDifferent(r.baseIt_); }
      private:
        SNLBaseIterator<Type>* baseIt_ {nullptr};
    };

    Iterator begin() { return Iterator(collection_->begin()); }
    Iterator end() { return Iterator(collection_->end()); }

    template<class SubType> SNLBaseCollection<SubType> getSubCollection() const {
      return SubTypeCollection<Type, SubType>(this);
    }

    SNLCollection() = delete;
    SNLCollection(const SNLBaseCollection<Type>* collection): collection_(collection) {}
    SNLCollection(const SNLCollection&) = delete;
    SNLCollection(SNLCollection&&) = delete;
    virtual ~SNLCollection() { delete collection_; }

    size_t size() const noexcept { if (collection_) { return collection_->size(); } return 0; }
    bool empty() const noexcept { if (collection_) { return collection_->empty(); } return true; }
  private:
    const SNLBaseCollection<Type>*  collection_ {nullptr};
};

}

#endif /* __SNL_COLLECTION_H_ */
