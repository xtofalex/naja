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

#include "SNLDump.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "SNLUniverse.h"

#include "SNLDumpManifest.h"
#include "SNLDumpException.h"

namespace {

void loadDBStream(std::istream& stream) {
  for(std::string line; std::getline(stream, line);) {
    std::stringstream ss(line);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> tokens(begin, end);
    std::string_view tag(tokens[0]);
    if (tag == "#") {
      continue;
    } else if (tag == "L") {

    }
    //for (std::string token: vstrings) {
    //  std::cout << token << std::endl;
    //}
  }
}

}

namespace naja { namespace SNL {

void SNLDump::loadUniverse(const std::filesystem::path& path) {
  if (not std::filesystem::exists(path)) {
    //create error
    return;
  }
  //load manifest
  SNLDumpManifest manifest = SNLDumpManifest::load(path);
  auto manifestVersion = manifest.getVersion();
  if (manifestVersion not_eq SNLDump::getVersion()) {
    std::ostringstream reason;
    reason << "Incompatible versions while loading SNLDump: ";
    reason << "Loader version is " << SNLDump::getVersion().getString()
      << ", while Dump version is " << manifestVersion.getString();
    throw SNLDumpException(reason.str());
  }
  //Create SNLUniverse if it does not exist
  std::filesystem::path dumpPath(path/DesignDBName);
  if (not std::filesystem::exists(dumpPath)) {
    std::ostringstream reason;
    reason << dumpPath.string() << " is not a valid path";
    throw SNLDumpException(reason.str());
  }
  std::ifstream dbStream;
	dbStream.open(dumpPath, std::ios::in);
  if (not dbStream) {
    std::ostringstream reason;
    reason << "cannot open " << dumpPath.string();
    throw SNLDumpException(reason.str());
  }
  if (not SNLUniverse::get()) {
    SNLUniverse::create();
  }
  loadDBStream(dbStream);
}


}} // namespace SNL // namespace naja