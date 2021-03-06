// Copyright 2020 The TensorFlow Runtime Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//===- dataset.cc ---------------------------------------------------------===//
//
// This file implements functions needed by the data pipeline library.
//
//===----------------------------------------------------------------------===//

#include "tfrt/data/dataset.h"

namespace tfrt {
namespace data {
namespace internal {

bool IsConcreteAndEmpty(const IterationResult& result) {
  return result.eof.IsConcrete() && result.eof.get();
}

}  // namespace internal
}  // namespace data
}  // namespace tfrt
