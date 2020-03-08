// Copyright (c) 2020 André Perez Maselco
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SOURCE_FUZZ_FUZZER_PASS_SWAP_COMMUTABLE_OPERANDS_H_
#define SOURCE_FUZZ_FUZZER_PASS_SWAP_COMMUTABLE_OPERANDS_H_

#include "source/fuzz/fuzzer_pass.h"

namespace spvtools {
namespace fuzz {

// This fuzzer pass searches for all commutative instructions in the module,
// probabilistically choosing which of these instructions will have its input
// operands swapped.
class FuzzerPassSwapCommutableOperands : public FuzzerPass {
 public:
  FuzzerPassSwapCommutableOperands(
      opt::IRContext* ir_context, FactManager* fact_manager,
      FuzzerContext* fuzzer_context,
      protobufs::TransformationSequence* transformations);

  ~FuzzerPassSwapCommutableOperands();

  void Apply() override;
};

}  // namespace fuzz
}  // namespace spvtools

#endif  // SOURCE_FUZZ_FUZZER_PASS_SWAP_COMMUTABLE_OPERANDS_H_
