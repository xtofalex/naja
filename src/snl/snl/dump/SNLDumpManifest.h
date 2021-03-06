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

#ifndef __SNL_DUMP_MANIFEST_H_
#define __SNL_DUMP_MANIFEST_H_

#include "SNLDump.h"

namespace naja { namespace SNL {

class SNLDumpManifest {
  public:
    SNLDump::Version getVersion() const { return version_; }
    static SNLDumpManifest load(const std::filesystem::path& snlDir);
  private:
    SNLDumpManifest(): version_(0, 0, 0) {}
    SNLDump::Version  version_;
};

class SNLDumpManifestDumper {
  public:
    static void dump(const SNLDesign* top, const std::filesystem::path& snlDir);
};

}} // namespace SNL // namespace naja

#endif // __SNL_DUMP_MANIFEST_H_