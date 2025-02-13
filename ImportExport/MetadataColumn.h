/*
 * Copyright 2022 OmniSci, Inc.
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

/*
 * @file MetadataColumn.h
 * @author Simon Eves <simon.eves@omnisci.com>
 * @brief Metadata Column info struct and parser
 */

#pragma once

#include <string>

#include "Catalog/ColumnDescriptor.h"

namespace import_export {

struct MetadataColumnInfo {
  ColumnDescriptor column_descriptor;
  std::string value;
};

using MetadataColumnInfos = std::vector<MetadataColumnInfo>;

MetadataColumnInfos parse_add_metadata_columns(const std::string& add_metadata_columns,
                                               const std::string& file_path);

}  // namespace import_export
