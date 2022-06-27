/*
 * Copyright 2022 The Naja Authors.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __DNLDB_H_
#define __DNLDB_H_

#include <vector>
#include "SNLID.h"

namespace naja { 

namespace SNL {
  class SNLInstance;
}  

namespace DNL {

class DNLDB {
  /**
   * @brief DNLDB 
   * 
   * Top:
   * SNLID
   * 
   * Top Terminals:
   * vector<SNL::TermID, begin>
   * 
   * Instances:
   * vector<SNL::InstanceOccurrence>, begin, end>
   * [ SNL::InstanceOccurrence, 12, 56 ] 
   * 
   * Terminals
   * Const0 Equi == Index 0
   * Const1 Equi == Index 1
   * vector<EquiID>
   * 
   * Equis:
   * EquiType: Standard, NoDriver, Const0, Const1
   * vector<SNL::NetOccurrence, EquiType begin, end>
   * [ SNL::NetOccurrence, Const0, 34, 78]
   * If Type == Standard, first id is driver
   * 
   * Browsing through DB:
   * - Start from Top terminal
   * - get EquiID
   * - get EquiType,  
   * 
   *    
   * 
   *    FlatEquis
   *    [ 0 | 1 | 34 56 67 34 14 | 0 10 45 36 67 | [] [] [] ]
   * 
   *          TOP
   *       A       B
   *     p1 p2   p3 p4
   * 
   * 
   * 
   *    InstancesIndex: Table of pairs
   *    [ DBID LibraryID InstanceID ]
   *    [ DBID LibraryID InstanceID ]
   *    [ DBID LibraryID InstanceID ]
   *    [ DBID LibraryID InstanceID ]
   * 
   *    FlatInstances
   *    [ [SNLInstanceID parentId [childID childID childID] startTerminalID stopTerminalID] |     ] 
   * 
   *    FlatTerminals
   *      .... 34 ....
   *    [ |    2        |   ]
   *           4
   */          

  public:
    friend class DNLSNLConstructor;
    using SNLInstanceIDs = std::vector<SNL::SNLID::DesignObjectID>;
    using DNLInstances = std::vector<size_t>;
    //using DNLInstances = std::vector<DNLInstance>;
    //using DNLTerminals = std::vector<DNLTerm>;
    //using DNLEquis = std::vector<DNLEqui>;
    //using DNLEquisConnectivity = std::vector<size_t>;

    static DNLDB* create();
     
    SNLInstanceIDs getInstancePath(size_t index) const;

  private:
    size_t pushInstance(const SNL::SNLInstance* instance, size_t parentIndex);
    void pushLeaf(const SNL::SNLInstance* instance, size_t parentIndex);

    SNLInstanceIDs  snlInstanceIDs_;
    DNLInstances    instances_;
    DNLInstances    leaves_;
    //DNLTerminals  terminals_;
    //DNLEquis      equis_;
};

}} //namespace DNL // namespace naja

#endif // __DNL_DB_H_