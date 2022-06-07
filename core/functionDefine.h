#pragma once
#include <memory>
#include "kernalDefine.h"

#ifndef VOXL_FUNCTION_DEF_H_
#    define VOXL_FUNCTION_DEF_H_

#    define DELETE_OBJ_NAKED_PTR(objPtr) \
        if (objPtr)                      \
        {                                \
            delete objPtr;               \
            objPtr = nullptr;            \
        }

#    define CREATE_OBJ_NAKED_PTR(objPtr, ClassType, ...) \
        if (objPtr == nullptr)                           \
        {                                                \
            objPtr = new ClassType(__VA_ARGS__);         \
        }
#    define DELETE_OBJ_SHARED_PTR(objPtr) \
        objPtr = nullptr;

#    define DEFINE_OBJ_SHARED_PTR(ptrName, ClassType) \
    std::shared_ptr<ClassType> ptrName

#    define CREATE_OBJ_SHARED_PTR(objSharedPtr, ClassType, ...)      \
        if (objSharedPtr == nullptr)                                 \
        {                                                            \
            objSharedPtr = std::make_shared<ClassType>(__VA_ARGS__); \
        }

#    define DEFINE_AND_CREATE_OBJ_SHARED_PTR(ptrName, ClassType, ...) \
    DEFINE_OBJ_SHARED_PTR(ptrName, ClassType);              \
    CREATE_OBJ_SHARED_PTR(ptrName, ClassType, __VA_ARGS__);

#    define MAKE_OBJ_SHARED_PTR(ptrName, ClassType, ...) \
        DEFINE_AND_CREATE_OBJ_SHARED_PTR(ptrName, ClassType, __VA_ARGS__);

#endif
