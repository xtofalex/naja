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

#ifndef __SNL_DUMP_H_
#define __SNL_DUMP_H_

#include <filesystem>
#include <string>

namespace naja { namespace SNL {

class SNLDesign;

class SNLDump {
  public:
    struct Version {
      Version() = delete;
      Version(unsigned major, unsigned minor, unsigned revision):
        major_(major), minor_(minor), revision_(revision)
      {}
      unsigned major_;
      unsigned minor_;
      unsigned revision_;
      unsigned getMajor() const    { return major_; }
      unsigned getMinor() const    { return minor_; }
      unsigned getRevision() const { return revision_; }
      std::string getString();
    };

    static const Version  version_;
    static Version getVersion() { return version_; }

    class Tag {
      public:
        static constexpr char Design      { 'D' };
        static constexpr char ScalarTerm  { 'T' };
        static constexpr char BusTerm     { 'B' };
        static constexpr char Net         { 'N' };
        static constexpr char Instance    { 'I' };
        static constexpr char Parameter   { 'P' };
    };

    static void dump(const SNLDesign* top, const std::filesystem::path& path);
    static void load(const std::filesystem::path& path);
};

}} // namespace SNL // namespace naja

#endif // __SNL_DUMP_H_