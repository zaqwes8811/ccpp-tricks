//
// Created by zaqwes on 02.01.2022.
//

#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallPtrSet.h>
#include <llvm/ADT/SmallSet.h>
#include <llvm/ADT/SmallVector.h>
//#include <llvm/ADT/ImmutableSet.h>
//#include <llvm/ADT/ImmutableMap.h>
//#include <llvm/ADT/Imm/

#include <gtest/gtest.h>

TEST(LlvmDataStructuresTest, SmallVector) { auto sv = llvm::SmallVector<int, 4>(); }

TEST(LlvmDataStructuresTest, DenseMap) { auto sv = llvm::DenseMap<int, int>(); }

TEST(LlvmDataStructuresTest, ImmutableMap) {
    //    auto sv = llvm::ImmutableMap<int, int>({1, 1});  // Need lot of code to
    //    link
}