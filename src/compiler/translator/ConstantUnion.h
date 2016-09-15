//
// Copyright (c) 2002-2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef COMPILER_TRANSLATOR_CONSTANTUNION_H_
#define COMPILER_TRANSLATOR_CONSTANTUNION_H_

#include <assert.h>

#include "compiler/translator/Common.h"
#include "compiler/translator/BaseTypes.h"

class TDiagnostics;

class TConstantUnion
{
  public:
    POOL_ALLOCATOR_NEW_DELETE();
    TConstantUnion();

    bool cast(TBasicType newType, const TConstantUnion &constant);

    void setIConst(int i) {iConst = i; type = EbtInt; }
    void setUConst(unsigned int u) { uConst = u; type = EbtUInt; }
    void setFConst(float f) {fConst = f; type = EbtFloat; }
    void setBConst(bool b) {bConst = b; type = EbtBool; }

    int getIConst() const { return iConst; }
    unsigned int getUConst() const { return uConst; }
    float getFConst() const { return fConst; }
    bool getBConst() const { return bConst; }

    bool operator==(const int i) const;
    bool operator==(const unsigned int u) const;
    bool operator==(const float f) const;
    bool operator==(const bool b) const;
    bool operator==(const TConstantUnion &constant) const;
    bool operator!=(const int i) const;
    bool operator!=(const unsigned int u) const;
    bool operator!=(const float f) const;
    bool operator!=(const bool b) const;
    bool operator!=(const TConstantUnion &constant) const;
    bool operator>(const TConstantUnion &constant) const;
    bool operator<(const TConstantUnion &constant) const;
    static TConstantUnion add(const TConstantUnion &lhs,
                              const TConstantUnion &rhs,
                              TDiagnostics *diag,
                              const TSourceLoc &line);
    static TConstantUnion sub(const TConstantUnion &lhs,
                              const TConstantUnion &rhs,
                              TDiagnostics *diag,
                              const TSourceLoc &line);
    static TConstantUnion mul(const TConstantUnion &lhs,
                              const TConstantUnion &rhs,
                              TDiagnostics *diag,
                              const TSourceLoc &line);
    TConstantUnion operator%(const TConstantUnion &constant) const;
    TConstantUnion operator>>(const TConstantUnion &constant) const;
    TConstantUnion operator<<(const TConstantUnion &constant) const;
    TConstantUnion operator&(const TConstantUnion &constant) const;
    TConstantUnion operator|(const TConstantUnion &constant) const;
    TConstantUnion operator^(const TConstantUnion &constant) const;
    TConstantUnion operator&&(const TConstantUnion &constant) const;
    TConstantUnion operator||(const TConstantUnion &constant) const;

    TBasicType getType() const { return type; }
  private:
    union {
        int iConst;           // used for ivec, scalar ints
        unsigned int uConst;  // used for uvec, scalar uints
        bool bConst;          // used for bvec, scalar bools
        float fConst;         // used for vec, mat, scalar floats
    };

    TBasicType type;
};

#endif // COMPILER_TRANSLATOR_CONSTANTUNION_H_
