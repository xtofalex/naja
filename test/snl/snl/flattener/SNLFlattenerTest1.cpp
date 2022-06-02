#include "gtest/gtest.h"

#include <filesystem>
#include <fstream>

#include "SNLNetlist0.h"

#include "SNLUniverse.h"

#include "SNLFlattener.h"
#include "SNLFlattenerInstanceTree.h"
#include "SNLFlattenerInstanceTreeNode.h"
#include "SNLFlattenerNetForest.h"

using namespace naja::SNL;

#ifndef FLATTENER_DUMP_PATHS
#define FLATTENER_DUMP_PATHS "Undefined"
#endif

class SNLFlattenerTest1: public ::testing::Test {
  //Test constant nets
  protected:
    void SetUp() override {
      SNLUniverse* universe = SNLUniverse::create();
      db_ = SNLDB::create(universe);
      auto modelLib = SNLLibrary::create(db_);
      auto inv = SNLDesign::create(modelLib, SNLName("INV"));
      top_ = SNLNetlist0::create(db_);
    }
    void TearDown() override {
      SNLUniverse::get()->destroy();
    }
  protected:
    SNLDB*      db_;
    SNLDesign*  top_;
};

TEST_F(SNLFlattenerTest0, test0) {
  ASSERT_NE(nullptr, top_);
  SNLFlattener flattener;
  flattener.process(top_);

  SNLFlattenerInstanceTree* tree = flattener.getInstanceTree();
  ASSERT_NE(nullptr, tree);
  std::filesystem::path dumpsPath(FLATTENER_DUMP_PATHS);
  std::filesystem::path instanceTreePath = dumpsPath/"SNLFlattenerTest0Test0InstanceTree.debug";
  std::ofstream instanceTreeFile;
  instanceTreeFile.open(instanceTreePath, std::ios::out);
  tree->print(instanceTreeFile);

  SNLFlattenerNetForest* forest = flattener.getNetForest();
  ASSERT_NE(nullptr, forest);
  std::filesystem::path netForestPath = dumpsPath/"SNLFlattenerTest0Test0NetForest.debug";
  std::ofstream netForestFile;
  netForestFile.open(netForestPath, std::ios::out);
  forest->print(netForestFile);

  auto root = tree->getRoot();
  ASSERT_NE(nullptr, root);
  auto ins0Node = root->getChildNode(SNLNetlist0::getTopIns0());
  ASSERT_NE(nullptr, ins0Node);
  auto ins1Node = root->getChildNode(SNLNetlist0::getTopIns1());
  ASSERT_NE(nullptr, ins1Node);
  EXPECT_EQ(root, ins0Node->getParent());
  EXPECT_EQ(root, ins1Node->getParent());
  EXPECT_EQ(tree, ins0Node->getTree());
  EXPECT_EQ(tree, ins1Node->getTree());
}