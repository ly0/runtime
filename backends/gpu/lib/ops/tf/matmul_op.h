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

//===- matmul_op.h - Declares a function to register tf.matmul --*- C++ -*-===//
//
// Declares a function to register tf.matmul implementation on GPU.
//
//===----------------------------------------------------------------------===//
#ifndef TFRT_BACKENDS_GPU_LIB_OPS_TF_MATMUL_OP_H_
#define TFRT_BACKENDS_GPU_LIB_OPS_TF_MATMUL_OP_H_

#include "tfrt/gpu/blas_support.h"

namespace tfrt {
class GpuOpRegistry;

namespace gpu {
class DenseGpuTensor;
class GpuBuffer;

llvm::Error RunCublasGemm(stream::CurrentContext current,
                          stream::BlasHandle handle, bool transpose_a,
                          bool transpose_b, const DenseGpuTensor& a,
                          const DenseGpuTensor& b, GpuBuffer* result);
}  // namespace gpu

void RegisterMatmulGpuTfOps(GpuOpRegistry* registry);
}  // namespace tfrt

#endif  // TFRT_BACKENDS_GPU_LIB_OPS_TF_MATMUL_OP_H_
