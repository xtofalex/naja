#ifndef __SNL_NETLIST0_H_
#define __SNL_NETLIST0_H_

#include <string>

namespace naja::SNL {
  class SNLDB;
  class SNLLibrary;
  class SNLDesign;
  class SNLInstance;
}

class SNLNetlist0 {
  public:
    static constexpr char DesignsLibName[]  { "DESIGNS" };
    static constexpr char TopName[]         { "Top" };
    static constexpr char TopIns0Name[]     { "ins0" };
    static constexpr char TopIns1Name[]     { "ins1" };
    
    static naja::SNL::SNLDesign* create(naja::SNL::SNLDB* db);
    static naja::SNL::SNLDB* getDB();
    static naja::SNL::SNLLibrary* getDesignsLib();
    static naja::SNL::SNLDesign* getTop();
    static naja::SNL::SNLInstance* getTopIns0();
    static naja::SNL::SNLInstance* getTopIns1();
};

#endif // __SNL_NETLIST0_H_