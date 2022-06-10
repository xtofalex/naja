#include "gtest/gtest.h"

#include "SNLUniverse.h"
#include "SNLFlattener.h"
#include "SNLNetlist0.h"

#include "DNLDB.h"

using namespace naja::SNL;
using namespace naja::DNL;

class DNLDBTest: public ::testing::Test {
  public:
    void SetUp() override {
      SNLUniverse* universe = SNLUniverse::create();
      db_ = SNLDB::create(universe);
      top_ = SNLNetlist0::create(db_);
    }
    void TearDown() override {
      SNLUniverse::get()->destroy();
    }
  protected:
    SNLDB*      db_;
    SNLDesign*  top_;
};

TEST_F(DNLDBTest, test) {
  ASSERT_NE(nullptr, top_);
  SNLFlattener flattener;
  flattener.process(top_);

  //DNLDB* dnldb = DNLDB
}
