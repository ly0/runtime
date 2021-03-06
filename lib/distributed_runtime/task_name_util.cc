/*
 * Copyright 2020 The TensorFlow Runtime Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//===- task_name_utils.cc -------------------------------------------------===//
//
// Defines utils for task name conversions.
//
//===----------------------------------------------------------------------===//

#include "tfrt/distributed_runtime/task_name_util.h"

#include "llvm/Support/Regex.h"
#include "tfrt/support/error_util.h"
#include "tfrt/support/string_util.h"

namespace tfrt {
std::string TaskNameUtil::ConcatTaskName(string_view job_name, int task_id) {
  return StrCat("/job:", job_name, "/task:", task_id);
}

// Regex pattern for an acceptable task name.
constexpr char kTaskNameRegex[] =
    "^/job:([a-zA-Z][_a-zA-Z0-9]*)/task:([0-9]|[1-9][0-9]+).*$";

Error TaskNameUtil::ParseTaskName(string_view task_name,
                                  std::string* out_job_name, int* out_task_id) {
  llvm::Regex regex(kTaskNameRegex);
  llvm::SmallVector<llvm::StringRef, 2> matches;
  std::string error_message;
  if (!regex.match(task_name, &matches, &error_message)) {
    return llvm::make_error<InvalidArgumentErrorInfo>(
        StrCat("Error parsing task name \"", task_name, "\": ", error_message));
  }
  *out_job_name = matches[1].str();
  // Since the match was got from a regex pattern with [0-9]+, we don't expect
  // any conversion error to an integer.
  llvm::to_integer(matches[2], *out_task_id);
  return Error::success();
}
}  // namespace tfrt
