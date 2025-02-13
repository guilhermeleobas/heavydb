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

/**
 * @file    file_type.h
 * @author  andrew.do@omnisci.com>
 * @brief   shared utility for mime-types
 *
 */

#include <string>

namespace shared {

bool is_compressed_mime_type(const std::string& mime_type);
bool is_compressed_file_extension(const std::string& location);

}  // namespace shared