//===--- Rule15_3_5Check.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Rule15_3_5Check.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {

void Rule15_3_5Check::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(varDecl(allOf(hasParent(cxxCatchStmt()), hasType(cxxRecordDecl(isStruct())))).bind("class_type_exception"), this);
}

void Rule15_3_5Check::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *Matched = Result.Nodes.getNodeAs<VarDecl>("class_type_exception");
    diag(Matched->getBeginLoc(), "A class type exception shall always be caught by reference.")
    << FixItHint::CreateInsertion(Matched->getBeginLoc(),"");
}

} // namespace misra
} // namespace tidy
} // namespace clang
