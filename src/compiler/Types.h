//
// Copyright (c) 2002-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef _TYPES_INCLUDED
#define _TYPES_INCLUDED

#include "compiler/BaseTypes.h"
#include "compiler/Common.h"
#include "compiler/debug.h"

class TType;
struct TPublicType;

//
// Need to have association of line numbers to types in a list for building structs.
//
struct TTypeLine {
    TType* type;
    int line;
};
typedef TVector<TTypeLine> TTypeList;

inline TTypeList* NewPoolTTypeList()
{
    void* memory = GlobalPoolAllocator.allocate(sizeof(TTypeList));
    return new(memory) TTypeList;
}

//
// Base class for things that have a type.
//
class TType
{
public:
    POOL_ALLOCATOR_NEW_DELETE(GlobalPoolAllocator)
    TType() {}
    TType(TBasicType t, TPrecision p, TQualifier q = EvqTemporary, int ps = 1, int ss = 1, bool a = false) :
            type(t), precision(p), qualifier(q), primarySize(ps), secondarySize(ss), array(a), layoutQualifier(TLayoutQualifier::create()), arraySize(0),
            maxArraySize(0), arrayInformationType(0), interfaceBlockType(0), structure(0), structureSize(0), deepestStructNesting(0), fieldName(0), mangled(0), typeName(0), instanceName(0)
    {
    }
    explicit TType(const TPublicType &p);
    TType(TTypeList* userDef, const TString& n, TPrecision p = EbpUndefined) :
            type(EbtStruct), precision(p), qualifier(EvqTemporary), primarySize(1), secondarySize(1), array(false), layoutQualifier(TLayoutQualifier::create()), arraySize(0),
            maxArraySize(0), arrayInformationType(0), interfaceBlockType(0), structure(userDef), structureSize(0), deepestStructNesting(0), fieldName(0), mangled(0), instanceName(0)
    {
        typeName = NewPoolTString(n.c_str());
    }

    TBasicType getBasicType() const { return type; }
    void setBasicType(TBasicType t) { type = t; }

    TPrecision getPrecision() const { return precision; }
    void setPrecision(TPrecision p) { precision = p; }

    TQualifier getQualifier() const { return qualifier; }
    void setQualifier(TQualifier q) { qualifier = q; }

    TLayoutQualifier getLayoutQualifier() const { return layoutQualifier; }
    void setLayoutQualifier(TLayoutQualifier lq) { layoutQualifier = lq; }

    int getNominalSize() const { return primarySize; }
    int getSecondarySize() const { return secondarySize; }
    int getCols() const { ASSERT(isMatrix()); return primarySize; }
    int getRows() const { ASSERT(isMatrix()); return secondarySize; }
    void setPrimarySize(int ps) { primarySize = ps; }
    void setSecondarySize(int ss) { secondarySize = ss; }

    // Full size of single instance of type
    int getObjectSize() const
    {
        int totalSize;

        if (getBasicType() == EbtStruct)
            totalSize = getStructSize();
        else
            totalSize = primarySize * secondarySize;

        if (isArray())
            totalSize *= std::max(getArraySize(), getMaxArraySize());

        return totalSize;
    }

    int elementRegisterCount() const
    {
        TTypeList *structure = getStruct();

        if (structure)
        {
            int registerCount = 0;

            for (size_t i = 0; i < structure->size(); i++)
            {
                registerCount += (*structure)[i].type->totalRegisterCount();
            }

            return registerCount;
        }
        else if (isMatrix())
        {
            return getRows();
        }
        else
        {
            return 1;
        }
    }

    int totalRegisterCount() const
    {
        if (array)
        {
            return arraySize * elementRegisterCount();
        }
        else
        {
            return elementRegisterCount();
        }
    }

    bool isMatrix() const { return primarySize > 1 && secondarySize > 1; }
    bool isArray() const  { return array ? true : false; }
    int getArraySize() const { return arraySize; }
    void setArraySize(int s) { array = true; arraySize = s; }
    int getMaxArraySize () const { return maxArraySize; }
    void setMaxArraySize (int s) { maxArraySize = s; }
    void clearArrayness() { array = false; arraySize = 0; maxArraySize = 0; }
    void setArrayInformationType(TType* t) { arrayInformationType = t; }
    TType* getArrayInformationType() const { return arrayInformationType; }
    void setInterfaceBlockType(TType* t) { interfaceBlockType = t; }
    TType* getInterfaceBlockType() const { return interfaceBlockType; }
    bool isInterfaceBlockMember() const { return interfaceBlockType != NULL; }

    bool isVector() const { return primarySize > 1 && secondarySize == 1; }
    bool isScalar() const { return primarySize == 1 && secondarySize == 1 && !structure; }
    bool isScalarInt() const { return isScalar() && (type == EbtInt || type == EbtUInt); }

    TTypeList* getStruct() const { return structure; }
    void setStruct(TTypeList* s) { structure = s; computeDeepestStructNesting(); }

    const TString& getTypeName() const
    {
        assert(typeName);
        return *typeName;
    }
    void setTypeName(const TString& n)
    {
        typeName = NewPoolTString(n.c_str());
    }

    bool isField() const { return fieldName != 0; }
    const TString& getFieldName() const
    {
        assert(fieldName);
        return *fieldName;
    }
    void setFieldName(const TString& n)
    {
        fieldName = NewPoolTString(n.c_str());
    }

    TString& getMangledName() {
        if (!mangled) {
            mangled = NewPoolTString("");
            buildMangledName(*mangled);
            *mangled += ';' ;
        }

        return *mangled;
    }

    void setInstanceName(const TString& n)
    {
        assert(type == EbtInterfaceBlock);
        instanceName = NewPoolTString(n.c_str());
    }

    bool hasInstanceName() const
    {
        assert(type == EbtInterfaceBlock);
        return instanceName != NULL;
    }

    const TString& getInstanceName() const
    {
        assert(type == EbtInterfaceBlock);
        assert(instanceName);
        return *instanceName;
    }

    bool sameElementType(const TType& right) const {
        return      type == right.type          &&
             primarySize == right.primarySize   &&
           secondarySize == right.secondarySize &&
               structure == right.structure;
    }
    bool operator==(const TType& right) const {
        return      type == right.type          &&
             primarySize == right.primarySize   &&
           secondarySize == right.secondarySize &&
                   array == right.array && (!array || arraySize == right.arraySize) &&
               structure == right.structure;
        // don't check the qualifier, it's not ever what's being sought after
    }
    bool operator!=(const TType& right) const {
        return !operator==(right);
    }
    bool operator<(const TType& right) const {
        if (type != right.type) return type < right.type;
        if (primarySize != right.primarySize) return primarySize < right.primarySize;
        if (secondarySize != right.secondarySize) return secondarySize < right.secondarySize;
        if (array != right.array) return array < right.array;
        if (arraySize != right.arraySize) return arraySize < right.arraySize;
        if (structure != right.structure) return structure < right.structure;

        return false;
    }

    const char* getBasicString() const { return ::getBasicString(type); }
    const char* getPrecisionString() const { return ::getPrecisionString(precision); }
    const char* getQualifierString() const { return ::getQualifierString(qualifier); }
    TString getCompleteString() const;

    // If this type is a struct, returns the deepest struct nesting of
    // any field in the struct. For example:
    //   struct nesting1 {
    //     vec4 position;
    //   };
    //   struct nesting2 {
    //     nesting1 field1;
    //     vec4 field2;
    //   };
    // For type "nesting2", this method would return 2 -- the number
    // of structures through which indirection must occur to reach the
    // deepest field (nesting2.field1.position).
    int getDeepestStructNesting() const { return deepestStructNesting; }

    bool isStructureContainingArrays() const;

protected:
    void buildMangledName(TString&);
    int getStructSize() const;
    void computeDeepestStructNesting();

    TBasicType type      : 6;
    TPrecision precision : 4;
    TQualifier qualifier : 7;
    unsigned int array   : 1;
    TLayoutQualifier layoutQualifier;
    int primarySize; // size of vector or cols matrix
    int secondarySize; // rows of a matrix
    int arraySize;
    int maxArraySize;
    TType* arrayInformationType;
    TType* interfaceBlockType;

    TTypeList* structure;      // 0 unless this is a struct
    mutable int structureSize;
    int deepestStructNesting;

    TString *fieldName;         // for structure field names
    TString *mangled;
    TString *typeName;          // for structure field type name
    TString *instanceName;      // for interface block instance names
};

//
// This is a workaround for a problem with the yacc stack,  It can't have
// types that it thinks have non-trivial constructors.  It should
// just be used while recognizing the grammar, not anything else.  Pointers
// could be used, but also trying to avoid lots of memory management overhead.
//
// Not as bad as it looks, there is no actual assumption that the fields
// match up or are name the same or anything like that.
//
struct TPublicType
{
    TBasicType type;
    TLayoutQualifier layoutQualifier;
    TQualifier qualifier;
    TPrecision precision;
    int primarySize;          // size of vector or cols of matrix
    int secondarySize;        // rows of matrix
    bool array;
    int arraySize;
    TType* userDef;
    int line;

    void setBasic(TBasicType bt, TQualifier q, int ln = 0)
    {
        type = bt;
        layoutQualifier = TLayoutQualifier::create();
        qualifier = q;
        precision = EbpUndefined;
        primarySize = 1;
        secondarySize = 1;
        array = false;
        arraySize = 0;
        userDef = 0;
        line = ln;
    }

    void setAggregate(int size)
    {
        primarySize = size;
    }

    void setMatrix(int c, int r)
    {
        ASSERT(c > 1 && r > 1 && c <= 4 && r <= 4);
        primarySize = c;
        secondarySize = r;
    }

    void setArray(bool a, int s = 0)
    {
        array = a;
        arraySize = s;
    }

    bool isStructureContainingArrays() const
    {
        if (!userDef)
        {
            return false;
        }

        return userDef->isStructureContainingArrays();
    }

    bool isMatrix() const
    {
        return primarySize > 1 && secondarySize > 1;
    }

    bool isVector() const
    {
        return primarySize > 1 && secondarySize == 1;
    }

    int getCols() const
    {
        ASSERT(isMatrix());
        return primarySize;
    }

    int getRows() const
    {
        ASSERT(isMatrix());
        return secondarySize;
    }

    int getNominalSize() const
    {
        return primarySize;
    }

    bool isAggregate() const
    {
        return array || isMatrix() || isVector();
    }
};

#endif // _TYPES_INCLUDED_
