#include "gtest/gtest.h"

#include "SNLUniverse.h"
#include "SNLScalarTerm.h"
#include "SNLPrimitivesLoader.h"
#include "SNLException.h"
using namespace naja::SNL;

#ifndef SNL_PRIMITIVES_TEST_PATH
#define SNL_PRIMITIVES_TEST_PATH "Undefined"
#endif

class SNLPrimitivesTest0: public ::testing::Test {
  protected:
    void SetUp() override {
      SNLUniverse::create();
    }
    void TearDown() override {
      if (SNLUniverse::get()) {
        SNLUniverse::get()->destroy();
      }
    }
};

TEST_F(SNLPrimitivesTest0, test) {
  auto db = SNLDB::create(SNLUniverse::get());
  auto library = SNLLibrary::create(db, SNLLibrary::Type::Primitives, SNLName("PRIMS"));
  auto primitives0Path = std::filesystem::path(SNL_PRIMITIVES_TEST_PATH);
  primitives0Path /= "primitives0.py";
  SNLPrimitivesLoader::load(library, primitives0Path);
  ASSERT_EQ(1, library->getDesigns().size());
  auto lut4 = library->getDesign(SNLName("LUT4")); 
  EXPECT_TRUE(lut4->isPrimitive());
  ASSERT_NE(nullptr, lut4);
  ASSERT_EQ(5, lut4->getScalarTerms().size());
  using Terms = std::vector<SNLScalarTerm*>;
  Terms terms(lut4->getScalarTerms().begin(), lut4->getScalarTerms().end()); 
  ASSERT_EQ(5, terms.size());
  EXPECT_EQ("I0", terms[0]->getName().getString());
  EXPECT_EQ("I1", terms[1]->getName().getString());
  EXPECT_EQ("I2", terms[2]->getName().getString());
  EXPECT_EQ("I3", terms[3]->getName().getString());
  EXPECT_EQ("O", terms[4]->getName().getString());
  EXPECT_EQ(SNLTerm::Direction::Input, terms[0]->getDirection());
  EXPECT_EQ(SNLTerm::Direction::Input, terms[1]->getDirection());
  EXPECT_EQ(SNLTerm::Direction::Input, terms[2]->getDirection());
  EXPECT_EQ(SNLTerm::Direction::Input, terms[3]->getDirection());
  EXPECT_EQ(SNLTerm::Direction::Output,  terms[4]->getDirection());
}

TEST_F(SNLPrimitivesTest0, testError0) {
  auto db = SNLDB::create(SNLUniverse::get());
  auto library = SNLLibrary::create(db, SNLLibrary::Type::Primitives, SNLName("PRIMS"));
  auto primitives0Path = std::filesystem::path(SNL_PRIMITIVES_TEST_PATH);
  primitives0Path /= "wrong_path.py";
  //Wrong path
  EXPECT_THROW(SNLPrimitivesLoader::load(library, primitives0Path), SNLException);
  
  library->destroy();
  //non Primitives library
  library = SNLLibrary::create(db, SNLName("PRIMS"));
  EXPECT_THROW(SNLPrimitivesLoader::load(library, primitives0Path), SNLException);

  //faulty python script
  primitives0Path = std::filesystem::path(SNL_PRIMITIVES_TEST_PATH);
  primitives0Path /= "error0.py";
  EXPECT_THROW(SNLPrimitivesLoader::load(library, primitives0Path), SNLException);
}

TEST_F(SNLPrimitivesTest0, testError1) {
  auto db = SNLDB::create(SNLUniverse::get());
  auto library = SNLLibrary::create(db, SNLLibrary::Type::Primitives, SNLName("PRIMS"));
  //non python script
  auto primitives0Path = std::filesystem::path(SNL_PRIMITIVES_TEST_PATH);
  primitives0Path /= "error1.py";
  EXPECT_THROW(SNLPrimitivesLoader::load(library, primitives0Path), SNLException);
}