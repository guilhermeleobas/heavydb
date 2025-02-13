/*
 * Copyright 2021 OmniSci, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "AbstractTextFileDataWrapper.h"
#include "DataMgr/ForeignStorage/RegexFileBufferParser.h"

namespace foreign_storage {
class RegexParserDataWrapper : public AbstractTextFileDataWrapper {
 public:
  RegexParserDataWrapper();

  RegexParserDataWrapper(const int db_id, const ForeignTable* foreign_table);

  RegexParserDataWrapper(const int db_id,
                         const ForeignTable* foreign_table,
                         const UserMapping* user_mapping,
                         const bool disable_cache = false);

  void validateTableOptions(const ForeignTable* foreign_table) const override;

  const std::set<std::string_view>& getSupportedTableOptions() const override;

 protected:
  const TextFileBufferParser& getFileBufferParser() const override;

 private:
  std::set<std::string_view> getAllRegexTableOptions() const;
  static const std::set<std::string_view> regex_table_options_;
  const RegexFileBufferParser regex_file_buffer_parser_;
};
}  // namespace foreign_storage
