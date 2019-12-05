// GENERATED FILE - DO NOT EDIT.
// Generated by gen_builtin_symbols.py using data from builtin_variables.json and
// builtin_function_declarations.txt.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ParseContext_ESSL_autogen.h:
//   Helpers for built-in related checks.

#ifndef COMPILER_TRANSLATOR_PARSECONTEXT_AUTOGEN_H_
#define COMPILER_TRANSLATOR_PARSECONTEXT_AUTOGEN_H_

namespace sh
{

namespace BuiltInGroup
{

bool isTextureOffsetNoBias(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3029 && id <= 3098;
}
bool isTextureOffsetBias(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3099 && id <= 3118;
}
bool isTextureGatherOffset(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3156 && id <= 3169;
}
bool isTextureGather(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3132 && id <= 3169;
}
bool isAtomicMemory(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3186 && id <= 3203;
}
bool isImageLoad(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3228 && id <= 3239;
}
bool isImageStore(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3240 && id <= 3251;
}
bool isImage(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3204 && id <= 3251;
}

}  // namespace BuiltInGroup

}  // namespace sh

#endif  // COMPILER_TRANSLATOR_PARSECONTEXT_AUTOGEN_H_
