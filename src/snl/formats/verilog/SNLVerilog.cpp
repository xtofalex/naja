#include <iostream>

#include "SNLUniverse.h"
#include "SNLUtils.h"

#include "SNLVRLParser.h"
#include "SNLVRLDumper.h"

namespace {

void usage() {
  std::cerr << "snlverilog input.v output.v" << std::endl; 
}

}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    usage();
    exit(1);
  }

  std::filesystem::path inputPath(argv[1]);
  if (not std::filesystem::exists(inputPath)) {
    usage();
    exit(1);
  }

  std::filesystem::path outputPath(argv[2]);

  auto universe = naja::SNL::SNLUniverse::create();
  auto db = naja::SNL::SNLDB::create(universe);
  auto library = naja::SNL::SNLLibrary::create(db);

  naja::SNL::SNLVRLParser::parse(library, inputPath);
  naja::SNL::SNLUtils::SortedDesigns sortedDesigns;
  naja::SNL::SNLUtils::getDesignsSortedByHierarchicalLevel(library, sortedDesigns);
  if (not sortedDesigns.empty()) {
    const naja::SNL::SNLDesign* top = sortedDesigns[0].first;
    naja::SNL::SNLVRLDumper vrlDumper;
    vrlDumper.dumpDesign(top, outputPath);
  }

  return 0;
}
