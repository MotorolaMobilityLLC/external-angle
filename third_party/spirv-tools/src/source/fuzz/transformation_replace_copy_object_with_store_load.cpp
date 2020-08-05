// Copyright (c) 2020 Google LLC
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

#include "source/fuzz/transformation_replace_copy_object_with_store_load.h"

#include "source/fuzz/fuzzer_util.h"
#include "source/fuzz/instruction_descriptor.h"

namespace spvtools {
namespace fuzz {

TransformationReplaceCopyObjectWithStoreLoad::
    TransformationReplaceCopyObjectWithStoreLoad(
        const spvtools::fuzz::protobufs::
            TransformationReplaceCopyObjectWithStoreLoad& message)
    : message_(message) {}

TransformationReplaceCopyObjectWithStoreLoad::
    TransformationReplaceCopyObjectWithStoreLoad(
        uint32_t copy_object_result_id, uint32_t fresh_variable_id,
        uint32_t variable_storage_class, uint32_t variable_initializer_id) {
  message_.set_copy_object_result_id(copy_object_result_id);
  message_.set_fresh_variable_id(fresh_variable_id);
  message_.set_variable_storage_class(variable_storage_class);
  message_.set_variable_initializer_id(variable_initializer_id);
}

bool TransformationReplaceCopyObjectWithStoreLoad::IsApplicable(
    opt::IRContext* ir_context, const TransformationContext& /*unused*/) const {
  // |message_.fresh_variable_id| must be fresh.
  if (!fuzzerutil::IsFreshId(ir_context, message_.fresh_variable_id())) {
    return false;
  }
  auto copy_object_instruction =
      ir_context->get_def_use_mgr()->GetDef(message_.copy_object_result_id());

  // This must be a defined OpCopyObject instruction.
  if (!copy_object_instruction ||
      copy_object_instruction->opcode() != SpvOpCopyObject) {
    return false;
  }

  // The opcode of the type_id instruction cannot be a OpTypePointer,
  // because we cannot define a pointer to pointer.
  if (ir_context->get_def_use_mgr()
          ->GetDef(copy_object_instruction->type_id())
          ->opcode() == SpvOpTypePointer) {
    return false;
  }

  // It must be valid to insert the OpStore and OpLoad instruction before it.
  if (!fuzzerutil::CanInsertOpcodeBeforeInstruction(SpvOpStore,
                                                    copy_object_instruction) ||
      !fuzzerutil::CanInsertOpcodeBeforeInstruction(SpvOpLoad,
                                                    copy_object_instruction)) {
    return false;
  }

  // A pointer type instruction pointing to the value type must be defined.
  auto pointer_type_id = fuzzerutil::MaybeGetPointerType(
      ir_context, copy_object_instruction->type_id(),
      static_cast<SpvStorageClass>(message_.variable_storage_class()));
  if (!pointer_type_id) {
    return false;
  }

  // Check that initializer is valid.
  const auto* constant_inst =
      ir_context->get_def_use_mgr()->GetDef(message_.variable_initializer_id());
  if (!constant_inst || !spvOpcodeIsConstant(constant_inst->opcode()) ||
      copy_object_instruction->type_id() != constant_inst->type_id()) {
    return false;
  }
  // |message_.variable_storage_class| must be Private or Function.
  return message_.variable_storage_class() == SpvStorageClassPrivate ||
         message_.variable_storage_class() == SpvStorageClassFunction;
}

void TransformationReplaceCopyObjectWithStoreLoad::Apply(
    opt::IRContext* ir_context,
    TransformationContext* transformation_context) const {
  auto copy_object_instruction =
      ir_context->get_def_use_mgr()->GetDef(message_.copy_object_result_id());
  // |copy_object_instruction| must be defined.
  assert(copy_object_instruction &&
         copy_object_instruction->opcode() == SpvOpCopyObject &&
         "The required OpCopyObject instruction must be defined.");
  // Get id used as a source by the OpCopyObject instruction.
  uint32_t src_operand = copy_object_instruction->GetSingleWordOperand(2);
  // A pointer type instruction pointing to the value type must be defined.
  auto pointer_type_id = fuzzerutil::MaybeGetPointerType(
      ir_context, copy_object_instruction->type_id(),
      static_cast<SpvStorageClass>(message_.variable_storage_class()));
  assert(pointer_type_id && "The required pointer type must be available.");

  // Adds a global or local variable (according to the storage class).
  if (message_.variable_storage_class() == SpvStorageClassPrivate) {
    fuzzerutil::AddGlobalVariable(ir_context, message_.fresh_variable_id(),
                                  pointer_type_id, SpvStorageClassPrivate,
                                  message_.variable_initializer_id());
  } else {
    auto function_id = ir_context->get_instr_block(copy_object_instruction)
                           ->GetParent()
                           ->result_id();
    fuzzerutil::AddLocalVariable(ir_context, message_.fresh_variable_id(),
                                 pointer_type_id, function_id,
                                 message_.variable_initializer_id());
  }

  // First, insert the OpLoad instruction before the OpCopyObject instruction
  // and then insert the OpStore instruction before the OpLoad instruction.
  fuzzerutil::UpdateModuleIdBound(ir_context, message_.fresh_variable_id());
  copy_object_instruction
      ->InsertBefore(MakeUnique<opt::Instruction>(
          ir_context, SpvOpLoad, copy_object_instruction->type_id(),
          message_.copy_object_result_id(),
          opt::Instruction::OperandList(
              {{SPV_OPERAND_TYPE_ID, {message_.fresh_variable_id()}}})))
      ->InsertBefore(MakeUnique<opt::Instruction>(
          ir_context, SpvOpStore, 0, 0,
          opt::Instruction::OperandList(
              {{SPV_OPERAND_TYPE_ID, {message_.fresh_variable_id()}},
               {SPV_OPERAND_TYPE_ID, {src_operand}}})));
  // Remove the CopyObject instruction.
  ir_context->KillInst(copy_object_instruction);

  ir_context->InvalidateAnalysesExceptFor(opt::IRContext::kAnalysisNone);

  // Adds the fact that |message_.copy_object_result_id|
  // and src_operand (id used by OpCopyObject) are synonymous.
  transformation_context->GetFactManager()->AddFactDataSynonym(
      MakeDataDescriptor(message_.copy_object_result_id(), {}),
      MakeDataDescriptor(src_operand, {}), ir_context);
}

protobufs::Transformation
TransformationReplaceCopyObjectWithStoreLoad::ToMessage() const {
  protobufs::Transformation result;
  *result.mutable_replace_copy_object_with_store_load() = message_;
  return result;
}

}  // namespace fuzz
}  // namespace spvtools
