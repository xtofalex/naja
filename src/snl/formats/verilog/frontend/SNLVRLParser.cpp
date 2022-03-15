#include "SNLVRLParser.h"

#include <sstream>

#include "verilog_reader.h"

#include "SNLLibrary.h"
#include "SNLDesign.h"
#include "SNLBusTerm.h"
#include "SNLScalarTerm.h"
#include "SNLBusNet.h"
#include "SNLScalarNet.h"
#include "SNLVRLParserException.h"

namespace {
using namespace naja::SNL;

SNLTerm::Direction getSNLDirection(const verilog::PortDirection direction) {
  switch (direction) {
    case verilog::PortDirection::INPUT:
      return SNLTerm::Direction::Input;
    case verilog::PortDirection::OUTPUT:
      return SNLTerm::Direction::Output;
    case verilog::PortDirection::INOUT:
      return SNLTerm::Direction::InOut;
  }
}
    

struct SNLVerilogParser: public verilog::ParserVerilogInterface {
  SNLVerilogParser(SNLLibrary* library): verilog::ParserVerilogInterface(), library_(library) {}

  void add_module(std::string&& name) override {
    design_ = SNLDesign::create(library_, SNLName(name));
  }

  void add_port(verilog::Port&& port) override {
    SNLTerm::Direction direction = getSNLDirection(port.dir);
    assert(port.names.size() == 1);
    std::string name = port.names[1];
    if (port.beg != -1 and port.end != -1) {
      SNLBusTerm::create(design_, direction, port.beg, port.end, SNLName(name));
    } else {
      SNLScalarTerm::create(design_, direction, SNLName(name));
    }
  }

  void add_net(verilog::Net&& net) override {
    assert(net.names.size() == 1);
    std::string name = net.names[1];
    if (net.beg != -1 and net.end != -1) {
      SNLBusNet::create(design_, net.beg, net.end, SNLName(name));
    } else {
      SNLScalarNet::create(design_, SNLName(name));
    }
  }

  void add_assignment(verilog::Assignment&&) override {
  }

  void add_instance(verilog::Instance&& instance) override {
    std::string instanceName = instance.inst_name;
    SNLDesign* model = library_->getDesign(SNLName(instance.module_name));
    if (not model) {
      std::ostringstream reason;
      reason << "Unknown model " << instance.module_name
        << " for instance " << instanceName << std::endl; 
      throw SNLVRLParserException(reason.str());
    }
    SNLInstance::create(design_, model, SNLName(instanceName));
  }

  SNLLibrary* library_  {nullptr};
  SNLDesign*  design_   {nullptr};
};

}

namespace naja { namespace SNL {

void SNLVRLParser::parse(SNLLibrary* library, const std::filesystem::path& filePath) {
  SNLVerilogParser parser(library);
  parser.read(filePath);
};

}} // namespace SNL // namespace naja
