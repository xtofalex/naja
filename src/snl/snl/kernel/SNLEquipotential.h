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

#ifndef __SNL_EQUIPOTENTIAL_H_
#define __SNL_EQUIPOTENTIAL_H_

#include <set>

namespace naja { namespace SNL {

class SNLNetComponent;
class SNLNetComponentOccurrence;
class SNLInstTermOccurrence;

class SNLEquipotential {
  public:
    SNLEquipotential()=delete;
    SNLEquipotential(const SNLEquipotential&)=delete;
    using InstTermOccurrences = std::set<SNLInstTermOccurrence>;

    SNLEquipotential(SNLNetComponent* netComponent);
    SNLEquipotential(const SNLNetComponentOccurrence& netComponentOccurrence);
  private:
    InstTermOccurrences instTermOccurrences_  {};
};

}} // namespace SNL // namespace naja

#endif // __SNL_EQUIPOTENTIAL_H_